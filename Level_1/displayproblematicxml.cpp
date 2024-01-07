#include "displayproblematicxml.h"
string getOpenTag(string t){
    int start = -1;    int end = -1;
    start = t.find("<", 0);    end = t.find(">", start);
    if (start != -1 && t[start + 1] != '/' && t[start + 1] != '?' && t[start + 1] != '!')        return t.substr(start + 1, end - start - 1);
    else        return "False";
}
string getClosedTag(string t){
    int start = -1;    int end = -1;
    start = t.find("/", 0);    end = t.find(">", start);
    if (start != -1)        return t.substr(start + 1, end - start - 1);
    else        return "False";
}

bool error_detector(string openTag , string closedTag , stack <string>& tagStack , string& errorType){
    stack <string> temp;

    if (openTag != "False" && closedTag != "False")
    {
        if (openTag != closedTag)
        {
            errorType = "Mismatching tags: " + openTag + " and " + closedTag;
            return false;
        }
    }
    if (openTag != "False")
    {
        tagStack.push(openTag);    // valid open tag is pushed into stack
    }
    if (closedTag != "False")
    {
        if (tagStack.empty())     // closed tag with no opening tag
        {
            errorType = "<" + closedTag + ">";
            return false;
        }
        else{

            if (closedTag == tagStack.top())
            {
                tagStack.pop();
            }
            else
            {
                while (!tagStack.empty() && closedTag != tagStack.top())
                {
                    temp.push(tagStack.top());
                    tagStack.pop();              // stored the mismatched top of the tag stack to another stack
                }
                if (tagStack.empty())
                {
                    errorType = "<" + closedTag + ">";    // closed tag with no open tag
                    while (!temp.empty())
                    {
                        tagStack.push(temp.top());        // resotring elements of temp into the original tag stack
                        temp.pop();
                    }

                }
                else                                    // opening tag at the top of the stack with no closing tag
                {
                    tagStack.pop();
                    while (!temp.empty())
                    {
                        tagStack.push(temp.top());        // resotring elements of temp into the original tag stack
                        temp.pop();
                    }
                    errorType = "</" + tagStack.top() + ">";
                    tagStack.pop();
                }
                return false;
            }
        }
        return true;
    }
    return true;
}

vector <err_data> detectError(vector<string> xmlVectorFile){
    vector<err_data> ErrorsVector;
    stack <string> tagStack;
    err_data errorData;
    string errorType;
    string line;
    int err_loc = -1;
    string openTag;
    string closedTag;



    for (int i = 0; i < xmlVectorFile.size(); i++)
    {
        line = xmlVectorFile[i];
        openTag = getOpenTag(line);
        closedTag = getClosedTag(line);

        if (openTag != "False" || closedTag != "False")
        {
            if (!error_detector(openTag ,  closedTag , tagStack , errorType))
            {
                if (errorType.size() > 24)           // 24 is the minimum number of characters for mismatchin tags error
                {
                    errorData.err_type = errorType;
                    errorData.err_loc = i;
                    ErrorsVector.push_back(errorData);
                }
                else
                {
                    errorData.err_type = errorType;
                    errorData.err_loc = i;
                    ErrorsVector.push_back(errorData);
                }
            }
        }
    }

    int i = xmlVectorFile.size();
    while (!tagStack.empty())
    {
        string err = "</" + tagStack.top() + ">";
        errorData.err_type = err;
        errorData.err_loc = i;
        ErrorsVector.push_back(errorData);
        i++;
        tagStack.pop();

    }

    return ErrorsVector;
}

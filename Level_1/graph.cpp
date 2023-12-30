#include "graph.h"

void Graph::addUser(User u1) {
    user_vector[u1.getID()] = u1;
    follower_edge[u1.getID()] = u1.getFollowers();
}

void Graph::printfollowers(string id) {
    for (auto follower : follower_edge[id]) {
        cout << follower << " ";
    }
    cout << endl;
}

unordered_map<string, vector<string>> Graph::get_follower_edge()
{
    return follower_edge;
}

unordered_map<string, User> Graph::get_user_vector()
{
    return user_vector;
}

User Graph::most_influencer() {
    int max = 0, followerNumber;
    string id;
    for (auto it : follower_edge) {
        if (!follower_edge[it.first].empty()) {
            followerNumber = follower_edge[it.first].size();
            if (followerNumber > max) {
                max = followerNumber;
                id = it.first;
            }
        }
    }
    return user_vector[id];
}

User Graph::most_active() {
    int max = 0;
    string id;
    unordered_map<string, int> visited;
    for (auto it : follower_edge) {
        for (auto follower : it.second) {
            visited[follower]++;
        }
    }
    for (auto it : visited) {
        if (it.second > max) {
            max = it.second;
            id = it.first;
        }
    }
    return user_vector[id];
}

vector<User> Graph::mutual_followers(string id1, string id2) {
    vector<User> mutual_friend;
    for (auto follower1 : follower_edge[id1]) {
        for (auto follower2 : follower_edge[id2]) {
            if (follower1 == follower2)
                mutual_friend.push_back(user_vector[follower1]);
        }
    }
    return mutual_friend;
}

string Graph::print_mutual_followers(string id1, string id2) {
    vector<User> mutual_friends = mutual_followers(id1, id2);

    if (mutual_friends.empty()) {
        return "No mutual followers between " + user_vector[id1].getName() + " and " + user_vector[id2].getName();
    }

    string result = "Mutual Followers between " + user_vector[id1].getName() + " and " + user_vector[id2].getName() + ":\n";

    for (auto mutual_friend : mutual_friends) {
        result += " - " + mutual_friend.getName() + " ID(" + mutual_friend.getID() + ")\n";
    }

    return result;
}

bool Graph::not_old_follower(vector<string> old_follower, string id) {
    for (auto old : old_follower) {
        if (id == old)
            return false;
    }
    return true;
}

vector<User> Graph::follow_suggestion(string id) {
    vector<User> suggestion_friend;
    string followerID, follower_of_follower;
    vector<string> old_follower = follower_edge[id];
    for (auto followerID : follower_edge[id]) {
        for (auto follower_of_follower : follower_edge[followerID]) {
            if (follower_of_follower != id  && not_old_follower(old_follower, follower_of_follower)) {
                suggestion_friend.push_back(user_vector[follower_of_follower]);
                old_follower.push_back(follower_of_follower);
            }
        }
    }
    return suggestion_friend;
}

string Graph::print_follow_suggestion(string id) {
    vector<User> suggestion_friends = follow_suggestion(id);

    if (suggestion_friends.empty()) {
        return "No follow suggestions for " + user_vector[id].getName();
    }

    string result = "Follow Suggestions for " + user_vector[id].getName() + ":\n";

    for (auto suggested_friend : suggestion_friends) {
        result += " - " + suggested_friend.getName() + " ID(" + suggested_friend.getID() + ")\n";
    }

    return result;
}

vector<string> Graph::post_search(string topic)
{
    vector<string> p;
    int checked_post;
    for (auto user : user_vector) {
        for (auto post : user.second.getPosts()) {
            checked_post = post.first.find(topic);
            if (checked_post != -1){
                p.push_back(post.first);
            }
            if (user.second.hasTopicInPosts(topic)) {
                for (int i = 0; i < post.second.size(); i++) {
                    if (post.second[i] == topic)
                        p.push_back(post.first);
                }
            }
        }
    }
    return p;
}


string Graph::print_post_search(string topic) {
    vector<string> posts = post_search(topic);

    if (posts.empty()) {
        return "No posts found for the topic: " + topic;
    }

    string result = "Posts related to the topic '" + topic + "':\n";

    for (auto post : posts) {
        result += " - " + post + "\n";
    }

    return result;
}

void Graph::print()
{
    for (auto it : user_vector) {
        cout << "(User  "<< it.first<<")\n";
        it.second.printUser();
        cout << "===================================" << endl;
    }
}


Graph createGraphOfUsers(string xmlText) {
    Graph ouput;
    Helpers helper;
    xmlText = helper.prepare(xmlText);
    vector<string> elements = helper.convertXMLToVector(xmlText);
    string name = "", id = "", postBody = "";

    for (int i = 0; i < elements.size(); i++) {
        if (elements[i] == "user" || elements[i] == "_user") {
            vector<pair<string, vector<string>>> posts;
            vector<string>followers;
            string closeUser = '/' + elements[i];
            i++;
            while (elements[i] != closeUser) {
                if (elements[i] == "name" || elements[i] == "_name") {
                    i++;
                    if (elements[i].substr(0, 4) == ";<?>") {
                        name = elements[i].substr(4, elements[i].length() - 4);
                    }
                }
                else if (elements[i] == "id" || elements[i] == "_id") {
                    i++;
                    if (elements[i].substr(0, 4) == ";<?>") {
                        id = elements[i].substr(4, elements[i].length() - 4);
                    }
                }
                else if (elements[i] == "followers" || elements[i] == "_followers") {
                    string closeFollowers = '/' + elements[i];
                    i++;
                    while (elements[i] != closeFollowers) {
                        if (elements[i].substr(0, 4) == ";<?>") {
                            followers.push_back(elements[i].substr(4, elements[i].length() - 4));
                        }
                        i++;
                    }
                }
                else if (elements[i] == "posts" || elements[i] == "_posts") {
                    string closePosts = '/' + elements[i];
                    i++;
                    while (elements[i] != closePosts) {
                        if (elements[i] == "post" || elements[i] == "_post") {
                            vector<string> postTopics;
                            string closePost = '/' + elements[i];
                            i++;
                            if (elements[i].substr(0, 4) == ";<?>") {
                                postBody = elements[i].substr(4, elements[i].length() - 4);
                            }
                            while (elements[i] != closePost) {
                                if (elements[i] == "topic" || elements[i] == "_topic") {
                                    i++;
                                    if (elements[i].substr(0, 4) == ";<?>") {
                                        postTopics.push_back(elements[i].substr(4, elements[i].length() - 4));
                                    }
                                }
                                else if (elements[i] == "body" || elements[i] == "_body") {
                                    i++;
                                    if (elements[i].substr(0, 4) == ";<?>") {
                                        postBody = elements[i].substr(4, elements[i].length() - 4);
                                    }
                                }
                                i++;
                            }
                            posts.push_back(make_pair(postBody, postTopics));
                        }
                        i++;
                    }
                }
                i++;
            }
            User user(name, id, followers, posts);
            // user.print_user();
            ouput.addUser(user);
        }
    }
    return ouput;
}

#include "Compression.h"


// Generate Huffman tree and codes
HuffmanNode* HuffmanTree::buildHuffmanTree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare>& pq) {
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();

        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* internalNode = new HuffmanNode('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    return pq.top();
}

// Traverse the Huffman tree to generate codes
void HuffmanTree::generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->character != '\0') {
        huffmanCodes[root->character] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Encode the input data using Huffman codes
string HuffmanTree::encodedata(string input, unordered_map<char, string>& huffmanCodes) {
    string encodeddata = "";
    for (char c : input) {
        encodeddata += huffmanCodes[c];
    }
    string compressData = byteToChar(encodeddata);
    return compressData;
}

string HuffmanTree::byteToChar(string data)
{
    string output;
    for (int i = 0; i < data.size(); i = i + 8) {
        output += binaryStringToChar (data.substr(i, 8));
    }
    return output;
}

char HuffmanTree::binaryStringToChar(const string& binaryString) {
    // Convert binary string to integer
    int intValue = bitset<8>(binaryString).to_ulong();

    // Convert integer to char
    char charValue = static_cast<char>(intValue);

    return charValue;
}

string HuffmanTree::compress(string input) {
    //Count the frequency of each character
    unordered_map<char, int> frequencyMap;
    for (char c : input) {
        frequencyMap[c]++;
    }

    //Create nodes for each character and insert into priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto entry : frequencyMap) {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }

    // Build Huffman tree
    root = buildHuffmanTree(pq);

    // Generate Huffman codes
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Step 5: Encode the input word
    string compress_data = encodedata(input, huffmanCodes);
    return compress_data;
}



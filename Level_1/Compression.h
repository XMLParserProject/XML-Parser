#pragma once
#include<iostream>
#include<string>
#include<queue>
#include<unordered_map>
#include <bitset>
using namespace std;

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char Character, int Frequency) : character(Character), frequency(Frequency), left(nullptr), right(nullptr) {}
};

// Comparison function for the priority queue
struct Compare {
    bool operator()(HuffmanNode* L, HuffmanNode* R) const {
        if (L->frequency == R->frequency)
            return L->character > L->character;
        return L->frequency > R->frequency;
    }
};

class HuffmanTree {
private:
    HuffmanNode* root;
    // Generate Huffman tree and codes
    HuffmanNode* buildHuffmanTree(priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare>& pq);
    // Traverse the Huffman tree to generate codes
    void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes);
    // Encode the input word using Huffman codes
    string encodedata(string input, unordered_map<char, string>& huffmanCodes);

    char binaryStringToChar(const string& binaryString);

    string byteToChar(string data);

public:
    HuffmanTree() : root(nullptr) {}

    ~HuffmanTree() {

    }

    string compress(string input);

};

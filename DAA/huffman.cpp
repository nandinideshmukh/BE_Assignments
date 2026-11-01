#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; 
    }
};

void printCodes(Node* root, string str) {
    if (!root) return;

    if (!root->left && !root->right) {
        cout << root->ch << ": " << str << "\n";
    }

    printCodes(root->left, str + "0");  
    printCodes(root->right, str + "1");
}

void buildHuffmanTree(const unordered_map<char, int>& freqMap) {
    // pq works inversely
    priority_queue<Node*, vector<Node*>, Compare> minHeap;

    for (auto pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    printCodes(minHeap.top(), "");
}

int main() {
    string text = "huffman";
    
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    cout << "Generated Huffman Codes:\n";
    buildHuffmanTree(freqMap);

    return 0;
}

#include <iostream>
#include <string>

// A dictionary Implementation

struct Node {
    std::string *word, *meaning;
    Node *left, *right;

    Node(std::string *newWord, std::string *newMeaning) {
        this->word = newWord;
        this->meaning = newMeaning;
        this->left = nullptr;
        this->right = nullptr;
    };
};

class Dictionary {
   private:
    Node *root;

   public:
    Dictionary() { this->root = nullptr; };

    void insert(std::string *newWord, std::string *newMeaning) {
        Node *newNode = new Node(newWord, newMeaning);

        if (!root) {
            root = newNode;
            return;
        }

        Node *currNode = root;

        while (currNode->left != nullptr || currNode->right != nullptr) {
            if (newNode->word < currNode->word) {
                currNode = currNode->left;
            } else {
                currNode = currNode->right;
            }
        }

        if (currNode->left == nullptr) {
            currNode->left = newNode;
        } else {
            currNode->right = newNode;
        }
    };

    void remove(Node *currNode){

    };

    void inOrderTraversal(Node *currNode) {
        if (currNode == nullptr) {
            return;
        }
        inOrderTraversal(currNode->left);
        std::cout << *currNode->word << " : " << *currNode->meaning << "\n";
        inOrderTraversal(currNode->right);
    };

    Node *getRoot() { return this->root; };
};

int main() {
    Dictionary myDict;

    std::string newWord = "Hellow";
    std::string newMeaning = "Greetin";
    myDict.insert(&newWord, &newMeaning);

    std::string word1 = "Latte";
    std::string meaning1 = "Coffee";
    myDict.insert(&word1, &meaning1);

    std::string word2 = "Yellow";
    std::string meaning2 = "Color";
    myDict.insert(&word2, &meaning2);

    myDict.inOrderTraversal(myDict.getRoot());

    return 0;
}
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

    void insert(std::string *word, std::string *meaning) {
        Node *newNode = new Node(word, meaning);

        if (!root) {
            root = newNode;
            return;
        }

        Node *curr = root;
        Node *parent = nullptr;

        while (curr != nullptr) {
            parent = curr;
            if (*newNode->word < *curr->word) {
                curr = curr->left;
            } else if (*newNode->word > *curr->word) {
                curr = curr->right;
            } else {
                return;  // simply return if duplicate element is inserted
            }
        }

        if (parent->left == nullptr) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    };

    void remove(std::string *word) {
        // case 0, BST does not exist
        if (!root) {
            std::cout << "Empty dictionary.\n";
            return;
        }

        // case 1, leaf node
        Node *curr = this->root;
        Node *parent = curr;

        while (curr != nullptr) {
            if (*word < *curr->word) {
                parent = curr;
                curr = curr->left;
            } else if (*word > *curr->word) {
                parent = curr;
                curr = curr->right;
            } else {
                std::cout << "Found element.\n";
                break;  // found element
            }
        }

        if (curr == nullptr) {
            std::cout << "Not found to be deleted.\n";
            return;
        }

        if (*parent->left->word == *word) {
            Node *tmp = parent->left;
            parent->left = nullptr;
            delete tmp;
        } else {
            Node *tmp = parent->right;
            parent->right = nullptr;
            delete tmp;
        }

        // case 1 and 2 will be implemented soon
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

    std::string word3 = "Yellow";
    std::string meaning3 = "Color";
    myDict.insert(&word3, &meaning3);

    std::string tempWord = "Green";

    myDict.remove(&word3);

    myDict.inOrderTraversal(myDict.getRoot());

    return 0;
}
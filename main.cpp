#include <string.h>

#include <iostream>

// A dictionary Implementation

struct Node {
    std::string word, meaning;
    Node *left, *right;

    Node(std::string newWord, std::string newMeaning)
        : word(newWord), meaning(newMeaning), left(nullptr), right(nullptr) {}
};

class Dictionary {
   private:
    Node *root;

   public:
    Dictionary() { this->root = nullptr; };

    void insert(std::string word, std::string meaning) {
        Node *newNode = new Node(word, meaning);

        if (!root) {
            root = newNode;
            return;
        }

        Node *curr = root;
        Node *parent = nullptr;

        while (curr != nullptr) {
            if (newNode->word.compare(curr->word) < 0) {
                parent = curr;
                curr = curr->left;
            } else if (newNode->word.compare(curr->word) > 0) {
                parent = curr;
                curr = curr->right;
            } else {
                return;  // simply return if duplicate element is inserted
            }
        }

        if (parent->word.compare(word) > 0) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    };

    std::pair<Node *, Node *> search(std::string word) {
        Node *curr = root;
        Node *parent = curr;

        while (curr != nullptr) {
            if (word.compare(curr->word) < 0) {
                parent = curr;
                curr = curr->left;
            } else if (word.compare(curr->word) > 0) {
                parent = curr;
                curr = curr->right;
            } else {
                break;  // found element
            }
        }

        return std::make_pair(curr, parent);
    };

    bool remove(std::string word) {
        // case 0, BST does not exist
        if (!root) {
            return false;
        }

        // BST exists, we search for Node with key word
        std::pair<Node *, Node *> found = search(word);
        Node *foundNode = found.first;
        Node *parentNode = found.second;

        if (foundNode == nullptr) {
            return false;
        }

        // case 1, leaf node
        if (foundNode->left == nullptr && foundNode->right == nullptr) {
            if (parentNode->left->word == word) {
                Node *tmp = parentNode->left;
                parentNode->left = nullptr;
                delete tmp;
            } else {
                Node *tmp = parentNode->right;
                parentNode->right = nullptr;
                delete tmp;
            }
            return true;  // successfully deleted
        }
        // case 2, one child
        else if (foundNode->left == nullptr || foundNode->right == nullptr) {
            Node *temp = foundNode;
            Node *foundNodeChild =
                foundNode->left != nullptr ? foundNode->left : foundNode->right;

            if (parentNode->left == foundNode) {
                parentNode->left = foundNodeChild;
            } else {
                parentNode->right = foundNodeChild;
            }

            delete temp;
            return true;
        }
        // case 3, two children
        else {
            std::cout << "Two children\n";
        }

        return false;
    };

    void inOrder(Node *currNode) {
        if (currNode == nullptr) {
            return;
        }
        inOrder(currNode->left);
        std::cout << currNode->word << " : " << currNode->meaning << "\n";
        inOrder(currNode->right);
    };

    Node *getRoot() { return root; };
};

int main() {
    Dictionary myDict;

    myDict.insert("Hellow", "Greetin");
    myDict.insert("Latte", "Coffee");
    myDict.insert("Yellow", "Color");
    myDict.insert("A", "Color");
    myDict.insert("B", "Color");
    myDict.insert("C", "Color");
    myDict.insert("K", "Color");
    myDict.insert("T", "Color");
    myDict.insert("P", "Color");

    if (myDict.remove("B")) {
        std::cout << "Removed.\n";
    } else {
        std::cout << "Not found.\n";
    }

    myDict.inOrder(myDict.getRoot());

    return 0;
}
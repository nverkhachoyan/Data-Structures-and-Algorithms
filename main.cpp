#include <iostream>
#include <string>

// A dictionary Implementation usng a BST

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
    Dictionary() : root(nullptr){};

    // Gets a word/meaning pair and inserts them in the BST
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

    // Gets a word and returns a pair of Node pointers
    // First is the node conatining keyword, second is the parent of node
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

    // Gets a string and searches it in the dictionary.
    // Removes it upon finding it. Returns false if not found.
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
            Node *successor = foundNode->right;

            while (successor->left != nullptr) {
                successor = successor->left;
            }

            std::string successorWord = successor->word;
            std::string successorMeaning = successor->meaning;

            remove(successor->word);

            foundNode->word = successorWord;
            foundNode->meaning = successorWord;
            return true;
        }

        return false;
    };

    // Traverses the BST in order
    void inOrderTraversal(Node *currNode) {
        if (currNode == nullptr) {
            return;
        }
        inOrderTraversal(currNode->left);
        std::cout << currNode->word << " : " << currNode->meaning << "\n";
        inOrderTraversal(currNode->right);
    };

    // Returns the root of the BST
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

    std::cout << "Traversing the dictionary.\n";
    myDict.inOrderTraversal(myDict.getRoot());

    if (myDict.remove("Latte")) {
        std::cout << "Removed B.\n";
    } else {
        std::cout << "Not found.\n";
    }

    std::cout << "\n";
    std::cout << "Traversing the dictionary after removal of an item."
              << std::endl;
    myDict.inOrderTraversal(myDict.getRoot());

    return 0;
}
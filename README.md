# Dictionary Implementation BST

This program implements a dictionary data structure using a BST. The dictionary stores key-value pairs and allows for efficient search, insert, and delete operations. Please note that this BST implementation is not self-balancing. As a result, the performance of the dictionary may degrade if the BST becomes heavily unbalanced.

Here is a list of operations this Dictionary can call.

- Insert
- Search
- Remove
- InOrderTraversal
- getRoot

### Removal of an item

There are three cases to consider when removing nodes from a graph, as depicted in the accompanying graphs. Firstly, let's review the initial state of the graph. Before we delve into the specifics of each case, it's important to understand the concept of a **successor** node. This function is necessary for the third type of removal we will discuss.

#### The Successor of a Node

Many people think that the successor of a node is simply the left child of the right child of the node. However, this is not true, and I will demonstrate it via the graph below. The simple idea of a successor is that it follows the current value, as in it comes immediately after it. In the graph below, 12 appears after 10, but it is not the next value in sequence. If 10 were replaced with 12, the binary search tree would no longer be valid.

<p align="center">
  <picture>
    <source media="(prefers-color-scheme: light)" srcset="/src/imgs/notthesuccessor.png">
    <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/notthesuccessorDarkMode.png">
    <img alt="Not the successor" width="400px" src="/src/imgs/notthesuccessor.png">
  </picture>
</p>

The successor is the node with the smallest value in the right subtree of the target node. In other words, the successor is the leftmost element in the right subtre of the target node. In our case, that would be the node with the value 11.

<p align="center">
  <picture>
    <source media="(prefers-color-scheme: light)" srcset="/src/imgs/thesuccessor.png">
    <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/thesuccessorDarkMode.png">
    <img  alt="The successor" width="400px" src="/src/imgs/thesuccessor.png">
  </picture>
</p>

In addition to the **successor** function, there is also a **predecessor** function. Although we will not be using it in our implementation, it serves a similar purpose by identifying the node preceding the target node.

Now, let's examine the three cases of removal in detail.

<picture>
  <source media="(prefers-color-scheme: light)" srcset="/src/imgs/nodetypes.png">
  <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/nodetypesDarkMode.png">
  <img alt="Node Types" src="/src/imgs/nodetypes.png">
</picture>

Let's observe the initial state of the graph below, and then explain the necessary actions depending on each case.

<picture>
  <source media="(prefers-color-scheme: light)" srcset="/src/imgs/initialgraph.png">
  <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/initialgraphDarkMode.png">
  <img alt="Initial Graph" src="/src/imgs/initialgraph.png">
</picture>

#### Case 1: A leaf node

For the first case, let's say we wanted to remove a **leaf node**. I'm going to choose to remove node 8, which is a left child of node 10. As you may already see, all I need to do is find the parent of the leaf node, and remove its left child. This is the simplest removal process as it just involves removing the left or right link from the parent and deleting the allocated memory for the node. Depending on what programming environment you use, you may not have to free the memory manually.

```cpp
// case 1, leaf node
if (foundNode->left == nullptr && foundNode->right == nullptr) {
    if (foundParent->left->word == word) {
        Node *tmp = foundParent->left;
        foundParent->left = nullptr;
        delete tmp;
    } else {
        Node *tmp = foundParent->right;
        foundParent->right = nullptr;
        delete tmp;
    }
    return true;  // successfully deleted
}
```

<picture>
  <source media="(prefers-color-scheme: light)" srcset="/src/imgs/leafnoderemoval.png">
  <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/leafnoderemovalDarkMode.png">
  <img alt="Leaf Node Removal" src="/src/imgs/leafnoderemoval.png">
</picture>

#### Case 2: Node with 1 child

For the second case, we are removing a **node with one child**. In this case, we find the parent of the node to be removed, and we replace the left or right child node of the parent with the child of the node that we want to remove. For example, if we wanted to remove 4 from the graph illustrated above, we first would find its parent. Node 4 is a left child of node 5, so we would replace the left child of node 5 with the left child of node 4 in our graph. It is also important to remember to free the memory that was allocated for the deleted node if possible.

```cpp
// case 2, one child
else if (foundNode->left == nullptr || foundNode->right == nullptr) {
    Node *temp = foundNode;
    Node *foundNodeChild =
        foundNode->left != nullptr ? foundNode->left : foundNode->right;

    if (foundParent->left == foundNode) {
        foundParent->left = foundNodeChild;
    } else {
        foundParent->right = foundNodeChild;
    }

    delete temp;
    return true; // successfully removed
}
```

<picture>
  <source media="(prefers-color-scheme: light)" srcset="/src/imgs/nodewith1ONE.png">
  <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/nodewith1ONEDarkMode.png">
  <img alt="Node with 1 child removal" src="/src/imgs/nodewith1ONE.png>">
</picture>

<p align="center">
<picture>
  <source media="(prefers-color-scheme: light)" srcset="/src/imgs/nodewith1TWO.png">
  <source media="(prefers-color-scheme: dark)" srcset="/src/imgs/nodewith1TWODarkMode.png">
  <img alt="Node with 1 child removal" width="400px" src="/src/imgs/nodewith1TWO.png">
</picture>
</p>

#### Case 3: Node with 2 children

In this case, we will delete a node from a binary search tree that has two children. To do this, we will first find the successor of the node to be deleted. The in-order successor is the next node in the tree that would be visited in an in-order traversal, which visits the nodes in a tree in ascending order (e.g., if the tree is a list of numbers, the in-order traversal would visit the nodes in ascending numerical order). For example, if the node to be deleted contains the number 10, the in-order successor would be the node containing the number 11 because it comes immediately after 10 in the in-order traversal. Once we have found the in-order successor, we replace the node to be deleted with it and adjust the connections between the nodes in the tree accordingly. Finally, we delete the original node and return true to indicate that the delete operation was successful.

```cpp
// case 3, two children
else {
    Node *successor = foundNode->right;
    Node *temp = successor;

    while (1) {
        successor = temp->left;
        if (successor->left == nullptr) break;
        temp = successor;
    }

    temp->left = successor->right;
    successor->left = foundNode->left;

    if (foundParent->left == foundNode) {
        foundParent->left = successor;
    } else {
        foundParent->right = successor;
    }

    successor->right = foundNode->right;

    delete foundNode;
    return true; // successfully removed
}
```

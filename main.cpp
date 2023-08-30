#include <iostream>
#include <list>

#include "ReadOnlyTree.cpp"

using namespace std;

// Function to print the tree signature

// Function to print the tree, go new line for each level
template<class T>
void printTree(ReadOnlyTree<T> tree) {
    // Create a list of nodes
    list<typename ReadOnlyTree<T>::Node *> nodes;

    // Add the root to the list
    nodes.push_back(tree.root());

    // While the list is not empty
    while (!nodes.empty()) {
        // Get the first node
        typename ReadOnlyTree<T>::Node *node = nodes.front();
        // Remove the first node
        nodes.pop_front();

        // Print the value of the node
        cout << "Node value: " << tree.read(node) << endl;

        // If the node has children
        if (!tree.leaf(node)) {
            // Add the first child to the list
            nodes.push_back(tree.firstChild(node));
            // While the node has a next sibling
            while (!tree.lastSibling(nodes.back())) {
                // Add the next sibling to the list
                nodes.push_back(tree.nextSibling(nodes.back()));
            }
        }
    }
}

int main() {

    // Create a tree
    ReadOnlyTree<float> tree = ReadOnlyTree<float>();

    // Check if the tree is empty
    if (tree.empty())
        std::cout << "The tree is empty" << std::endl;
    else
        std::cout << "The tree is not empty" << std::endl;

    // Add a root
    ReadOnlyTree<float>::Node *root = tree.insRoot();

    // Check if the tree is empty
    if (tree.empty())
        std::cout << "The tree is empty" << std::endl;
    else
        std::cout << "The tree is not empty" << std::endl;


    // Insert a first child
    ReadOnlyTree<float>::Node *firstChild = tree.insFirst(root);

    // Insert a second child
    ReadOnlyTree<float>::Node *secondChild = tree.insNext(firstChild);

    // Insert a third child as last child
    ReadOnlyTree<float>::Node *thirdChild = tree.insLast(secondChild);

    // Insert a first child of the second child
    ReadOnlyTree<float>::Node *firstChildOfSecondChild = tree.insFirst(secondChild);
    // Insert a second child of the second child
    ReadOnlyTree<float>::Node *secondChildOfSecondChild = tree.insNext(firstChildOfSecondChild);
    // Insert a last child of the second child
    ReadOnlyTree<float>::Node *thirdChildOfSecondChild = tree.insLast(secondChildOfSecondChild);

    // Insert a first child of the third child
    ReadOnlyTree<float>::Node *firstChildOfThirdChild = tree.insFirst(thirdChild);
    // Insert a last child of the third child
    ReadOnlyTree<float>::Node *secondChildOfThirdChild = tree.insLast(firstChildOfThirdChild);


    // Print the tree
    printTree(tree);


    return 0;
}



// Output:
// The tree is empty
// The tree is not empty
// First child value: 1
// Second child value: 2
// Third child value: 3

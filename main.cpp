#include <iostream>
#include <list>

#include "ReadOnlyTree.cpp"

using namespace std;

template <typename T> void postVisita(ReadOnlyTree<T>* tree, typename ReadOnlyTree<T>::Node* node){

    if(!(tree->leaf(node))){

        typename ReadOnlyTree<T>::Node* current_node = tree->firstChild(node);
        typename ReadOnlyTree<T>::Node* temp_current_node = current_node;
        postVisita(tree, current_node);
        current_node = temp_current_node;

        while(tree->lastSibling(current_node)){
            current_node = tree->nextSibling(current_node);
            temp_current_node = current_node;
            postVisita(tree, current_node);
            current_node = temp_current_node;
        }
    }


    // esamina nodo
    std::cout << tree->read(node) << "\t";

}

template <typename T> void postVisita(ReadOnlyTree<T>* tree){
    postVisita(tree, tree->root());
}

void genRandomIntChild(ReadOnlyTree<int>* tree, ReadOnlyTree<int>::Node* current_node, int n_child){
    cout << n_child << endl;
    for(int i=0; i<n_child; i++){

        if(i==0){
            current_node = tree->insFirst(current_node);
        }else if(i==n_child-1){
            current_node = tree->insLast(current_node);
        }else{
            current_node = tree->insNext(current_node, 1+(rand()%11));
        }

        tree->write(current_node, 1+(rand()%11));
        ReadOnlyTree<int>::Node* temp_node = current_node;
        genRandomIntChild(tree, current_node, n_child-1);
        current_node = temp_node;
    }
}

ReadOnlyTree<int>* genRandomIntTree(){
    srand((unsigned) time(nullptr));

    ReadOnlyTree<int>* tree = new ReadOnlyTree<int>();
    ReadOnlyTree<int>::Node* current_node;

    tree->insRoot();
    tree->write( tree->root(), 1 + (rand() % 11) );
    current_node = tree->root();

    genRandomIntChild(tree, current_node, 5);

    return tree;
}

// Pretty print a tree, go new line for each level
template<class T>
void printTreeAtLevels(ReadOnlyTree<T> tree) {
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
        cout << tree.read(node) << " ";

        // If the node has children
        if (!tree.leaf(node)) {
            // Add the first child to the list
            nodes.push_back(tree.firstChild(node));
            // While the node has a next sibling
            while (!tree.lastSibling(nodes.back())) {
                // Add the next sibling to the list
                nodes.push_back(tree.nextSibling(nodes.back()));
            }
            // Go new line
            cout << endl;
        }
    }
}

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

// Function to print the tree in pre-order
template<class T>
void printPreOrder(ReadOnlyTree<T> tree, typename ReadOnlyTree<T>::Node *node) {

    cout << tree.read(node) << " ";

    if (!tree.leaf(node)) {
        typename ReadOnlyTree<T>::Node *child = tree.firstChild(node);
         do {
            printPreOrder(tree, child);
            child = tree.nextSibling(child);
        } while (!tree.lastSibling(child));
    }

    cout << endl;
}


// Function to print the tree in post-order
template<class T>
void printPostOrder(ReadOnlyTree<T> tree, typename ReadOnlyTree<T>::Node *node) {
    // If the node has children
    if (!tree.leaf(node)) {
        // Print the children
        for (
                typename ReadOnlyTree<T>::Node *child = tree.firstChild(node);
                child != nullptr;
                child = tree.nextSibling(child)
                        ) {
            printPostOrder(tree, child);
        }
    }

    // Print the value of the node
    cout << tree.read(node) << " ";
}

using Node = ReadOnlyTree<int>::Node;

// Function to print the tree in in-order
template<class T>
void printInOrder(ReadOnlyTree<T> tree, Node *node) {
    // If the node has children
    if (!tree.leaf(node)) {
        // Print the first child
        printInOrder(tree, tree.firstChild(node));
    }

    // Print the value of the node
    cout << tree.read(node) << " ";

    // If the node has children
    if (!tree.leaf(node)) {
        // Print the children
        for (
                Node *child = tree.firstChild(node);
                child != nullptr;
                child = tree.nextSibling(child)
                        ) {
            // If the child is not the first child
            if (child != tree.firstChild(node)) {
                printInOrder(tree, child);
            }
        }
    }
}

// Function to print the tree in level-order - Breadth First Search (BFS)
template<class T>
void printLevelOrder(ReadOnlyTree<T> tree) {
    // Create a list of nodes
    list<typename ReadOnlyTree<T>::Node *> nodes;

    // Add the root to the list
    nodes.push_back(tree.root());

    // While the list is not empty
    while (!nodes.empty()) {
        // Get the first node
        typename ReadOnlyTree<T>::Node *current_node = nodes.front();
        // Remove the first node
        nodes.pop_front();

        // Print the value of the node
        cout << tree.read(current_node) << " ";

        // If the node has children
        if (!tree.leaf(current_node)) {
            // Add the children to the list
            for (
                    typename ReadOnlyTree<T>::Node *child = tree.firstChild(current_node);
                    child != nullptr;
                    child = tree.nextSibling(child)
                            ) {
                nodes.push_back(child);
            }
        }
    }
}



int main() {

    ReadOnlyTree<int> tree;

    Node* root = tree.insRoot(1);

    Node* child1 = tree.insFirst(root, 2);
    Node* child2 = tree.insNext(child1, 3);

    Node* child11 = tree.insFirst(child1, 4);
    Node* child12 = tree.insNext(child11, 5);

    Node* child21 = tree.insFirst(child2, 6);
    Node* child22 = tree.insNext(child21, 7);

   

    printPreOrder(tree, root);

    cout << endl;

    return 0;
}


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
            current_node = tree->insNext(current_node);
        }

        tree->write(current_node, 1+(rand()%11));
        ReadOnlyTree<int>::Node* temp_node = current_node;
        genRandomIntChild(tree, current_node, n_child-1);
        current_node = temp_node;
    }
}


ReadOnlyTree<int>* genRandomIntTree(){
    srand((unsigned) time(NULL));

    ReadOnlyTree<int>* tree = new ReadOnlyTree<int>();
    ReadOnlyTree<int>::Node* current_node;

    tree->insRoot();
    tree->write( tree->root(), 1+(rand()%11) );
    current_node = tree->root();

    genRandomIntChild(tree, current_node, 5);

    return tree;
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

int main() {

    // Create a tree
    ReadOnlyTree<int> tree;


    // Generate a random tree
    tree = *genRandomIntTree();
    postVisita(&tree);

    // Print the tree
    //printTree(tree);


    return 0;
}



// Output:
// The tree is empty
// The tree is not empty
// First child value: 1
// Second child value: 2
// Third child value: 3

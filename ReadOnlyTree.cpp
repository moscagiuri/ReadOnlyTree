//
// Created by h1tman2 on 27/08/23.

using namespace std;


template <class T>
class ReadOnlyTree {


public:

    // Struct for the nodes
    struct Node {
        // Value of the node
        T value;
        // Pointer to the parent
        Node *parent;
        // Pointer to the first child
        Node *firstChild;
        // Pointer to the next sibling
        Node *nextSibling;
    };
    // Pointer to the root
    Node *rootNode;

    // Tree operations
    ReadOnlyTree();
    bool empty() ;
    Node * insRoot() ;
    Node * root() ;
    Node parent(Node n) const;
    Node * firstChild(Node *n) const;
    Node * nextSibling(Node *n) const;
    bool lastSibling(Node *n) const;
    bool leaf(Node *n) const;
    T read(Node *n) const;
    void write(Node *n, const T &val);

    // Insert a new node as the first child of a given node
    Node *insFirst(Node* n);

    // Insert a new node as the last child of a given node
    Node *insLast(Node *n);

    // Insert a new node as the next sibling of a given node
    Node *insNext(Node *n);

    // Remove a node and all its descendants
    void remove(Node *n);

    // Get level of a node
    int level(Node *n) const;


    };

template<class T>
ReadOnlyTree<T>::ReadOnlyTree() {
    rootNode = nullptr;
}

// empty: returns true if the tree is empty, false otherwise
template<class T>
bool ReadOnlyTree<T>::empty()  {
    return rootNode == nullptr;
}
template<class T>
typename ReadOnlyTree<T>::Node* ReadOnlyTree<T>::insRoot() {
    // Create a new node
    Node *newNode = new Node;

    // Set the parent of the new node
    newNode->parent = nullptr;

    // Set the first child of the new node
    newNode->firstChild = nullptr;

    // Set the next sibling of the new node
    newNode->nextSibling = nullptr;

    // Set the root of the tree
    rootNode = newNode;

    // Return the new node
    return rootNode;
}

template<class T>
typename ReadOnlyTree<T>::Node* ReadOnlyTree<T>::root()  {
    return rootNode;
}

template<class T>
typename ReadOnlyTree<T>::Node ReadOnlyTree<T>::parent(Node n) const {
    return n->parent;
}

template<class T>
typename ReadOnlyTree<T>::Node * ReadOnlyTree<T>::firstChild(Node *n) const {
    return n->firstChild;
}

template<class T>
typename ReadOnlyTree<T>::Node * ReadOnlyTree<T>::nextSibling(Node *n) const {
    return n->nextSibling;
}

template<class T>
bool ReadOnlyTree<T>::lastSibling(Node *n) const {
    return n->nextSibling == nullptr;
}

template<class T>
bool ReadOnlyTree<T>::leaf(Node *n) const {
    return n->firstChild == nullptr;
}

template<class T>
T ReadOnlyTree<T>::read(Node *n) const {
    return n->value;
}

template<class T>
void ReadOnlyTree<T>::write(Node *n, const T &val) {
    // Write the value of the node
    n->value = val;

}

template<class T>
typename ReadOnlyTree<T>::Node* ReadOnlyTree<T>::insFirst(Node *n) {
    // Create a new node
    Node *newNode = new Node;

    // Set the parent of the new node
    newNode->parent = n;

    // Set the first child of the new node
    newNode->firstChild = nullptr;


    // Set the first child of the given node
    n->firstChild = newNode;

    // Return the new node
    return newNode;
}

template<class T>
typename ReadOnlyTree<T>::Node* ReadOnlyTree<T>::insLast(Node *n) {
    // Create a new node
    Node *newNode = new Node;

    // Set the parent of the new node
    newNode->parent = n;

    // Set the first child of the new node
    newNode->firstChild = nullptr;

    // Set the next sibling of the new node
    newNode->nextSibling = nullptr;

    // Set the first child of the given node
    n->firstChild = newNode;

    // Return the new node
    return newNode;
}

template<class T>
typename ReadOnlyTree<T>::Node *ReadOnlyTree<T>::insNext(Node *n) {
    // Create a new node
    Node *newNode = new Node;

    // Set the parent of the new node
    newNode->parent = n->parent;

    // Set the first child of the new node
    newNode->firstChild = nullptr;

    // Set the next sibling of the new node
    newNode->nextSibling = n->nextSibling;

    // Set the next sibling of the given node
    n->nextSibling = newNode;

    // Return the new node
    return newNode;
}

template<class T>
void ReadOnlyTree<T>::remove(Node *n) {
    // If the node is not a leaf
    if (!leaf(n)) {
        // Remove all the descendants of the node
        Node *child = n->firstChild;
        while (child != nullptr) {
            Node *nextChild = child->nextSibling;
            remove(child);
            child = nextChild;
        }
    }

    // Remove the node
    if (n->parent != nullptr) {
        // If the node is not the root
        if (n->parent->firstChild == n) {
            // If the node is the first child of its parent
            n->parent->firstChild = n->nextSibling;
        } else {
            // If the node is not the first child of its parent
            Node *sibling = n->parent->firstChild;
            while (sibling->nextSibling != n) {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = n->nextSibling;
        }
    } else {
        // If the node is the root
        rootNode = nullptr;
    }

    // Delete the node
    delete n;
}

template<class T>
int ReadOnlyTree<T>::level(Node *n) const {
    // If the node is the root
    if (n->parent == nullptr) {
        return 0;
    } else {
        // If the node is not the root
        return 1 + level(n->parent);
    }
}
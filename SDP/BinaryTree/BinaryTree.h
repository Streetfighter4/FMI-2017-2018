//
// Created by yasen on 11/16/18.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

template <class T>
class BinaryTree {
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(const T&);
    };

private:
    Node* root;
public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree& operator=(const BinaryTree&);


public:
    /*
    class Iterator {
    private:
        const BinaryTree<T>* pTree;
        BinaryTree<T>::Node* currNode;
        Iterator(BinaryTree<T>* tree, Node* node) : pTree(tree), currNode(node) {};

    public:
        bool operator==(Iterator*) const;
        bool operator!=(Iterator*) const;
        Iterator*operator++();
        T&operator*();
    };
     */
public:
    void insert(const T&);
    void print();
    void remove(const T&);
    void sortArray(T*& array, size_t size);
    void makebalanceTreeFromSortedArray(const T*& array, size_t);

private:
    void insertRecursive(Node*& node, const T& elem);
    void printRecursive(Node*& node) const;

    Node* removeRecursive(Node*& node, const T& elem);
    Node* minValueNode(Node*& node) const;
    Node* copyRecursive(Node* node);

    void feelsortedArray(T*& array, size_t&, Node* node);
    void makebalanceTreeFromSortedArrayRecursive(const T*& array, size_t, size_t, Node*);

    void copy(const BinaryTree&);
    void clear(Node*);
};

template<class T>
BinaryTree<T>::Node::Node(const T& newData) : data(newData), left(nullptr), right(nullptr) {}

template<class T>
BinaryTree<T>::BinaryTree() : root(nullptr){}

template<class T>
BinaryTree<T>::~BinaryTree() {
    clear(root);
}

template<class T>
void BinaryTree<T>::insert(const T& elem) {
    if(root == nullptr) {
        root = new Node(elem);
        return;
    }
    insertRecursive(root, elem);
}

template<class T>
void BinaryTree<T>::insertRecursive(BinaryTree::Node*& node, const T& elem) {
    if(elem <= node->data) {
        if(node->left == nullptr) {
            node->left = new Node(elem);
        } else {
            insertRecursive(node->left, elem);
        }
    } else {
        if(node->right == nullptr) {
            node->right = new Node(elem);
        } else {
            insertRecursive(node->right, elem);
        }
    }
}

template<class T>
void BinaryTree<T>::print() {
    if(root == nullptr) {
        return;
    }
    printRecursive(root);
}

template<class T>
void BinaryTree<T>::printRecursive(BinaryTree::Node*& node) const {
    if(node->left != nullptr) {
        printRecursive(node->left);
    }
    std::cout << node->data << std::endl;
    if(node->right != nullptr) {
        printRecursive(node->right);
    }
}

template<class T>
void BinaryTree<T>::remove(const T& elem) {
    removeRecursive(root, elem);
}

template<class T>
typename BinaryTree<T>::Node* BinaryTree<T>::removeRecursive(BinaryTree::Node*& node, const T& elem) {
    if(node == nullptr) {
        return node;
    }
    if(elem < node->data) {
        node->left = removeRecursive(node->left, elem);
    } else if(elem > node->data) {
        node->right = removeRecursive(node->right, elem);
    } else {
        if(node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if(node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        Node* temp = minValueNode(node->right);
        node->data = temp->data;
        removeRecursive(node->right, temp->data);
    }
    return node;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::minValueNode(BinaryTree::Node*& node) const {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template<class T>
void BinaryTree<T>::clear(BinaryTree::Node* node) {
    if(node == nullptr) {
        return;
    }
    if(node->left) {
        clear(node->left);
    }
    if(node->right) {
        clear(node->right);
    }
    delete node;
}

template<class T>
void BinaryTree<T>::copy(const BinaryTree& other) {
    root = copyRecursive(other.root);
}

template<class T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyRecursive(BinaryTree::Node* node) {
    if(node == nullptr) {
        return node;
    }
    Node* temp = new Node(node->data);
    temp->left = copyRecursive(node->left);
    temp->right = copyRecursive(node->right);
    return temp;
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree& rhs) {
    copy(rhs);
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other) {
    if(this != &other) {
        clear(root);
        copy(other);
    }
    return *this;
}

template<class T>
void BinaryTree<T>::sortArray(T*& array, size_t size) {
    clear(root);
    for (size_t i = 0; i < size; ++i) {
        insert(array[i]);
    }
    size_t index = 0;
    feelsortedArray(array, index, root);
}

template<class T>
void BinaryTree<T>::feelsortedArray(T*& array, size_t& index,  Node* node) {
    if(node->left != nullptr) {
        feelsortedArray(array, index, node->left);
    }
    array[index++] = node->data;
    if(node->right != nullptr) {
        feelsortedArray(array, index, node->right);
    }
}

template<class T>
void BinaryTree<T>::makebalanceTreeFromSortedArray(const T*& array, size_t size) {
    clear(root);
    size_t begin = 0;
    size_t end = size-1;
    makebalanceTreeFromSortedArrayRecursive(array, begin, end, root);
    // 1 2 3 4 5 6 7 8 9 10
    //       6
    //    3     6
    //  1  3  5   7
}

template<class T>
void BinaryTree<T>::makebalanceTreeFromSortedArrayRecursive(const T*& array, size_t begin, size_t end, Node* node) {
    if(end < begin) {
        return;
    }
    insert(array[(end + begin) /2]);
    if((end+begin) % 2 == 0) {
        makebalanceTreeFromSortedArrayRecursive(array, begin, (begin+end)/2 - 1, node->left);
        makebalanceTreeFromSortedArrayRecursive(array, (begin+end)/2 + 1, end, node->right);
    } else {
        makebalanceTreeFromSortedArrayRecursive(array, begin, (begin+end)/2, node->left);
        makebalanceTreeFromSortedArrayRecursive(array, (begin+end)/2 + 1, end, node->right);
    }
}


#endif //BINARYTREE_BINARYTREE_H

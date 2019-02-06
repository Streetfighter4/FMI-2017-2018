#include <iostream>
#include <vector>


struct Node {
    int value;
    Node *left;
    Node *right;

    explicit Node(int newValue) : value(newValue), left(nullptr), right(nullptr){

        std::cout << "In Node cnst" << std::endl;
    }
};

struct NodeN {
    int value;
    std::vector<NodeN*> children;

    explicit NodeN(int newValue) : value(newValue) {
        std::cout << "In NodeN cnst" << std::endl;
    }
};

bool isComplete(Node* root) {
    if(root == nullptr) {
        return true;
    }
    if(root->left == nullptr && root->right == nullptr) {
        return true;
    }
    if(root->left == nullptr && root->right != nullptr ||
            root->left != nullptr && root->right == nullptr) {
        return false;
    }
    if(root->value >= root->left->value && root->value < root->right->value) {
        return isComplete(root->left) && isComplete(root->right);
    } else {
        return false;
    }
}

void countNodesInSubtree(Node* root, size_t& countNodes) {
    if(root->left) {
        countNodesInSubtree(root->left, countNodes);
    }
    ++countNodes;
    if(root->right) {
        countNodesInSubtree(root->right, countNodes);
    }
}

Node* getLargestBstSubtree(Node* root) {
    if(root == nullptr) {
        return nullptr;
    }
    if(root->left == nullptr && root->right == nullptr) {
        return nullptr;
    }
    if(root->left == nullptr && root->right != nullptr) {
        return root->right;
    }
    if(root->left != nullptr && root->right == nullptr) {
        return root->left;
    }

    size_t countNodesLeft = 0;
    size_t countNodesRight = 0;
    countNodesInSubtree(root->left, countNodesLeft);
    countNodesInSubtree(root->right, countNodesRight);
    return (countNodesLeft >= countNodesRight) ? root->left : root->right;
}

void getNthFrontRecursive(NodeN* root, unsigned currentLevel, unsigned level, std::vector<NodeN*>& vector) {
    if(currentLevel == level-1) {
        for(auto& child : root->children) {
            vector.push_back(child);
        }
        return;
    }
    for(auto& child : root->children) {
        getNthFrontRecursive(child, currentLevel+1, level, vector);
    }
}

std::vector<NodeN*> getNthFront(NodeN* root, unsigned level) {
    std::vector<NodeN*> vector;
    if(level == 0) {
        vector.push_back(root);
        return vector;
    }
    getNthFrontRecursive(root, 0, level, vector);
    return vector;
}

void getBetweenRecursive(NodeN* root, int A, int B, std::vector<NodeN*>& vector) {

    if(root->value >= A && root->value <= B) {
        vector.push_back(root);
    }
    for(auto& child : root->children) {
        getBetweenRecursive(child, A, B, vector);
    }
}

std::vector<NodeN*> getBetween(NodeN* root, int A, int B) {
    std::vector<NodeN*> vector;
    getBetweenRecursive(root, A, B, vector);
    return vector;
}

Node* search(Node* node, int number) {
    if(node->value == number) {
        return node;
    }
    if(node->left != nullptr) {
        return search(node->left, number);
    }
    if(node->right != nullptr) {
        return search(node->right, number);
    }
    return nullptr;
}

Node* getCommonAncestor(Node* root, int A, int B) {
    if(root == nullptr) {
        return nullptr;
    }
    Node *temp = nullptr;
    if(root->value == A) {
        std::cout << "Found A" << std::endl;
        temp = search(root, B);
    }
    if(root->value == B) {
        std::cout << "Found B" << std::endl;
        temp = search(root, A);
    }
    if(temp) {
        return root;
    } else {
        Node *temp1 = nullptr, *temp2 = nullptr;
        if(root->left) {
            temp1 = getCommonAncestor(root->left, A, B);
        }
        if(root->right) {
            temp2 = getCommonAncestor(root->right, A, B);
        }
        if(temp1 && temp2) {
            return root;
        } else {
            nullptr;
        }
    }
}


void init_blance_binary_tree(Node*& root) {
    root = new Node(3);

    root->left = new Node(1);
    root->right = new Node(5);

    root->left->left = new Node(0);
    root->left->right = new Node(2);

    root->right->left = new Node(4);
    root->right->right = new Node(6);

}

void init_binary_tree(Node*& root) {
    root = new Node(10);

    root->left = new Node(1);
    root->right = new Node(5);

    root->left->left = new Node(0);
    root->left->right = new Node(2);

    root->right->left = new Node(4);
    root->right->right = new Node(6);

}

void clear(Node*& root) {
    if(root->left != nullptr) {
        clear(root->left);
    }
    if(root->right != nullptr) {
        clear(root->right);
    }

    delete root;
    root = nullptr;
}

void init_NTree(NodeN*& root) {
    root = new NodeN(10);
    for(int i = 0; i < 10; ++i) {
        root->children.push_back(new NodeN(i));
    }
    for(auto& child : root->children) {
        child->children.push_back(new NodeN(0));
        child->children.push_back(new NodeN(1));
    }
}

void clearNTree(NodeN*& root) {
    if(root == nullptr)
        return;

    if(root->children.empty()) {
        delete root;
    } else {
        for(auto& child : root->children) {
            clearNTree(child);
        }
    }
}

int main() {

    Node* root;
    init_binary_tree(root);


    Node* node = getCommonAncestor(root, 0, 2);
    if(node)
        std::cout << "node value: " << node->value << std::endl;

    clear(root);
    /*
    NodeN* root;
    init_NTree(root);

    std::vector<NodeN*> vector = getBetween(root, 10 , 15);
    for(auto& node : vector) {
        std::cout << node->value << ' ';
    }

    clearNTree(root);
    */
    return 0;
}
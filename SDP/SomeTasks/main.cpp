#include <iostream>
#include <vector>

#define min(a, b) ((a < b) ? a:b)

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

struct Box {
    int value;

    Box* pNext;
    explicit Box(int newValue) : value(newValue) , pNext(nullptr) {}
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


void search(Node* root, int number, bool& isFound, std::vector<Node*> buff, std::vector<Node*>& vector) {
    buff.push_back(root);
    if(root->value == number) {
        vector = buff;
        isFound = true;
        return;
    }
    if(root->left && !isFound) {
        search(root->left, number, isFound, buff, vector);
    }
    if(root->right && !isFound) {
        search(root->right, number, isFound, buff, vector);
    }
}

Node* getCommonAncestor(Node* root, int A, int B) {
    bool isFound = false;
    std::vector<Node*> buff, vector1, vector2;
    search(root, A, isFound, buff, vector1);
    isFound = false;
    search(root, B, isFound, buff, vector2);

    for(int i = 0; i < min(vector1.size(), vector2.size()); ++i) {
        if(vector1[i] != vector2[i]) {
            return vector1[i-1];
        }
    }
    return nullptr;
}

std::vector<int> getPath(Node *root, int A, int B) {
    bool isFound = false;
    std::vector<Node*> buff, vector1, vector2;
    search(root, A, isFound, buff, vector1);
    isFound = false;
    search(root, B, isFound, buff, vector2);

    int i;
    for(i = 0; i < min(vector1.size(), vector2.size()); ++i) {
        if(vector1[i] != vector2[i]) {
            break;
        }
    }

    std::vector<int> vector;
    for(int j = vector1.size()-1; j >= i; --j) {
        vector.push_back(vector1[j]->value);
    }
    for(int k = 0; k < vector2.size(); ++k) {
        vector.push_back(vector2[k]->value);
    }
    return vector;
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

void insert_back(int elem, Box*& tail) {
    Box* newElem = new Box(elem);
    tail->pNext = newElem;
    tail = newElem;
}

void init_linked_list(Box*& head, Box*& tail) {
    head = new Box(5);
    tail = head;

    insert_back(4, tail);
    insert_back(-1, tail);
    insert_back(10, tail);
    insert_back(0, tail);
}

void clear_linked_list(Box*& head) {
    Box* buff = head;

    while(head != nullptr) {
        head = head->pNext;
        delete buff;
        buff = head;
    }
}

void itarate_list(Box*& head) {
    Box* buff = head;

    while(buff != nullptr) {
        std::cout << buff->value << " ";
        buff = buff->pNext;
    }
    std::cout << std::endl;
}

void sort_list(Box*& head) {
    std::cout << "Sorting list..." << std::endl;

    Box* result_head = head;
    Box* result_tail = head;
    Box* it = result_head->pNext;
    result_head->pNext = nullptr;

    while (it) {
        if(it->value < result_head->value) {
            Box* tmp = it;
            it = it->pNext;
            tmp->pNext = result_head;
            result_head = tmp;
            continue;
        }

        Box* res_it = result_head;

        while (res_it->pNext && res_it->pNext->value <= it->value) {
            res_it = res_it->pNext;
        }

        if(res_it == nullptr) {
            Box* tmp = it;
            it = it->pNext;
            result_tail->pNext = tmp;
            result_tail = tmp;
            result_head->pNext = nullptr;
            continue;
        }

        Box* tmp = it->pNext;
        it->pNext = res_it->pNext;
        res_it->pNext = it;
        it = tmp;
    }
    head = result_head;

}

int main() {
    Box *head, *tail;
    init_linked_list(head, tail);
    itarate_list(head);
    sort_list(head);

    itarate_list(head);

    clear_linked_list(head);

    return 0;
}
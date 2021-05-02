#include <vector>
#include <iostream>

template <class T>
struct Test {
    struct Node {
        Node* next;
        T val;
        
        Node(Node* a_next, const T& a_val) : next(a_next), val(a_val) {
            
        }
    };
    
    void insert(const T& val) {
        root = new Node(root, val);
    }
    
    void traverse_func_ptr(void (*callback)(Node* node)) {
        Node* cur = root;
        while(cur) {
            callback(cur);
            cur = cur->next;
        }
    }
    
    template <class Func>
    void traverse_functor(Func callback) {
        Node* cur = root;
        while(cur) {
            callback(cur);
            cur = cur->next;
        }
    }
    
    ~Test() {
        std::vector<Node*> vec;
        traverse_functor([&](Node* node) {
            std::cout << "traverce ~: " << node->val << std::endl;
            vec.push_back(node);
        });
        for (Node* node : vec) {
            delete node;
        }
    };
    
    Node* root;
};



int main(int argc, const char * argv[]) {
    Test<int> test;
    for (int i = 0; i < 10; i++) {
        test.insert(i);
    }
    
    test.traverse_func_ptr([](Test<int>::Node* node) {
        std::cout << "traverse_func_ptr: " << node->val << std::endl;
    });
    
    test.traverse_functor([&](Test<int>::Node* node) {
        std::cout << "traverse_functor: " << node->val << std::endl;
    });
    
    return 0;
}

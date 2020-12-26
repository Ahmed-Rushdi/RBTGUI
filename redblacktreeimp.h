#ifndef REDBLACKTREEIMP_H
#define REDBLACKTREEIMP_H
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include <direct.h>


using namespace std;


enum Color {
    BLACK,
    RED
};

struct node {
    bool color;
    int key;
    node *left, *right, *p;

    node() {
    }

    node(int key) {
        this->key = key;
        this->color = RED;
        left = right = p = NULL;
    }
};

class redBlackTree {
private:
    node* root;
    node* empty_node;


    string random(int len) {
        string a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string r;
        for (int i = 0; i < len; i++) r.push_back(a.at(size_t(rand() % 52)));
        return r;
    }

    void printwrapper(node*& x) {
        ofstream file("src\\RBT.dot");
        file << "digraph tree {" << endl;
//        file << "graph [ dpi = 600 ];" << endl;
        file <<
            "node [shape = circle , style = filled, fillcolor = black, fontcolor = white,fontname = \"helvetica bold\", fontsize = 17];"
            << endl;
        print(x, file);
        file << "}";
        file.close();
        system("src\\dot.exe -Tpng -O src\\RBT.dot");
    }

    void print(node*& x, ofstream& file) {

        string s;
        if (x->left == empty_node || x->left == nullptr) {
            if (x->color == RED) {
                file << x->key << " [fillcolor = red];" << endl;
            }
            s = random(10);
            file << x->key << " -> " << s << ";" << endl;
            file << s << "[label = NIL, fixedsize = true, fontname = \"helvetica\"];" << endl;

        }
        else {
            if (x->color == RED) {
                file << x->key << " [fillcolor = red];";
            }
            file << x->key << " -> " << x->left->key << ";" << endl;

            print(x->left, file);
        }
        if (x->right == empty_node || x->right == nullptr) {
            if (x->color == RED) {
                file << x->key << " [fillcolor = red];" << endl;
            }
            s = random(10);
            file << x->key << " -> " << s << ";" << endl;
            file << s << "[label = NIL, fixedsize = true, fontname = \"helvetica\"];" << endl;
        }
        else {
            if (x->color == RED) {
                file << x->key << " [fillcolor = red];";
            }
            file << x->key << " -> " << x->right->key << ";" << endl;
            print(x->right, file);
        }

    }

    void clear(node*& x) {
        if (x != NULL) {
            clear(x->left);
            clear(x->right);
            delete x;
        }
    }


    void leftRotate(node*& x) {
        if (x == x->p->right) {
            node* parent = x->p;
            x = x->p;
            node* node_right = x->right;
            if (parent->p != NULL) {
                if (parent == parent->p->left) {
                    node_right->p = parent->p;
                    node_right->p->left = node_right;
                }
                else {
                    node_right->p = parent->p;
                    node_right->p->right = node_right;
                }
            }
            parent->right = node_right->left;
            node_right->left = parent;
            parent->p = node_right;
        }
        else {
            node* parent = x->p;
            x = x->p;
            node* node_left = parent->left;
            if (parent->p != NULL) {
                if (parent == parent->p->left) {
                    node_left->p = parent->p;
                    node_left->p->left = node_left;
                }
                else if (parent == parent->p->right) {
                    node_left->p = parent->p;
                    node_left->p->right = node_left;
                }
            }

            parent->left = node_left->right;
            node_left->right = parent;
            parent->p = node_left;
        }

    }

    void rightRotate(node*& x) {
        if (x == x->p->left) {
            node* parent = x->p;
            node* node_left = x;
            if (parent->p != NULL) {
                if (parent == parent->p->left) {
                    node_left->p = parent->p;
                    node_left->p->left = node_left;
                }
                else if (parent == parent->p->right) {
                    node_left->p = parent->p;
                    node_left->p->right = node_left;
                }
            }
            else {
                root = node_left;
                parent->left = NULL;
                root->p = NULL;
            }
            parent->p = node_left;
            if (node_left->right != NULL) {
                parent->left = node_left->right;
            }
            else {
                parent->left = NULL;
            }
            node_left->right = parent;

        }
        else {
            node* parent = x->p;
            node* node_right = x;
            if (parent->p != NULL) {
                if (parent == parent->p->left) {
                    node_right->p = parent->p;
                    node_right->p->left = node_right;
                }
                else if (parent == parent->p->right) {
                    node_right->p = parent->p;
                    node_right->p->right = node_right;
                }
            }
            else {
                root = node_right;
                parent->right = NULL;
                root->p = NULL;
            }
            parent->p = node_right;

            if (parent->left != NULL) {
                parent->right = node_right->left;
            }
            else {
                parent->right = NULL;
            }
            node_right->left = parent;

        }

    }

    void insertnode(node*& x) {
        if (root == NULL || root == empty_node) {
            root = new node();
            root = x;
            root->color = BLACK;
        }
        else {
            node* current = root;
            while (current != NULL) {
                if(current->key == x->key){
                    return;
                }
                if (current->key < x->key && current->right != NULL) {
                    current = current->right;
                }
                else if (current->key < x->key && current->right == NULL) {
                    x->p = current;
                    current->right = x;
                    break;
                }
                if (current->key > x->key && current->left != NULL) {
                    current = current->left;
                }
                else if (current->key > x->key && current->left == NULL) {
                    x->p = current;
                    current->left = x;
                    break;
                }
            }
        }
    }

    node* search(int key) {
        node* current = root;
        while (current != NULL) {
            if (current->key == key) {
                return current;
                break;
            }
            if (current->key < key && current->right != NULL) {
                current = current->right;
            }
            else if (current->key < key && current->right == NULL) {
                return NULL;
            }
            if (current->key > key && current->left != NULL) {
                current = current->left;
            }
            else if (current->key > key && current->left == NULL) {
                return NULL;
            }
        }
    }


public:
    redBlackTree() {
        root = NULL;
    }

    void clear() {
        clear(root);
        root = empty_node;
    }

    void print() {
        node* current = root;
        printwrapper(current);
    }

    void insert(int key) {
        node* x = new node(key);
        insertnode(x);
        if(x!=root && x->p == NULL){
            return;
        }
        while (x != root && x->p->color == RED && x->color == RED) {
            if (x->p->p != NULL && x->p == x->p->p->left) {
                node* y = x->p->p->right;
                if (y != NULL && y->color == RED) {
                    x->p->color = BLACK;
                    y->color = BLACK;
                    x->p->p->color = RED;
                    x = x->p->p;
                }
                else // y->color == BLACK
                {
                    if (x == x->p->right) {
                        leftRotate(x);
                    }
                    x->p->color = BLACK;
                    x->p->p->color = RED;
                    rightRotate(x->p);
                }

            }
            else if (x->p->p != NULL && x->p == x->p->p->right) // x->p == x->p->p->right
            {
                node* y = x->p->p->left;
                if (y != NULL && y->color == RED) {
                    x->p->color = BLACK;
                    y->color = BLACK;
                    x->p->p->color = RED;
                    x = x->p->p;
                }
                else {
                    if (x == x->p->left) {
                        leftRotate(x);
                    }
                    x->p->color = BLACK;
                    x->p->p->color = RED;
                    rightRotate(x->p);
                }
            }
        }
        root->color = BLACK;
    }

    void Delete(int key) {
        node* x = search(key);
        if (x == NULL) {
            return;
        }
        if (x->color == RED) {
            if (x->left == NULL && x->right == NULL) {
                delete x;
            }
            else if (x->left != NULL && x->right == NULL) {
                node* cur = x->left;
                while (cur != NULL) {
                    if (cur->right != NULL) {
                        cur = cur->right;
                    }
                    else {
                        break;
                    }
                }
            }
        }


    }

//    std::string get_current_dir() {
//        char buff[FILENAME_MAX]; //create string buffer to hold path
//        _getcwd(buff, FILENAME_MAX);
//        string current_working_dir(buff);
//        return current_working_dir;
//    }

};

#endif // REDBLACKTREEIMP_H

#include <cstdio>
using namespace std;
 
struct Node {
    Node *parent;
    Node *left;
    Node *right;
    int key;
};
 
Node *NIL = NULL;
Node *root = NIL;
 
void preorder(Node *v) {
    if (v == NIL) return;
    printf(" %d", v->key);
    preorder(v->left);
    preorder(v->right);
}
 
void inorder(Node* v) {
    if (v == NIL) return;
    inorder(v->left);
    printf(" %d", v->key);
    inorder(v->right);
}
 
void postorder(Node* v) {
    if (v == NIL) return;
    postorder(v->left);
    postorder(v->right);
    printf(" %d", v->key);
}
 
void insert(Node* &T, Node *z) {
    Node *y = NIL;
    Node *x = T;
    while (x != NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
 
    if (y == NIL)
        T = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
}
 
bool find(Node* T, int key) {
    Node *x = T;
    if (x == NIL) return false;
    if (x->key == key)
        return true;
    else if (key < x->key)
        return find(x->left, key);
    else
        return find(x->right, key);
}
 
Node* findNext(Node *z) {
    if (z == NIL) return NIL;
    if (z->right != NIL) {
        Node *x = z->right;
        while (x->left != NIL) {
            x = x->left;
        }
        return x;
    }
 
    Node *y = z->parent;
    while (y != NIL && y->right == z) {
        z = y;
        y = z->parent;
    }
    return y;
}
 
void del(Node* z, int key) {
    if (z == NIL) return;
    if (z->key == key) {
        if (z->left == NIL && z->right == NIL) {
            Node *w = z->parent;
            if (w != NIL && w->left == z) {
                w->left = NIL;
            } else if (w != NIL && w->right == z) {
                w->right = NIL;
            }
            if (z->parent == NIL) root = NIL;
            delete z;
        } else if (z->right == NIL) {
            Node *w = z->parent;
            Node *x = z;
            Node *y = z->left;
            z = y;
            if (w != NIL) {
                if (w->left == x) w->left = z;
                else              w->right = z;
            }
            if (x->parent == NIL) root = NIL;
            delete x;
        } else if (z->left == NIL) {
            Node *w = z->parent;
            Node *x = z;
            Node *y = z->right;
            z = y;
            z->parent = w;
            if (w != NIL) {
                if (w->right == x) w->right = z;
                else               w->left = z; 
            }
            if (x->parent == NIL) root = NIL;
            delete x;
        } else {
            Node* x = findNext(z);
            z->key = x->key;
            del(x, x->key);
        }
    } else if (key < z->key) {
        del(z->left, key);
    } else {
        del(z->right, key);
    }
}
 
int main()
{
    int n;
    scanf("%d", &n);
 
    for (int i = 0; i < n; ++i) {
        char cmd[20];
        int v;
        scanf("%s", cmd);
        if (cmd[0] == 'i') {
            scanf("%d", &v);
            Node *p = new Node;
            p->key = v;
            p->left = NIL;
            p->right = NIL;
            insert(root, p);
        } else if (cmd[0] == 'f') {
            scanf("%d", &v);
            printf("%s\n", find(root, v) ? "yes" : "no");
        } else if (cmd[0] == 'p') {
            inorder(root);
            printf("\n");
            preorder(root);
            printf("\n");
        } else if (cmd[0] == 'd') {
            scanf("%d", &v);
            del(root, v);
        }
    }
 
    return 0;
}
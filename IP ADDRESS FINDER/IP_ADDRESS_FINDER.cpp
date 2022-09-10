#include <time.h>
#include <iostream>

using namespace std;
class Node
{
public:
    int ipAdd;
    int dataPacket;
    Node *left;
    Node *right;
    Node *parent;

    Node()
    {
    }

    Node(int ipAdd)
    {
        this->ipAdd = ipAdd;
        this->parent = NULL;
        this->right = NULL;
        this->left = NULL;
    }
};

class splay_tree
{

public:
    Node *root;
    splay_tree()
    {
        root = new Node();
    }

    Node *maximum(Node *x)
    {
        while (x->right != NULL)
            x = x->right;
        return x;
    }

    void left_rotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;
        if (y->right != NULL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }


    void splay(Node *n)
    {
        while (n->parent != NULL)
        {
            if (n->parent == root)
            {
                if (n == n->parent->left)
                {
                    right_rotate(n->parent);
                }
                else
                {
                    left_rotate(n->parent);
                }
            }
            else
            {
                Node *p = n->parent;
                Node *g = p->parent;
                if (n->parent->left == n && p->parent->left == p)
                {
                    right_rotate(g);
                    right_rotate(p);
                }
                else if (n->parent->right == n && p->parent->right == p)
                {
                    left_rotate(g);
                    left_rotate(p);
                }
                else if (n->parent->right == n && p->parent->left == p)
                {
                    left_rotate(p);
                    right_rotate(g);
                }
                else if (n->parent->left == n && p->parent->right == p)
                {
                    right_rotate(p);
                    left_rotate(g);
                }
            }
        }
    }

    void insert(Node *n)
    {   
        Node *y = NULL;
        Node *temp = root;
        while (temp != NULL)
        {
            y = temp;
            if (n->ipAdd < temp->ipAdd)
                temp = temp->left;
            else
                temp = temp->right;
        }
        n->parent = y;
        if (y == NULL)
            root = n;
        else if (n->ipAdd < y->ipAdd)
            y->left = n;
        else
            y->right = n;
        splay(n);
    }

    Node *search(Node *n, int x)
    {
        if (x == n->ipAdd)
        {
            splay(n);
            return n;
        }
        else if (x < n->ipAdd)
            return search(n->left, x);
        else if (x > n->ipAdd)
            return search(n->right, x);
        else
            return NULL;
    }

    void inorder(Node *n, char *cmn)
    {
        if (n != NULL)
        {
            inorder(n->left, cmn);
            cout << cmn << n->ipAdd << "->" << n->dataPacket << endl;
            inorder(n->right, cmn);
        }
    }
};

int main()
{

    char cmn[] = "192.168.3.";
    splay_tree st;
    Node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = new Node(104);
    b = new Node(112);
    c = new Node(117);
    d = new Node(124);
    e = new Node(121);
    f = new Node(108);
    g = new Node(109);
    h = new Node(111);
    i = new Node(122);
    j = new Node(125);
    k = new Node(129);

    st.insert(a);
    st.insert(b);
    st.insert(c);
    st.insert(d);
    st.insert(e);
    st.insert(f);
    st.insert(g);
    st.insert(h);
    st.insert(i);
    st.insert(j);
    st.insert(k);

    int x;
    int find[11] = {104, 112, 117, 124, 121, 108, 109, 111,
                    122, 125, 129};
    Node *add[11] = {a, b, c, d, e, f, g, h, i, j, k};

    srand(time(0));

    for (x = 0; x < 11; x++)
    {
        int data = rand() % 200;
        Node *temp = st.search(add[x], find[x]);
        if (temp != NULL)
        {
            temp->dataPacket = data;
        }
    }
    printf("IP ADDRESS -> DATA PACKET\n");
    st.inorder(st.root, cmn);
    return 0;
}
#include<iostream>
#define red 1
#define black 2
#define NILL -99999


using namespace std;

struct node
{
    int key;
    int color;
    node * parent;
    node * left;
    node * right;

};

struct node * root;


void initializeTree()
{
    root = 0;
}

node * createnode(int key)
{
    node * newNode;
    newNode = new node();
    newNode->key = key;
    newNode->color = red;
    newNode->left = 0;
    newNode->right=0;
    newNode->parent = 0;
    return newNode;
}

void left_rotation(node * x)
{

    node * y = x->right;
    x->right = y->left;
    if (y->left != 0) y->left->parent = x;
    y->parent = x->parent;



    if(x->parent == 0)
    {
        root = y;
    }
    else if(x == x->parent->left)
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


void right_rotation(node * x)
{
    node * y = x->left;
    x->left = y->right;
    if (y->right != 0) y->right->parent = x;
    y->parent = x->parent;

    if(x->parent == 0)
    {
        root = y;
    }
    else if(x == x->parent->right)
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

void insert_fixup(node *z)
{
    if(z->parent == 0)
    {
        root->color = black;
        return;
    }
    while(z->parent->color == red)
    {
        node * y;
        if(z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y!=0)
            {
                if(y->color == red)
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->right)
                    {
                        z = z->parent;
                        left_rotation(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    right_rotation(z->parent->parent);
                }
            }
            else
            {
                if(z == z->parent->right)
                {
                    z = z->parent;
                    left_rotation(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                right_rotation(z->parent->parent);
            }
        }

        else
        {
            y = z->parent->parent->left;
            if (y!=0)
            {
                if(y->color == red)
                {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }
                else
                {
                    if(z == z->parent->left)
                    {
                        z = z->parent;
                        right_rotation(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    left_rotation(z->parent->parent);
                }
            }
            else
            {
                if(z == z->parent->left)
                {
                    z = z->parent;
                    right_rotation(z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                left_rotation(z->parent->parent);
            }

        }

        if(z->parent == 0 ) break;
    }

    root->color = black;
}

void insertnode(node * z)
{
    node* y = 0;
    node * x = root;

    while (x != 0)
    {
        y = x;
        if(z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if(y == 0) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;
    z->left = 0;
    z->right = 0;
    z->color = red;
    insert_fixup(z);
}





void print_inorder(node *x)
{
    if(x != 0)
    {
        print_inorder(x->left);
        cout<<"("<<x->key<<", ";
        if(x->color == red) cout<<"red) ";
        else cout<<"black) ";
        print_inorder(x->right);
    }
}


node * searchnode(node* x,int value)
{
    if(x!=0)
    {
        if(x->key == value) return x;
        else if(x->key < value)
        {
            return searchnode(x->right,value);
        }
        else
        {
            return searchnode(x->right,value);
        }
    }
    else return 0;
}

node* treesuccessor(node *z)
{
    while(z->left != 0)
    {
        z = z->left;
    }
    return z;
}

void deletenode(node* z)
{
    node* y;
    if(z->left == 0 || z->right == 0)
    {
        y = z;
    }
    else
    {
        y = treesuccessor(z->right);
    }

    node* x;
    if(y->left != 0)
    {
      x = y->left;
    }
    else
    {
        x = z->right;
    }

    x->parent = y->parent;
    if(y->parent == 0)
    {
        root = x;
    }
    else if(y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    if(y!=z)
    {
        z->key = y->key;
    }

    if(y->color == black)
    {
        //fixup
    }
}


int main()
{
    initializeTree();

    bool test = true;
    while(test)
    {
        int test1;
        cout<<"1.Insert Value  2.Delete Value  3.Print Tree  4.Search Node by value"<<endl;
        cout<<"5.Exit"<<endl;
        cin>>test1;
        if(test1 == 1)
        {
            int value;
            cout<<"Enter a value for inserting : ";
            cin>>value;
            insertnode(createnode(value));
        }
        else if(test1 == 2)
        {
            int value;
            cin >> value;
            node* temp = searchnode(root,value);
            if(temp!=0)
            {
                deletenode(temp);
                cout<<"Successfully deleted!\n";
            }
            else
            {
                cout<<"Node doesn't exist!\n";
            }

        }
        else if(test1 == 3)
        {
            cout<<endl<<"------------------------------------------------------------------"<<endl;
            cout<<"Print In order : \n";
            print_inorder(root);
            cout<<endl<<"------------------------------------------------------------------"<<endl;

        }
        else if(test1 == 4)
        {
            int value;
            cout<<"Enter a value for searching : ";
            cin>>value;
            node* temp = searchnode(root,value);
            if( temp == 0) cout<<"Sorry!Not found!\n";
            else
            {
                cout<< "Node Found! And It's color is : ";
                if(temp->color == red) cout<<"red \n";
                else cout<<"black \n";
            }
        }
        else
        {
            test = false;
        }
    }
}

/*
1 20
1 30
1 25
1 35
1 40
1 27
1 15
1 5
1 29
1 22
1 26
1 19
1 95
*/


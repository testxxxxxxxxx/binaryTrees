//Author: Marcin Wrzaskowski 160329
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

int maxValue = 0; 
int minValue = 0;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value = 0): key(value), left(nullptr), right(nullptr)
    {

    }

};

Node* newNode(int key) 
{
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int height(Node* node) 
{
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) 
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* rightRotate(Node* y) 
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) 
{
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insertAVL(Node* node, int key) 
{
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else 
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
Node* insertBST(Node* root, int key) 
{
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);

    return root;
}
Node* constructBinarySearchTree(int arr[], int size) 
{
    Node* root = nullptr;

    for (int i = 0; i < size; i++) {
        root = insertBST(root, arr[i]);
    }

    return root;
}
void findMax(Node *root)
{
    if(!root)
        return;

    if(root->key > maxValue)
        maxValue = root->key;

    findMax(root->left);
    findMax(root->right);

}
void findMin(Node *root)
{
    if(!root)
        return;

    if(root->key < minValue)
        minValue = root->key;

    findMin(root->left);
    findMin(root->right);

}
void inOrder(Node* root) {
    if (root == nullptr)
        return;

    if(root != nullptr)
    {
        inOrder(root->left);
        cout << root->key << ", ";
        inOrder(root->right);

    }
}
void preOrder(Node* root) {
    if (root == nullptr)
        return;

    if(root != nullptr)
    {

        cout << root->key << ", ";

        preOrder(root->left);
        preOrder(root->right);

    }

}
void postOrder(Node* root) {
    if (root == nullptr)
        return;

    if(root != nullptr)
    {
        postOrder(root->left);
        postOrder(root->right);

        cout << root->key << ", ";

    }
}

void print(Node *root)
{
    cout<<"In-order: ";
    inOrder(root);
    cout<<endl;
    cout<<"Post-order: ";
    postOrder(root);
    cout<<endl;
    cout<<"Pre-order: ";
    preOrder(root);
    cout<<endl;

}
void findMinMax(Node *root)
{
    cout<<endl;

    maxValue = 0;
    minValue = root->key;

    findMax(root);
    findMin(root);

    cout<<"min: "<<minValue<<endl;
    cout<<"max: "<<maxValue<<endl;

}
string exportTree(Node *root)
{
    string l_str = "";
    string r_str = "";

    if(!root->left && !root->right)
        return "node " + to_string(root->key);

    if(root->left)
        l_str = "child " + exportTree(root->left);
    else
        l_str = "child[missing]";
    
    if(root->right)
        r_str = "child " + exportTree(root->right);
    else
        r_str = "child[missing]";

    return " node " + to_string(root->key) + " \\" + l_str + "\\" + r_str + "\\";

}
Node* findMinInBinary(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}
Node* removeKey(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = removeKey(root->left, key);
    else if (key > root->key)
        root->right = removeKey(root->right, key);
    else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr) {
            Node* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            Node* temp = findMinInBinary(root->right);
            root->key = temp->key;
            root->right = removeKey(root->right, temp->key);
        }
    }
    return root;
}
void deleteAllNodes(Node *root)
{
    if(root == nullptr)
        return;

    deleteAllNodes(root->left);
    deleteAllNodes(root->right);

    delete root;

}
int treeToList(Node *root)
{
    int count = 0;
 
    Node* temp = root->right;
 
    while (temp) 
    {     
        if (temp->left) 
        {
            Node* oldTmp0 = temp;
            temp = temp->left;
            oldTmp0->left = temp->right;
            temp->right = oldTmp0;
            root->right = temp;
        }
        else 
        {
            count++;
            root = temp;
            temp = temp->right;
        }

    }
 
    return count;
    
}
void compress(Node *root, int m)
{
    Node* temp = root->right;
 
    for (int i = 0; i < m; i++) 
    {
        Node* oldTemp = temp;
        temp = temp->right;
        root->right = temp;
        oldTemp->right = temp->left;
        temp->left = oldTemp;
        root = temp;
        temp = temp->right;
    }
}
Node* balanceTree(Node* root)
{
    Node* root0 = new Node(0);
 
    root0->right = root;
 
    int count = treeToList(root0);

    int height = log2(count + 1);
 
    int m = pow(2, height) - 1;
 
    compress(root0, count - m);

    for (m = m / 2; m > 0; m /= 2) {
        compress(root0, m);
    }
 
    return root0->right;
}

int main(int argc, char *argv[])
{
    //Driver code for tests

    /*Node *root = nullptr;

    root = insertAVL(root, 10);
    root = insertAVL(root, 20);
    root = insertAVL(root, 30);
    root = insertAVL(root, 40);
    root = insertAVL(root, 50);
    root = insertAVL(root, 25);

    findMinMax(root);

    print(root);

    removeKey(root, 10);
    removeKey(root, 25);

    print(root);

    balanceTree(root);

    print(root);

    delete root;

    int numbers[] = {50, 30, 20, 40, 70, 60, 80};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    Node *bst = constructBinarySearchTree(numbers, size);

    cout<<endl;

    print(bst);

    removeKey(bst, 50);
    removeKey(bst, 40);

    deleteAllNodes(bst);

    print(bst);*/

    if((string)argv[1] == "--tree")
    {
        Node *root = nullptr;

        if((string)argv[2] == "AVL") 
        {
            int numberOfNodes = 0;
            int *n;
            int *nodes;
            string insert;

            cout<<"node>";
            cin>>numberOfNodes;

            cout<<numberOfNodes<<endl;

            nodes = new int[numberOfNodes];

            n = nodes;

            cout<<"insert>";
            getline(cin >> ws, insert);
            
            string value = "";
            int it = -1;

            for(int i = 0; i < insert.length(); i++)
            {
                if(insert[i] != ' ')
                {
                    value += insert[i];
                }
                else
                {
                    it += 1;

                    nodes[it] = stoi(value);

                    value = "";
                }

                if(i == insert.length() - 1 && insert[i] != ' ')
                {
                    it += 1;

                    nodes[it] = stoi(value);

                    value = "";
                    
                }

            }

            for(int i = 0; i < numberOfNodes; i++)
            {
                root = insertAVL(root, nodes[i]);

            }

        }
        else if((string)argv[2] == "BST")
        {
            int numberOfNodes = 0;
            int *n;
            int *nodes;
            string insert;

            cout<<"node>";
            cin>>numberOfNodes;

            cout<<numberOfNodes<<endl;

            nodes = new int[numberOfNodes];

            n = nodes;

            cout<<"insert>";
            getline(cin >> ws, insert);
            
            string value = "";
            int it = 0;

            for(int i = 0; i < insert.length(); i++)
            {
                if(insert[i] != ' ')
                {
                    value += insert[i];
                }
                else
                {
                    nodes[it] = stoi(value);

                    it += 1;

                    value = "";
                }

            }

            root = constructBinarySearchTree(nodes, numberOfNodes);

        }
        else
        {
            cout<<"Error"<<endl;

            return 0;
        }

        string action = "action";
        string command = "";

        while(true)
        {
            cout<<action<<">";
            cin>>command;

            if(command == "Print")
                print(root);
            if(command == "Exit")
                return 0;

        }

    }
    else
        cout<<"Error"<<endl;

    return 0;
}
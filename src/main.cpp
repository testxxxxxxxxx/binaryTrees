//Author: Marcin Wrzaskowski 160329
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

int maxValue = 0; 
int minValue = 0;
bool removed = false;
chrono::milliseconds timePrint;

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

    auto startPrint = chrono::high_resolution_clock::now();

    if(!removed)
        inOrder(root);

    auto stopPrint = chrono::high_resolution_clock::now();

    timePrint = chrono::duration_cast<chrono::milliseconds>(stopPrint - startPrint);

    cout<<"timePrint: "<<timePrint.count()<<endl;

    cout<<endl;
    cout<<"Post-order: ";
    if(!removed)
        postOrder(root);
    cout<<endl;
    cout<<"Pre-order: ";
    if(!removed)
        preOrder(root);
    cout<<endl;

}
void findMinMax(Node *root)
{
    cout<<endl;

    maxValue = 0;
    minValue = root->key;

    if(!removed)
    {
        findMax(root);
        findMin(root);

    }
    else
    {
        minValue = 0;
        maxValue = 0;

    }

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
    if(!argv[1] || !argv[2])
    {
        cout<<"Error"<<endl;

        return 0;
    }

    string path = "/home/tomasz/projects/binaryTrees/benchmark_results/";
    string name = "benchmark_results.csv";
    string dir = path + name;

    fstream benchmarkResults;

    benchmarkResults.open(dir, ios::out | ios::app);

        if(strcmp(argv[1], "--tree") == 0)
        {
            int numberOfNodes = 0;

            Node *root = nullptr;

            if(strcmp(argv[2], "AVL") == 0) 
            {
                int *n;
                int *nodes;
                string insert;

                cout<<"node>";
                cin>>numberOfNodes;

                nodes = new int[numberOfNodes];

                n = nodes;

                cout<<"insert>";
                getline(cin >> ws, insert);
                
                string value = "";
                int it = -1;

                for(int i = 0; i < insert.length(); i++)
                {
                    if(insert[i] != ' ' && insert[i] != ',')
                    {
                        value += insert[i];
                    }
                    else
                    {
                        it += 1;

                        nodes[it] = stoi(value);

                        value = "";
                    }

                    if(i == insert.length() - 1 && insert[i] != ' ' && insert[i] != ',')
                    {
                        it += 1;

                        nodes[it] = stoi(value);

                        value = "";
                        
                    }

                }

                auto startAVL = chrono::high_resolution_clock::now();

                sort(nodes, nodes + numberOfNodes);

                cout<<"sorted: ";
                for(int i = 0; i < numberOfNodes; i++)
                {
                    cout<<nodes[i]<<" ";

                }

                cout<<endl;

                for(int i = 0; i < numberOfNodes; i++)
                {
                    root = insertAVL(root, nodes[i]);

                }

                auto stopAVL = chrono::high_resolution_clock::now();

                auto timeAVL = chrono::duration_cast<chrono::milliseconds>(stopAVL - startAVL);

                cout<<"timeAVL: "<<timeAVL.count()<<endl;

                benchmarkResults<<"createAVLTree;"<<to_string(numberOfNodes)+";"<<to_string(timeAVL.count())<<endl;

            }
            else if(strcmp(argv[2], "BST") == 0)
            {
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
                    if(insert[i] != ' ' && insert[i] != ',')
                    {
                        value += insert[i];
                    }
                    else
                    {
                        it += 1;

                        nodes[it] = stoi(value);

                        value = "";
                    }

                    if(i == insert.length() - 1 && insert[i] != ' ' && insert[i] != ',')
                    {
                        it += 1;

                        nodes[it] = stoi(value);

                        cout<<it<<endl;
                        cout<<nodes[it]<<endl;

                        value = "";
                        
                    }

                }

                cout<<"inserting: ";

                for(int i = 0; i < numberOfNodes; i++)
                {
                    cout<<nodes[i]<<" ";

                }

                cout<<endl;

                auto startBST = chrono::high_resolution_clock::now();

                root = constructBinarySearchTree(nodes, numberOfNodes);

                auto stopBST = chrono::high_resolution_clock::now();

                auto timeBST = chrono::duration_cast<chrono::milliseconds>(stopBST - startBST);

                cout<<"timeBST: "<<timeBST.count()<<endl;

                benchmarkResults<<"createBSTTree;"<<to_string(numberOfNodes)+";"<<to_string(timeBST.count())<<endl;

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

                if(command == "Help")
                {
                    cout<<"Help"<<"                     "<<"Show this message"<<endl;
                    cout<<"FindMinMax"<<"                     "<<"Find min max"<<endl;
                    cout<<"Print"<<"                     "<<"print tree inorder, postorder, preorder"<<endl;
                    cout<<"Remove"<<"                     "<<"Remove element from tree"<<endl;
                    cout<<"Delete"<<"                     "<<"Delete whole tree"<<endl;
                    cout<<"Export"<<"                     "<<"Export tzpicture"<<endl;
                    cout<<"Rebalance"<<"                     "<<"Rebalance tree"<<endl;
                    cout<<"Exit"<<"                     "<<"Exit"<<endl;

                }
                if(command == "Print")
                {
                    print(root);

                    benchmarkResults<<"Inorder"+(string)argv[2]+";"<<to_string(numberOfNodes)+";"<<to_string(timePrint.count())<<endl;
                }
                if(command == "Remove")
                {
                    string nodesToRemove = "";
                    string value = "";

                    cout<<"numberOfNodes: "<<numberOfNodes<<endl;

                    cout<<"remove>";
                    getline(cin >> ws, nodesToRemove);

                    for(int i = 0; i < nodesToRemove.length(); i++)
                    {
                        if(numberOfNodes <= 1)
                            removed = true;

                        if(nodesToRemove[i] != ' ')
                        {
                            value += nodesToRemove[i];
                        }
                        else
                        {
                            root = removeKey(root, stoi(value));
                            numberOfNodes--;

                            value = "";
                        }

                        if(i == nodesToRemove.length() - 1 && nodesToRemove[i] != ' ' && !removed)
                        {
                            root = removeKey(root, stoi(value));
                            numberOfNodes--;

                            value = "";
                            
                        }

                    }

                }
                if(command == "Delete")
                {
                    cout<<"Deleting: ";
                    postOrder(root);

                    deleteAllNodes(root);

                    removed = true;

                    cout<<endl;

                    cout<<"Tree sucessfully removed"<<endl;

                }
                if(command == "FindMinMax")
                {
                    auto startFindMinMax = chrono::high_resolution_clock::now();

                    findMinMax(root);

                    auto stopFindMinMax = chrono::high_resolution_clock::now();

                    auto timeFindMinMax = chrono::duration_cast<chrono::milliseconds>(stopFindMinMax - startFindMinMax);

                    cout<<"timeFindMinMax: "<<timeFindMinMax.count()<<endl;

                    benchmarkResults<<"FindMinMax"+(string)argv[2]+";"<<to_string(numberOfNodes)+";"<<to_string(timeFindMinMax.count())<<endl;

                }
                if(command == "Export" && !removed)
                {
                    string exportResult = exportTree(root);
                    cout<<exportResult<<endl;

                    fstream file;

                    file.open("exportResult.txt", ios::out);

                    file<<exportResult<<endl;

                }                
                if(command == "Rebalance" && !removed)
                {
                    auto startRebalance = chrono::high_resolution_clock::now();

                    root = balanceTree(root);

                    auto stopRebalance = chrono::high_resolution_clock::now();

                    auto timeRebalance = chrono::duration_cast<chrono::milliseconds>(stopRebalance - startRebalance);

                    cout<<"timeRebalance: "<<timeRebalance.count()<<endl;

                    benchmarkResults<<"RebalanceTree"+(string)argv[2]+";"<<to_string(numberOfNodes)+";"<<to_string(timeRebalance.count())<<endl;

                }
                if(command == "Exit")
                    return 0;

            }

        }
        else
            cout<<"Error"<<endl;

    return 0;
}
#ifndef PROJECT1_AVL_H
#define PROJECT1_AVL_H
#include <iostream>
#include <stack>
#include "helper.h"

using namespace std;

class BalancedTree{
private:
    Node* root = nullptr;
    vector<string> postorderNames(Node* node, vector<string> &names);
    vector<string> preorderNames(Node* node, vector<string> &names);
    vector<string> inorderNames(Node* node, vector<string> &names);
    bool RemoveIDHelper(int id, Node* node, Node* prev_node = nullptr);
    Node* SearchIDHelper(Node* node, int id);
    Node* getRoot();
    bool SearchNameHelper(Node* node, string name);
    bool BalanceBranch(stack<Node*> ancestors);
    vector<int> Inorder(Node* node, vector<int> &ids);
    bool deleteTreeNode(Node* node, Node* prev_node, int id);


public:
    BalancedTree() = default;
    ~BalancedTree();
    //Main methods
    int printLevelCount();
    string printPostorder();
    string printPreorder();
    string printInorder();
    bool Insert(string name, int id);
    bool removeID(int id);
    Node* searchID(int id);
    bool searchName(string name);
    bool removeInorderN(int n);


    //methods that need to be public for testing
    vector<int> inorderTester(vector<int> &ids);
    bool isRoot(int id);

};

BalancedTree::~BalancedTree(){
    destroyTree(getRoot());
}

Node* BalancedTree::getRoot(){
    return this->root;
}

//function to handle when to do rotations
bool BalancedTree::BalanceBranch(stack<Node*> ancestors){

    Node* curr = nullptr;

    while(!ancestors.empty()){
        // iterate through ancestors
        // adjust height to
        curr = ancestors.top();

        ancestors.pop();

        Node* connector = nullptr;
        if (!ancestors.empty()){
            connector = ancestors.top();
        }

        curr->changeHeight(CalculateHeight(curr));
        //following logic was adapted from inclass slides
        if (Balance(curr) < -1){ //right heavy
            if (Balance(curr->getRight()) > 0) {//right subtree is left heavy -> Right Left Rotation
                curr = RightLeftRotation(curr);
            }
            else{
                curr = LeftRotation(curr);
            }
        }
        else if (Balance(curr) > 1){ // left side is heavy
            if (Balance(curr->getLeft()) < 0){//left right rotation
                curr = LeftRightRotation(curr);
            }
            else{//Left Left
                curr = RightRotation(curr);
            }
        }
        else{
            continue;
        }
        if (ancestors.empty()){
            this->root = curr;
            continue;
        }
        if (curr->getStudentInfo().gatorID < connector->getStudentInfo().gatorID){
            connector->changeLeft(curr);
        }
        else{
            connector->changeRight(curr);
        }

    }
    return true;
}

bool BalancedTree::Insert(string name, int id){
    student stu;
    stu.gatorID = id;
    stu.name = name;

    stack<Node*> ancestors;

    if (this->root == nullptr){ // check if tree is empty
        this->root = new Node(stu, 1);
        return true;
    }

    Node* curr = this->root;


    while(curr != nullptr){ // traverse to the bottom of the tree
        //store the current students information (ID and name)
        student current_student;
        current_student.gatorID = curr->getStudentInfo().gatorID;
        current_student.name = curr->getStudentInfo().name;
        ancestors.push(curr);

        if (id > current_student.gatorID){ // traverse right

            if (curr->getRight() == nullptr){
                Node* newNode = new Node(stu, 1);// height is the same because we will increment the ancestors by one
                curr->changeRight(newNode);
                curr = curr->getRight();

                break;
            }

            curr = curr->getRight();

        }
        else if (id < current_student.gatorID){ // traverse left
            if (curr->getLeft() == nullptr){
                Node* newNode = new Node(stu, 1);
                curr->changeLeft(newNode);
                curr = curr->getLeft();
                break;
            }
            curr = curr->getLeft();
        }
        else{
            return false; //Node already exists (not unique)
        }
    }

    BalanceBranch(ancestors);
    return true;
}

//handles all logic for Removing using an ID
//recursively iterate through nodes until the ID is found, or not
//logic altered from Project 1 breakdown google slides: https://docs.google.com/presentation/d/1llw2u6PmbgUjE1nQM_Qyc4lVMeb84_UVINRpQvrycqE/edit#slide=id.g10f8ea06aa0_1_25
bool BalancedTree::RemoveIDHelper(int id, Node* node, Node* prev_node){
    if (node == nullptr){
        return false;
    }

    if (node->getStudentInfo().gatorID == id){
        return deleteTreeNode(node, prev_node, id); //function made to handle deleting and moving nodes
    }

    prev_node = node;
    if (id > node->getStudentInfo().gatorID){
        return RemoveIDHelper(id, node->getRight(), prev_node);
    }
    else{
        return RemoveIDHelper(id, node->getLeft(), prev_node);
    }
}

//wraps the removeID function to deny users the ability to touch memory
bool BalancedTree::removeID(int id){
    return RemoveIDHelper(id, getRoot());
}

//recursively iterates through nodes until an ID match is found
Node* BalancedTree::SearchIDHelper(Node* node, int id){
    if (node == nullptr){
        return node;
    }
    student temp = node->getStudentInfo();
    if (id < node->getStudentInfo().gatorID){
        return SearchIDHelper(node->getLeft(), id);
    }
    else if (id > node->getStudentInfo().gatorID){
        return SearchIDHelper(node->getRight(), id);
    }
    else{
        return node;
    }
}

//wrapper for searchID function
Node* BalancedTree::searchID(int id){
    return SearchIDHelper(this->root, id);
}

//prints Nodes in order traversal
string BalancedTree::printInorder() {
    vector<string> names;
    names = inorderNames(this->root ,names);
    string out = "";
    for (string name : names){
        out += " " + name + ",";
    }
    out = out.substr(1, out.length() - 2);
    cout << out << endl;

    return out;
}

//prints nodes using preorder traversal
string BalancedTree::printPreorder() {
    vector<string> names;
    names = preorderNames(this->root ,names);
    string out = "";
    for (string name : names){
        out += " " + name + ",";
    }
    out = out.substr(1, out.length() - 2);
    cout << out << endl;

    return out;
}

//prints nodes using post order traversal
string BalancedTree::printPostorder() {
    vector<string> names;
    names = postorderNames(this->root ,names);
    string out = "";
    for (string name : names){
        out += " " + name + ",";
    }
    out = out.substr(1, out.length() - 2);
    cout << out << endl;

    return out;
}

//returns the Level count for the tree
int BalancedTree::printLevelCount(){
    if (this->root == nullptr){
        return 0;
    }

    return this->root->getHeight();
}

//handles logic of searching by name
bool BalancedTree::SearchNameHelper(Node* node, string name) {
    if (node == nullptr) {
        return false;
    }

    int count = 0;

    stack<Node *> nodes;
    nodes.push(node);

    while (!nodes.empty()) {
        Node *current = nodes.top();
        nodes.pop();

        if (current->getStudentInfo().name == name) {
            cout << current->getStudentInfo().gatorID << endl;
            count++;
        }

        if (current->getRight() != nullptr) {
            nodes.push(current->getRight());
        }
        if (current->getLeft() != nullptr) {
            nodes.push(current->getLeft());
        }
    }

    if (count > 0){
        return true;
    }
    else{
        return false;
    }
}

//wrapper for searching by name
bool BalancedTree::searchName(string name){
    return SearchNameHelper(this->root, name);
}

//removes the nth node
bool BalancedTree::removeInorderN(int n) {
    vector<int> ids;
    Inorder(this->getRoot(), ids); //using a helper function proved to be far easier
    if((n-1) < int(ids.size())) {
        return removeID(ids[n - 1]);//searches tree for the nth id
    }

    return false;
}

//returns a vector of Ids using in order traversal
vector<int> BalancedTree::Inorder(Node* node, vector<int> &ids) {
    if (node == nullptr) {
        return ids;
    }

    Inorder(node->getLeft(), ids);

    ids.push_back(node->getStudentInfo().gatorID);

    Inorder(node->getRight(), ids);

    return ids;
}

//returns a vector of Names using post order traversal
vector<string> BalancedTree::postorderNames(Node* node, vector<string> &names) {
    if (node == nullptr) {
        return names;
    }

    postorderNames(node->getLeft(), names);
    postorderNames(node->getRight(), names);
    names.push_back(node->getStudentInfo().name);

    return names;
}

//returns a vector of Names using pre order traversal
vector<string> BalancedTree::preorderNames(Node* node, vector<string> &names) {
    if (node == nullptr) {
        return names;
    }

    names.push_back(node->getStudentInfo().name);
    preorderNames(node->getLeft(), names);
    preorderNames(node->getRight(), names);

    return names;
}

//returns a vector of Names using in order traversal
vector<string> BalancedTree::inorderNames(Node* node, vector<string> &names) {
    if (node == nullptr) {
        return names;
    }

    inorderNames(node->getLeft(), names);
    names.push_back(node->getStudentInfo().name);
    inorderNames(node->getRight(), names);

    return names;
}

//handles logic of deleting tree nodes
bool BalancedTree::deleteTreeNode(Node* node, Node* prev_node, int id) {
    if (node == nullptr) {
        return false;  // Node doesn't exist
    }


    if (node->getLeft() == nullptr && node->getRight() == nullptr) {//no children
        if (prev_node != nullptr) {
            if (id > prev_node->getStudentInfo().gatorID) { //make parents right child
                prev_node->changeRight(nullptr);
            } else {//make parents left child
                prev_node->changeLeft(nullptr);
            }
        }
        else {
            this->root = nullptr;
        }
        delete node;  // delete the target node
        calculateSubtreeHeight(this->root);
        return true;
    }

    if (node->getLeft() == nullptr) {//one child (right)
        Node* child = node->getRight();
        if (prev_node != nullptr) {
            if (id > prev_node->getStudentInfo().gatorID) {
                prev_node->changeRight(child);
            } else {
                prev_node->changeLeft(child);
            }
        } else {
            this->root = child;
        }
        delete node;
        calculateSubtreeHeight(this->root); //recalculate the heights of the tree
        return true;
    }


    if (node->getRight() == nullptr) {//one child (left)
        Node* child = node->getLeft();
        if (prev_node != nullptr) {
            if (id > prev_node->getStudentInfo().gatorID) {
                prev_node->changeRight(child);
            } else {
                prev_node->changeLeft(child);
            }
        } else {
            this->root = child;
        }
        delete node;
        calculateSubtreeHeight(this->root);
        return true;
    }


    //two children
    Node* successorParent = node;
    Node* successor = node->getRight(); //node which will be swapped


    while (successor->getLeft() != nullptr) {//finding leftmost Node
        successorParent = successor;
        successor = successor->getLeft();
    }

    //swap nodes
    if (successorParent != node) {
        successorParent->changeLeft(successor->getRight());
    } else {
        successorParent->changeRight(successor->getRight());
    }

    if (prev_node != nullptr) {
        if (prev_node->getLeft() == node) {
            prev_node->changeLeft(successor);
        } else {
            prev_node->changeRight(successor);
        }
    } else {
        this->root = successor;
    }

    successor->changeLeft(node->getLeft());
    successor->changeRight(node->getRight());

    delete node;
    calculateSubtreeHeight(this->root);
    return true;

}

//Methods for testing
//method for testing a large ammount of inserts
vector<int> BalancedTree::inorderTester(vector<int> &ids){
    return Inorder(this->root, ids);
}

//allows testing if a node is the root without accessing memory directly
bool BalancedTree::isRoot(int id){
    if (id == this->root->getStudentInfo().gatorID){
        return true;
    }
    return false;
}

#endif //PROJECT1_AVL_H

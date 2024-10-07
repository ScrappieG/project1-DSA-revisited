#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H

#include <iostream>

using namespace std;

struct student{
    string name ="No Name";
    int gatorID = -2; // this is redundant, but CLion didnt want me to leave it be
};

class Node{
private:
    student studentInfo;
    Node* right = nullptr;
    Node* left = nullptr;
    int height = 1;

public:
    Node(student studentInfo, int height = 1){
        this->studentInfo = studentInfo;
        this->height = height;
        this->right = nullptr;
        this->left = nullptr;
    }

    student getStudentInfo(){
        return this->studentInfo;
    }
    Node* getRight(){
        return this->right;
    }
    Node* getLeft(){
        return this->left;
    }
    int getHeight(){
        return this->height;
    }
    void changeRight(Node* newRight){
        this->right = newRight;
    }
    void changeLeft(Node* newLeft){
        this->left = newLeft;
    }
    void changeHeight(int height){
        this->height = height;
    }

};

#endif //PROJECT1_NODE_H

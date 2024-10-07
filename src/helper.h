#ifndef PROJECT1_HELPER_H
#define PROJECT1_HELPER_H


#include <iostream>


#include "node.h"

using namespace std;



int CalculateHeight(Node* node){
    int leftHeight = 1;
    int rightHeight = 1;
    if(node == nullptr){
        return 0;
    }
    if (node->getLeft() == nullptr && node->getRight() == nullptr){
        return 1; //default leaf value
    }

    if (node->getRight() == nullptr){
        leftHeight = node->getLeft()->getHeight() + 1;
    }
    else if (node->getLeft() == nullptr){
        rightHeight = node->getRight()->getHeight() + 1;
    }
    else{
        rightHeight = node->getRight()->getHeight() + 1;
        leftHeight = node->getLeft()->getHeight() + 1;
    }
    return max(rightHeight, leftHeight);

}
void calculateSubtreeHeight(Node* node){
    if (node == nullptr){
        return;
    }

    calculateSubtreeHeight(node->getLeft());
    calculateSubtreeHeight(node->getRight());

    node->changeHeight(CalculateHeight(node));

    return;

}

Node* LeftRotation(Node* ancestor){
    Node* parent = ancestor->getRight();
    Node* temp = parent->getLeft();

    parent->changeLeft(ancestor);
    ancestor->changeRight(temp);
    //since parent is the root of the subtree we call the following function on it
    calculateSubtreeHeight(parent);

    return parent;
}

Node* RightRotation(Node* ancestor){
    Node* parent = ancestor->getLeft();
    Node* temp = parent->getRight();

    parent->changeRight(ancestor);
    ancestor->changeLeft(temp);

    calculateSubtreeHeight(parent);
    return parent;
}

Node* LeftRightRotation(Node* ancestor){
    Node* parent = ancestor->getLeft();
    Node* child = parent->getRight();
    Node* temp = child->getLeft();

    child->changeLeft(parent);
    ancestor->changeLeft(child);
    parent->changeRight(temp);

    calculateSubtreeHeight(parent);

    return RightRotation(ancestor);
}

Node* RightLeftRotation(Node* ancestor){
    Node* parent = ancestor->getRight();
    Node* child = parent->getLeft();

    Node* temp = child->getRight();
    child->changeRight(parent);
    ancestor->changeRight(child);
    parent->changeLeft(temp);

    calculateSubtreeHeight(ancestor);

    return LeftRotation(ancestor);
}

int Balance(Node* node){
    int right_subtree = 0;
    int left_subtree = 0;

    if (node == nullptr){
        return 0;
    }
    else if (node->getRight() == nullptr && node->getLeft() == nullptr){
        return 0;
    }
    else if (node->getRight() == nullptr){
        left_subtree = node->getLeft()->getHeight();
    }
    else if (node->getLeft() == nullptr){
        right_subtree = node->getRight()->getHeight();
    }
    else{
        left_subtree = node->getLeft()->getHeight();
        right_subtree = node->getRight()->getHeight();
    }
    return (left_subtree - right_subtree);
}

void destroyTree(Node* node){
    if (node == nullptr){
        return;
    }
    destroyTree(node->getLeft());
    destroyTree(node->getRight());
    delete node;
}


#endif //PROJECT1_HELPER_H

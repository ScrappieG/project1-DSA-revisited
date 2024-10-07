#ifndef PROJECT1_INPUT_H
#define PROJECT1_INPUT_H
#include <vector>
#include "AVL.h"


vector<string> parseInput(string line){ // break up user input into functions and arguments
    vector<string> output;
    while(true){
        if(line.find(' ') == string::npos){
            break;
        }
        int space_index = line.find(' ');

        string temp = line.substr(0, space_index);
        line = line.substr(space_index + 1);

        output.push_back(temp); // storing each func or args in vector
    }

    if (line.length() > 0){ // catch any args left
        output.push_back(line);
    }
    return output;

}

bool validateName(string name){// validates names are alphabetical, and have ""
    if(name.length() <= 2){
        return false;
    }
    if (name[0] =='\"' && name[name.length() - 1] == '\"'){
        name = name.substr(1, name.length() - 2);// removing ""
        for (char letter : name){
            if (!isalpha(letter)){ // using the function from C to check if each char is alpha
                return false;
            }
        }
        return true;
    }
    return false;
}

bool validateID(string idString){ // validates IDs are numerical

    try{
        stoi(idString);
        if (idString.length() != 8){ // ID's must be 8 digits
            return false;
        }

        return true;
    }
    catch(...){
        return false; // stoi will throw an exception if it is given a non-numerical char
    }
}

bool insert(vector<string> input, BalancedTree &tree){//handles arguments for insert
    if (input.size() < 2){
        return false;
    }
    string name = input[1];

    if (!validateName(name)){
        return false;
    }
    name = name.substr(1, name.length() - 2);
    string idString = input[2];

    if(!validateID(idString)){
        return false;
    }
    int id = stoi(idString);

    return tree.Insert(name, id);
}

bool remove(vector<string> input, BalancedTree &tree){//handles arguments for remove
    if (input.size() <= 1){
        return false;
    }
    string idString = input[1];

    if (!validateID(idString)){
        return false;
    }
    int id = stoi(idString);


    return tree.removeID(id);

}

bool search(vector<string> input, BalancedTree &tree){ //handles arguments for search
    if (input.size() <= 1){
        return false;
    }
    string idString = input[1];

    if (validateID(idString)){
        int id = stoi(idString);
        Node* node = tree.searchID(id);
        if (node == nullptr){
            return false;
        }
        cout << node->getStudentInfo().name << endl;
        return true;
    }
    if (validateName(idString)){
        string name = idString.substr(1, idString.length() - 2);
        return tree.searchName(name);
    }
    return false;
}

bool removeInorder(vector<string> input, BalancedTree &tree){//handles arguments for removeInorder
    int n;
    string nString = input[1];

    try{
        n = stoi(nString);
    }
    catch(...){
        return false;
    }
    return tree.removeInorderN(n);
}

#endif //PROJECT1_INPUT_H

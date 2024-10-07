#include <iostream>
#include <vector>
#include "AVL.h"
#include "input.h"

using namespace std;

int main(){
    BalancedTree tree;
    int num = 0;
    string line = "";
    while(num <= 0){
        getline(cin, line);
        try{
            num = stoi(line);
        }
        catch(...){
            continue;
        }
    }
    getline(cin, line);

    for(int i = 0; i < num; i++){
        line = "";
        bool out = false;
        getline(cin, line);

        vector<string> input = parseInput(line);

        if (input.empty()){
            continue;
        }
        string function = input[0];
        if (function == "insert"){
            out = insert(input, tree);
        }

        else if (function == "remove"){
            out = remove(input, tree);
        }
        else if (function == "search"){
            if (input.size() <= 1){
                continue;
            }
            out = search(input, tree);
            if (out){
                continue;
            }
        }
        else if (function == "removeInorder"){
            if (input.size() <= 1){
                continue;
            }
            out = removeInorder(input, tree);
        }
        else if (function == "printInorder"){
            tree.printInorder();
            continue;
        }
        else if (function == "printPostorder"){
            tree.printPostorder();
            continue;
        }
        else if (function == "printPreorder"){
            tree.printPreorder();
            continue;
        }
        else if (function == "printLevelCount"){
            int level = tree.printLevelCount();
            cout << level << endl;
            continue;
        }
        else if (function == "quit"){
            break;
        }
        else{
            continue;
        }
        if (out){
            cout << "successful" << endl;
        }
        else{
            cout << "unsuccessful" << endl;
        }
    }

    return 1;
}


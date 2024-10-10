/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>

#include "AVL.h"
#include "input.h"


using namespace std;
//Note: I found out about sections, I think it keeps the test cases more organized hopefully it doesnt mess anything up
TEST_CASE("Input and Parsing", "[parseInput]") {

    SECTION("insert") {
        BalancedTree tree;
        vector<string> testInputs = {
                "insert \"1234567aasdf\" 12345678",
                "insert \"as#as()\" 12345678",
                "insert \"Jack\"\" 12345678",
                "insert \"jack\" 1234567",
                "insert \"jack\" 1234a67",
        };
        for (const auto & testInput : testInputs){
            vector<string> test = parseInput(testInput);
            REQUIRE(insert(test, tree) == false);
        }
    }

    SECTION("remove") {
        BalancedTree tree;
        vector<string> testInputs = {
                "remove     12345678",
                "remove 12/4!6a8",
                "remove 1",
                "remove 1234567",
                "remove",
        };
        for (const auto & testInput : testInputs){
            vector<string> test = parseInput(testInput);
            REQUIRE(remove(test, tree) == false);
        }
    }

    SECTION("search") {
        BalancedTree tree;

        vector<string> testInputs = {
                "search     12345678",
                "search 12/4!6a8",
                "search 1",
                "search 1234567",
                "search",
                "search     \"asdfa\"",
                "search \"asd\"fa\"",
                "search \"as123\"",
                "search \"as!fa\"",
                "search",
        };
        for (const auto & testInput : testInputs){
            vector<string> test = parseInput(testInput);
            REQUIRE(search(test, tree) == false);
        }
    }
}

TEST_CASE("Edge Cases", "[Insert], [Remove], [RemoveN]") {
    BalancedTree tree;

    tree.Insert("Jack", 12345678);
    tree.Insert("Joe", 23456789);
    tree.Insert("Bob", 33456789);
    tree.Insert("Carl", 63456789);

    SECTION("Inserting Existing ID") {
        REQUIRE(tree.Insert("Mark", 12345678) == false);
        REQUIRE(tree.Insert("Carl", 63456789) == false);
    }

    SECTION("Removing Node that does not exist"){
        REQUIRE(tree.removeID(73456789) == false);
    }
    SECTION("Removing N with invalid numbers"){
        REQUIRE(tree.removeInorderN(-1) == false);
        REQUIRE(tree.removeInorderN(1000) == false);
    }
}

TEST_CASE("Rotations", "[Left-Left], [Right-Right], [Left-Right], [Right-Left]") {

    SECTION("Left Left Rotation") {
        BalancedTree tree;
        tree.Insert("Bob", 33456789);
        tree.Insert("Joe", 23456789);
        tree.Insert("Jack", 12345678);
        REQUIRE(tree.isRoot(23456789) == true);
        REQUIRE(tree.printPostorder() == "Jack, Bob, Joe");
    }
    SECTION("Right Right Rotation") {
        BalancedTree tree;
        tree.Insert("Jack", 12345678);
        tree.Insert("Joe", 23456789);
        tree.Insert("Bob", 33456789);
        REQUIRE(tree.isRoot(23456789) == true);
        REQUIRE(tree.printPostorder() == "Jack, Bob, Joe");
    }
    SECTION("Left Right Rotation") {
        BalancedTree tree;
        tree.Insert("Jack", 12345678);
        tree.Insert("Joe", 12345676);
        tree.Insert("Bob", 12345677);
        REQUIRE(tree.isRoot(12345677) == true);
        REQUIRE(tree.printPostorder() == "Joe, Jack, Bob");
    }
    SECTION("Right Left Rotation") {
        BalancedTree tree;
        tree.Insert("Jack", 12345677);
        tree.Insert("Joe", 12345678);
        tree.Insert("Bob", 12345679);
        REQUIRE(tree.isRoot(12345678) == true);
        REQUIRE(tree.printPostorder() == "Jack, Bob, Joe");
    }
}
TEST_CASE("Deletion Cases", "[Delete][BalancedTree]") {

    SECTION("No children (Leaf node)") {

        BalancedTree tree;
        tree.Insert("Adam", 12345678);
        tree.Insert("Bob", 23456789);
        tree.Insert("Charlie", 34567890);

        REQUIRE(tree.removeID(34567890) == true);
        REQUIRE(tree.searchID(34567890) == nullptr);
        REQUIRE(tree.searchID(12345678)->getHeight() == 1);
        REQUIRE(tree.searchID(23456789)->getHeight() == 2);
    }

    SECTION("1 child") {

        BalancedTree tree;
        tree.Insert("Adam", 12345678);
        tree.Insert("Bob", 23456789);
        tree.Insert("Charlie", 34567890);
        tree.Insert("Diana", 45678901);

        REQUIRE(tree.removeID(34567890) == true);
        REQUIRE(tree.searchID(34567890) == nullptr);


        REQUIRE(tree.searchID(12345678)->getHeight() == 1);
        REQUIRE(tree.searchID(23456789)->getHeight() == 2);
        REQUIRE(tree.searchID(45678901)->getHeight() == 1);
    }

    SECTION("2 children") {

        BalancedTree tree;
        tree.Insert("Adam", 12345678);
        tree.Insert("Bob", 23456789);
        tree.Insert("Charlie", 34567890);
        tree.Insert("Diana", 45678901);
        tree.Insert("Edward", 56789012);
        tree.Insert("Edward", 66789012);
        tree.Insert("Edward", 76789012);
        tree.Insert("Edward", 86789012);
        tree.Insert("Edward", 96789012);

        REQUIRE(tree.removeID(66789012) == true);
        REQUIRE(tree.searchID(66789012) == nullptr);

        REQUIRE(tree.searchID(12345678) != nullptr);
        REQUIRE(tree.searchID(23456789) != nullptr);
        REQUIRE(tree.searchID(45678901) != nullptr);
        REQUIRE(tree.searchID(56789012) != nullptr);
        REQUIRE(tree.searchID(76789012) != nullptr);
        REQUIRE(tree.searchID(86789012) != nullptr);
        REQUIRE(tree.searchID(96789012) != nullptr);

        REQUIRE(tree.searchID(12345678)->getHeight() == 1);
        REQUIRE(tree.searchID(23456789)->getHeight() == 2);
        REQUIRE(tree.searchID(45678901)->getHeight() == 4);
        REQUIRE(tree.searchID(56789012)->getHeight() == 1);
        REQUIRE(tree.searchID(76789012)->getHeight() == 3);
        REQUIRE(tree.searchID(86789012)->getHeight() == 2);
        REQUIRE(tree.searchID(96789012)->getHeight() == 1);
    }
}
TEST_CASE("BST Insert Large", "[flag]"){ // This is modified code from https://www.onlinegdb.com/Ih4XEhD80w
    BalancedTree inputTree;
    std::vector<int> expectedOutput, actualOutput;

    for(int i = 0; i < 100000; i++)
    {
        int randomInput = rand();
        if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
        {
            expectedOutput.push_back(randomInput);
            inputTree.Insert("name", randomInput);
        }
    }

    actualOutput = inputTree.inorderTester(actualOutput);
    REQUIRE(expectedOutput.size() == actualOutput.size());
    std::sort(expectedOutput.begin(), expectedOutput.end());
    REQUIRE(expectedOutput == actualOutput);

}


*/
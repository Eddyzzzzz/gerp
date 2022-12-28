/*
unit_tests.h
Duncan and Eddy
12/2/2022

CS 15 Proj4 Gerp
  
We unit tested all of our functions in HashTable and Gerp, including edge
cases and diff testing. We make all member variables public during testing
in order to make sure that the Hash Tables and vectors stored our data
perfectly, our tests have now be commented out. Because we are using linked
lists, a lot of our tests are very verbose in iterating through our LL chains
and LL ints of indicies, so testing was somewhat difficult, but it convinced
us that our Hashes worked correctly. 
*/

//void traverseTree(std::string dir_name);

#include <cassert>
#include <string>
#include <iostream>

//#include "stringProcessing.h"
#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"
#include "Gerp.h"



/*

************ GERP SEARCH UNIT TESTS ********************

void GerpQueryOneCaseSens() {
    std::ofstream outputStream("test_output1.txt");
    Gerp gerp("subdirs", "random_output_file.txt");

    gerp.query("Dog", true, outputStream);

    outputStream.close();

    std::ifstream inputStream("test_output1.txt");

    std::string line;
    std::getline(inputStream, line);
    assert(line == "/subdirs/folder1/folder4/text2.txt:1:The Dog");
}

void GerpQueryOneNonSens() {
    std::ofstream outputStream("test_output2.txt");
    Gerp gerp("subdirs", "random_output_file.txt");

    gerp.query("DOG", false, outputStream);

    outputStream.close();

    std::ifstream inputStream("test_output2.txt");

    std::string line;
    std::getline(inputStream, line);
    assert(line == "/subdirs/folder1/folder4/text2.txt:1:The Dog");
}

void GerpQueryNotFoundNotSens() {
    std::ofstream outputStream("test_output3.txt");
    Gerp gerp("subdirs", "random_output_file.txt");

    gerp.query("Duncan", false, outputStream);

    outputStream.close();

    std::ifstream inputStream("test_output3.txt");

    std::string line;
    std::getline(inputStream, line);
    assert(line == "Duncan Not Found.");
}

void GerpQueryNotFoundSens() {
    std::ofstream outputStream("test_output4.txt");
    Gerp gerp("subdirs", "random_output_file.txt");

    gerp.query("Duncan", true, outputStream);

    outputStream.close();

    std::ifstream inputStream("test_output4.txt");

    std::string line;
    std::getline(inputStream, line);
    assert(line == "Duncan Not Found. Try with @insensitive or @i.");
}


*********** GERP SETUP UNIT TESTS ************************

void GerpOneFile() {
    Gerp gerp("only_files");

    assert(gerp.lines[0] == "/only_files/cs15.txt:1:Duncan Eddy");

    bool found = false;
    for (int i = 0; i < gerp.caseSens.size; i++) {
        Bucket *curr = gerp.caseSens.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "Duncan") {
                std::list<int>::iterator it2;
                for (it2 = it->indicies.begin(); it2 != it->indicies.end(); 
                        ++it2) {
                    if (*it2 == 0) {
                        found = true;
                    }
                }
            }
        }
    }

    assert(found);

    bool found2 = false;
    for (int i = 0; i < gerp.lowerCase.size; i++) {
        Bucket *curr = gerp.lowerCase.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "eddy") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 0) {
                        found2 = true;
                    }
                }
            }
        }
    }

    assert(found2);
}

void GerpMoreFiles() {
    Gerp gerp("many_files");
    
    assert(gerp.lines[0] == "/many_files/eddy.txt:1:the boy");
    assert(gerp.lines[1] == "/many_files/eddy.txt:2:the girl the boy");
    assert(gerp.lines[2] == "/many_files/duncan.txt:1:the cat");
    assert(gerp.lines[3] == "/many_files/duncan.txt:2:the dog");

    bool found = false;
    for (int i = 0; i < gerp.caseSens.size; i++) {
        Bucket *curr = gerp.caseSens.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "dog") {
                std::list<int>::iterator it2;
                for (it2 = it->indicies.begin(); it2 != it->indicies.end(); 
                        ++it2) {
                    if (*it2 == 3) {
                        found = true;
                    }
                }
            }
        }
    }

    assert(found);

    bool found2 = false;
    for (int i = 0; i < gerp.lowerCase.size; i++) {
        Bucket *curr = gerp.lowerCase.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "girl") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 1) {
                        found2 = true;
                    }
                }
            }
        }
    }

    assert(found2);

    bool foundThe0 = false;
    bool foundThe1 = false;
    bool foundThe2 = false;
    bool foundThe3 = false;
    bool reset = false;
    for (int i = 0; i < gerp.lowerCase.size; i++) {
        Bucket *curr = gerp.lowerCase.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "the") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 0) {
                        foundThe0 = true;
                    }
                    if (*it2 == 1) {
                        foundThe1 = true;
                    }
                    if (*it2 == 2) {
                        foundThe2 = true;
                    }
                    if (*it2 == 3 and reset == true) {
                        assert("Found three twice" == ""); 
                    }
                    if (*it2 == 3 and reset == false) {
                        foundThe3 = true;
                        reset = true;
                    }
                }
            }
        }
    }

    assert(foundThe0);
    assert(foundThe1);
    assert(foundThe2);
    assert(foundThe3);

}

void GerpSubDirs() {
    Gerp gerp("subdirs");

    assert(gerp.lines[0] == "/subdirs/folder1/folder4/text2.txt:1:The Dog");
    assert(gerp.lines[1] == "/subdirs/folder1/folder4/text2.txt:2:the CAT");
    assert(gerp.lines[2] == "/subdirs/folder1/folder3/text1.txt:1:the Boy");
    assert(gerp.lines[3] == "/subdirs/folder1/folder3/text1.txt:2:The Girl");
    assert(gerp.lines[4] == "/subdirs/folder2/text0.txt:1:The cat");
}

void GerpSubDirsCase() {
    Gerp gerp("subdirs");

    assert(gerp.lines[0] == "/subdirs/folder1/folder4/text2.txt:1:The Dog");
    assert(gerp.lines[1] == "/subdirs/folder1/folder4/text2.txt:2:the CAT");
    assert(gerp.lines[2] == "/subdirs/folder1/folder3/text1.txt:1:the Boy");
    assert(gerp.lines[3] == "/subdirs/folder1/folder3/text1.txt:2:The Girl");
    assert(gerp.lines[4] == "/subdirs/folder2/text0.txt:1:The cat");

    bool foundthe0 = false;
    bool foundthe1 = false;
    for (int i = 0; i < gerp.caseSens.size; i++) {
        Bucket *curr = gerp.caseSens.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "the") {
                std::list<int>::iterator it2;
                for (it2 = it->indicies.begin(); it2 != it->indicies.end(); 
                        ++it2) {
                    if (*it2 == 1) {
                        foundthe0 = true;
                    }
                    if (*it2 == 2) {
                        foundthe1 = true;
                    }
                    if (*it2 == 0) {
                        assert("found a The we shouldn't have" == "");
                    }
                }
            }
        }
    }

    assert(foundthe0);
    assert(foundthe1);

    bool foundThe0 = false;
    bool foundThe1 = false;
    bool foundThe2 = false;
    bool foundThe3 = false;
    bool foundThe4 = false;
    for (int i = 0; i < gerp.lowerCase.size; i++) {
        Bucket *curr = gerp.lowerCase.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            if (it->word == "the") {
                std::list<int>::iterator it2;
                for (it2 = it->indicies.begin(); it2 != it->indicies.end(); 
                        ++it2) {
                    if (*it2 == 0) {
                        foundThe0 = true;
                    }
                    if (*it2 == 1) {
                        foundThe1 = true;
                    }
                    if (*it2 == 2) {
                        foundThe2 = true;
                    }
                    if (*it2 == 3) {
                        foundThe3 = true;
                    }
                    if (*it2 == 4) {
                        foundThe4 = true;
                    }
                }
            }
        }
    }

    assert(foundThe0);
    assert(foundThe1);
    assert(foundThe2);
    assert(foundThe3);
    assert(foundThe4);
}


************** HASH TABLE UNIT TESTS ***********************

void hashConstructor() {
    HashTable hashTable(100000);

    KeyValue newKV;
    newKV.word = "Duncan";
    newKV.indicies.push_back(5);

    hashTable.hash[99999]->chain.push_back(newKV);

    assert(hashTable.size == 100000);
}

void hashInsertSmall() {
    HashTable hashTable(100);

    hashTable.insert("Duncan", 5);

    bool found = false;
    for (int i = 0; i < hashTable.size; i++) {
        Bucket *curr = hashTable.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            // we put the incorrect name and indicies and it successfully 
            // didn't work
            if (it->word == "Duncan") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 5) {
                        found = true;
                    }
                }
            }
        }
    }

    assert(found);
}

void hashInsertTwoOfSameWord() {
    HashTable hashTable(100);

    hashTable.insert("Duncan", 5);
    hashTable.insert("Duncan", 6);

    bool found5 = false;
    bool found6 = false;
    for (int i = 0; i < hashTable.size; i++) {
        Bucket *curr = hashTable.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            // we put the incorrect name and indicies and it successfully 
            // didn't work
            if (it->word == "Duncan") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 5) {
                        found5 = true;
                    }
                    if (*it2 == 6) {
                        found6 = true;
                    }
                }
            }
        }
    }

    assert(found5);
    assert(found6);
}

void hashInsertCollision() {
    HashTable hashTable(1);

    hashTable.insert("Duncan", 5);
    hashTable.insert("Duncan", 6);
    hashTable.insert("Eddy", 6);

    bool found5 = false;
    bool found6 = false;
    bool found6Eddy = false;
    for (int i = 0; i < hashTable.size; i++) {
        Bucket *curr = hashTable.hash[i];
        std::list<KeyValue>::iterator it;
        for (it = curr->chain.begin(); it != curr->chain.end(); ++it) {
            // we put the incorrect name and indicies and it successfully 
            // didn't work
            if (it->word == "Duncan") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 5) {
                        found5 = true;
                    }
                    if (*it2 == 6) {
                        found6 = true;
                    }
                }
            }
            if (it->word == "Eddy") {
                std::list<int> indexList = it->indicies;
                std::list<int>::iterator it2;
                for (it2 = indexList.begin(); it2 != indexList.end(); ++it2) {
                    if (*it2 == 6) {
                        found6Eddy = true;
                    }
                }
            }
        }
    }

    assert(found5);
    assert(found6);
    assert(found6Eddy);
}

void getValuesSimple() {
    HashTable hashTable(100);

    hashTable.insert("Duncan", 5);

    std::list<int> indicies = hashTable.getValues("Duncan");

    bool found = false;

    std::list<int>::iterator it;
    for (it = indicies.begin(); it != indicies.end(); ++it) {
        if (*it == 5) {
            found = true;
        }
    }

    assert(found);
}

void getValuesTwo() {
    HashTable hashTable(100);

    hashTable.insert("Duncan", 5);
    hashTable.insert("Duncan", 6);

    std::list<int> indicies = hashTable.getValues("Duncan");

    bool found5 = false;
    bool found6 = false;

    std::list<int>::iterator it;
    for (it = indicies.begin(); it != indicies.end(); ++it) {
        if (*it == 5) {
            found5 = true;
        }
        if (*it == 6) {
            found6 = true;
        }
    }

    assert(found5);
    assert(found6);
}

// also tests the expand function! Still findable!
void getValuesCollision() {
    HashTable hashTable(1);

    hashTable.insert("Duncan", 5);
    hashTable.insert("Duncan", 6);
    hashTable.insert("Eddy", 6);

    std::list<int> indiciesDuncan = hashTable.getValues("Duncan");
    std::list<int> indiciesEddy = hashTable.getValues("Eddy");

    bool found5 = false;
    bool found6 = false;
    bool found6Eddy = false;

    std::list<int>::iterator it;
    for (it = indiciesDuncan.begin(); it != indiciesDuncan.end(); ++it) {
        if (*it == 5) {
            found5 = true;
        }
        if (*it == 6) {
            found6 = true;
        }
    }
    
    std::list<int>::iterator it2;
    for (it2 = indiciesEddy.begin(); it2 != indiciesEddy.end(); ++it2) {
        if (*it2 == 6) {
            found6Eddy = true;
        }
    }

    

    assert(found5);
    assert(found6);
    assert(found6Eddy);
    
}

void expandTest() {
    HashTable hashTable(4);

    hashTable.insert("Duncan", 5);
    hashTable.insert("Duncan", 6);
    hashTable.insert("Eddy", 6);

    assert(hashTable.size == 8);

    KeyValue newKV;
    newKV.word = "CS15";
    newKV.indicies.push_back(109);

    hashTable.hash[6]->chain.push_back(newKV);
}





********PHASE ONE UNIT TESTS*************

// traversing an empty directory
void traverseEmpty() {
    traverseTree("empty_folder");
}

// traversing only files
void traverseOnlyFiles() {
    traverseTree("only_files");
}

// traversing subdirectories
void traverseSubDirs() {
    traverseTree("subdirs");
}

// parsing empty string input
void parseEmpty() {
    assert(stripNonAlphaNum("") == "");
}

// parse single alphanum char
void parseSingleAlpha() {
    assert(stripNonAlphaNum("a") == "a");
}

// parse single non-alphanum char
void parseSingleNonAlpha() {
    assert(stripNonAlphaNum("$") == "");
}

// parse all alphanum char
void parseAllAlpha() {
    assert(stripNonAlphaNum("DuncanEddy") == "DuncanEddy");
}

// parse all non-alphanum char
void parseAllNonAlpha() {
    assert(stripNonAlphaNum("$$$$$$$$$$") == "");
}

// parse leading and trailing with no non-alphanum in middle
void parseNoMiddle() {
    assert(stripNonAlphaNum(" $ & DuncanEddy ()^%^ ") == "DuncanEddy");
}

// parse alphanum in middle
void parseNormal() {
    assert(stripNonAlphaNum("@##!!#!@!#COMP-15!!!!!!!") == "COMP-15");
}

*/
/*
Gerp.h
Duncan and Eddy
12/8/2022

CS15 Proj4 Gerp

Functions declarations of Gerp class, the only public function is the 
constructor which gets called by main.cpp with the command line arguments,
then two Hash Tables are created, one with case sensitive words and one
with all lowercase words. We also have a vector that has every line of
text that we might need to print to the output file.

*/

#ifndef _GERP_H_
#define _GERP_H_

#include <string>
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>


#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"

class Gerp
{
public:
    Gerp(std::string folderName, std::string outputFile);

private:
    std::vector<std::string> lines;
    
    // hash tables for both case-sensitive and case-nonsensitive searches
    HashTable caseSens;
    HashTable lowerCase;

    // set up the vector "lines" and hash tables for the searching later
    void Setup(std::string folderName);

    // traverses a tree, adding all lines to vector and words to hashtable
    void traverseTree(std::string dir_name);
    // helper function for traverseTree
    void recurseTraverse(DirNode *folder, std::string path);
    // strips preceding and trailing non-alphanumeric characters
    std::string stripNonAlphaNum(std::string input);
    // adds all lines of a file to vector and the words to the hashtables
    void ParseFile(std::string path);

    // adds the line and its words to the hash tables and vector
    void ParseLine(std::string path, std::string line, int lineNum);

    // searches for a word and prints out the lines it's on
    void query(std::string word, bool caseMatters, std::ofstream &output);

    // converts a string to lowercase
    std::string toLower(std::string word);

    // game loop asking for commands
    void gameLoop(std::ofstream &output);
};

#endif

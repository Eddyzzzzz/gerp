/*
Gerp.cpp
Duncan and Eddy
12/8/2022

CS15 Proj4 Gerp

Gerp.cpp implements the functions declared in Gerp.h by first setting
up the two different Hash Tables, traversing the directory file tree,
and then indexing each file and pulling the lines into our vector "Lines"
and each word into the two Hash Tables.
We then run our game loop, asking for user input of words to search for,
files to switch to, and when they want to quit.

*/

#include "Gerp.h"
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <cstdint>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>


#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"

// Constructor for gerp, takes in folderName, assembles HashTables and vector
// then runs loop for user to search up words
// opens and closes the output file stream
Gerp::Gerp(std::string folderName, std::string outputFile) : 
    caseSens(500000), lowerCase(500000) {

    // set everything up
    traverseTree(folderName);
    std::ofstream output;
    output.open(outputFile);

    // run the loop of commands
    gameLoop(output);

    output.close();
}

/*
    name:      gameLoop
    purpose:   run the command loop
    arguments: ofstream of output file
    returns:   none
    effects:   might change output if you use @f
 */
void Gerp::gameLoop(std::ofstream &output) {
    bool quit = false;
    while (not quit) {
        std::cout << "Query? ";

        std::string command;
        std::cin >> command;
        if (command == "@q" or command == "@quit" or std::cin.eof()) {
            quit = true;
            std::cout << "Goodbye! Thank you and have a nice day." 
                << std::endl;
        } else if (command == "@f") {
            output.close(); 
            std::string newFile;
            std::cin >> newFile;
            output.open(newFile);
        } else if (command == "@i" or command == "@insensitive") {
            std::string word;
            std::cin >> word;
            query(stripNonAlphaNum(word), false, output);
        } else {
            query(stripNonAlphaNum(command), true, output);
        }
    }
}


/*
    name:      traverseTree
    purpose:   traverses a tree, printing out full file paths of each file
    arguments: string name of the root directory
    returns:   none
    effects:   prints out every full file path in the directory
 */
void Gerp::traverseTree(std::string dir_name) {
    FSTree dir;
    try {
        dir = FSTree(dir_name);
    } catch (const std::runtime_error &e) {
        std::cerr << "Could not build index, exiting." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    DirNode *root = dir.getRoot();

    recurseTraverse(root, dir_name);

    dir.burnTree();
}

/*
    name:      recurseTraverse
    purpose:   recursive helper function to recurse through folders
    arguments: pointer to a DirNode
               string current path
    returns:   none
    effects:   setup all the files in all subdirectories
 */
void Gerp::recurseTraverse(DirNode *folder, std::string path) {
    // print out files in current folder
    for (int i = 0; i < folder->numFiles(); i++) {
        ParseFile(path + "/" + folder->getFile(i));
    }

    // recurse deeper
    for (int i = 0; i < folder->numSubDirs(); i++) {
        DirNode *subDir = folder->getSubDir(i);
        recurseTraverse(subDir, path + '/' + subDir->getName());
    }
}

/*
    name:      stripNonAlphaNum
    purpose:   removes all leading and trailing non-alphanumeric chars
    arguments: original string
    returns:   parsed string without leading/trailing non-alphanum chars
    effects:   none
 */
std::string Gerp::stripNonAlphaNum(std::string input) {

    // strip leading chars
    int i = 0;
    while ((not isalnum(input[i])) and (i < int(input.length()))) {
        i++;
    }

    int j = input.length() - 1;
    // strip following chars
    

    bool foundAlnum = false;
    while (j >= 0 and not foundAlnum) {
        if (not (isalnum(input[j]))) {
            j--;
        } else {
            foundAlnum = true;
        }
    }

    // in case it's a completely non-alphanumeric string
    if (j < i) {
        return "";
    }

    return input.substr(i, j - i + 1);
}

/*
    name:      ParseFile
    purpose:   adds all lines to vector and words to hashtables
    arguments: path of the file
    returns:   none
    effects:   adds lines to vector, inserts into HashTables
 */
void Gerp::ParseFile(std::string path) {    
    // open the file
    std::ifstream fileStream;
    fileStream.open(path);

    if (not fileStream.is_open()) {
        std::cerr << "File can't be opened. Path: " << path << std::endl;
    }

    // for each line
    std::string line;
    int lineNum = 1;
    while (std::getline(fileStream, line)) {

        ParseLine(path, line, lineNum);
        
        lineNum++;
    }
    
    fileStream.close();

}

/*
    name:      ParseLine
    purpose:   set up vector and hashes
    arguments: a string line to be added
                int the number of the line in the file
    returns:   the string in lowercase
    effects:   adds the line to the vector and the words to the hash
 */
void Gerp::ParseLine(std::string path, std::string line, int lineNum) {
    std::stringstream ss(line);
    // for each word
    std::string word = "";

    std::set<std::string> wordsInLine;

    while(not ss.eof()) {
        ss >> word;
        word = stripNonAlphaNum(word);

        wordsInLine.insert(word);
    }

    std::set<std::string>::iterator it;
    for (it = wordsInLine.begin(); it != wordsInLine.end(); ++it) {
        if (*it != "") {
            caseSens.insert(*it, lines.size());

            lowerCase.insert(toLower(*it), lines.size());
        }
    }
        
    // add to vector
    lines.push_back(path + ":" + std::to_string(lineNum) + ": " + line);
}

/*
    name:      toLower
    purpose:   converts a string to lowercase
    arguments: a string
    returns:   the string in lowercase
    effects:   none
 */
std::string Gerp::toLower(std::string word) {
    std::string lower = "";
    int wordLen = word.length();
    for (int i = 0; i < int(wordLen); i++) {
        lower += std::tolower(word[i]);
    }
    return lower;
}

/*
    name:      query
    purpose:   find all lines a word appears on
    arguments: the word to query for
               bool true if we want a case sensitive search, false if not
    returns:   none
    effects:   prints out all lines the word appears on
 */
void Gerp::query(std::string word, bool caseMatters, std::ofstream &output) {
    std::list<int> word_indicies;

    if (caseMatters) {
        word_indicies = caseSens.getValues(word);
        if (word_indicies.empty()){
            output << word << " Not Found. Try with @insensitive or @i." 
            << std::endl;
        }
    } else {
        word_indicies = lowerCase.getValues(toLower(word));
        if (word_indicies.empty()){
            output << word << " Not Found." << std::endl;
        }
    }



    std::list<int>::iterator it;
    for (it = word_indicies.begin(); it != word_indicies.end(); ++it) {
        output << lines[*it] << std::endl;
    }
    
}
/*
FSTreeTraversal.cpp
Duncan and Eddy
12/2/2022

CS15 Proj4 Gerp

Take the highest directory as a command line argument, and then print the 
full paths of all the files accessible from that directory. Recursively
find all files in all subdirectories of the provided directory.

*/

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdint>

#include "FSTree.h"
#include "DirNode.h"

// traverses a tree, printing out file paths
void traverseTree(std::string dir_name);
// helper function for traverseTree(std::string dir_name)
void recurseTraverse(DirNode *folder, std::string path);

// // command line input parsing main function
// int main(int argc, char *argv[]) {
//     // check if the command line is right
//     if (argc != 2) {
//         std::cerr << "Usage: ./treeTraversal DirectoryName" << std::endl;
//         exit(EXIT_FAILURE);
//     }

//     traverseTree(argv[1]);

//     return 0;
// }

/*
    name:      traverseTree
    purpose:   traverses a tree, printing out full file paths of each file
    arguments: string name of the root directory
    returns:   none
    effects:   prints out every full file path in the directory
 */
void traverseTree(std::string dir_name) {
    FSTree dir(dir_name);
    
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
    effects:   prints all of the FILES in the current folder
 */
void recurseTraverse(DirNode *folder, std::string path) {
    // print out files in current folder
    for (int i = 0; i < folder->numFiles(); i++) {
        std::cout << path << '/' << folder->getFile(i) << std::endl;
    }

    // recurse deeper
    for (int i = 0; i < folder->numSubDirs(); i++) {
        DirNode *subDir = folder->getSubDir(i);
        recurseTraverse(subDir, path + '/' + subDir->getName());
    }
}
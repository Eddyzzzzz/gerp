/*
main.cpp
Duncan and Eddy 
12/10/2022

CS 15 Proj4 gerp

main.cpp runs the gerp and checks if gerp is called in the right way,
passing command line arguments to the Gerp constructor. If the user types
in the wrong number of arguments, the program exits and tells them the 
proper gerp command usage.

*/

#include "Gerp.h"

#include <iostream>

int main(int argc, char *argv[]) {
    //check if the command is given correctly
    if (argc != 3) {
        std::cerr << "Usage: ./gerp inputDirectory outputFile" << std::endl;
        exit(EXIT_FAILURE);
    } else {
        Gerp gerp(argv[1], argv[2]);
    }
    return 0;
}
/*
Hash.cpp
Duncan and Eddy
12/3/2022

CS15 Proj4 Gerp

Description TODO

*/

#include <string>
#include <list>

#include "Hash.h"

/*
    name:      Hash Constructor
    purpose:   initializes the hash array
    arguments: number of buckets for the hash array to have
    returns:   none
    effects:   initializes an array with size numBuckets
 */
Hash::Hash(int numBuckets) {
    hash = new std::list<KeyValue>[numBuckets];
}

/*
    name:      Hash Destructor
    purpose:   frees memory associated with the Hash
    arguments: none
    returns:   none
    effects:   frees hash
 */
Hash::~Hash() {
    delete [] hash;
}

/*
    name:      insert
    purpose:   insert a word and the line it appears on into the hash
    arguments: string word
               int index the word is on
    returns:   none
    effects:   adds a KeyValue to the list in the right bucket
                calls expand function if load factor > 70%
 */
void Hash::insert(std::string word, int indexAppearing) {
    
}

/*
    name:      getValues
    purpose:   get all of the indicies of the lines containing the given word
    arguments: string word
    returns:   list of int indicies containing the given word
    effects:   none
 */
std::list<int> Hash::getValues(std::string word) {
    
}

/*
    name:      expand
    purpose:   expand the hashtable and then rehash it
    arguments: none
    returns:   none
    effects:   the size of the array doubles, all the elements are rehashed in 
               new buckets
 */
void Hash::expand() {

}
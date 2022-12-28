/*
HashTable.cpp
Duncan and Eddy
12/3/2022

CS15 Proj4 Gerp

Implements the Hash ADT using an array of buckets, which gives us constant
time access to each Bucket and the ability to control when the Hash expands
in order to keep the average constant time access and insertion.
Clients can insert a string as the key and an int as the value, which gets
added to a list that corresponds to each word. When the client gets the
values for a string, a list of integers is returned. 
*/

#include <string>
#include <list>
#include <iostream>

#include "HashTable.h"


/*
    name:      Hash Constructor
    purpose:   initializes the hash array
    arguments: number of buckets for the hash array to have
    returns:   none
    effects:   initializes an array with size numBuckets
 */
HashTable::HashTable(int numBuckets) {
    hash = new Bucket*[numBuckets];
    for (int i = 0; i < numBuckets; i++) {
        Bucket *b = new Bucket;
        hash[i] = b;
    }
    size = numBuckets;
    currElements = 0;
}

/*
    name:      Hash Destructor
    purpose:   frees memory associated with the Hash
    arguments: none
    returns:   none
    effects:   frees hash
 */
HashTable::~HashTable() {
    for (int i = 0; i < size; i++) {
        delete hash[i];
    }
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
void HashTable::insert(std::string inputWord, int indexAppearing) {

    Bucket *bucket = hash[getBucket(inputWord)];

    // iterate through the Bucket and see if the word appears
    std::list<KeyValue>::iterator it;
    for (it = bucket->chain.begin(); it != bucket->chain.end(); ++it) {
        if (it->word == inputWord) {
        // if yes, add the indexAppearing to the value list
            it->indicies.push_back(indexAppearing);
            return;
        }
    }

    // calculate load factor, update the currElements
    currElements++;
    // if it's over 70%, expand
    if (currElements / size > 0.7) {
        expand();
    }

    bucket = hash[getBucket(inputWord)];

    // if no, create a Key Value pair with word and indexAppearing and add it
    KeyValue newKV;
    newKV.word = inputWord;
    newKV.indicies.push_back(indexAppearing);
    bucket->chain.push_back(newKV);   
}

/*
    name:      getValues
    purpose:   get all of the indicies of the lines containing the given word
    arguments: string word
    returns:   list of int indicies containing the given word
    effects:   none
 */
std::list<int> HashTable::getValues(std::string inputWord) {
    Bucket *bucket = hash[getBucket(inputWord)];

    std::list<KeyValue>::iterator it;
    for (it = bucket->chain.begin(); it != bucket->chain.end(); ++it) {
        if (it->word == inputWord) {
            return it->indicies;
        }
    }
    std::list<int> emptyList;
    return emptyList;
}

/*
    name:      expand
    purpose:   expand the hashtable and then rehash it
    arguments: none
    returns:   none
    effects:   the size of the array doubles, all the elements are rehashed in 
               new buckets
 */
void HashTable::expand() {

    std::cout << "expanding now" << std::endl;

    Bucket** oldHash = hash;
    
    size *= 2;

    hash = new Bucket*[size];
    for (int i = 0; i < size; i++) {
        Bucket *b = new Bucket;
        hash[i] = b;
    }

    for (int i = 0; i < (size / 2); i++) {
        std::list<KeyValue>::iterator it;
        for (it = oldHash[i]->chain.begin(); it != oldHash[i]->chain.end(); 
                ++it) {
            // add the KeyValue object to the new bucket
            hash[getBucket(it->word)]->chain.push_back(*it);
        }
    }

    for (int i = 0; i < (size / 2); i++) {
        delete oldHash[i];
    }
    delete [] oldHash;
}

/*
    name:      getBucket
    purpose:   gets the bucket the word goes in
    arguments: the string word to get the bucket of
    returns:   the index (int) of the bucket to place the word in
    effects:   none
 */
int HashTable::getBucket(std::string word) {
    std::size_t hashValue = std::hash<std::string>{}(word);
    return hashValue % size;
}

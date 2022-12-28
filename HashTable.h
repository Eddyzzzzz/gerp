/*
HashTable.h
Duncan and Eddy
12/3/2022

Declaration of HashTable class. Hashtable is implemented by an array of 
Buckets, and each bucket contains a KeyValue type list. KeyValue has two 
elements -- a string word and a list of int indicies that represent the 
lines the word appears.

*/

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <string>
#include <list>


struct KeyValue {
    std::string word;
    std::list<int> indicies;
};

struct Bucket {
    std::list<KeyValue> chain;
};

class HashTable
{
public:
    HashTable(int numBuckets);
    ~HashTable();
    
    // insert a word and the line it appears on into the hash
    void insert(std::string inputWord, int indexAppearing);

    // get all of the indicies of the lines containing the given word
    std::list<int> getValues(std::string inputWord);

// TODO UNCOMMENT PRIVATE
// private:
    // the hashtable -- implemented by an array of buckets
    Bucket** hash;

    double currElements;
    int size;

    // expand the hash and rehash all of the values
    void expand();

    // return the index of the bucket to place the word in
    int getBucket(std::string word);

};

#endif

/*
Hash.h
Duncan and Eddy
12/3/2022

CS15 Proj4 Gerp

Description TODO

*/

#ifndef _HASH_H_
#define _HASH_H_

#include <string>
#include <list>

struct KeyValue {
    std::string word;
    std::list<int> indicies;
};

class Hash 
{
public:
    Hash(int numBuckets);
    ~Hash();
    
    // insert a word and the line it appears on into the hash
    void insert(std::string word, int indexAppearing);

    // get all of the indicies of the lines containing the given word
    std::list<int> getValues(std::string word);

//private:
    // the hashtable -- implemented by an array with lists for chaining
    std::list<KeyValue> *hash;

    // expand the hash and rehash all of the values
    void expand();

};

#endif rehash all of the values
    void expand();

};

#endif
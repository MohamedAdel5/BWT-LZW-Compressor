
#ifndef ENWIK8_BWT_H
#define ENWIK8_BWT_H

#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include <iterator>
#include<list>
#include<fstream>
#include "globalConfig.h"
#include "FileManager.h"


using namespace std;

class Bwt
{
private:
    //int compareLexicographically(const void* firstPermutation, const void* secondPermutation);
public:
    static vector<uint8>* text;
    static uint32 lastIndex;
    uint32 chunkIndex;

    Bwt(vector<uint8>* txt, uint32 textLength, uint32 chunkIndex);
    Bwt();
    vector<uint8> encode(uint32& originalIndex);
    void decode(vector<uint8>& bwtVector, uint32 originalIndex, char* outFileName);

    ~Bwt();
};


#endif //ENWIK8_BWT_H

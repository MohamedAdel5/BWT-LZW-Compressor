

#ifndef ENWIK8_LZW_H
#define ENWIK8_LZW_H


#include<vector>
#include <unordered_map>
#include<string>
#include<iostream>
#include "globalConfig.h"

using namespace std;

class Lzw
{
    void addStringToCharactersDict(string s, vector<uint8>& charactersDict);
public:
    Lzw();
    void encode(vector<uint8>& inVector, vector<uint32>& outVector);
    void decode(vector<uint32>& inVector, vector<uint8>& outVector);
    ~Lzw();
};

#endif //ENWIK8_LZW_H

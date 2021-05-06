

#ifndef ENWIK8_FILEMANAGER_H
#define ENWIK8_FILEMANAGER_H

#include <vector>
#include <fstream>
#include <iostream>
#include "globalConfig.h"

using namespace std;

class FileManager
{
public:
    FileManager();
    void readFile(char* fileName, vector<uint8>& readVector, uint32 seek, uint32 count);
    void readFile(char* fileName, vector<uint32>& readVector, uint8 bytesNum, uint32 vectorStart, uint32 vectorLength);
    void writeFile(char* fileName, vector<uint8>& outVector);
    void writeFile(char* fileName, vector<uint32>& ouVector, uint8 bytesNum);
    void writeFile(char* fileName, vector<uint16>& outVector);
    void writeFile(char* fileName, string& outString);
    void clearFile(char* fileName);
    void writeInt(char* fileName, uint32 number);
    void readInt(char* fileName, uint32& number, uint32 seek);


    ~FileManager();
};




#endif //ENWIK8_FILEMANAGER_H

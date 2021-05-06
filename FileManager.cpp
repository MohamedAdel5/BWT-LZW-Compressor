#include "FileManager.h"

FileManager::FileManager()
{
}

void FileManager::readFile(char* fileName, vector<uint8>& readVector, uint32 seek, uint32 count)
{

    ifstream ifs(fileName, ios::in | ios::binary);
    unsigned char temp;
    unsigned long long i = 0;
    ifs.seekg(seek, ifs.beg);
    while (i < count) {
        ifs >> noskipws >> temp;
        readVector[i++] = temp;
    }
    ifs.close();
}

void FileManager::readFile(char* fileName, vector<uint32>& readVector, uint8 bytesNum, uint32 vectorStart, uint32 vectorLength)
{

    ifstream ifs(fileName, ios::in | ios::binary);

    ifs.seekg(vectorStart*bytesNum, ifs.beg);
    unsigned long long i = 0;
    while (ifs.tellg() < bytesNum*(vectorStart + vectorLength))
    {
        readVector.push_back(int());
        ifs.read((char*)&readVector[i], bytesNum);
        ++i;
    }

    ifs.close();
}
void FileManager::writeFile(char* fileName, vector<unsigned char>& outVector)
{
    ofstream of(fileName, ios::app | ios::binary);
    of.write((const char*)&outVector[0], outVector.size());
    of.close();
}
void FileManager::writeFile(char* fileName, vector<uint32>& outVector, uint8 bytesNum)
{

    ofstream ofs(fileName, ios::app | ios::binary);
    if(bytesNum == 4)
        ofs.write((char*)&outVector[0], (outVector.size()) * sizeof(uint32));
    else
        for (uint32 i = 0; i < outVector.size(); ++i)
        {
            ofs.write((const char*)&outVector[i], 3);
        }
    ofs.close();
}
void FileManager::writeFile(char* fileName, vector<uint16>& outVector)
{

    ofstream ofs(fileName, ios::out | ios::binary);
    ofs.write((char*)&outVector[0], outVector.size() * sizeof(uint16));
    ofs.close();
}
void FileManager::writeFile(char* fileName, string& outString)
{
    ofstream ofs(fileName, ios::app | ios::binary);
    ofs.write(&outString[0], outString.size()-1);
    ofs.close();
}
void FileManager::clearFile(char* fileName)
{
    ofstream ofs;
    ofs.open(fileName, ofstream::out | ofstream::trunc);
    ofs.close();
}
void FileManager::writeInt(char* fileName, uint32 number)
{
    ofstream ofs(fileName, ios::binary | ios::app);
    ofs.write((char*)&number, sizeof(number));
    ofs.close();
}
void FileManager::readInt(char* fileName, uint32& number, uint32 seek)
{
    ifstream ifs(fileName, ios::binary);
    ifs.seekg(seek, ifs.beg);
    ifs.read((char*)&number, sizeof(number));
    ifs.close();
}
FileManager::~FileManager()
{
}

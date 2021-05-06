#include "Lzw.h"

void Lzw::addStringToCharactersDict(string s, vector<uint8>& charactersDict)
{
    for (uint32 i = 0; i < s.length(); ++i)
    {
        charactersDict.push_back(s[i]);
    }
}

Lzw::Lzw()
{
}

void Lzw::encode(vector<uint8>& inVector, vector<uint32>& outVector)
{
    //Build the dictionary with initial values ascii characters
    unordered_map<string, uint32> codesDict;
    for (uint16 i = 0; i < 256; i++) {
        codesDict[string(1,char(i))] = i;
    }

    uint32 currentCharacterIndex = 0;
    string stringThatMatchesAnyOfTheDictEnteries = "";
    uint32 nextIndexInDict = 256;
    while (currentCharacterIndex < inVector.size())
    {
        string currentCharacter = string(1, inVector[currentCharacterIndex]);
        //Check if the string exists in the dictionary
        if (codesDict.find(stringThatMatchesAnyOfTheDictEnteries + currentCharacter) != codesDict.end())
        {
            stringThatMatchesAnyOfTheDictEnteries += currentCharacter;
            ++currentCharacterIndex;
        }
        else
        {
            codesDict[stringThatMatchesAnyOfTheDictEnteries + currentCharacter] = nextIndexInDict;
            ++nextIndexInDict;
            outVector.push_back(codesDict[stringThatMatchesAnyOfTheDictEnteries]);
            stringThatMatchesAnyOfTheDictEnteries = "";
            if (codesDict.size() > 1000000)
            {
                codesDict.clear();
                for (uint16 i = 0; i < 256; i++) {
                    codesDict[string(1, char(i))] = i;
                }
            }
        }
    }
    if (codesDict.find(stringThatMatchesAnyOfTheDictEnteries) != codesDict.end())
    {
        outVector.push_back(codesDict[stringThatMatchesAnyOfTheDictEnteries]);
    }

}

void Lzw::decode(vector<uint32>& indexesVector, vector<uint8>& outVector)
{
    //Build the dictionary with initial values ascii characters
    unordered_map<uint32, string> codesDict;
    for (uint16 i = 0; i < 256; i++) codesDict[i] = char(i);

    uint32 indexToDecode = indexesVector[0];
    string decodedString = codesDict[indexToDecode];
    addStringToCharactersDict(decodedString, outVector);


    uint32 nextIndexInDict = 256;
    for (uint32 i = 1; i < indexesVector.size(); i++) {
        string lastDecoded = codesDict[indexesVector[i-1]];

        if (codesDict.find(indexesVector[i]) != codesDict.end())
        {
            decodedString = codesDict[indexesVector[i]];
            lastDecoded += decodedString[0];
        }
        else
        {
            lastDecoded += lastDecoded[0];
            decodedString = lastDecoded;
        }

        codesDict[nextIndexInDict++] = lastDecoded;
        addStringToCharactersDict(decodedString, outVector);

        if (codesDict.size() > 1000000)
        {
            codesDict.clear();
            for (uint16 i = 0; i < 256; i++) codesDict[i] = char(i);
        }
    }
}

Lzw::~Lzw()
{
}

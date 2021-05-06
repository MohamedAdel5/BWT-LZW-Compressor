
#include <iostream>
#include <vector>
#include "FileManager.h"
#include "Bwt.h"
#include "Lzw.h"
#include <cmath>
#include <chrono>
#include "globalConfig.h"

using namespace std;



//void printVector(vector<uint8> &inputVector);
//void printVector(vector<uint32> &vec);
//void printMap(map<uint8, uint32> map);



int main()
{
    char outFileName1[] = "out.txt";
    char outFileName2[] = "originalIndexes.txt";
    char outFileName3[] = "vectorLengths.txt";


    char decodedFileName[] = "restoredFile.txt";
    char inputFileName[] = INPUT_FILE_NAME;
    FileManager fm;

    cout << endl << endl;
    cout << "THE FILE SIZE (SPECIFIED IN globalConfig.h) IS: " << FILE_SIZE << " Bytes" << endl << endl;
    cout << "THE FILE IS DIVIDED INTO " << FILE_SIZE/FILE_CHUNK << " CHUNKS (Chunk Size is specified in globalConfig.h)" << endl << endl;
    cout << "This Program Encodes 'enwik8.txt' file then decodes it in 'restoredFile.txt'" << endl << endl;
    cout << "Three output files will be generated:\n 'out.txt': for storing the encoded data.\n"
            "'vectorIndexes.txt': for storing chunks lengths.\n"
            " 'originalIndexes.txt': for storing the original indexes for BWT" << endl;

    cout << endl << "---------------------------------BWT & LZW ENCODING---------------------------" << endl;
    fm.clearFile(outFileName1);
    fm.clearFile(outFileName2);
    fm.clearFile(outFileName3);
    fm.clearFile(decodedFileName);

    uint32 encodedFileSize = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (uint8 i = 0; i < FILE_SIZE / FILE_CHUNK; ++i)
    {
        //inputVector
        vector<uint8> inputVector(FILE_CHUNK + 1);
        fm.readFile(inputFileName, inputVector, i*FILE_CHUNK, FILE_CHUNK);
        inputVector[FILE_CHUNK] = '\0';

        cout << "Reading Chunk " << to_string(i+1) <<" Done" << endl;
        cout << "Performing BWT transform..." << endl;

        Bwt bwt(&inputVector, inputVector.size(), i);
        uint32 originalIndex = 0;
        vector<uint8> bwtVector = bwt.encode(originalIndex);

        cout << "BWT Transform Done" << endl;
        cout << "Performing LZW encoding..." << endl;

        Lzw lzw;
        vector<uint32> indexesVector;
        lzw.encode(bwtVector, indexesVector);

        cout << "LZW Encoding Done " << endl;
        cout << "Encoded Vector Length " << indexesVector.size() << endl;
        encodedFileSize += indexesVector.size()*3;
        cout << "Writing Encoded Chunk To File..." << endl;

        fm.writeFile(outFileName1, indexesVector, 3);
        //printVector(indexesVector);
        fm.writeInt(outFileName2, originalIndex);
        fm.writeInt(outFileName3, indexesVector.size());


        cout << "Writing Encoded Chunk To File Done" << endl << "---------" << endl;

    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    cout <<endl<< "----------------------------BWT & LZW ENCODING FINISHED-----------------------" << endl;




    cout << endl<< "---------------------------------BWT & LZW DECODING---------------------------" << endl;
    uint32 vectorStart = 0;
    uint32 vectorLength = 0;

    for (uint8 i = 0; i < FILE_SIZE / FILE_CHUNK; ++i)
    {
        vector<uint32> indexesVector;
        vector<uint8> decodedLzwVector;
        fm.readInt(outFileName3, vectorLength, i * sizeof(uint32));
        fm.readFile(outFileName1, indexesVector, 3, vectorStart, vectorLength);
        vectorStart += vectorLength;
        cout << "Reading Encoded Chunk " << to_string(i+1) << " Done" << endl;
        cout << "Chunk Length: " << indexesVector.size() << endl;

        cout << "Performing LZW decoding..." << endl;
        Lzw lzw;
        lzw.decode(indexesVector, decodedLzwVector);
        cout << "LZW Decoding Done" << endl;

        uint32 originalIndex = 0;
        fm.readInt(outFileName2, originalIndex, i * sizeof(uint32));

        cout << "Performing BWT inverse transformation..." << endl;
        Bwt bwt;
        bwt.decode(decodedLzwVector, originalIndex, decodedFileName);

        cout << "BWT Decoding Done" << endl << "---------" << endl;

    }
    cout <<endl<< "----------------------------BWT & LZW DECODING FINISHED-----------------------" << endl;
    cout << "File Decoding Done" << endl;


    cout<< endl << "Encoding Time: " << elapsed.count() << "s" << endl;

    uint32 twoPowerThirty = pow(2,20);
    cout << "Encoded File Size: " << encodedFileSize  << " Bytes ~= " << (double)encodedFileSize/(twoPowerThirty) << " MB" << endl;
    cout << "Compression Ratio: " << (double)FILE_SIZE/encodedFileSize << endl;

    cout << "Press Enter To Exit." << endl;
    getchar();

}

//void printVector(vector<uint8> &vec) {
//    for (uint32 i = 0; i < vec.size(); ++i)
//    {
//        cout << vec[i] ;
//    }
//    cout << endl << "Vector TOTAL SIZE: " << vec.size() << endl;
//}
//
//void printVector(vector<uint32> &vec) {
//    for (uint32 i = 0; i < vec.size(); ++i)
//    {
//        cout << vec[i] << " ";
//    }
//    cout << endl << "Vector TOTAL SIZE: " << vec.size() << endl;
//}

//void printMap(map<uint8, uint32> mp) {
//    map<uint8,uint32>::iterator it;
//
//    for (it = mp.begin(); it != mp.end(); it++)
//    {
//        cout << (char)it->first << ": " << it->second << endl;
//    }
//    cout << "Map TOTAL SIZE: " << mp.size() << endl;
//}










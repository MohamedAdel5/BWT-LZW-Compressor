#include "Bwt.h"
vector<uint8>* Bwt::text = NULL;
uint32 Bwt::lastIndex = 0;

//template<class T>
//int compareLexicographically(const void* firstPermutationIndex, const void* secondPermutationIndex)
//{
//    T fp = *(T*)firstPermutationIndex;
//    T sp = *(T*)secondPermutationIndex;
//
//    T i = fp;
//    T j = sp;
//    while (i <= Bwt::lastIndex && j <= Bwt::lastIndex) {
//        if ((*Bwt::text)[i] == (*Bwt::text)[j]) {
//            ++i;
//            ++j;
//        }
//        else if ((*Bwt::text)[i] < (*Bwt::text)[j]) return -1;
//        else {
//            return 1;
//        }
//    }
//    return 0;
//}


Bwt::Bwt(vector<uint8> *txt, uint32 textLength, uint32 chnkIndx)
{

    text = txt;
    lastIndex = textLength - 1;
    chunkIndex = chnkIndx;
}
Bwt::Bwt()
{
}

//int compareRanks(const void* f, const void* s)
//{
//    vector<uint32>* first = (vector<uint32>*)f;
//    vector<uint32>* second = (vector<uint32>*)s;
//
//    return ((*first)[0] == (*second)[0]) ? ((*first)[1] < (*second)[1] ? -1 : 1) :
//           ((*first)[0] <  (*second)[0] ? -1 : 1);
//}

int compareRanks(vector<uint32>& first, vector<uint32>& second)
{
    return (first[0] == second[0]) ? (first[1] < second[1] ? 1 : 0) :
           (first[0] <  second[0] ? 1 : 0);
}

vector<uint8> Bwt::encode(uint32& originalIndex)
{

    const uint32 textLength = lastIndex + 1;

    //vector<uint32> suffixVector(textLength);
    //for (int i = 0; i < textLength; i++) {
    //	suffixVector[i] = i;
    //}
    //qsort(&suffixVector[0], suffixVector.size(), sizeof(uint32), compareLexicographically<uint32>);

    vector<vector<uint32>> firstSuffixesVector(textLength);


    for (uint32 i = 0; i < textLength; i++)
    {
        firstSuffixesVector[i] = vector<uint32>(3);
        firstSuffixesVector[i][2] = i;
        firstSuffixesVector[i][0] = (*text)[i];
        firstSuffixesVector[i][1] = ((i + 1) < textLength) ? ((*text)[i + 1]) : -1;

    }

    vector<uint8>().swap((*text));
//	cout << "Now text capacity: "  << (*text).capacity() << endl;
//    qsort(&firstSuffixesVector[0], firstSuffixesVector.size(),24, compareRanks);
    sort(firstSuffixesVector.begin(), firstSuffixesVector.end(), compareRanks);



    for (uint32 l = 4; l < 2 * textLength; l = l * 2)
    {
        vector<uint32> indexes(textLength);
        int rank = 0;
        int lastRank = firstSuffixesVector[0][0];
        firstSuffixesVector[0][0] = rank;
        indexes[firstSuffixesVector[0][2]] = 0;

        for (uint32 i = 1; i < textLength; i++)
        {
            if (firstSuffixesVector[i][0] == lastRank &&
                firstSuffixesVector[i][1] == firstSuffixesVector[i - 1][1])
            {
                lastRank = firstSuffixesVector[i][0];
                firstSuffixesVector[i][0] = rank;
            }
            else
            {
                lastRank = firstSuffixesVector[i][0];
                firstSuffixesVector[i][0] = ++rank;
            }
            indexes[firstSuffixesVector[i][2]] = i;
        }

        for (uint32 i = 0; i < textLength; i++)
        {
            uint32 next = firstSuffixesVector[i][2] + l / 2;
            firstSuffixesVector[i][1] = (next < textLength) ?
                                        firstSuffixesVector[indexes[next]][0] : -1;
        }

        vector<uint32>().swap(indexes);
//		cout << "Now indexes capacity: "  << indexes.capacity() << endl;
		
//        qsort(&firstSuffixesVector[0], firstSuffixesVector.size(),24, compareRanks);
        sort(firstSuffixesVector.begin(), firstSuffixesVector.end(), compareRanks);
    }


//    uint32 *suffixVector = new uint32[textLength];
//    for (uint32 i = 0; i < textLength; i++)
//        suffixVector[i] = firstSuffixesVector[i][2];

    FileManager fm;
    (*text).reserve(FILE_CHUNK + 1);
    string fileName = INPUT_FILE_NAME;
    fm.readFile((char*)fileName.c_str(), (*text), chunkIndex*FILE_CHUNK, FILE_CHUNK);
    (*text)[FILE_CHUNK] = '\0';

    vector<uint8>  bwtVector(textLength);
    for (uint32 i = 0; i < textLength; i++) {
        int indexInText = firstSuffixesVector[i][2] - 1;
        if (indexInText < 0) indexInText = indexInText + textLength;
        bwtVector[i] = (*text)[indexInText];
        if (firstSuffixesVector[i][2] == 0) originalIndex = i;
    }

    return bwtVector;
}
void Bwt::decode(vector<uint8>& bwtVector, uint32 originalIndex, char* outFileName) {
    uint32 bwtSize = bwtVector.size();
    vector<uint8> sortedBwt(bwtVector);
    vector<uint32> rightShiftedVector(bwtSize);
    sort(sortedBwt.begin(), sortedBwt.end());

    vector<list<uint32>> linkedLists(256);
    vector< list<uint32>::iterator> linkedListsHeads(256);

    for (uint32 i = 0; i < bwtSize; ++i) {
        linkedLists[bwtVector[i]].push_back(i);
    }
    for (short i = 0; i < 256; ++i) {
        linkedListsHeads[i] = linkedLists[i].begin();
    }

    for (uint32 i = 0; i < bwtSize; i++) {
        rightShiftedVector[i] = *linkedListsHeads[sortedBwt[i]];
        ++linkedListsHeads[sortedBwt[i]];
    }

    ofstream of(outFileName, ios::app | ios::binary);
    for (uint32 i = 0; i < bwtSize-1; ++i) {
        originalIndex = rightShiftedVector[originalIndex];
        of << noskipws << (uint8)bwtVector[originalIndex];
    }

}


Bwt::~Bwt()
{
}

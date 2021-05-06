
#ifndef ENWIK8_GLOBALCONFIG_H
#define ENWIK8_GLOBALCONFIG_H

#define TEST 1
#define PRODUCTION 0
#define ENVIRONMENT PRODUCTION





#if ENVIRONMENT == TEST
//4000 - 1000 // 69 - 69
#define FILE_SIZE 1000000
#define FILE_CHUNK 250000
#define INPUT_FILE_NAME "enwik8.txt"

#elif ENVIRONMENT == PRODUCTION

#define FILE_SIZE 100000000
#define FILE_CHUNK 1000000
#define INPUT_FILE_NAME "enwik8.txt"


#endif
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#endif //ENWIK8_GLOBALCONFIG_H

#ifndef DEF_DATAS
#define DEF_DATAS

#include <bitset>
#include <vector>
#include "std.h"

extern int Plaintext[100][BLOC_LENGTH];
extern int Ciphertext[100][BLOC_LENGTH];

std::vector<std::bitset<BLOC_LENGTH>> bitsetFromArray(int texts[][BLOC_LENGTH]);

#endif

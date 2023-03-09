#include "svdpi.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

extern "C" void cfunc(/** output */ svBitVecVal res[10])
{
    for(int i = 0; i<10;++i){
        res[i] = i;
    }
}

extern "C" void put_array(/** output */ svOpenArrayHandle arr)
{
    for(int i = svRight(arr, 1); i<=svLeft(arr, 1); ++i){
        *(uint8_t*)(svGetArrElemPtr1(arr, i)) = rand();
    }
}

extern "C" void get_array(/** input */ const svOpenArrayHandle arr)
{
    for(int i = svRight(arr, 1); i<=svLeft(arr, 1); ++i){
        printf("\t%d", *(unsigned char*)(svGetArrElemPtr1(arr, i)));
    }
    cout << endl;
}
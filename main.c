#include<immintrin.h>
#include<stdint.h>
#include<stdio.h>

#define align __attribute__ ((aligned (16)))
#if !defined (ALIGN16)
    #if defined (__GNUC__)
        #define ALIGN16 __attribute__ ((aligned (16)))
    #else
        #define ALIGN16 __declspec (align (16))
    #endif
#endif

#include"FieldAdd.h"
#include"reduce.h"
#include"constantMult.h"
#include"FieldMult.h"

void printBytes(uint64_t *data, int num){
    for (int i=num-1; i>=0; i--)
        printf("%016lx ",data[i]);
    printf("\n");
}

int main()
{
    //First pair of numbers
    ALIGN16 uint64_t u[4] = {0x0706050403020100, 0x0f0e0d0c0b0a0908, 0x1716151413121110, 0x001e1d1c1b1a1918};
    //ALIGN16 uint64_t m[4] = {0x0101010101010101, 0x0101010101010101, 0x0101010101010101, 0x0101010101010112};
    ALIGN16 uint64_t m[4] = {0x0706050403020100, 0x0f0e0d0c0b0a0908, 0x1716151413121110, 0x001e1d1c1b1a1918};
    //Second pair of numbers
    ALIGN16 uint64_t v[4] = {0x0706050403020100, 0x0f0e0d0c0b0a0908, 0x0706050403020100, 0x070e0d0c0b0a0908};
    ALIGN16 uint64_t n[4] = {0x0706050403020100, 0x0f0e0d0c0b0a0908, 0x0706050403020100, 0x070e0d0c0b0a0908};
    
    printf("\nFirst pair of numbers:\nu: ");
    printBytes(u,4);
    printf("m: ");
    printBytes(m,4);
    
    printf("\nSecond pair of numbers:\nv: ");
    printBytes(v,4);
    printf("n: ");
    printBytes(n,4);
    
    //Field Addition
    ALIGN16 uint64_t add1[4], add2[4];
    AddSub(u, m, v, n, add1, add2);
    
    printf("\nField Addition:\n");
    printf("u.m: ");
    printBytes(add1, 4);
    printf("v.n: ");
    printBytes(add2, 4);
    
    //Multiplication By Small Constant
    uint64_t c = 0x0101010101010101;
    ALIGN16 uint64_t cmul1[4], cmul2[4];
    CnstMult(u, v, c, cmul1, cmul2);
    
    printf("\nMultiplication by Small Constant:\n");
    printf("c.u: ");
    printBytes(cmul1, 4);
    printf("c.v: ");
    printBytes(cmul2, 4);
    
    //field Multiplication
    ALIGN16 uint64_t mult1[4], mult2[4];
    reduction(u, m, v, n, mult1, mult2);
    
    printf("\nField Multiplication:\n");
    printf("u.m: ");
    printBytes(mult1, 4);
    printf("v.n: ");
    printBytes(mult2, 4);
    
    
    return 0;
}    
     

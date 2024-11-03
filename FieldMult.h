
void reduction(uint64_t *u, uint64_t *m, uint64_t *v, uint64_t *n, uint64_t *res1, uint64_t *res2){
    //inserting multiplicands into four different registers
    __m256i multiplicand0 = _mm256_setzero_si256();
    multiplicand0 = _mm256_insert_epi64(multiplicand0, u[0], 0);
    multiplicand0 = _mm256_insert_epi64(multiplicand0, v[0], 2);
    
    __m256i multiplicand1 = _mm256_setzero_si256();
    multiplicand1 = _mm256_insert_epi64(multiplicand1, u[1], 0);
    multiplicand1 = _mm256_insert_epi64(multiplicand1, v[1], 2);
    
    __m256i multiplicand2 = _mm256_setzero_si256();
    multiplicand2 = _mm256_insert_epi64(multiplicand2, u[2], 0);
    multiplicand2 = _mm256_insert_epi64(multiplicand2, v[2], 2);
    
    __m256i multiplicand3 = _mm256_setzero_si256();
    multiplicand3 = _mm256_insert_epi64(multiplicand3, u[3], 0);
    multiplicand3 = _mm256_insert_epi64(multiplicand3, v[3], 2);
    
    //inserting multiplicands into four different registers
    __m256i multiplier0 = _mm256_setzero_si256();
    multiplier0 = _mm256_insert_epi64(multiplier0, m[0], 0);
    multiplier0 = _mm256_insert_epi64(multiplier0, n[0], 2);
    
    __m256i multiplier1 = _mm256_setzero_si256();
    multiplier1 = _mm256_insert_epi64(multiplier1, m[1], 0);
    multiplier1 = _mm256_insert_epi64(multiplier1, n[1], 2);
    
    __m256i multiplier2 = _mm256_setzero_si256();
    multiplier2 = _mm256_insert_epi64(multiplier2, m[2], 0);
    multiplier2 = _mm256_insert_epi64(multiplier2, n[2], 2);
    
    __m256i multiplier3 = _mm256_setzero_si256();
    multiplier3 = _mm256_insert_epi64(multiplier3, m[3], 0);
    multiplier3 = _mm256_insert_epi64(multiplier3, n[3], 2);
   
    __m256i temp1, temp2, temp3 ,temp4, temp5, temp6, temp7, temp8, temp9, temp10;
    temp1 = _mm256_clmulepi64_epi128(multiplicand0, multiplier0, 0x00);	// v0n0 : u0m0
    temp2 = _mm256_clmulepi64_epi128(multiplicand1, multiplier1, 0x00); // v1n1 : u1m1
    temp3 = _mm256_clmulepi64_epi128(multiplicand2, multiplier2, 0x00); // v2n2 : u2m2
    temp4 = _mm256_clmulepi64_epi128(multiplicand3, multiplier3, 0x00); // v3n3 : u3m3
     
    __m256i TEMP1 = _mm256_xor_si256(multiplicand0, multiplicand1); // 0 : (v0+v1) : 0 : (u0+u1)
    __m256i TEMP2 = _mm256_xor_si256(multiplicand2, multiplicand3); // 0 : (v2+v3) : 0 : (u2+u3)	
    __m256i TEMP3 = _mm256_xor_si256(multiplier0, multiplier1);	// 0 : (n0+n1) : 0 : (m0+m1)
    __m256i TEMP4 = _mm256_xor_si256(multiplier2, multiplier3); // 0 : (n2+n3) : 0 : (m2+m3)
    
    __m256i TEMP5 = _mm256_xor_si256(multiplicand0, multiplicand2); // 0 : (v0+v2) : 0 : (u0+u2)
    __m256i TEMP6 = _mm256_xor_si256(multiplicand1, multiplicand3); // 0 : (v1+v3) : 0 : (u1+u3)
    __m256i TEMP7 = _mm256_xor_si256(multiplier0, multiplier2); // 0 : (n0+n2) : 0 : (m0+m2)
    __m256i TEMP8 = _mm256_xor_si256(multiplier1, multiplier3); // 0 : (n1+n3) : 0 : (m1+m3)
    
    temp5 = _mm256_clmulepi64_epi128(TEMP1, TEMP3, 0x00); // (v0+v1)(n0+n1) : (u0+u1)(m0+m1)
    temp6 = _mm256_clmulepi64_epi128(TEMP2, TEMP4, 0x00); // (v2+v3)(n2+n3) : (u2+u3)(m2+m3)
    
    temp5 = _mm256_xor_si256(_mm256_xor_si256(temp5, temp1), temp2); // (v0+v1)(n0+n1) + v0n0 + v1n1 : (u0+u1)(m0+m1) + u0m0 + u1m1
    temp6 = _mm256_xor_si256(_mm256_xor_si256(temp6, temp3), temp4); // (v2+v3)(n2+n3) + v2n2 + v3n3 : (u2+u3)(m2+m3) + u2m2 + u3m3
    
    temp7 = _mm256_clmulepi64_epi128(TEMP5, TEMP7, 0x00); // (v0+v2)(n0+n2) : (u0+u2)(m0+m2) 
    temp8 = _mm256_clmulepi64_epi128(TEMP6, TEMP8, 0x00); // (v1+v3)(n1+n3) : (u1+u3)(m1+m3)
    temp9 = _mm256_clmulepi64_epi128(TEMP5, TEMP8, 0x00); // (v0+v2)(n1+n3) : (u0+u2)(m1+m3) 
    temp10 = _mm256_clmulepi64_epi128(TEMP6, TEMP7, 0x00); // (v1+v3)(n0+n2) : (u1+u3)(m0+m2) 
    temp9 = _mm256_xor_si256(temp9, temp10); // (v0+v2)(n1+n3) + (v1+v3)(n0+n2) : (u0+u2)(m1+m3) + (u1+u3)(m0+m2) 
    
  
    //creating w0,w1,w2
    __m256i lower_w0 = _mm256_xor_si256(temp1,_mm256_slli_si256(temp5, 8));    
    __m256i upper_w0 = _mm256_xor_si256(temp2, _mm256_srli_si256(temp5, 8));
    
    __m256i lower_w2 = _mm256_xor_si256(temp3, _mm256_slli_si256(temp6, 8));    
    __m256i upper_w2 = _mm256_xor_si256(temp4, _mm256_srli_si256(temp6, 8));
    
    __m256i lower_w1 = _mm256_xor_si256(temp7, _mm256_slli_si256(temp9, 8));
    __m256i upper_w1 = _mm256_xor_si256(temp8, _mm256_srli_si256(temp9, 8));
    lower_w1 = _mm256_xor_si256(lower_w2, _mm256_xor_si256(lower_w1, lower_w0)); 
    upper_w1 = _mm256_xor_si256(upper_w2, _mm256_xor_si256(upper_w1, upper_w0));
    
    __m256i mult0 = lower_w0; 	//0th (lowest) 128 bits of mult result without reduction
    __m256i mult1 = _mm256_xor_si256(upper_w0, lower_w1); //1st 128 bits of mult result without reduction
    __m256i mult2 = _mm256_xor_si256(lower_w2, upper_w1); //2nd 128 bits of mult result without reduction
    __m256i mult3 = upper_w2; 	//3rd (highest) 128 bits of mult result without reduction
    
    /*//printing mult result
    uint64_t M0[4], M1[4], M2[4], M3[4];
    _mm256_storeu_si256((__m256i*)M0, mult0);
    _mm256_storeu_si256((__m256i*)M1, mult1);
    _mm256_storeu_si256((__m256i*)M2, mult2);
    _mm256_storeu_si256((__m256i*)M3, mult3);
    
    printf("\nmult0:\n");
    for (int i=3; i>=0; i--)
        printf("%016lx ",M0[i]);
    //printf("\n");
    printf("\nmult1:\n");
    for (int i=3; i>=0; i--)
        printf("%016lx ",M1[i]);
    //printf("\n");
    printf("\nmult2:\n");
    for (int i=3; i>=0; i--)
        printf("%016lx ",M2[i]);
    //printf("\n");
    printf("\nmult3:\n");
    for (int i=3; i>=0; i--)
        printf("%016lx ",M3[i]);
    printf("\n");*/
    
    reduce(mult0, mult1, mult2, mult3, res1, res2);
    
}

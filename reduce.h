void reduce(__m256i mult0, __m256i mult1, __m256i mult2, __m256i mult3, uint64_t *res1, uint64_t *res2)
{//mask
    __m256i mask02 = _mm256_set_epi64x(0x0000000000000000, 0xffffffffffffffff, 0x0000000000000000, 0xffffffffffffffff);
    __m256i mask13 = _mm256_set_epi64x(0xffffffffffffffff, 0x0000000000000000, 0xffffffffffffffff, 0x0000000000000000);
    
    //storing mult result into 8 256-bit registers at lower bits 
    __m256i X0 = _mm256_and_si256(mult0, mask02);
    
    __m256i t1 = _mm256_and_si256(mult0, mask13);
    __m256i X1 = _mm256_permute4x64_epi64(t1, 0b10110001);
    
    __m256i X2 = _mm256_and_si256(mult1, mask02);
    
    __m256i t2 = _mm256_and_si256(mult1, mask13);
    __m256i X3 = _mm256_permute4x64_epi64(t2, 0b10110001);
    
    __m256i X4 = _mm256_and_si256(mult2, mask02);
    
    __m256i t3 = _mm256_and_si256(mult2, mask13);
    __m256i X5 = _mm256_permute4x64_epi64(t3, 0b10110001);
    
    __m256i X6 = _mm256_and_si256(mult3, mask02);
    
    __m256i t4 = _mm256_and_si256(mult3, mask13);
    __m256i X7 = _mm256_permute4x64_epi64(t4, 0b10110001);
   
   /*uint64_t x0[4], x1[4], x2[4], x3[4], x4[4], x5[4], x6[4], x7[4];
   _mm256_storeu_si256((__m256i*)x0, X0);
   _mm256_storeu_si256((__m256i*)x1, X1);
   _mm256_storeu_si256((__m256i*)x2, X2);
   _mm256_storeu_si256((__m256i*)x3, X3);
   _mm256_storeu_si256((__m256i*)x4, X4);
   _mm256_storeu_si256((__m256i*)x5, X5);
   _mm256_storeu_si256((__m256i*)x6, X6);
   _mm256_storeu_si256((__m256i*)x7, X7);
   
   printf("\nx0: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x0[i]);
    //printf("\n");
    printf("\nx1: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x1[i]);
    //printf("\n");
    printf("\nx2: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x2[i]);
    //printf("\n");
    printf("\nx3: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x3[i]);
    //printf("\n");
    printf("\nx4: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x4[i]);
    //printf("\n");
    printf("\nx5: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x5[i]);
    //printf("\n");
    printf("\nx6: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x6[i]);
    //printf("\n");
    printf("\nx7: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",x7[i]);
    printf("\n");*/
    
    
    __m256i C0,C1,C2,C3;
    C0 = _mm256_or_si256(_mm256_slli_epi64(X4,5), _mm256_srli_epi64(X3,59));
    C1 = _mm256_or_si256(_mm256_slli_epi64(X5,5), _mm256_srli_epi64(X4,59));
    C2 = _mm256_or_si256(_mm256_slli_epi64(X6,5), _mm256_srli_epi64(X5,59));
    C3 = _mm256_or_si256(_mm256_slli_epi64(X7,5), _mm256_srli_epi64(X6,59));
    
    /*uint64_t c0[4], c1[4], c2[4], c3[4];
    _mm256_storeu_si256((__m256i*)c0, C0);
    _mm256_storeu_si256((__m256i*)c1, C1);
    _mm256_storeu_si256((__m256i*)c2, C2);
    _mm256_storeu_si256((__m256i*)c3, C3);
    
    printf("\nc0: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",c0[i]);
    printf("\nc1: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",c1[i]);
    printf("\nc2: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",c2[i]);
    printf("\nc3: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",c3[i]);
    printf("\n");*/
        
    //step 1 : shift C3 by 62-5, 60-5, 57-5 bits to the right
    __m256i A,B,C,D;
    A = _mm256_srli_epi64(C3, 57);
    B = _mm256_srli_epi64(C3, 55);
    C = _mm256_srli_epi64(C3, 52);
     
    //step 2: XOR A, B, C with C0 to compute D
    D =  _mm256_xor_si256(_mm256_xor_si256(_mm256_xor_si256(C0, A), B), C);
    
    __m256i E0, E1, E2, E3, F0, F1, F2, F3, G0, G1, G2, G3, H0, H1, H2, H3;
    //step 3: shift [c3:c2:c1:cD] by 2, 4 and 7 bits to the left
    E3 = _mm256_or_si256(_mm256_srli_epi64(C2, 62), _mm256_slli_epi64(C3, 2));
    E2 = _mm256_or_si256(_mm256_srli_epi64(C1, 62), _mm256_slli_epi64(C2, 2));
    E1 = _mm256_or_si256(_mm256_srli_epi64(D, 62), _mm256_slli_epi64(C1, 2));
    E0 = _mm256_slli_epi64(D, 2);
    
    F3 = _mm256_or_si256(_mm256_srli_epi64(C2, 60), _mm256_slli_epi64(C3, 4));
    F2 = _mm256_or_si256(_mm256_srli_epi64(C1, 60), _mm256_slli_epi64(C2, 4));
    F1 = _mm256_or_si256(_mm256_srli_epi64(D, 60), _mm256_slli_epi64(C1, 4));
    F0 = _mm256_slli_epi64(D, 4);
    
    G3 = _mm256_or_si256(_mm256_srli_epi64(C2, 57), _mm256_slli_epi64(C3, 7));
    G2 = _mm256_or_si256(_mm256_srli_epi64(C1, 57), _mm256_slli_epi64(C2, 7));
    G1 = _mm256_or_si256(_mm256_srli_epi64(D, 57), _mm256_slli_epi64(C1, 7));
    G0 = _mm256_slli_epi64(D, 7);
    
    //step 4: XOR [E3:E2:E1:E0], [F3:F2:F1:F0], [G3:G2:G1:G0] with each other and [C3:C2:C1:D] to compute {H3:H2:H1:H0]
    H3 = _mm256_xor_si256(_mm256_xor_si256(_mm256_xor_si256(C3, G3), F3), E3);
    H2 = _mm256_xor_si256(_mm256_xor_si256(_mm256_xor_si256(C2, G2), F2), E2);
    H1 = _mm256_xor_si256(_mm256_xor_si256(_mm256_xor_si256(C1, G1), F1), E1);
    H0 = _mm256_xor_si256(_mm256_xor_si256(_mm256_xor_si256(D, G0), F0), E0);
    
    //compute the final result [X3 ⊕ H3 : X2 ⊕ H2 : X1 ⊕ H1 : X0 ⊕ H0]
    H3 = _mm256_xor_si256(X3, H3);
    H2 = _mm256_xor_si256(X2, H2);
    H1 = _mm256_xor_si256(X1, H1);
    H0 = _mm256_xor_si256(X0, H0);
    
    __m256i temp = _mm256_set_epi64x(0x0000000000000000, 0x07ffffffffffffff, 0x0000000000000000, 0x07ffffffffffffff);
    H3 = _mm256_and_si256(temp,H3);
    
    //multiplication result with reduction of u.m
    res1[0] = _mm256_extract_epi64(H0, 0);
    res1[1] = _mm256_extract_epi64(H1, 0);
    res1[2] = _mm256_extract_epi64(H2, 0);
    res1[3] = _mm256_extract_epi64(H3, 0);
    
    //multiplication result with reduction of v.n
    res2[0] = _mm256_extract_epi64(H0, 2);
    res2[1] = _mm256_extract_epi64(H1, 2);
    res2[2] = _mm256_extract_epi64(H2, 2);
    res2[3] = _mm256_extract_epi64(H3, 2);
    
}

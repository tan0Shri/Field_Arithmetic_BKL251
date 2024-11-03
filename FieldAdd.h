void AddSub(uint64_t *u, uint64_t *m, uint64_t *v, uint64_t *n, uint64_t *res1, uint64_t *res2)
{
    __m256i num1_0 = _mm256_set_epi64x(v[1], v[0], u[1], u[0]);
    __m256i num1_1 = _mm256_set_epi64x(v[3], v[2], u[3], u[2]);
    
    __m256i num2_0 = _mm256_set_epi64x(n[1], n[0], m[1], m[0]);
    __m256i num2_1 = _mm256_set_epi64x(n[3], n[2], m[3], m[2]);
    
    __m256i result0 = _mm256_xor_si256(num1_0, num2_0);
    __m256i result1 = _mm256_xor_si256(num1_1, num2_1);
    
   /* uint64_t t1[4], t2[4];
    _mm256_storeu_si256((__m256i*)t1, result0);
    _mm256_storeu_si256((__m256i*)t2, result1);
    printf("\nresult0: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",t1[i]);
    printf("\nresult1: ");
    for (int i=3; i>=0; i--)
        printf("%016lx ",t2[i]);*/
    
    //storing result of u+m
    res1[0] = _mm256_extract_epi64(result0, 0);
    res1[1] = _mm256_extract_epi64(result0, 1);
    res1[2] = _mm256_extract_epi64(result1, 0);
    res1[3] = _mm256_extract_epi64(result1, 1);
    
    //storing result of v+n
    res2[0] = _mm256_extract_epi64(result0, 2);
    res2[1] = _mm256_extract_epi64(result0, 3);
    res2[2] = _mm256_extract_epi64(result1, 2);
    res2[3] = _mm256_extract_epi64(result1, 3);
    
}

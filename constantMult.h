
void CnstMult(uint64_t *u, uint64_t *v, uint64_t c, uint64_t *result1, uint64_t *result2)
{
    __m256i num0 = _mm256_set_epi64x(v[1], v[0], u[1], u[0]);
    //__m256i num1 = _mm256_set_epi64x(0x0000000000000000, v[1], 0x0000000000000000, u[1]);
    
    __m256i num1 = _mm256_set_epi64x(v[3], v[2], u[3], u[2]);
    //__m256i num3 = _mm256_set_epi64x(0x0000000000000000, v[3], 0x0000000000000000, u[3]);
    
    __m256i constant = _mm256_set_epi64x(0, c, 0, c);
    
    __m256i temp0, temp1, temp2, temp3;
    temp0 = _mm256_clmulepi64_epi128(num0, constant, 0x00); // cv[0] : cu[0]
    temp1 = _mm256_clmulepi64_epi128(num0, constant, 0x10); // cv[1] : cu[1]
    temp2 = _mm256_clmulepi64_epi128(num1, constant, 0x00); // cv[2] : cu[2]
    temp3 = _mm256_clmulepi64_epi128(num1, constant, 0x10); // cv[3] : cu[3]
    
    reduce(temp0, temp1, temp2, temp3, result1, result2);
}





#include <immintrin.h>
#include <stdio.h>

typedef struct {
    int x, y, z;
} Vector3;

void multiply_vectors_avx2(Vector3* vectors, int count, int scalar) {
    __m256i scalar_vec = _mm256_set1_epi32(scalar);
    
    // Przetwarzamy 8 int'ów na raz, co odpowiada 2 pełnym wektorom i 2/3 trzeciego
    for (int i = 0; i < count; i += 2) {
        // Ładujemy 8 kolejnych int'ów (2 pełne wektory i część trzeciego)
        __m256i vec = _mm256_loadu_si256((__m256i*)&vectors[i].x);
        
        // Mnożymy przez skalar używając AVX2
        vec = _mm256_mullo_epi32(vec, scalar_vec);
        
        // Zapisujemy wynik z powrotem do pamięci
        _mm256_storeu_si256((__m256i*)&vectors[i].x, vec);
    }
    
    // Obsługa pozostałych elementów, jeśli liczba wektorów nie jest parzysta
    for (int i = (count / 2) * 2; i < count; i++) {
        vectors[i].x *= scalar;
        vectors[i].y *= scalar;
        vectors[i].z *= scalar;
    }
}

int main() {
    Vector3 vectors[] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
        {13, 14, 15}
    };
    int count = sizeof(vectors) / sizeof(Vector3);
    int scalar = 2;

    multiply_vectors_avx2(vectors, count, scalar);

    for (int i = 0; i < count; i++) {
        printf("Vector %d: (%d, %d, %d)\n", i, vectors[i].x, vectors[i].y, vectors[i].z);
    }

    return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplicate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbuczyns <gbuczyns@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:08:52 by gbuczyns          #+#    #+#             */
/*   Updated: 2024/07/10 20:15:53 by gbuczyns         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gcc -mavx2 -o multiplicate multiplicate.c
#include <immintrin.h>
#include <stdio.h>

void multiply_array_avx(int* arr, int size, int multiplier) {
    __m256i mult = _mm256_set1_epi32(multiplier);
    
    for (int i = 0; i < size; i += 8) {
        __m256i vec = _mm256_loadu_si256((__m256i*)&arr[i]);
        vec = _mm256_mullo_epi32(vec, mult);
        _mm256_storeu_si256((__m256i*)&arr[i], vec);
    }
}

int main() {
    int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int size = 16;
    int multiplier = 2;
	int i = 0;


    multiply_array_avx(arr, size, multiplier);

    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }
	
	while(i < size)
	{
		printf("%d, ", arr[i]);
		i++;
	}
	printf("\n");

    return 0;
}
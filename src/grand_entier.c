//
// Created by khalid on 10/10/2025.
//
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define BASE 2

BigBinary createBigBinary(int size) {
    BigBinary binary;
    binary.Signe = 0;
    binary.Taille = size;
    binary.BigBinary = malloc(size * sizeof(int));
}
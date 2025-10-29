//
// Created by khalid on 10/10/2025.
//

#ifndef PROJET_C_PGCD_GRAND_ENTIER_H
#define PROJET_C_PGCD_GRAND_ENTIER_H

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define BASE 2

typedef struct {
    int *Tdigits;
    int Taille;
    int Signe;
} BigBinary;

BigBinary createBigBinary(int size);
BigBinary initBigBinary(int taille, int signe);
BigBinary createBigBinaryFromString(char *chaine);
void displayBigBinary(BigBinary nb);
void freeBigBinary(BigBinary *nb);
BigBinary sumBigBinary(BigBinary a, BigBinary b);
void ajusterTaille(BigBinary *nb);

#endif //PROJET_C_PGCD_GRAND_ENTIER_H
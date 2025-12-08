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
BigBinary createZero();
BigBinary initBigBinary(int taille, int signe);
BigBinary createBigBinaryFromString(char *chaine);
BigBinary sumBigBinary(BigBinary a, BigBinary b);
BigBinary subBigBinary(BigBinary a, BigBinary b);
BigBinary copierBigBinary(BigBinary source);
BigBinary pgcdBigBinary(BigBinary a, BigBinary b);
void displayBigBinary(BigBinary nb);
void freeBigBinary(BigBinary *nb);
void ajusterTaille(BigBinary *nb);
void divisePar2(BigBinary *nb);
void multiplierPar2(BigBinary *nb);
bool comparaisonEgal(BigBinary a, BigBinary b);
bool comparaisonInferieur(BigBinary a, BigBinary b);
bool estPair(BigBinary nb);
char* bigBinaryToDecimal(const BigBinary nb);

#endif //PROJET_C_PGCD_GRAND_ENTIER_H
//
// Created by khalid on 10/10/2025.
//
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "grand_entier.h"

#include <string.h>

#define BASE 2

// -------------------------------------------------------------------------
//                          FONCTIONS DE BASE (INIT / MEMOIRE)
// -------------------------------------------------------------------------

BigBinary createBigBinary(int size) {
    BigBinary binary;
    binary.Signe = 0;
    binary.Taille = size;
    binary.Tdigits = malloc(size * sizeof(int));
    return binary;
}

BigBinary createZero() {
    BigBinary zero;
    zero.Tdigits = malloc(sizeof(int));
    zero.Tdigits[0] = 0;
    zero.Taille = 1;
    zero.Signe = 0;
    return zero;
}

BigBinary createBigBinaryFromString(char *chaine) {
    BigBinary binary;
    int n = strlen(chaine);
    binary.Taille = 0;

    // Comptons uniquement les caractères valides ('0' ou '1')
    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1'){
            binary.Taille++;
        }
    }

    binary.Tdigits = malloc(sizeof(int) * binary.Taille);
    binary.Signe = +1;
    int index = 0;
    int tousZeros = 1;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            binary.Tdigits[index] = chaine[i] - '0';
            if (binary.Tdigits[index] == 1) tousZeros = 0;
            index++;
        }
    }
    if (tousZeros) binary.Signe = 0;
    return binary;
}

BigBinary initBigBinary(int taille, int signe) {
    BigBinary nb;
    nb.Signe = signe;
    nb.Taille = taille;
    nb.Tdigits = malloc(sizeof(int) * taille);
    for (int i = 0; i < taille; ++i) {
        nb.Tdigits[i] = 0;
    }
    return nb;
}

void displayBigBinary(BigBinary nb) {
    if (nb.Signe == -1) {
        printf("-");
    }

    if (nb.Taille == 0 || nb.Tdigits == NULL) {
        printf("0\n");
        return;
    }

    // Si le nombre est nul (tous les bits à 0)
    bool estNul = true;
    for (int i = 0; i < nb.Taille; ++i) {
        if (nb.Tdigits[i] != 0) {
            estNul = false;
            break;
        }
    }
    if (estNul) {
        printf("0\n");
        return;
    }

    // Affichage du nombre binaire
    for (int i = 0; i < nb.Taille; ++i) {
        printf("%d", nb.Tdigits[i]);
    }

    printf("\n");
}

void freeBigBinary(BigBinary *nb) {
    if (nb->Tdigits != NULL) {
        free(nb->Tdigits);
        nb->Tdigits = NULL;
    }
    nb->Taille = 0;
    nb->Signe = 0;
}

// -------------------------------------------------------------------------
//                          UTILITAIRES (COPIE, AJUSTEMENT, ETC.)
// -------------------------------------------------------------------------

// Fonction pour supprimer les zéros non significatifs
void ajusterTaille(BigBinary *nb) {
    // Trouver le premier bit non nul
    int nouveauDebut = 0;
    while (nouveauDebut < nb->Taille && nb->Tdigits[nouveauDebut] == 0) {
        nouveauDebut++;
    }

    // Si tout est zéro
    if (nouveauDebut == nb->Taille) {
        nb->Taille = 1;
        nb->Tdigits[0] = 0;
        nb->Signe = 0;
        return;
    }

    // Décaler le tableau si nécessaire
    if (nouveauDebut > 0) {
        int nouvelleTaille = nb->Taille - nouveauDebut;
        for (int i = 0; i < nouvelleTaille; i++) {
            nb->Tdigits[i] = nb->Tdigits[nouveauDebut + i];
        }
        nb->Taille = nouvelleTaille;
    }
}

// Crée une copie d'un BigBinary
BigBinary copierBigBinary(BigBinary source) {
    BigBinary copie;

    if (source.Signe == 0 || source.Taille == 0) {
        return createZero();
    }

    copie.Tdigits = malloc(source.Taille * sizeof(int));
    copie.Taille = source.Taille;
    copie.Signe = source.Signe;

    for (int i = 0; i < source.Taille; i++) {
        copie.Tdigits[i] = source.Tdigits[i];
    }

    return copie;
}

bool estPair(BigBinary nb) {
    // Un nombre est pair si son bit de poids faible (LSB) est 0
    if (nb.Taille == 0 || nb.Signe == 0) {
        return true;
    }
    return (nb.Tdigits[nb.Taille - 1] == 0);
}

// -------------------------------------------------------------------------
//                          COMPARAISONS
// -------------------------------------------------------------------------

bool comparaisonEgal(BigBinary a, BigBinary b) {
    if (a.Signe != b.Signe) return false;
    if (a.Taille != b.Taille) return false;

    for (int i = 0; i < a.Taille; i++) {
        if (a.Tdigits[i] != b.Tdigits[i]) return false;
    }
    return true;
}

bool comparaisonInferieur(BigBinary a, BigBinary b) {
    if (a.Signe < b.Signe) return true;
    if (a.Signe > b.Signe) return false;

    if (a.Taille < b.Taille) return true;
    if (a.Taille > b.Taille) return false;

    for (int i = 0; i < a.Taille; i++) {
        if (a.Tdigits[i] < b.Tdigits[i]) return true;
        if (a.Tdigits[i] > b.Tdigits[i]) return false;
    }
    return false;
}

// -------------------------------------------------------------------------
//                          OPERATIONS ARITHMETIQUES (ADD, SUB, DIV2, MUL2)
// -------------------------------------------------------------------------

BigBinary sumBigBinary(BigBinary a, BigBinary b) {
    BigBinary resultat;

    int maxLen = (a.Taille > b.Taille) ? a.Taille : b.Taille;
    resultat.Tdigits = malloc((maxLen + 1) * sizeof(int));
    resultat.Taille = maxLen + 1;
    resultat.Signe = 1;

    int retenue = 0;

    for (int i = 0; i < maxLen; i++) {
        int indexA = a.Taille - 1 - i;
        int indexB = b.Taille - 1 - i;

        int bitA = (indexA >= 0) ? a.Tdigits[indexA] : 0;
        int bitB = (indexB >= 0) ? b.Tdigits[indexB] : 0;

        int somme = bitA + bitB + retenue;
        int indexResultat = resultat.Taille - 1 - i;
        resultat.Tdigits[indexResultat] = somme % BASE;
        retenue = somme / BASE;
    }

    resultat.Tdigits[0] = retenue;
    ajusterTaille(&resultat);

    return resultat;
}

BigBinary subBigBinary(BigBinary a, BigBinary b) {
    BigBinary resultat;
    int emprunt = 0;

    if (a.Signe < 0 || b.Signe < 0) {
        fprintf(stderr, "Erreur: la fonction n'attend que les nombres positifs\n");
        return createZero();
    }

    if (comparaisonInferieur(a, b)) {
        fprintf(stderr, "Erreur: A doit être >= B pour la soustraction\n");
        return createZero();
    }

    if (comparaisonEgal(a, b)) {
        return createZero();
    }

    resultat.Tdigits = malloc(a.Taille * sizeof(int));
    resultat.Taille = a.Taille;
    resultat.Signe = 1;

    for (int i = 0; i < a.Taille; i++) {
        int indexA = a.Taille - 1 - i;
        int indexB = b.Taille - 1 - i;

        int bitA = a.Tdigits[indexA];
        int bitB = (indexB >= 0) ? b.Tdigits[indexB] : 0;

        int diff = bitA - bitB - emprunt;

        if (diff < 0) {
            diff += BASE;
            emprunt = 1;
        } else {
            emprunt = 0;
        }

        int indexResultat = resultat.Taille - 1 - i;
        resultat.Tdigits[indexResultat] = diff;
    }

    ajusterTaille(&resultat);
    return resultat;
}

void divisePar2(BigBinary *nb) {
    if (nb->Signe == 0 || nb->Taille <= 1) {
        nb->Tdigits[0] = 0;
        nb->Taille = 1;
        nb->Signe = 0;
        return;
    }

    nb->Taille--;
    int *nouveauTableau = malloc(nb->Taille * sizeof(int));
    for (int i = 0; i < nb->Taille; i++) {
        nouveauTableau[i] = nb->Tdigits[i];
    }
    free(nb->Tdigits);
    nb->Tdigits = nouveauTableau;

    if (nb->Taille == 0) {
        nb->Tdigits = malloc(sizeof(int));
        nb->Tdigits[0] = 0;
        nb->Taille = 1;
        nb->Signe = 0;
    }
}

void multiplierPar2(BigBinary *nb) {
    if (nb->Signe == 0) {
        return;
    }
    int *nouveauTableau = malloc((nb->Taille + 1) * sizeof(int));

    for (int i = 0; i < nb->Taille; i++) {
        nouveauTableau[i] = nb->Tdigits[i];
    }

    nouveauTableau[nb->Taille] = 0;

    free(nb->Tdigits);
    nb->Tdigits = nouveauTableau;
    nb->Taille++;
}

// -------------------------------------------------------------------------
//                          OPERATIONS AVANCEES (MULT, MOD, EXP)
// -------------------------------------------------------------------------

// Multiplication Égyptienne (A * B) - [AJOUTÉ COMME DEMANDÉ]
BigBinary multiplicationEgyptienne(BigBinary a, BigBinary b) {
    BigBinary resultat = createZero();
    BigBinary A = copierBigBinary(a);
    BigBinary B = copierBigBinary(b);

    while (B.Signe != 0) {
        // Si B est impair
        if (!estPair(B)) {
            BigBinary temp = sumBigBinary(resultat, A);
            freeBigBinary(&resultat);
            resultat = temp;
        }

        // A = A * 2
        multiplierPar2(&A);
        // B = B / 2
        divisePar2(&B);
    }

    freeBigBinary(&A);
    freeBigBinary(&B);
    return resultat;
}

// Modulo (A % N) - [RE-INTEGRE POUR FAIRE FONCTIONNER L'EXP]
BigBinary moduloBigBinary(BigBinary a, BigBinary n) {
    if (n.Signe == 0) {
        fprintf(stderr, "Erreur: Modulo par zero interdit.\n");
        return createZero();
    }
    if (a.Signe == 0) return createZero();

    BigBinary R = copierBigBinary(a);
    R.Signe = 1;
    BigBinary N = copierBigBinary(n);
    N.Signe = 1;

    while (!comparaisonInferieur(R, N)) {
        int diffTaille = R.Taille - N.Taille;
        if (diffTaille < 0) diffTaille = 0;

        BigBinary N_shift = copierBigBinary(N);
        for (int i = 0; i < diffTaille; i++) {
            multiplierPar2(&N_shift);
        }

        if (comparaisonInferieur(R, N_shift)) {
            divisePar2(&N_shift);
        }

        BigBinary temp = subBigBinary(R, N_shift);
        freeBigBinary(&R);
        R = temp;
        freeBigBinary(&N_shift);
    }

    freeBigBinary(&N);
    return R;
}

// Exponentiation Modulaire (base ^ exp) % mod - [RE-INTEGRE]
BigBinary exponentiationModulaire(BigBinary base, BigBinary exp, BigBinary mod) {
    BigBinary resultat = createBigBinaryFromString("1");
    BigBinary b = moduloBigBinary(base, mod);
    BigBinary e = copierBigBinary(exp);

    while (e.Signe != 0) {
        if (!estPair(e)) {
            BigBinary mult = multiplicationEgyptienne(resultat, b);
            freeBigBinary(&resultat);
            resultat = moduloBigBinary(mult, mod);
            freeBigBinary(&mult);
        }

        BigBinary carre = multiplicationEgyptienne(b, b);
        freeBigBinary(&b);
        b = moduloBigBinary(carre, mod);
        freeBigBinary(&carre);

        divisePar2(&e);
    }

    freeBigBinary(&b);
    freeBigBinary(&e);
    return resultat;
}

// -------------------------------------------------------------------------
//                          PGCD (ALGORITHME BINAIRE)
// -------------------------------------------------------------------------

BigBinary pgcdBigBinary(BigBinary a, BigBinary b) {
    if (b.Signe == 0) return copierBigBinary(a);
    if (a.Signe == 0) return copierBigBinary(b);

    BigBinary aCopy = copierBigBinary(a);
    BigBinary bCopy = copierBigBinary(b);
    int facteur2 = 0;

    while (estPair(aCopy) && estPair(bCopy)) {
        divisePar2(&aCopy);
        divisePar2(&bCopy);
        facteur2++;
    }

    while (aCopy.Signe != 0 && bCopy.Signe != 0) {
        while (estPair(aCopy) && !estPair(bCopy)) {
            divisePar2(&aCopy);
        }
        while (!estPair(aCopy) && estPair(bCopy)) {
            divisePar2(&bCopy);
        }

        if (!estPair(aCopy) && !estPair(bCopy)) {
            if (comparaisonInferieur(aCopy, bCopy)) {
                BigBinary temp = aCopy;
                aCopy = bCopy;
                bCopy = temp;
            }
            BigBinary diff = subBigBinary(aCopy, bCopy);
            freeBigBinary(&aCopy);
            aCopy = diff;
        }
    }

    BigBinary resultat;
    if (bCopy.Signe == 0) {
        resultat = aCopy;
        freeBigBinary(&bCopy);
    } else {
        resultat = bCopy;
        freeBigBinary(&aCopy);
    }

    for (int i = 0; i < facteur2; i++) {
        multiplierPar2(&resultat);
    }

    return resultat;
}
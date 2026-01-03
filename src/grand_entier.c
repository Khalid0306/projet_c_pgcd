//
// Created by khalid on 10/10/2025.
//
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include"grand_entier.h"

#include <string.h>

#define BASE 2

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

    // Comptons uniquementles caractèresvalides (’0’ou ’1’)
    for (int i =0; i< n;++i) {
        if (chaine[i] == '0' || chaine[i] == '1'){
            binary.Taille++;
        }
    }

    binary.Tdigits= malloc(sizeof(int) * binary.Taille);
    binary.Signe= +1;
    int index= 0;
    int tousZeros = 1;

    for (int i = 0; i < n; ++i) {
        if (chaine[i] == '0' || chaine[i] == '1') {
            binary.Tdigits[index] = chaine[i]- '0';
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

// Libération de la mémoire
void freeBigBinary(BigBinary *nb) {
    free(nb->Tdigits);
    nb->Tdigits = NULL;
    nb->Taille = 0;
    nb->Signe = 0;
}

BigBinary sumBigBinary(BigBinary a, BigBinary b) {
    BigBinary resultat;

    // Déterminer la taille maximale
    int maxLen = (a.Taille > b.Taille) ? a.Taille : b.Taille;

    // Allouer pour maxLen + 1 (pour la retenue finale)
    resultat.Tdigits = malloc((maxLen + 1) * sizeof(int));
    resultat.Taille = maxLen + 1;
    resultat.Signe = 1;  // Résultat positif (A, B ≥ 0)

    int retenue = 0;

    // Parcourir du LSB au MSB
    for (int i = 0; i < maxLen; i++)
    {
        // Index dans A et B (depuis la FIN du tableau)
        int indexA = a.Taille - 1 - i;
        int indexB = b.Taille - 1 - i;

        // Récupérer les bits
        int bitA = (indexA >= 0) ? a.Tdigits[indexA] : 0;
        int bitB = (indexB >= 0) ? b.Tdigits[indexB] : 0;

        // Calcul de la somme avec retenue
        int somme = bitA + bitB + retenue;

        // Stocker dans resultat
        int indexResultat = resultat.Taille - 1 - i;
        resultat.Tdigits[indexResultat] = somme % BASE;
        retenue = somme / BASE;
    }

    // Stocker la retenue finale en tête
    resultat.Tdigits[0] = retenue;

    // Supprimer le 0 de tête si pas de retenue
    ajusterTaille(&resultat);

    return resultat;

}

// Fonction pour supprimer les zéros non significatifs
void ajusterTaille(BigBinary *nb)
{
    // Trouver le premier bit non nul
    int nouveauDebut = 0;
    while (nouveauDebut < nb->Taille && nb->Tdigits[nouveauDebut] == 0)
    {
        nouveauDebut++;
    }

    // Si tout est zéro
    if (nouveauDebut == nb->Taille)
    {
        nb->Taille = 1;
        nb->Tdigits[0] = 0;
        nb->Signe = 0;
        return;
    }

    // Décaler le tableau si nécessaire
    if (nouveauDebut > 0)
    {
        int nouvelleTaille = nb->Taille - nouveauDebut;
        for (int i = 0; i < nouvelleTaille; i++)
        {
            nb->Tdigits[i] = nb->Tdigits[nouveauDebut + i];
        }
        nb->Taille = nouvelleTaille;
    }
}

bool comparaisonEgal(BigBinary a, BigBinary b) {
    // Signes différents
    if (a.Signe != b.Signe) return false;

    // Tailles différentes
    if (a.Taille != b.Taille) return false;

    // Compare tous les bits
    for (int i = 0; i < a.Taille; i++) {
        if (a.Tdigits[i] != b.Tdigits[i]) return false;
    }

    return true;
}

bool comparaisonInferieur(BigBinary a, BigBinary b) {
    // Si les signes sont différents
    if (a.Signe < b.Signe) return true;
    if (a.Signe > b.Signe) return false;

    // Si les tailles sont différentes
    if (a.Taille < b.Taille) return true;
    if (a.Taille > b.Taille) return false;

    // Comparer bit par bit (MSB first)
    for (int i = 0; i < a.Taille; i++) {
        if (a.Tdigits[i] < b.Tdigits[i]) return true;
        if (a.Tdigits[i] > b.Tdigits[i]) return false;
    }

    // Ils sont égaux
    return false;
}

BigBinary subBigBinary(BigBinary a, BigBinary b) {
    BigBinary resultat;
    int emprunt = 0;


    // A et B doivent être positifs ou nuls
    if (a.Signe < 0 || b.Signe < 0) {
        fprintf(stderr, "Erreur: la fonction n'attend que les nombres positifs\n");
        // Retourner un BigBinary null
        resultat.Tdigits = NULL;
        resultat.Taille = 0;
        resultat.Signe = 0;
        return resultat;
    }

    // A doit être >= B
    if (comparaisonInferieur(a, b)) {
        fprintf(stderr, "Erreur: A doit être >= B pour la soustraction\n");
        return createZero();
    }

    // Si A == B, return 0
    if (comparaisonEgal(a, b)) {
        return createZero();
    }

    // Allouer pour la taille de A
    resultat.Tdigits = malloc(a.Taille * sizeof(int));
    resultat.Taille = a.Taille;
    resultat.Signe = 1;  // Résultat positif

    // Parcourir de DROITE à GAUCHE (du LSB au MSB)
    for (int i = 0; i < a.Taille; i++) {
        // Index dans A et B (depuis la FIN du tableau)
        int indexA = a.Taille - 1 - i;
        int indexB = b.Taille - 1 - i;

        // Récupérer les bits (0 si hors limites pour B)
        int bitA = a.Tdigits[indexA];
        int bitB = (indexB >= 0) ? b.Tdigits[indexB] : 0;

        // Calcul de la différence avec emprunt
        int diff = bitA - bitB - emprunt;

        if (diff < 0) {
            diff += BASE;  // BASE = 2
            emprunt = 1;
        } else {
            emprunt = 0;
        }

        // Stocker dans resultat (index depuis la FIN)
        int indexResultat = resultat.Taille - 1 - i;
        resultat.Tdigits[indexResultat] = diff;
    }

    // Supprimer les zéros de tête)
    ajusterTaille(&resultat);

    return resultat;
}

void divisePar2(BigBinary *nb) {
    // Cas zéro ou nombre à 1 bit
    if (nb->Signe == 0 || nb->Taille <= 1) {
        nb->Tdigits[0] = 0;
        nb->Taille = 1;
        nb->Signe = 0;
        return;
    }

    // Enlever le bit de poids faible = dernier élément
    nb->Taille--;

    // Réallouer pour libérer la mémoire
    int *nouveauTableau = malloc(nb->Taille * sizeof(int));
    for (int i = 0; i < nb->Taille; i++) {
        nouveauTableau[i] = nb->Tdigits[i];
    }
    free(nb->Tdigits);
    nb->Tdigits = nouveauTableau;

    // Si le résultat est vide, mettre à 0
    if (nb->Taille == 0) {
        nb->Tdigits = malloc(sizeof(int));
        nb->Tdigits[0] = 0;
        nb->Taille = 1;
        nb->Signe = 0;
    }
}

bool estPair(BigBinary nb) {
    // Un nombre est pair si son bit de poids faible (LSB) est 0
    if (nb.Taille == 0 || nb.Signe == 0) {
        return true;
    }
    return (nb.Tdigits[nb.Taille - 1] == 0);
}


void multiplierPar2(BigBinary *nb) {
    if (nb->Signe == 0) {
        return;  // 0 * 2 = 0
    }
    int *nouveauTableau = malloc((nb->Taille + 1) * sizeof(int));

    // Copie les bits existants
    for (int i = 0; i < nb->Taille; i++) {
        nouveauTableau[i] = nb->Tdigits[i];
    }

    // LSB
    nouveauTableau[nb->Taille] = 0;

    // Libérer l'ancien tableau et mettre à jour
    free(nb->Tdigits);
    nb->Tdigits = nouveauTableau;
    nb->Taille++;
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

BigBinary multiplicationEgyptienne(BigBinary a, BigBinary b) {
    // 1. Initialiser le résultat à 0
    BigBinary resultat = createZero();

    // 2. Faire des copies pour ne pas modifier les originaux
    BigBinary A = copierBigBinary(a);
    BigBinary B = copierBigBinary(b);

    // 3. Boucle tant que B > 0
    while (B.Signe != 0) {
        // Si B est impair (LSB == 1), on ajoute A au résultat
        if (!estPair(B)) {
            BigBinary temp = sumBigBinary(resultat, A);
            freeBigBinary(&resultat); // Libérer l'ancienne mémoire
            resultat = temp;
        }

        // A = A * 2
        multiplierPar2(&A);

        // B = B / 2
        divisePar2(&B);
    }

    // Nettoyage des copies
    freeBigBinary(&A);
    freeBigBinary(&B);

    return resultat;
}

// Algorithme binaire d'Euclide pour le PGCD
BigBinary pgcdBigBinary(BigBinary a, BigBinary b) {
    // Si PGCD(a, 0) = a
    if (b.Signe == 0) {
        return copierBigBinary(a);
    }

    // Si PGCD(b, 0) = b
    if (a.Signe == 0) {
        return copierBigBinary(b);
    }

    // Créer des copies
    BigBinary aCopy = copierBigBinary(a);
    BigBinary bCopy = copierBigBinary(b);

    // Compteur pour le facteur 2^k
    int facteur2 = 0;

    // Si a et b sont tous deux pairs, factoriser par 2
    while (estPair(aCopy) && estPair(bCopy)) {
        divisePar2(&aCopy);
        divisePar2(&bCopy);
        facteur2++;
    }

    while (aCopy.Signe != 0 && bCopy.Signe != 0) {
        // Si a est pair et b impair
        while (estPair(aCopy) && !estPair(bCopy)) {
            divisePar2(&aCopy);
        }

        // Si a est impair et b pair
        while (!estPair(aCopy) && estPair(bCopy)) {
            divisePar2(&bCopy);
        }

        // Si a et b sont impairs
        if (!estPair(aCopy) && !estPair(bCopy)) {
            // S'assurer que a >= b
            if (comparaisonInferieur(aCopy, bCopy)) {
                BigBinary temp = aCopy;
                aCopy = bCopy;
                bCopy = temp;
            }

            // a = a - b
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

    // Multiplier par 2^facteur2
    for (int i = 0; i < facteur2; i++) {
        multiplierPar2(&resultat);
    }

    return resultat;
}
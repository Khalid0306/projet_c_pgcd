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

// Fonction d'addition de deux grands entiers
BigBinary sumBigBinary(BigBinary a, BigBinary b) {
    BigBinary resultat;

    // Déterminer la taille maximale
    int maxLen = (a.Taille > b.Taille) ? a.Taille : b.Taille;

    // Allouer pour maxLen + 1 (pour la retenue finale)
    resultat.Tdigits = malloc((maxLen + 1) * sizeof(int));
    resultat.Taille = maxLen + 1;
    resultat.Signe = 1;  // Résultat positif (A, B ≥ 0)

    int retenue = 0;

    // Parcourir de DROITE à GAUCHE (du LSB au MSB)
    for (int i = 0; i < maxLen; i++)
    {
        // Index dans A et B (depuis la FIN du tableau)
        int indexA = a.Taille - 1 - i;
        int indexB = b.Taille - 1 - i;

        // Récupérer les bits (0 si hors limites)
        int bitA = (indexA >= 0) ? a.Tdigits[indexA] : 0;
        int bitB = (indexB >= 0) ? b.Tdigits[indexB] : 0;

        // Calcul de la somme avec retenue
        int somme = bitA + bitB + retenue;

        // Stocker dans resultat (index depuis la FIN)
        int indexResultat = resultat.Taille - 1 - i;
        resultat.Tdigits[indexResultat] = somme % BASE;
        retenue = somme / BASE;
    }

    // Stocker la retenue finale en tête (MSB)
    resultat.Tdigits[0] = retenue;

    // Ajuster la taille (supprimer le 0 de tête si pas de retenue)
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

//Fonction comparaison renvoi true si A==B Sinon renvoi false
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

//faire la fonction de comparaison inferieur, si A<B renvoi true sinon false
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

// Fonction de soustraction : A - B avec A >= B
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
    // Cas zéro ou nombre à 1 bit (Dans les deux cas division par zéro)
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
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
Boolean comparaisonEgal(BigBinary a, BigBinary b) {
	if (BigbinaryCompare(&a, &b) == 0)
		return true;
	else
		return false;
}
//faire la fonction de comparaison inferieur, si A<B renvoi true sinon false
Boolean comparaisonInferieur(BigBinary a, BigBinary b) {
    if (&a < &b) {
        return true;
    }
    else if (&b < &a) {
        return false;
    }
}
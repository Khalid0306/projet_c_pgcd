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

    // Comptons uniquement les caractères valides (’0’ou ’1’)
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

// Convertit un BigBinary en chaîne de caractères décimale
char* bigBinaryToDecimal(const BigBinary nb) {
    // Cas du zéro ou vide
    if (nb.Taille == 0 || (nb.Taille == 1 && nb.Tdigits[0] == 0) || nb.Signe == 0) {
        char *res = malloc(2 * sizeof(char));
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    // Allocation d'un buffer pour la chaîne décimale.
    // Taille max approx : nombre de bits + 2 (pour sécurité et signe)
    int cap = nb.Taille + 2;
    char *buffer = malloc(cap * sizeof(char));

    // On initialise la chaîne à "0"
    // Note : On stocke les chiffres à l'envers (Unités à l'index 0) pour faciliter le calcul
    int len = 1;
    buffer[0] = '0';

    // Algorithme "Double Dabble" simplifié : pour chaque bit, on double le nombre décimal actuel et on ajoute le bit.
    for (int i = 0; i < nb.Taille; ++i) {
        int bit = nb.Tdigits[i]; // On lit du MSB (poids fort) vers le LSB
        int carry = bit;         // On ajoute le bit courant après le décalage (x2)

        // On parcourt la chaîne décimale actuelle pour la multiplier par 2
        for (int j = 0; j < len; j++) {
            int val = (buffer[j] - '0') * 2 + carry;
            buffer[j] = (val % 10) + '0';
            carry = val / 10;
        }
        // Si une retenue reste à la fin, on agrandit le nombre
        while (carry > 0) {
            buffer[len] = (carry % 10) + '0';
            carry /= 10;
            len++;
        }
    }
    buffer[len] = '\0';

    // On inverse la chaîne pour l'avoir dans le bon ordre (MSB à gauche)
    for (int i = 0; i < len / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[len - 1 - i];
        buffer[len - 1 - i] = temp;
    }

    return buffer;
}

void displayBigBinary(BigBinary nb) {
    // 1. Affichage du signe
    if (nb.Signe == -1) {
        printf("-");
    }

    // 2. Gestion du cas zéro/vide
    bool estNul = true;
    if (nb.Taille > 0 && nb.Tdigits != NULL) {
        for (int i = 0; i < nb.Taille; ++i) {
            if (nb.Tdigits[i] != 0) {
                estNul = false;
                break;
            }
        }
    }

    if (estNul || nb.Signe == 0) {
        printf("Binaire: 0 | Decimal: 0\n");
        return;
    }

    // 3. Affichage Binaire
    printf("Binaire: ");
    for (int i = 0; i < nb.Taille; ++i) {
        printf("%d", nb.Tdigits[i]);
    }

    // 4. Conversion et Affichage Décimal
    char* decimalStr = bigBinaryToDecimal(nb);
    printf(" | Decimal: %s%s\n", (nb.Signe == -1 ? "-" : ""), decimalStr);

    // Important : Libérer la mémoire de la chaîne générée
    free(decimalStr);
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

// Modulo calcule A % N pour des BigBinary (binaire)
BigBinary moduloBigBinary(BigBinary a, BigBinary n) {
    // modulo par 0 n'existe pas
    if (n.Signe == 0) {
        fprintf(stderr, "Erreur: Modulo par zero interdit.\n");
        return createZero();
    }
    // si a =0 alors 0 % n =0
    if (a.Signe == 0) return createZero();

    // On travaille avec des valeurs positives pour le calcul
    // Pour le modulo, le signe n'est pas utile, reste soit positif.
    BigBinary R = copierBigBinary(a); // R = "reste" courant
    R.Signe = 1;
    BigBinary N = copierBigBinary(n); // n = diviseur
    N.Signe = 1;

    // Tant que R >= N, on peut encore retirer des "paquets" de N.
    // Objectif : arriver à un reste R < N.
    while (!comparaisonInferieur(R, N)) {

        // On cherche le plus grand k tel que 2^k * N qui reste <= R.
        // On approxime k par la différence de taille en bits.
        int diffTaille = R.Taille - N.Taille;
        if (diffTaille < 0) diffTaille = 0;

        // Créer N_shift = N << diffTaille  (donc N * 2^diffTaille)
        BigBinary N_shift = copierBigBinary(N);
        for (int i = 0; i < diffTaille; i++) {
            multiplierPar2(&N_shift); // décalage à gauche : *2
        }

        // Si on a décalé trop loin (N_shift > R), on revient d'un cran
        // N_shift = N_shift / 2
        if (comparaisonInferieur(R, N_shift)) {
            divisePar2(&N_shift);
        }

        // On sait que R >= N_shift donc la soustraction est autorisée
        BigBinary temp = subBigBinary(R, N_shift);
        freeBigBinary(&R); // On libère l'ancien R remplacé
        R = temp;

        // N_shift est temporaire donc on libère
        freeBigBinary(&N_shift);
    }

    freeBigBinary(&N); // Plus besoin de la copie N

    return R; // R < N ce qui équivaut au reste A % N
}

// Exponentiation Modulaire : calcule (base ^ exp) % mod pour des BigBinary
BigBinary exponentiationModulaire(BigBinary base, BigBinary exp, BigBinary mod) {

    // Début, le résultat vaut 1 (élément neutre de la multiplication).
    BigBinary resultat = createBigBinaryFromString("1");

    // On réduit la base modulo mod dès le début pour éviter des nombres trop grands.
    BigBinary b = moduloBigBinary(base, mod);

    // copie l'exposant pour pouvoir le modifier sans toucher à l'initial.
    BigBinary e = copierBigBinary(exp);

    // Algorithme d'exponentiation binaire (Square and Multiply)
    // On parcourt les bits de l'exposant du LSB vers le MSB (en utilisant divisePar2)

    while (e.Signe != 0) { // Tant que e > 0

        // Si le bit de poids faible de e vaut 1, on doit multiplier le résultat
        if (!estPair(e)) {

            // resultat = resultat * b
            BigBinary mult = multiplicationEgyptienne(resultat, b);

            // On libère l'ancien résultat avant de le remplacer
            freeBigBinary(&resultat);

            //On applique le modulo immédiatement pour rester dans des tailles raisonnables
            resultat = moduloBigBinary(mult, mod);

            // mult est temporaire, on peut le libérer
            freeBigBinary(&mult);
        }

        // b = (b * b) (mise au carré de la base)
        BigBinary carre = multiplicationEgyptienne(b, b);
        freeBigBinary(&b);

        // On réduit encore modulo mod pour éviter que b devienne trop grand
        b = moduloBigBinary(carre, mod);
        freeBigBinary(&carre);

        // On divise l'exposant par 2 (décalage à droite en binaire)
        divisePar2(&e);
    }
    // Libération des variables temporaires
    freeBigBinary(&b);
    freeBigBinary(&e);

    // À la fin, resultat contient (base^exp) % mod
    return resultat;
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
//Multiplication Egyptienne
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

// Modulo calcule A % N pour des BigBinary (binaire)
BigBinary moduloBigBinary(BigBinary a, BigBinary n) {
    // modulo par 0 n'existe pas
    if (n.Signe == 0) {
        fprintf(stderr, "Erreur: Modulo par zero interdit.\n");
        return createZero();
    }
    // si a =0 alors 0 % n =0
    if (a.Signe == 0) return createZero();

    // On travaille avec des valeurs positives pour le calcul
    // Pour le modulo, le signe n'est pas utile, reste soit positif.
    BigBinary R = copierBigBinary(a); // R = "reste" courant
    R.Signe = 1;
    BigBinary N = copierBigBinary(n); // n = diviseur
    N.Signe = 1;

    // Tant que R >= N, on peut encore retirer des "paquets" de N.
    // Objectif : arriver à un reste R < N.
    while (!comparaisonInferieur(R, N)) {

        // On cherche le plus grand k tel que 2^k * N qui reste <= R.
        // On approxime k par la différence de taille en bits.
        int diffTaille = R.Taille - N.Taille;
        if (diffTaille < 0) diffTaille = 0;

        // Créer N_shift = N << diffTaille  (donc N * 2^diffTaille)
        BigBinary N_shift = copierBigBinary(N);
        for (int i = 0; i < diffTaille; i++) {
            multiplierPar2(&N_shift); // décalage à gauche : *2
        }

        // Si on a décalé trop loin (N_shift > R), on revient d'un cran
        // N_shift = N_shift / 2
        if (comparaisonInferieur(R, N_shift)) {
            divisePar2(&N_shift);
        }

        // On sait que R >= N_shift donc la soustraction est autorisée
        BigBinary temp = subBigBinary(R, N_shift);
        freeBigBinary(&R); // On libère l'ancien R remplacé
        R = temp;

        // N_shift est temporaire donc on libère
        freeBigBinary(&N_shift);
    }

    freeBigBinary(&N); // Plus besoin de la copie N

    return R; // R < N ce qui équivaut au reste A % N
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
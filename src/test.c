//
// Created by khalid on 07/11/2025.
//

#include <stdio.h>
#include "grand_entier.h"

void printTestHeader(const char *testName) {
    printf("\n================================================\n");
    printf("  %s\n", testName);
    printf("================================================\n");
}

void printSubTestHeader(const char *subTestName) {
    printf("\n--- %s ---\n", subTestName);
}

int main() {
    printf("\n████████████████████████████████████████████████\n");
    printf("█  Début du test █\n");
    printf("████████████████████████████████████████████████\n");

    BigBinary A1 = createBigBinaryFromString("10101010101001110011101000111110100001011101001000101100011010110000111000000110100011101001");
    BigBinary B1 = createBigBinaryFromString("11001011011111111000110000111010000000110101011000000100000010110101101001100011110001011000");
    printf("✓ A1 et B1 initialisés\n");

    BigBinary A2 = createBigBinaryFromString("11001110111000001101101111110100110000001010101010001000000110010010001110000100001110010011");
    BigBinary B2 = createBigBinaryFromString("10110100101100011101100011110100101110111100000100111000110000001001000100110110100100110000");
    BigBinary C2 = createBigBinaryFromString("11100001000100000000100110010110010010100100111011011100001100000110011101101000101010010000");
    printf("✓ A2, B2, C2 initialisés\n");

    printTestHeader("TEST 1 : ADDITION A1 + B1");

    printf("A1 = ");
    displayBigBinary(A1);
    printf("B1 = ");
    displayBigBinary(B1);

    BigBinary somme_A1_B1 = sumBigBinary(A1, B1);
    printf("\nA1 + B1 = ");
    displayBigBinary(somme_A1_B1);

    printTestHeader("TEST 2 : COMPARAISONS");

    printSubTestHeader("Affichage des nombres");
    printf("A2 = ");
    displayBigBinary(A2);
    printf("B2 = ");
    displayBigBinary(B2);
    printf("C2 = ");
    displayBigBinary(C2);

    printSubTestHeader("A2 == B2");
    printf("Résultat : %s \n", comparaisonEgal(A2, B2) ? "true" : "false");

    printSubTestHeader("A2 == A2");
    printf("Résultat : %s \n", comparaisonEgal(A2, A2) ? "true" : "false");

    printSubTestHeader("A2 > C2");
    bool inf_A2_C2 = comparaisonInferieur(A2, C2);
    printf("A2 < C2 ? %s\n", inf_A2_C2 ? "true" : "false");
    printf("A2 > C2 ? %s\n", inf_A2_C2 ? "false" : "true");

    printSubTestHeader("Autres comparaisons");
    printf("B2 < A2 ? %s\n", comparaisonInferieur(B2, A2) ? "true" : "false");
    printf("B2 < C2 ? %s\n", comparaisonInferieur(B2, C2) ? "true" : "false");

    printTestHeader("TEST 3 : SOUSTRACTION");

    printSubTestHeader("A2 - B2");
    BigBinary diff_A2_B2 = subBigBinary(A2, B2);
    printf("A2 - B2 = ");
    displayBigBinary(diff_A2_B2);

    printSubTestHeader("A2 - C2");
    BigBinary diff_A2_C2 = subBigBinary(A2, C2);
    printf("A2 - C2 = ");
    displayBigBinary(diff_A2_C2);

    printSubTestHeader("C2 - A2 (test erreur)");
    BigBinary diff_C2_A2 = subBigBinary(C2, A2);
    if (diff_C2_A2.Tdigits != NULL) {
        printf("C2 - A2 = ");
        displayBigBinary(diff_C2_A2);
    }

    printSubTestHeader("Test avec A1 et B1");
    if (comparaisonInferieur(A1, B1)) {
        BigBinary diff_B1_A1 = subBigBinary(B1, A1);
        printf("B1 - A1 = ");
        displayBigBinary(diff_B1_A1);
        freeBigBinary(&diff_B1_A1);
    } else {
        BigBinary diff_A1_B1 = subBigBinary(A1, B1);
        printf("A1 - B1 = ");
        displayBigBinary(diff_A1_B1);
        freeBigBinary(&diff_A1_B1);
    }

    printTestHeader("TEST 4 : DIVISION PAR 2");

    printSubTestHeader("Division de A1");
    BigBinary A1_copy = createBigBinaryFromString("10101010101001110011101000111110100001011101001000101100011010110000111000000110100011101001");
    printf("A1         = ");
    displayBigBinary(A1_copy);
    divisePar2(&A1_copy);
    printf("A1 / 2     = ");
    displayBigBinary(A1_copy);
    divisePar2(&A1_copy);
    printf("A1 / 4     = ");
    displayBigBinary(A1_copy);

    printSubTestHeader("Division de B2");
    BigBinary B2_copy = createBigBinaryFromString("10110100101100011101100011110100101110111100000100111000110000001001000100110110100100110000");
    printf("B2         = ");
    displayBigBinary(B2_copy);
    divisePar2(&B2_copy);
    printf("B2 / 2     = ");
    displayBigBinary(B2_copy);

    printSubTestHeader("Division de C2");
    BigBinary C2_copy = createBigBinaryFromString("11100001000100000000100110010110010010100100111011011100001100000110011101101000101010010000");
    printf("C2         = ");
    displayBigBinary(C2_copy);
    divisePar2(&C2_copy);
    printf("C2 / 2     = ");
    displayBigBinary(C2_copy);

    printTestHeader("TEST 5 : COHÉRENCE");

    printSubTestHeader("(A1 + B1) - B1 = A1");
    BigBinary verif1 = subBigBinary(somme_A1_B1, B1);
    printf("(A1 + B1) - B1 = ");
    displayBigBinary(verif1);
    printf("A1             = ");
    displayBigBinary(A1);
    printf("Égaux ? %s\n", comparaisonEgal(verif1, A1) ? "True" : "False");

    printSubTestHeader("(A1 + B1) - A1 = B1");
    BigBinary verif2 = subBigBinary(somme_A1_B1, A1);
    printf("(A1 + B1) - A1 = ");
    displayBigBinary(verif2);
    printf("B1             = ");
    displayBigBinary(B1);
    printf("Égaux ? %s\n", comparaisonEgal(verif2, B1) ? "True" : "False");

    printTestHeader("TEST 6 : PGCD BINAIRE");

    printSubTestHeader("PGCD avec données du PDF");
    BigBinary PGCD_A = createBigBinaryFromString("11110001111000100111100100001010110100110010110000100111001100110010111001010111101101110");
    BigBinary PGCD_B = createBigBinaryFromString("11100110011111011000000111111110110001110000011001111100111011011010101110110111000110111");

    printf("PGCD_A = ");
    displayBigBinary(PGCD_A);
    printf("PGCD_B = ");
    displayBigBinary(PGCD_B);

    BigBinary pgcd_result = pgcdBigBinary(PGCD_A, PGCD_B);
    printf("\nPGCD(A, B) = ");
    displayBigBinary(pgcd_result);

    printSubTestHeader("Test simple : PGCD(51, 57) = 3");
    BigBinary test_a = createBigBinaryFromString("110011");  // 51
    BigBinary test_b = createBigBinaryFromString("111001");  // 57
    printf("PGCD(51, 57) = ");
    BigBinary pgcd_simple = pgcdBigBinary(test_a, test_b);
    displayBigBinary(pgcd_simple);  // Devrait afficher 11 (3 en binaire)

    printSubTestHeader("Modulo A % N");
    BigBinary A = createBigBinaryFromString("10101"); // 21
    BigBinary N = createBigBinaryFromString("110");   // 6
    BigBinary R = moduloBigBinary(A, N);
    printf("21 %% 6 = ");
    displayBigBinary(R); // attendu: 11
    freeBigBinary(&A);
    freeBigBinary(&N);
    freeBigBinary(&R);

    printTestHeader("LIBÉRATION MÉMOIRE");

    freeBigBinary(&A1);
    freeBigBinary(&B1);
    freeBigBinary(&A2);
    freeBigBinary(&B2);
    freeBigBinary(&C2);
    freeBigBinary(&somme_A1_B1);
    freeBigBinary(&diff_A2_B2);
    freeBigBinary(&diff_A2_C2);
    if (diff_C2_A2.Tdigits != NULL) freeBigBinary(&diff_C2_A2);
    freeBigBinary(&A1_copy);
    freeBigBinary(&B2_copy);
    freeBigBinary(&C2_copy);
    freeBigBinary(&verif1);
    freeBigBinary(&verif2);
    freeBigBinary(&PGCD_A);
    freeBigBinary(&PGCD_B);
    freeBigBinary(&pgcd_result);
    freeBigBinary(&test_a);
    freeBigBinary(&test_b);
    freeBigBinary(&pgcd_simple);

    printf("Mémoire libérée\n");

    printf("\n████████████████████████████████████████████████\n");
    printf("█         TESTS TERMINÉS              █\n");
    printf("████████████████████████████████████████████████\n\n");

    return 0;
}
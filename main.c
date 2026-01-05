//
// Main de présentation - Projet BigBinary
// Trinôme 7
//

#include <stdio.h>
#include <stdlib.h>
#include"grand_entier.h"

void afficher_section(const char* titre) {
    printf("\n");
    printf("================================================================\n");
    printf("%s\n", titre);
    printf("================================================================\n");
}

void afficher_test(const char* nom) {
    printf("\n--- %s ---\n", nom);
}

int main(void) {
    printf("\n");
    printf("================================================================\n");
    printf("        PROJET C - DEMONSTRATION \n");
    printf("================================================================\n");

    // ================================================================
    // PHASE 1 : OPERATIONS DE BASE
    // ================================================================

    afficher_section("PHASE 1 : OPERATIONS DE BASE");

    // Initialisation des nombres de test (données du PDF)
    BigBinary A1 = createBigBinaryFromString(
        "10101010101001110011101000111110100001011101001000101100011010110000111000000110100011101001"
    );
    BigBinary B1 = createBigBinaryFromString(
        "11001011011111111000110000111010000000110101011000000100000010110101101001100011110001011000"
    );

    BigBinary A2 = createBigBinaryFromString(
        "11001110111000001101101111110100110000001010101010001000000110010010001110000100001110010011"
    );
    BigBinary B2 = createBigBinaryFromString(
        "10110100101100011101100011110100101110111100000100111000110000001001000100110110100100110000"
    );
    BigBinary C2 = createBigBinaryFromString(
        "11100001000100000000100110010110010010100100111011011100001100000110011101101000101010010000"
    );

    printf("\nNombres initialises : %d bits\n", A1.Taille);

    // Test 1 : Addition
    afficher_test("Test 1 : Addition");
    printf("A1 = "); displayBigBinary(A1);
    printf("B1 = "); displayBigBinary(B1);

    BigBinary somme = sumBigBinary(A1, B1);
    printf("\nA1 + B1 = "); displayBigBinary(somme);

    // Test 2 : Comparaisons
    afficher_test("Test 2 : Comparaisons");
    printf("A2 = "); displayBigBinary(A2);
    printf("B2 = "); displayBigBinary(B2);
    printf("C2 = "); displayBigBinary(C2);

    printf("\nA2 == B2 ? %s\n", comparaisonEgal(A2, B2) ? "Vrai" : "Faux");
    printf("A2 == A2 ? %s\n", comparaisonEgal(A2, A2) ? "Vrai" : "Faux");
    printf("A2 < C2  ? %s\n", comparaisonInferieur(A2, C2) ? "Vrai" : "Faux");
    printf("B2 < A2  ? %s\n", comparaisonInferieur(B2, A2) ? "Vrai" : "Faux");

    // Test 3 : Soustraction
    afficher_test("Test 3 : Soustraction");
    BigBinary diff = subBigBinary(A2, B2);
    printf("A2 - B2 = "); displayBigBinary(diff);

    // Test 4 : Division par 2
    afficher_test("Test 4 : Division par 2");
    BigBinary test_div = createBigBinaryFromString("1010011"); // 83
    printf("Nombre initial (83) = "); displayBigBinary(test_div);

    divisePar2(&test_div);
    printf("Apres division / 2  = "); displayBigBinary(test_div);

    divisePar2(&test_div);
    printf("Apres division / 4  = "); displayBigBinary(test_div);

    // Test 5 : Cohérence
    afficher_test("Test 5 : Coherence");
    BigBinary verif = subBigBinary(somme, B1);
    printf("Calcul : (A1 + B1) - B1\n");
    printf("Resultat = "); displayBigBinary(verif);
    printf("A1       = "); displayBigBinary(A1);
    printf("Egalite  ? %s\n", comparaisonEgal(verif, A1) ? "OK" : "ERREUR");

    // ================================================================
    // PHASE 2 : ALGORITHMES AVANCES
    // ================================================================

    afficher_section("PHASE 2 : ALGORITHMES AVANCES");

    // Test 6 : PGCD (Algorithme Binaire d'Euclide)
    afficher_test("Test 6 : PGCD ");

    BigBinary PGCD_A = createBigBinaryFromString(
        "11110001111000100111100100001010110100110010110000100111001100110010111001010111101101110"
    );
    BigBinary PGCD_B = createBigBinaryFromString(
        "11100110011111011000000111111110110001110000011001111100111011011010101110110111000110111"
    );

    printf("A = "); displayBigBinary(PGCD_A);
    printf("B = "); displayBigBinary(PGCD_B);

    BigBinary pgcd_result = pgcdBigBinary(PGCD_A, PGCD_B);
    printf("\nPGCD(A, B) = "); displayBigBinary(pgcd_result);

    // Vérification avec exemple simple
    printf("\nVerification : PGCD(54, 36)\n");
    BigBinary test_a = createBigBinaryFromString("110110"); // 54
    BigBinary test_b = createBigBinaryFromString("100100"); // 36
    BigBinary pgcd_simple = pgcdBigBinary(test_a, test_b);
    printf("PGCD(54, 36) = "); displayBigBinary(pgcd_simple);
    printf("Attendu : 18\n");

    // Test 7 : Modulo
    afficher_test("Test 7 : Operation Modulo");

    BigBinary MOD_A = createBigBinaryFromString(
        "11001110000111010001010110000101101001111000010001001110011100110100000110000010011011010"
    );
    BigBinary MOD_B = createBigBinaryFromString(
        "11001001100000010001111000000101111110010111111011101010001000010100010001111111010011010"
    );

    printf("A = "); displayBigBinary(MOD_A);
    printf("B = "); displayBigBinary(MOD_B);

    BigBinary mod_result = moduloBigBinary(MOD_A, MOD_B);
    printf("\nA mod B = "); displayBigBinary(mod_result);

    // Vérification simple
    printf("\nVerification : 21 mod 6\n");
    BigBinary mod_a = createBigBinaryFromString("10101"); // 21
    BigBinary mod_b = createBigBinaryFromString("110");   // 6
    BigBinary mod_simple = moduloBigBinary(mod_a, mod_b);
    printf("21 mod 6 = "); displayBigBinary(mod_simple);
    printf("Attendu : 3\n");

    // Test 8 : Multiplication Égyptienne
    afficher_test("Test 8 : Multiplication Egyptienne");

    BigBinary mul_a = createBigBinaryFromString("1101"); // 13
    BigBinary mul_b = createBigBinaryFromString("101");  // 5
    printf("A = "); displayBigBinary(mul_a);
    printf("B = "); displayBigBinary(mul_b);

    BigBinary mul_result = multiplicationEgyptienne(mul_a, mul_b);
    printf("\nA x B = "); displayBigBinary(mul_result);
    printf("Attendu : 65\n");

    // Test 9 : Exponentiation Modulaire
    afficher_test("Test 9 : Exponentiation Modulaire");

    BigBinary EXP_M = createBigBinaryFromString(
        "101100110000001100011011000000110010011101100100101001010111010010001011110110001001101100"
    );
    BigBinary EXP_EXP = createBigBinaryFromString("1001001000010111");
    BigBinary EXP_MOD = createBigBinaryFromString(
        "101001110001111101100000111000110001110100000111111010001011100101101100101101101011000"
    );

    printf("Base M      = "); displayBigBinary(EXP_M);
    printf("Exposant    = "); displayBigBinary(EXP_EXP);
    printf("Modulo N    = "); displayBigBinary(EXP_MOD);

    printf("\nCalcul en cours...\n");
    BigBinary exp_result = exponentiationModulaire(EXP_M, EXP_EXP, EXP_MOD);
    printf("M^exp mod N = "); displayBigBinary(exp_result);

    // Vérification simple
    printf("\nVerification : 2^5 mod 13\n");
    BigBinary base = createBigBinaryFromString("10");   // 2
    BigBinary exp  = createBigBinaryFromString("101");  // 5
    BigBinary mod  = createBigBinaryFromString("1101"); // 13
    BigBinary exp_simple = exponentiationModulaire(base, exp, mod);
    printf("2^5 mod 13 = "); displayBigBinary(exp_simple);
    printf("Attendu : 6\n");

    // ================================================================
    // LIBERATION MEMOIRE
    // ================================================================

    printf("\nLiberation de la memoire...\n");

    freeBigBinary(&A1);
    freeBigBinary(&B1);
    freeBigBinary(&A2);
    freeBigBinary(&B2);
    freeBigBinary(&C2);
    freeBigBinary(&somme);
    freeBigBinary(&diff);
    freeBigBinary(&test_div);
    freeBigBinary(&verif);
    freeBigBinary(&PGCD_A);
    freeBigBinary(&PGCD_B);
    freeBigBinary(&pgcd_result);
    freeBigBinary(&test_a);
    freeBigBinary(&test_b);
    freeBigBinary(&pgcd_simple);
    freeBigBinary(&MOD_A);
    freeBigBinary(&MOD_B);
    freeBigBinary(&mod_result);
    freeBigBinary(&mod_a);
    freeBigBinary(&mod_b);
    freeBigBinary(&mod_simple);
    freeBigBinary(&mul_a);
    freeBigBinary(&mul_b);
    freeBigBinary(&mul_result);
    freeBigBinary(&EXP_M);
    freeBigBinary(&EXP_EXP);
    freeBigBinary(&EXP_MOD);
    freeBigBinary(&exp_result);
    freeBigBinary(&base);
    freeBigBinary(&exp);
    freeBigBinary(&mod);
    freeBigBinary(&exp_simple);

    printf("Memoire liberee.\n");

    printf("\n");
    printf("================================================================\n");
    printf("                  DEMONSTRATION TERMINEE\n");
    printf("================================================================\n\n");

    return 0;
}
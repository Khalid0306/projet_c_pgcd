# Projet BigBinary – Calculs en Précision Arbitraire

Ce projet consiste en l’implémentation d’une bibliothèque en **C** permettant de manipuler des **grands entiers binaires** (au-delà de 128 bits).  
Il inclut des opérations arithmétiques fondamentales ainsi que des algorithmes avancés utilisés en **cryptographie**, tels que le **PGCD** et l’**exponentiation modulaire**.

**Trinôme 7**

---

## Fonctionnalités

### Opérations de base
- **Structure `BigBinary`** : gestion dynamique de la taille et du signe.
- **Arithmétique** :
  - Addition
  - Soustraction
  - Multiplication (méthode égyptienne)
- **Comparaisons** :
  - Égalité
  - Inférieur strict
- **Opérations bit à bit** :
  - Décalage à gauche (multiplication par 2)
  - Décalage à droite (division par 2)

---

### Algorithmes avancés
- **PGCD** : implémentation de l’algorithme binaire d’Euclide.
- **Modulo** : calcul du reste de la division entière.
- **Exponentiation modulaire** : calcul efficace de  
  \[
  base^{exp} \bmod n
  \]

---

## Installation et Exécution

### Prérequis
- Compilateur C (**GCC** ou **Clang**)
- **CMake** version 3.26 ou supérieure

---

### Lancement

Compilation et exécution manuelles :

```bash
mkdir build
cd build
cmake ..
make
./projet_c_pgcd
```
Auteurs : 
Khalid
Yannis
Arwin


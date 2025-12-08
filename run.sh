#!/bin/bash

# Créer le dossier build s'il n'existe pas
if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake ..
else
    cd build
fi

# Compiler et exécuter
make && ./projet_c_pgcd
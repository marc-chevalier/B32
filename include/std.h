#pragma once

/**
* Un bloc fait 32 bits, c'est l'atome chiffrable.
* Une pièce fait 4 bits, c'est la taille de la SBox.
* Il y a donc BLOC_LENGTH/PIECE_LENGTH pièces par blocs
**/

#define BLOC_LENGTH 32
#define PIECE_LENGTH 4

/*
 * Pokedex.h
 *
 * Base de datos de todos los Pokemons
 */

#ifndef PLAYERCLASS_POKEDEX_POKEDEX_H_
#define PLAYERCLASS_POKEDEX_POKEDEX_H_

/****************** INCLUDES ******************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>	// Incluye el conjunto de algoritmos de la libreria STL del cual usaremos los iteradores

/****************** STRUCS ******************/
struct Stats {				// Estructura para las estad˙êticas de los Pokemon
	float health;
	float attack;
	float defense;
	float attack_x;
	float defense_x;
	float velocity;
	float weight;
	float heigh;
	float captured_indice;
	float base_exp;
};

struct MoveLevel {			// Estructura que almacena el nombre de un movimiento con su correspondiente nivel de aprendizaje
	std::string name;
	int level;
};

struct Evolution {			// Estructura que almacena el nombre y nivel de la evoluciÛn
	std::string name;
	int level;
};

struct PokemonData {		// Estructura para los datos de cada Pokemon
	std::string name;
	std::string number;
	std::vector<std::string> types;
	int growth_curve;	// 0 = Parabolica, 1 = Lenta, 2 = Media, 3 = Rapida
	Stats stats;
	int hability;		// La habilidad se determina con un integer (haciendo referencia al txt de habilidades), y su efecto se ejecuta en el mismo codigo a partir de determinar si el Pokemon tiene determianda habilidad
	std::vector<MoveLevel> moves;	// Cada movimiento se almacena con el nivel en que se puede aprender
	Evolution evolution;
};

struct boolFloat {			// Estructura que almacenaun bool y un float
	bool defeated;
	float damage;
};

/****************** FUNCTIONS ******************/
PokemonData findPokemon(std::string pokemon);

/****************** CONST ******************/
extern const std::vector<std::vector<float>> growth;	// Vector que alamacena todas las curvas de crecimiento

/****************** VARIABLES ******************/
extern std::vector<PokemonData> pokedex;			// Vector que contiene a todos los Pokemon

#endif /* PLAYERCLASS_POKEDEX_POKEDEX_H_ */

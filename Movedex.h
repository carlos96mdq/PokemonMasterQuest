/*
 * Movedex.h
 *
 * Base de datos de los Movimientos
 */

#ifndef PLAYERCLASS_POKEMONCLASS_MOVECLASS_MOVEDEX_H_
#define PLAYERCLASS_POKEMONCLASS_MOVECLASS_MOVEDEX_H_

/****************** INCLUDES ******************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>	// Incluye el conjunto de algoritmos de la libreria STL del cual usaremos los iteradores

/****************** STRUCS ******************/
struct Type {	// Estructura donde se indican todos los tipos y contra que tipos son efectivos
	std::string name;
	std::vector<std::string> effective;
};

struct Move {			// Estructura para los datos de cada Movimiento
	std::string name;
	std::string type;
	std::string clas;
	int power;		// 0 = no hace daño
	int accuracy;	// 0 = no tiene precisión
	int objetive;	// 0 = usuario, 1 = enemigo, 2 = enemigos, 3 = equipo, 4 = todos
	int priority;	// Prioridad -6 a +6 (0 inclusive)
	int critic;		// Aumento de critico, empieza en 0 y aumenta de +2
	bool contact;
	bool sonic;
	bool effect;				// Indica true si tiene efecto
	float effect_probability;	// = 0.0 no entra, < 1.0 normal, 1.0 acierta, > 1.0 y <= 2.0 propio
	std::string effect_1;
	std::vector<std::string> effect_2;
	float effect_3;
	std::string effect_description;
};

/****************** FUNCTIONS ******************/
Move findMove(std::string move_chosed);													// Función para encontrar movimientos a partir del nombre
float getEffectiveness(std::string move_type, std::vector<std::string> pokemon_types);	// Función para obtener la efectividad de un movimiento
int getPriority(std::string move_chosed);												// Funcón que devuelve el valor de prioridad

/****************** MOVEDEX ******************/
extern std::vector<Move> movedex;	// Vector que contiene a todos los Movimientos

#endif /* PLAYERCLASS_POKEMONCLASS_MOVECLASS_MOVEDEX_H_ */

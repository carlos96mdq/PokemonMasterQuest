/*
 * Player.h
 *
 *  Clase para instanciar cada nuevo jugador
 */

#ifndef PLAYERS_PLAYER_H_
#define PLAYERS_PLAYER_H_

/****************** INCLUDES ******************/
#include <string>
#include <iostream>
#include "Pokemon.h"		// Incluye las clases para instanciar Pokemons

/****************** CLASS ******************/
class Player {
	friend void battle(std::vector<Player> &players);		// Función para manjear las peleas contra salvajes y entrenadores
	friend void pokemonCenter(std::vector<Player> &players);// Función para curar Pokemon y modificar team
	friend void administrateTeam(std::vector<Player>& players);	// Función para modificar team
private:
	std::string name;
	std::vector<Pokemon> pokemons;		// Lista con todos los Pokemon del Jugador
	std::vector<int> team;				// Integer que indica ubicaci en vector pokemons los Pokemons en el team
	int active_pokemon;					// Integer que indica ubicaci en vector pokemons al Pokemon activo
	bool defeated;						// Es verdadero cuando el jugador tiene su team completo debilitado
public:
	Player(std::string name);
	virtual ~Player();
	void addPokemon(Pokemon pokemon);					// Agregar nuevo Pokemon a lista de Pokemons
	bool capturePokemon(Pokemon &captured_pokemon);		// Intenta capturar un Pokemon salvaje
	void changeTeam();									// Intercambia Pokemons del team por de la PC
	void giveObject();									// Se le da un objeto a alg佖 Pokemon del team
	void gainExp(float exp);							// Al ganar experiencia la distribuye acorde a la participaci
	void selectActive();								// Elegir el Pokemon activo del team
	bool isTeamDefeated();								// Verifica si todos los Pokemon del team se encuentran debilitados, y de estarlos, debilita al jugador
	Pokemon getTeamPokemon(int i);						// Me devuelve un Pokemon del team
	std::string getName();								// Devuelve el nombre del Jugador
	void displayPokemons();								// Muestra la lista de Pokemons
	int displayTeam();									// Muestra solo a los Pokemons del equipo actual
};

#endif /* PLAYERS_PLAYER_H_ */

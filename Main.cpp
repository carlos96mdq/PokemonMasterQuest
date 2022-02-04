//============================================================================
// Name        : PokemonMasterQuest.cpp
// Author      : Carlos Piccolini
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Pokemon Master Quest juego de mesa.
/*
 * El objetivo de esta versi es el de funcionar como un hibrido entre el
 * juego de mesa para realizar las cuentas. No se busca que guie a los
 * jugadores totalmente en su viaje, sino acomparlos en todos los calculos
 * realizados durante cada batalla pokemon.
 */
//============================================================================

/****************** INCLUDES ******************/
#include <iostream>
#include <iomanip>
#include <wchar.h>
#include <locale.h>
#include "Player.h"		// Incluye las clases para instanciar Jugadores

/****************** VARIABLES ******************/
std::vector<Player> players {};	// Donde se alamacenan todos los jugadores
int players_quantity {0};		// Donde se alamacena la cantidad de jugadores
int eventChoice {};				// Donde se almacena el evento seleccionado
bool playing {true};

/****************** FUNCTIONS DECLARATIONS ******************/
void newGame();
// Por ahora estas funciones no se usan
/*	Por ahora no se usan
void newZone();
void newEvent();
*/

/****************** MAIN ******************/
int main() {
	// Establecer el idioma a español
	setlocale(LC_ALL, "spanish");
	/****************** CARGAR PARTIDA ******************/
	/****************** JUEGO NUEVO ******************/
	newGame();
	/****************** LOOP ZONAS ******************/
	while(playing) {
		std::cout << "Seleccione el evento a ejecutarse: "
				  << std::endl
				  << std::setw(10) << std::left << "1 Ruta"
				  << std::setw(20) << std::left << "2 Centro Pokemon"
				  << std::setw(20) << std::left << "3 Cambio Equipo"
				  << std::setw(10) << std::left << "4 Gimnasio"
				  << std::endl;
		std::cin >> eventChoice;	// Se elije un evento
		std::cout << std::endl;
		switch(eventChoice) {		// Se prosigue acorde al evento elegido
			case 1:	// Ruta
				battle(players);
				break;
			case 2:	// CP
				pokemonCenter(players);
				break;
			case 3:	// Modificar team y usar objetos
				administrateTeam(players);
				break;
		}	
	}

	/*
	while(playing) {
		newEvent();
	}
	*/
	/****************** FIN ******************/
	return 0;
}

/****************** FUNCTIONS DEFINITIONS ******************/

void newGame() {
	std::string name_temp {};

	std::cout << std::setw(40) << std::right << "Pokemon Master Quest v0.1" << std::endl << std::endl;

	while(players_quantity < 1 || players_quantity > 5) {	// Se pregunta e indica la cantidad de jugadores
		std::cout << "Indique la cantidad de jugadores (de 1 a 5 jugadores): ";
		std::cin >> players_quantity;
		std::cout << std::endl;
		if(players_quantity < 1 || players_quantity > 5)
			std::cout << "La cantidad de jugadores indicada no es válida" << std::endl << std::endl;
	}

	for(int i = 0; i < players_quantity; i++) {				// Se crean los jugadores
		std::cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
		std::cin >> name_temp;
		players.push_back(Player (name_temp));
	}

	for(int i = 0; i < players_quantity; i++) {				// Se le asigna a cada jugador un Pokemon inicial
		std::cout << "Indique el nombre del pokemon inicial de "
				  << players.at(i).getName() << ": ";
		std::cin >> name_temp;
		std::cout << std::endl;
		players.at(i).addPokemon(Pokemon (findPokemon(name_temp), 1));
		// Esto solo está para el debuggeo
		players.at(i).displayPokemons();
		players.at(i).displayTeam();
		std::cout << std::endl;
	}

	// Se le asigna a cada jugador una lista de objetos
}

// Por ahora estas funciones no se usan
/*
void newZone() {
	int event {0};				// Para elegir el evento
	bool event_valid {false};	// Para verificar que se eligi・un evento v疝ido
	std::cout << std::left << "Comienza nueva zona" << std::endl;
	while(!event_valid) {		// Selecciono un tipo de zona
		std::cout << "La siguiente zona es una Ruta (1) o un Pueblo (2): ";
		std::cin >> event;
		if(event == 1 || event == 2) {
			event_valid = true;
			std::cout << "Evento v疝ido" << std::endl;
		} else std::cout << "Evento no v疝ido" << std::endl;
	}
	switch(event) {				// Dependiendo la zona procedo con el evento
		case 1:		// Ruta
			std::cout << "Evento de Ruta" << std::endl;
			for(int i = 0; i < players_quantity; i++) {
				std::cout << "Evento del jugador " << players.at(i).getName() << std::endl;
			}
			break;
		case 2:		// Pueblo o Ciudad
			std::cout << "Evento de Ciudad" << std::endl;
			break;
	}


}

void newEvent() {
	int event {0};				// Para elegir el evento
	bool event_valid {false};	// Para verificar que se eligi・un evento v疝ido
	while(!event_valid) {		// Selecciono un tipo de evento
		std::cout << "Indique el n伹ero de evento: " << std::endl
				  << std::setw(5) << ' ' << "1. Batalla Individual" << std::endl
				  << std::setw(5) << ' ' << "2. Centro Pokemon" << std::endl
				  << std::setw(5) << ' ' << "3. Gimnasio" << std::endl;
		std::cin >> event;
		if(event == 1 || event == 2 || event == 3) {
			event_valid = true;
			std::cout << "Evento v疝ido" << std::endl;
		} else std::cout << "Evento no v疝ido" << std::endl;
	}
}
*/

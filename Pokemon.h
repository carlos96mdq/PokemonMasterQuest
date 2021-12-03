/*
 * Pokemon.h
 *
 *  Clase para instanciar cada nuevo Pokemon
 */

#ifndef PLAYERCLASS_POKEMON_H_
#define PLAYERCLASS_POKEMON_H_

/****************** INCLUDES ******************/
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>					// Se incluye para usar la funci pow()
#include "Pokedex.h"				// De aqu・se obtiene la informaci de cada Pokem creado
#include "Movedex.h"	// De aqu・se obtiene la informaci sobre cada movimiento

/****************** CLASS ******************/
class Pokemon {
	friend std::ostream &operator<<(std::ostream &os, const Pokemon &poke);	// Operator overload para mostrar en pantalla todos los datos del Pokemon solo con el oeprador <<
private:
	PokemonData info {};
	float health;		// Toda esta lista de stats son los actuales del Pokemon, en base a la info y el nivel
	float attack;
	float defense;
	float attack_x;
	float defense_x;
	float velocity;
	float attack_mod;	// Modificadores que alteran las estad﨎ticas. Van de a x1.4 Desaaprecen cuando el pokemon sale de la batalla.
	float defense_mod;
	float attack_x_mod;
	float defense_x_mod;
	float velocity_mod;
	float accuracy_mod;	// Van de a x1.3
	float evasion_mod;
	int critic_mod;		// Va de a +2 ya que no se puede bajar
	float damage;		// El da recibido acumulado. Cuando iguala o supera al health, el Pokemon es derrotado
	int level;			// Nivel actual del Pokemon
	bool savage;		// Indica si es un Pokemon Salvaje o tiene Entrenador
	float exp;			// Experiencia acumualda del Pokemon
	bool defeated;		// Indica si un Pokemon est・debilitado o no
	std::string state;	// Indica el estado permanente (Congelado, Dormido, Envenenado, Envenenado Gravemente, Paralizado, Quemado)
	int sleep_counter;	// Contador para indicar la cantidad de turnos Dormido
	int poisoned_counter;// Contador para indicar la cantidad d eturnos Envenenado Gravemente
	bool confused;		// Indica verdadero si el Pokemon se encuentra Confundido
	int confused_counter;// Contador para indicar la cantidad de turnos Confundido
	bool seeded;		// Indica verdadero si el Pokemon se encuentra Drenado
	bool flinched;		// Indica verdadero si el Pokemon se encuentra Amedrentado
	bool light_screen;	// Indica verdadero si el Pokemon se encuentra bajo la influencua de Pantalla de Luz
	int light_screen_counter;// Indica la cantidad de turnos que Pantalla de Luz lleva activado
	bool safeguard;		// Indica verdadero si el Pokemon se encuentra bajo la influencua de Velo Sagrado
	int safeguard_counter;// Indica la cantidad de turnos que Velo Sagrado lleva activado
	bool tailwind;		// Indica verdadero si el Pokemon se encuentra bajo la influencua de Viento Af匤
	int tailwind_counter;// Indica la cantidad de turnos que Viento Afin lleva activado
	bool toxic_spikes;	// Indica verdadero si en el campo del Pokemon hay Púas Tóxicas
	bool toxic_spikes_plus;	// Indica verdadero si en el campo del Pokemon hay dos tandas de Púas Tóxicas
	std::vector<std::string> moves;	// Los movimientos actuales del Pokemon. Todos son strings, porque luego con otro método se buscara los stats del movimiento para los c疝culos de da y efectos en batalla
public:
	Pokemon();							// Empty constrcutor
	Pokemon(PokemonData poke, int level, bool savage=true);	// Uso un Pokemon del Pokedex, le digo el nivel y por default empieza con la experiencia de su nivel
	virtual ~Pokemon();
	float statRefresh(float stat);		// Es invocado para actualizar un stat que no sea health
	void statsRefresh();				// Es invocado para actualizar los stats en base a atributos del Pokemon
	void modifierRefresh();				// Es invocado para actualizar los modificadores
	void temporalStatusRefresh();		// Es invocado para curar todos los estados ef匇eros, como Confundido o Enamorado
	void campusStatusRefresh();			// Es invocado para curar todos los efectos de campo
	void passCampusStatus(Pokemon &last_pokemon);	// Es invocado para pasar los estados de campo al siguiente Pokemon en entrar
	void domated();						// Pone en false el savage
	void newMove(bool newPokemon=false, bool evolutionMove=false);// Agrega un nuevo Movimiento a los movimientos conocidos
	void receiveObject(int object);		// Se le da al Pokemon un objeto (el cual puede ser una piedra evolutiva
	void evolve();						// El Pokemon evoluciona
	void levelUp();						// Es invocado para subir de nivel
	void gainExp(float gained_exp);		// Es invocado para ganar experiencia
	float giveExp();					// Se entrega la experiencia por ser derrotado
	void counterUp();						// Aumenta todos los contadores temporales
	void useMove(Pokemon &objetive, std::string move);	// Es invocado para utilizar un movimiento
	void ejecuteMove(Pokemon &objetive, Move &move_info);// Es invocado por useMovepara ejecutar da y efectos del movimiento
	float receiveMove(Move &move_info, int accuracy_dice=20, int user_level=1, float user_attack=0.0, float user_attack_mod=0.0, float user_velocity=0, float stab=1.0, float hability_bonus=1.0);	// Es invocado por ejecuteMove para termianr de ejecutar un movimiento
	boolFloat receiveDamage(float received_damage=0.0);	// Es invocado por receiveMove para aplicar el da recibido, si el da es 0 verifica si se sufre alg佖 da por estados
	void receiveEffect(Move &move_info);				// Es invocado para recibir efectos de movimientos
	void cureDamage(float healed=0.0);	// El Pokemon se cura da, si el valor curado es 0 se cura al m痊imo
	void cureState(std::string curedState="All");	// El Pokemon se cura un estado, si el valor es All se cura de todos
	void cureFlinch();					// Cura el amedrentamiento
	float getActualHealth();			// Devuelve la saludad actual del objetivo (health - damage)
	float getMaxHealth();				// Devuelve la salud maxima del pokemon (health)
	float getVelocity();
	float getRatio();
	int getHability();					// Devuelve el numero correspondiente a la habildiad del Pokemon
	float getExp();						// Devuelve la cantidad de experiencia acumulada
	std::string getMove(int i);
	bool isSeeded();					// Devuelve true si el Pokemon se encuentra Drenado
	bool isFlinched();					// Devuelve true si el Pokemon se encuentra Amedrentado
	bool isDefeated();					// Devuelve true si el Pokemon se encuentra debilitado
	void displayName();
	void displayHealth();
	void displayMove(int i);			// Es invocado para mostrar un movimiento espec凬ico
	int displayMoves();					// Es invocado para mostrar los movimientos actuales del Pokemon
};

#endif /* PLAYERCLASS_POKEMON_H_ */

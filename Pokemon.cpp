/*
 * Pokemon.cpp
 */

/******************INCLUDES******************/
#include "Pokemon.h"

/******************METODOS******************/
Pokemon::Pokemon() {
}

Pokemon::Pokemon(PokemonData poke, int level, float exp)
	:info(poke), damage(0.0), level(level), exp(exp), defeated(false), state("None"), sleep_counter(0), flinched(false), moves() {
	statsRefresh();
	modifierRefresh();
	temporalStatusRefresh();
	campusStatusRefresh();
	newMove(true);
}

Pokemon::~Pokemon() {
	// TODO Auto-generated destructor stub
}

float Pokemon::statRefresh(float stat) {
	return (2 * stat * level * 4 / 100) + 5;	// Ese x4 aparece para compensar el crecimiento r疳ido de los Pokemon
}

void Pokemon::statsRefresh() {
	health = (2 * info.stats.health * level * 4 / 100) + level * 4 + 10;
	attack = statRefresh(info.stats.attack);
	defense = statRefresh(info.stats.defense);
	attack_x = statRefresh(info.stats.attack_x);
	defense_x = statRefresh(info.stats.defense_x);
	velocity = statRefresh(info.stats.velocity);
}

void Pokemon::modifierRefresh() {
	attack_mod = 1.0;
	defense_mod = 1.0;
	attack_x_mod = 1.0;
	defense_x_mod = 1.0;
	velocity_mod = 1.0;
	accuracy_mod = 1.0;
	evasion_mod = 1.0;
	critic_mod = 1;
}

void Pokemon::temporalStatusRefresh() {
	confused = false;
	confused_counter = 0;
	seeded = false;
	if(state == "Envenenado+")
		poisoned_counter = 1;
	else
		poisoned_counter = 0;
}

void Pokemon::campusStatusRefresh() {
	light_screen = false;
	light_screen_counter = 0;
	safeguard = false;
	safeguard_counter = 0;
	tailwind = false;
	tailwind_counter = 0;
	toxic_spikes = false;
	toxic_spikes_plus = false;
}

void Pokemon::passCampusStatus(Pokemon &last_pokemon) {
	light_screen = last_pokemon.light_screen;
	light_screen_counter = last_pokemon.light_screen_counter;
	safeguard = last_pokemon.safeguard;
	safeguard_counter = last_pokemon.safeguard_counter;
	tailwind = last_pokemon.tailwind;
	tailwind_counter = last_pokemon.tailwind_counter;
	toxic_spikes = last_pokemon.toxic_spikes;
	toxic_spikes_plus = last_pokemon.toxic_spikes_plus;

	if(toxic_spikes || toxic_spikes_plus) {	// Se activa el efecto de P俉s Ticas
		bool immune {false};
		bool poison {false};
		bool flying {false};
		bool levitation {false};

		for(auto type: info.types) {	// Inmunidad por tipo
			if(type == "Veneno") {
				immune = true;
				poison = true;
			}
			if(type == "Volador") {
				immune = true;
				flying = true;
			}
			if(type == "Acero")
				immune = true;
		}
		if(info.hability == 17)		// Inmunidad por habilidad Inmunidad
			immune = true;
		if(info.hability == 26) {	// Inmunidad por habilidad Levitaci
			immune = true;
			levitation = false;
		}
		if(!(state == "None") && !(state == "Envenenado"))		// Inmunidad por ya tener otro estado
			immune = true;
		if(!immune || !toxic_spikes_plus) {
			state == "Envenenado";
			std::cout << info.name << " se encuentra ahora Envenenado por el efecto de P俉s Ticas" << std::endl;
		} else if(!immune || toxic_spikes_plus) {
			state == "Envenenado+";
			poisoned_counter = 1;
			std::cout << info.name << " se encuentra ahora Gravemente Envenenado por el efecto de P俉s Ticas" << std::endl;
		} else
			std::cout << info.name << " es inmune al efecto de P俉s Ticas" << std::endl;

		if(poison && !flying && !levitation) {	// Despeja las P俉s Ticas
			toxic_spikes = false;
			std::cout << info.name << " ha esparcido las P俉s Ticas" << std::endl;
		}
	}
}

void Pokemon::newMove(bool newPokemon, bool evolutionMove) {
	int changedMove {};
	int temp_level {};
	int end_level {level};
	if(newPokemon)	// Verifico si estoy creando un nuevo Pokemon para tener ataques aprendidos en niveles anteriores al creado
		temp_level = 1;
	else if(evolutionMove) {
		temp_level = 0;
		end_level = 0;
	} else
		temp_level = level;
	std::vector<MoveLevel>::iterator it = std::find_if(info.moves.begin(), info.moves.end(), [&](MoveLevel move) {return temp_level == move.level;});
	for(auto j = temp_level; j < end_level + 1; j++) {	// Este for es para contemplar la creaci de un nuevo Pokemon
		for(auto i = 0; i < 3; i++ ) {		// Contempla hasta 3 movimientos nuevos por nivel
			if(it != info.moves.end()) {		// Verifico que s・haya alg佖 movimiento que se gana en ese nivel
				if(it->level == j) {	// Verifico si se aprende en este nivel (esta comprobaci est・m疽 que nada por el 2do movimiento
					std::cout << info.name << " puede aprender el movimiento " << it->name << std::endl;
					if(moves.size() <= 4) {		// Tengo lugar para aprender movimientos
						moves.push_back(it->name);	// Agrego el movimiento a la lista
						std::cout << info.name << " ha aprendido " << it->name << std::endl;
					} else {					// No tengo lugar para aprender movimientos
						std::cout << "Pero " << info.name << " ya no tiene lugar para aprender nudevos movimientos"
								  << std::endl
								  << "Desea reemplazar uno de los siguientes movimientos por " << it->name << "?"
								  << " (presione el numero del movimiento para reemplazarlo, o 0 para no aprenderlo"
								  << std::endl;
						displayMoves();
						std::cin >> changedMove;// Eligio un movimiento a cambiar o no aprender el nuevo movimiento
						if(changedMove == 0)
							std::cout << "No se ha aprendido el movimiento " << it->name << std::endl;
						else if(changedMove == 1 || changedMove == 2 || changedMove == 3 || changedMove == 4) {
							moves.at(changedMove) = it->name;
						} else
							std::cout << "No se ha ingresado un numero valido" << std::endl;
					}
					it = std::next(it, 1);		// Para poner el iterador en el siguiente movimiento almacenado por si puede aprender otro movimiento
				}
			}
		}
	}
}
void Pokemon::receiveObject(int object) {
	switch(object) {
		case 103:	// Piedra Trueno
			std::cout << "Se ha usado la Piedra Trueno con " << info.name << std::endl;
			if(info.evolution.level == object)
				evolve();
			else
				std::cout << "Este objeto no hace nada" << std::endl;
			break;
		case 104:	// Piedra Lunar
			std::cout << "Se ha usado la Piedra Lunar con " << info.name << std::endl;
			if(info.evolution.level == object)
				evolve();
			else
				std::cout << "Este objeto no hace nada" << std::endl;
	}
}

void Pokemon::evolve() {
	std::cout << "Parece que " << info.name << " esta evolucionando" << std::endl;
	std::cout << info.name << " ha evolucionado en " << info.evolution.name << std::endl;
	info = findPokemon(info.evolution.name);
	newMove(false, true);	// Para aprender movimientos de Evoluci
}

void Pokemon::levelUp() {
	level += 1;
	if(level >= info.evolution.level && level < 15)
		evolve();
	statsRefresh();
	newMove();
}

void Pokemon::gainExp(float gained_exp) {
	exp += gained_exp;
	std::cout << info.name << " ha ganado "
			  << gained_exp << " puntos de experiencia"
			  << std::endl;
	if(level < 15)
		if(exp >= growth.at(info.growth_curve).at(level - 1))
			levelUp();
}

float Pokemon::giveExp() {
	return info.stats.base_exp * level * 4;	// El 4 se agrega para compensar
}

void Pokemon::counterUp() {
	if(light_screen)			// Aumento contador de Pantalla de Luz
		light_screen_counter += 1;

	if(light_screen_counter == 5) {// Se acab・el efecto de Pantalla de Luz
		light_screen = false;
		light_screen_counter = 0;
	}

	if(safeguard)				// Aumento contador de Velo Sagrado
		safeguard_counter += 1;

	if(safeguard_counter == 5) {// Se acab・el efecto de Velo Sagrado
		safeguard = false;
		safeguard_counter = 0;
	}

	if(tailwind)				// Aumento contador de Viento Af匤
		tailwind_counter += 1;

	if(tailwind_counter == 4) {	// Se acab・el efecto de Viento Af匤
		tailwind = false;
		tailwind_counter = 0;
	}
}

void Pokemon::useMove(Pokemon &objetive, std::string move) {
	float accuracy_dice {};				// Valor del dado de 1-20, siendo 1 cr咜ico
	bool failed {false};				// Indica true si en este turno el pokemon no puede moverse por la Paralisis o la Confusi
	Move move_info (findMove(move));	// Creo referencia a la base de datos de movimientos

	if(state == "Dormido") {			// Verifico si estoy dormido
		std::cout << info.name << " se encuentra dormido" << std::endl;
		std::cout << "Lanza el dado para intentar despertarse: ";
		std::cin >> accuracy_dice;
		if(accuracy_dice < 4 + sleep_counter * 2) {
			std::cout << info.name << " se ha despertado" << std::endl;
			state = "None";
			sleep_counter = 0;
		} else {
			std::cout << info.name << " sigue dormido" << std::endl;
			sleep_counter++;
		}
	} else if(state == "Paralizado") {	// Verifico si puedo moverme por la paralisis
		std::cout << info.name << " se encuentra paralizado, es posible que no pueda moverse" << std::endl;
		std::cout << "Lanza el dado para intentar moverse: ";
		std::cin >> accuracy_dice;
		if(accuracy_dice > 15) {
			std::cout << info.name << " no puede moverse por la paralisis" << std::endl;
			failed = true;
		}
	}

	if(confused && !failed && !(state == "Dormido")) {	// Verifico si se autogolpea por la Confusi y si se libera de la Confusi
		std::cout << info.name << " se encuentra confundido" << std::endl;
		std::cout << "Lanza el dado para intentar moverse: ";
		std::cin >> accuracy_dice;
		if(accuracy_dice < 4 + confused_counter * 2) {
			std::cout << info.name << " ya no est・confundido" << std::endl;
			confused = "false";
			confused_counter = 0;
		} else {
			confused_counter++;
			if(accuracy_dice > 10) {
				std::cout << info.name << " se ataca a si mismo por la confusion" << std::endl;
				move_info = findMove("Autolesion");	// Se cambia el movimiento a Autolesion y se prosigue
			}
		}
	}

	if(!(state == "Dormido") && !failed) {			// Solo se realizar・el movimiento si el Pokemon est・despierto
		std::cout << info.name << " ha utilizado el movimiento " << move_info.name << std::endl;

		if(move_info.effect_1 == "Cadena")	// Si es un movimiento cadena los ejecuto, al estilo Ataque Furia
			for(int i = 0; i < move_info.effect_3; i++)
				ejecuteMove(objetive, move_info);
		else
			ejecuteMove(objetive, move_info);
	}

	if(info.hability == 61 && (state == "Quemado" || state == "Dormido" || state == "Envenenado" || state == "Envenenado+" || state == "Paralizado" || state == "Congelado")) {	// Habilidad Mudar
		displayName();
		std::cout << " utiliza la habilidad Mudar para curar el estado " << state << std::endl;
		cureState();
	}
}

void Pokemon::ejecuteMove(Pokemon &objetive, Move &move_info) {
	float accuracy_dice {10};			// Valor del dado de 1-20, siendo 1 cr咜ico; se pone en 10 por movimientos de da como Golpe A駻eo que nunca fallan
	float accuracy_hability_mod {1.0};	// Modificador de la Precisi porducto de una habilidad
	bool missed {false};				// Indica true si el movimiento falla
	float stab {1.0};					// Bonificaci por movimiento del mismo tipo que el pokemon
	float hability_bonus {1.0};			// Bonificaci por ciertas habilidades
	float damage_done {0};				// Da realizado cn el movimiento

	if(move_info.accuracy > 0) {		// Si el movimiento tiene precisi ya se lanza el dado y se determina si el movimiento acierta
		std::cout << "Lanza el dado de precisi e indique el valor: ";
		std::cin >> accuracy_dice;
		if(info.hability == 14)	// Habilidad Ojo Compuesto
			accuracy_hability_mod = 1.3;
		if(accuracy_dice * 5 < move_info.accuracy * accuracy_hability_mod * accuracy_mod / objetive.evasion_mod) {
			std::cout << "El movimiento ha acertado" << std::endl;
		} else {
			std::cout << "El movimiento ha fallado" << std::endl;
			missed = true;
		}
	}

	if(move_info.objetive == 0 || move_info.objetive == 3) { // En el caso que el movimiento sea para el mismo usuario, ya se procede con el efecto
		if(move_info.name == "Autolesion")
			receiveMove(move_info, 15, level, attack, attack_mod);
		else
			receiveMove(move_info);
	} else if(missed == false)  {							// En caso que el movimiento sea para un 佖ico objetivo, todos los oponentes, o todos y no haya fallado
		for(auto type: info.types) {						// Verifico si tengo bonificaci stab
			if(type == move_info.type)
				stab = 1.5;
		}

		if(info.hability == 65 || info.hability == 66 || info.hability == 67 || info.hability == 68) {	// Verifico si tengo un aumento de da por habilidad
			switch(info.hability) {
				case 65:	// Espesura
					if(move_info.type == "Planta" && (getActualHealth() / getMaxHealth()) <= 0.34 ) {
						displayName();
						std::cout << " utiliza la habilidad Espesura para aumentar el da hecho" << std::endl;
						hability_bonus = 1.5;
					}
				break;
				case 66:	// Mar Llamas
					if(move_info.type == "Fuego" && (getActualHealth() / getMaxHealth()) <= 0.34 ) {
						displayName();
						std::cout << " utiliza la habilidad Mar Llamas para aumentar el da hecho" << std::endl;
						hability_bonus = 1.5;
					}
				break;
				case 67:	// Torrente
					if(move_info.type == "Agua" && (getActualHealth() / getMaxHealth()) <= 0.34 ) {
						displayName();
						std::cout << " utiliza la habilidad Torrente para aumentar el da hecho" << std::endl;
						hability_bonus = 1.5;
					}
				break;
				case 68:	// Enjambre
					if(move_info.type == "Bicho" && (getActualHealth() / getMaxHealth()) <= 0.34 ) {
						displayName();
						std::cout << " utiliza la habilidad Enjambre para aumentar el da hecho" << std::endl;
						hability_bonus = 1.5;
					}
				break;
			}
		}

		if(move_info.clas == "Fisico") {					// Si el movimiento es f﨎isco
			if(move_info.name == "Esfuerzo")
				objetive.receiveMove(move_info, accuracy_dice, level, getActualHealth());
			else if(info.hability == 62 && (state == "Quemado" || state == "Dormido" || state == "Envenenado" || state == "Paralizado")) {// Habilidad Agallas
				displayName();
				std::cout << " utiliza la habilidad Agallas para aumentar el da hecho" << std::endl;
				damage_done = objetive.receiveMove(move_info, accuracy_dice, level, attack*1.5, attack_mod, getVelocity(), stab, hability_bonus);
			} else if(state == "Quemado")							// Si est・Quemado se reduce el Ataque
				damage_done = objetive.receiveMove(move_info, accuracy_dice, level, attack/2.0, attack_mod, getVelocity(), stab, hability_bonus);
			else
				damage_done = objetive.receiveMove(move_info, accuracy_dice, level, attack, attack_mod, getVelocity(), stab, hability_bonus);
		} else if(move_info.clas == "Especial")	{			// Si el movimiento es especial
			damage_done = objetive.receiveMove(move_info, accuracy_dice, level, attack_x, attack_x_mod, getVelocity(), stab, hability_bonus);
		} else objetive.receiveMove(move_info);				// Si el movimiento es de estado

		if(move_info.effect_1 == "Retroceso") {
			std::cout << info.name << " ha sufrido da de retroceso" << std::endl;
			if(receiveDamage(damage_done * move_info.effect_3).defeated)	// Si el Pokemon se debilita con el da se acaba la ejecuci del movimiento
				return;
		}

		if(move_info.contact && objetive.info.hability == 9 && state == "None") {	// Habilidad Electricidad Est疸ica
			std::cout << info.name << " lanza el dado para verificar si es afectado por la habilidad Electricidad Est疸ica";
			std::cin >> accuracy_dice;
			if(accuracy_dice > 14) {
				state = "Paralizado";
				std::cout << info.name << " ahora est・Paralizado" << std::endl;
			}
		}

		if(move_info.contact && objetive.info.hability == 38 && state == "None") {	// Habilidad Punto Tico
			std::cout << info.name << " lanza el dado para verificar si es afectado por la habilidad Punto Toxico";
			std::cin >> accuracy_dice;
			if(accuracy_dice > 14) {
				state = "Envenenado";
				std::cout << info.name << " ahora est・Envenenado" << std::endl;
			}
		}

		if(move_info.effect && move_info.effect_probability > 1.0) {// Verifico si el movimiento tiene efecto para el Pokemon usuario a pesar que el objetivo es enemigo
			receiveEffect(move_info);
		}
	}
}

float Pokemon::receiveMove(Move &move_info, int accuracy_dice, int user_level, float user_attack, float user_attack_mod, float user_velocity, float stab, float hability_bonus) {
	float effectiveness {1};
	float objetive_defense {0};	// La defensa del Pokemon objetivo, la cual dependera del tipo de move si se utiliza defensa o defensa expecial
	float objetive_defense_mod {1};
	int critic {1};
	float received_damage {0};	// Da recibido por este movimiento
	int power {move_info.power};
	float light_screen_mod {1};

	if(move_info.power > 0) {	// Si es un movimiento que hace da se calcula, sino se saltea este paso
		if(move_info.clas == "Fisico") {		// Si el movimiento es f﨎isco
			objetive_defense = defense;
			objetive_defense_mod = defense_mod;
		}

		else if(move_info.clas == "Especial") {	// Si el movimiento es especial
			objetive_defense = defense_x;
			objetive_defense_mod = defense_x_mod;
			if(light_screen)
				light_screen_mod = 0.5;
		}

		effectiveness = getEffectiveness(move_info.type, info.types);	// Verifica efectividad

		if(accuracy_dice <= (critic_mod + move_info.critic)) {			// Verifica si hay o no golpe cr咜ico
			critic = 2;
			std::cout << "Ha sido un golpe critico" << std::endl;
			if(light_screen_mod == 0.5) {
				light_screen_mod = 1;
				light_screen = false;
				std::cout << "La Pantalla de Luz ha sido eliminada" << std::endl;
			}
			// Deberia de ver si tener en cuenta la anulaci de modificadores
		}

		if(move_info.name == "Carga Toxica" && (state == "Envenenado" || state == "Envenenado+")) {	// Verifica si se activa Carga Tica
			std::cout << "Carga Toxica duplica su fuerza" << std::endl;
			move_info = (findMove("Carga Toxica+"));
		}

		if(move_info.name == "Bola Voltio") {	// Verifica la potencia del movimiento Bola Voltio
			if(user_velocity < getVelocity())
				power = 40;
			else if(user_velocity < 2 * getVelocity())
				power = 60;
			else if(user_velocity < 3 * getVelocity())
				power = 80;
			else if(user_velocity < 4 * getVelocity())
				power = 120;
			else if(user_velocity >= 4 * getVelocity())
				power = 150;
		}

		if(move_info.name == "Patada Baja") {	// Verifica la potencia del movimiento Patada Baja
			if(info.stats.weight < 10.0)
				power = 20;
			else if(info.stats.weight < 25.0)
				power = 40;
			else if(info.stats.weight < 50.0)
				power = 60;
			else if(info.stats.weight < 100.0)
				power = 80;
			else if(info.stats.weight < 200.0)
				power = 100;
			else if(info.stats.weight >= 200.0)
				power = 120;
		}

		if(move_info.name == "Esfuerzo") {	// Movimiento Esfuerzo, tener en cuenta que user_attack es en realidad la health actual del Pokemon atacante
			if(user_attack < getActualHealth())
				received_damage = getActualHealth() - user_attack;
			else
				std::cout << info.name << " no se ve afectado por Esfuerzo" << std::endl;
		} else
			received_damage = 0.01 * critic * light_screen_mod * stab * hability_bonus * effectiveness * (82 + 20 / accuracy_dice) * ((((0.2 * user_level * 4 + 1) * power * user_attack * user_attack_mod) / (25 * objetive_defense * objetive_defense_mod)) + 2);	// El 4 se agreg・por la rapidez para subir de nivel

		if(receiveDamage(received_damage).defeated)	// Si el Pokemon se debilita con el da se acaba la ejecuci del movimiento
			return received_damage;
	}

	if(move_info.effect && !(move_info.effect_probability > 1.0) && move_info.effect_probability > 0.0) {		// Si el movimiento tiene un efecto se aplica, sino se saltea este paso
		if(info.hability == 19 && move_info.power != 0) {	// Habilidad Polvo Escudo
			displayName();
			std::cout << "es inmune a efectos secundarios por la habilidad Polvo Escudo" << std::endl;
		} else {
			receiveEffect(move_info);
		}
	}

	return received_damage;
}

boolFloat Pokemon::receiveDamage(float received_damage) {
	displayName();
	if(received_damage > 0) {	// Da por movimiento
		std::cout << " ha sufrido " << received_damage << " puntos de da" << std::endl;
		damage += received_damage;
	} else {					// Da por estado
		if(state == "Envenenado") {			// Da de Envenenamiento
			received_damage = health / 8;
			std::cout << " ha sufrido " << received_damage << " puntos de da por Envenenamiento" << std::endl;
			damage += received_damage;
		} else if(state == "Envenenado+") {	// Da de Envenenamiento Grave
			received_damage = poisoned_counter * health / 16;
			std::cout << " ha sufrido " << received_damage << " puntos de da por Envenenamiento Grave" << std::endl;
			damage += received_damage;
			poisoned_counter++;
		} else if(state == "Quemado") {		// Da de Quemadura
			received_damage = health / 8;
			std::cout << " ha sufrido " << received_damage << " puntos de da por Quemadura" << std::endl;
			damage += received_damage;
		}
		if(seeded) {						// Da de Drenado
			received_damage = health / 8;	// Lo dejo al final as・devuelve el da de drenado
			std::cout << " ha sufrido " << received_damage << " puntos de da por Drenado" << std::endl;
			damage += received_damage;
		}
	}
	std::cout << "El da acumulado es de " << damage << " puntos" << std::endl;

	if(damage >= health) {	// Si el da excede a los PS, el Pokemon se debilita
		std::cout << info.name << " se ha debilitado" << std::endl;
		defeated = true;
		return {true, received_damage};
	} else
		return {false, received_damage};
}

void Pokemon::receiveEffect(Move &move_info) {
	float effect_dice {};		// Dado que determina si el efecto se ejcuta o no

	if(move_info.effect_probability < 1.0) {										// Verifico si tiene probabildiad de fallar
		std::cout << "Lanza el dado para el efecto: ";
		std::cin >> effect_dice;
		if(effect_dice > 20 - 20 * move_info.effect_probability) {			// El efecto no se activa y se acaba el recivimiento de da
			std::cout << "El efecto no se ha activado" << std::endl;
			return;
		}
	}

	if(move_info.effect_probability > 1.0 && move_info.effect_probability < 2.0) {	// Verifico si tiene probabildiad de fallar
		std::cout << "Lanza el dado para el efecto: ";
		std::cin >> effect_dice;
		if(effect_dice > 20 - 20 * (move_info.effect_probability - 1.0)) {	// El efecto no se activa y se acba el recivimiento de da
			std::cout << "El efecto no se ha activado" << std::endl;
			return;
		}
	}

	if(move_info.effect_1 == "Estadistica") {	// Efectos que modifican estadisticas
		for(auto effect_2: move_info.effect_2) {
			if(effect_2 == "Ataque") {				// Modifica el Ataque
				attack_mod *= pow(1.4, move_info.effect_3);
				displayName();
				std::cout << move_info.effect_description << std::endl;
			} else if(effect_2 == "Defensa") {		// Modifica la Defensa
				defense_mod *= pow(1.4, move_info.effect_3);
				displayName();
				std::cout << move_info.effect_description << std::endl;
			} else if(effect_2 == "Ataque Especial") {// Modifica el Ataque Especial
				attack_x_mod *= pow(1.4, move_info.effect_3);
				displayName();
				std::cout << move_info.effect_description << std::endl;
			} else if(effect_2 == "Defensa Especial") {		// Modifica la Defensa Especial
				defense_x_mod *= pow(1.4, move_info.effect_3);
				displayName();
				std::cout << move_info.effect_description << std::endl;
			} else if(effect_2 == "Velocidad") {		// Modifica la Velocidad
				velocity_mod *= pow(1.4, move_info.effect_3);
				displayName();
				std::cout << move_info.effect_description << std::endl;
			} else if(effect_2 == "Precision") {		// Modifica la Precisi
				if(!(info.hability == 51)) {	// Habilidad Vista Lince
					accuracy_mod *= pow(1.3, move_info.effect_3);
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a bajar su Precision por la habilidad Vista Lince" << std::endl;
				}
			} else if(effect_2 == "Critico") {		// Modifica el 匤dice de golpe cr咜ico
				critic_mod += move_info.effect_3;
				displayName();
				std::cout << move_info.effect_description << std::endl;
			}
		}
	} else if(move_info.effect_1 == "Estado" || move_info.name == "Doble Ataque") {	// Efectos que modifican los estados // Doble ataque es un caso muy espec凬ico por lo que tiene su propio nombre
		for(auto effect_2: move_info.effect_2) {
			bool immune {false};
			if(effect_2 == "Drenado") {				// Estado Drenado
				for(auto type: info.types)
					if(type == "Planta")
						immune = true;
				if(!immune) {
					seeded = true;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune al Drenado" << std::endl;
				}
			} else if(effect_2 == "Confundido") {		// Estado Confundido
				if(safeguard)
					immune = true;
				if(!immune) {
					confused = true;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a la Confusion" << std::endl;
				}
			} else if(effect_2 == "Congelado") {		// Estado Congelado
				if(safeguard)
					immune = true;
				for(auto type: info.types)
					if(type == "Hielo")
						immune = true;
				if(!immune && state == "None") {
					state = "Congelado";
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune al Congelamiento" << std::endl;
				}
			} else if(effect_2 == "Dormido") {		// Estado Dormido
				if(safeguard || info.hability == 72)	// Velo Sagrado y habilidad Esp叝itu Vital
					immune = true;
				if(!immune && state == "None") {
					state = "Dormido";
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a Dormirse" << std::endl;
				}
			} else if(effect_2 == "Envenenado") {		// Estado Envenenado
				if(safeguard)
					immune = true;
				for(auto type: info.types)
					if(type == "Veneno" || type == "Acero")
						immune = true;
				if(!immune && state == "None") {
					state = "Envenenado";
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune al Envenenamiento" << std::endl;
				}
			} else if(effect_2 == "Envenenado+") {		// Estado Envenenado Gravemente
				if(safeguard)
					immune = true;
				for(auto type: info.types)
					if(type == "Veneno" || type == "Acero")
						immune = true;
				if(!immune && (state == "None" || state == "Envenenado")) {
					state = "Envenenado+";
					poisoned_counter = 1;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune al Envenenamiento Grave" << std::endl;
				}
			} else if(effect_2 == "Paralizado") {		// Estado Paralizado
				if(safeguard)
					immune = true;
				if(!immune && state == "None") {
					state = "Paralizado";
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a la Paralisis" << std::endl;
				}
			} else if(effect_2 == "Quemado") {		// Estado Quemado
				if(safeguard)
					immune = true;
				for(auto type: info.types)
					if(type == "Fuego")
						immune = true;
				if(!immune && state == "None") {
					state = "Quemado";
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a la Quemadura" << std::endl;
				}
			}
		}
	} else if(move_info.effect_1 == "Campo") {
		for(auto effect_2: move_info.effect_2) {
			bool immune {false};
			if(effect_2 == "Puas Toxicas") {				// Puas Ticas
				if(!immune && !toxic_spikes) {
					toxic_spikes = true;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else if(!immune && toxic_spikes) {
					toxic_spikes_plus = true;
					displayName();
					std::cout << move_info.effect_description << std::endl;
					std::cout << "En total hay dos capas de Puas Toxicas en el campo" << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a las P俉s Ticas" << std::endl;
				}
			} else if(effect_2 == "Pantalla de Luz") {			// Velo Sagrado
				if(!immune) {
					light_screen = true;
					light_screen_counter = 0;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a los efectos de Pantalla de Luz" << std::endl;
				}
			} else if(effect_2 == "Velo Sagrado") {			// Velo Sagrado
				if(!immune) {
					safeguard = true;
					safeguard_counter = 0;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a los efectos de Velos Sagrado" << std::endl;
				}
			} else if(effect_2 == "Viento Afin") {		// Viento Af匤
				if(!immune) {
					tailwind = true;
					tailwind_counter = 0;
					displayName();
					std::cout << move_info.effect_description << std::endl;
				} else {
					displayName();
					std::cout << " es inmune a los efectos de Viento Afin" << std::endl;
				}
			}
		}
	}
}

void Pokemon::cureDamage(float healed) {
	if(healed > 0) {
		damage += -healed;
		std::cout << info.name << " se ha curado " << healed
				  << " puntos de da"
				  << std::endl
				  << "Su salud actual es de " << getActualHealth()
				  << " puntos de salud"
				  << std::endl;
	} else {
		damage = 0;
		defeated = false;
	}
}

void Pokemon::cureState(std::string curedState) {
	if(curedState == "All") {
		state = "None";
		std::cout << info.name << " se ha curado todos los estados" << std::endl;
	}
}

void Pokemon::cureFlinch() {
	flinched = false;
}

float Pokemon::getActualHealth() {
	return health - damage;
}

float Pokemon::getMaxHealth() {
	return health;
}

float Pokemon::getVelocity() {
	float bonus {1};
	if(state == "Paralizado")	// El estado Paralizado reduce la Velocidad
		bonus *= 0.25;
	if(tailwind)
		bonus *= 2;				// Viento Af匤 duplica la Velocidad
	return velocity * velocity_mod * bonus;
}

float Pokemon::getRatio() {
	return info.stats.captured_indice;
}

int Pokemon::getHability() {
	return info.hability;
}

float Pokemon::getExp() {
	return exp;
}

std::string Pokemon::getMove(int i) {
	return moves.at(i - 1);
}

bool Pokemon::isSeeded() {
	return seeded;
}

bool Pokemon::isFlinched() {
	return flinched;
}

bool Pokemon::isDefeated() {
	return defeated;
}

void Pokemon::displayName() {
	std::cout << info.name;
}

void Pokemon::displayHealth() {
	std::cout << health - damage << "/" << health;
}

void Pokemon::displayMove(int i) {
	std::cout << moves.at(i - 1) << std::endl;
}

int Pokemon::displayMoves() {
	for(size_t i = 0; i < moves.size(); i++)
		std::cout << i + 1 << ' ' << moves.at(i) << std::setw(5) << ' ';
	std::cout << std::endl;
	return moves.size();
}

/******************OVERLOAD******************/
std::ostream &operator<<(std::ostream &os, const Pokemon &poke) {
	os << std::setw(15) << std::left << poke.info.name
		<< std::setw(5) << poke.info.number
		<< std::setw(8) << poke.info.types.at(0) << "/" << std::setw(8) << std::right << poke.info.types.at(1)
		<< std::setw(8) << std::right << "nivel " << poke.level
		<< std::endl;
	return os;
}

/*
 * Player.cpp
 */

#include "Player.h"

Player::Player(std::string name)
	:name(name), pokemons(), team(), active_pokemon(), defeated(false) {
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::addPokemon(Pokemon pokemon) {
	pokemon.domated();
	pokemons.push_back(pokemon);								// Se agrega el nuevo Pokemon a la caja de Pokemons
	if(team.size() < 4) {
		team.push_back(pokemons.size() - 1);					// Cada vez que que se captura un nuevo Pokemon, si hay espacio en el team entonces se agrega al mismo
	}
}

bool Player::capturePokemon(Pokemon &captured_pokemon) {
	int pokeball {};
	float pokeball_ratio {};
	float pokeball_dice {};
	bool valid_pokeball {false};
	float capture_chance {};
	int state_bonus {0};			// Bonus por estar bajo algun estado

	while(!valid_pokeball) {	// Se selecciona la pokeball a usar
		std::cout << "Eliga que Pokeball lanzar:" << std::endl
				  << std::setw(15) << std::left << "1 Pokeball"
				  << std::setw(15) << std::left << "2 Superball"
				  << std::setw(15) << std::left << "3 Ultraball"
				  << std::setw(15) << std::left << "4 Masterball"
				  << std::endl;
		std::cin >> pokeball;
		switch(pokeball) {
			case 1:
				pokeball_ratio = 1.0;
				valid_pokeball = true;
				break;
			case 2:
				pokeball_ratio = 1.5;
				valid_pokeball = true;
				break;
			case 3:
				pokeball_ratio = 2.0;
				valid_pokeball = true;
				break;
			case 4:
				pokeball_ratio = 1000.00;
				valid_pokeball = true;
				break;
			default:
				std::cout << "Pokeball elegida no v疝ida" << std::endl;
				break;
		}
	}
	// Se debe determinar el valor de state_bonus
	capture_chance = ((3 * captured_pokemon.getMaxHealth() - 2 * captured_pokemon.getActualHealth()) * captured_pokemon.getRatio() * pokeball_ratio / (3 * captured_pokemon.getMaxHealth())) + state_bonus;
	std::cout << "Indique valor de dado de Pokeball (1d100): ";
	std::cin >> pokeball_dice;
	if(pokeball_dice * 2.55 < capture_chance) {
		captured_pokemon.displayName();
		std::cout << " ha sido capturado" << std::endl;
		addPokemon(captured_pokemon);
		return true;
	} else {
		std::cout << "El pokemon salvaje ha escapado de la Pokeball" << std::endl;
		return false;
	}
}

void Player::changeTeam() {
	char answer {};
	bool changing {true};
	unsigned int pokemon_team {};
	unsigned int pokemon_pc {};
	while(changing) {
		std::cout << "El team de " << name << " es:" << std::endl;		// Muestro team
		displayTeam();
		std::cout << "Los pokemons de " << name << " son:" << std::endl;// Muestro todos los Pokemons
		displayPokemons();
		std::cout << "Indique el numero del pokemon del team que desea reemplazar y el del pokemon que desea agregar: ";
		std::cin >> pokemon_team >> pokemon_pc;							// Indico cuales voy a cambiar
		if(pokemon_team <= team.size() && pokemon_pc <= pokemons.size() && pokemon_team * pokemon_pc >> 0)
			team.at(pokemon_team - 1) = pokemon_pc - 1;					// Realizo el cambio
		else std::cout << "Valor utilizado no valido" << std::endl;
		std::cout << "Desea seguir cambiando? (y/n): ";					// Verifico si voy a hacer otro cambio
		std::cin >> answer;
		if(answer == 'n')
			changing = false;
	}
}

void Player::giveObject() {
	char answer {};
	bool giving {true};
	unsigned int pokemon_team {};
	unsigned int object {};
	while(giving) {
		std::cout << "El team de " << name << " es:" << std::endl;	// Muestro team
		displayTeam();
		std::cout << "Indique el numero del pokemon del team que desea darle un objeto: ";
		std::cin >> pokemon_team;									// Indico a cu疝 se lo doy
		std::cout << "Indique el numero del objeto que le voy a dar: ";
		std::cin >> object;											// Indico qu・objecto le doy
		if(object <= 200 && object >= 100)
			pokemons.at(team.at(pokemon_team - 1)).receiveObject(object);// Le doy el objeto
		else std::cout << "Valor utilizado no valido" << std::endl;
		std::cout << "Desea seguir cambiando? (y/n): ";					// Verifico si voy a hacer otro cambio
		std::cin >> answer;
		if(answer == 'n')
			giving = false;
	}
}

void Player::gainExp(float exp) {
	if(!pokemons.at(active_pokemon).isDefeated())
		pokemons.at(active_pokemon).gainExp(exp);
	for(size_t i = 0; i < team.size(); i++) {
		if(team.at(i) != active_pokemon && !pokemons.at(team.at(i)).isDefeated())
			pokemons.at(team.at(i)).gainExp(exp / 2);
	}
}

void Player::selectActive() {
	int pokemon_quantity {};
	int chosed_pokemon {};
	bool valid_pokemon {false};
	int last_active_pokemon {active_pokemon};
	while(!valid_pokemon) {
		std::cout << "Los pokemons en el team de " << name << " son:" << std::endl;
		pokemon_quantity = displayTeam();
		std::cout << "Elija su Pokemon activo: ";
		std::cin >> chosed_pokemon;
		if(chosed_pokemon <= pokemon_quantity && chosed_pokemon > 0 ) {	// Verifico que el n伹ero este dentro del rango
			if(!pokemons.at(team.at(chosed_pokemon - 1)).isDefeated()) {			// Verifico que el Pokemon elegido no este debilitado
				valid_pokemon = true;
				active_pokemon = team.at(chosed_pokemon - 1);
				std::cout << name << " ha elegido a ";
				pokemons.at(active_pokemon).displayName();
				std::cout << std::endl;
				pokemons.at(active_pokemon).modifierRefresh();		// Elimino cualquier modificador de estad﨎ticas que le haya quedado
				pokemons.at(active_pokemon).temporalStatusRefresh();// Elimino cualquier estado temporal que le haya quedado
				pokemons.at(active_pokemon).passCampusStatus(pokemons.at(last_active_pokemon));
			} else {
				pokemons.at(team.at(chosed_pokemon - 1)).displayName();
				std::cout << " se encuentra debilidato y no puede pelear" << std::endl;
			}

		} else std::cout << "Pokemon no v疝ido" << std::endl;
	}
}

bool Player::isTeamDefeated() {
	defeated = true;
	for(auto &pokemon: team) {
		if(!pokemons.at(pokemon).isDefeated())
			defeated = false;
	}
	if(defeated) {
		std::cout << "El jugador " << name
				  << " ya no tiene Pokemons que puedan luchar"
				  << std::endl
				  << name << " ha quedado inconsiente"
				  << std::endl;
	}
	return defeated;

}

Pokemon Player::getTeamPokemon(int i) {
	return pokemons.at(team.at(i));
}

std::string Player::getName() {
	return name;
}

void Player::displayPokemons() {
	for(size_t i = 0; i < pokemons.size(); i++) {
		std::cout << i + 1 << ' ';
		pokemons.at(i).displayName();
		std::cout << ' ' << pokemons.at(i).getExp() << " exp" << std::endl;
	}
}

int Player::displayTeam() {
	for(size_t i = 0; i < team.size(); i++) {
		std::cout << i + 1 << ' ';
		pokemons.at(team.at(i)).displayName();
		std::cout << " ";
		pokemons.at(team.at(i)).displayHealth();
		if(pokemons.at(team.at(i)).isDefeated())
			std::cout << " (debilitado)";
		std::cout << "   " << pokemons.at(i).getExp() << " exp" << std::endl;
	}
	return team.size();
}

void battle(std::vector<Player> &players) {
	int moves_quantity {};
	int chosed_action {};
	int chosed_move {};
	std::string player_chosed_move {};		// Nombre del movimiento elegido por el jugador
	std::string enemy_chosed_move {};		// Nombre del movimiento elegido por el enemigo
	bool battling {false};					// Indica si la batalla de todos los jugadores continua
	std::vector<bool> player_battling {};	// Indica como va la batalla de cada jugador, porque un jugador puede haber terminado pero otro no
	bool valid_action {false};
	bool valid_move {false};
	std::string enemy_pokemon {};
	std::vector<Pokemon> enemy_pokemons {};
	int enemy_pokemon_level {};
	std::vector<std::vector<bool>> player_battle_states {};	// Indica los estados: 1=Viento Af匤

	for(auto &player: players) {	// Indico que jugadores participan y sus respectivos adversarios
		if(player.defeated) {	// Si el jugador no participa
			player_battling.push_back(false);								// Indico que no pelea
			std::cout << player.name << " no puede pelear" << std::endl;
			enemy_pokemons.push_back(Pokemon());							// Agrego un Pokemon enemigo "dummy" por temas de llenar el vector para la sincronizaci
		} else {
			player_battling.push_back(true);								// Indico que pelea
			battling = true;												// De este manera, con que un solo jugador pueda luchar se inicia la pelea, enc aso contrario no
			player.selectActive();											// Elecci de Pokemon activo de cada jugador que pueda pelear
			std::cout << "Indique el pokemon y nivel enemigo del jugador " << player.name << ": ";
			std::cin >> enemy_pokemon;										// Se indica el nombre del Pokemon enemigo (sea salvaje o de un entrenador)
			std::cin >> enemy_pokemon_level;								// Se indica el nivel del Pokemon enemigo
			enemy_pokemons.push_back(Pokemon (findPokemon(enemy_pokemon), enemy_pokemon_level));	// Agrego al Pokemon enemigo
		}
	}

	while(battling) {		// Loop para la batalla
		for(size_t i = 0; i < players.size(); i++) {	// Se descenlazan las acciones de cada jugador con su respectivo enemigo
			if(player_battling.at(i)) {		// Se verifica que el jugador este luchando

				while(!valid_move) {	// Selecciono movimiento del Pokemon enemigo
					std::cout << "Elija el movimiento de ";
					enemy_pokemons.at(i).displayName();
					std::cout << " el Pokemon enemigo del jugador "
							  << players.at(i).name
							  << ": " << std::endl;
					moves_quantity = enemy_pokemons.at(i).displayMoves();
					std::cin >> chosed_move;
					if(chosed_move <= moves_quantity && chosed_move > 0 ) {			// Se verifica que la selecci sea v疝ida
						valid_move = true;
						enemy_chosed_move = enemy_pokemons.at(i).getMove(chosed_move);	// De ser v疝ida, se alamacena el movimiento a usar por el pokemon enemigo
						std::cout << "El pokemon salvaje ha usado ";
						enemy_pokemons.at(i).displayMove(chosed_move);
					} else std::cout << "Movimiento no v疝ido" << std::endl;
				}
				valid_move = false;

				while(!valid_action) {	// Selecciono la acci del jugador
					std::cout << "Elija la acci a ejecutar del jugador " << players.at(i).name << ": " << std::endl
							  << std::setw(12) << std::right << "1 Movimiento"
							  << std::setw(12) << std::right << "2 Capturar"
							  << std::setw(12) << std::right << "3 Cambiar"
							  // Falta agregar opc匤 de usar objetos
							  << std::endl;
					std::cin  >> chosed_action;
					if(chosed_action <= 3 && chosed_action > 0 )
						valid_action = true;
					else
						std::cout << "Acci no v疝ido" << std::endl;
				}
				valid_action = false;

				switch(chosed_action) {	// Depende a la acci, se prosigue
					case 1:	// Selecci de usar movimiento
						// Se podr僘 integrar esto como una funci
						std::cout << "Elija el Movimiento a usar de ";	// Se elije el movimiento a usar
						players.at(i).pokemons.at(players.at(i).active_pokemon).displayName();
						std::cout << ": " << std::endl;
						while(!valid_move) {
							moves_quantity = players.at(i).pokemons.at(players.at(i).active_pokemon).displayMoves();
							std::cin >> chosed_move;
							if(chosed_move <= moves_quantity && chosed_move > 0 ) {
								valid_move = true;
								player_chosed_move = players.at(i).pokemons.at(players.at(i).active_pokemon).getMove(chosed_move);
								players.at(i).pokemons.at(players.at(i).active_pokemon).displayName();
								std::cout << " ha elegido usar ";
								players.at(i).pokemons.at(players.at(i).active_pokemon).displayMove(chosed_move);
							} else std::cout << "Movimiento no v疝ido" << std::endl;
						}
						valid_move = false;

						if(getPriority(player_chosed_move) > getPriority(enemy_chosed_move) || (!(getPriority(player_chosed_move) < getPriority(enemy_chosed_move)) && players.at(i).pokemons.at(players.at(i).active_pokemon).getVelocity() >= enemy_pokemons.at(i).getVelocity())) {	// Se descenlazan movimientos de jugador y enemigo
							players.at(i).pokemons.at(players.at(i).active_pokemon).useMove(enemy_pokemons.at(i), player_chosed_move);
							if(!enemy_pokemons.at(i).isDefeated() && !enemy_pokemons.at(i).isFlinched())
								enemy_pokemons.at(i).useMove(players.at(i).pokemons.at(players.at(i).active_pokemon), enemy_chosed_move);
						} else {
							enemy_pokemons.at(i).useMove(players.at(i).pokemons.at(players.at(i).active_pokemon), enemy_chosed_move);
							if(!players.at(i).pokemons.at(players.at(i).active_pokemon).isDefeated() && !players.at(i).pokemons.at(players.at(i).active_pokemon).isFlinched())
								players.at(i).pokemons.at(players.at(i).active_pokemon).useMove(enemy_pokemons.at(i), player_chosed_move);
						}
						break;

					case 2:	// Selecci de usar pokeball
						if(players.at(i).capturePokemon(enemy_pokemons.at(i)))
							player_battling.at(i) = false;	// Elecci de Pokeball y ejecuci de captura
						else
							enemy_pokemons.at(i).useMove(players.at(i).pokemons.at(players.at(i).active_pokemon), enemy_chosed_move);
						break;

					case 3:	// Selecci de cambiar pokemon
						if(enemy_chosed_move == "Persecucion")											// Verifica si se utiliz・persecucion
							enemy_pokemons.at(i).useMove(players.at(i).pokemons.at(players.at(i).active_pokemon), "Persecucion+");
						players.at(i).selectActive();													// Elijo nuevo Pokemon activo
						break;
				}

				if(players.at(i).pokemons.at(players.at(i).active_pokemon).getHability() == 61) {	// Habilidad Mudar
					players.at(i).pokemons.at(players.at(i).active_pokemon).cureState();
				}

				if(player_battling.at(i) == true) {	// Se verifica que el combate no haya acabado por la captura del enemigo
					if(getPriority(player_chosed_move) > getPriority(enemy_chosed_move) || (!(getPriority(player_chosed_move) < getPriority(enemy_chosed_move)) && players.at(i).pokemons.at(players.at(i).active_pokemon).getVelocity() >= enemy_pokemons.at(i).getVelocity())) {	// Se descenlazan da por estados en el orden de los movimientos
						if(players.at(i).pokemons.at(players.at(i).active_pokemon).isSeeded() && !enemy_pokemons.at(i).isDefeated())		// Se descuenta el da de estados
							enemy_pokemons.at(i).cureDamage(players.at(i).pokemons.at(players.at(i).active_pokemon).receiveDamage().damage);// Al no indicar valor de da (por default 0) el m騁odo verificar・si el pokemon tiene alg佖 estado y calcular・el da
						else
							players.at(i).pokemons.at(players.at(i).active_pokemon).receiveDamage();
						if(enemy_pokemons.at(i).isSeeded() && !players.at(i).pokemons.at(players.at(i).active_pokemon).isDefeated())		// Se descuenta el da de estados
							players.at(i).pokemons.at(players.at(i).active_pokemon).cureDamage(enemy_pokemons.at(i).receiveDamage().damage);// Al no indicar valor de da (por default 0) el m騁odo verificar・si el pokemon tiene alg佖 estado y calcular・el da
						else
							enemy_pokemons.at(i).receiveDamage();
					} else {
						if(enemy_pokemons.at(i).isSeeded() && !players.at(i).pokemons.at(players.at(i).active_pokemon).isDefeated())		// Se descuenta el da de estados
							players.at(i).pokemons.at(players.at(i).active_pokemon).cureDamage(enemy_pokemons.at(i).receiveDamage().damage);// Al no indicar valor de da (por default 0) el m騁odo verificar・si el pokemon tiene alg佖 estado y calcular・el da
						else
							enemy_pokemons.at(i).receiveDamage();
						if(players.at(i).pokemons.at(players.at(i).active_pokemon).isSeeded() && !enemy_pokemons.at(i).isDefeated())		// Se descuenta el da de estados
							enemy_pokemons.at(i).cureDamage(players.at(i).pokemons.at(players.at(i).active_pokemon).receiveDamage().damage);// Al no indicar valor de da (por default 0) el m騁odo verificar・si el pokemon tiene alg佖 estado y calcular・el da
						else
							players.at(i).pokemons.at(players.at(i).active_pokemon).receiveDamage();
					}
				}

				// Se descuenta el da de climas

				players.at(i).pokemons.at(players.at(i).active_pokemon).cureFlinch();	// Curo el amedrentamiento
				enemy_pokemons.at(i).cureFlinch();

				players.at(i).pokemons.at(players.at(i).active_pokemon).counterUp();	// Aumento contador
				enemy_pokemons.at(i).counterUp();

				if(players.at(i).pokemons.at(players.at(i).active_pokemon).isDefeated()) {// Cuando el Pokemon del jugador se debilita deja de ser el Pokemon activo
					if(players.at(i).isTeamDefeated()) {
						player_battling.at(i) = false;
					} else {
						std::cout << "Seleccione otro pokemon para continuar" << std::endl;
						players.at(i).selectActive();
					}
				}

				if(enemy_pokemons.at(i).isDefeated()) {			// Cuando el Pokemon salvaje o entrenador enemigo se debilita el combate termina
					player_battling.at(i) = false;
					players.at(i).gainExp(enemy_pokemons.at(i).giveExp());
				}
			}
		}

		battling = false;
		for(size_t i = 0; i < players.size(); i++)	// Verifico si al menos un jugador sigue luchando luego de esta ronda
			if(player_battling.at(i))
				battling = true;
		if(!battling)
			std::cout << "La batalla ha terminado" << std::endl << std::endl;
	}
}

void pokemonCenter(std::vector<Player> &players) {
	for(auto &player: players) {	// Ejecuto acción en cada jugador
		for(auto &pokemon: player.pokemons) {	// Se curan todos los Pokemons
			pokemon.cureDamage();
			pokemon.cureState();
		}
		player.defeated = false;	// Se cura al jugador
		std::cout << "Se han curado todos los pokemons de " << player.name << std::endl;
	}
	administrateTeam(players);
}

void administrateTeam(std::vector<Player>& players) {
	char answer{};
	for (auto& player : players) {	// Ejecuto acción en cada jugador
		std::cout << "Desea " << player.name << " modificar algun pokemon del team? (y/n): ";
		std::cin >> answer;						// Se elige si cambiar Pokemons
		std::cout << std::endl;
		if (answer == 'y')
			player.changeTeam();

		std::cout << "Desea " << player.name << " utilizar algun objeto? (y/n): ";
		std::cin >> answer;						// Se elige si usar un objeto
		std::cout << std::endl;
		if (answer == 'y')
			player.giveObject();
	}
}

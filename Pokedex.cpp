/*
 * Pokedex.cpp
 */

/****************** INCLUDES ******************/
#include "Pokedex.h"

/****************** FUNCTIONS ******************/
PokemonData findPokemon(std::string pokemon_chosed) { // @suppress("No return")
	bool valid_pokemon = false;
	while(!valid_pokemon) {
		std::vector<PokemonData>::iterator it = std::find_if(pokedex.begin(), pokedex.end(), [pokemon_chosed](PokemonData pokemon) {return pokemon_chosed == pokemon.name;});
		if(it != pokedex.end()) {
			valid_pokemon = true;
			return *it;	// Me devuelve una estructura PokemonData
		} else {
			std::cout << "Nombre de Pokemon no v·lido" << std::endl
					  << "Elija otro nombre de Pokemon: ";
			std::cin >> pokemon_chosed;
		}
	}
	// No deber˙} de ser necesaria esta opciÛn, pero me molesta que salte el warning
	return pokedex.at(0);
}

/****************** CONST ******************/
const std::vector<std::vector<float>> growth {	// Curvas de crecimiento
	{314.4, 973.6, 2535.2, 5460, 10208.8, 17242.4, 27021.6, 40007.2, 56660, 77440.8, 102810.4, 133229.6, 169159.2, 211060},	// Parabolica
	{},	// 1 Lenta
	{512, 1728, 4096, 8000, 13824, 21952, 32768, 46656, 64000, 85184, 110592, 140608, 175616, 216000},	// 2 Media
	{}	// 3 Rapida
};

/****************** VARIABLES ******************/
std::vector<PokemonData> pokedex {		// De esta manera es mucho m·s f·cil buscar cada Pokemon
	PokemonData {
		"Bulbasaur",	// Nombre
		"001",			// Numero
		{				// Tipo
			"Planta",
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			45,	// Putos de Saluda
			49,	// Ataque
			49,	// Defensa
			65,	// Ataque Especial
			65,	// Defensa Especial
			45,	// Velocidad
			6.9,// Peso
			0.7,// Altura
			45,	// Indice de Captura
			64	// Experiencia Bae
		},
		65,				// Espesura
		{				// Movimientos
			{"Placaje", 1},
			{"GruÒido", 1},
			{"Latigo Cepa", 2},
			{"Drenadoras", 3},
			{"Polvo Veneno", 4},
			{"Paralizador", 4},
			{"Somnifero", 4}
		},
		{"Ivysaur", 5}	// Evolution
	},
	PokemonData {
		"Ivysaur",	// Nombre
		"002",			// Numero
		{				// Tipo
			"Planta",
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			60,	// Putos de Saluda
			62,	// Ataque
			63,	// Defensa
			80,	// Ataque Especial
			80,	// Defensa Especial
			60,	// Velocidad
			13.0,// Peso
			1.0,// Altura
			45,	// Indice de Captura
			141	// Experiencia Bae
		},
		65,				// Espesura
		{				// Movimientos
			{"Derribo", 5},
			{"Hoja Afilada", 6},
			{"Dulce Aroma", 7},
			{"Desarrollo", 8},
			{"Doble Filo", 8},
		},
		{"Venasaur", 9}	// Evolution
	},
	PokemonData {
		"Venasaur",	// Nombre
		"003",			// Numero
		{				// Tipo
			"Planta",
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			80,	// Putos de Saluda
			82,	// Ataque
			83,	// Defensa
			100,// Ataque Especial
			100,// Defensa Especial
			80,	// Velocidad
			100.0,// Peso
			2.0,// Altura
			45,	// Indice de Captura
			208	// Experiencia Base
		},
		65,				// Espesura
		{				// Movimientos
			{"Danza Petalo", 9},
			{"Abatidoras", 10},
			{"Sintesis", 11},
			{"Tormenta Floral", 12},
			{"Rayo Solar", 13},
		},
		{"None", 16}	// Evolution
	},
	PokemonData {
		"Charmander",	// Nombre
		"004",			// Numero
		{				// Tipo
			"Fuego"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			39,	// Putos de Saluda
			52,	// Ataque
			43,	// Defensa
			60,	// Ataque Especial
			50,	// Defensa Especial
			65,	// Velocidad
			8.5,// Peso
			0.6,// Altura
			45,	// Indice de Captura
			65	// Experiencia Base
		},
		66,				// Mar Llamas
		{				// Movimientos
			{"AraÒazo", 1},
			{"GruÒido", 1},
			{"Ascuas", 2},
			{"Pantalla de Humo", 3},
			{"Garra Metal", 4}
		},
		{"Charmeleon", 5}	// Evolution
	},
	PokemonData {
		"Charmeleon",	// Nombre
		"005",			// Numero
		{				// Tipo
			"Fuego"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			58,	// Putos de Saluda
			64,	// Ataque
			58,	// Defensa
			80,	// Ataque Especial
			65,	// Defensa Especial
			80,	// Velocidad
			10.0,// Peso
			1.1,// Altura
			45,	// Indice de Captura
			143	// Experiencia Base
		},
		66,				// Mar Llamas
		{				// Movimientos
			{"Furia Dragon", 5},
			{"Furia", 6},
			{"Cara Susto", 7},
			{"Colmillo Igneo", 8},
			{"Pirotecnia", 8},
			{"Cuchillada", 9}
		},
		{"Charizard", 10}	// Evolution
	},
	PokemonData {
		"Charizard",	// Nombre
		"006",			// Numero
		{				// Tipo
			"Fuego",
			"Volador"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			78,	// Putos de Saluda
			84,	// Ataque
			78,	// Defensa
			109,	// Ataque Especial
			85,	// Defensa Especial
			100,	// Velocidad
			90.5,// Peso
			1.7,// Altura
			45,	// Indice de Captura
			209	// Experiencia Base
		},
		66,				// Mar Llamas
		{				// Movimientos
			{"Lanzallamas", 10},
			{"Ataque Ala", 10},
			{"Giro Fuego", 11},
			{"Infierno", 12},
			{"Envite Igneo", 13},
			{"Tajo Aereo", 14},
			{"Onda Ignea", 15}
		},
		{"None", 16}	// Evolution
	},
	PokemonData {
		"Squirtle",	// Nombre
		"007",			// Numero
		{				// Tipo
			"Agua"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			44,	// Putos de Saluda
			48,	// Ataque
			65,	// Defensa
			50,	// Ataque Especial
			64,	// Defensa Especial
			43,	// Velocidad
			9.0,// Peso
			0.5,// Altura
			45,	// Indice de Captura
			66	// Experiencia Base
		},
		67,				// Torrente
		{				// Movimientos
			{"Placaje", 1},
			{"Latigo", 1},
			{"Burbuja", 2},
			{"Refugio", 3},
			{"Pistola Agua", 4}
		},
		{"Wartortle", 5}	// Evolution
	},
	PokemonData {
		"Wartortle",	// Nombre
		"008",			// Numero
		{				// Tipo
			"Agua"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			59,	// Putos de Saluda
			63,	// Ataque
			80,	// Defensa
			65,	// Ataque Especial
			80,	// Defensa Especial
			58,	// Velocidad
			22.5,// Peso
			1.0,// Altura
			45,	// Indice de Captura
			143	// Experiencia Base
		},
		67,				// Torrente
		{				// Movimientos
			{"Mordisco", 5},
			{"Giro Rapido", 6},
			{"Proteccion", 7},
			{"Hidropulso", 7},
			{"Acua Cola", 8},
			{"Rayo Burbuja", 9},
		},
		{"Blastoise", 10}	// Evolution
	},
	PokemonData {
		"Blastoise",	// Nombre
		"009",			// Numero
		{				// Tipo
			"Agua"
		},
		0,				// Crecimiento parabÛlico
		{				// Stats
			79,	// Putos de Saluda
			83,	// Ataque
			100,	// Defensa
			85,	// Ataque Especial
			105,	// Defensa Especial
			78,	// Velocidad
			85.5,// Peso
			1.6,// Altura
			45,	// Indice de Captura
			210	// Experiencia Base
		},
		67,				// Torrente
		{				// Movimientos
			{"Cabezazo", 10},
			{"Danza Lluvia", 11},
			{"Defensa Ferrea", 12},
			{"Hidrobomba", 13},
			{"Golpe Cabeza", 14},
			{"Rompecoraza", 15},
		},
		{"None", 16}	// Evolution
	},
	PokemonData {
		"Caterpie",	// Nombre
		"010",			// Numero
		{				// Tipo
			"Bicho"
		},
		2,				// Crecimiento medio
		{				// Stats
			45,	// Putos de Saluda
			30,	// Ataque
			35,	// Defensa
			20,	// Ataque Especial
			20,	// Defensa Especial
			45,	// Velocidad
			2.9,// Peso
			0.3,// Altura
			255,	// Indice de Captura
			53	// Experiencia Base
		},
		19,				// Polvo Escudo
		{				// Movimientos
			{"Placaje", 1},
			{"Disparo Demora", 1}
		},
		{"Metapod", 2}	// Evolution
	},
	PokemonData {
		"Metapod",	// Nombre
		"011",			// Numero
		{				// Tipo
			"Bicho"
		},
		2,				// Crecimiento medio
		{				// Stats
			50,	// Putos de Saluda
			20,	// Ataque
			55,	// Defensa
			25,	// Ataque Especial
			25,	// Defensa Especial
			30,	// Velocidad
			9.9,// Peso
			0.7,// Altura
			120,	// Indice de Captura
			72	// Experiencia Base
		},
		61,				// Mudar
		{				// Movimientos
			{"Fortaleza", 2}
		},
		{"Butterfree", 3}	// Evolution
	},
	PokemonData {
		"Butterfree",	// Nombre
		"012",			// Numero
		{				// Tipo
			"Bicho",
			"Volador"
		},
		2,				// Crecimiento medio
		{				// Stats
			60,	// Putos de Saluda
			45,	// Ataque
			50,	// Defensa
			90,	// Ataque Especial
			80,	// Defensa Especial
			70,	// Velocidad
			32.0,// Peso
			1.1,// Altura
			45,	// Indice de Captura
			160	// Experiencia Base
		},
		14,				// Mudar
		{				// Movimientos
			{"Confusion", 3},
			{"Polvo Veneno", 4},
			{"Paralizador", 4},
			{"Somnifero", 4},
			{"Supersonico", 5},
			{"Tornado", 6},
			{"Psicorrayo", 7},
			{"Viento Plata", 7},
			{"Viento Afin", 8},
			{"Zumbido", 9},
			{"Velo Sagrado", 10},
			{"Danza Aleteo", 11}

		},
		{"None", 16}	// Evolution
	},
	PokemonData {
		"Weedle",	// Nombre
		"013",			// Numero
		{				// Tipo
			"Bicho",
			"Veneno"
		},
		2,				// Crecimiento medio
		{				// Stats
			40,	// Putos de Saluda
			35,	// Ataque
			30,	// Defensa
			20,	// Ataque Especial
			20,	// Defensa Especial
			50,	// Velocidad
			3.2,// Peso
			0.3,// Altura
			255,	// Indice de Captura
			52	// Experiencia Base
		},
		19,				// Polvo Escudo
		{				// Movimientos
			{"Picotazo Veneno", 1},
			{"Disparo Demora", 1}
		},
		{"Kakuna", 2}	// Evolution
	},
	PokemonData {
		"Kakuna",	// Nombre
		"014",			// Numero
		{				// Tipo
			"Bicho",
			"Veneno"
		},
		2,				// Crecimiento medio
		{				// Stats
			45,	// Putos de Saluda
			25,	// Ataque
			50,	// Defensa
			25,	// Ataque Especial
			25,	// Defensa Especial
			35,	// Velocidad
			10.0,// Peso
			0.6,// Altura
			120,	// Indice de Captura
			71	// Experiencia Base
		},
		61,				// Mudar
		{				// Movimientos
			{"Fortaleza", 2}
		},
		{"Beedrill", 3}	// Evolution
	},
	PokemonData {
		"Beedrill",	// Nombre
		"015",			// Numero
		{				// Tipo
			"Bicho",
			"Veneno"
		},
		2,				// Crecimiento medio
		{				// Stats
			65,	// Putos de Saluda
			90,	// Ataque
			40,	// Defensa
			45,	// Ataque Especial
			80,	// Defensa Especial
			75,	// Velocidad
			29.5,// Peso
			1.0,// Altura
			45,	// Indice de Captura
			159	// Experiencia Base
		},
		68,				// Enjambre
		{				// Movimientos
			{"Ataque Furia", 3},
			{"Foco energia", 4},
			{"Furia", 4},
			{"Pin Misil", 4},
			{"Doble Ataque", 5},
			{"Persecucion", 6},
			{"Carga Toxica", 7},
			{"Buena Baza", 7},
			{"Puas Toxicas", 8},
			{"Puya Nociva", 9},
			{"Agilidad", 10},
			{"Esfuerzo", 11}
		},
		{"None", 16}	// Evolution
	},
	PokemonData {
		"Pidgey",
		"016",
		{
			"Normal",
			"Volador"
		},
		0,				// Crecimiento parabÛlico
		{
			40,
			45,
			40,
			35,
			35,
			56,
			1.8,
			0.3,
			255,
			55
		},
		51,		// Vista Lince
		{
			{"Placaje", 1},
			{"Ataque Arena", 2},
			{"Tornado", 3},
			{"Ataque Rapido", 4}
		},
		{"Pidgeotto", 5}
	},
	PokemonData {
		"Pidgeotto",
		"017",
		{
			"Normal",
			"Volador"
		},
		0,				// Crecimiento parabÛlico
		{
			63,
			60,
			55,
			50,
			50,
			71,
			30.0,
			1.1,
			120,
			113
		},
		51,		// Vista Lince
		{
			{"Remolino", 5},
			{"Ciclon", 6},
			{"Ataque Ala", 7},
			{"Danza Pluma", 8},
			{"Agilidad", 9}
		},
		{"Pidgeot", 10}
	},
	PokemonData {
		"Pidgeot",
		"018",
		{
			"Normal",
			"Volador"
		},
		0,				// Crecimiento parabÛlico
		{
			83,
			80,
			75,
			70,
			70,
			91,
			39.5,
			1.5,
			45,
			172
		},
		51,		// Vista Lince
		{
			{"Respiro", 11},
			{"Viento Afin", 12},
			{"Movimiento Espejo", 13},
			{"Tajo Aereo", 14},
			{"Vendabal", 15}
		},
		{"None", 16}
	},
	PokemonData {
		"Rattata",
		"019",
		{
			"Normal"
		},
		2,				// Crecimiento medio
		{
			30,
			56,
			35,
			25,
			35,
			72,
			3.5,
			0.3,
			255,
			57
		},
		62,	// Agallas
		{
			{"Placaje", 1},
			{"Latigo", 1},
			{"Ataque Rapido", 2},
			{"Foco Energia", 3},
			{"Mordisco", 4},
			{"Persecucion", 4},
			{"Hipercolmillo", 5}
		},
		{"Raticate", 6}
	},
	PokemonData {
		"Raticate",
		"020",
		{
			"Normal"
		},
		2,				// Crecimiento medio
		{
			55,
			81,
			60,
			50,
			70,
			97,
			18.5,
			0.7,
			127,
			116
		},
		62,	// Agallas
		{
			{"Cara Susto", 6},
			{"Triturar", 7},
			{"Golpe Bajo", 7},
			{"Buena Baza", 8},
			{"Superdiente", 9},
			{"Doble Filo", 10},
			{"Esfuerzo", 11}
		},
		{"None", 16}
	},
	PokemonData {
		"Spearow",
		"021",
		{
			"Normal",
			"Volador"
		},
		2,				// Crecimiento medio
		{
			40,	// Putos de Saluda
			60,	// Ataque
			30,	// Defensa
			31,	// Ataque Especial
			31,	// Defensa Especial
			70,	// Velocidad
			2.0,// Peso
			0.3,// Altura
			255,	// Indice de Captura
			58	// Experiencia Base
		},
		51,		// Vista Lince
		{
			{"Picotazo", 1},
			{"GruÒido", 1},
			{"Malicioso", 2},
			{"Ataque Furia", 3},
			{"Persecucion", 4},
			{"Foco Energia", 4},
			{"Golpe Aereo", 5}
		},
		{"Fearow", 6}
	},
	PokemonData {
		"Fearow",
		"022",
		{
			"Normal",
			"Volador"
		},
		2,				// Crecimiento medio
		{
			65,	// Putos de Saluda
			90,	// Ataque
			65,	// Defensa
			61,	// Ataque Especial
			61,	// Defensa Especial
			100,// Velocidad
			38.0,// Peso
			1.2,// Altura
			90,	// Indice de Captura
			162	// Experiencia Base
		},
		51,		// Vista Lince
		{
			{"Movimiento Espejo", 6},
			{"Buena Baza", 7},
			{"Agilidad", 8},
			{"Pico Taladro", 9},
			{"Respiro", 10},
			{"Taladradora", 11}
		},
		{"None", 16}
	},
	PokemonData {
		"Pikachu",
		"025",
		{
			"Electrico"
		},
		2,				// Crecimiento medio
		{
			35,	// Putos de Saluda
			55,	// Ataque
			40,	// Defensa
			50,	// Ataque Especial
			50,	// Defensa Especial
			90,	// Velocidad
			6.0,// Peso
			0.4,// Altura
			190,	// Indice de Captura
			82	// Experiencia Base
		},
		9,		// Electricidad Est·tica
		{
			{"Impactrueno", 1},
			{"GruÒido", 1},
			{"Latigo", 2},
			{"Ataque Rapido", 3},
			{"Onda Trueno", 3},
			{"Doble Equipo", 4},
			{"Bola Voltio", 4},
			{"Atizar", 5},
			{"Moflete Estatico", 6},
			{"Chispa", 7},
			{"Rayo", 8},
			{"Agilidad", 9},
			{"Chispazo", 10},
			{"Pantalla de Luz", 11},
			{"Trueno", 12},
			{"Voltio Cruel", 13}
		},
		{"Raichu", 103}	// Piedra Trueno
	},
	PokemonData {
		"Raichu",
		"026",
		{
			"Electrico"
		},
		2,				// Crecimiento medio
		{
			60,	// Putos de Saluda
			90,	// Ataque
			55,	// Defensa
			90,	// Ataque Especial
			80,	// Defensa Especial
			110,	// Velocidad
			30.0,// Peso
			0.8,// Altura
			75,	// Indice de Captura
			122	// Experiencia Base
		},
		9,		// Electricidad Est·tica
		{
			{"PuÒo Trueno", 0}
		},
		{"None", 16}
	},
	PokemonData {	// Nidoran Hembra
		"NidoranH",
		"029",
		{
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{
			55,	// Putos de Saluda
			47,	// Ataque
			52,	// Defensa
			40,	// Ataque Especial
			40,	// Defensa Especial
			41,	// Velocidad
			7.0,// Peso
			0.4,// Altura
			235,// Indice de Captura
			59	// Experiencia Base
		},
		38,		// Punto TÛxico
		{
			{"AraÒazo", 1},
			{"GruÒido", 1},
			{"Latigo", 2},
			{"Doble Patada", 3},
			{"Picotazo Veneno", 4}
		},
		{"Nidorina", 5}
	},
	PokemonData {
		"Nidorina",
		"030",
		{
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{
			70,	// Putos de Saluda
			62,	// Ataque
			67,	// Defensa
			55,	// Ataque Especial
			55,	// Defensa Especial
			56,	// Velocidad
			20.0,// Peso
			0.8,// Altura
			120,// Indice de Captura
			117	// Experiencia Base
		},
		38,		// Punto TÛxico
		{
			{"Golpes Furia", 5},
			{"Mordisco", 6},
			{"Refuerzo", 7},
			{"Puas Toxicas", 7},
			{"Colmillo Veneno", 8},
			{"Camelo", 8},
			{"Triturar", 9}
		},
		{"Nidoqueen", 104}	// Piedra Lunar
	},
	PokemonData {
		"Nidoqueen",
		"031",
		{
			"Veneno",
			"Tierra"
		},
		0,				// Crecimiento parabÛlico
		{
			90,	// Putos de Saluda
			92,	// Ataque
			87,	// Defensa
			75,	// Ataque Especial
			85,	// Defensa Especial
			76,	// Velocidad
			60.0,// Peso
			1.3,// Altura
			45,// Indice de Captura
			194	// Experiencia Base
		},
		38,		// Punto TÛxico
		{
			{"Golpe Cuerpo", 0},
			{"Fuerza Bruta", 0},
			{"Guardia Baja", 6},
			{"Golpe Cuerpo", 9},
			{"Tierra Viva", 11},
			{"Fuerza Bruta", 14}
		},
		{"None", 16}
	},
	PokemonData {	// Nidoran Macho
		"NidoranM",
		"032",
		{
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{
			46,	// Putos de Saluda
			57,	// Ataque
			40,	// Defensa
			40,	// Ataque Especial
			40,	// Defensa Especial
			50,	// Velocidad
			9.0,// Peso
			0.5,// Altura
			235,// Indice de Captura
			60	// Experiencia Base
		},
		38,		// Punto TÛxico
		{
			{"Picotazo", 1},
			{"Malicioso", 1},
			{"Foco Energia", 2},
			{"Cornada", 2},
			{"Doble Patada", 3},
			{"Picotazo Veneno", 4}
		},
		{"Nidorino", 5}
	},
	PokemonData {
		"Nidorino",
		"033",
		{
			"Veneno"
		},
		0,				// Crecimiento parabÛlico
		{
			61,	// Putos de Saluda
			72,	// Ataque
			57,	// Defensa
			55,	// Ataque Especial
			55,	// Defensa Especial
			65,	// Velocidad
			19.5,// Peso
			0.9,// Altura
			120,// Indice de Captura
			118	// Experiencia Base
		},
		38,		// Punto TÛxico
		{
			{"Ataque Furia", 5},
			{"Refuerzo", 7},
			{"Puas Toxicas", 7},
			{"Camelo", 8},
			{"Puya Nociva", 9},
			{"Perforador", 10}
		},
		{"Nidoking", 104}	// Piedra Lunar
	},
	PokemonData {
		"Nidoking",
		"034",
		{
			"Veneno",
			"Tierra"
		},
		0,				// Crecimiento parabÛlico
		{
			81,	// Putos de Saluda
			102,	// Ataque
			77,	// Defensa
			85,	// Ataque Especial
			75,	// Defensa Especial
			85,	// Velocidad
			62.0,// Peso
			1.4,// Altura
			45,// Indice de Captura
			195	// Experiencia Base
		},
		38,		// Punto TÛxico
		{
			{"Golpe", 0},
			{"Megacuerno", 0},
			{"Guardia Baja", 6},
			{"Golpe", 9},
			{"Tierra Viva", 11},
			{"Megacuerno", 14}
		},
		{"None", 16}
	},
	PokemonData {
		"Mankey",
		"056",
		{
			"Lucha"
		},
		2,				// Crecimiento medio
		{
			40,	// Putos de Saluda
			80,	// Ataque
			35,	// Defensa
			35,	// Ataque Especial
			45,	// Defensa Especial
			70,	// Velocidad
			28.0,// Peso
			0.5,// Altura
			190,// Indice de Captura
			74	// Experiencia Base
		},
		72,		// Esp˙èitu Vital
		{
			{"AraÒazo", 1},
			{"Malicioso", 1},
			{"Foco Energ˙}", 2},
			{"Patada Baja", 3},
			{"Golpe K·rate", 4},
			{"Chirrido", 4},
			{"Golpes Furia", 5},
			{"Persecucion", 6},
			{"Buena Baza", 7}
		},
		{"Primeape", 8}
	},
	PokemonData {
		"Primeape",
		"057",
		{
			"Lucha"
		},
		2,				// Crecimiento medio
		{
			65,	// Putos de Saluda
			105,	// Ataque
			60,	// Defensa
			60,	// Ataque Especial
			70,	// Defensa Especial
			95,	// Velocidad
			32.0,// Peso
			1.0,// Altura
			75,// Indice de Captura
			149	// Experiencia Base
		},
		72,		// Esp˙èitu Vital
		{
			{"Furia", 8},
			{"Movimiento Sismico", 9},
			{"Contoneo", 10},
			{"Ida y Vuelta", 10},
			{"Tajo Cruzado", 11},
			{"Chirrido", 4},
			{"Golpe", 12},
			{"Enfado", 13},
			{"A Bocarrajo", 14},
			{"Sacrificio", 15}
		},
		{"None", 16}
	}
};





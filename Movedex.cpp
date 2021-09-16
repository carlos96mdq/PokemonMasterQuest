/*
 * Movedex.cpp
 */

/******************INCLUDES******************/
#include "Movedex.h"

/****************** FUNCTIONS ******************/
Move findMove(std::string move_chosed) {
	bool valid_move = false;
	while(!valid_move) {
		std::vector<Move>::iterator it = std::find_if(movedex.begin(), movedex.end(), [move_chosed](Move move) {return move_chosed == move.name;});
		if(it != movedex.end()) {
			valid_move = true;
			return *it;	// Me devuelve una estructura Move
		} else {
			std::cout << "Nombre de Pokemon no v·lido" << std::endl
					  << "Elija otro nombre de Pokemon: ";
			std::cin >> move_chosed;
		}
	}
}

float getEffectiveness(std::string move_type, std::vector<std::string> pokemon_types) {
	float effectiveness {1.0};
	if(move_type == "Acero") {
		for(auto type: pokemon_types) {
			if(type == "Hada" || type == "Hielo" || type == "Roca")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Agua" || type == "Electrico" || type == "Fuego")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Agua") {
		for(auto type: pokemon_types) {
			if(type == "Fuego" || type == "Roca" || type == "Tierra")
				effectiveness *= 2;
			else if(type == "Agua" || type == "Dragon" || type == "Planta")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Bicho") {
		for(auto type: pokemon_types) {
			if(type == "Planta" || type == "Psiquico" || type == "Siniestro")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Fantasma" || type == "Fuego" || type == "Hada" || type == "Lucha" || type == "Veneno" || type == "Volador")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Dragon") {
		for(auto type: pokemon_types) {
			if(type == "Dragon")
				effectiveness *= 2;
			else if(type == "Acero")
				effectiveness *= 0.5;
			else if(type == "Hada")
				effectiveness *= 0;
		}
	} else if(move_type == "Electrico") {
		for(auto type: pokemon_types) {
			if(type == "Agua" || type == "Volador")
				effectiveness *= 2;
			else if(type == "Dragon" || type == "Electrico" || type == "Planta")
				effectiveness *= 0.5;
			else if(type == "Tierra")
				effectiveness *= 0;
		}
	} else if(move_type == "Fantasma") {
		for(auto type: pokemon_types) {
			if(type == "Fantasma" || type == "Psiquico")
				effectiveness *= 2;
			else if(type == "Siniestro")
				effectiveness *= 0.5;
			else if(type == "Normal")
				effectiveness *= 0;
		}
	} else if(move_type == "Fuego") {
		for(auto type: pokemon_types) {
			if(type == "Acero" || type == "Bicho" || type == "Hielo" || type == "Planta")
				effectiveness *= 2;
			else if(type == "Agua" || type == "Dragon" || type == "Fuego" || type == "Roca")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Hada") {
		for(auto type: pokemon_types) {
			if(type == "Dragon" || type == "Lucha" || type == "Siniestro")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Fuego" || type == "Veneno")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Hielo") {
		for(auto type: pokemon_types) {
			if(type == "Dragon" || type == "Planta" || type == "Tierra" || type == "Volador")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Agua" || type == "Fuego" || type == "Hielo")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Lucha") {
		for(auto type: pokemon_types) {
			if(type == "Acero" || type == "Hielo" || type == "Normal" || type == "Roca" || type == "Siniestro")
				effectiveness *= 2;
			else if(type == "Bicho" || type == "Hada" || type == "Psiquico" || type == "Veneno" || type == "Volador")
				effectiveness *= 0.5;
			else if(type == "Fantasma")
				effectiveness *= 0;
		}
	} else if(move_type == "Normal") {
		for(auto type: pokemon_types) {
			if(type == "Acero" || type == "Roca")
				effectiveness *= 0.5;
			else if(type == "Fantasma")
				effectiveness *= 0;
		}
	} else if(move_type == "Planta") {
		for(auto type: pokemon_types) {
			if(type == "Agua" || type == "Roca" || type == "Tierra")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Bicho" || type == "Dragon" || type == "Fuego" || type == "Planta" || type == "Veneno" || type == "Volador")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Psiquico") {
		for(auto type: pokemon_types) {
			if(type == "Lucha" || type == "Veneno")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Psiquico")
				effectiveness *= 0.5;
			else if(type == "Siniestro")
				effectiveness *= 0;
		}
	} else if(move_type == "Roca") {
		for(auto type: pokemon_types) {
			if(type == "Bicho" || type == "Fuego" || type == "Hielo" || type == "Volador")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Lucha" || type == "Tierra")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Siniestro") {
		for(auto type: pokemon_types) {
			if(type == "Fantasma" || type == "Psiquico")
				effectiveness *= 2;
			else if(type == "Hada" || type == "Lucha" || type == "Siniestro")
				effectiveness *= 0.5;
		}
	} else if(move_type == "Tierra") {
		for(auto type: pokemon_types) {
			if(type == "Acero" || type == "Electrico" || type == "Electrico" || type == "Roca" || type == "Veneno")
				effectiveness *= 2;
			else if(type == "Bicho" || type == "Planta")
				effectiveness *= 0.5;
			else if(type == "Volador")
				effectiveness *= 0;
		}
	} else if(move_type == "Veneno") {
		for(auto type: pokemon_types) {
			if(type == "Hada" || type == "Planta")
				effectiveness *= 2;
			else if(type == "Fantasma" || type == "Roca" || type == "Tierra" || type == "Veneno")
				effectiveness *= 0.5;
			else if(type == "Acero")
				effectiveness *= 0;
		}
	} else if(move_type == "Volador") {
		for(auto type: pokemon_types) {
			if(type == "Bicho" || type == "Lucha" || type == "Planta")
				effectiveness *= 2;
			else if(type == "Acero" || type == "Electrico" || type == "Roca")
				effectiveness *= 0.5;
		}
	}

	if(effectiveness == 2.0)
		std::cout << "El movimiento es super efectivo" << std::endl;
	else if(effectiveness == 4.0)
		std::cout << "El movimiento es ultra efectivo" << std::endl;
	else if(effectiveness == 0.5)
		std::cout << "El movimiento no es muy efectivo" << std::endl;
	else if(effectiveness == 0.25)
		std::cout << "El movimiento no es nada efectivo" << std::endl;
	else if(effectiveness == 0)
		std::cout << "El Pokemon enemigo es inmune al movimiento" << std::endl;
	return effectiveness;
}

int getPriority(std::string move_chosed) {
	std::vector<Move>::iterator it = std::find_if(movedex.begin(), movedex.end(), [move_chosed](Move move) {return move_chosed == move.name;});
	if(it != movedex.end())
		return it->priority;	// Me devuelve la prioridad del movimiento
	else {
		std::cout << "Nombre del Movimiento no v·lido" << std::endl;
		return 0;
	}
}

/******************MOVEDEX******************/
/*En esta secciÛn se alamacenar·n a todos los Movimientos
 */
std::vector<Move> movedex {
	Move {
		"Agilidad",	// Nombre
		"Psiquico",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		0,		// Objetivo usuario
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Velocidad"},
		2,
		" ha subido su Velocidad en 2 niveles"
	},
	Move {
		"AraÒazo",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Ascuas",	// Nombre
		"Fuego",	// Tipo
		"Especial",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estado",
		{"Quemado"},
		0,
		" ahora esta Quemado"
	},
	Move {
		"Ataque Arena",	// Nombre
		"Tierra",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Precision"},
		-1,
		" ha bajado su Precision en 1 nivel"
	},
	Move {
		"Ataque Furia",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		15,	// Potencia
		85,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.0,	// Probabilidad del efecto
		"Cadena",
		{""},
		5,	// M·ximo numero de golpes
	},
	Move {
		"Ataque Rapido",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		1,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Atizar",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		80,	// Potencia
		75,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {	// Movimiento producto de la autolesiÛn por confusiÛn
		"Autolesion",	// Nombre
		"None",	// Tipo
		"Fisico",	// Clase
		40,	// Potencia
		0,	// PrecisiÛn
		0,	// Objetivo usuario
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Bola Voltio",	// Nombre
		"Electrico",	// Tipo
		"Especial",	// Clase
		1,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false,	// Efecto
	},
	Move {
		"Buena Baza",	// Nombre
		"Siniestro",	// Tipo
		"Fisico",	// Clase
		50,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Burbuja",	// Nombre
		"Agua",	// Tipo
		"Especial",	// Clase
		20,	// Potencia
		100,	// PrecisiÛn
		2,	// Objetivo enemigos
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estadistica",
		{"Velocidad"},
		-1,
		" ha bajado su Velocidad en 1 nivel"
	},
	Move {
		"Carga Toxica",	// Nombre
		"Veneno",	// Tipo
		"Especial",	// Clase
		65,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false,	// Efecto
	},
	Move {	// Se activa con la habilidad de Carga TÛxica
		"Carga Toxica+",	// Nombre
		"Veneno",	// Tipo
		"Especial",	// Clase
		130,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false,	// Efecto
	},
	Move {
		"Chispa",	// Nombre
		"Electrico",	// Tipo
		"Fisico",	// Clase
		65,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.3,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Chirrido",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		85,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		true,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Defensa"},
		-2,
		" ha bajado su Ataque en 2 niveles"
	},
	Move {
		"Chispazo",	// Nombre
		"Electrico",	// Tipo
		"Especial",	// Clase
		80,	// Potencia
		100,	// PrecisiÛn
		2,	// Objetivo enemigos
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.3,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Confusion",	// Nombre
		"Psiquico",	// Tipo
		"Especial",	// Clase
		50,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estado",
		{"Confundido"},
		0,
		" ahora esta Confundido"
	},
	Move {
		"Cornada",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		65,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Danza Aleteo",	// Nombre
		"Bicho",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		0,		// Objetivo usuario
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{
				"Ataque Especial",
				"Defensa Especial",
				"Velocidad"
		},
		1,
		" ha subido su Ataque Especial, Defensa Especial y Velocidad en 1 nivel"
	},
	Move {
		"Disparo Demora",	// Nombre
		"Bicho",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		95,// PrecisiÛn
		2,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Velocidad"},
		-1,
		" ha bajado su Velocidad en 1 nivel"
	},
	Move {	// Este movimiento es ˙nico en cuanto efecto, asÅEque no tomar como referencia para otros movimientos
		"Doble Ataque",	// Nombre
		"Bicho",	// Tipo
		"Fisico",	// Clase
		25,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.2,	// Probabilidad del efecto
		"Cadena",
		{"Envenenado"},
		2,	// M·ximo numero de golpes
	},
	Move {
		"Doble Equipo",	// Nombre
		"Normal",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		0,		// Objetivo usuario
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Evasion"},
		1,
		" ha subido su Evasion en 1 nivel"
	},
	Move {
		"Doble Patada",	// Nombre
		"Lucha",	// Tipo
		"Fisico",	// Clase
		30,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.0,	// Probabilidad del efecto
		"Cadena",
		{""},
		2,	// M·ximo numero de golpes
	},
	Move {
		"Drenadoras",	// Nombre
		"Planta",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		90,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Drenado"},
		0,
		" ahora esta Drenado"
	},
	Move {	// tiene un trato especial programado en las funciones ejecuteMove y receiveMove
		"Esfuerzo",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		1,	// Potencia	// Necesito hacerlo asÅEpar aque el cÛdigo funcione
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false,	// Efecto
	},
	Move {
		"Foco Energia",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		0,// PrecisiÛn
		0,	// Objetivo usuario
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Critico"},
		+2,
		" ha subido su Indice de Golpe Critico en 1 nivel"
	},
	Move {
		"Fortaleza",	// Nombre
		"Normal",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		0,		// Objetivo usuario
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Defensa"},
		1,
		" ha subido su Defensa en 1 nivel"
	},
	Move {
		"Garra Metal",	// Nombre
		"Acero",	// Tipo
		"Fisico",	// Clase
		50,	// Potencia
		95,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.1,	// Probabilidad del efecto
		"Estadistica",
		{"Ataque"},
		1,
		" ha aumentado su Ataque en 1 nivel"
	},
	Move {
		"Golpe Aereo",	// Nombre
		"Volador",	// Tipo
		"Fisico",	// Clase
		60,	// Potencia
		0,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Golpe Karata",	// Nombre
		"Lucha",	// Tipo
		"Fisico",	// Clase
		50,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		2,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Golpes Furia",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		18,	// Potencia
		80,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.0,	// Probabilidad del efecto
		"Cadena",
		{""},
		5,	// M·ximo numero de golpes
	},
	Move {
		"GruÒido",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		100,// PrecisiÛn
		2,	// Objetivo enemigos
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		true,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Ataque"},
		-1,
		" ha bajado su Ataque en 1 nivel"
	},
	Move {
		"Hipercolmillo",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		80,	// Potencia
		90,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estado",
		{"Amedrentado"},
		0,
		" ha retrocedido"
	},
	Move {
		"Impactrueno",	// Nombre
		"Electrico",	// Tipo
		"Especial",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Latigo",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		100,// PrecisiÛn
		2,	// Objetivo enemigos
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Defensa"},
		-1,
		" ha bajado su Defensa en 1 nivel"
	},
	Move {
		"Latigo Cepa",	// Nombre
		"Planta",	// Tipo
		"Fisico",	// Clase
		35,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Malicioso",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		100,// PrecisiÛn
		2,	// Objetivo enemigos
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Defensa"},
		-1,
		" ha bajado su Ataque en 1 nivel"
	},
	Move {
		"Moflete Estatico",	// Nombre
		"Electrico",	// Tipo
		"Fisico",	// Clase
		20,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Mordisco",	// Nombre
		"Siniestro",	// Tipo
		"Fisico",	// Clase
		60,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.3,	// Probabilidad del efecto
		"Estado",
		{"Amedrentado"},
		0,
		" ha retrocedido"
	},
	Move {
		"Onda Trueno",	// Nombre
		"Electrico",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Pantalla de Luz",	// Nombre
		"Psiquico",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		3,		// Objetivo equipo
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Campo",
		{"Pantalla de Luz"},
		0,
		" ha invocado Pantalla de Luz para todo el equipo"
	},
	Move {
		"Pantalla de Humo",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Precision"},
		-1,
		" ha bajado su Precision en 1 nivel"
	},
	Move {
		"Paralizador",	// Nombre
		"Planta",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		75,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Patada Baja",	// Nombre
		"Lucha",	// Tipo
		"Fisico",	// Clase
		1,	// Potencia	// Este valor es 1 para ayudar al cÛdigo
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false,	// Efecto
	},
	Move {
		"Persecucion",	// Nombre
		"Siniestro",	// Tipo
		"Fisico",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {	// Este movimiento es la versiÛn de PersecuciÛn cuando es utilizada durante el cambio del enemigo
		"Persecucion+",	// Nombre
		"Siniestro",	// Tipo
		"Fisico",	// Clase
		80,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Picotazo",	// Nombre
		"Volador",	// Tipo
		"Fisico",	// Clase
		35,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Picotazo Veneno",	// Nombre
		"Veneno",	// Tipo
		"Fisico",	// Clase
		15,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.3,	// Probabilidad del efecto
		"Estado",
		{"Envenenado"},
		0,
		" ahora esta Envenenado"
	},
	Move {
		"Pin Misil",	// Nombre
		"Bicho",	// Tipo
		"Fisico",	// Clase
		14,	// Potencia
		85,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.0,	// Probabilidad del efecto
		"Cadena",
		{""},
		5,	// M·ximo numero de golpes
	},
	Move {
		"Pistola Agua",	// Nombre
		"Agua",	// Tipo
		"Especial",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Placaje",	// Nombre
		"Normal",	// Tipo
		"Fisico",	// Clase
		35,	// Potencia
		95,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Polvo Veneno",	// Nombre
		"Veneno",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		75,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Envenenado"},
		0,
		" ahora esta Envenenado"
	},
	Move {
		"Psicorrayo",	// Nombre
		"Psiquico",	// Tipo
		"Especial",	// Clase
		65,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estado",
		{"Confundido"},
		0,
		" ahora esta Confundido"
	},
	Move {
		"Puas Toxicas",	// Nombre
		"Veneno",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		0,	// PrecisiÛn
		2,	// Objetivo enemigos
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Campo",
		{"Puas Toxicas"},
		0,
		" ahora tiene una nueva capa de Puas Toxicas en su campo"
	},
	Move {
		"Puya Nociva",	// Nombre
		"Veneno",	// Tipo
		"Fisico",	// Clase
		80,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.3,	// Probabilidad del efecto
		"Estado",
		{"Envenenado"},
		0,
		" ahora esta Envenenado"
	},
	Move {
		"Rayo",	// Nombre
		"Electrico",	// Tipo
		"Especial",	// Clase
		95,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Refugio",	// Nombre
		"Agua",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		0,		// Objetivo usuario
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Estadistica",
		{"Defensa"},
		1,
		" ha subido su Defensa en 1 nivel"
	},
	Move {
		"Somnifero",	// Nombre
		"Planta",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		75,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Dormido"},
		0,
		" ahora esta Dormido"
	},
	Move {
		"Supersonico",	// Nombre
		"Normal",	// Tipo
		"Estado",	// Clase
		0,	// Potencia
		55,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		true,	// SÛnico
		true,	// Efecto
		1.0,	// Probabilidad del efecto
		"Estado",
		{"Confundido"},
		0,
		" ahora esta Confundido"
	},
	Move {
		"Tornado",	// Nombre
		"Volador",	// Tipo
		"Especial",	// Clase
		40,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	// Se tiene que implementar
	Move {	// Variante de Tornado cuando el enemigo uso Vuelo, Caida Libre o Bote
		"Tornado+",	// Nombre
		"Volador",	// Tipo
		"Especial",	// Clase
		80,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		false	// Efecto
	},
	Move {
		"Trueno",	// Nombre
		"Electrico",	// Tipo
		"Especial",	// Clase
		120,	// Potencia
		70,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0.3,	// Probabilidad del efecto
		"Estado",
		{"Paralizado"},
		0,
		" ahora esta Paralizado"
	},
	Move {
		"Velo Sagrado",	// Nombre
		"Normal",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		3,		// Objetivo equipo
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Campo",
		{"Velo Sagrado"},
		0,
		" ha invocado Velo Sagrado para todo el equipo"
	},
	Move {
		"Viento Afin",	// Nombre
		"Volador",		// Tipo
		"Estado",	// Clase
		0,		// Potencia
		0,		// PrecisiÛn
		3,		// Objetivo equipo
		0,		// Prioridad
		0,		// Cr˙ëico
		false,
		false,
		true,
		1.0,	// Probabilidad del efecto
		"Campo",
		{"Viento Afin"},
		0,
		" ha subido su velocidad y la de todo el equipo con Viento Afin"
	},
	Move {
		"Viento Plata",	// Nombre
		"Bicho",	// Tipo
		"Especial",	// Clase
		60,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		1.1,	// Probabilidad del efecto
		"Estadistica",
		{
				"Ataque",
				"Defensa"
				"Ataque Especial"
				"Defensa Especial"
				"Velocidad"
		},
		1,
		" ha aumentado su Ataque, Defensa, Ataque Especial, Defensa Especial y Velocidad en 1 nivel"
	},
	Move {
		"Voltio Cruel",	// Nombre
		"Electrico",	// Tipo
		"Fisico",	// Clase
		90,	// Potencia
		100,// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		true,	// Contacto
		false,	// SÛnico
		true,	// Efecto
		0,	// Probabilidad del efecto
		"Retroceso",
		{},
		0.25,
	},
	Move {
		"Zumbido",	// Nombre
		"Bicho",	// Tipo
		"Especial",	// Clase
		90,	// Potencia
		100,	// PrecisiÛn
		1,	// Objetivo enemigo
		0,	// Prioridad
		0,	// Cr˙ëico
		false,	// Contacto
		true,	// SÛnico
		true,	// Efecto
		0.1,	// Probabilidad del efecto
		"Estadistica",
		{"Defensa Especial"},
		1,
		" ha bajado su Defensa Especial"
	}
};


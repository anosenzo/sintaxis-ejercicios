/*
 ============================================================================
 Name        : Cap2_AFD.c
 Author      : Alejandro Nosenzo
 Version     :
 Copyright   : Your copyright notice
 Description : Ejericcios 14 y 15 - Cap1 - Vol 2
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define CANT_ESTADOS 4
#define CANT_PALABRAS_ALFABETO 2
#define CANT_ESTADOS_FINALES 1

static const int COLUMNA_AS = 0;
static const int COLUMNA_OTRO_CARACTER = 1;

static const char CARACTER_FIN_PALABRA = '#';
static const char CARACTER_FIN_TEXTO = '\0';

int EsCadenaVacia(char *s);
int LongitudCadena(char *s);
char* Concantena2Cadenas(char* s1, char *s2, char *s3);

void InicializarTablaDeTransicionesDelAFD(
		int tablaDeTransciciones[CANT_ESTADOS][CANT_PALABRAS_ALFABETO]);
int ObtenerCantidadDePalabrasValidasConAFD(
		int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO],
		int estadosFinales[CANT_ESTADOS_FINALES], int estadoRechazo,
		char *cadenaAEvaluar);
int determinarProximoEstado(
		int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO],
		int estadoActual, char caracter);
int obtenerColumanAPartirDeCaracter(char caracter);
void mostrarCantidadPalabrasValidasPorAFD(
		int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO],
		int estadosFinales[CANT_ESTADOS_FINALES], int estadoRechazo,
		char *cadenaAEvaluar);
int esEstadoFinal(int estadoActual, int estadosFinales[CANT_ESTADOS_FINALES]);

int main(void) {

	char texto[] = "132bx#4azz,de#Azz#zAz#aaaaaaaaa#012345";

	int tablaDeTransciciones[CANT_ESTADOS][CANT_PALABRAS_ALFABETO] = { { 1, 1 },
			{ 2, 3 }, { 2, 2 }, {3,3} };

	//InicializarTablaDeTransicionesDelAFD(tablaDeTransciciones);

	int estadosFinales[] = { 2 };
	int estadoRechazo = 5;

	mostrarCantidadPalabrasValidasPorAFD(tablaDeTransciciones, estadosFinales,
			estadoRechazo, texto);

	return EXIT_SUCCESS;
}

void mostrarCantidadPalabrasValidasPorAFD(
		int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO],
		int estadosFinales[CANT_ESTADOS_FINALES], int estadoRechazo,
		char *cadenaAEvaluar) {

	printf("El AFD detecto %d palabras validas en la cadena: %s \n",
			ObtenerCantidadDePalabrasValidasConAFD(tablaDeTranscionDelAFD,
					estadosFinales, estadoRechazo, cadenaAEvaluar),
			cadenaAEvaluar);

}

// calculo que funciona sin pasar la dir. con & porque sera como los Strings que estoy pasando la direccion siempre en este caso
// (*)[3] o algo asi.
//
void InicializarTablaDeTransicionesDelAFD(
		int tablaDeTransciciones[CANT_ESTADOS][CANT_PALABRAS_ALFABETO]) {

	int tablaDeTranscicionesAux[CANT_ESTADOS][CANT_PALABRAS_ALFABETO] = { { 1,
			2, 0, 5, 6 }, { 5, 2, 0, 5, 6 }, { 5, 2, 3, 5, 4 },
			{ 1, 2, 0, 5, 6 }, { 6, 6, 6, 6, 6 }, { 5, 5, 0, 5, 6 }, { 6, 6, 6,
					6, 6 } };

	for (int i = 0; i < CANT_ESTADOS; i++) {

		for (int j = 0; j < CANT_PALABRAS_ALFABETO; j++) {
			tablaDeTransciciones[i][j] = tablaDeTranscicionesAux[i][j];
		}

	}

}

int ObtenerCantidadDePalabrasValidasConAFD(
		int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO],
		int estadosFinales[CANT_ESTADOS_FINALES], int estadoRechazo,
		char *cadenaAEvaluar) {

	int cantPalabrasReconocidasPorAFD = 0;

	int estadoInicial = 0;

	int estadoActual = estadoInicial;

	int i = 0;

	while (cadenaAEvaluar[i] != CARACTER_FIN_TEXTO) {

		estadoActual = estadoInicial;

		if(cadenaAEvaluar[i] == CARACTER_FIN_PALABRA){
			i++;
		}

		while (cadenaAEvaluar[i] != CARACTER_FIN_TEXTO //! esEstadoFinal(estadoActual, estadosFinales)
		&& cadenaAEvaluar[i] != CARACTER_FIN_PALABRA) {

			estadoActual = determinarProximoEstado(tablaDeTranscionDelAFD,
					estadoActual, cadenaAEvaluar[i]);

			i++;
		}

		if (esEstadoFinal(estadoActual, estadosFinales))
			cantPalabrasReconocidasPorAFD++;
	}

	return cantPalabrasReconocidasPorAFD;

}

int esEstadoFinal(int estadoActual, int estadosFinales[CANT_ESTADOS_FINALES]) {

	int encontrado = 0;

	for (int i = 0; i < CANT_ESTADOS_FINALES && encontrado == 0; i++) {

		if (estadoActual == estadosFinales[i])
			encontrado = 1;
	}

	return encontrado;

}

int determinarProximoEstado(
		int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO],
		int estadoActual, char caracter) {

	int columnaTablaDeTransicion = obtenerColumanAPartirDeCaracter(caracter);

	return tablaDeTranscionDelAFD[estadoActual][columnaTablaDeTransicion];

}

int obtenerColumanAPartirDeCaracter(char caracter) {

	int columnaCorrespondiente;

	switch (caracter) {
	case 'a':
	case 'A':
		columnaCorrespondiente = COLUMNA_AS;
		break;
	default:
		columnaCorrespondiente = COLUMNA_OTRO_CARACTER;
		break;
	}

	return columnaCorrespondiente;
}

int LongitudCadena(char *s) {

	int i = 0;

	while (s[i] != '\0') {

		i++;

	}

	return i;

}

int EsCadenaVacia(char *s) {

	return s[0] == '\0';

	if (s[0] == '\0')
		return 1;
	else
		return 0;
}

char* Concantena2Cadenas(char* s1, char *s2, char *s3) {

	int longitudCadena1 = LongitudCadena(s1);
	int longitudCadena2 = LongitudCadena(s2);

	for (int i = 0; i < longitudCadena1; i++) {

		s3[i] = s1[i];

	}

	for (int i = 0; i < longitudCadena2; i++) {

		s3[i + longitudCadena1] = s2[i];

	}

	s3[longitudCadena1 + longitudCadena2] = '\0';

	return s3;

}

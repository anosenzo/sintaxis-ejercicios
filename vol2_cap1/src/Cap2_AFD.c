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
#define CANT_PALABRAS_ALFABETO 3

static const int COLUMNA_SIGNO = 0;
static const int COLUMNA_DIGITO = 1;
static const int COLUMNA_OTRO_CARACTER = 2;

int EsCadenaVacia(char *s);
int LongitudCadena(char *s);
char* Concantena2Cadenas(char* s1, char *s2, char *s3);

void InicializarTablaDeTransicionesDelAFD(
		int tablaDeTransciciones[CANT_ESTADOS][CANT_PALABRAS_ALFABETO]);
int validarCadenaConAFD(int tablaDeTranscionDelAFD[4][3], char *cadenaAEvaluar);
int determinarProximoEstado(int tablaDeTranscionDelAFD[4][3], int estadoActual,
		char caracter);
int obtenerColumanAPartirDeCaracter(char caracter);
void mostrarValidacionDeAFD(int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO], char *cadenaAEvaluar);


int main(void) {

	char cadenaCorrecta[] = "-1234";
	char cadenaIncorrecta[] = "12*34";
	char cadenaCorrecta2[] = "4531235151";
	char cadenaIncorrecta2[] = "+-1234";

	int tablaDeTransciciones[CANT_ESTADOS][CANT_PALABRAS_ALFABETO];// = {
			//{ 1, 2, 3 }, { 3, 2, 3 }, { 3, 2, 3 }, { 3, 3, 3 } };

	InicializarTablaDeTransicionesDelAFD( tablaDeTransciciones);

	mostrarValidacionDeAFD(tablaDeTransciciones, cadenaCorrecta);
	mostrarValidacionDeAFD(tablaDeTransciciones, cadenaIncorrecta);
	mostrarValidacionDeAFD(tablaDeTransciciones, cadenaCorrecta2);
	mostrarValidacionDeAFD(tablaDeTransciciones, cadenaIncorrecta2);

	return EXIT_SUCCESS;
}

void mostrarValidacionDeAFD(int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO], char *cadenaAEvaluar){

	printf("El AFD %s la cadena: %s \n", validarCadenaConAFD(tablaDeTranscionDelAFD, cadenaAEvaluar) ? "RECONOCE" : "RECHAZA", cadenaAEvaluar);

}

// calculo que funciona sin pasar la dir. con & porque sera como los Strings que estoy pasando la direccion siempre en este caso
// (*)[3] o algo asi.
//
void InicializarTablaDeTransicionesDelAFD(
		int tablaDeTransciciones[CANT_ESTADOS][CANT_PALABRAS_ALFABETO]) {

	int tablaDeTranscicionesAux[CANT_ESTADOS][CANT_PALABRAS_ALFABETO] = { { 1, 2, 3 }, { 3, 2, 3 }, { 3, 2, 3 },
			{ 3, 3, 3 } };

	for(int i=0;i<CANT_ESTADOS;i++){

		for(int j=0;j<CANT_PALABRAS_ALFABETO;j++){
			tablaDeTransciciones[i][j] = tablaDeTranscicionesAux[i][j];
		}

	}

}

int validarCadenaConAFD(int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO], char *cadenaAEvaluar) {

	int i = 0;

	int estadoFinal = 2;
	int estadoInicial = 0;

	int estadoActual = estadoInicial;

	while (cadenaAEvaluar[i] != '\0') {
		estadoActual = determinarProximoEstado(tablaDeTranscionDelAFD,
				estadoActual, cadenaAEvaluar[i]);

		i++;
	}

	return estadoActual == estadoFinal;

}

int determinarProximoEstado(int tablaDeTranscionDelAFD[CANT_ESTADOS][CANT_PALABRAS_ALFABETO], int estadoActual,
		char caracter) {

	int columnaTablaDeTransicion = obtenerColumanAPartirDeCaracter(caracter);

	return tablaDeTranscionDelAFD[estadoActual][columnaTablaDeTransicion];

}

int obtenerColumanAPartirDeCaracter(char caracter) {

	int columnaCorrespondiente;

	switch (caracter) {
		case '+':
		case '-':
			columnaCorrespondiente = COLUMNA_SIGNO;
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			columnaCorrespondiente = COLUMNA_DIGITO;
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

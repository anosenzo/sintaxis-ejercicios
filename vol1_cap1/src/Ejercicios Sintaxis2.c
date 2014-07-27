/*
 ============================================================================
 Name        : Ejercicios.c
 Author      : Alejandro Nosenzo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int EsCadenaVacia(char *s);
int LongitudCadena(char *s);
char* Concantena2Cadenas(char* s1, char *s2, char *s3);

int main(void) {

	char cadenaAux1[] = "Hola";
	char cadenaAux2[] = "Chau";
	char cadenaAux3[LongitudCadena(cadenaAux1)+LongitudCadena(cadenaAux2)+1];

	char cadenaVacia[] = "";

	if (EsCadenaVacia(cadenaAux1))
		printf("La cadena %s es vacia \n", cadenaAux1);
	else
		printf("La cadena %s NO es vacia \n", cadenaAux1);

	if (EsCadenaVacia(cadenaVacia))
		printf("La cadena %s es vacia \n", cadenaVacia);
	else
		printf("La cadena %s NO es vacia \n", cadenaVacia);

	printf("La longitud de la cadena Hola es %i \n", LongitudCadena("Hola"));
	printf("La longitud de la cadena vacia es %i \n", LongitudCadena(""));

	printf("La concatenacion de Hola y Chau es %s \n", Concantena2Cadenas(cadenaAux1,cadenaAux2,cadenaAux3));

	return EXIT_SUCCESS;
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

		s3[i+longitudCadena1] = s2[i];

	}

	s3[longitudCadena1 + longitudCadena2 ] = '\0';

	return s3;

}

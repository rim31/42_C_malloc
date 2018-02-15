#include <stdio.h>
#include <stdlib.h>

int main() {

	int nombre = 0;
	int *tableau = NULL;
	int x = 0;

	printf ("Veuillez entrer la taille du tableau : ");
	scanf ("%d", &nombre);

	tableau = malloc(sizeof(int) * nombre);

	for (x = 0; x < nombre; ++x) {
		printf ("Veuillez entrer un nombre : ");
		scanf ("%d", &tableau[x]);
	}

	for (x = 0; x < nombre; ++x) {
		printf ("Nombre %d : %d\n", (x + 1), tableau[x]);
	}

	tableau = realloc(tableau, sizeof(int) * (nombre + 1));
	tableau[nombre] = 100;

	for (x = 0; x < nombre + 1; ++x) {
		printf ("Nombre %d : %d\n", (x + 1), tableau[x]);
	}

	free(tableau);

	return 0;

}

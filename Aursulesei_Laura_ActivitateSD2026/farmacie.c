#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Farmacie {
	unsigned short int idFarmacie;
	char* denumireFarmacie;
	float cifraAfaceriAnuala;
	char* numeFarmacistSef;
	unsigned char nrAngajati;
	char* localitate;
} Farmacie;

typedef struct NodABC {
	Farmacie* info;
	struct NodABC* left;
	struct NodABC* right;
} NodABC;

Farmacie* initializareFarmacie(unsigned short int idFarmacie, char* denumireFarmacie, float cifraAfaceriAnuala, char* numeFarmacistSef, unsigned char nrAngajati, char* localitate) {
	Farmacie* farmacie = (Farmacie*)malloc(sizeof(Farmacie));
	farmacie->idFarmacie = idFarmacie;
	farmacie->denumireFarmacie = (char*)malloc(strlen(denumireFarmacie) + 1);
	strcpy(farmacie->denumireFarmacie, denumireFarmacie);
	farmacie->cifraAfaceriAnuala = cifraAfaceriAnuala;
	farmacie->numeFarmacistSef = (char*)malloc(strlen(numeFarmacistSef) + 1);
	strcpy(farmacie->numeFarmacistSef, numeFarmacistSef);
	farmacie->nrAngajati = nrAngajati;
	farmacie->localitate = (char*)malloc(strlen(localitate) + 1);
	strcpy(farmacie->localitate, localitate);
	return farmacie;
}

NodABC* initializareNod(Farmacie* f) {
	NodABC* farmacie = (NodABC*)malloc(sizeof(NodABC));
	farmacie->info = f;
	farmacie->left = NULL;
	farmacie->right = NULL;
	return farmacie;
}

NodABC* inserareArbore(NodABC* radacina, Farmacie* f) {
	if (radacina == NULL) {
		return initializareNod(f);
	}
	if (f->idFarmacie < radacina->info->idFarmacie) {
		radacina->left = inserareArbore(radacina->left, f);
	}
	else if (f->idFarmacie > radacina->info->idFarmacie) {
		radacina->right = inserareArbore(radacina->right, f);
	}
	return radacina;
}

void afisareInOrdine(NodABC* radacina) {
	if (radacina != NULL) {
		afisareInOrdine(radacina->left);
		printf("%hu %s %5.2f %s %hhu %s \n", radacina->info->idFarmacie, radacina->info->denumireFarmacie, radacina->info->cifraAfaceriAnuala, radacina->info->numeFarmacistSef, radacina->info->nrAngajati, radacina->info->localitate);
		afisareInOrdine(radacina->right);
	}
}

void afisarePreOrdine(NodABC* radacina) {
	if (radacina != NULL) {
		printf("%hu %s %5.2f %s %hhu %s \n", radacina->info->idFarmacie, radacina->info->denumireFarmacie, radacina->info->cifraAfaceriAnuala, radacina->info->numeFarmacistSef, radacina->info->nrAngajati, radacina->info->localitate);
		afisarePreOrdine(radacina->left);
		afisarePreOrdine(radacina->right);
	}
}

void afisarePostOrdine(NodABC* radacina) {
	if (radacina != NULL) {
		afisarePostOrdine(radacina->left);
		afisarePostOrdine(radacina->right);
		printf("%hu %s %5.2f %s %hhu %s \n", radacina->info->idFarmacie, radacina->info->denumireFarmacie, radacina->info->cifraAfaceriAnuala, radacina->info->numeFarmacistSef, radacina->info->nrAngajati, radacina->info->localitate);
	}
}

void dezalocareArbore(NodABC* radacina) {
	if (radacina != NULL) {
		dezalocareArbore(radacina->left);
		dezalocareArbore(radacina->right);
		free(radacina->info->denumireFarmacie);
		free(radacina->info->localitate);
		free(radacina->info->numeFarmacistSef);
		free(radacina->info);
		free(radacina);
	}
}

int nrAngajatiPerLocalitate(NodABC* radacina, char* localitate) {
	int nrAngajati = 0;
	if (radacina != NULL) {
		if (strcmp(radacina->info->localitate, localitate) == 0) {
			nrAngajati += radacina->info->nrAngajati;
		}
		nrAngajati += nrAngajatiPerLocalitate(radacina->left, localitate);
		nrAngajati += nrAngajatiPerLocalitate(radacina->right, localitate);
	}
	return nrAngajati;
}

int main() {
	unsigned short int idFarmacie;
	char denumireFarmacie[40];
	float cifraAfaceriAnuala;
	char numeFarmacistSef[40];
	unsigned char nrAngajati;
	char localitate[40];

	NodABC* radacina = NULL;
	FILE* file = fopen("farmacii.txt", "r");
	while (fscanf(file, "%hu %s %f %s %hhu %s", &idFarmacie, denumireFarmacie, &cifraAfaceriAnuala, numeFarmacistSef, &nrAngajati, localitate) == 6) {
		Farmacie* farmacie = initializareFarmacie(idFarmacie, denumireFarmacie, cifraAfaceriAnuala, numeFarmacistSef, nrAngajati, localitate);
		radacina = inserareArbore(radacina, farmacie);
	}
	fclose(file);
	afisareInOrdine(radacina);
	printf("=======================\n");

	afisarePreOrdine(radacina);
	printf("=======================\n");

	afisarePostOrdine(radacina);
	printf("=======================\n");

	printf("%d\n", nrAngajatiPerLocalitate(radacina, "Bucuresti"));

	dezalocareArbore(radacina);

	//tema 3
	//al 2-lea subiect 1, 2, 3
}


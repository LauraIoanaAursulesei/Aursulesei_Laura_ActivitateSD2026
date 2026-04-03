//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Ticket {
//	unsigned int ticketID;
//	char* attendeeName;
//	char* access;
//	float price;
//	char scanned;
//} Ticket;
//
//typedef struct Nod {
//	Ticket* info;
//	struct Nod* next;
//} Nod;
//
//typedef struct HT {
//	Nod** vector;
//	int dimensiune;
//} HT;
//
//Ticket* initializareTicket(unsigned int ticketID, char* attendeeName, char* access, float price, char scanned) {
//	Ticket* ticket = (Ticket*)malloc(sizeof(Ticket));
//	ticket->ticketID = ticketID;
//	ticket->attendeeName = (char*)malloc(strlen(attendeeName) + 1);
//	strcpy(ticket->attendeeName, attendeeName);
//	ticket->access = (char*)malloc(strlen(access) + 1);
//	strcpy(ticket->access, access);
//	ticket->price = price;
//	ticket->scanned = scanned;
//	return ticket;
//}
//
//Nod* initializareNod(Ticket* ticket) {
//	Nod* nod = (Nod*)malloc(sizeof(Nod));
//	nod->next = NULL;
//	nod->info = ticket;
//	return nod;
//}
//
//HT* initializareHT(int dimensiune) {
//	HT* ht = (HT*)malloc(sizeof(HT));
//	ht->dimensiune = dimensiune;
//	ht->vector = (Nod**)malloc(dimensiune * sizeof(Nod*));
//	for (int i = 0; i < dimensiune; i++) {
//		ht->vector[i] = NULL;
//	}
//	return ht;
//}
//
//int functieHash(HT* ht, char* attendeeName) {
//	return(attendeeName[0] - 'A') % ht->dimensiune;
//	//return ticketID % ht->dimensiune; - PENTRU RESTUL CAZURILOR
//}
//
////inserare prin chaining
//HT* inserareInHT(HT* ht, Ticket* ticket) {
//	int pozitie = functieHash(ht, ticket->attendeeName);
//	Nod* nod = initializareNod(ticket);
//	if (ht->vector[pozitie] == NULL) {
//		ht->vector[pozitie] = nod;
//	}
//	else {
//		Nod* temp = ht->vector[pozitie];
//		while (temp->next != NULL) {
//			temp = temp->next;
//		}
//		temp->next = nod;
//	}
//	return ht;
//}
//
//void afisareLista(Nod* cap) {
//	if (cap != NULL) {
//		while (cap != NULL) {
//			printf("%hu %s %s %5.2f %c \n", cap->info->ticketID, cap->info->attendeeName, cap->info->access, cap->info->price, cap->info->scanned);
//			cap = cap->next;
//		}
//	}
//}
//
//void afisareHT(HT* ht) {
//	for (int i = 0; i < ht->dimensiune; i++) {
//		if (ht->vector[i] != NULL) {
//			printf("pozitie: %d \n", i);
//			afisareLista(ht->vector[i]);
//		}
//	}
//}
//
//void dezalocareHT(HT* ht) {
//	for (int i = 0; i < ht->dimensiune; i++) {
//		Nod* temp = ht->vector[i];
//		while (temp != NULL) {
//			Nod* nodDeSters = temp;
//			temp = temp->next;
//			free(nodDeSters->info->attendeeName);
//			free(nodDeSters->info->access);
//			free(nodDeSters->info);
//			free(nodDeSters);
//		}
//	}
//	free(ht->vector);
//	free(ht);
//}
//
//int nrBiletePerInvitat(HT* ht, char* attendeeName) {
//	int contor = 0;
//	for (int i = 0; i < ht->dimensiune; i++) {
//		Nod* nod = ht->vector[i];
//		while (nod != NULL) {
//			if (strcmp(nod->info->attendeeName, attendeeName) == 0) {
//				contor++;
//			}
//			nod = nod->next;
//		}
//	}
//	return contor;
//}
//
//int main() {
//	unsigned int ticketID;
//	char attendeeName[40];
//	char access[40];
//	float price;
//	char scanned;
//
//	HT* ht = initializareHT(10);
//	FILE* file = fopen("file.txt", "r");
//	while (fscanf(file, "%hu %s %s %f %c", &ticketID, attendeeName, access, &price, &scanned) == 5) {
//		Ticket* ticket = initializareTicket(ticketID, attendeeName, access, price, scanned);
//		ht = inserareInHT(ht, ticket);
//	}
//	fclose(file);
//	afisareHT(ht);
//
//	printf("=========================\n");
//	printf("%d", nrBiletePerInvitat(ht, "Mihai"));
//
//	dezalocareHT(ht);
//
//}
//

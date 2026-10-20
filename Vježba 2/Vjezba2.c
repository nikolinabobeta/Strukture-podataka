#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Osoba* Pozicija;

typedef struct Osoba {
	char ime[20];
	char prezime[20];
	int godRod;
	Pozicija next;
}osoba;

int InsertAfter(Pozicija, Pozicija);
int UnosP(char*, char*, int, Pozicija);
int Ispis(Pozicija);
int UnosK(char*, char*, int, Pozicija);
Pozicija Trazi(char*, Pozicija);
int Brisi(char*, Pozicija);

int main() {

	osoba head = { .ime = {0}, .prezime = {0}, .godRod = {0},.next = NULL };
	int i;
	char prezime[20], izbrisan[20];
	osoba* Osoba = NULL;
	Pozicija trazen;

	Osoba = (osoba*)malloc(5 * sizeof(osoba));
	if (Osoba == NULL) {
		printf("Pogreska pri alociranju memorije.");
		return -1;
	}

	for (i = 0;i < 5;i++) {
		printf("Unesi podatke za prvu osobu:\n");
		scanf("%19s %19s %d", Osoba[i].ime, Osoba[i].prezime, &Osoba[i].godRod);
	}

	for (i = 3;i > 0;i--)
		UnosP(Osoba[i].ime, Osoba[i].prezime, Osoba[i].godRod, &head);

	Ispis(head.next);

	UnosK(Osoba[4].ime, Osoba[4].prezime, Osoba[4].godRod, &head);

	Ispis(head.next);

	printf("Upisi prezime osobe koja se trazi:\n");
	scanf("%s", prezime);
	trazen = Trazi(prezime, head.next);
	printf("Trazeno prezime je: %s", trazen->prezime);

	printf("Osobu kojeg prezimena zelis izbrisari s liste?:\n");
	scanf("%s", izbrisan);
	Brisi(izbrisan, &head);

	Ispis(head.next);


	return 0;
}

int InsertAfter(Pozicija q, Pozicija p) {

	q->next = p->next;
	p->next = q;

	return 0;
}

int UnosP(char* _ime, char* _prezime, int _godRod, Pozicija P) {
	Pozicija Q;

	Q = (Pozicija)malloc(sizeof(osoba));
	if (Q == NULL) {
		printf("Greska pri alociranju memorije.");
		return -1;
	}

	strcpy(Q->ime, _ime);
	strcpy(Q->prezime, _prezime);
	Q->godRod = _godRod;

	InsertAfter(Q, P);

	Q->next = NULL;
	return 0;
}

int Ispis(Pozicija P) {

	if (P == NULL)
		printf("Lista prazna.");

	while (P != NULL) {
		printf("%s %s %d", P->ime, P->prezime, P->godRod);
		P = P->next;
	}

	return 0;
}

int UnosK(char* _ime, char* _prezime, int _godRod, Pozicija P) {

	Pozicija Q;

	Q = (Pozicija)malloc(sizeof(osoba));
	if (Q == NULL) {
		printf("Greska pri alociranju memorije.");
		return -1;
	}

	while (P->next != NULL)
		P = P->next;

	strcpy(Q->ime, _ime);
	strcpy(Q->prezime, _prezime);
	Q->godRod = _godRod;

	InsertAfter(Q, P);

	return 0;
}

Pozicija Trazi(char* _prezime, Pozicija P) {

	while (P != NULL) {
		if (strcmp(P->prezime, _prezime) == 0)
			break;
		P = P->next;
	}

	return P;
}

int Brisi(char* _prezime, Pozicija P) {
	Pozicija curr = P->next;
	Pozicija prev = P;

	curr = Trazi(_prezime, curr);
	if (curr == NULL) {
		printf("Oosba nije prona?ena.");
		return -1;
	}

	while (prev->next != curr)
		prev = prev->next;

	prev->next = curr->next;
	free(curr);

	return 0;
}

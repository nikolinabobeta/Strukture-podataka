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
int DodajIza( Pozicija, Pozicija);
int DodajIspred(Pozicija, Pozicija, Pozicija);
int Sortiraj(Pozicija);
int IspisDat(Pozicija);
int CitaDat(Pozicija);

int main() {

	osoba head = { .ime = {0}, .prezime = {0}, .godRod = {0},.next = NULL };
	int i;
	char prezime[20], izbrisan[20],iza[20],ispred[20];
	osoba* Osoba = NULL,*novaOsoba=NULL, * novaOsoba2 = NULL;
	Pozicija trazen, izaPoz,ispredPoz;
	

	Osoba = (osoba*)malloc(5 * sizeof(osoba));
	if (Osoba == NULL) {
		printf("Pogreska pri alociranju memorije.");
		return -1;
	}


	novaOsoba = (osoba*)malloc(sizeof(osoba));
	if (novaOsoba == NULL) {
		printf("Pogreska pri alociranju memorije.");
		return -1;
	}

	novaOsoba2 = (osoba*)malloc(sizeof(osoba));
	if (novaOsoba2 == NULL) {
		printf("Pogreska pri alociranju memorije.");
		return -1;
	}

	for (i = 0;i < 5;i++) {
		printf("Unesi podatke za osobu:\n");
		if(scanf("%19s %19s %d", Osoba[i].ime, Osoba[i].prezime, &Osoba[i].godRod)!=3)
			printf("Greska pri unosu podataka.");
	}

	for (i = 3;i >= 0;i--)
		UnosP(Osoba[i].ime, Osoba[i].prezime, Osoba[i].godRod, &head);

	Ispis(head.next);

	UnosK(Osoba[4].ime, Osoba[4].prezime, Osoba[4].godRod, &head);

	Ispis(head.next);

	printf("\nUpisi prezime osobe koja se trazi:\n");
	if(scanf("%s", prezime)!=1)
	printf("Greska pri unosu podataka.");

	trazen = Trazi(prezime, head.next);
	printf("\nTrazeno prezime je: %s", trazen->prezime);

	printf("\nOsobu kojeg prezimena zelis izbrisari s liste?:\n");
	if(scanf("%s", izbrisan)!=1)
		printf("Greska pri unosu podataka.");

	Brisi(izbrisan, &head);

	Ispis(head.next);

	printf("\nUpisi prezime osobe iza koje zelis dodati novu osobu\n");
	if(scanf("%s", iza)!=1)
		printf("Greska pri unosu podataka.");

	printf("\nUpisi ime, prezime i godinu rodenja nove osobe\n");
	if (scanf("%19s %19s %d", novaOsoba->ime, novaOsoba->prezime, &novaOsoba->godRod) != 3)
		printf("Greska pri unosu podataka.");

	izaPoz=Trazi(iza, head.next);

	if (izaPoz == NULL)
		printf("Osoba nije pronadena.");
	else
	    DodajIza( izaPoz, novaOsoba);

	Ispis(head.next);

	printf("\nUpisi prezime osobe ispred koje zelis dodati novu osobu\n");
	if(scanf("%s", ispred)!=1)
		printf("Greska pri unosu podataka.");

	printf("\nUpisi ime, prezime i godinu rodenja nove osobe\n");
	if(scanf("%s %s %d", novaOsoba2->ime, novaOsoba2->prezime, &novaOsoba2->godRod)!=3)
	printf("Greska pri unosu podataka.");

	ispredPoz = Trazi(ispred, head.next);

	if (ispredPoz == NULL)
		printf("Osoba nije pronadena.");
	else
		DodajIspred(ispredPoz, novaOsoba2,&head);

	Ispis(head.next);

	Sortiraj(&head);

	Ispis(head.next);

	IspisDat(head.next);

	CitaDat(head.next);

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

	return 0;
}

int Ispis(Pozicija P) {

	if (P == NULL)
		printf("Lista prazna.");

	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->godRod);
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
	Q->next = NULL;

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

int DodajIza( Pozicija iza, Pozicija nova) {
	
	if (iza != NULL&&nova!=NULL) {
		nova->next = iza->next;
		iza->next = nova;
	}

	return 0;
}

int DodajIspred(Pozicija ispred, Pozicija nova, Pozicija P) {

	if (ispred != NULL && nova != NULL) {
		while (P->next != NULL && P->next != ispred)
			P = P->next;
		if (P->next != NULL) {
			P->next = nova;
			nova->next = ispred;
		}
	}

	return 0;
}

int Sortiraj(Pozicija P) {
	Pozicija prev,temp,curr,end=NULL;

	while (P->next != end) {

		prev = P;
		curr = P->next;

		while (curr->next != end) {

			if (strcmp(curr->prezime, curr->next->prezime) > 0) {
				temp = curr->next;
				prev->next = temp;
				curr->next = temp->next;
				temp->next = curr;
				curr = temp;

			}
			prev = curr;
			curr = curr->next;
		}
		end = curr;
	}

	return 0;
}

int IspisDat(Pozicija P) {
	FILE* fp;

	fp = fopen("Osobe.txt", "w");
	if (fp == NULL){
		printf("Pogreska pri otvaranju datoteke.");
	    return -1;
}

	while (P != NULL) {
		fprintf(fp, "%19s %19s %d\n", P->ime, P->prezime, P->godRod);
		P = P->next;
	}

	fclose(fp);
	return 0;
}

int CitaDat(Pozicija P){
	FILE* fp;
	fp = fopen("Osobe.txt", "w");
	if (fp == NULL) {
		printf("Pogreska pri otvaranju datoteke.");
		return -1;
	}

	while (P != NULL) {
		if (fscanf(fp, "%19s %19s %d\n",
			P->ime, P->prezime, &P->godRod) != 3)
			printf("Greska pri unosu podataka.");

		P = P->next;
	}

	fclose(fp);
	return 0;
}
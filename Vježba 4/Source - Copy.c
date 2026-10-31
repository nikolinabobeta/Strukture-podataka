#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Polinom* Pozicija;

typedef struct Polinom {
	int koef;
	int pot;
	Pozicija next;

}polinom;

int CitDat(Pozicija, Pozicija, polinom*);
int InsertAfter(int, int, Pozicija);
int SortUnos(int, int, Pozicija);
int Ispis(Pozicija);
int ZbrojiP(Pozicija,Pozicija,Pozicija);
int MnoziP(Pozicija,Pozicija,Pozicija);

int main() {

	polinom head1 = { 0,0,NULL};
	polinom head2 = { 0,0,NULL };
	polinom head3 = { 0,0,NULL };
	polinom head4 = { 0,0,NULL };
	polinom polinomi[2];

	
	CitDat(&head1, &head2, polinomi);
	Ispis(head1.next);
	Ispis(head2.next);

	ZbrojiP(&head1, &head2,&head3);

	Ispis(head3.next);

	MnoziP(&head1, &head2,&head4);

	Ispis(head4.next);


	return 0;
}

int CitDat(Pozicija head1,Pozicija head2, polinom* poli) {
	Pozicija P = NULL;
	FILE* fp = NULL;
	int i = 0;

	fp = fopen("Polinomi.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	if (fp != NULL) {
		for (i = 0;i < 2;i++) {
			if (i == 0)
				P = head1;
			else
				P = head2;
			while (fscanf(fp, "%d %d", &poli[i].koef, &poli[i].pot) == 2) {
				if (P->next == NULL)
					InsertAfter(poli[i].koef, poli[i].pot, P);
				else SortUnos(poli[i].koef, poli[i].pot, P);
				if (fgetc(fp) == '\n')
					break;
			}
		}
	}
	fclose(fp);
	return 0;
}

int InsertAfter(int koef, int pot, Pozicija P) {

	Pozicija q=NULL;
	q = (Pozicija)malloc(sizeof(polinom));

	if (q == NULL) {
		printf("Greska pri alociranju memorije.");
		return -1;
	}

	q->koef = koef;
	q->pot = pot;

	P->next = q;
	q->next = NULL;

	return 0;
}

int SortUnos(int koef, int pot, Pozicija P) {
	Pozicija q = NULL;
	
	while (P->next != NULL && P->next->pot > pot)
		P = P->next;

	if (P->next != NULL && P->next->pot == pot) {
		P->next->koef += koef;
		return 0;
	}

	q = (Pozicija)malloc(sizeof(polinom));

	if (q == NULL) {
		printf("Greska pri alociranju memorije.");
		return -1;
	}

		q->koef = koef;
		q->pot = pot;

		q->next = P->next;
		P->next = q; 

	return 0;
}


int Ispis(Pozicija P) {

	while (P != NULL) {
		printf("%d %d ", P->koef, P->pot);
		P = P->next;
	}
	printf("\n");
	return 0;
}

int ZbrojiP(Pozicija a, Pozicija b, Pozicija c) {

	while (a->next != NULL && b->next != NULL) {
		if (a->next->pot == b->next->pot) {
			InsertAfter(a->next->koef + b->next->koef, a->next->pot, c);
			a = a->next;
			b = b->next;
		}
		else if (a->next->pot > b->next->pot) {
			InsertAfter(a->next->koef, a->next->pot, c);
			a = a->next;
		}
		else{
			InsertAfter(b->next->koef, b->next->pot, c);
			b = b->next;
		}
		c = c->next;
	}
	while (a->next != NULL) {
		InsertAfter(a->next->koef, a->next->pot, c);
		a = a->next;
		c = c->next;
	}
	while (a->next != NULL) {
		InsertAfter(b->next->koef, b->next->pot, c);
		b = b->next;
		c = c->next;
	}

	return 0;
}

int MnoziP(Pozicija a, Pozicija b, Pozicija c) {

	Pozicija p, q;
	p = a->next;
	q = b->next;

	while (p != NULL) {
		q = b->next;
		while (q != NULL) {
			SortUnos(p->koef * q->koef, p->pot + q->pot, c);
			q = q->next;
		}
		p = p->next;
	}

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Stog* Pozicija;

typedef struct Stog {
	int broj;
	Pozicija next;
}stog;

int Push(int,Pozicija);
int Pop(int*,Pozicija);
int Racunaj(char, Pozicija);

int main() {
	stog head = { .broj = 0,.next = NULL };
	char postfix[20] = { 0 };
	int br;
	int temp,temp2;

	FILE* fp = fopen("Postfix.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}

	while (fscanf(fp, "%19s", postfix) == 1) {
		if (sscanf(postfix, "%d", &br) == 1) {
			if (Push(br, &head) != 0) {
				fclose(fp);
				return -1;
			}
		}
		else {
			if (Racunaj(postfix[0], &head) != 0) {
				printf("Pogresan izraz postfixa.\n");
				while (Pop(&temp, &head) == 0);
				fclose(fp);
				return -1;
			}
		}
	}
	fclose(fp);
	if (Pop(&temp2, &head) != 0 || head.next != NULL) {
		printf("Pogresan izraz postfixa.\n");
		while (Pop(&temp2, &head) == 0);
	    return -1;
	}
	printf("%d\n", temp2);

		return 0;
	}

int Push(int br, Pozicija P) {
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(stog));
	if (q == NULL) {
		printf("Greska pri alociranju memorije.\n");
		return -1;
	}
	q->broj = br;

	q->next = P->next;
	P->next = q;

	return 0;
}

int Pop(int*vr, Pozicija P) {
	Pozicija q = P->next;
	if (q == NULL)
		return -1;

	*vr = q->broj;
	P->next = q->next;

	free(q);

	return 0;
}

int Racunaj(char op, Pozicija P) {
	int a,b,rez;
	if (Pop(&a, P) != 0)
		return -1;
	if (Pop(&b, P) != 0)
		return -1;

	switch (op) {
	case '+':
		rez = a + b;
		break;
	case '-':
		rez = b - a;
		break;
	case '*':
		rez = a * b;
		break;
	case '/':
		if (a == 0)
			return -1;
		else rez = b / a;
		break;
	default:
		return -1;
	}

	Push(rez, P);
	return 0;
}


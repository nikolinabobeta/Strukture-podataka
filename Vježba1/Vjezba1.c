#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct {
	char ime[20];
	char prezime[20];
	int bodovi;
}student;


int main() {
	int brojac = 0;
	int i;
	char buffer[50] = { 0 };
	float relBr[20];

	student* S = NULL;

	FILE* fp = fopen("polozili.txt","r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	while (fgets(buffer, 50, fp)!=NULL) {
		brojac++;
	}
	rewind(fp);

	S = (student*)(malloc(brojac * sizeof(student)));
	if (S == NULL) {
		printf("Greska pri alociranju memorije!");
		free(S);
		return -1;
	}

	for (i = 0;i < brojac;i++) {
		fscanf(fp, "%s %s %d", S[i].ime, S[i].prezime, &S[i].bodovi);
		relBr[i] = (float)S[i].bodovi / 100 * 100;
		printf("%s %s %d %f\n", S[i].ime, S[i].prezime, S[i].bodovi, relBr[i]);
	}

	free(S);
	fclose(fp);
	return 0;
}


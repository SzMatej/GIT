#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct prvok
{
	char kateg[52];
	char znacka[52];
	char predajca[102];
	char cena[100];
	char rok_vyroby[100];
	char stav_vozidla[202];
	int bol;					//ci hodnoty boli nacitane z file
	struct prvok *dalsi;
} PRVOK;

typedef struct zaznam 
{
	PRVOK *prvy;
} ZAZNAM;

FILE *open()
{
	FILE *fr;
	int x = 0;

	if ((fr = fopen("auta.TXT", "r")) == NULL)
		printf("Zaznamy neboli nacitane \n");

	return fr;
}

int pocet(FILE *fr)
{
	char c;
	int i = 0;

	if (fr != NULL)
		while ((c = getc(fr)) != EOF)
		{
			if (c == '$')
				i++;
		}
	rewind(fr);

	return i;
}

ZAZNAM *vytvor()
{
	ZAZNAM *zaznam = (ZAZNAM*)malloc(sizeof(ZAZNAM));
	zaznam->prvy = NULL; 
	return zaznam;
}

void vyprazdni(ZAZNAM *zaznam)
{
	PRVOK *tmpNext;
	while (zaznam->prvy != NULL) 
	{
		tmpNext = zaznam->prvy->dalsi;
		free(zaznam->prvy);
		zaznam->prvy = tmpNext;
	}
}

void uvolni(ZAZNAM **zaznam)
{
	vyprazdni(*zaznam);
	free(*zaznam);
	(*zaznam) = NULL;
}

void pridajnovy(ZAZNAM *zaznam, FILE *fr, int i, int n)
{
	PRVOK *novy = (PRVOK*)malloc(sizeof(PRVOK));

	fgetc(fr);
	fgetc(fr);
	fgets(novy->kateg, 100, fr);
	fgets(novy->znacka, 100, fr);
	fgets(novy->predajca, 102, fr);
	fgets(novy->cena, 100, fr);
	fgets(novy->rok_vyroby, 100, fr);
	fgets(novy->stav_vozidla, 202, fr);
	novy->bol = 0;
	if (i == n)
		novy->bol = 2;							//posledna hodnota - nema na konci enter

	novy->dalsi = NULL;
	
	if (zaznam->prvy == NULL) {
		zaznam->prvy = novy;
	}
	else {
		PRVOK* tmp = zaznam->prvy;
		while (tmp->dalsi != NULL) {
			tmp = tmp->dalsi;
		}
		tmp->dalsi = novy;
	}
}

void vypis(ZAZNAM *zaznam)
{
	PRVOK *tmp = zaznam->prvy;
	int i = 1, x = 1;

	while (tmp != NULL) 
	{
		printf("%d.\n", i++);
		printf("kategoria: %s", tmp->kateg);
		if (tmp->bol == 1) printf("\n");
		printf("znacka: %s", tmp->znacka);
		if (tmp->bol == 1) printf("\n");
		printf("predajca: %s", tmp->predajca);
		if (tmp->bol == 1) printf("\n");
		printf("cena: %s", tmp->cena);
		if (tmp->bol == 1) printf("\n");
		printf("rok_vyroby: %s", tmp->rok_vyroby);
		if (tmp->bol == 1) printf("\n");
		printf("stav_vozidla: %s", tmp->stav_vozidla);
		if (tmp->bol == 1) printf("\n");
		if (tmp->bol == 2) printf("\n");

		tmp = tmp->dalsi;
	}
}

void pridajvlastny(ZAZNAM *zaznam)
{
	PRVOK *novy = (PRVOK*)malloc(sizeof(PRVOK));
	PRVOK *tmp = zaznam->prvy;
	int n, i=1;

	scanf("%d\n", &n);
	gets_s(novy->kateg);
	gets_s(novy->znacka);
	gets_s(novy->predajca);
	gets_s(novy->cena);
	gets_s(novy->rok_vyroby);
	gets_s(novy->stav_vozidla);
	novy->bol = 1;

	if (zaznam->prvy == NULL) 
	{
		zaznam->prvy = novy;
		novy->dalsi = NULL;
	}

	else
	{
		while (i < n - 1)
		{
			if (tmp->dalsi != NULL)
				tmp = tmp->dalsi;
			i++;
		}

		if (n == 1)
		{
			novy->dalsi = tmp;
			zaznam->prvy = novy;
		}
		if (n > 1)
		{
			novy->dalsi = tmp->dalsi;
			tmp->dalsi = novy;
		}
	}
}

void vyhladaj(ZAZNAM *zaznam)
{
	int i = 1, x, cena1;
	PRVOK *tmp = zaznam->prvy;
	scanf("%d", &x);

	while (tmp != NULL)
	{
		cena1 = atoi(tmp->cena);
		if (cena1 <= x)
		{
			printf("%d.\n", i++);
			printf("kategoria: %s", tmp->kateg);
			if (tmp->bol == 1) printf("\n");
			printf("znacka: %s", tmp->znacka);
			if (tmp->bol == 1) printf("\n");
			printf("predajca: %s", tmp->predajca);
			if (tmp->bol == 1) printf("\n");
			printf("cena: %s", tmp->cena);
			if (tmp->bol == 1) printf("\n");
			printf("rok_vyroby: %s", tmp->rok_vyroby);
			if (tmp->bol == 1) printf("\n");
			printf("stav_vozidla: %s", tmp->stav_vozidla);
			if (tmp->bol == 1) printf("\n");
			if (tmp->bol == 2) printf("\n");
		}

		tmp = tmp->dalsi;
	}

	if (i == 1)
		printf("V ponuke su auta len s vyssiou cenou.\n");
}

void zmaz(ZAZNAM *zaznam)
{
	PRVOK *tmp = zaznam->prvy, *pomocny, *nazmaz;
	int length, n, m, i = 0, bol, cisloprvku = 0, cislozmazanych = 0;
	char c[52], d[52], malepismeno;
	
	d[49] = getchar();
	gets_s(d, 50);

	while (d[i] != NULL)
	{

		if (d[i] >= 'A' && d[i] <= 'Z')
			c[i] = d[i] + ('a' - 'A');
		else
			c[i] = d[i];

		i++;
	}

	while (tmp != NULL)
	{

		cisloprvku++;
		length = sizeof(tmp->znacka);
		bol = 0;

		for (n = 0; n < length; n++)
		{
			for (m = 0; m < i; m++)
			{
				if (tmp->znacka[n + m] >= 'A' && tmp->znacka[n + m] <= 'Z')
					malepismeno = tmp->znacka[n + m] + ('a' - 'A');
				else
					malepismeno = tmp->znacka[n + m];

				if (malepismeno == c[m])
					bol++;
				else
				{
					bol = 0;
					break;
				}
			}

			if (bol == i)
				break;
		}

		tmp = tmp->dalsi;

		if (bol == i)
		{

			pomocny = zaznam->prvy;
			if (cisloprvku == 1)
			{
				zaznam->prvy = zaznam->prvy->dalsi;
				free(pomocny);
				cisloprvku--;
			}

			else
			{
				for (m = 1; m < cisloprvku - 1; m++)
					pomocny = pomocny->dalsi;

				nazmaz = pomocny->dalsi;
				pomocny->dalsi = pomocny->dalsi->dalsi;
				free(nazmaz);
				cisloprvku--;
			}

			cislozmazanych++;
		}
	}
	printf("Vymazalo sa %d zaznamov\n", cislozmazanych);
}

void uprav(ZAZNAM *zaznam)
{
	PRVOK *tmp = zaznam->prvy;
	int cen, length, n, m, i = 0, bol, cislozmenenych = 0;
	char c[50], d[50], malepismeno;

	char kateg[60];
	char znacka[52];
	char predajca[101];
	char cena[100];
	char rok_vyroby[100];
	char stav_vozidla[201];

	d[49] = getchar();
	gets_s(d);
	scanf("%d", &cen);

	d[49] = getchar();
	gets_s(kateg);
	gets_s(znacka);
	gets_s(predajca);
	gets_s(cena);
	gets_s(rok_vyroby);
	gets_s(stav_vozidla);

	while (d[i] >= 'a' && d[i] <= 'z' || d[i] >= 'A' && d[i] <= 'Z' || d[i] == ' ')
	{

		if (d[i] >= 'A' && d[i] <= 'Z')
			c[i] = d[i] + ('a' - 'A');
		else
			c[i] = d[i];

		i++;
	}

	while (tmp != NULL)
	{

		length = sizeof(tmp->znacka);
		bol = 0;

		for (n = 0; n < length; n++)
		{
			for (m = 0; m < i; m++)
			{
				if (tmp->znacka[n + m] >= 'A' && tmp->znacka[n + m] <= 'Z')
					malepismeno = tmp->znacka[n + m] + ('a' - 'A');
				else
					malepismeno = tmp->znacka[n + m];

				if (malepismeno == c[m])
					bol++;
				else
				{
					bol = 0;
					break;
				}
			}

			if (bol == i)
				break;
		}

		if (bol == i && cen == atoi(tmp->cena))
		{
			strcpy(tmp->kateg, kateg);
			strcpy(tmp->znacka, znacka);
			strcpy(tmp->predajca, predajca);
			strcpy(tmp->cena, cena);
			strcpy(tmp->rok_vyroby, rok_vyroby);
			strcpy(tmp->stav_vozidla, stav_vozidla);
			tmp->bol = 1;

			cislozmenenych++;
		}

		tmp = tmp->dalsi;
	}

	printf("Aktualizovalo sa %d zaznamov\n", cislozmenenych);
}

void main()
{
	FILE *fr = NULL;
	ZAZNAM  *zaznam = NULL;
	int n, i, x = 1;
	char c;

	while (x == 1)
	{
		scanf("%c", &c);
		if (c == 'k')
		{
			if (zaznam != NULL)
				uvolni(&zaznam);
			x = 0;
		}

		switch (c)
		{
		case 'n':
			fr = open();
			if (fr != NULL)
			{
				i = pocet(fr);

				if (zaznam != NULL)
					uvolni(&zaznam);
				zaznam = vytvor();

				if (zaznam != NULL)
				{
					n = 1;
					while (n <= i)
					{
						pridajnovy(zaznam, fr, i, n);
						n++;
					}
					printf("Nacitalo sa %d zaznamov \n", i);
				}
			}
			break;

		case 'v':
			if (zaznam != NULL)
				vypis(zaznam);
			break;

		case 'p':
			if (zaznam == NULL)
				zaznam = vytvor();
			pridajvlastny(zaznam);
			break;

		case 'z':
			if (zaznam != NULL)
				zmaz(zaznam);
			break;

		case 'h':
			if (zaznam != NULL)
				vyhladaj(zaznam);
			break;

		case 'a':
			if (zaznam != NULL)
				uprav(zaznam);
			break;
		}
	}
}

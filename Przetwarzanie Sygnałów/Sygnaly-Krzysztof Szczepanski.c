#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <locale.h>




void generuj_przebieg_funkcji(double* tablica_wspolczynnikow, double Dziedzina_dolna_granica, double Dziedzina_gorna_granica, double* Tablica_wynikowa_funkcji, int Rozmiar_tablicy_wynikowej)
{
	for (int i = floor(Dziedzina_dolna_granica); i < Rozmiar_tablicy_wynikowej; i++)
	{
		Tablica_wynikowa_funkcji[i] = tablica_wspolczynnikow[0] * sin(tablica_wspolczynnikow[1] * i + tablica_wspolczynnikow[2]) + tablica_wspolczynnikow[3];
	}
}

void drukuj_tablice(double* tablica_drukowana, int rozmiar_tablicy_drukowanej)
{
	for (int i = 0; i < rozmiar_tablicy_drukowanej; i++)
	{
		printf("%lf \n", tablica_drukowana[i]);
	}
}

void wpisz_wspolczynniki(double* tablica_wspolczynnikow)
{
	printf("Podaj wartosci wspolczynnikow funkcji \n");
	scanf_s("%lf", &tablica_wspolczynnikow[0]);
	scanf_s("%lf", &tablica_wspolczynnikow[1]);
	scanf_s("%lf", &tablica_wspolczynnikow[2]);
	scanf_s("%lf", &tablica_wspolczynnikow[3]);
}

void wpisz_dziedzine(double* Dziedzina_dolna_funkcji, double* Dziedzina_gorna_funkcji)
{
	printf("Podaj dolna granice dziedziny funkcji \n");
	scanf_s("%lf", &Dziedzina_dolna_funkcji);
	printf("Podaj gorna granice dziedziny funkcji \n");
	scanf_s("%lf", &Dziedzina_gorna_funkcji);
}

void generuj_szum(double* tablica_wejsciowa, double* tablica_zaszumiona, int rozmiar_tablicy)
{
	srand(time(NULL));

	for (int i = 0; i < rozmiar_tablicy; i++)
	{
		int j = rand() %(rand() %6 +2);

		if (j == 0)
			tablica_zaszumiona[i] = tablica_wejsciowa[i] + 0.0000005 * rand();
		else
			tablica_zaszumiona[i] = tablica_wejsciowa[i];
	}
}

void zapisz_tablice(double* tablica_wejsciowa, int rozmiar_tablicy, char* nazwa_pliku)
{
	FILE* plik;
	fopen_s(&plik ,nazwa_pliku, "w");

	if (plik == NULL)
	{
		printf("Nie udalo sie otworzyc pliku.\n");
		return;
	}

	for (int i = 0; i < rozmiar_tablicy; i++)
	{
		fprintf(plik, "%lf,", tablica_wejsciowa[i]);
	}

	fclose(plik);
}

int wpisz_rozmiar_tablicy()
{
	int i;
	int k = 1;

	while (k != 0)
	{
		printf("Podaj rozmiar tablicy wynikowej funkcji. Wpisz liczbe naturalna, rozna od 0. \n");
		scanf_s("%d", &i);

		if (i < 1)
		{
			printf("Wielkosc tablicy nie moze byc mniejsza od 1.\n");
		}

		else
			k = 0;
	}
	return i;
}

void wczytaj_przebieg_funkcji(double* Wczytana_tablica_wynikowa, int Rozmiar_wczytanej_tablicy_wynikowej, char* nazwa_pliku)
{
	FILE* plik;
	fopen_s(&plik, nazwa_pliku, "r");

	if (plik == NULL)
	{
		printf("Nie udalo sie otworzyc pliku.\n");
		return;
	}

	for (int i = 0; i < Rozmiar_wczytanej_tablicy_wynikowej; i++)
	{
		fscanf_s(plik, "%lf,", Wczytana_tablica_wynikowa[i]);
	}

	fclose(plik);
}

void wpisz_nazwe_pliku(char* nazwa_pliku)
{
	printf("Podaj nazwe pliku.\n");
	scanf_s("%255s", nazwa_pliku, 256);
}

void Zapisanie_funkcji(double* Tablica_do_zapisania, int Rozmiar_tablicy_do_zapisania)
{	
	int wybor_uzytkownika;
	char Nazwa_zapisanego_pliku[256];

	printf("Czy chcesz zapisac funkcje w obecnym stanie? Wpisz 1 lub 2.\n");
	scanf_s("%d", &wybor_uzytkownika);
	while (wybor_uzytkownika != 0)
	{
		switch (wybor_uzytkownika)
		{
		case 1:
			wpisz_nazwe_pliku(Nazwa_zapisanego_pliku);

			zapisz_tablice(Tablica_do_zapisania, Rozmiar_tablicy_do_zapisania, Nazwa_zapisanego_pliku);

			printf("Zapisano tablice.\n");

			wybor_uzytkownika = 0;

			break;
		case 2:
			printf("Nie zapisano tablicy.\n");

			wybor_uzytkownika = 0;

			break;
		default:
			printf("Zly parametr!\n");

			break;
		}
	}
}

void Filtruj_tablice_medianowo(double* Tablica_wejsciowa, int Rozmiar_tablicy, double* Tablica_odfiltrowana)
{
	Tablica_odfiltrowana[0] = Tablica_wejsciowa[0];

	for (int i = 0; i < Rozmiar_tablicy - 1; i++)
	{
		if ((Tablica_wejsciowa[1 + 1] <= Tablica_wejsciowa[i + 2] && Tablica_wejsciowa[1 + 1] >= Tablica_wejsciowa[i]) || (Tablica_wejsciowa[1 + 1] >= Tablica_wejsciowa[i + 2] && Tablica_wejsciowa[1 + 1] <= Tablica_wejsciowa[i]))
			Tablica_odfiltrowana[i + 1] = Tablica_wejsciowa[i + 1];
		else if (Tablica_wejsciowa[i + 1] <= Tablica_wejsciowa[i + 1] && Tablica_wejsciowa[i + 1] <= Tablica_wejsciowa[i])
		{
			if (Tablica_wejsciowa[i] >= Tablica_wejsciowa[i + 2])
				Tablica_odfiltrowana[i + 1] = Tablica_wejsciowa[i];
			else
				Tablica_odfiltrowana[i + 1] = Tablica_wejsciowa[i + 2];
		}
		else if (Tablica_wejsciowa[i + 1] >= Tablica_wejsciowa[i + 1] && Tablica_wejsciowa[i + 1] >= Tablica_wejsciowa[i])
		{
			if (Tablica_wejsciowa[i] >= Tablica_wejsciowa[i + 2])
				Tablica_odfiltrowana[i + 1] = Tablica_wejsciowa[i + 2];
			else
				Tablica_odfiltrowana[i + 1] = Tablica_wejsciowa[i];
		}
	}

	Tablica_odfiltrowana[Rozmiar_tablicy] = Tablica_wejsciowa[Rozmiar_tablicy];

	printf("Odfiltrowano\n");
}

void filtruj_tablice_srednia(double* Tablica_wejsciowa, int Rozmiar_tablicy, double* Tablica_odfiltrowana)
{
	Tablica_odfiltrowana[0] = Tablica_wejsciowa[0];

	for (int i = 0; i < Rozmiar_tablicy - 1; i++)
	{
		Tablica_odfiltrowana[i + 1] = (Tablica_wejsciowa[i] + Tablica_wejsciowa[i + 1] + Tablica_wejsciowa[i + 2]) / 3;
	}
	
	Tablica_odfiltrowana[Rozmiar_tablicy] = Tablica_wejsciowa[Rozmiar_tablicy];

	printf("Odfiltrowano\n");
}

int main()
{
	int Rozmiar_tablicy_wynikowej;
	double tablica_wspolczynnikow_funkcji[4];
	double Dziedzina_gorna_granica_main = 0;
	double Dziedzina_dolna_granica_main = 0;
	double *Tablica_wynikowa_funkcji_main;
	double *Tablica_zaszumiona_main;
	double* Tablica_odfiltrowana_main;
	int Opcja_pozyskania_tablicy = 5;
	int Opcja_operacji_na_tablicy = 5;
	int Opcja_wyboru_filtra = 5;
	int Opcja_menu = 5;
	char nazwa_pliku[256];

	Rozmiar_tablicy_wynikowej = wpisz_rozmiar_tablicy();

	Tablica_wynikowa_funkcji_main = malloc(Rozmiar_tablicy_wynikowej * sizeof(double));
	Tablica_zaszumiona_main = malloc(Rozmiar_tablicy_wynikowej * sizeof(double));
	Tablica_odfiltrowana_main = malloc(Rozmiar_tablicy_wynikowej * sizeof(double));



	while (Opcja_menu != 0)
	{
		printf("Chcesz wczytac (wpisz 1) funkcje z pliku czy ja wygenerowac (wpisz 2)? \n");
		scanf_s("%d", &Opcja_pozyskania_tablicy);

		switch (Opcja_pozyskania_tablicy)
		{
		case 1:

			system("cls");

			wczytaj_przebieg_funkcji(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej, nazwa_pliku);

			drukuj_tablice(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej);

			Opcja_menu = 0;
			
			break;

		case 2:

			system("cls");

			wpisz_wspolczynniki(tablica_wspolczynnikow_funkcji);
			wpisz_dziedzine(&Dziedzina_dolna_granica_main, &Dziedzina_gorna_granica_main);

			generuj_przebieg_funkcji(tablica_wspolczynnikow_funkcji, Dziedzina_gorna_granica_main, Dziedzina_dolna_granica_main, Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej);

			drukuj_tablice(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej);

			Zapisanie_funkcji(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej);

			Opcja_menu = 0;
			
			break;

		default:
			printf("Zly parametr pozyskania funkcji!\n");

			break;
		}
	}

	Opcja_menu = 5;

	while (Opcja_menu != 0)
	{ 
		printf("Chcesz zaszumic funkcje (wpisz 1) czy ja odfiltrowac (wpisz 2)?\n");
		scanf_s("%d", &Opcja_operacji_na_tablicy);

		switch (Opcja_operacji_na_tablicy)
		{
		case 1:

			system("cls");

			generuj_szum(Tablica_wynikowa_funkcji_main, Tablica_zaszumiona_main, Rozmiar_tablicy_wynikowej);

			drukuj_tablice(Tablica_zaszumiona_main, Rozmiar_tablicy_wynikowej);

			Zapisanie_funkcji(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej);

			Opcja_menu = 0;

			break;
		case 2:

			printf("Wybierz rodzaj filtra. Medianowy (wpisz 1), wartosci sredniej (wpisz 2).\n");
			scanf_s("%d", &Opcja_wyboru_filtra);

			switch (Opcja_wyboru_filtra)
			{
			case 1:

				system("cls");

				Filtruj_tablice_medianowo(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej, Tablica_odfiltrowana_main);

				drukuj_tablice(Tablica_odfiltrowana_main, Rozmiar_tablicy_wynikowej);

				Zapisanie_funkcji(Tablica_odfiltrowana_main, Rozmiar_tablicy_wynikowej);

				free(Tablica_wynikowa_funkcji_main);
				free(Tablica_zaszumiona_main);
				free(Tablica_odfiltrowana_main);

				Opcja_menu = 0;

				break;

			case 2:

				system("cls");

				filtruj_tablice_srednia(Tablica_wynikowa_funkcji_main, Rozmiar_tablicy_wynikowej, Tablica_odfiltrowana_main);

				drukuj_tablice(Tablica_odfiltrowana_main, Rozmiar_tablicy_wynikowej);

				Zapisanie_funkcji(Tablica_odfiltrowana_main, Rozmiar_tablicy_wynikowej);

				free(Tablica_wynikowa_funkcji_main);
				free(Tablica_zaszumiona_main);
				free(Tablica_odfiltrowana_main);

				Opcja_menu = 0;

				break;

			default:
				printf("Zly parametr wyboru filtra!\n");	
			}
			break;
		default:
			printf("Zly parametr operacji na funkcji!\n");
		}


	printf("\nProgram sie wylacza.");
	}
}
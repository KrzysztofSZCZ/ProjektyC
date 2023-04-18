#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#pragma warning(disable : 4996)

struct autobus {
	char numer_autobusu[40];
	int liczba_miejsc;
	int cena_biletu;
	char miejsce_docelowe[40];
};

#define SROTUJ_CENA_BILETU 1
#define SORTUJ_MIEJSCEM_DOCELOWYM 2


void wpisz_dane_do_autobusu(struct autobus* wpisywany) {
	
	char wpisany_numer_autobusu[40];
	char wpisane_miejsce_docelowe[40];
	int wpisana_liczba_miejsc = 0;
	int wpisana_cena_biletu = 0;
	int i;
	char parametr_do_zmienijszania_liter;
	int parametr_poprawnego_wpisania_danych1 = 1;
	int parametr_poprawnego_wpisania_danych2 = 1;

	printf("UWAGA: Wszytskie wpisane litery, zostana zmienone na male.\n");
	printf("Wpisz numer autobusu.\n");
	scanf_s("%39s", &wpisany_numer_autobusu, 40);

	while (parametr_poprawnego_wpisania_danych1 != 0)
	{
		
		printf("Wpisz liczbe miejsc w autobusie.\n");
		scanf_s("%d", &wpisana_liczba_miejsc);
	
		if (wpisana_liczba_miejsc <= 0)
			printf("Podano niepoprawna liczbe miejsc!\n");

		else
			parametr_poprawnego_wpisania_danych1 = 0;
	}

	while (parametr_poprawnego_wpisania_danych2 != 0)
	{
		
		printf("Wpisz cene biletu w autobusie. Prosze podac liczbe naturalna, rozna od zera. (Bedziesz mogl ja zmienic na losowa w innej funkcji) \n");
		scanf_s("%d", &wpisana_cena_biletu);
	
		if (wpisana_cena_biletu <= 0)
			printf("Podano nieporawna cene biletu!\n");

		else
			parametr_poprawnego_wpisania_danych2 = 0;

	}
	
	printf("Wpisz miejsce docelowe autobusu.\n");
	scanf_s("%39s", &wpisane_miejsce_docelowe, 40);

	for (i = 0; i < 40; i++)
	{
		parametr_do_zmienijszania_liter = tolower(wpisany_numer_autobusu[i]);
		wpisany_numer_autobusu[i] = parametr_do_zmienijszania_liter;
	}

	for (i = 0; i < 40; i++)
	{
		parametr_do_zmienijszania_liter = tolower(wpisane_miejsce_docelowe[i]);
		wpisane_miejsce_docelowe[i] = parametr_do_zmienijszania_liter;
	}

	strcpy(wpisywany->numer_autobusu, wpisany_numer_autobusu);
	strcpy(wpisywany->miejsce_docelowe, wpisane_miejsce_docelowe);
	wpisywany->cena_biletu = wpisana_cena_biletu;
	wpisywany->liczba_miejsc =wpisana_liczba_miejsc;

	printf("Wpisano dane do autobusu\n");
}

void zapisz_autobusy_do_pliku(struct autobus* zapisywana_lista, int liczba_zapisywanych_autobusow)
{
	char nazwa_zapisywanego_pliku[256];
	int parametr_wpisywania_do_pliku = 0;
	char zapisywany_numer[40];
	char zapisywane_miejsce_docelowe[40];
	int zapisywana_liczba_miejsc;
	int zapisywana_cena_biletu;

	printf("Podaj sciezke pliku .csv. ( Prosze wpisac rozszerzenie .csv)\n");
	scanf_s("%255s", nazwa_zapisywanego_pliku, 256);

	FILE* plik;

	fopen_s(&plik, nazwa_zapisywanego_pliku, "w");

	if (plik == NULL)
	{
		printf("Nie udalo sie zapisac pliku\n");
		return;
	}

	fprintf(plik, "Autobus:");
	fputs(";", plik);
	fprintf(plik, "Numer autobusu:");
	fputs(";", plik);
	fprintf(plik, "Liczba miejsc w autobusie:");
	fputs(";", plik);
	fprintf(plik, "Cena biletu w autobusie:");
	fputs(";", plik);
	fprintf(plik, "Miejsce docelowe autobusu:");
	fputs("\n", plik);

	for (parametr_wpisywania_do_pliku = 0; parametr_wpisywania_do_pliku < liczba_zapisywanych_autobusow; parametr_wpisywania_do_pliku++)
	{
		strcpy(zapisywany_numer, zapisywana_lista[parametr_wpisywania_do_pliku].numer_autobusu);
		strcpy(zapisywane_miejsce_docelowe, zapisywana_lista[parametr_wpisywania_do_pliku].miejsce_docelowe);
		zapisywana_liczba_miejsc = zapisywana_lista[parametr_wpisywania_do_pliku].liczba_miejsc;
		zapisywana_cena_biletu = zapisywana_lista[parametr_wpisywania_do_pliku].cena_biletu;

		fprintf(plik,"Autobus %d:", parametr_wpisywania_do_pliku);
		fputs(";", plik);
		fputs(zapisywany_numer, plik);
		fputs(";", plik);
		fprintf(plik, "%d", zapisywana_liczba_miejsc);
		fputs(";", plik);
		fprintf(plik, "%d", zapisywana_cena_biletu);
		fputs(";", plik);
		fputs(zapisywane_miejsce_docelowe, plik);
		fputs("\n", plik);
	}


	fclose(plik);

	printf("Zapisano autobusy do pliku\n");

}

void losuj_cene_biletu(struct autobus* losowany)
{
	int parametr_poprawnosci_wpisywania_dolu_przedzialu = 1;
	int parametr_poprawnosci_wpisywania_gory_przedzialu = 1;
	int dolna_granica_przedzialu;
	int gorna_granica_przedzialu;
	int wylosowana_cenu_biletu;

	while (parametr_poprawnosci_wpisywania_dolu_przedzialu != 0)
	{
		printf("Podaj dolna granice przedzialu, z ktorego zostanie wylosowana cena biletu w autobusie.\n Podaj liczbe naturalna\n");
		scanf_s("%d", &dolna_granica_przedzialu);

		if (dolna_granica_przedzialu < 0)
		{
			printf("Wpisana wartosc jest niepoprawna!\n");
		}

		else
			parametr_poprawnosci_wpisywania_dolu_przedzialu = 0;
	}

	while (parametr_poprawnosci_wpisywania_gory_przedzialu != 0)
	{
		printf("Podaj gorna granice przedzialu, z ktorego zostanie wylosowana cena biletu w autobusie.\n Podaj liczbe naturalna, wieksza niz dolna granica przedialu.\n");
		scanf_s("%d", &gorna_granica_przedzialu);

		if (gorna_granica_przedzialu < 0)
		{
			printf("Wpisana wartosc jest niepoprawna!\n");
		}

		else if (gorna_granica_przedzialu < dolna_granica_przedzialu)
		{
			printf("Gorna granica nie moze byc mniejsza niz dolna!\n");
		}

		else
			parametr_poprawnosci_wpisywania_gory_przedzialu = 0;
	}

	srand(time(NULL));

	wylosowana_cenu_biletu = dolna_granica_przedzialu + rand() % (gorna_granica_przedzialu - dolna_granica_przedzialu + 1);
	
	losowany->cena_biletu = wylosowana_cenu_biletu;

	printf("Wylosowano cene: %d\n", wylosowana_cenu_biletu);
}

void sortuj_liste_autobusow(struct autobus* lista_sortowana, int liczba_autobusow_w_liscie)
{
	struct autobus chwilowo_przechowujacy_dane;
	int parametr_petli_sortujacej1;
	int parametr_petli_sortujacej2;
	int wybrana_metoda_sortowania;
	int parametr_poprawnosci_wyboru_metody_sortowania = 1;

	while (parametr_poprawnosci_wyboru_metody_sortowania != 0)
	{
		printf("Wedlug czego chcesz sortowac? Wpisz 1- Ceny biletu 2- Miejsca docelowego\n");
		scanf_s("%d", &wybrana_metoda_sortowania);

		if (wybrana_metoda_sortowania == 1)
		{
			for (parametr_petli_sortujacej1 = 0; parametr_petli_sortujacej1 < liczba_autobusow_w_liscie - 1; parametr_petli_sortujacej1++)
			{
				for (parametr_petli_sortujacej2 = 0; parametr_petli_sortujacej2 < liczba_autobusow_w_liscie - 1 - parametr_petli_sortujacej1; parametr_petli_sortujacej2++)
				{
					if (lista_sortowana[parametr_petli_sortujacej2].cena_biletu > lista_sortowana[parametr_petli_sortujacej2 + 1].cena_biletu)
					{
						chwilowo_przechowujacy_dane.cena_biletu = lista_sortowana[parametr_petli_sortujacej2 + 1].cena_biletu;
						chwilowo_przechowujacy_dane.liczba_miejsc = lista_sortowana[parametr_petli_sortujacej2 + 1].liczba_miejsc;
						strcpy(chwilowo_przechowujacy_dane.miejsce_docelowe, lista_sortowana[parametr_petli_sortujacej2 + 1].miejsce_docelowe);
						strcpy(chwilowo_przechowujacy_dane.numer_autobusu, lista_sortowana[parametr_petli_sortujacej2 + 1].numer_autobusu);

						lista_sortowana[parametr_petli_sortujacej2 + 1].cena_biletu = lista_sortowana[parametr_petli_sortujacej2].cena_biletu;
						lista_sortowana[parametr_petli_sortujacej2 + 1].liczba_miejsc = lista_sortowana[parametr_petli_sortujacej2].liczba_miejsc;
						strcpy(lista_sortowana[parametr_petli_sortujacej2 + 1].miejsce_docelowe, lista_sortowana[parametr_petli_sortujacej2].miejsce_docelowe);
						strcpy(lista_sortowana[parametr_petli_sortujacej2 + 1].numer_autobusu, lista_sortowana[parametr_petli_sortujacej2].numer_autobusu);

						lista_sortowana[parametr_petli_sortujacej2].cena_biletu = chwilowo_przechowujacy_dane.cena_biletu;
						lista_sortowana[parametr_petli_sortujacej2].liczba_miejsc = chwilowo_przechowujacy_dane.liczba_miejsc;
						strcpy(lista_sortowana[parametr_petli_sortujacej2].miejsce_docelowe, chwilowo_przechowujacy_dane.miejsce_docelowe);
						strcpy(lista_sortowana[parametr_petli_sortujacej2].numer_autobusu, chwilowo_przechowujacy_dane.numer_autobusu);

					}
				}
			}

			parametr_poprawnosci_wyboru_metody_sortowania = 0;
		}

		else if (wybrana_metoda_sortowania == 2)
		{
			for (parametr_petli_sortujacej1 = 0; parametr_petli_sortujacej1 < liczba_autobusow_w_liscie - 1; parametr_petli_sortujacej1++)
			{
				for (parametr_petli_sortujacej2 = 0; parametr_petli_sortujacej2 < liczba_autobusow_w_liscie - 1 - parametr_petli_sortujacej1; parametr_petli_sortujacej2++)
				{
					if (strcoll(lista_sortowana[parametr_petli_sortujacej2].miejsce_docelowe, lista_sortowana[parametr_petli_sortujacej2 + 1].miejsce_docelowe) == 1)
					{
						chwilowo_przechowujacy_dane.cena_biletu = lista_sortowana[parametr_petli_sortujacej2 + 1].cena_biletu;
						chwilowo_przechowujacy_dane.liczba_miejsc = lista_sortowana[parametr_petli_sortujacej2 + 1].liczba_miejsc;
						strcpy(chwilowo_przechowujacy_dane.miejsce_docelowe, lista_sortowana[parametr_petli_sortujacej2 + 1].miejsce_docelowe);
						strcpy(chwilowo_przechowujacy_dane.numer_autobusu, lista_sortowana[parametr_petli_sortujacej2 + 1].numer_autobusu);

						lista_sortowana[parametr_petli_sortujacej2 + 1].cena_biletu = lista_sortowana[parametr_petli_sortujacej2].cena_biletu;
						lista_sortowana[parametr_petli_sortujacej2 + 1].liczba_miejsc = lista_sortowana[parametr_petli_sortujacej2].liczba_miejsc;
						strcpy(lista_sortowana[parametr_petli_sortujacej2 + 1].miejsce_docelowe, lista_sortowana[parametr_petli_sortujacej2].miejsce_docelowe);
						strcpy(lista_sortowana[parametr_petli_sortujacej2 + 1].numer_autobusu, lista_sortowana[parametr_petli_sortujacej2].numer_autobusu);

						lista_sortowana[parametr_petli_sortujacej2].cena_biletu = chwilowo_przechowujacy_dane.cena_biletu;
						lista_sortowana[parametr_petli_sortujacej2].liczba_miejsc = chwilowo_przechowujacy_dane.liczba_miejsc;
						strcpy(lista_sortowana[parametr_petli_sortujacej2].miejsce_docelowe, chwilowo_przechowujacy_dane.miejsce_docelowe);
						strcpy(lista_sortowana[parametr_petli_sortujacej2].numer_autobusu, chwilowo_przechowujacy_dane.numer_autobusu);

					}
				}
			}

			parametr_poprawnosci_wyboru_metody_sortowania = 0;
		}

		else
			printf("Wpisano niepoprawna wartosc!\n");

	}

	printf("Posortowano liste.\n");

}

int main() {

	struct autobus* lista_autobusow;
	int parametr_menu = 250;
	int parametr_poprawnosci_wyboru_uzytkowanika = 1;
	int liczba_autobusow_w_liscie = 0;
	int maksymalna_liczba_autobusow_w_liscie = 1;
	int indeks_aktywnego_autobusu = 0; 
	int parametr_wpisywania_maksymalnej_liczby_autobusow = 1;
	int czy_pierwsze_uruchomienie = 1;
	int czy_ustalono_maksymalna_liczbe_autobusow = 0;
	int parametr_zmiany_aktywnego_autobusu = 1;
	int parametr_wyswietlania_listy_autobusow = 0;
	int parametr_usuwania_autobusow = 0;
	int parametr_sprawdzania_aktywnego_autobusu;
	char numer_aktywnego_autobusu_przed_sortowaniem[40];
	int liczba_miejsc_aktywnego_autobusu_przed_sortowaniem;
	int cena_biletu_w_aktywnym_autobusie_przed_sortowaniem;
	char miejsce_docelowe_aktywnego_autobusu_przed_sortowaniem[40];

	char opcja_0[50] = "WYJSCIE Z PROGRAMU";
	char opcja_1[50] = "WYSWIETLENIE LISTY AUTOBUSOW";
	char opcja_2[50] = "ZMIANA MAKSYMALNEJ LICZBY AUTOBUSOW - DOMYSLNE 1.";
	char opcja_3[50] = "DODANIE AUTOBUSU DO LISTY";
	char opcja_4[50] = "USUNIECIE AUTOBUSU Z LISTY";
	char opcja_5[50] = "WYSWIETLENIE AKTYWNEGO AUTOBUSU";
	char opcja_6[50] = "ZMIANA AKTYWNEGO AUTOBUSU";
	char opcja_7[50] = "USTALENIE CENY BILETU W AUTOBUSIE";
	char opcja_8[50] = "SORTOWANUE LISTY AUTOBUSOW";
	char opcja_9[50] = "ZAPISANIE LISTY AUTOBUSOW";


	lista_autobusow = malloc(sizeof(struct autobus));

	while (parametr_poprawnosci_wyboru_uzytkowanika != 0)
	{
		printf("\nWybierz funkcje z listy\nOperacje takie jak: losowanie ceny biletu i usuwanie autobusu odbywaja sie na autobusie aktywnym\n 0- %s\n 1- %s\n 2- %s\n 3- %s\n 4- %s\n 5- %s\n 6- %s\n 7- %s\n 8- %s\n 9- %s\n", opcja_0, opcja_1, opcja_2, opcja_3, opcja_4, opcja_5, opcja_6, opcja_7, opcja_8, opcja_9);
		scanf_s("%d", &parametr_menu);
		
		switch (parametr_menu)
		{

		case 0:

			system("cls");

			if (liczba_autobusow_w_liscie != 0)
			{
				free(lista_autobusow);

				return 0;
			}

			else
				return 0;

			break;

		case 1:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}

			for(parametr_wyswietlania_listy_autobusow = 0; parametr_wyswietlania_listy_autobusow < liczba_autobusow_w_liscie; parametr_wyswietlania_listy_autobusow++)
				printf("%d: %s %d %d %s\n", parametr_wyswietlania_listy_autobusow, lista_autobusow[parametr_wyswietlania_listy_autobusow].numer_autobusu, lista_autobusow[parametr_wyswietlania_listy_autobusow].cena_biletu, lista_autobusow[parametr_wyswietlania_listy_autobusow].liczba_miejsc, lista_autobusow[parametr_wyswietlania_listy_autobusow].miejsce_docelowe);
	
			break;

		case 2:

			system("cls");

			if (czy_ustalono_maksymalna_liczbe_autobusow == 1)
			{
				printf("Maksymalna liczba autobusow juz zostala ustalona\n");
				break;
			}

			while (parametr_wpisywania_maksymalnej_liczby_autobusow != 0)

			{

				printf("Jaka ma byc maksymalna liczba autobusow? UWAGA: PO WPISANIU, NIE MA MOZLIWOSCI ZMIANY TEGO PARAMETRU!\n");
				scanf_s("%d", &maksymalna_liczba_autobusow_w_liscie);

				if (maksymalna_liczba_autobusow_w_liscie <= 0)
					printf("Podano niepoprawna maksymalna liczbe autobusow!\n");

				else
					parametr_wpisywania_maksymalnej_liczby_autobusow = 0;

			}

			czy_ustalono_maksymalna_liczbe_autobusow = 1;

			break;

		case 3:

			system("cls");

			if (liczba_autobusow_w_liscie == 0 && czy_pierwsze_uruchomienie == 1)
			{
				printf("Wpisz dane pierwszego autobusu\n");
				wpisz_dane_do_autobusu(&lista_autobusow[0]);

				czy_pierwsze_uruchomienie = 0;
				liczba_autobusow_w_liscie++;

				break;
			}

			else if (liczba_autobusow_w_liscie == 0 && czy_pierwsze_uruchomienie != 1)
			{

				lista_autobusow = malloc(sizeof(struct autobus));

				printf("Wpisz dane pierwszego autobusu\n");
				wpisz_dane_do_autobusu(&lista_autobusow[0]);

				liczba_autobusow_w_liscie++;
				break;
			}

			if (liczba_autobusow_w_liscie == maksymalna_liczba_autobusow_w_liscie)
			{
				printf("Nie mozna dodac wiecej autobusow\n");
				break;
			}

			liczba_autobusow_w_liscie++;
			lista_autobusow = realloc(lista_autobusow, liczba_autobusow_w_liscie * sizeof(struct autobus));
			
			indeks_aktywnego_autobusu = liczba_autobusow_w_liscie - 1;

			wpisz_dane_do_autobusu(&lista_autobusow[indeks_aktywnego_autobusu]);

			break;

		case 4:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}


			if (liczba_autobusow_w_liscie == 1)
			{

				liczba_autobusow_w_liscie--;
				free(lista_autobusow);
				break;
			}


			for (parametr_usuwania_autobusow = indeks_aktywnego_autobusu; parametr_usuwania_autobusow < liczba_autobusow_w_liscie; parametr_usuwania_autobusow++)
			{
				lista_autobusow[parametr_usuwania_autobusow] = lista_autobusow[parametr_usuwania_autobusow + 1];
			}

			liczba_autobusow_w_liscie--;
			indeks_aktywnego_autobusu = liczba_autobusow_w_liscie - 1;
			lista_autobusow = realloc(lista_autobusow, liczba_autobusow_w_liscie * sizeof(struct autobus));
				

			break;

		case 5:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}

			printf("Aktywny autoobus:\n %s %d %d %s\n" ,lista_autobusow[indeks_aktywnego_autobusu].numer_autobusu, lista_autobusow[indeks_aktywnego_autobusu].cena_biletu, lista_autobusow[indeks_aktywnego_autobusu].liczba_miejsc, lista_autobusow[indeks_aktywnego_autobusu].miejsce_docelowe);
			break;

		case 6:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}

			while (parametr_zmiany_aktywnego_autobusu != 0)
			{
				printf("Wpisz indeks autobusu, ktory ma byc aktywny\n");
				scanf_s("%d", &indeks_aktywnego_autobusu);

				if (indeks_aktywnego_autobusu < 0 || indeks_aktywnego_autobusu > (liczba_autobusow_w_liscie - 1))
					printf("Brak autobusu o takim indeksie!\n");

				else
					parametr_zmiany_aktywnego_autobusu = 0;
			}

			parametr_zmiany_aktywnego_autobusu = 1;

			break;

		case 7:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}

			losuj_cene_biletu(&lista_autobusow[indeks_aktywnego_autobusu]);

			break;

		case 8:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}

			strcpy(numer_aktywnego_autobusu_przed_sortowaniem, lista_autobusow[indeks_aktywnego_autobusu].numer_autobusu);
			strcpy(miejsce_docelowe_aktywnego_autobusu_przed_sortowaniem, lista_autobusow[indeks_aktywnego_autobusu].miejsce_docelowe);
			liczba_miejsc_aktywnego_autobusu_przed_sortowaniem = lista_autobusow[indeks_aktywnego_autobusu].liczba_miejsc;
			cena_biletu_w_aktywnym_autobusie_przed_sortowaniem = lista_autobusow[indeks_aktywnego_autobusu].cena_biletu;


			sortuj_liste_autobusow(lista_autobusow, liczba_autobusow_w_liscie);

			for (parametr_sprawdzania_aktywnego_autobusu = 0; parametr_sprawdzania_aktywnego_autobusu < liczba_autobusow_w_liscie; parametr_sprawdzania_aktywnego_autobusu++)
			{
				if (strcoll(numer_aktywnego_autobusu_przed_sortowaniem, lista_autobusow[parametr_sprawdzania_aktywnego_autobusu].numer_autobusu) == 0 && strcoll(miejsce_docelowe_aktywnego_autobusu_przed_sortowaniem, lista_autobusow[parametr_sprawdzania_aktywnego_autobusu].miejsce_docelowe) == 0 && cena_biletu_w_aktywnym_autobusie_przed_sortowaniem == lista_autobusow[parametr_sprawdzania_aktywnego_autobusu].cena_biletu && liczba_miejsc_aktywnego_autobusu_przed_sortowaniem == lista_autobusow[parametr_sprawdzania_aktywnego_autobusu].liczba_miejsc)
				{
					indeks_aktywnego_autobusu = parametr_sprawdzania_aktywnego_autobusu;
					break;
				}

			}

			break;

		case 9:

			system("cls");

			if (liczba_autobusow_w_liscie == 0)
			{
				printf("Brak autobusow w liscie\n");
				break;
			}

			zapisz_autobusy_do_pliku(lista_autobusow, liczba_autobusow_w_liscie);

			break;

		default:
			
			system("cls");

			printf("Niepoprawny parametr! Wpisz ponownie");

			break;
		}
	}
}
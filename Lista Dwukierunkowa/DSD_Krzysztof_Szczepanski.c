#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<locale.h>
#include<string.h>
#include<ctype.h>



#pragma warning(disable : 4996)


#define SORTUJ_IMIONA 1
#define SORTUJ_NAZWISKA 2
#define SORTUJ_GRUPY 3

#define EXIT 0
#define DRUKUJ_LISTE 1
#define DODAJ_ELEMENT 2
#define WCZYTAJ_Z_PLIKU 3
#define USUN_ELEMENT 4
#define ZWOLNIJ_LISTE 5
#define SORTUJ_LISTE 6
#define DODAJ_KONTAKT 7
#define WYSZUKAJ_PO_IMIENIU_I_NAZWISKU 8
#define WYSZUKAJ_PO_GRUPIE 9

struct element* pierwszy;

struct element
{
    struct element* poprzedni;
    struct kontakt
    {
        char imie[40];
        char nazwisko[40];
        char numer_telefonu[40];
        char grupa[40];
    };
    struct element* kolejny;

};


struct element* utworz_nowy_element()
{
    struct element* nowy_element = (struct element*)malloc(sizeof(struct element));

    nowy_element->poprzedni = NULL;
    nowy_element->kolejny = NULL;

    return nowy_element;
}

void dodaj_nowy_element_na_koniec_listy()
{
    struct element* chwilowy = pierwszy;

    struct element* nowy_element = utworz_nowy_element();

    if (pierwszy == NULL)
    {
        pierwszy = nowy_element;
        return;
    }

    while (chwilowy->kolejny != NULL)
        chwilowy = chwilowy->kolejny;

    chwilowy->kolejny = nowy_element;
    nowy_element->poprzedni = chwilowy;

}

void drukuj_liste()
{
    struct element* chwilowy = pierwszy;

    while (chwilowy != 0)
    {
        printf("%s ", chwilowy->imie);
        printf("%s ", chwilowy->nazwisko);
        printf("%s ", chwilowy->numer_telefonu);
        printf("%s\n", chwilowy->grupa);

        chwilowy = chwilowy->kolejny;
    }

}

void zwolnij_liste()
{
    struct element* chwilowy = pierwszy;
    struct element* usuwany;

    do
    {
        usuwany = chwilowy;
        chwilowy = chwilowy->kolejny;
        free(usuwany);
    } while (chwilowy != 0);

}

void wczytaj_kontakty()
{
    char nazwa_pliku[256];
    struct element* chwilowy = pierwszy;
    char zastepcza_tablica[256];
    char chwilowe_imie[40];
    char chwilowe_nazwisko[40];
    char chwilowy_numer[40];
    char chwilowa_grupa[40];
    int i = 0;
    char j;


    printf("Podaj sciezke pliku z rozszerzeniem .csv.\n");
    scanf_s("%255s", nazwa_pliku, 256);

    FILE* plik;
    fopen_s(&plik, nazwa_pliku, "r");

    if (plik == NULL)
    {
        printf("Nie udalo sie wczytac pliku.\n");
        return;
    }

    do
    {
        fgets(zastepcza_tablica, 255, plik);
        sscanf(zastepcza_tablica, "%[^;]; %[^;]; %[^;]; %s", chwilowe_imie, chwilowe_nazwisko, chwilowy_numer, chwilowa_grupa);
        for (i = 0; i < 40; i++)
        {
            j = tolower(chwilowe_imie[i]);
            chwilowe_imie[i] = j;
        }
        for (i = 0; i < 40; i++)
        {
            j = tolower(chwilowe_nazwisko[i]);
            chwilowe_nazwisko[i] = j;
        }
        for (i = 0; i < 40; i++)
        {
            j = tolower(chwilowa_grupa[i]);
            chwilowa_grupa[i] = j;
        }
        strcpy(chwilowy->imie, chwilowe_imie);
        strcpy(chwilowy->nazwisko, chwilowe_nazwisko);
        strcpy(chwilowy->numer_telefonu, chwilowy_numer);
        strcpy(chwilowy->grupa, chwilowa_grupa);
        chwilowy = chwilowy->kolejny;
    } while (chwilowy != NULL);

    fclose(plik);

}

void sortuj_liste(int* ostatnio_uzyta_metoda_sortowania)
{
    int parametr_sortowania;
    int i = 1;
    struct element* zastepczy;
    struct element* chwilowy = pierwszy;
    struct element* chwilowy_2;

    zastepczy = (struct element*)malloc(sizeof(struct element));
    chwilowy_2 = (struct element*)malloc(sizeof(struct element));

    while (i != 0)
    {
        printf("Wedlug czaego chcesz sortowaæ liste? Wpisz: 1- Imienia 2- Nazwsika 3- Grupy\n");
        scanf_s("%d", &parametr_sortowania);

        if (parametr_sortowania == 1)
        {
            for (chwilowy = pierwszy; chwilowy != NULL; chwilowy = chwilowy->kolejny)
            {
                for (chwilowy_2 = chwilowy->kolejny; chwilowy_2 != NULL; chwilowy_2 = chwilowy_2->kolejny)
                {
                    if (strcoll(chwilowy->imie, chwilowy_2->imie) == 1)
                    {
                        strcpy(zastepczy->imie, chwilowy_2->imie);
                        strcpy(chwilowy_2->imie, chwilowy->imie);
                        strcpy(chwilowy->imie, zastepczy->imie);
                        strcpy(zastepczy->nazwisko, chwilowy->nazwisko);
                        strcpy(zastepczy->numer_telefonu, chwilowy->numer_telefonu);
                        strcpy(zastepczy->grupa, chwilowy->grupa);
                        strcpy(chwilowy->nazwisko, chwilowy_2->nazwisko);
                        strcpy(chwilowy->numer_telefonu, chwilowy_2->numer_telefonu);
                        strcpy(chwilowy->grupa, chwilowy_2->grupa);
                        strcpy(chwilowy_2->nazwisko, zastepczy->nazwisko);
                        strcpy(chwilowy_2->numer_telefonu, zastepczy->numer_telefonu);
                        strcpy(chwilowy_2->grupa, zastepczy->grupa);

                    }
                }
            }
            *ostatnio_uzyta_metoda_sortowania = 1;
            i = 0;
        }
        else if (parametr_sortowania == 2)
        {
            for (chwilowy = pierwszy; chwilowy != NULL; chwilowy = chwilowy->kolejny)
            {
                for (chwilowy_2 = chwilowy->kolejny; chwilowy_2 != NULL; chwilowy_2 = chwilowy_2->kolejny)
                {
                    if (strcoll(chwilowy->nazwisko, chwilowy_2->nazwisko) == 1)
                    {
                        strcpy(zastepczy->nazwisko, chwilowy->nazwisko);
                        strcpy(chwilowy->nazwisko, chwilowy_2->nazwisko);
                        strcpy(chwilowy_2->nazwisko, zastepczy->nazwisko);
                        strcpy(zastepczy->imie, chwilowy_2->imie);
                        strcpy(chwilowy_2->imie, chwilowy->imie);
                        strcpy(chwilowy->imie, zastepczy->imie);
                        strcpy(zastepczy->numer_telefonu, chwilowy->numer_telefonu);
                        strcpy(zastepczy->grupa, chwilowy->grupa);
                        strcpy(chwilowy->numer_telefonu, chwilowy_2->numer_telefonu);
                        strcpy(chwilowy->grupa, chwilowy_2->grupa);
                        strcpy(chwilowy_2->numer_telefonu, zastepczy->numer_telefonu);
                        strcpy(chwilowy_2->grupa, zastepczy->grupa);

                    }
                }
            }
            *ostatnio_uzyta_metoda_sortowania = 2;
            i = 0;
        }

        else if (parametr_sortowania == 3)
        {
            for (chwilowy = pierwszy; chwilowy != NULL; chwilowy = chwilowy->kolejny)
            {
                for (chwilowy_2 = chwilowy->kolejny; chwilowy_2 != NULL; chwilowy_2 = chwilowy_2->kolejny)
                {
                    if (strcoll(chwilowy->grupa, chwilowy_2->grupa) == 1)
                    {
                        strcpy(zastepczy->nazwisko, chwilowy->nazwisko);
                        strcpy(chwilowy->nazwisko, chwilowy_2->nazwisko);
                        strcpy(chwilowy_2->nazwisko, zastepczy->nazwisko);
                        strcpy(zastepczy->imie, chwilowy_2->imie);
                        strcpy(chwilowy_2->imie, chwilowy->imie);
                        strcpy(chwilowy->imie, zastepczy->imie);
                        strcpy(zastepczy->numer_telefonu, chwilowy->numer_telefonu);
                        strcpy(zastepczy->grupa, chwilowy->grupa);
                        strcpy(chwilowy->numer_telefonu, chwilowy_2->numer_telefonu);
                        strcpy(chwilowy->grupa, chwilowy_2->grupa);
                        strcpy(chwilowy_2->numer_telefonu, zastepczy->numer_telefonu);
                        strcpy(chwilowy_2->grupa, zastepczy->grupa);

                    }
                }
            }
            *ostatnio_uzyta_metoda_sortowania = 3;
            i = 0;
        }

        else
            printf("Bledny parametr sortowania! Wpisz ponownie.");
    }

    free(zastepczy);
}

void usun_element(int liczba_elementow_w_liscie)
{
    struct element* chwilowy = pierwszy;
    struct element* chwilowy2 = NULL;
    int j, i;
    int k = 1;
    while (k != 0)
    {
        printf("Ktory kontakt chcesz usunac?\n");
        scanf_s("%d", &i);

        if (i < 0 || i > liczba_elementow_w_liscie)
            printf("Nie ma kontaktu o takim numerze. Wpisz ponownie\n");
        else
            k = 0;
    }

    if (i == 1)
    {
        pierwszy = chwilowy->kolejny;
        free(chwilowy);
        return;
    }

    else if (i == liczba_elementow_w_liscie)
    {
        while (chwilowy->kolejny != NULL)
            chwilowy = chwilowy->kolejny;
        chwilowy2 = chwilowy->poprzedni;
        chwilowy2->kolejny = NULL;
        free(chwilowy);
    }
    else

    {
        for (j = 0; j < i - 2; j++)
            chwilowy = chwilowy->kolejny;

        chwilowy2 = chwilowy->kolejny;
        chwilowy->kolejny = chwilowy2->kolejny;
        free(chwilowy2);
    }
}

int zwroc_pozycje_nowego_kontaku(struct element* wczytywany, int ostatnio_uzyta_metoda_sortowania)
{
    struct element* chwilowy = pierwszy;
    int pozycja_nowego_elementu = 1;

    do
    {
        if (ostatnio_uzyta_metoda_sortowania == SORTUJ_IMIONA)
        {
            if (strcoll(wczytywany->imie, chwilowy->imie) != 1)
            {
                return pozycja_nowego_elementu;
            }
        }

        else if (ostatnio_uzyta_metoda_sortowania == SORTUJ_NAZWISKA)
        {
            if (strcoll(wczytywany->nazwisko, chwilowy->nazwisko) != 1)
            {
                return pozycja_nowego_elementu;
            }
        }

        else if (ostatnio_uzyta_metoda_sortowania == SORTUJ_GRUPY)
        {
            if (strcoll(wczytywany->grupa, chwilowy->grupa) != 1)
            {
                return pozycja_nowego_elementu;
            }
        }

        chwilowy = chwilowy->kolejny;
        pozycja_nowego_elementu++;
    } while (chwilowy != NULL);
    return pozycja_nowego_elementu;
}

void dodaj_kontakt_miedzy_inne(int ostatnio_uzyta_metoda_sortowania, int liczba_elementow_w_liscie)
{
    struct element* chwilowy = pierwszy;
    struct element* chwilowy2 = NULL;
    struct element* nowy = utworz_nowy_element();
    int i;
    char j;
    int pozycja_kontaktu;
    int pozycja_poprzedniego_kontaktu;

    char chwilowe_imie[40];
    char chwilowe_nazwisko[40];
    char chwilowy_numer_telefonu[40];
    char chwilowa_grupa[40];

    printf("Podaj imie nowego kontaktu\n");
    scanf_s("%39s", &chwilowe_imie, 40);
    printf("Podaj nazwisko nowego kontaktu\n");
    scanf_s("%39s", &chwilowe_nazwisko, 40);
    printf("Podaj numer nowego kontaktu\n");
    scanf_s("%39s", &chwilowy_numer_telefonu, 40);
    printf("Podaj grupe nowego kontaktu\n");
    scanf_s("%39s", &chwilowa_grupa, 40);

    for (i = 0; i < 40; i++)
    {
        j = tolower(chwilowe_imie[i]);
        chwilowe_imie[i] = j;
    }
    for (i = 0; i < 40; i++)
    {
        j = tolower(chwilowe_nazwisko[i]);
        chwilowe_nazwisko[i] = j;
    }
    for (i = 0; i < 40; i++)
    {
        j = tolower(chwilowa_grupa[i]);
        chwilowa_grupa[i] = j;
    }
    strcpy(nowy->imie, chwilowe_imie);
    strcpy(nowy->nazwisko, chwilowe_nazwisko);
    strcpy(nowy->numer_telefonu, chwilowy_numer_telefonu);
    strcpy(nowy->grupa, chwilowa_grupa);

    pozycja_kontaktu = zwroc_pozycje_nowego_kontaku(nowy, ostatnio_uzyta_metoda_sortowania);
    pozycja_poprzedniego_kontaktu = pozycja_kontaktu - 1;


    if (pozycja_kontaktu == liczba_elementow_w_liscie)
    {
        while (chwilowy->kolejny != 0)
            chwilowy = chwilowy->kolejny;
        chwilowy->kolejny = nowy;
        nowy->poprzedni = chwilowy;

    }

    else if (pozycja_kontaktu == 1)
    {
        pierwszy->poprzedni = nowy;
        nowy->kolejny = pierwszy;
        pierwszy = nowy;
    }

    else
    {
        while (pozycja_poprzedniego_kontaktu != 1)
        {
            chwilowy = chwilowy->kolejny;
            pozycja_poprzedniego_kontaktu--;
        }

        chwilowy2 = chwilowy->kolejny;
        chwilowy->kolejny = nowy;
        chwilowy2->poprzedni = nowy;
        nowy->kolejny = chwilowy2;
        nowy->poprzedni = chwilowy;
    }
}

void wyszukaj_kontakt_po_imieniu_i_naziwsku()
{
    char wyszukiwany_ciag[40];
    struct element* chwilowy = pierwszy;
    int i;
    char j;
    int liczba_wyszukanych_kontaktow = 0;

    printf("Wpisz ciag, w ktorym chcesz wyszukac kontakty\n");
    scanf_s("%39s", &wyszukiwany_ciag, 40);

    for (i = 0; i < 40; i++)
    {
        j = tolower(wyszukiwany_ciag[i]);
        wyszukiwany_ciag[i] = j;
    }

    do
    {
        if (strstr(chwilowy->imie, wyszukiwany_ciag) != NULL)
        {
            printf("%s %s %s %s \n", chwilowy->imie, chwilowy->nazwisko, chwilowy->numer_telefonu, chwilowy->grupa);
            liczba_wyszukanych_kontaktow++;
        }

        else if (strstr(chwilowy->nazwisko, wyszukiwany_ciag) != NULL)
        {
            printf("%s %s %s %s \n", chwilowy->imie, chwilowy->nazwisko, chwilowy->numer_telefonu, chwilowy->grupa);
            liczba_wyszukanych_kontaktow++;
        }


        chwilowy = chwilowy->kolejny;
    } while (chwilowy != NULL);

    printf("Wyszukoano %d kontaktow\n", liczba_wyszukanych_kontaktow);
}

void wyszukaj_kontakt_po_grupie()
{
    char wyszukiwany_ciag[40];
    struct element* chwilowy = pierwszy;
    int i;
    char j;
    int liczba_wyszukanych_kontaktow = 0;

    printf("Wpisz ciag, ktorym chcesz wyszukac kontakty");
    scanf_s("%39s", &wyszukiwany_ciag, 40);

    for (i = 0; i < 40; i++)
    {
        j = tolower(wyszukiwany_ciag[i]);
        wyszukiwany_ciag[i] = j;
    }

    do
    {
        if (strstr(chwilowy->grupa, wyszukiwany_ciag) != NULL)
        {
            printf("%s %s %s %s \n", chwilowy->imie, chwilowy->nazwisko, chwilowy->numer_telefonu, chwilowy->grupa);
            liczba_wyszukanych_kontaktow++;
        }

        chwilowy = chwilowy->kolejny;
    } while (chwilowy != NULL);

    printf("Wyszukano %d kontaktow\n", liczba_wyszukanych_kontaktow);
}

int main()
{

    setlocale(LC_CTYPE, "Polish");
    int* ostatnio_uzyta_metoda_sortowania = malloc(sizeof(int));
    int liczba_elementow_w_liscie = 0;
    int czy_sortowano = 0;
    int czy_dodano_dane = 0;
    int parametr_menu = 25;
    int parametr_chwilowy = 1;
    int parametr_chilowy_2 = 25;
    int parametr_chwilowy_3 = 25;

    while (parametr_menu != 0)
    {
        parametr_chwilowy_3 = 25;

        if (liczba_elementow_w_liscie == 0)
        {
            czy_dodano_dane = 0;
            czy_sortowano = 0;
        }

        printf("Wybierz opcje z menu:\n 0- Wyjdz z programu\n 1-Pokaz liste\n 2-Dodaj elementy na koniec listy\n 3-Wczytaj kontakty z pliku\n 4-Usun konakt i element z listy\n 5-Wyczysc cala liste\n 6-Sortuj liste\n 7-Dodaj kontakt do posortowanej listy\n 8-Wyszukaj kontakty po imieniu i nazwisku\n 9-Wyszukaj kontakty po grupie\n");
        scanf_s("%d", &parametr_menu);
        switch (parametr_menu)
        {

        case EXIT:

            system("cls");

            if(liczba_elementow_w_liscie != 0)
                zwolnij_liste();

            return 0;

        case DRUKUJ_LISTE:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            drukuj_liste();

            break;

        case DODAJ_ELEMENT:

            system("cls");

            while (parametr_chwilowy_3 != 0)
            {
                printf("Ile miejsc na kontakt chcesz dodac?\n");
                scanf_s("%d", &parametr_chilowy_2);

                if (parametr_chilowy_2 < 0)
                    printf("Wprowadzono niepoprawny parametr! Wpisz ponownie\n");

                else
                {
                    for (parametr_chwilowy = 0; parametr_chwilowy < parametr_chilowy_2; parametr_chwilowy++)
                    {
                        dodaj_nowy_element_na_koniec_listy();
                        liczba_elementow_w_liscie++;;
                        parametr_chwilowy_3 = 0;
                    }
                }
            }

            break;

        case WCZYTAJ_Z_PLIKU:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            wczytaj_kontakty();

            czy_dodano_dane = 1;

            break;

        case USUN_ELEMENT:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            usun_element(liczba_elementow_w_liscie);
            liczba_elementow_w_liscie--;

            break;

        case ZWOLNIJ_LISTE:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            zwolnij_liste();
            liczba_elementow_w_liscie = 0;

            break;

        case SORTUJ_LISTE:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            sortuj_liste(ostatnio_uzyta_metoda_sortowania);

            czy_sortowano = 1;

            break;

        case DODAJ_KONTAKT:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            if (czy_sortowano == 0)
            {
                printf("Nie mozna dodac kontaktu. Lista nie jest posortowana! Posortuj liste.\n");
                break;
            }

            dodaj_kontakt_miedzy_inne(*ostatnio_uzyta_metoda_sortowania, liczba_elementow_w_liscie);
            liczba_elementow_w_liscie++;

            break;

        case WYSZUKAJ_PO_IMIENIU_I_NAZWISKU:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            wyszukaj_kontakt_po_imieniu_i_naziwsku();

            break;

        case WYSZUKAJ_PO_GRUPIE:

            system("cls");

            if (liczba_elementow_w_liscie == 0)
            {
                printf("Brak elementow w liscie!\n");
                break;
            }

            if (czy_dodano_dane == 0)
            {
                printf("Dodano elementy, ale nie przypisano do nich kontaktow. Wczytaj kontakty!\n");
                break;
            }

            wyszukaj_kontakt_po_grupie();

            break;

        default:
            printf("Podano bledny parametr! Wpisz ponownie.\n");
            break;
        }
    }

    return;
}
// conways_game_of_life_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "windows.h"
#include <time.h>
#include <cstdlib>

using namespace std;

/* DEKLARACJA STA�YCH WYMIAR�W PLANSZY */
const int y = 30; //30 fajnie 
const int x = 80; //80 fajnie

struct cellStructure //pojedyncza kom�rka
{
	bool isAlive; //czy kom�rka jest �ywa w tej generacji
	int neighbours; //liczba �ywych s�siad�w kom�rki
};

void cellsSetDead(cellStructure cell[y][x]); //TWORZENIE MARTWEJ PLANSZY (SZABLONU)

 /* DEKLARACJA STA�YCH, STANOWI�CYCH INDEKSY WIERZCHO�K�W CZʌCI PLANSZY NA KT�REJ B�DZIE TOCZY�O SI� �YCIE (WSZYSTKIE KOM�RKI POZA KOM�RKAMI NA KRAW�DZIACH PLANSZY) */
const int first_y = 1;
const int last_y = y - 2;
const int first_x = 1;
const int last_x = x - 2;

int main()
{
	srand(time(NULL));
	COORD cursorReset;
	cursorReset.X = 0;
	cursorReset.Y = 0;
	cellStructure cell[y][x];
	cellsSetDead(cell); //TWORZENIE MARTWEJ PLANSZY (SZABLONU)
	/* O�YWIANIE PLANSZY */
	char startMap;
	cout << "wci�nij s jesli chcesz gotowa mapke, lub dowolny inny przycisk aby plansza byla zapelniana losowo: ";
	cin >> startMap;
	system("cls");
	if (startMap == 's') {} //wklei� funkcje losuj�c� map�
	 //LOSOWANKO
		 for (int iy = first_y; iy <= last_y; ++iy) {
			 for (int jx = first_x; jx <= last_x; ++jx) {
				 if (rand() % 10 > 6)
					 cell[iy][jx].isAlive = true;
			 }
		 }
	
	/* �YCIE!!! */
	char ch = 'a';
	//while (ch != 'e'){ //przej�cie do nast�pnej generacji lub zamkniecie programu klikaj�c 'e'
	while (ch == 'a') {
		//		przesuwanie si� po �ywej planszy aby wy�wietli� obecn� generacj�
		for (int iy = first_y; iy <= last_y; ++iy) {
			for (int jx = first_x; jx <= last_x; ++jx) {
				if (cell[iy][jx].isAlive == false)
					cout << char(' '); //0xB0
				else
					cout << char(0xB2);
			}
			cout << endl;
		}
		//		ponowne przesuwanie si� po �ywej planszy
		for (int iy = first_y; iy <= last_y; ++iy) {
			for (int jx = first_x; jx <= last_x; ++jx) {
				if (cell[iy][jx].isAlive == true) { // dla znalezionej �ywej kom�rki inkrementowanie warto�ci neigbours jej s�siad�w o 1
					cell[iy + 1][jx - 1].neighbours++;
					cell[iy + 1][jx].neighbours++;
					cell[iy + 1][jx + 1].neighbours++;
					cell[iy][jx - 1].neighbours++;
					cell[iy][jx + 1].neighbours++;
					cell[iy - 1][jx - 1].neighbours++;
					cell[iy - 1][jx].neighbours++;
					cell[iy - 1][jx + 1].neighbours++;
				}
			}
		}
		/*
		//		wy�wietlanie tablicy s�siedztw
		for (int iy = first_y; iy <= last_y; ++iy) {
		for (int jx = first_x; jx <= last_x; ++jx) {
		cout << cell[iy][jx].neighbours;
		}
		cout << endl;
		}
		*/
		//		kolejne	przesuwanie si� po �ywej planszy
		for (int iy = first_y; iy <= last_y; ++iy) {
			for (int jx = first_x; jx <= last_x; ++jx) {
				if (cell[iy][jx].isAlive == false) { // dla martwej kom�rki sprawdzam czy ma dokladnie 3 sasiadow (wtedy komorka ozywa czyli zmienia sie jej stan) 
					if (cell[iy][jx].neighbours == 3)
						cell[iy][jx].isAlive = true;
				}
				else { // dla �ywych kom�rek maj�cych 2 lub 3 s�siad�w stan sie nie zmienia (stateChange wci�� ma warto�� false), przy innej liczbie s�siad�w kom�rka umiera (stateChange = true)
					if (cell[iy][jx].neighbours != 2 && cell[iy][jx].neighbours != 3)
						cell[iy][jx].isAlive = false;
				}
				cell[iy][jx].neighbours = 0; //zmiana warto�ci neigbours na pocz�tkowe ju� sprawdzonych kom�rek, �eby przygotowa� je do kolejnej generacji
			}
		}

		Sleep(15);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorReset); //ustawianie kursora na pocz�tek tablicy, aby j� nadpisa�
																				//cin >> ch;
	}
	return 0;
}

void cellsSetDead(cellStructure cell[y][x]) { //TWORZENIE MARTWEJ PLANSZY (SZABLONU)
	for (int iy = 0; iy < y; iy++) {
		for (int jx = 0; jx < x; jx++) {
			cell[iy][jx].isAlive = false;
			cell[iy][jx].neighbours = 0;
		}
	}
};
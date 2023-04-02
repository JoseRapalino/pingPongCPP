#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

using std::endl; using std::cout; using std::cin;

const int ejeX = 90, ejeY = 25;

const int upIzq = 119, downIzq = 115, upDer = 72, downDer = 80;

int direRandom = 0;

int winsIzq = 0, winsDer = 0;

struct Paletas{

	int largo, cont, paddingX, paddingY;
	char paletaCaracter = '#';
	
	int auxPosIzqY;
	int auxContIzq;

	int auxPosDerY;
	int auxContDer;

	int cambioPos(int tecla, int up, int dowm) {
		
		if (tecla == up) {
			
			if (paddingY < 0) { 
				paddingY = 1; 
			}
			else {
				paddingY--;
			}

			return paddingY;
		}
		
		if (tecla == dowm) {
			if (paddingY > 20) { 
				paddingY = 20; 
			}
			else {
				paddingY++;
			}

			return paddingY;
		}
		return paddingY;	
	}
};

struct Pelota {

	int posX = 25;
	int posY = 10;
	char caracter = 'o';
	int direccionX = -1;
	int direccionY = 1;


};

void printPaletas( Paletas& paletaIzq, Paletas& paletaDer,int tecla);
void pelotaMov(Pelota& pelota, Paletas& paletaIzq, Paletas& paletaDer);
void gotoxy(int x, int y);


int main() {

	Paletas paletaIzq;	
	paletaIzq.largo = ejeY / 3;
	paletaIzq.cont = paletaIzq.largo;
	paletaIzq.paddingX = (paletaIzq.largo / 3) + 2;
	paletaIzq.paddingY = paletaIzq.largo;
		
	Paletas paletaDer;	
	paletaDer.largo = ejeY / 3;
	paletaDer.cont = paletaDer.largo;
	paletaDer.paddingX = (paletaDer.largo / 3) + 83;
	paletaDer.paddingY = paletaDer.largo;

	Pelota pelota;
	
	bool pass = true;

	int tecla = 0;

	int newPosIzqY, newPosDerY;

	for (int i = 0; i < ejeX; i++) {
		gotoxy(i, 0); cout << "_";
		gotoxy(i, 29); cout << "_";
	}
	
	gotoxy(90, 5); cout << "by Jose Rapalino";

	printPaletas(paletaIzq, paletaDer, tecla);

	while (pass) {
		
	gotoxy(90, 10); cout << "**** PUNTOS DE LA PARTIDA ****";
	gotoxy(90, 15); cout << "DERECHO: "; gotoxy(100, 15); cout<<winsDer;
	gotoxy(90, 20); cout << "IZQUIERDO: "; gotoxy(100, 20); cout<<winsIzq;

			printPaletas(paletaIzq, paletaDer, tecla);

			pelotaMov(pelota, paletaIzq, paletaDer);

			if (_kbhit()) {

				tecla = _getch();
				(tecla == upIzq || tecla == downIzq) ? newPosIzqY = paletaIzq.cambioPos(tecla,upIzq,downIzq) : newPosDerY = paletaDer.cambioPos(tecla,upDer,downDer);
				printPaletas(paletaIzq, paletaDer, tecla);
				tecla = 0;
			}
		}

	return 0;
}

void printPaletas( Paletas& paletaIzq, Paletas& paletaDer, int tecla) {


	int auxPosIzqY = paletaIzq.paddingY;
	int auxContIzq = paletaIzq.cont;

	int auxPosDerY = paletaDer.paddingY;
	int auxContDer = paletaDer.cont;

	if (paletaIzq.paddingY > 0 && paletaIzq.paddingY < 20)  {

		for (int i = 0; i < paletaIzq.largo; i++) {

			if (paletaIzq.cont != 0) {

				paletaIzq.cont--;
				paletaIzq.paddingY++;
				gotoxy(paletaIzq.paddingX, paletaIzq.paddingY); cout << paletaIzq.paletaCaracter;

			}

		}

		if (tecla == downIzq) { gotoxy(paletaIzq.paddingX, auxPosIzqY); cout << " "; }

		if (tecla == upIzq) { gotoxy(paletaIzq.paddingX, auxPosIzqY + 9); cout << " "; }
		
}


	if (paletaDer.paddingY > 0 && paletaDer.paddingY < 20){
		

		for (int i = 0; i < paletaDer.largo; i++) {

			if (paletaDer.cont != 0) {


				paletaDer.cont--;
				paletaDer.paddingY++;
				gotoxy(paletaDer.paddingX, paletaDer.paddingY); cout << paletaDer.paletaCaracter;

			}

		}

		if (tecla == downDer) { gotoxy(paletaDer.paddingX, auxPosDerY); cout << " "; }

		if (tecla == upDer) { gotoxy(paletaDer.paddingX, auxPosDerY + 9); cout << " "; }
	}

	paletaIzq.paddingY = auxPosIzqY;
	paletaIzq.cont = auxContIzq;

	paletaDer.paddingY = auxPosDerY;
	paletaDer.cont = auxContDer;


}


void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}


void pelotaMov(Pelota& pelota, Paletas& paletaIzq, Paletas& paletaDer) {

	int auxPosX = pelota.posX;
	int auxPosY = pelota.posY;
	
	Sleep(20);

		if (pelota.posX > 0 && pelota.posX < ejeX-4) {
			
		if(paletaIzq.paddingX+1 == pelota.posX &&  pelota.posY > paletaIzq.paddingY && pelota.posY < paletaIzq.paddingY+9){
				pelota.direccionX = 1;
		}
		
		if(paletaDer.paddingX-1 == pelota.posX &&  pelota.posY > paletaDer.paddingY && pelota.posY < paletaDer.paddingY+9){
				pelota.direccionX = -1;
		}
	
			if (pelota.posY == 2) {
				pelota.direccionY = 1;
			}
			else if (pelota.posY == 27) {
				pelota.direccionY = -1;
			}
		}
		else{			
				if(pelota.posX < 1){
					winsDer++;
				}
				if(pelota.posX > 80){
					winsIzq++;
				}
				
				direRandom++;
				
				if(direRandom % 2 == 0){
					pelota.direccionX = -1;
				}else{
					pelota.direccionX = 1;
				}
				
				gotoxy(auxPosX, auxPosY); cout << " ";
				Sleep(50);
				
				pelota.posX = ejeX/2;
				pelota.posY = ejeY/3;
				auxPosX = pelota.posX;
				auxPosY = pelota.posY;
		}
		
			pelota.posX += pelota.direccionX;
			pelota.posY += pelota.direccionY;
			gotoxy(pelota.posX, pelota.posY); cout << pelota.caracter;
			gotoxy(auxPosX, auxPosY); cout << " ";

}



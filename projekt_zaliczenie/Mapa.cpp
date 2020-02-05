#include "Mapa.h"
#include <iostream>
#include <random>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

using namespace std;

Pole TablicaLosowychPol[4]{ {"Pola",1,1,"img/grass.png",0}, {"Gory",1,0,"img/mountain.png",1}, {"Woda",0,0,"img/water.png",2}, {"Pustynia",1,1,"img/sand.png",3} };


int Mapa::losowa(int max, int min) {
	random_device dev;
	mt19937 rng(dev());
	uniform_int_distribution<int> range(min, max);
	return range(rng);
}

Mapa::Mapa(int dlugosc, int szerokosc) {

	Mapa::dlugosc = dlugosc;
	Mapa::szerokosc = szerokosc;

	rozdzielZiarno(ziarno, ziarnoTab);
	WypelnTab(mapaPol);
}


void Mapa::WypelnTab(vector<vector<Pole>>& mapaPol)
{
	LoadFont();
	for (int i = 0; i < dlugosc; i++)
	{	
		vector<Pole> tmp;
		for (int j = 0; j < szerokosc; j++)
		{
			Pole poleTmp = TablicaLosowychPol[0];
			if (i == 0 || j == 0 || i == (dlugosc-1) || j == (szerokosc - 1))
			{
				poleTmp = TablicaLosowychPol[1];
			}
			else
			{
				poleTmp = TablicaLosowychPol[0];
			}
			poleTmp.position[0][0] = i * 30;
			poleTmp.position[0][1] = j * 30;
			poleTmp.position[1][0] = i * 30+30;
			poleTmp.position[1][1] = j * 30+30;
			poleTmp.sprite.setPosition(i * 30-2, j * 30-2);
			
			
			tmp.push_back(poleTmp);
		}
		mapaPol.push_back(tmp);
	}

	losujGory();
	losujPlacki(ziarnoTab[2] * 5, losowa(3), 3);
	losujPlacki(ziarnoTab[2] * 3, losowa(3), 2);
	losujRzeki();
	WypelnText();
}
void Mapa::WypelnText() {
	for (int i = 0; i < mapaPol.size(); i++)
	{
		for (int j = 0; j < mapaPol[i].size(); j++)
		{

			mapaPol[i][j].budowaT.setFillColor(sf::Color::Black);
			mapaPol[i][j].budowaT.setPosition(940, 120);
			mapaPol[i][j].budowaT.setFont(font);
			mapaPol[i][j].budowaT.setCharacterSize(24);

			mapaPol[i][j].przejscieT.setFillColor(sf::Color::Black);
			mapaPol[i][j].przejscieT.setPosition(940, 80);
			mapaPol[i][j].przejscieT.setFont(font);
			mapaPol[i][j].przejscieT.setCharacterSize(24);

			mapaPol[i][j].nazwaT.setFillColor(sf::Color::Black);
			mapaPol[i][j].nazwaT.setPosition(1020, 40);
			mapaPol[i][j].nazwaT.setFont(font);
			mapaPol[i][j].nazwaT.setCharacterSize(40);

			mapaPol[i][j].nazwaT.setString(mapaPol[i][j].nazwa);
			if (mapaPol[i][j].budowa)
			{
				mapaPol[i][j].budowaT.setString("Mozna Budowac");
			}
			else
			{
				mapaPol[i][j].budowaT.setString("Nie Mozna Budowac");
			}
			if (mapaPol[i][j].przejscie)
			{
				mapaPol[i][j].przejscieT.setString("Mozna Przechodzic");
			}
			else
			{
				mapaPol[i][j].przejscieT.setString("Nie Mozna Przechodzic");
			}
		}
	}
	
}


void Mapa::WypiszTab(vector<vector<Pole>>& mapaPol, RenderWindow& window)
{
	for (int i = 0; i < mapaPol.size(); i++)
	{
		for (int j = 0; j < mapaPol[i].size(); j++)
		{
			
			window.draw(mapaPol[i][j].sprite);
		}
	}
	StatystykiGen();
	window.draw(spriteStat);
}

void Mapa::StatystykiGen() {
	textureStat.loadFromFile("img/tloStat.png");
	spriteStat.setTexture(textureStat);
	spriteStat.setScale(1.5, 1);
	spriteStat.setPosition(920, 20);
}


void Mapa::rozdzielZiarno(int ziarno, unsigned short(&ziarnoTab)[7]) {
	ziarnoTab[0] = ziarno / 10000 % 10;
	ziarnoTab[1] = ziarno / 1000 % 10;
	ziarnoTab[2] = ziarno / 100 % 10;
	ziarnoTab[3] = ziarno / 10 % 10;
	ziarnoTab[4] = ziarno % 10;
	ziarnoTab[5] = ziarnoTab[1] + ziarnoTab[2];
	ziarnoTab[6] = ziarnoTab[3] + ziarnoTab[4];
}

void Mapa::losujGory() {
	unsigned short liczbaGor = ziarnoTab[3];
	unsigned short liczbaPasm = ziarnoTab[0];

	
	
	for (int i = 0; i < liczbaPasm; i++)
	{
		int positionX = losowa(dlugosc - 2);
		int positionY = losowa(szerokosc - 2);

		for (int j = 0; j < liczbaGor; j++)
		{
			int kierunek = losowa(4);
			while (losowanieSprawdzanieKierunku(positionX, positionY, kierunek))
			{
				kierunek = losowa(4);
			}

			postawPole(mapaPol, positionX, positionY, 1);

		}
	}

	
}
void Mapa::losujRzeki() {
	int dlugoscRzek = ziarnoTab[6]*2;
	int iloscRzek = ziarnoTab[4];
	

	for (int i = 0; i < iloscRzek; i++)
	{
		int positionX = losowa(dlugosc - 2);
		int positionY = losowa(szerokosc - 2);
		for (int j = 0; j < dlugoscRzek; j++)
		{
			int OldPositionX = positionX;
			int OldPositionY = positionY;
			int kierunek = losowa(4);
			while (losowanieSprawdzanieKierunku(positionX, positionY, kierunek) && rzekaSprawdzanie(positionX, positionY))
			{
				positionX = OldPositionX;
				positionY = OldPositionY;
				kierunek = losowa(4);
			}

			postawPole(mapaPol, positionX, positionY, 2);

		}
	}
}
bool Mapa::rzekaSprawdzanie(int positionX, int positionY)
{
	bool doRet = 1;
	int liczbaPolaczen = 0;
	if (mapaPol[(int)positionX+1][(int)positionY+1].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[(int)positionX + 1][positionY].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[(int)positionX + 1][(int)positionY-1].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[positionX][(int)positionY + 1].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[positionX ][(int)positionY - 1].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[(int)positionX - 1][(int)positionY - 1].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[(int)positionX - 1][(int)positionY + 1].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (mapaPol[(int)positionX - 1][positionY].typ == 2)
	{
		liczbaPolaczen++;
	}
	if (liczbaPolaczen>1)
	{
		doRet = 0;
	}
	return doRet;
}

void Mapa::losujPlacki(int wielkosc, int ilosc, int typ)
{
	int positionX = losowa(dlugosc - 2);
	int positionY = losowa(szerokosc - 2);
	for (int i = 0; i < ilosc; i++)
	{
		for (int j = 0; j < wielkosc; j++)
		{
			int kierunek = losowa(4);
			while (losowanieSprawdzanieKierunku(positionX,positionY,kierunek))
			{
				kierunek = losowa(4);
			}
			postawPole(mapaPol, positionX, positionY, typ);
		}
	}
}


void Mapa::postawPole(vector<vector<Pole>>& mapaPol, int X, int Y, int typPola)
{
	Pole poleTmp = TablicaLosowychPol[typPola];
	poleTmp.position[0][0] = X * 30;
	poleTmp.position[0][1] = Y * 30;
	poleTmp.position[1][0] = X * 30+30;
	poleTmp.position[1][1] = Y * 30+30;
	poleTmp.sprite.setPosition(X * 30 - 2, Y * 30 - 2);
	mapaPol[X][Y] = poleTmp;

}

bool Mapa::losowanieSprawdzanieKierunku(int& positionX, int& positionY, int kierunek)
{
	/*
	kierunek 1 -lewo
	kierunek 2 -gora
	kierunek 3 -prawo
	kierunek 4 -dol
	*/
	bool doRet = 1;



		if (kierunek == 1 && positionX != 1)
		{
			positionX--;
			doRet = 1;
		}

		if (kierunek == 2 && positionY != 1)
		{
			positionY--;
			doRet = 1;
		}
		if (kierunek == 3 && positionX != (szerokosc - 2))
		{
			positionX++;
			doRet = 1;
		}
		if (kierunek == 4 && positionY != (dlugosc - 2))
		{
			positionY++;
			doRet = 1;
		}
		else
			doRet = 0;

		if (mapaPol[positionX][positionY].typ != 0)
		{
			doRet = 0;
		}

	return doRet;
}

void Mapa::EventListener(RenderWindow& window, Event& event, int(&TabPomPola)[2])
{
	float mouseX = Mouse::getPosition(window).x;
	float mouseY = Mouse::getPosition(window).y;

	switch (event.type)
	{

		break;
	case Event::MouseMoved:
		if (Statystyki(mouseX, mouseY))
		{
			int X = mouseX / 30;
			int Y = mouseY / 30;
			if (X > 0 && Y > 0 && X < (dlugosc - 1) && Y < (szerokosc - 1))
			{
				TabPomPola[0] = X;
				TabPomPola[1] = Y;
			}
		}
		break;

	default:
		break;
	}
}
bool Mapa::Statystyki(float& mouseX, float& mouseY) {
	if (mouseX < 900 && mouseX > 0 && mouseX < 900 && mouseX > 0)
	{
		return true;
	}
	return false;
}

bool Mapa::WcisnietyPrzycisk(RenderWindow& window, float& mouseX, float& mouseY)
{

	if (mouseX < 900 && mouseX > 0 && mouseX < 900 && mouseX > 0)
	{
		return true;
	}
	return false;
}

void Mapa::LoadFont()
{
	font.loadFromFile("fonts/Roboto-Black.ttf");
}

Mapa::~Mapa() {

}
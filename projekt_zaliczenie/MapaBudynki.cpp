#include "MapaBudynki.h"
#include "Budynek.h"
#include "Ludz.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

Budynek BudynkiTab[4]{ {"Pusto",0,0,"", 0}, {"Dom",10,4,"img/dom.png", 1},{"Fabryka", 20, 6, "img/fabryka.png", 2},{"Droga", 0, 1, "img/droga.png", 3} };
vector<vector<Pole>> MapaPol;
MapaBudynki::MapaBudynki(int dlugosc, int szerokosc, vector<vector<Pole>>& mapaPol)
{
	this->dlugosc = dlugosc;
	this->szerokosc = szerokosc;
	MapaPol = mapaPol;
	WypelnTab();
}
void MapaBudynki::WypelnTab() {
	LoadFont();
	for (int i = 0; i < dlugosc; i++)
	{
		vector<Budynek> tmp;
		for (int j = 0; j < szerokosc; j++)
		{
			Budynek budynekTmp = BudynkiTab[0];
			budynekTmp = BudynkiTab[0];
			budynekTmp.position[0][0] = i * 30;
			budynekTmp.position[0][1] = j * 30;
			budynekTmp.position[1][0] = i * 30 + 30;
			budynekTmp.position[1][1] = j * 30 + 30;
			budynekTmp.sprite.setPosition(i * 30 - 2, j * 30 - 2);
			tmp.push_back(budynekTmp);
		}
		mapaBud.push_back(tmp);
	}
	WypelnText();

}

void MapaBudynki::StatystykiGen() {
	textureStat.loadFromFile("img/tloStat.png");
	spriteStat.setTexture(textureStat);
	spriteStat.setScale(1.5, 1);
	spriteStat.setPosition(920, 240);
}

void MapaBudynki::WypiszTab(vector<vector<Budynek>>& mapaBud, RenderWindow& window)
{
	for (int i = 0; i < mapaBud.size(); i++)
	{
		for (int j = 0; j < mapaBud[i].size(); j++)
		{
			window.draw(mapaBud[i][j].sprite);
		}
	}
	StatystykiGen();
	window.draw(spriteStat);
	for (int i = 0; i < 3; i++)
	{
		menu[i].position[0][0] = 940 + 40 * i;
		menu[i].position[0][1] = 500;
		menu[i].position[1][0] = 970 + 40 * i;
		menu[i].position[1][1] = 530;
		menu[i].sprite.setPosition(menu[i].position[0][0], menu[i].position[0][1]);
		window.draw(menu[i].sprite);
	}

}

void MapaBudynki::WypelnText() {
	for (int i = 0; i < mapaBud.size(); i++)
	{
		for (int j = 0; j < mapaBud[i].size(); j++)
		{
			mapaBud[i][j].NazwaT.setFillColor(sf::Color::Black);
			mapaBud[i][j].NazwaT.setPosition(940, 260);
			mapaBud[i][j].NazwaT.setFont(font);
			mapaBud[i][j].NazwaT.setCharacterSize(40);

			mapaBud[i][j].KosztT.setFillColor(sf::Color::Black);
			mapaBud[i][j].KosztT.setPosition(940, 300);
			mapaBud[i][j].KosztT.setFont(font);
			mapaBud[i][j].KosztT.setCharacterSize(24);

			mapaBud[i][j].MieszkT.setFillColor(sf::Color::Black);
			mapaBud[i][j].MieszkT.setPosition(940, 340);
			mapaBud[i][j].MieszkT.setFont(font);
			mapaBud[i][j].MieszkT.setCharacterSize(24);

			mapaBud[i][j].NazwaT.setString(mapaBud[i][j].nazwa);
			mapaBud[i][j].MieszkT.setString("Mieszkancy:" + to_string(mapaBud[i][j].mieszkancy) + " Na " + to_string(mapaBud[i][j].mieszkancyMax));
			mapaBud[i][j].KosztT.setString("Utrzymanie: " + to_string(mapaBud[i][j].koszt));

		}
	}
	for (int i = 0; i < 3; i++)
	{
		menu[i].NazwaT.setFillColor(sf::Color::Black);
		menu[i].NazwaT.setPosition(940, 260);
		menu[i].NazwaT.setFont(font);
		menu[i].NazwaT.setCharacterSize(40);

		menu[i].KosztT.setFillColor(sf::Color::Black);
		menu[i].KosztT.setPosition(940, 300);
		menu[i].KosztT.setFont(font);
		menu[i].KosztT.setCharacterSize(24);

		menu[i].MieszkT.setFillColor(sf::Color::Black);
		menu[i].MieszkT.setPosition(940, 340);
		menu[i].MieszkT.setFont(font);
		menu[i].MieszkT.setCharacterSize(24);

		menu[i].NazwaT.setString(menu[i].nazwa);
		menu[i].MieszkT.setString("Mieszkancy Max:" + to_string(menu[i].mieszkancyMax));
		menu[i].KosztT.setString("Utrzymanie: " + to_string(menu[i].koszt));
	}
}

void MapaBudynki::EventListener(RenderWindow& window, Event& event, int(&TabPomBud)[2])
{
	float mouseX = Mouse::getPosition(window).x;
	float mouseY = Mouse::getPosition(window).y;

	switch (event.type)
	{
	case Event::MouseMoved:
	{if (Statystyki(mouseX, mouseY))
	{
		int X = mouseX / 30;
		int Y = mouseY / 30;
		if (X > 0 && Y > 0 && X < (dlugosc - 1) && Y < (szerokosc - 1))
		{
			TabPomBud[0] = X;
			TabPomBud[1] = Y;
		}
	}


	int menuPos{};
	if (BudynkiMenu(mouseX, mouseY, menuPos))
	{
		TabPomBud[0] = 100;
		TabPomBud[1] = menuPos;

	}

	MoveTmpBud(window, mouseX, mouseY);

	break; }
	case Event::MouseButtonPressed:
		int menuPos2{};
		if (BudynkiMenu(mouseX, mouseY, menuPos2))
		{
			TmpBud = menu[menuPos2];
			window.draw(TmpBud.sprite);
			TmpBud.sprite.setPosition(TmpBud.position[0][0], TmpBud.position[0][1]);
			cout << "x";
		}

		if (PostawBudynekSpr(mouseX, mouseY))
		{
			int X = mouseX / 30;
			int Y = mouseY / 30;
			if (X > 0 && Y > 0 && X < (dlugosc - 1) && Y < (szerokosc - 1)) {
				PostawBudynek(X, Y);
				WypelnText();
			}
		}
		break;

	}
}

void MapaBudynki::PostawBudynek(int X, int Y)
{
	if (mapaBud[X][Y].typ == 0 && PoleSprawdz(X,Y))
	{
		NowyLudz();
		mapaBud[X][Y] = TmpBud;
	}
	LudzieDodaj(X,Y);
}

bool MapaBudynki::PoleSprawdz(int X, int Y)
{
	if (MapaPol[X][Y].typ == 0 || MapaPol[X][Y].typ == 3)
		return true;
	else
		return false;
}

bool MapaBudynki::PostawBudynekSpr(float& mouseX, float& mouseY)
{

	if (mouseX < 900 && mouseX > 0 && mouseX < 900 && mouseX > 0)
	{
		return true;
	}
	return false;
}

void MapaBudynki::MoveTmpBud(RenderWindow& window ,float& mouseX, float& mouseY) {
	int X = mouseX / 30;
	int Y = mouseY / 30;

	TmpBud.position[0][0] = X * 30-2;
	TmpBud.position[0][1] = Y * 30-2;
	TmpBud.position[1][0] = X * 30+30-2;
	TmpBud.position[1][1] = Y * 30+30-2;

	TmpBud.sprite.setPosition(TmpBud.position[0][0], TmpBud.position[0][1]);
	window.draw(TmpBud.sprite);
	
}

bool MapaBudynki::Statystyki(float& mouseX, float& mouseY) {
	if (mouseX < 900 && mouseX > 0 && mouseX < 900 && mouseX > 0)
	{
		return true;
	}
	return false;
}

bool MapaBudynki::BudynkiMenu(float& mouseX, float& mouseY, int& menuPos)
{
	bool doRet = false;
	for (int i = 0; i < 3; i++)
	{
		if (mouseX > menu[i].position[0][0] && mouseX < menu[i].position[1][0] && mouseY > menu[i].position[0][1] && mouseY < menu[i].position[1][1])
		{
			menuPos = i;
			doRet = true;
		}
	}

	return doRet;
}

void MapaBudynki::WyswietlTyp()
{

	for (int i = 0; i < 3; i++)
	{
		menu[i].position[0][0] = 940 + 40 * i;
		menu[i].position[0][1] = 500;
		menu[i].position[1][0] = 970 + 40 * i;
		menu[i].position[0][1] = 530;
		menu[i].sprite.setPosition(position[0][0], position[0][1]);
	}

}

void MapaBudynki::NowyLudz()
{
	if (TmpBud.typ == 1)
	{
		LudziePotrzeba -= 10;
	}
	if (TmpBud.typ == 2)
	{
		LudziePotrzeba += 20;
	}
}

void MapaBudynki::LudzieDodaj(int X, int Y)
{
	if (LudziePotrzeba < 0)
	{
		int dom[2]{ X,Y };
		int ludzieLoop = -LudziePotrzeba;
		for (int i = 0; i < ludzieLoop; i++)
		{
			Ludz tmp("Janusz",dom,"img/human.png",dom);
			ludzie.push_back(tmp);
			LudziePotrzeba++;
		}
	}
}

void MapaBudynki::LoadFont()
{
	font.loadFromFile("fonts/Roboto-Black.ttf");
}
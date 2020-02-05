#pragma once
#include "Pole.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;

class Mapa
{
private:
	unsigned short ziarnoTab[7]{};
	Font font;

	int losowa(int max, int min = 1);
	void WypelnTab(vector<vector<Pole>>& mapaPol);
	void rozdzielZiarno(int ziarno, unsigned short (&ziarnoTab)[7]);
	void losujGory();
	void losujRzeki();
	void losujPlacki(int wielkosc, int ilosc,int typ);
	void postawPole(vector<vector<Pole>>& mapaPol, int X, int Y, int typPola = 0);
	bool losowanieSprawdzanieKierunku(int& positionX, int& positionY, int kierunek);
	bool rzekaSprawdzanie(int positionX, int positionY);
	void LoadFont();
	void WypelnText();
	
public:
	int ziarno = 88888;
	vector<vector<Pole>> mapaPol;
	int dlugosc{}, szerokosc{};
	Texture textureStat;
	Sprite spriteStat;
	void StatystykiGen();
	bool Statystyki( float& mouseX, float& mouseY);
	Mapa(int dlugosc, int wielkosc);
	void WypiszTab(vector<vector<Pole>>& mapaPol, RenderWindow& window);
	void EventListener(sf::RenderWindow& window, sf::Event& event, int (&TabPomPola)[2]);
	bool WcisnietyPrzycisk(sf::RenderWindow& window, float& mouseX, float& mouseY);
	~Mapa();
};


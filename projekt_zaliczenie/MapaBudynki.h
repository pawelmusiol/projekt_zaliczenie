#pragma once
#include <vector>
#include "Budynek.h"
#include "Ludz.h"
#include "Mapa.h"
class MapaBudynki
{
public:
	MapaBudynki(int dlugosc, int wielkosc, vector<vector<Pole>>& mapaPol);
	int dlugosc{};
	int szerokosc{};
	int position[2][2];
	int LudziePotrzeba{};
	void EventListener(sf::RenderWindow& window, sf::Event& event, int(&TabPomBud)[2]);
	vector<vector<Budynek>> mapaBud;
	vector<Ludz> ludzie;
	Font font;
	Budynek menu[3] = { {"Dom",4, 10,"img/dom.png", 1},{"Fabryka", 6, 20, "img/fabryka.png", 2},{"Droga", 1, 0, "img/droga.png", 3} };
	Budynek TmpBud = { "Pusto",0,0,"", 0};
	
	void WypiszTab(vector<vector<Budynek>>& mapaBud ,RenderWindow& window);
private:
	Texture textureStat;
	Sprite spriteStat;

	void NowyLudz();
	void LudzieDodaj(int X, int Y);
	void WypelnTab();
	void LoadFont();
	bool Statystyki(float& mouseX, float& mouseY);
	void WypelnText();
	void StatystykiGen();
	//int WybierzTyp();
	bool BudynkiMenu(float& mouseX, float& mouseY, int& menuPos);
	void WyswietlTyp();
	void MoveTmpBud(RenderWindow& window, float& mouseX, float& mouseY);
	bool PostawBudynekSpr(float& mouseX, float& mouseY);
	void PostawBudynek(int X, int Y);
	bool PoleSprawdz(int X, int Y);
};


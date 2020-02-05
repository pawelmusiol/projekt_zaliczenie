#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Ludz.h"

using namespace std;
using namespace sf;

class Budynek
{
public:
	Texture texture;
	Sprite sprite;
	int position[2][2];
	Text NazwaT;
	Text KosztT;
	Text MieszkT;
	string nazwa;
	int koszt;
	int mieszkancy{};
	int mieszkancyMax{};
	int typ;
	vector<Ludz>LudzBudynek;

	Budynek(string nazwa, int koszt, int mieszkancyMax, string url, int typ);

private:
	string url;
};


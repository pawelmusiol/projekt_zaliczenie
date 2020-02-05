#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"


using namespace std;
using namespace sf;

class Ludz
{
public:
	Ludz(string imie, int dom[2], string url, int position[2], int wiek = 0);
	string imie;
	int wiek;
	int dom[2];
	int praca[2];
	string url;
	Texture texture;
	Sprite sprite;
	int position[2];
	
};


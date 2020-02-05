#include "Pole.h"
#include <string>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;


Pole::Pole(string nazwa, bool p, bool b, string url, int typ)
{
	przejscie = p;
	budowa = b;
	this->nazwa = nazwa;
	this->url = url;
	this->typ = typ;
	texture.loadFromFile(url);
	sprite.setTexture(texture);
}



Pole::~Pole() {

}
#include "Ludz.h"

Ludz::Ludz(string imie, int dom[2], string url, int position[2], int wiek)
{
	this->url = url;
	this->imie = imie;
	this->dom[0] = dom[0];
	this->dom[1] = dom[1];
	wiek = 0;
	texture.loadFromFile(url);
	sprite.setTexture(texture);
}

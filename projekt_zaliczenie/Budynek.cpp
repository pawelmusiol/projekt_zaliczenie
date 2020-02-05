#include "Budynek.h"

Budynek::Budynek(string nazwa, int koszt, int mieszkancyMax, string url, int typ)
{
	this->typ = typ;
	this->nazwa = nazwa;
	this->mieszkancyMax = mieszkancyMax;
	this->koszt = koszt;
	this->url = url;
	texture.loadFromFile(url);
	sprite.setTexture(texture);
}

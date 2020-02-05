#pragma once
#include <string>
#include <random>
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <vector>

using namespace std;

class Pole
{
public:
	Pole(string nazwa, bool p, bool b, string url, int typ);
	bool przejscie = 0, budowa = 0;
	string nazwa;
	string url;
	int position[2][2];
	int typ;
	sf::Font font;
	vector<sf::Text> text;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Text budowaT;
	sf::Text nazwaT;
	sf::Text przejscieT;
	~Pole();
};


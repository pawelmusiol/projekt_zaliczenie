#include <SFML/Graphics.hpp>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Mapa.h";
#include "MapaBudynki.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1240, 900), "Gierka");
	Mapa mapa(30, 30);
	MapaBudynki mapaBudynki(30, 30, mapa.mapaPol);
	int TabPomPola[2]{};
	int TabPomBud[2]{};
	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			}
		}

		mapa.EventListener(window, event, TabPomPola);
		mapaBudynki.EventListener(window, event, TabPomBud);
		window.clear();
		mapa.WypiszTab(mapa.mapaPol ,window);
		mapaBudynki.WypiszTab(mapaBudynki.mapaBud, window);
		if (TabPomBud[0] == 100)
		{
			window.draw(mapaBudynki.menu[TabPomBud[1]].NazwaT);
			window.draw(mapaBudynki.menu[TabPomBud[1]].MieszkT);
			window.draw(mapaBudynki.menu[TabPomBud[1]].KosztT);
		}
		else
		{
			window.draw(mapaBudynki.mapaBud[TabPomBud[0]][TabPomBud[1]].NazwaT);
			window.draw(mapaBudynki.mapaBud[TabPomBud[0]][TabPomBud[1]].MieszkT);
			window.draw(mapaBudynki.mapaBud[TabPomBud[0]][TabPomBud[1]].KosztT);
		}
		window.draw(mapaBudynki.TmpBud.sprite);
		window.draw(mapa.mapaPol[TabPomPola[0]][TabPomPola[1]].nazwaT);
		window.draw(mapa.mapaPol[TabPomPola[0]][TabPomPola[1]].przejscieT);
		window.draw(mapa.mapaPol[TabPomPola[0]][TabPomPola[1]].budowaT);
		

		window.display();
	}
	
	return 0;
}
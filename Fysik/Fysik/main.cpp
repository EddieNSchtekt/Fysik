#include <SFML/Graphics.hpp>

#include "Boat.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	sf::Clock cl;

	Boat o(100.0f,Vec(100.0f, 100.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), SailMain(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 15, 5,Vec(0.0,1.0,0.0)));


	//PhysicalObject o(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f));
	float t = 0.0f;
	while (window.isOpen())
	{
		t = cl.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
				{
					o.setAcc(o.getAcc() + Vec(-1.0f, 0.0f, 0.0f)*t);
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
				{
					o.setAcc(o.getAcc() + Vec(1.0f, 0.0f, 0.0f)*t);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				{
					o.setAcc(o.getAcc() + Vec(0.0f, -1.0f, 0.0f)*t);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				{
					o.setAcc(o.getAcc() + Vec(0.0f, 1.0f, 0.0f)*t);
				}*/
			}
		}
		o.windCalc(t,Vec(5,5,0));
		float x = o.getPos().getX();
		float y = o.getPos().getY();
		system("CLS");
		printf("X : %f\nY: %f", x, y);
		shape.setPosition(x, y);

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
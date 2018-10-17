#include <SFML/Graphics.hpp>

#include "Boat.h"
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	sf::Clock cl;

	sf::Sprite bg;
	sf::Texture bgTexture;
	int bgSize = 200;
	float keyFrame = 0;
	if (!bgTexture.loadFromFile("Images/Background.png"))
	{
		//Error!
	}
	bg.setTexture(bgTexture);
	bg.setTextureRect(sf::IntRect(0, 0, bgSize, bgSize));

	sf::Sprite boatSprite;
	sf::Texture boatTexture;
	int boatWidth = 64, boatHeight = 64;
	if (!boatTexture.loadFromFile("Images/Boat.png"))
	{
		//Error!
	}
	boatSprite.setTexture(boatTexture);
	boatSprite.setTextureRect(sf::IntRect(0, 0, boatWidth, boatHeight));

	sf::Sprite arrow;
	sf::Texture arrowTex;
	int arrowSize = 32;
	if (!arrowTex.loadFromFile("Images/Arrow.png"))
	{
		//Error!
	}
	arrow.setTexture(arrowTex);
	arrow.setTextureRect(sf::IntRect(0, 0, arrowSize, arrowSize));
	arrow.setOrigin(arrowSize / 2, arrowSize / 2);
	arrow.setPosition(arrowSize / 2, bgSize - arrowSize / 2);

	Boat o(100.0f,Vec((bgSize-boatWidth)/2, (bgSize-boatHeight)/2, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), SailMain(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 15, 5,Vec(0.0, -1.0,0.0)), Keel(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 1, 0.8, Vec(0.0, -1.0, 0.0)));


	//PhysicalObject o(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f));
	float t = 0.0f;
	Vec wind = Vec(5, 5, 0);
	float windVel;// = wind.getLength();

	float windAngle; /*= Vec(0.f, -1.f, 0.f).dot(wind);
	windAngle = windAngle / sqrt(((wind.getX()*wind.getX() + wind.getY()*wind.getY())));
	windAngle = acos(windAngle) * 360 / (2 * PI);
	if (wind.getX() < 0)
		windAngle = 360 - windAngle;*/

	windVel = 10;
	windAngle = 0;
	wind = Vec(sin(windAngle*(2*PI)/360), -cos(windAngle*(2 * PI) / 360), 0) * windVel;
	
	int waveDir = 0;
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
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
				{
					windAngle--;
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
				{
					windAngle++;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
				{
					windVel++;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
				{
					windVel--;
				}
			}
		}
		o.windCalc(t,wind);
		o.waterDragCalc(t);
		float x = o.getPos().getX();
		float y = o.getPos().getY();

		float vel = o.getVel().getLength();
		float spdX = o.getVel().getX();
		float spdY = o.getVel().getY();
		float dirX = spdX / vel;
		float dirY = spdY / vel;

		//windVel = wind.getLength();
		float windDirX = wind.getX() / windVel;
		float windDirY = wind.getY() / windVel;

		system("cls");
		printf("X : %f\nY: %f\nBoat Velocity: %f\nBoat Direction: (%f,%f)\nWind Velocity: %f\nWind Direction: (%f,%f)", x, y, vel, dirX, dirY, windVel, windDirX, windDirY);
		boatSprite.setPosition(x, y);
		if (y < -boatHeight)
			o.setPos(Vec(x, bgSize, 0));
		else if (y > bgSize)
			o.setPos(Vec(x, -boatHeight, 0));
		if (x > bgSize)
			o.setPos(Vec(-boatWidth, y, 0));
		else if (x < -boatWidth)
			o.setPos(Vec(bgSize, y, 0));


		if (wind.getX() > 0)
		{
			if (wind.getY() > 0)
				waveDir = 0;
			else
				waveDir = 1;
		}
		else
		{
			if (wind.getY() < 0)
				waveDir = 2;
			else
				waveDir = 3;
		}


		bg.setTextureRect(sf::IntRect(bgSize*((int)keyFrame%8), bgSize*waveDir, bgSize, bgSize));
		boatSprite.setTextureRect(sf::IntRect(boatWidth*((int)(keyFrame/2) % 2), 0, boatWidth, boatHeight));
		keyFrame += 0.02 * log(abs(windVel)+1);

		wind = Vec(sin(windAngle*(2 * PI) / 360), -cos(windAngle*(2 * PI) / 360), 0) * windVel;

		arrow.setRotation(windAngle);

		window.clear();
		window.draw(bg);
		window.draw(boatSprite);
		window.draw(arrow);
		window.display();
	}

	return 0;
}
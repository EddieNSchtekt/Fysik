#include <SFML/Graphics.hpp>

#include "Boat.h"

void representVector(Vec vec, sf::RectangleShape * rect)
{
	rect->setSize(sf::Vector2f(vec.getLength() / 4, 3));

	float angle = 360 / (2 * PI)*acos(vec.dot(Vec(1.0f, 0.0f, 0.0f))*(1 / vec.getLength()));

	if (vec.getY() < 0.0001)
	{
		angle = 360 - angle;
	}

	rect->setRotation(angle);
}

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

	Boat o(1200.0f,Vec((bgSize-boatWidth)/2, (bgSize-boatHeight)/2, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), SailMain(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 15, 5,Vec(0.0, -1.0,0.0)), Keel(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 1, 0.8, Vec(0.0, -1.0, 0.0)));

	sf::RectangleShape l(sf::Vector2f(10, 3));
	l.setPosition(o.getPos().getX(), o.getPos().getY());
	sf::RectangleShape d(sf::Vector2f(10, 3));
	d.setPosition(o.getPos().getX(), o.getPos().getY());

	sf::RectangleShape kl(sf::Vector2f(10, 3));
	kl.setPosition(o.getPos().getX(), o.getPos().getY());
	kl.setFillColor(sf::Color::Green);
	sf::RectangleShape kd(sf::Vector2f(10, 3));
	kd.setPosition(o.getPos().getX(), o.getPos().getY());
	kd.setFillColor(sf::Color::Red);

	//PhysicalObject o(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f));
	float t = 0.0f;
	float clearCounter = 0.0f;
	Vec wind;
	float windVel;

	float windAngle;

	windVel = 10;
	windAngle = 90;
	wind = Vec(sin(windAngle*(2 * PI) / 360), -cos(windAngle*(2 * PI) / 360), 0) * windVel;
	
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

		float windDirX = wind.getX() / windVel;
		float windDirY = wind.getY() / windVel;

		representVector(o.getSailLift(), &l);
		representVector(o.getSailDrag(), &d);

		representVector(o.getKeelDrag(), &kd);
		representVector(o.getKeelLift(), &kl);

		Vec appWind = wind - o.getVel();
		float appWindDirX = appWind.getX() / appWind.getLength();
		float appWindDirY = appWind.getY() / appWind.getLength();

		clearCounter += 0.001;
		if (clearCounter > 1)
		{
			system("cls");
			clearCounter = 0;
			printf("X : %f\nY: %f\nBoat Velocity: %f\nBoat Direction: (%f,%f)\nWind Velocity: %f\nWind Direction: (%f,%f)\nApparent Wind Velocity: %f\nApparent Wind Direction: (%f,%f)", x, y, vel, dirX, dirY, windVel, windDirX, windDirY, appWind.getLength(), appWindDirX, appWindDirY);
		}
		boatSprite.setPosition(x, y);
		l.setPosition(x, y);
		d.setPosition(x, y);
		kl.setPosition(x, y);
		kd.setPosition(x, y);

		if (y < -boatHeight)
		{
			o.setPos(Vec(x, bgSize, 0));
			l.setPosition(x, bgSize);
			d.setPosition(x, bgSize);
			kl.setPosition(x, bgSize);
			kd.setPosition(x, bgSize);
		}
		else if (y > bgSize)
		{
			o.setPos(Vec(x, -boatHeight, 0));

			d.setPosition(x, -boatHeight);
			l.setPosition(x, -boatHeight);
			kl.setPosition(x, -boatHeight);
			kd.setPosition(x, -boatHeight);
		}
		if (x > bgSize)
		{
			o.setPos(Vec(-boatWidth, y, 0));
			d.setPosition( -boatWidth, y);
			l.setPosition( -boatWidth, y);
			kl.setPosition(-boatWidth, y);
			kd.setPosition(-boatWidth, y);
		}
		else if (x < -boatWidth)
		{
			o.setPos(Vec(bgSize, y, 0));
			l.setPosition( bgSize, y);
			d.setPosition( bgSize, y);
			kl.setPosition(bgSize, y);
			kd.setPosition(bgSize, y);
		}

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
		keyFrame += 0.0005 * log(abs(windVel)+1);

		wind = Vec(sin(windAngle*(2 * PI) / 360), -cos(windAngle*(2 * PI) / 360), 0) * windVel;

		arrow.setRotation(windAngle);

		window.clear();
		window.draw(bg);
		window.draw(boatSprite);
		window.draw(arrow);
		window.draw(l);
		window.draw(d);
		window.draw(kl);
		window.draw(kd);
		window.display();
	}

	return 0;
}
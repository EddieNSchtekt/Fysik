#include <SFML/Graphics.hpp>

#include "Boat.h"

#define WINDOW_WIDTH 204
#define WINDOW_HEIGHT 204

void representVector(Vec vec, sf::RectangleShape * rect)
{
	rect->setSize(sf::Vector2f(vec.getLength() / 100, 3));

	float angle = 360 / (2 * PI)*acos(vec.dot(Vec(1.0f, 0.0f, 0.0f))*(1 / vec.getLength()));

	if (vec.getY() < 0.0001)
	{
		angle = 360 - angle;
	}

	rect->setRotation(angle);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	sf::Clock cl;

	sf::Sprite bg;
	sf::Texture bgTexture;
	int bgSize = 272;
	float keyFrame = 0;
	if (!bgTexture.loadFromFile("Images/BackgroundNew.png"))
	{
		//Error!
	}
	bg.setTexture(bgTexture);
	bg.setTextureRect(sf::IntRect(0, 0, bgSize, bgSize));
	bg.setOrigin(34, 34);

	sf::Sprite boatSprite;
	sf::Texture boatTexture;
	int boatWidth = 18, boatHeight = 64;
	if (!boatTexture.loadFromFile("Images/SmallBoat.png"))
	{
		//Error!
	}
	boatSprite.setTexture(boatTexture);
	boatSprite.setTextureRect(sf::IntRect(0, 0, boatWidth, boatHeight));
	boatSprite.setOrigin(boatWidth / 2, boatHeight - 27);
	boatSprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	sf::Sprite mainSail;
	sf::Texture mainSailTex;
	int sailWidth = 18, sailHeight = 64;
	if (!mainSailTex.loadFromFile("Images/SmallSail.png"))
	{
		//Error!
	}
	mainSail.setTexture(mainSailTex);
	mainSail.setTextureRect(sf::IntRect(0, 0, sailWidth, sailHeight));
	mainSail.setOrigin(sailWidth / 2, (sailHeight / 2) - 14);
	mainSail.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 19);
	
	sf::Sprite rudder;
	sf::Texture rudderTex;
	int rudderWidth = 18, rudderHeight = 64;
	if (!rudderTex.loadFromFile("Images/Rudder.png"))
	{
		//Error!
	}
	rudder.setTexture(rudderTex);
	rudder.setTextureRect(sf::IntRect(0, 0, rudderWidth, rudderHeight));
	rudder.setOrigin(rudderWidth / 2, rudderHeight - 15);
	rudder.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 12);

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
	arrow.setPosition(arrowSize / 2, WINDOW_HEIGHT - arrowSize / 2);

	sf::Sprite arrow2;
	sf::Texture arrow2Tex;
	int arrow2Size = 32;
	if (!arrow2Tex.loadFromFile("Images/Arrow2.png"))
	{
		//Error!
	}
	arrow2.setTexture(arrow2Tex);
	arrow2.setTextureRect(sf::IntRect(0, 0, arrow2Size, arrow2Size));
	arrow2.setOrigin(arrow2Size / 2, arrow2Size / 2);
	arrow2.setPosition(arrow2Size / 2, WINDOW_HEIGHT - arrow2Size * 2);

	Boat o(8120, Vec(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), SailMain(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 15.1, 4.7,Vec(0.0, -1.0, 0.0)), Keel(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 1.50, 1.85, 1.05, Vec(0.0, -1.0, 0.0)*(1 / sqrtf(1))), Keel(Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), Vec(0.0f, 0.0f, 0.0f), 1.47,0.68,0.32, Vec(1.0, -1.0, 0.0)*(1/sqrtf(1))));

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

	float t = 0.0f;
	float clearCounter = 0.0f;

	float windVel = 30; //Pixels per second. One meter is approximately 4 pixels
	float windAngle = 90; // Degrees
	Vec wind = Vec(sin(windAngle*(2 * PI) / 360), -cos(windAngle*(2 * PI) / 360), 0) * windVel;

	float sailAngle = o.getMainSailAngle().dot(Vec(0.f, -1.f, 0.f));
	sailAngle = acos(sailAngle) * 360 / (2 * PI);

	float rudderAngle = o.getRudderAngle().dot(Vec(0.f, -1.f, 0.f));
	rudderAngle = acos(rudderAngle) * 360 / (2 * PI);

	float x = WINDOW_WIDTH / 2;
	float y = WINDOW_HEIGHT / 2;
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

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
				{
					sailAngle++;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
				{
					sailAngle--;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				{
					rudderAngle++;
					if (rudderAngle > 45)
					{
						rudderAngle = 45;
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				{
					rudderAngle--;
					
					if(rudderAngle < -45)
						rudderAngle = -45;
				}
			}
		}
		o.calcForce(t, wind);

		float moveX = x - o.getPos().getX();
		float moveY = y - o.getPos().getY();

		x = o.getPos().getX();
		y = o.getPos().getY();

		float vel = o.getVel().getLength();
		float spdX = o.getVel().getX();
		float spdY = o.getVel().getY();

		float dirX = 0;
		float dirY = 0;
		if (vel > 0.00001)
		{
			dirX = spdX / vel;
			dirY = spdY / vel;
		}

		float windDirX = wind.getX() / windVel;
		float windDirY = wind.getY() / windVel;
		
		representVector(o.getSailLift(), &l);
		representVector(o.getSailDrag(), &d);

		representVector(o.getKeelDrag(), &kd);
		representVector(o.getKeelLift(), &kl);


		float appWindDirX = 0;
		float appWindDirY = 0;

		Vec appWind = wind - o.getVel();
		if (appWind.getLength() > 0.0001)
		{
			appWindDirX = appWind.getX() / appWind.getLength();
			appWindDirY = appWind.getY() / appWind.getLength();
		}

		clearCounter += 0.001;
		if (clearCounter > 1)
		{
			system("cls");
			clearCounter = 0;
			printf("X : %f\nY: %f\nBoat Velocity: %f\nBoat Direction: (%f,%f)\nWind Velocity: %f\nWind Direction: (%f,%f)\nApparent Wind Velocity: %f\nApparent Wind Direction: (%f,%f)", x, y, vel, dirX, dirY, windVel, windDirX, windDirY, appWind.getLength(), appWindDirX, appWindDirY);
		}

		bg.move(moveX, moveY);

		if (bg.getPosition().y < -34)
		{
			bg.setPosition(bg.getPosition().x, 34);
		}
		else if (bg.getPosition().y > 34)
		{
			bg.setPosition(bg.getPosition().x, -34);
		}
		if (bg.getPosition().x > 34)
		{
			bg.setPosition(-34, bg.getPosition().y);
		}
		else if (bg.getPosition().x < -34)
		{
			bg.setPosition(34, bg.getPosition().y);
		}

		bg.setTextureRect(sf::IntRect(bgSize*((int)keyFrame%4), 0, bgSize, bgSize));
		boatSprite.setTextureRect(sf::IntRect(boatWidth*((int)(keyFrame/2) % 2), 0, boatWidth, boatHeight));
		boatSprite.setRotation(o.getAngle() *360/(2*PI));
		keyFrame += 0.0003 * log(abs(windVel)+1);

		wind = Vec(sin(windAngle*(2 * PI) / 360), -cos(windAngle*(2 * PI) / 360), 0) * windVel;
		o.setMainSailAngle(Vec(sin(sailAngle*(2 * PI) / 360), -cos(sailAngle*(2 * PI) / 360), 0));
		o.setRudderAngle(Vec(sin(rudderAngle*(2 * PI) / 360), -cos(rudderAngle*(2 * PI) / 360), 0));

		appWind = appWind * (1 / appWind.getLength());
		float appWindAngle = appWind.dot(Vec(0.f, -1.f, 0.f));
		appWindAngle = acos(appWindAngle) * 360 / (2 * PI);
		float cross = (Vec(0.f,-1.f,0.f).crossProd(appWind)).getZ();
		if (cross < 0)
		{
			appWindAngle *= -1;
		}

		arrow.setRotation(windAngle);
		arrow2.setRotation(appWindAngle);

		float mainSailAngle = atan2f(o.getMainSailAngle().getX(), -o.getMainSailAngle().getY())*360/(2*PI);
		mainSail.setRotation(mainSailAngle);
		float rudderAngle = atan2f(o.getRudderAngle().getX(), -o.getRudderAngle().getY()) * 360 / (2 * PI);
		rudder.setRotation(rudderAngle);

		float boatRotation = boatSprite.getRotation() * 2 * PI / 360;

		mainSail.setPosition(boatSprite.getPosition().x + (19*sin(boatRotation)), boatSprite.getPosition().y + (-19*cos(boatRotation)));
		rudder.setPosition(boatSprite.getPosition().x + (-12 * sin(boatRotation)), boatSprite.getPosition().y + (12 * cos(boatRotation)));

		window.clear();
		window.draw(bg);
		window.draw(rudder);
		window.draw(boatSprite);
		window.draw(mainSail);
		window.draw(arrow);
		window.draw(arrow2);

		window.draw(l);
		window.draw(d);
		window.draw(kl);
		window.draw(kd);

		window.display();
	}

	return 0;
}
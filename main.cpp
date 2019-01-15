#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

#define PI 3.14159265

constexpr int windowWidth{800}, windowHeight{600};
constexpr float snakeSize{50.f}, snakePoints{3};

struct Snake
{
    CircleShape shape;
    Vector2f velocity;
    Vector2i mousePos;
    float angle;

    Snake(float mx, float my)
    {
	shape.setPosition(mx, my);
	shape.setRadius(snakeSize);
	shape.setPointCount(snakePoints);
	shape.setFillColor(Color::Red);
	shape.setOrigin(snakeSize, snakeSize);
    }

    void update(RenderWindow& refWindow)
    {
	mousePos = Mouse::getPosition(refWindow);
	cout << mousePos.x << "\n";
	cout << mousePos.y << "\n";

	angle = atan2(mousePos.y - shape.getPosition().y, mousePos.x - shape.getPosition().x) * (180/PI);
	cout << angle << "\n";

	if(angle < 0)
	    {
		angle = 360 - (-angle);
	    }
	angle -= 30.f;
	shape.setRotation(angle);
	// shape.move(velocity)
    }
};
    
int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 4;
    
    RenderWindow window(VideoMode(windowWidth, windowHeight), "AI Snake", Style::Default, settings);


    // Constructs and starts timer
    Clock clock;

    Snake snake{windowWidth / 2, windowHeight / 2};

    while (window.isOpen())
    {
	// Restarts clock and returns time since last restart.
	Time elapsed = clock.restart();
	
	cout << elapsed.asMicroseconds() << "\n";
	cout << elapsed.asSeconds() << "\n";
	cout << elapsed.asMilliseconds() << "\n";

	snake.update(window);
	
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

	
        window.clear();
        window.draw(snake.shape);
        window.display();
    }

    return 0;
}

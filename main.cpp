#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

#define PI 3.14159265

constexpr int windowWidth{800}, windowHeight{600};
constexpr float snakeSize{30.f}, snakePoints{5};

class Util
{
private:
    
    float desiredAngle;
    
public:
    // Helper func to make nodes of snake objects point at the previous node
    float angleToPointAt(CircleShape& originalShape, CircleShape& targetShape, float offset)
    {
	
	desiredAngle = atan2(targetShape.getPosition().y - originalShape.getPosition().y, targetShape.getPosition().x - originalShape.getPosition().x) * (180/PI);
	
	if(desiredAngle < 0)
	    {
		desiredAngle = 360 - (desiredAngle);
	    }

	desiredAngle += offset;
	
	return desiredAngle;
    }
};

class Snake
{
private:

    Vector2f velocity;
    Vector2i mousePos;
    float angle;
    int nodes;
    Util util;
    Texture texture;
    
public:
    
    CircleShape shape;
    
    Snake(float mx, float my, Color idk)
    {
	if(!texture.loadFromFile("test.png"))
	    {
		cout << "Did not load image\n";
	    }
	
	shape.setPosition(mx, my);
	shape.setRadius(snakeSize);
	shape.setPointCount(snakePoints);
	//	shape.setFillColor(Color::Green);
	shape.setFillColor(idk);
	shape.setOrigin(snakeSize, snakeSize);
	shape.setTexture(&texture);
    }

    void createSnakeTail(int nodes)
    {
        for(int i = 0; i++; i < nodes)
	    {
		//add snake node to list and set each angle to follow the previous node
	    }
    }
    
    void update(/*RenderWindow& refWindow*/ CircleShape& target)
    {
	// // Use the window created in main() and get the mouse position from it.
	// mousePos = Mouse::getPosition(refWindow);

	// cout << mousePos.x << "\n";
	// cout << mousePos.y << "\n";
	
	// // Take the distance form the mouse to the current shape pos and the take tan(y/x)
	// // to obtain the proper angle between the two. 
	// angle = atan2(mousePos.y - shape.getPosition().y, mousePos.x - shape.getPosition().x) * (180/PI);
	// cout << angle << "\n";

	// // Since the angle is calculated from [-180, 180] it needs to be converted to [0, 360]
	// // to work with sfml setRotation().
	// if(angle < 0)
	//     {
	// 	angle = 360 - (-angle);
	//     }

	// // Triangle oriented incorrectly, -30f rotates the triangle so a point is facing the mouse.
	// angle -= 30.f;
	// shape.setRotation(angle);
	// // shape.move(velocity)

	shape.setRotation(util.angleToPointAt(shape,target,0.f));
    }
};
    
int main()
{
    ContextSettings settings;
    settings.antialiasingLevel = 4;
    
    RenderWindow window(VideoMode(windowWidth, windowHeight), "AI Snake", Style::Default, settings);


    // Constructs and starts timer
    Clock clock;

    Color color;

    // Creates a object in the center of the screen.
    Snake snake{windowWidth / 2, windowHeight / 2, color.Green};
    Snake otherSnake{windowWidth / 2, windowHeight - 200, color.Red};
    Snake anotherSnake{windowWidth / 2, windowHeight - 150, color.Blue};
    Snake theLastSnake{windowWidth / 2, windowHeight - 100, color.White};
    

    float deltaTime;

    while (window.isOpen())
    {
	// Restarts clock and returns time since last restart.
	Time elapsed = clock.restart();
	deltaTime = elapsed.asSeconds();

	cout << deltaTime << "\n";

	
	// Update list
	otherSnake.update(snake.shape);
	anotherSnake.update(otherSnake.shape);
	theLastSnake.update(anotherSnake.shape);
	
        Event event;

	// Listens for close event to close the window.
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

	
        window.clear();
	
	// List of objects to draw
        window.draw(snake.shape);
	window.draw(otherSnake.shape);
	window.draw(anotherSnake.shape);
	window.draw(theLastSnake.shape);
        window.display();
    }

    return 0;
}

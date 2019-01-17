#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

#define PI 3.14159265

constexpr int windowWidth{800}, windowHeight{600};
constexpr float snakeSize{30.f}, snakePoints{3};

class Util
{
private:
    
    float desiredAngle;
    
public:
    // Helper func to make nodes of snake objects point at the previous node
    float angleToPointAt(CircleShape& originalShape, CircleShape& targetShape, float offset)
    {
	// Takes the distance from the origin to the target and calculates tan(y/x) to get the desired angle.
	desiredAngle = atan2(targetShape.getPosition().y - originalShape.getPosition().y, targetShape.getPosition().x - originalShape.getPosition().x) * (180/PI);

	// From [-180, 180] to [0, 360]
	if(desiredAngle < 0)
	{
	    desiredAngle = 360 - (desiredAngle);
	}
	
	// Gives the option to offset the angle for use with different shapes.
	desiredAngle += offset;
	
	return desiredAngle;
    }
};

class Snake
{
private:

    Vector2f velocity;
    float angle;
    Util util;
    Texture texture;
    Color snakeColor;
    float startPosX;
    float adjustedPosX;
    float startPosY;
    int numberOfNodes;
    CircleShape snake;
    vector<CircleShape> snakeNodes;
    
    // Looking into using ternary to construct tail from vector of snakes
    void snakeTail()
    {
	cout << "snakeTail() called." << "\n";
	cout << "Number of nodes: " << numberOfNodes << "\n";
	// Step through and set values for each snakeNode

	// Initialize
	snakeNodes.resize(numberOfNodes);

	cout << "allocate memory for snakeNodes" << "\n";
	adjustedPosX = startPosX;

	cout << "adjustedPosX: " << adjustedPosX << "\n";
	
        for(int i = 0; i < numberOfNodes; i++)
	{
	    cout << "for loop working..." << "\n";
	    // Need to adjust start pos by some amount
	    adjustedPosX += 10;

	    cout << "new pos: " << adjustedPosX << "\n";
	
	    snakeNodes[i].setPosition(adjustedPosX, startPosY);
	    snakeNodes[i].setRadius(snakeSize);
	    snakeNodes[i].setPointCount(snakePoints);
	    snakeNodes[i].setFillColor(snakeColor);
	    snakeNodes[i].setOrigin(snakeSize, snakeSize);
	    //snakeNodes[i].setTexture(&snakeTexture);
	    // each origin should be fixed to the previous origin
	    // add snake node to list and set each angle to follow the previous node
	}
    }
    
public:
    
    // Snake constructor
    Snake(float mx, float my, Color color, int nodes)
    {
	snakeColor = color;
	numberOfNodes = nodes;	
	startPosX = mx;
	startPosY = my;
	
	// if(!texture.loadFromFile("someImage.png"))
	// {
	//     cout << "Did not load image\n";
	// }
	
	snake.setPosition(mx, my);
	snake.setRadius(snakeSize);
	snake.setPointCount(snakePoints);
	snake.setFillColor(color);
	snake.setOrigin(snakeSize, snakeSize);
	//shape.setTexture(&snakeTexture);
	
       	snakeTail();
        
    }

    // Call to update properties of object each frame
    void update(CircleShape& target)
    {
	snake.setRotation(util.angleToPointAt(snake,target,-90.f));
    }

    // Call to draw the updated property values each frame
    void draw(RenderWindow& window)
    {
	// Draw a single snake node
	window.draw(snake);
	
	// Draw each other snake node to create a tail
	for(int i = 0; i < numberOfNodes; i++)
	{
	    // cout << "drawing stuff..." << "\n";
	    window.draw(snakeNodes[i]);
	}
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

    // Creates a snake object in the center of the screen.
    int snakeNodes = 5;
    Snake snake{windowWidth / 2, windowHeight / 2, color.Green, snakeNodes};

    float deltaTime;

    while (window.isOpen())
    {
	// Restarts clock and returns time since last restart.
	Time elapsed = clock.restart();
	deltaTime = elapsed.asSeconds();

	//cout << deltaTime << "\n";	

	// Meh, an event
        Event event;

	// Listens for close event to close the window.
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
	    {
		window.close();
	    }
        }

	// Clear the window each frame
        window.clear();
	
	// List of objects to draw
	snake.draw(window);

	// Display the screen
        window.display();
    }

    return 0;
}

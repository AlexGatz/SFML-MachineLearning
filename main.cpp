// This is a thing, that does stuff. If you would like to learn about the thing or the stuff
// you can contact me at the.neocoder@gmail.com
// GitHub: TheNeoCoder/SFML-MachineLearning

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;
using namespace sf;

#define PI 3.14159265

constexpr int windowWidth{800}, windowHeight{600};
constexpr float snakeSize{30.f}, snakePoints{3};

// ------------------------------------------------------------------------------------ Utilities

class Util
{
private:
    
    float desiredAngle;
    
public:
    // Helper func to make nodes of snake objects point at the previous node
    // Accepts two CircleShape objects and a float and returns a float which is what
    // sfml uses for its setRotation functions. TODO: Perhaps make this more generic and eliminate
    // the use of CircleShape objects ..... maybe... eventually ... if I have to (template).
    float angleToPointAt(CircleShape& originalShape, CircleShape& targetShape, float offset)
    {
	
	// Takes the distance from the origin to the target and calculates tan(y/x) to get the
	// desired angle.
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

// ----------------------------------------------------------------------------------- Main Objects

class Snake
{
private:

    Vector2f velocity; // Not used yet
    float angle; // I mean... its an angle...
    Util util; // Need to use to force each snakeNode to face the previous one
    Texture texture; // png for new look for the snake nodes
    Color snakeColor; // don't really need this atm, but it makes things look nice
    float startPosX; // class scope position variable
    float adjustedPosX; // holds value of adjusted value used to initialize each snake node
    float startPosY; // same as x
    int numberOfNodes; // should probably be used localy for every snake obeject ... idk
    CircleShape snake; // its a snake... really this is the head of the snake

    // this is actually the tail at this time... maybe I don't need the snake head? but somehow
    // I want to control the head and have the tail lag behind... idk...
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

	// This needs to go somewhere else for class scope
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

// -------------------------------------------------------------------------- main ... enough said.
    
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

	// Listens for window close event to close the window.
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
	    {
		window.close();
	    }
        }
p
	// Clear the window each frame
        window.clear();
	
	// List of objects to draw
	snake.draw(window);

	// Display the screen
        window.display();
    }

    return 0;
}

// ----------------------------------------------------------------------- The End, or is it!??!??!

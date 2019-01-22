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
//constexpr float snakeSize{30.f}, snakePoints{3};

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
	desiredAngle = atan2(targetShape.getPosition().y - originalShape.getPosition().y,
			     targetShape.getPosition().x - originalShape.getPosition().x) * (180/PI);

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

struct Position { int x, y; };

class Snake {
    constexpr static float defaultRadius = 30.f; 
    constexpr static int defaultPointCount = 6;
    constexpr static float defaultVelocity = 10.f;
    float currentVelocityX;
    float currentVelocityY;
  
    vector<CircleShape> bodyShapes; //includes head

public:
    Snake(Position pos,
	  Color fillColor, 
	  int bodyLength, 
	  int pointCount = defaultPointCount,
	  float radius   = defaultRadius)
    {
        //init body
        bodyShapes.resize(bodyLength + 1);
        for(auto& shp : bodyShapes)
	{
	    shp.setRadius(radius);
	    shp.setPosition(pos.x, pos.y);
	    shp.setPointCount(pointCount);
	    shp.setFillColor(fillColor);
	    shp.setOrigin(radius , radius);
	    pos.y+=50;
        }  
    }

    void move()
    {
	if(Keyboard::isKeyPressed(Keyboard::W))
	{
	    currentVelocityX = 0;
	    currentVelocityY = -defaultVelocity;
	    cout << "W is pressed" << "\n";
	}
	if(Keyboard::isKeyPressed(Keyboard::A))
	{
	    currentVelocityX = -defaultVelocity;
	    currentVelocityY = 0;
	    cout << "A is pressed" << "\n";
	}
	if(Keyboard::isKeyPressed(Keyboard::S))
	{
	    currentVelocityX = 0;
	    currentVelocityY = defaultVelocity;
	    cout << "S is pressed" << "\n";
	}
	if(Keyboard::isKeyPressed(Keyboard::D))
	{
	    currentVelocityX = defaultVelocity;
	    currentVelocityY = 0;
	    cout << "D is pressed" << "\n";
	}
	// Move some stuff here
	
	for(auto& shp : bodyShapes)
	{
	    shp.move(currentVelocityX, currentVelocityY);
        }
    }

    void update(float deltaTime)
    {
	move();
	//calculate your angle here
	//float angle = ...;
	//bodyShapes.front().setRotation(angle);
    }
  
    void draw(RenderWindow& window) const
    {
	for(const auto& shp : bodyShapes)
	{
	    window.draw(shp);
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
    int snakeBodySize{5};
    Position position{windowWidth / 2, windowHeight /2};
    Snake snake(position, color.Green, snakeBodySize);

    float deltaTime;
    float accumulator;
    float t = 0.0f;
    const float dt = 0.01;

    while (window.isOpen())
    {
	// Restarts clock and returns time since last restart.
	Time elapsed = clock.restart();
	deltaTime = elapsed.asSeconds();

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

	// Clear the window each frame
        window.clear();

	// Update objects
      	snake.update(deltaTime);
	
	// Draw objects
	snake.draw(window);

	// Display the screen
        window.display();
    }

    return 0;
}

// ----------------------------------------------------------------------- The End, or is it!??!??!

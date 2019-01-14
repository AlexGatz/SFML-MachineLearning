#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Constructs and starts timer
    sf::Clock clock;

    while (window.isOpen())
    {
	// Restarts clock and returns time since last restart.
	sf::Time elapsed = clock.restart();
	cout << elapsed.asSeconds() << "\n";

	
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

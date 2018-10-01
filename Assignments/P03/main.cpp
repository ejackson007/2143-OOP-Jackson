#include <SFML/Graphics.hpp>
int main() {
	// creates window to print on
 sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
 // creates circle object with size
 sf::CircleShape shape(100.f);
 // fills the shape object color to greem
 shape.setFillColor(sf::Color::Green);
 // Keeps the program running while the window is open
 while (window.isOpen()) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }

  window.clear();
  window.draw(shape);
  window.display();
}
  return 0;
}

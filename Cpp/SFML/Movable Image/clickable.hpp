/*
 * clickable.hpp
 *
 *  Created on: 10.03.2017
 *      Author: Gregor
 */

#ifndef SRC_CLICKABLE_HPP_
#define SRC_CLICKABLE_HPP_

#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*
 * Represents a graphical element, that can be drawn on an
 * sf::Renderwindow. It is able to be moved, displays an image
 * and runs a callback if the mouse clicked it.
 */
class Button {

	private:

		// reference to the main-window
		RenderWindow *pmWindow;

		// callback function
		void (*command) (Event event, Button *clickable);

	public:

		// graphical informations
		Vector2f pos;
		Vector2f size;

		// graphical elements
		Texture texture;
		Sprite  sprite;

	public:

		// Initialisation
		Clickable(RenderWindow *pmWindow, Vector2f pos, Vector2f size, string filename, void (*command) (Event event, Button *button));

		// draws the widget to the screen
		void draw();

		// handles incoming events and calls command if this is clicked
		void handleEvent(Event event);

		// computes whether a point is inside the boundingbox of this widget
		bool isMouseInside();
		bool isPointInside(Vector2f point);

		// moves this widget by a given difference
		void move(Vector2f difference);
};



#endif /* SRC_CLICKABLE_HPP_ */

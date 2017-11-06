/*
 * Label.hpp
 *
 *  Created on: 06.04.2017
 *      Author: Gregor
 */

#ifndef SRC_LABEL_HPP_
#define SRC_LABEL_HPP_

#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*
 * A simple widget to display some text.
 */
class Label {

	private:

		// reference to the main-window
		RenderWindow *pmWindow;

		// graphical elements
		Font font;
		Text text;
		RectangleShape background;

		// graphical informations
		Vector2f pos;
		Vector2f size;
		Vector2f padding;

		// content
		string message;

	public:

		// Initialisation
		Label(RenderWindow *pmWindow, Vector2f pos, string message, string fontPath);

		// draws the widget to the screen
		void draw();

		// changes the displayed text
		void setMessage(string message);
		void setForegroundColor(Color color);
		void setBackgroundColor(Color color);

		// get-functions
		Font *getFont();
		Text *getText();
		Vector2f getPos();
		Vector2f getSize();
		string getMessage();

};

#endif /* SRC_LABEL_HPP_ */

/*
 * Triangle.hpp
 *
 *  Created on: 21.03.2017
 *      Author: Gregor
 */

#ifndef SRC_TRIANGLE_TRIANGLE_HPP_
#define SRC_TRIANGLE_TRIANGLE_HPP_

#include <SFML/Graphics.hpp>

using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*
 * Defines a class to handle single triangles in the
 * polygon triangulation. These triangles can be drawn.
 */
class Triangle {

	private:

		// reference to the main-window
		RenderWindow *pmWindow;

		// graphical informations
		Vector2f points[3];
		Color color;

	public:

		// Initialisation
		Triangle();
		void init(RenderWindow *pmWindow, Vector2f points[], Color color);

		// draws the thriangle to the screen
		void draw();

		// get-methods
		Vector2f getPoint(int index);
};



#endif /* SRC_TRIANGLE_TRIANGLE_HPP_ */

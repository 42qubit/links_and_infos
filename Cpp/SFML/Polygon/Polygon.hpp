/*
 * Polygon.hpp
 *
 *  Created on: 15.03.2017
 *      Author: Gregor
 */

#ifndef SRC_POLYGON_HPP_
#define SRC_POLYGON_HPP_

#include <vector>

#include <SFML/Graphics.hpp>

#include "Triangle.hpp"

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*
 * The polygon class handles pointlists, so that they can be drawn
 * to an sf::RenderWindow.
 */
class Polygon {

	private:

		// reference to the main-window
		RenderWindow *pmWindow;

		// callback function
		void (*command) (Event event, Polygon *polygon);

		// graphical informations
		int size;
		float minX, minY, maxX, maxY;
		Color color;
		vector<Triangle> triangles;
		vector<Vector2f> points;

	private:

		// Belong to init()
		void  triangulate();
		float sign (Vector2f p1, Vector2f p2, Vector2f p3);
		bool  isPointInTriangle (Vector2f v1, Vector2f v2, Vector2f v3, Vector2f pt);
		int   getEar(vector<Vector2f> *pointList);

		// Belongs to isPointInside()
		float computeCross(float testPointY, Vector2f p1, Vector2f p2);

	public:

		// Initialisation
		Polygon(RenderWindow *pmWindow, Color color, void (*command) (Event event, Polygon *polygon));
		void setPoints(vector<Vector2f> points);

		// draws the polygon to the screen
		void draw();

		// handles incoming events and calls command if this is clicked
		void handleEvent(Event event);

		// Tests, whether a point is inside the polygon or not
		bool isPointInside(Vector2f testPoint);

		// get-methods
		Vector2f getPoint(int index);
		int 	 getSize();
		int 	 getNumberOfTriangles();

};

#endif /* SRC_POLYGON_HPP_ */

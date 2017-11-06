/*
 * map.hpp
 *
 *  Created on: 04.02.2017
 *      Author: Gregor
 */

#ifndef SRC_MAP_HPP_
#define SRC_MAP_HPP_

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../Clickable/clickable.hpp"
#include "../Polygon/Polygon.hpp"

using namespace std;
using namespace sf;

enum MapType { GEOGRAPHY, NAMES, POLITICS };

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*
 * This class is a graphical element, that mixes graphical- and game-
 * logic. The Map is a field, on which the player's armies move and
 * where cities and countries find their interactive-visual representation.
 */
class Map {

	private:

		// reference to the main-window
		RenderWindow *pmWindow;

		// relevant for the movement of the map and its sprites
		bool isMapMoving;
		bool isSpriteMoving;
		int  actualSprite;

		// relevant for the map-move function
		Vector2f mouseOldPos, mouseOldPosOnMap;

		// relevant for the map-zoom function
		float zoomList[8] = { 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3 };
		int zoomIndex;

		// graphical elements
		Texture mapGeo, mapName, mapPolit;
		Sprite map;
		View mapView;
		vector<Button> sprites;
		vector<Polygon> polygons;

	public:

		// graphical informations
		Vector2f pos;
		Vector2f size;
		Vector2f rootSize;
		Vector2f imageSize;

	public:

		// Initialisation
		Map(RenderWindow *_pmWindow, Vector2i _pos, Vector2i _size, string _image, Vector2i _viewstart, MapType _type);

		// function, to enable interaction with the map
		void handleEvent(Event event);

		// draws the map to the screen
		void draw();

		// tests, whether the mouse is inside the map or not
		bool isMouseInside();

		// changes the map-image
		void setMapType(MapType type);

		// add a sprite/polygon to the map
		void addSprite(Button sprite);
		void addPolygon(Polygon poly) {
			polygons.push_back(poly);
		};

		// returns the mouse-position in map/mainWindow-coordinates
		Vector2f getMousePosOnMap();
		Vector2f getMousePosOnWindow();

};



#endif /* SRC_MAP_HPP_ */

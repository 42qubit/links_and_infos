/*
 * TerrainGenerator.hpp
 *
 *  Created on: 10.10.2017
 *      Author: Gregor Soennichsen
 */

#ifndef TERRAINGENERATOR_HPP
#define TERRAINGENERATOR_HPP

#include <vector>

#include "../constants.hpp"

using namespace std;



/**
 * @brief generateTerrainMap    Generates to a given point a terrain type.
 * @param rows                  Number of rows in the terrainmap.
 * @param columns               Number of columns in the terrainmap.
 *
 * This procedure uses a Perlin Noise implementation to generate a heightmap
 * that can be associated in an quite realistic way with terrain types. A two-
 * dimensional vector with these terrain types is returned to the caller.
 */
vector<vector<TERRAIN_TYPE>> generateTerrainMap(unsigned int rows, unsigned int columns);



#endif // TERRAINGENERATOR_HPP

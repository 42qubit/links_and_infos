/*
 * TerrainGenerator.cpp
 *
 *  Created on: 10.10.2017
 *      Author: Gregor Soennichsen
 */

#include <QVector2D>

#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <limits>

#include "../constants.hpp"

#include "TerrainGenerator.hpp"

using namespace std;



// start frequency, maximum frequency, start amplitude, persistence and wished octaves of the superposition process
// recommended: 0.01, 0.5, 3

const double F0        = 0.01;
const double A0        = 0.8;
const unsigned int OCT = 4;
const double PERSIS    = 0.7;


// These constants define how values of a heightmap shall be mapped to a climate.

const float BORDER_SNOW  =  0.9;
const float BORDER_ROCKS =  0.7;
const float BORDER_EARTH =  0.4;
const float BORDER_SAND  = -0.0;
const float BORDER_WATER = -0.4;


// All 256 integers are in the range [0..255] and can be used for hashing purposes.

const int PERM[256] = {

    151, 160, 137, 91, 90, 15, 131, 13,
    201, 95, 96, 53, 194, 233, 7, 225,
    140, 36, 103, 30, 69, 142, 8, 99,
    37, 240, 21, 10, 23, 190, 6, 148,
    247, 120, 234, 75, 0, 26, 197, 62,
    94,	252, 219, 203, 117, 35, 11, 32,
    57, 177, 33, 88, 237, 149, 56, 87,
    174, 20, 125, 136, 171, 168, 68, 175,
    74, 165, 71, 134, 139, 48, 27, 166,
    77, 146, 158, 231, 83, 111, 229, 122,
    60, 211, 133, 230, 220, 105, 92, 41,
    55, 46, 245, 40, 244, 102, 143, 54,
    65, 25, 63, 161, 1, 216, 80, 73,
    209, 76, 132, 187, 208, 89, 18, 169,
    200, 196, 135, 130, 116, 188, 159, 86,
    164, 100, 109, 198, 173, 186, 3, 64,
    52, 217, 226, 250, 124, 123, 5,	202,
    38, 147, 118, 126, 255, 82, 85, 212,
    207, 206, 59, 227, 47, 16, 58, 17,
    182, 189, 28, 42, 223, 183, 170, 213,
    119, 248, 152, 2, 44, 154, 163, 70,
    221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110,
    79, 113, 224, 232, 178,	185, 112, 104,
    218, 246, 97, 228, 251, 34, 242, 193,
    238, 210, 144, 12, 191, 179, 162, 241,
    81, 51, 145, 235, 249, 14, 239,	107,
    49, 192, 214, 31, 181, 199, 106, 157,
    184, 84, 204, 176, 115, 121, 50, 45,
    127, 4, 150, 254, 138, 236, 205, 93,
    222, 114, 67, 29, 24, 72, 243, 141,
    128, 195, 78, 66, 215, 61, 156,	180

};



/**
 * @brief getSeed                           Generates a random seed.
 *
 * Generates a random seed, being in fact the time in microseconds since 01.01.1970.
 */
unsigned int getSeed() {
    chrono::system_clock::time_point t = chrono::system_clock::now();
    return chrono::duration_cast<chrono::microseconds> (t.time_since_epoch()).count();
}



/**
 * @brief grad                        Computes a random gradient.
 * @param u                           X value of the point, which the gradient shall be assigned to.
 * @param v                           Y value of the point, which the gradient shall be assigned to.
 * @param seed                        A seed, that adds extra randomness.
 *
 * Returns a random gradient to every raster point (u,v). Hashing by a permutation table and a seed
 * are used to generate the pseudo-random values. The same seed gives the same values, so later maps
 * can be shared.
 */
QVector2D grad(unsigned int u, unsigned int v, unsigned int seed) {

    int hashValue = PERM[ (PERM[(u + seed) % 256] + v) % 256 ];
    int hashX     = hashValue / 16;
    int hashY     = hashValue % 16;

    double gx = 2 * hashX - 1;
    double gy = 2 * hashY - 1;
    return QVector2D(gx, gy);

}



/**
 * @brief noise                       Generates a noise value for a point (x,y).
 * @param x                           X-value of the point.
 * @param y                           Y-value of the point.
 * @param seed                        A seed that adds randomness to the gradients.
 *
 * This method generates a noise value for a point (x,y). 'noise' is one of the main components for
 * the Perlin Noise algorithm and delivers the basic values, that are later in the superposition
 * process and the heightmap generation used to create a good random heightmap. The returned values
 * is in the intervall [0..1].
 */
double noise(double x, double y, unsigned int seed) {

    // Determine Cell

    unsigned int px, py;
    px = static_cast<int> (floor(x));
    py = static_cast<int> (floor(y));

    // Determine Gradients

    QVector2D g00, g10, g01, g11;
    g00 = grad(px,   py  , seed);
    g10 = grad(px+1, py  , seed);
    g01 = grad(px,   py+1, seed);
    g11 = grad(px+1, py+1, seed);

    // Determine Displacements

    double x01, y01;
    x01 = x - px;
    y01 = y - py;

    // Compute Dot-Vector Products

    double w00, w10, w01, w11;
    w00 = g00.x() * (x01)  + g00.y() * (y01);
    w10 = g10.x() * (x01-1)+ g10.y() * (y01);
    w01 = g01.x() * (x01)  + g01.y() * (y01-1);
    w11 = g11.x() * (x01-1)+ g11.y() * (y01-1);

    // Interpolate

    double sx = x01*x01*x01 * (x01 * (x01 * 6 - 15) + 10); // manipulate weights, so that
    double sy = y01*y01*y01 * (y01 * (y01 * 6 - 15) + 10); // transitions look smoothier

    double w0 = (1 - sx) * w00 + sx * w10;
    double w1 = (1 - sx) * w01 + sx * w11;

    return (1 - sy) * w0 + sy * w1;

}



/**
 * @brief NOISE                 Generates to a given point a heightmap value.
 * @param x                     X-value of the point.
 * @param y                     Y-value of the point.
 * @param seed                  A seed that adds randomness to the value compution.
 *
 * 'NOISE' uses the superposition of several 'noise' values for one point to
 * create a heightmap value. This method implements for the most part the idea
 * of the 'Perlin Noise' algorithm.
 * It uses the global constants F0, A0, OCT and FMAX trough who the algorithm
 * can be configured.
 * F0 determines to which point on the fictive completed heightmap x (the
 * argument of 'noise') shall be mapped to. A0 determines how heavily 'noise(x)'
 * is weighted. PERSIS determines how fast the amplitude has to grow with every
 * noise value. And OCT decides how many noise values shall be included.
 *
 * Two informations for the superposition process have to be computed before start:
 * - a list of frequencies for every sum
 * - a list of amplitudes for every sum
 */
double NOISE(double x, double y, unsigned int seed) {

    // Generate the number of sums for the superposition process and all frequencies amd amplitudes

    vector<double> F;
    vector<double> A;

    double f=F0, a=A0;

    unsigned int n;
    for(n=0; n < OCT; n++) {

        F.push_back(f);
        A.push_back(a);
        f *= 2;
        a *= PERSIS;

    }

    // Compute Perlin Noise value by superposition of noise values

    double sum = 0.0;

    unsigned int i;
    for(i = 0; i < OCT; i++)
        sum += A[i] * noise(F[i] * x, F[i] * y, seed);

    return sum;
}



/**
 * @brief generateTerrainMap    Generates to a given point a terrain type.
 * @param rows                  Number of rows in the terrainmap.
 * @param columns               Number of columns in the terrainmap.
 *
 * This procedure uses the Perlin Noise implementation 'NOISE' to generate
 * a heightmap whose values can be associated with terrain types. Therefore,
 * first the heightmap is created. Afterwards the resulting values are mapped
 * to a [-1..1] intervall and interpreted as terrain types. A two-dimensional
 * vector with these terrain types is returned to the caller.
 */
vector<vector<TERRAIN_TYPE>> generateTerrainMap(unsigned int rows, unsigned int columns) {

    double min = numeric_limits<double>::max();
    double max = numeric_limits<double>::min();

    unsigned int seed = getSeed();

    // ****************** LOG ****************************
    cout << endl << "---- Generate Terrainmap ----" << endl;
    cout << "Size: x/y\t" << columns << "/" << rows << endl;
    cout << "Seed:\t"     << seed << endl;
    // ***************************************************

    double heightmap[rows][columns];

    unsigned int u, v;
    for(v=0; v < rows; v++) {
        for(u=0; u < columns; u++) {

            // Determine given point

            double x = (static_cast<double> (u)) + 0.5;
            double y = (static_cast<double> (v)) + 0.5;

            double w = NOISE(x, y, seed);

            if(w > max)
                max = w;
            if(w < min)
                min = w;

            heightmap[v][u] = w;
        }
    }

    // ****************** LOG ****************************
    cout << "Successfully generated heightmap" << endl;
    cout << "max/min:\t"  << max << "/" << min << endl;
    // ***************************************************



    // Normalize to [0..1] & Determine Terrain Type

    vector<vector<TERRAIN_TYPE>> terrainmap;

    for(v=0; v < rows; v++) {
        terrainmap.push_back(vector<TERRAIN_TYPE> (columns));
        for(u=0; u < columns; u++) {

            double t = heightmap[v][u];

            // normalize intervall from [min_w..max_w] to  [-1..+1]

            t = t - min;
            t = t / (max - min);
            t = t * 2;
            t = t - 1;

            // Determine Terrain Type

            TERRAIN_TYPE type;

            if(t >= BORDER_SNOW)
                type = SNOW;
            else if(BORDER_SNOW > t && t >= BORDER_ROCKS)
                type = ROCKS;
            else if(BORDER_ROCKS > t && t >= BORDER_EARTH)
                type = EARTH;
            else if(BORDER_EARTH > t && t >= BORDER_SAND)
                type = SAND;
            else if(BORDER_SAND > t && t >= BORDER_WATER)
                type = SHALLOW_WATER;
            else if(BORDER_WATER > t)
                type = DEEP_WATER;

            terrainmap[v][u] = type;
        }
    }

    // ****************** LOG ****************************
    cout << "Successfully normalized and interpreted heightmap" << endl;
    cout << "--------" << endl << endl;
    // ***************************************************

    return terrainmap;
}

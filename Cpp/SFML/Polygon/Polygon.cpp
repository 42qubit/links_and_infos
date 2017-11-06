/*
 * Polygon.cpp
 *
 *  Created on: 16.03.2017
 *      Author: Gregor
 */

#include <limits>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../snippets.hpp"
#include "Triangle.hpp"
#include "Polygon.hpp"

using namespace std;
using namespace sf;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void Polygon::triangulate() {

	vector<Vector2f> pointList;
	for(unsigned int i=0; i<points.size(); i++)
		pointList.push_back(points[i]);

// DEBUGGING
//	cout << "--------------------" << endl;
//	cout << "start" << endl;
//	cout << "PointList-Size: "	<< pointList.size()	<< endl;
//	cout << endl << "--------------------" << endl;

	int left, ear, right;
	int triangleIndex = 0;

	while(pointList.empty() == false) {

		triangles.push_back(Triangle());

		if(pointList.size() == 3) {

			left = 0; ear = 1; right = 2;

			Vector2f restT[] = { pointList[0], pointList[1], pointList[2] };
			triangles.at(triangleIndex).init(pmWindow, restT, color);
			pointList.clear();
		}

		else {

			ear = getEar(&pointList);
			if(ear == 0)
				left = pointList.size()-1;
			else
				left = ear-1;
			if(ear == (signed) pointList.size()-1)
				right = 0;
			else
				right = ear+1;

			Vector2f trianglePoints[] = { pointList[left], pointList[ear], pointList[right] };
			triangles.at(triangleIndex).init(pmWindow, trianglePoints, color);
			pointList.erase(pointList.begin() + ear);
		}

// DEBUGGING
//		cout << endl << "PointList-Size: "	<< pointList.size()	<< endl;
//		cout << "pointList: ";
//		for(int i=0; i<(signed) pointList.size(); i++)
//			cout << printVasI(pointList[i]) << " ";
//		cout << "\nEar:\t   "	<< ear << endl;
//		cout << "TriIndex:  " << triangleIndex << "\n";
//		cout << "Triangle:  "			<< printVasI(triangles.at(triangleIndex).getPoint(0)) << " " << printVasI(triangles.at(triangleIndex).getPoint(1)) << " " << printVasI(triangles.at(triangleIndex).getPoint(2)) << "\n\n";
//		for(int i=0; i<=triangleIndex; i++) {
//			for(int j=0; j<3; j++)
//				cout << printVasI(triangles.at(i).getPoint(j)) << " ";
//			cout << endl;
//		} cout << endl << "--------------------" << endl;

		triangleIndex++;
	}
};



float Polygon::sign(Vector2f p1, Vector2f p2, Vector2f p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
};
bool Polygon::isPointInTriangle(Vector2f v1, Vector2f v2, Vector2f v3, Vector2f pt) {
	bool b1, b2, b3;

	b1 = sign(pt, v1, v2) < 0.0f;
	b2 = sign(pt, v2, v3) < 0.0f;
	b3 = sign(pt, v3, v1) < 0.0f;

	return ((b1 == b2) && (b2 == b3));
};



int Polygon::getEar(vector<Vector2f> *pointList) {

	bool isKonkav[pointList->size()];
	bool hasPoint[pointList->size()];

	int minusCounter=0, plusCounter=0;

	Vector2f v1, v2, v3;
	unsigned int h, i, j;

	for(i=0; i<pointList->size(); i++) {

		if(i == 0)
			h = pointList->size()-1;
		else
			h = i-1;

		j = i+1;
		if(j == pointList->size())
			j = 0;

		// Without other points inside or not

		v1 = pointList->at(h);
		v2 = pointList->at(i);
		v3 = pointList->at(j);

		for(unsigned int k=0; k<pointList->size(); k++) {
			hasPoint[k] = true;
			if(k!=h && k!=i && k!=j)
				if(!isPointInTriangle(v1, v2, v3, pointList->at(k)))
					hasPoint[k] = false;
		}

		// Konkav or not

		v1 = pointList->at(h) - pointList->at(i);
		v2 = pointList->at(j) - pointList->at(i);

		if( (v1.x * v2.y - v1.y * v2.x) < 0) {
			minusCounter++;
			isKonkav[i] = false;
		}
		else {
			plusCounter++;
			isKonkav[i] = true;
		}
	}

	for(i=0; i<pointList->size(); i++) {

		if(minusCounter < plusCounter) {
			if(isKonkav[i])
				isKonkav[i] = false;
			else
				isKonkav[i] = true;
		}

		if(!isKonkav[i] && !hasPoint[i])
			return i;
	}

	return 0;
};



Polygon::Polygon(RenderWindow *_pmWindow, Color _color, void (*_command) (Event _event, Polygon *_polygon)) :
	pmWindow(_pmWindow),
	command(_command),
	size(0),
	minX(INT_MAX), minY(INT_MAX), maxX(INT_MIN), maxY(INT_MIN),
	color(_color),
	triangles(),
	points()
{};

void Polygon::setPoints(vector<Vector2f> _points) {
	this->size = (signed) _points.size();
	if(this->size < 4)
		throw "Size has to be bigger than 3";

	for(int i=0; i<size; i++)
		this->points.push_back(_points[i]);

	for(int i=0; i<size; i++) {

		if(this->minX > _points[i].x)
			this->minX = _points[i].x;

		if(this->minY > _points[i].y)
			this->minY = _points[i].y;

		if(this->maxX < _points[i].x)
			this->maxX = _points[i].x;

		if(this->maxY < _points[i].y)
			this->maxY = _points[i].y;
	}

	triangulate();
};



void Polygon::draw() {
    for(int i=0; i<getNumberOfTriangles(); i++)
    	triangles[i].draw();
};



void Polygon::handleEvent(Event _event) {
	if(_event.type == Event::MouseButtonReleased)
		command(_event, this);
};



bool Polygon::isPointInside(Vector2f _testPoint) {

	if(!FloatRect(minX, minY, maxX, maxY).contains(_testPoint))
		return false;

	int j;
	int intersections = 0;

	for(int i=0; i<size; i++) {
		j = i+1;
		if(j==size)
			j = 0;

		if( min(points[i].y, points[j].y) < _testPoint.y && _testPoint.y < max(points[i].y, points[j].y) ) {

			float crossX = computeCross(_testPoint.y, points[i], points[j]);

			if(_testPoint.x < crossX)
				intersections++;
		}
	}

	if(intersections%2 == 1)
		return true;
	else
		return false;
};



Vector2f Polygon::getPoint(int _index) {

	if(_index>=0 && _index<this->size)
		return this->points[_index];
	else
		throw "Wrong Index!";
};

int Polygon::getSize() {
	return this->size;
};

int Polygon::getNumberOfTriangles() {
	return this->size-2;
};



/*
 * Computes the x-Value of the cross of of y(x) = testPointY
 * and the line between p1 and p2
 */
float Polygon::computeCross(float _testPointY, Vector2f _p1, Vector2f _p2) {

	double m = (_p2.y - _p1.y) / (_p2.x - _p1.x);
	double b = _p1.y - m * _p1.x;
	double xS = (_testPointY - b) / m;
	return xS;
};



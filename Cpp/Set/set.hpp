/*
 * set.hpp
 *
 *  Created on: 03.02.2017
 *      Author: Gregor
 */

#include <iostream>

#ifndef SRC_SET_HPP_
#define SRC_SET_HPP_

class set {

friend std::ostream& operator<<(std::ostream& os, set& s);

private:

	int MAX_ELEMENTS = 255;
	int content[255];
	int position;

public:

	set();

	bool insert(int element);
	bool contains(int element);
	bool remove(int element);

	set operator-(set& other);
	set operator+(set& other);
	set operator*(set& other);
	set operator~();

};

#endif /* SRC_SET_HPP_ */

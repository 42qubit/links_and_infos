/*
 * set.cpp
 *
 *  Created on: 03.02.2017
 *      Author: Gregor
 */

#include <iostream>

#include "set.hpp"


set::set() : position(0) { }


bool set::insert(int element) {
	if(contains(element) || position==MAX_ELEMENTS || element < 0 || element >= MAX_ELEMENTS)
		return false;
	else {
		content[position] = element;
		position++;
		return true;
	}
}


bool set::contains(int element) {
	if(position == 0) return false;

	for(int i=0; i<position; i++)
		if(content[i] == element)
			return true;
	return false;
}



bool set::remove(int element) {
	if(position == 0) return false;

	for(int i=0; i<position; i++)
		if(content[i] == element) {
			if(position == 1)
                content[i] = 0;
			else {
				content[i] = content[position-1];
				content[position-1] = 0;
			}
			position--;
			return true;
		}
	return false;
}


set set::operator-(set &other) {
	set newSet;
	for(int i=0; i<MAX_ELEMENTS; i++)
		if(this->contains(i) && !other.contains(i))
			newSet.insert(i);
	return newSet;
}


set set::operator+(set &other) {
	set newSet;
	for(int i=0; i<MAX_ELEMENTS; i++)
		if(this->contains(i) || other.contains(i))
			newSet.insert(i);
	return newSet;
}


set set::operator*(set &other) {
	set newSet;
	for(int i=0; i<MAX_ELEMENTS; i++)
		if(this->contains(i) && other.contains(i))
			newSet.insert(i);
	return newSet;
}


set set::operator~() {
	set newSet;
	for(int i=0; i<MAX_ELEMENTS; i++)
		if(!contains(i))
			newSet.insert(i);
	return newSet;
}



std::ostream& operator<<(std::ostream& os, set& s) {
	os << "set( ";
	for(int i=0; i<s.position; i++) {
		os << s.content[i];
		if(i != s.position-1)
			os << ", ";
	}
	os << " )" ;
	return os;
}

#ifndef PLATONIC_H
#define PLATONIC_H

//#include<map>
#include<SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "vector.h"
#include "rspace.h"
#include "shape.h"
//#include ""

//####################################################################

class AxeSys : public Shape
{
	public:
		AxeSys(RSpace<3>& _RS);
		void updateEdges();
		void set_position(const Vect<3>& V);
		void rotate();
};

//####################################################################
//###################################################################

class Cube : public Shape
{
	public:
		Cube(RSpace<3>& _RS, sf::Color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
};

//###################################################################
//###################################################################

class Tetra : public Shape
{
	public:
		Tetra(RSpace<3>& _RS, sf::Color color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
};

//###################################################################
//###################################################################

#endif

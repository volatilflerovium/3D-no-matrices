#ifndef SHAPE_H
#define SHAPE_H
#include<SFML/Graphics.hpp>
#include "base.h"
#include "vector.h"
#include "noise.h"
#include "rspace.h"

using namespace std;

class Camera;

//####################################################################

class Shape : public Base
{
	private:
		int id=0;
		Vect<3> Correction;
		static int Shape_ID;
		Noise Ns[3];

	protected:
		double cosZ;
		Vect<3> Centroid;
		int numEdges;
		sf::Color Color;
		RSpace<3>& RS;
		Vect<3>* Vertex;
		sf::Vertex** Edges;
		bool hasChanged=true;
		static Camera* Cm;

	public:
		Shape(RSpace<3>& _RS, int nE, sf::Color color);
		virtual ~Shape();
		void draw();
		virtual void rotate()=0;
		virtual void updateEdges()=0;
		static void setCamera(Camera* cm);
		int getID();
		void move(double t); // this update the position of the underlying position vector of the local space
		virtual void set_position(const Vect<3>& V)=0;
		
		Vect<3> getCentroidW() const; // return the centroid in world coordinates
		double getCos()const;
};


inline void Shape::setCamera(Camera* cm){
	if(Cm==nullptr){
		Cm=cm;
	}
}

inline int Shape::getID(){
	return id;
}


inline void Shape::draw(){
	for(int i=0; i<numEdges; i++){
		Window->draw(Edges[i], 2, sf::Lines);
	}
}

inline Vect<3> Shape::getCentroidW() const{
	return RS.ltw(Centroid);
}

inline double Shape::getCos()const{
	return cosZ;
}

//####################################################################
//####################################################################
//####################################################################



#endif
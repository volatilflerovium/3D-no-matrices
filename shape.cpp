#include<SFML/Graphics.hpp>
#include "shape.h"
#include "vector.h"
#include "noise.h"

int Shape::Shape_ID=0;
Camera* Shape::Cm=nullptr;

Shape::~Shape(){
	for(int i=0; i<numEdges; i++){
		delete[] Edges[i];
	}
	delete[] Vertex;
	delete[] Edges;
}


Shape::Shape(RSpace<3>& _RS, int nE, sf::Color color)
	: RS(_RS), numEdges(nE), Correction({1.0, 1.0, 1.0}),Color(color){
	id=++Shape_ID;
	Ns[0]=Noise(10);
	Ns[1]=Noise(10);
	Ns[2]=Noise(10);
}

void Shape::move(double t){
	Vect<3> Speed({Correction.coordinate(0)*Ns[0].lerp(), 
						Correction.coordinate(1)*Ns[1].lerp(), 
						Correction.coordinate(2)*Ns[2].lerp()});
	Speed*=t;
	Vect<3> VT=RS.getPos()+Speed;
	for(int i=0; i<3; i++){
		
		if(abs(VT.coordinate(i))>3000.0){
			Correction+=-2.0*Correction.coordinate(i)*Vect<3>(i+1);
      	Speed+=-2.0* Speed.coordinate(i)*Vect<3>(i+1);
   	}
   }
   set_position(Speed);   
}   


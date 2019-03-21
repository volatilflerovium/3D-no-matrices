#include "camera.h"
#include "platonic.h"

/*
For practical terms we set the centroid as a pertinent point inside 
the respective polyhedra
*/


AxeSys::AxeSys(RSpace<3>& _RS)
	: Shape(_RS, 3, sf::Color::Black)
{
	Centroid=400*Vect<3>({1,1,1});
	Vertex=new Vect<3>[4];
	Vertex[0]=Vect<3>({0,0,0});
	Vertex[1]=850*Vect<3>(1);
	Vertex[2]=850*Vect<3>(2);
	Vertex[3]=850*Vect<3>(3);
	Edges=new sf::Vertex*[3];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
	cosZ=Cm->angCos(getCentroidW());
}

void AxeSys::updateEdges(){
	if(hasChanged || 1){
		for(int i=0; i<3; i++){
			Edges[i][0]=Cm->VtSFVx(RS.ltw(Vertex[0]));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(Vertex[i+1]));
		}

		Edges[0][0].color=sf::Color::Blue;
		Edges[0][1].color=sf::Color::Blue;

		Edges[1][0].color=sf::Color::Green;
		Edges[1][1].color=sf::Color::Green;

		Edges[2][0].color=sf::Color::Yellow;
		Edges[2][1].color=sf::Color::Yellow;
		hasChanged=false;
	}
}


void AxeSys::rotate(){
}

void AxeSys::set_position(const Vect<3>& V){
	RS.move(V);
	cosZ=Cm->angCos(getCentroidW());
	hasChanged=true;
}

//####################################################################
//####################################################################


Cube::Cube(RSpace<3>& _RS, sf::Color color)
	:Shape(_RS, 12, color)
{
	double sd=220.0;
	Centroid=Vect<3>({sd/2.0, sd/2.0, sd/2.0});
	Vertex=new Vect<3>[8];
	Vertex[0]=Vect<3>({0,0,0});
	Vertex[1]=Vect<3>({sd, 0, 0});
	Vertex[2]=Vect<3>({sd, sd, 0});
	Vertex[3]=Vect<3>({0, sd, 0});
	Vertex[4]=Vect<3>({0, 0, sd});
	Vertex[5]=Vect<3>({sd, 0, sd});
	Vertex[6]=Vect<3>({sd, sd, sd});
	Vertex[7]=Vect<3>({0, sd, sd});
	Edges=new sf::Vertex*[12];
	for(int i=0; i<12; i++){
		Edges[i]=new sf::Vertex[2];
	}
	cosZ=Cm->angCos(getCentroidW());
};


void Cube::updateEdges(){
	if(hasChanged){
		int j;
		for(int i=0; i<8; i++){
			j=4*(i/4)+(i+1)%4;
			Edges[i][0]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(Vertex[j]));
			
			Edges[i][0].color=Color;
			Edges[i][1].color=Color;
		}
		for(int i=8; i<numEdges; i++){
			j=4*(i/4)+(i+1)%4;
			Edges[i][0]=Edges[i-8][0];
			Edges[i][1]=Edges[i-4][0];
		}		
		hasChanged=false;
	}
}

void Cube::rotate(){
	static Rotation<3> Rt({1,1,1}, 2.0);
	Centroid=Rt(Centroid);
	cosZ=Cm->angCos(getCentroidW());
	
	for(int i=0; i<8; i++){
		Vertex[i]=Rt(Vertex[i]);
	}
	hasChanged=true;
}


void Cube::set_position(const Vect<3>& V){
	RS.move(V);
	cosZ=Cm->angCos(getCentroidW());
	hasChanged=true;
}


//####################################################################
//####################################################################


Tetra::Tetra(RSpace<3>& _RS, sf::Color color)
	: Shape(_RS, 6,color)
{
	Centroid=Vect<3>({0,0,0});
	Vertex=new Vect<3>[4];
	Vertex[0]=300*Vect<3>({sqrt(8/9.0), 0, -1/3.0});
	Vertex[1]=300*Vect<3>({-sqrt(2/9.0), sqrt(2/3.0), -1/3.0});
	Vertex[2]=300*Vect<3>({-sqrt(2/9.0), -sqrt(2/3.0), -1/3.0});
	Vertex[3]=300*Vect<3>({0, 0, 1}); 

	Edges=new sf::Vertex*[numEdges];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
	cosZ=Cm->angCos(getCentroidW());
}

void Tetra::updateEdges(){
	if(hasChanged){
		int j, k;
		for(int i=0; i<3; i++){
			j=(i+1)%3;
			k=2*i;
			Edges[k][0]=Cm->VtSFVx(RS.ltw(Vertex[3]));
			Edges[k][1]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			
			Edges[k][0].color=Color;
			Edges[k][1].color=Color;
			
			Edges[k+1][0]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			Edges[k+1][1]=Cm->VtSFVx(RS.ltw(Vertex[j]));
			
			Edges[k+1][0].color=Color;
			Edges[k+1][1].color=Color;
		}
		hasChanged=false;
	}
}

void Tetra::rotate(){
	static Rotation<3> Rt({0,0,1}, -2.0);
	Centroid=Rt(Centroid);
	cosZ=Cm->angCos(getCentroidW());
	
	for(int i=0; i<4; i++){
		Vertex[i]=Rt(Vertex[i]);
	}
	hasChanged=true;
}


void Tetra::set_position(const Vect<3>& V){
	RS.move(V);
	cosZ=Cm->angCos(getCentroidW());
	hasChanged=true;
}


//####################################################################
//####################################################################



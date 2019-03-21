/*********************************************************************
* camera class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include "camera.h"

using namespace std;

std::vector<Shape*> Camera::Shapes;
std::vector<Shape*> Camera::Shapes2;
std::map<Shape*, int> Camera::Shapes3;

Camera::Camera(RSpace<3>& _RS, double _fD, double ap)
	:RS(_RS), fD(_fD), app(ap)
{
	Ax=RS.getPos();
	Ax=Vect<3>({-1.0*Ax.coordinate(1), Ax.coordinate(0), 0});

	threshold=fD/sqrt(fD*fD+app*app);
	vertex[0]=Vect<3>({0,0,0});
	vertex[1]=Vect<3>(1);
	vertex[2]=Vect<3>(2);
	vertex[3]=Vect<3>(3);
}

void Camera::draw(){
	/*
	cout<<"========================"<<endl;
	for(int i=0; i<4; i++){
		cout<<"Camera global position: "<<vertex[i]<<" | "<<RS.ltw(vertex[i])<<endl;
	}
	/**/
}


void Camera::sorting2(Shape* shp, double cosZ, bool reset){
	static int i=0, j=1, k;
	static Shape* tmp_shp;
	if(reset){
		j=i;
		i=0;
	}
	else{
		if(cosZ>=threshold){
			k=Shapes3[shp];
			Shapes2[k]=Shapes2[i];
			Shapes2[i]=shp;
			Shapes3[Shapes2[k]]=k;
			Shapes3[Shapes2[i]]=i;
			
		}
	}
	
}


void Camera::takePicture(){
	sorting();
	for(int i=0; i<Shapes.size(); i++){
		if(Shapes[i]->getCos()>threshold){
			Shapes[i]->updateEdges();
			Shapes[i]->draw();
		}
		else{
			break;
		}
	}
}


sf::Vertex Camera::VtSFVx(const Vect<3>& V) const{
	static Vect<3> Cv;
	Cv=RS.wtl(V);
	double r=fD/Cv.coordinate(2);
	Cv*=r;
	return sf::Vertex(sf::Vector2f(RF->trans_x(ppWx(Cv.coordinate(0))), RF->trans_y(ppWx(Cv.coordinate(1)))));
}


void Camera::lRuD(int k){
	static Rotation<3> RT[4]={Rotation<3>({0,0,1}, 5.0), 
					Rotation<3>({0,0,1}, -5.0),
					Rotation<3>(Ax, 5.0),
					Rotation<3>(Ax, -5.0)};

	k-=71;
	if(hasChanged && k>1){
		RT[2]=Rotation<3>(Ax, 5.0);
		RT[3]=Rotation<3>(Ax, -5.0);
		hasChanged=false;
	}

	if(k<2){//left or right
		Ax=RT[k](Ax);
		hasChanged=true;
	}

	Vect<3> V(RS.getPos());
	RS.move(RT[k](RS.getPos())-V);	
}




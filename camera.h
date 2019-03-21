/*********************************************************************
* camera class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include<map>
#include<SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "vector.h"
#include "rspace.h"
#include "shape.h"


class Camera : public Base
{
	private:
		static std::vector<Shape*> Shapes;
		static std::vector<Shape*> Shapes2;
		static std::map<Shape*, int> Shapes3;

	public:
		static void registerShape(Shape* shape);
		void takePicture();

	private:
		RSpace<3>& RS;
		Vect<3> Ax;
		Vect<3> vertex[4];
		bool hasChanged=false;
		double fD;
		double app;
		double threshold=0;
		double ppWx(float d) const;
		double ppWy(float d) const;
		void sorting();


	public:
		Camera(RSpace<3>& _RS, double _fD, double ap);		
		Vect<3> transf(const Vect<3>& V);
		void updateAngle(int i, double ang);
		void draw();
		sf::Vertex VtSFVx(const Vect<3>& V) const;
		void lRuD(int k);
		double angCos(const Vect<3>& V) const; // V is in world coordinates		
		void sorting2(Shape* shp, double cosZ, bool reset=false);
};


inline void Camera::registerShape(Shape* shape){
	Shapes.push_back(shape);
	Shapes3[shape]=Shapes2.size();
	Shapes2.push_back(shape);
}


inline void Camera::sorting(){
	std::sort(Shapes.begin(), Shapes.end(), [](Shape* s1, Shape* s2)->float{
		return s1->getCos()>s2->getCos();
	});
}


inline Vect<3> Camera::transf(const Vect<3>& Vx){
	Vect<3> Cv=RS.wtl(Vx);
	double r=fD/Cv.coordinate(2);
	Cv*=r;
	return Cv;
}


inline void Camera::updateAngle(int i, double ang){
	RS.updateTrans(i, ang);
}


inline double Camera::ppWx(float d) const {
	return d*WINDOW_WIDTH/(2.0*app);
}


inline double Camera::ppWy(float d) const {
	return d*WINDOW_HEIGHT/(2.0*app);
}

// V is in world coordinates
inline double Camera::angCos(const Vect<3>& V) const{
	return ang_cos(RS.wtl(V), vertex[3]);

}




#endif
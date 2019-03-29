/*********************************************************************
* camera class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef CAMERA_H
#define CAMERA_H
#include<memory>
#include<SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "vector.h"
#include "rspace.h"
#include "shape.h"
#include "fast_list.h"

using namespace std;

class Camera : public Base
{
	private:
		relLink fastList;
		static void doSomething(Node*, int n);

	public:
		void registerShape(Shape* shape);
		void takePicture();

	private:
		RSpace<3>& RS;
		std::shared_ptr<RSpace<3>> __RS;
		Vect<3> Ax;
		Vect<3> vertex[4];
		bool hasChanged=false;
		double fD;
		double app;
		double threshold=0;
		double ppWx(float d) const;
		double ppWy(float d) const;
		

	public:
		Camera(std::shared_ptr<RSpace<3>> _RS, double _fD, double ap);		
		Vect<3> transf(const Vect<3>& V);
		void updateAngle(int i, double ang);
		void draw();
		sf::Vertex VtSFVx(const Vect<3>& V) const;
		void lRuD(int k);
		void angCos(Shape* shp); // V is in world coordinates		
		void updateVertex(sf::Vertex& V, const Vect<3>& W);
		double angCos(const Vect<3>& V) const; // V is in world coordinates		
};


inline void Camera::registerShape(Shape* shape){
//	Shapes.push_back(shape);
	fastList.insert(shape, ang_cos(RS.wtl(shape->getCentroidW()), vertex[3])>=threshold);
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


inline void Camera::angCos(Shape* shp){	
	//bool a=ang_cos(RS.wtl(shp->getCentroidW()), vertex[3])>=threshold;
	bool a=fast_cos(RS.wtl(shp->getCentroidW()))>=threshold;
	fastList.swap(shp, a);
}

// V is in world coordinates
inline double Camera::angCos(const Vect<3>& V) const{
	return ang_cos(RS.wtl(V), vertex[3]);
}




#endif
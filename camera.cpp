/*********************************************************************
* camera class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include<thread>
#include "camera.h"

using namespace std;


Camera::Camera(std::shared_ptr<RSpace<3>> _RS, double _fD, double ap)
	:__RS(_RS), RS(*_RS), fD(_fD), app(ap)
{
	Ax=RS.getPos();
	Ax=Vect<3>({-1.0*Ax.coordinate(1), Ax.coordinate(0), 0});

	threshold=fD/sqrt(fD*fD+app*app);

	fastList.setThreshold(fD/sqrt(fD*fD+app*app));

	vertex[0]=Vect<3>({0,0,0});
	vertex[1]=Vect<3>(1);
	vertex[2]=Vect<3>(2);
	vertex[3]=Vect<3>(3);
}

void Camera::draw(){
}

Node* tt(Node* t, int n){
	int i=0;
	while(i<n && t){
		t=t->next;
		i++;	
	}
	return t;
}

void Camera::doSomething(Node* tail, int n){
	Node* tmp=tt(tail, n);
	int i=0;
	while(tmp){
		tmp->shape->updateEdges();
		//tmp->shape->draw();
		tmp=tt(tmp, 3);
		i++;
	}
	/**/
}

void Camera::takePicture(){
	static double total=0;
	static double tt=1.0;
	
	auto start = chrono::high_resolution_clock::now();

	Node* tmp=fastList.getTail();	
	/*
	std::thread t1(Camera::doSomething, tmp, 0);
	std::thread t2(Camera::doSomething, tmp, 1);
	std::thread t3(Camera::doSomething, tmp, 2);
	t1.join();
	t2.join();
	t3.join();
	/**/
	fastList.getTotal();

	while(tmp){
		tmp->shape->updateEdges();
		tmp->shape->draw();		
		tmp=tmp->next;
	}		

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	
	cout<<"Total Elapsed time: "<<microseconds/1000000.0<<endl;
	total+=microseconds/1000000.0;
	cout<<tt<<"============================= "<<total/tt<<endl;
	tt+=1.0;
}

void Camera::updateVertex(sf::Vertex& V, const Vect<3>& W){
	
	static Vect<3> Cv;
	Cv=RS.wtl(W);
	/*
	static double r;
	r=fD/Cv.coordinate(2);
	Cv*=r;
	/**/
	Cv*=fD/Cv.coordinate(2);
	V.position.x=RF->trans_x(ppWx(Cv.coordinate(0)));
	V.position.y=RF->trans_y(ppWy(Cv.coordinate(1)));

}

Vect<3> Camera::transf(const Vect<3>& Vx){
	static Vect<3> Cv;
	static double r;
	Cv=RS.wtl(Vx);
	r=fD/Cv.coordinate(2);
	Cv*=r;
	return Cv;
}

sf::Vertex Camera::VtSFVx(const Vect<3>& V) const{
	static Vect<3> Cv;
	Cv=RS.wtl(V);
	//double r=fD/Cv.coordinate(2);
	//Cv*=r;
	Cv*=fD/Cv.coordinate(2);
	
	return sf::Vertex(sf::Vector2f(RF->trans_x(ppWx(Cv.coordinate(0))), RF->trans_y(ppWx(Cv.coordinate(1)))));
}

//*
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




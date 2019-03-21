#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<ctime>
#include <algorithm>
#include <functional>
//#include<thread>
#include<SFML/Graphics.hpp>

#include "helper.h"
#include "base.h"
#include "framerate.h"
#include "noise.h"
#include "rspace.h"
#include "vector.h"
#include "shape.h"
#include "camera.h"
#include "platonic.h"

using namespace std;

//###################################################################
//###################################################################

int main(){
	srand(time(0));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window",sf::Style::Default, settings);
	ReferenceFrame RF(400, 400);
	Base::set_window(&window);
	Base::set_rf(&RF);

	RSpace<3> Global({0, 0, 0}, {0, 0, 0});
	
	RSpace<3> Crf(Global.spawn({3200, 3200, 3200}, {-50, 105, 65}));		
	Camera CameraView(Crf, 1.0, 0.8);	

	Shape::setCamera(&CameraView);
	
	AxeSys XYZ(Global);
	Cube Cub(Global, sf::Color(0, 102, 153));

	RSpace<3> TetraSp(Global.spawn({0, 0, 800}, {0, 0, 0}));		
	Tetra Tet(TetraSp, sf::Color(153, 102, 255));
	Rotation<3> mR({0,1,0}, 2.0);
	Vect<3> movTet({0,0, 800});
	
	Camera::registerShape(&XYZ);
	Camera::registerShape(&Cub);
	Camera::registerShape(&Tet);

	const int NT=20;

	Shape* Shps[NT];
	RSpace<3>* RS_Tet[NT];
	
	for(int i=0; i<NT; i++){
		RS_Tet[i]=new RSpace<3>(Global.spawn({20+5.0*i, 50+4.0*i, 250+8.0*i}, {0, 0, 0}));
		Shps[i]=new Tetra(*(RS_Tet[i]), sf::Color(rand()%256, rand()%256, rand()%256));
		Camera::registerShape(Shps[i]);
	}
	
	CameraView.takePicture();

	Vect<3> vtmp;

	bool a=false;
	FrameRate Framerate(50);

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
			{
				window.close();
			}
			else if(a && event.type == sf::Event::KeyPressed){
				// Yes, this bit needs tidy up!
				if(event.key.code == sf::Keyboard::Q){
					// X up
					CameraView.updateAngle(0, -5.0);
					a=true;
				}
				else if(event.key.code == sf::Keyboard::W){
					// X down
					CameraView.updateAngle(0, 5.0);
					a=true;
				}
				else if(event.key.code == sf::Keyboard::S){
					// Y up
					CameraView.updateAngle(1, -5.0);
					a=true;	
				}
				else if(event.key.code == sf::Keyboard::A){
					// Y down
					CameraView.updateAngle(1, 5.0);
					a=true;
				}
				else if(event.key.code == sf::Keyboard::X){
					//Z up
					CameraView.updateAngle(2, -5.0);
					a=true;
				}
				else if(event.key.code == sf::Keyboard::Z){
					CameraView.updateAngle(2, 5.0);
					a=true;
				}
				else if(event.key.code>70 && event.key.code<75){
					CameraView.lRuD(event.key.code);
					a=true;
				}
			}
		}

		if(Framerate()>=0){
			Framerate.reset();

			window.clear(sf::Color::White);
		  
			//################################################################
			//draw things here ###############################################

			vtmp=mR(movTet);
			Tet.set_position(vtmp-movTet);
			movTet=vtmp;
			
			Cub.rotate();
			Tet.rotate();
			for(int i=0; i<NT; i++){
				Shps[i]->rotate();
				Shps[i]->move(2.0);
			}

			CameraView.takePicture();
			a=true;

			// END of drawing ###############################################
			//###############################################################

			//t=0;
			Framerate.reset();
		}
		window.display();
	}
	for(int i=0; i<NT; i++){
		delete Shps[i];
		delete RS_Tet[i];
	}

	return 0;
}



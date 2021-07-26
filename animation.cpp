#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <chrono>

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

//####################################################################
//####################################################################
//####################################################################

int main()
{
	Shape::registerShapeMaker('T', Tetra::mkTetra);
	Shape::registerShapeMaker('C', Cube::mkCube);
	Shape::registerShapeMaker('O', Octahedron::mkOcta);
	Shape::registerShapeMaker('D', Dodecahedron::mkDode);
	const int NP=4;
	char shp[NP]={'T', 'C', 'O', 'D'};	
	
	srand(time(0));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	//cout<<"Display settings: "<< sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height<<endl;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window",sf::Style::Default, settings);
	ReferenceFrame RF(400, 400);
	Base::set_window(&window);
	Base::set_rf(&RF);

	std::shared_ptr<RSpace<3>> Global(RSpace<3>::maker({0, 0, 0}, {0, 0, 0}));

	Camera CameraView(Global->spawn({6080, 0, 0}, {0, 90, 0}), 1.0, 0.8);	
	Shape::setCamera(&CameraView);
	
	AxeSys XYZ(Global);
	Cube Cub(Global, sf::Color(0, 102, 153));

	Tetra Tet(Global->spawn({0, 0, 800}, {0, 0, 0}), sf::Color(153, 102, 255));
	Rotation<3> mR({0,1,0}, 2.0);
	Vect<3> movTet({0,0, 800});

	Octahedron Octa(Global->spawn({0, 800, 0}, {0, 0, 0}), sf::Color(204, 0, 102));

	Dodecahedron Dode(Global->spawn({0, 0, 0}, {0, 0, 0}), sf::Color(104, 90, 30));

	XYZ.draw();
	
	Tesseract C4(Global->spawn({800, 800, 0}, {0, 0, 0}), sf::Color(104, 90, 202));

	const int Nt=400;
	Shape* Shps[Nt];
	for(int i=0; i<Nt; i++){
		Shps[i]=Shape::Mk_Poliedrom(shp[i%NP], Global->spawn({20, 50, 250}, {0, 0, 0}), sf::Color(rand()%256, rand()%256, rand()%256));		
	}

	Vect<3> vtmp;

	static double total=0;
	static double tt=1.0;

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
			else if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Q){
					// X up
					CameraView.updateAngle(0, -5.0);
				}
				else if(event.key.code == sf::Keyboard::W){
					// X down
					CameraView.updateAngle(0, 5.0);
				}
				else if(event.key.code == sf::Keyboard::S){
					// Y up
					CameraView.updateAngle(1, -5.0);
				}
				else if(event.key.code == sf::Keyboard::A){
					// Y down
					CameraView.updateAngle(1, 5.0);
				}
				else if(event.key.code == sf::Keyboard::X){
					//Z up
					CameraView.updateAngle(2, -5.0);
				}
				else if(event.key.code == sf::Keyboard::Z){
					//Z down
					CameraView.updateAngle(2, 5.0);
				}
				else if(event.key.code>70 && event.key.code<75){
					CameraView.lRuD(event.key.code);
				}
			}
		}

		if(Framerate()>=0){
			Framerate.reset();

			window.clear(sf::Color::White);
		  
			//################################################################
			//draw things here ###############################################

			auto start = chrono::high_resolution_clock::now();

			C4.rotate();
			C4.draw();
			XYZ.draw();
	
			int rrr=0;
			for(int i=0; i<Nt; i++){
				Shps[i]->rotate();
				Shps[i]->move(2.0);
				Shps[i]->draw();
				if(Shps[i]->display()){
					rrr++;
				}
			}

			a=true;

			// END of drawing ###############################################
			//###############################################################
			//###############################################################
			//t=0;
			Framerate.reset();
		}

		window.display();
		
	}

	for(int i=0; i<Nt; i++){
		//cout<<Shps[i]<<endl;
		delete Shps[i];
	}

	return 0;
}



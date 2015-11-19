#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <string>
#include <sstream>
#include "Utils.h"

using namespace std;

int Utils::getSizeBullet(){
	return 5;
}

int Utils::getVelocidadeBullet(){
	return 15;
}

int Utils::getTamanhoDaNave(){
	return 25;
}

int Utils::getMaxVida(){
	return 100;
}

int Utils::getMovimento(){
	return 5;
}

int Utils::getLarguraTela(){
	return 800;
}

int Utils::getAlturaTela(){
	return 600;
}

int Utils::getAsteroideSize(){
	return 10;
}

int Utils::getPosicaoAst(int px){
	int newpx;
	newpx = (rand()%602-2)+2;
	while(px == newpx){	
		newpx = (rand()%602-2)+2;
	}
	return newpx;

	/*int newpx = (rand()%(Utils::getLarguraTela()-1))+1;
	while(px == newpx){
		newpx = (rand()%(Utils::getLarguraTela()-1))+1;
	}*/
}

int Utils::getVelocidadeAsteroide(){
	return 2;
}

int Utils::getFrequenciaInimigo(){
	return 30;
}

int Utils::getMaximoInimigo(){
	return 10;
}
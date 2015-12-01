#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
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
	return 7;
}

int Utils::getLarguraTela(){
	return 800;
}

int Utils::getAlturaTela(){
	return 640;
}

int Utils::getAlturaInfo(){
	return 40;
}

int Utils::getStartAltura(){
	//Menor que o tamanho da linha que tem informações
	return Utils::getAlturaTela()-Utils::getAlturaInfo();
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

string Utils::getNumberToString(int number){
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	return Result;
}

int Utils::getStringToNumber(string str){
	int Result;          //number which will contain the result
	istringstream convert(str); // stringstream used for the conversion constructed with the contents of 'Text' 
                             // ie: the stream will start containing the characters of 'Text'
	if ( !(convert >> Result) ){
		Result = 0;
	} //give the value to 'Result' using the characters in the stream
	return Result;
}

ALLEGRO_FONT *Utils::getFonte(){
	ALLEGRO_FONT *fonte = al_load_ttf_font("fonte/ARCADE.TTF", 50, 0);
	return fonte;
}


ALLEGRO_FONT *Utils::getFonteAlvo(){
	ALLEGRO_FONT *fonte = al_load_ttf_font("fonte/Timeless.ttf",15,0);
	return fonte;
}

int Utils::getCountChar(string str, string busca){
	int count = 0;
	for (int i = 0; i < str.size(); i++){
		if (str[i] == busca[0]){
			count++;	
		} 
	}
  return count;
}

char *Utils::getStringToChar(string str){
	char *a=new char[str.size()+1];
	a[str.size()]=0;
	memcpy(a,str.c_str(),str.size());
	return a;
}
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

class Utils {
	public:
		static int getSizeBullet();

		static int getVelocidadeBullet();

		static int getTamanhoDaNave();

		static int getMaxVida();

		static int getMovimento();

		static int getLarguraTela();

		static int getAlturaTela();

		static int getAlturaInfo();

		static int getStartAltura();

		static int getAsteroideSize();

		static int getPosicaoAst(int px);

		static int getVelocidadeAsteroide();

		static int getFrequenciaInimigo();

		static int getMaximoInimigo();

		static string getNumberToString(int number);

		static int getStringToNumber(string str);

		static ALLEGRO_FONT *getFonte();

		static ALLEGRO_FONT *getFonteAlvo();

		static int getCountChar(string str, string i);

		static char *getStringToChar(string str);

		//static char manipular_entrada(ALLEGRO_EVENT evento);
};

#endif


#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <iostream>
#include <allegro5/allegro.h>
#include <string>
#include <sstream>

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

		static int getAsteroideSize();

		static int getPosicaoAst(int px);

		static int getVelocidadeAsteroide();

		static int getFrequenciaInimigo();

		static int getMaximoInimigo();

};

#endif


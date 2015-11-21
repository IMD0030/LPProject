#ifndef RANKINGLIST_H_INCLUDED
#define RANKINGLIST_H_INCLUDED
#include <string>
#include <typeinfo>
#include <iostream>
#include "Ranking.h"

using namespace std;



class NoDoRanking {
public:
	Ranking *valor;
	NoDoRanking *prox;
};

class RankingList{
public:
    NoDoRanking *inicio;
    //float tam_x, tam_y;

    RankingList();

	void Adicionar(Ranking *r);

	string RetornarLista();

	void AdicionarSeq(Ranking *r);

	//void InserirNaOrdem(Ranking *r);

};

#endif
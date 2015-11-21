#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Ranking.h"
#include "RankingList.h"

Ranking::Ranking(std::string n, int k){
	this->nome = n;
	this-> kills = k;
}

void Ranking::Novo(RankingList *R, std::string nome, int k){
	Ranking * rk = new Ranking();
	rk->nome = nome;
	rk->kills = k;
	R->Adicionar(rk);
}
#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class RankingList;


class Ranking{
    public:
		std::string nome;
		int kills;
		
		Ranking(std::string n = "", int k = 0);

		void Novo(RankingList *R, std::string nome, int k);
};

#endif
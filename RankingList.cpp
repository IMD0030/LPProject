#include <string>
#include <typeinfo>
#include <iostream>
#include "Ranking.h"
#include "RankingList.h"
#include "Utils.h"

using namespace std;

RankingList::RankingList(){
	this->inicio = NULL;
}

void RankingList::Adicionar(Ranking *r){
	NoDoRanking *novo = new NoDoRanking();
	novo->valor = r;
	novo->prox = NULL;
	if(this->inicio == NULL){
		this->inicio=novo;
	}
	else{
		NoDoRanking *atual;
		atual=this->inicio;
		while(atual->prox !=NULL){
			atual=atual->prox;
		}
		atual->prox=novo;
	}
}

string RankingList::RetornarLista(){
	NoDoRanking *aux;
	string str;
	cout<<"Chamou a lista"<<endl;
	if(this->inicio == NULL){
		str.append("Lista Vazia");
		return str;
	}
	else{
		aux=this->inicio;
		cout<<"Entrou no else"<<endl;
		while(aux !=NULL){
			cout<<"Tou no while"<<endl;
			cout<<"Imprimindo os nomes " << aux->valor->nome<<endl;
			str.append(aux->valor->nome);
			str.append("|");
			str.append(Utils::getNumberToString(aux->valor->kills));
			//str = str+aux->valor->nome + ;
			str.append(";");
			if(aux->prox != NULL){
				aux=aux->prox;
			}
			else{
				break;
			}
						
		}
	}
	cout << "Todos os nomes sao: " << str << endl;
	return str;
}

void RankingList::AdicionarSeq(Ranking *r){
	NoDoRanking *novo = new NoDoRanking();
	novo->valor = r;
	novo->prox = NULL;
	if(this->inicio == NULL || novo->valor->kills >= this->inicio->valor->kills){
		novo->prox = this->inicio;
		this->inicio=novo;
	}
	else{
		NoDoRanking *current, *old;
		current = this->inicio->prox;
		old = this->inicio;
		while(current!=NULL){
			cout << "!!!!!!!!!!!!!!!!!!!!!!!!! Entrando no while !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
			cout << "O nome do Current eh: " << current->valor->nome << " A pontuaçao eh " << current->valor->kills << endl;
			cout << "O nome do Old eh: " << old->valor->nome << " A pontuaçao eh " << old->valor->kills << endl;
			if(/*current->prox == NULL || */novo->valor->kills >= current->valor->kills){
				novo->prox = current;
				old->prox = novo;
				cout << "Adicionei e agora? " << endl;
				break;
			}
			else if(current->prox == NULL){
				current->prox = novo;
				break;
			}
			old=current;
			current=current->prox;
		}
	}
}

void RankingList::LimparLista() {
    if(this->inicio != NULL)
    {
    	NoDoRanking *aux = this->inicio;
        NoDoRanking *aux_prox = NULL;
        while(aux != NULL)
        {
        	aux_prox = aux->prox;
            delete(aux->valor);
            delete(aux);
            aux = aux_prox;
		}
        delete(aux_prox);
        delete(aux);
    }
	this->inicio=NULL;
}
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
			if(current->prox == NULL || novo->valor->kills >= current->valor->kills){
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


/*void insertion_sort (int arr[], int length){
	 	int j, temp;
		
	for (int i = 0; i < length; i++){
		j = i;
		
		while (j > 0 && arr[j] < arr[j-1]){
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  }
		}
}*/

/*void RankingList::Ordernar(RankingList *pList){
	NoDoRanking *aux, *temp = new NoDoRanking();
	aux = pList->inicio;
	while(aux != NULL){
		while(aux->valor->kills < aux->prox->valor->kills){
			temp = aux;
			aux = aux->prox;
			aux-
		}
	}



    // head is the first element of resulting sorted list
    /*NoDoRanking *head = NULL;

    while(pList != NULL) {

        struct LIST * current = pList;
        pList = pList->pNext;
        if(head == NULL || current->iValue < head->iValue) {
            // insert into the head of the sorted list
            // or as the first element into an empty sorted list
            current->pNext = head;
            head = current;
        } else {
            // insert current element into proper position in non-empty sorted list
            struct LIST * p = head;
            while(p != NULL) {
                if(p->pNext == NULL || // last element of the sorted list
                   current->iValue < p->pNext->iValue) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    current->pNext = p->pNext;
                    p->pNext = current;
                    break; // done
                }
                p = p->pNext;
            }
        }
    }
    return head;
}

	
}*/


void RankingList::AdicionarOrdenar(){
	NoDoRanking *current = this->inicio;
	NoDoRanking *old = NULL;
	//Item *head = lista;
	NoDoRanking *next = current->prox;
	bool troca = true;

	while(troca) {
		troca = false;
		current = this->inicio;
		old = NULL;
		next = current->prox;
		while (next != NULL) {
			cout << "Valor do current eh " <<current->valor->kills << " e do next eh " << next->valor->kills;
			if (current->valor->kills < next->valor->kills) {
				troca = true;
				if (old == NULL) {
					current->prox = next->prox;
					next->prox = current;

					this->inicio = next;
					
				} else {// if (next->prox == NULL) {

					old->prox = next;
					current->prox = next->prox;
					next->prox = current;
					
				}

				// avança
				old = next;
				// current já aponta pra o local certo
				next = current->prox;

			} else {
				// somenta avança
				old = current;
				current = current->prox;
				next = next->prox;			
			}

			//mostra(head);

		}
	}
}

/*
novo->prox = current;
				old->prox = novo;
				cout << "Adicionei e agora? " << endl;
				break;


 while(p != NULL) {
                if(p->pNext == NULL || current->iValue < p->pNext->iValue) // middle of the list
                {
                    // insert into middle of the sorted list or as the last element
                    current->pNext = p->pNext;
                    p->pNext = current;
                    break; // done
                }
                p = p->pNext;

	int j, temp;
		
	for (int i = 0; i < length; i++){
		j = i;
		
		while (j > 0 && arr[j] < arr[j-1]){
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  }
		}*/

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
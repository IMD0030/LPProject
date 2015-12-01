#include <iostream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <typeinfo>
#include "GameObject.h"
#include "GameObjectList.h"
#include <math.h>
#include "Nave.h"


using namespace std;


    GameObjectList::GameObjectList() {
        this->inicio = NULL;
    }


	void GameObjectList::Adicionar(GameObject *item) {
        NoDaLista * novo = new NoDaLista();
        novo->valor = item;
        novo->prox = NULL;

        if(this->inicio == NULL){
            this->inicio = novo;
        }
        else {
            NoDaLista *atual;
            atual = this->inicio;
            while(atual->prox !=NULL){
                atual=atual->prox;
            }
            atual->prox = novo;
        }
    }

    void GameObjectList::RemoverSeq(GameObject *item) {
        NoDaLista *aux;
        if (this->inicio == NULL ) {
            //cout << "Lista vazia" << endl;
        }
        else {
            aux = inicio->prox;
            delete(item);
        }
    }

    void GameObjectList::LimparLista() {
        if(this->inicio != NULL){
            NoDaLista *aux = this->inicio;
            NoDaLista *aux_prox = NULL;
            while(aux != NULL){
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

    void GameObjectList::Remover(GameObject *item){
        if(this->inicio == NULL) {
            //cout << "Lista vazia" << endl;
        }
        else {
            //cout << "removendo objeto" << endl;
            NoDaLista *old = NULL;
            NoDaLista *curr = this->inicio;
            while (curr != NULL) {
                //cout << "Entrou no while da remocao" << endl;
                if (curr->valor == item) {
                    //cout << "Compara se o valor currente é o que eu quero" << endl;
                    if(old != NULL) {
                        //cout << "verificou o antigo não tem ninguem e mandou pra o proximo" << endl;
                        old->prox = curr->prox;
                    }
                    else {
                        //cout << "viu que o antigo tem alguem" << endl;
                        this->inicio = curr->prox;
                    }
                    //cout << "Apagando a galera" << endl;
                    delete(curr);
                    delete(item);
                    //cout << "Galera apagada" << endl;
                    return;
                }
                //cout << "Atribuindo o novo old" << endl;
                old = curr;
                curr = curr->prox;
                //cout << "removendo objeto final" << endl;
            }       
        }
    }

    void GameObjectList::Render(){
        NoDaLista *aux = inicio;
        while (aux != NULL){
            aux->valor->Render();
            aux = aux->prox;
        }
    }

    void GameObjectList::Update(){
        NoDaLista *aux = inicio;
        while (aux != NULL){
            aux->valor->Update();
            if(aux->valor->Devo_Morrer()){
                this->Remover(aux->valor);
            }
            
            aux = aux->prox;
        }
    }

    //Alterar impacto para procurar pelo primeiro objeto de cada Lista
    //Se for ele que foi atigindo, remover, se não, não remover!
    void GameObjectList::Impacto(GameObjectList *Lista){
        NoDaLista *auxUm = this->inicio;
        NoDaLista *auxDois = Lista->inicio;
        while(auxUm != NULL){
            //std::cout << "A lista de tiro não eh null" << std::endl;  
            while(auxDois != NULL){
                //std::cout << "A lista de meteoro não eh null" << std::endl;
                if(this->Distancia(auxDois->valor->posicao_x, auxUm->valor->posicao_x, 
                                    auxDois->valor->posicao_y, auxUm->valor->posicao_y, 
                                    auxDois->valor->size, auxUm->valor->size)){
                    //std::cout << "Existem elementos para serem destruidos" << std::endl;
                    NoDaLista *aux_prox = auxDois->prox;
                    if(aux_prox == NULL) {
                        //cout << "Esse elemento é o ultimo" << endl << endl << endl;
                    }
                    //cout << "removendo um asteroid"<<endl<<endl<<endl;
                    Lista->Remover(auxDois->valor);
                    auxDois = aux_prox;
                    //cout << "Valor de auxDois depois de removido: ";
                    //cout << "quantidade de asteroides: " << Lista->ObjectCont() << endl;
                }
                //cout << "Atribuindo um novo valor" << endl;
                if(auxDois != NULL){
                    //cout<<"Valor de proximo eh null" <<endl;
                    auxDois=auxDois->prox;
                } 
            }
            //cout << "A vericando se a bala é nulla" << endl;
            if(auxUm !=NULL) {
                //cout << "Atribuindo a bala para a proxima" << endl;
                auxUm=auxUm->prox;    
            }
            //cout << "quantidade de balas: " << this->ObjectCont() << endl;            
        }
    }

    bool GameObjectList::ImpactoFirstElement(Nave *n, GameObjectList *Lista){
        NoDaLista *auxUm = this->inicio;
        NoDaLista *auxDois = Lista->inicio;
        bool impacto = false;
        while(auxUm != NULL){
            if(auxDois != NULL){
                if(this->Distancia(auxDois->valor->posicao_x, auxUm->valor->posicao_x, 
                                    auxDois->valor->posicao_y, auxUm->valor->posicao_y, 
                                    auxDois->valor->size, auxUm->valor->size)){
                    NoDaLista *aux_prox = auxDois->prox;
                    Lista->Remover(auxDois->valor);
                    auxDois = aux_prox;
                    aux_prox = auxUm->prox;
                    this->Remover(auxUm->valor);
                    auxUm = aux_prox;
                    n->kills++;
                    impacto = true; 
                }
                else{
                    auxUm = auxUm->prox;
                }
            }
            else{
                auxUm = auxUm->prox;
            }
        }
        return impacto;
        //cout << "Quantidade de kill da nave eh de: " << n->kills << endl;
    }


    int GameObjectList::ObjectCont(){
        NoDaLista *aux = this->inicio;
        int qtd = 0;
        while(aux != NULL){
            aux = aux->prox;
            qtd++;
        }
        return qtd;
    }

    bool GameObjectList::Distancia(int pxdois, int pxum, int pydois, int pyum, float sizedois, float sizeum){
        if( sqrt(((pxdois-pxum)*(pxdois-pxum)) + ((pydois-pyum)*(pydois-pyum))) <= (sizeum+sizedois) ){
            return true;
        }else{
            return false;
        }
    }

    int GameObjectList::MouseDown(float x, float y){
        NoDaLista *aux = inicio;    
        while (aux != NULL)
        {
            if(aux->valor->MouseDown(x,y)) {
                return 1;
                break;
            }
            aux = aux->prox;
        }
        return 0;
    }

    int GameObjectList::idLastObject(){
        NoDaLista *aux = this->inicio;
        int id = 0;
        while(aux != NULL){
            id = aux->valor->id;
            //cout << "Id do Asteroid é: " << id << endl;
            if(aux->prox != NULL){
                aux = aux->prox;
            }
            else{
                break;
            }
        }
        //cout << "Id do Asteroide retornado eh: " << id << endl;
        return id;
    }
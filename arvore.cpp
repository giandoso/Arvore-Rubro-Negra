/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include<cstdlib>
#include<fstream>
#include <iostream>
#include <stdbool.h>
#include <string>

#include"arvore.h"

using namespace std;

Arvore::Arvore() {
    raiz = NULL;
    qtde = 0;
}

Arvore::~Arvore() {

}

void Arvore::Pre_Ordem() {
    raiz->Pre_Ordem(raiz);
}

void Arvore::Pos_Ordem() {
    raiz->Pos_Ordem(raiz);
}

void Arvore::Em_Ordem() {
    raiz->Em_Ordem(raiz);
}

void Arvore::Estado() {
    //TODO
}

void Arvore::Insere(int valor) {
    if (qtde == 0) {
        No *n = new No(valor, false, NULL); // primeiro nó, pai nulo e negro
        raiz = n;
        qtde++;
        return;
    }
    if (!Busca(valor)) {
        No *n = new No(valor, true, NULL); // Insere nó rubro, a principio sem pai
        qtde++;
        raiz->Insere(raiz, NULL, n);
    }
}

bool Arvore::Busca(int valor) {
    return raiz->Busca(valor, raiz);
}

bool Arvore::Remove(int valor) {
    if (raiz->Busca(valor, raiz)) {
        return raiz->Remove(valor, raiz, NULL);
    }
    return false;
}

No * Arvore::Captura_Maximo() {
    return raiz->Captura_Maximo(raiz);
}

No::No(int valor, bool rubro, No *pai) {
    this->dado = valor;
    this->rubro = rubro;
    this->esq = NULL;
    this->dir = NULL;
    this->pai = pai;
}

No::~No() {

}

// retorna true se tio de n é rubro

bool tio_eh_rubro(No *n) {
    No * avo = n->pai->pai;
    if (n->dado > avo->dado) {
        // neto a direita, tio a esquerda do avo        
        return !avo->esq ? false : avo->esq->rubro;
    } else {
        // neto a esquerda, tio a direita do avo
        return !avo->dir ? false : avo->dir->rubro;
    }
}

// retorna true se filho eh rubro com base no lado \/

bool filho_eh_rubro(No *n, int lado) { // 1 = dir 2 = esq
    if (lado == 1) {
        //esq
        return !n->dir ? false : n->dir->rubro;
    } else {
        //dir
        return !n->esq ? false : n->esq->rubro;
    }
}

// realiza a troca de cor do avo para vermelho
// e de seus filhos para preto

void troca_cor(No *n) {
    No * avo = n->pai;
    avo->rubro = true;
    avo->dir->rubro = false;
    avo->esq->rubro = false;

    if (avo->pai == NULL) { // estou na raiz da arvore
        avo->rubro = false;
    }
}

// acessar https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
// para visualizar imagens com nomes dos nós e visualização da rotação

void aplica_rotacao(No *p) {
    No * g = p->pai;
    No * x = p->esq->rubro ? p->esq : p->dir;
    if (p->dado < g->dado) {
        if (x->dado < p->dado) {
            // rotação_dir (left left)
//            if(g->pai == NULL){ // rotação na raiz
//                
//                
//            }else{
//                
//            }
            No * t3 = p->dir ? p->dir : NULL;
            p->dir = g;
            g->pai = p;
            g->esq = t3;
            if (t3)
                t3->pai = g;
            // troca_cor_rotacao()
        } else {
            // rotação esq dir (left right)
            // t2 = x->esq
            // t3 = x->dir
            // 
            // x->esq = p
            // p->pai = x
            // 
            // x->dir = g
            // g->pai = x
            // 
            // p->dir = t2
            // t2->pai = p
            //
            // g->esq = t3
            // t3->pai = g
            // troca_cor_rotacao()
        }
    } else {
        if (x->dado < p->dado) {
            // rotação dir esq
            // t3 = x->esq
            // t4 = x->dir
            //
            // x->esq = g
            // g->pai = x
            //
            // x->dir = p
            // p->pai = x
            //
            // g->dir = t3
            // t3->pai = g
            //
            // p->esq = t4
            // t4->pai = g
            // troca_cor_rotacao()

        } else {
            // rotação esq (right right)
            // t3 = p->esq
            //
            // p->esq = g
            // g->pai = p
            //
            // g->dir = aux
            // aux->pai = g
            // troca_cor_rotacao()
        }
    }
}

No * No::Insere(No *curr, No *prev, No * n) {
    if (curr == NULL) {
        n->pai = prev;
        return n;
    }
    if (curr->dado > n->dado)
        curr->esq = Insere(curr->esq, curr, n);
    else
        curr->dir = Insere(curr->dir, curr, n);


    if ((curr->rubro && (filho_eh_rubro(curr, 1) || filho_eh_rubro(curr, 2))) == true) {
        if (tio_eh_rubro(n)) {
            // troca cor
            troca_cor(curr); //troca a cor do avô e filhos
            cout << "Troca cor" << endl;

        } else {
            // rotação
            aplica_rotacao(curr);
            cout << "Rotação" << endl;
        }
    }
    return curr;
}

void No::Estado(No *raiz) {
    //TODO
}

void No::Pre_Ordem(No *raiz) {
    if (raiz) {
        cout << raiz->dado << " ";
        Pre_Ordem(raiz->esq);
        Pre_Ordem(raiz->dir);
    }
}

void No::Pos_Ordem(No *raiz) {
    if (raiz) {
        Pos_Ordem(raiz->esq);
        Pos_Ordem(raiz->dir);
        cout << raiz->dado << " ";
    }
}

void No::Em_Ordem(No *raiz) {
    if (raiz) {
        Em_Ordem(raiz->esq);
        cout << raiz->dado << " ";
        Em_Ordem(raiz->dir);
    }
}

bool No::Busca(int valor, No *raiz) {
    if (raiz) {
        if (raiz->dado == valor)
            return true;
        if (raiz->dado > valor)
            return Busca(valor, raiz->esq);
        else
            return Busca(valor, raiz->dir);
    } else return false;
}

No *No::Captura_Maximo(No* raiz) {
    if (raiz->dir == NULL) {
        return raiz;
    }
    if (raiz) {
        return Captura_Maximo(raiz->dir);
        //        return Captura_Maximo(raiz->esq, maior);
    }

}

bool No::Remove(int valor, No *raiz, No *pai) {
    if (raiz == NULL) {
        return false;
    }
    if (valor == raiz->dado) {
        No *aux = raiz;
        if (raiz->esq == NULL || raiz->dir == NULL) {
            //delete one child
            if (raiz->esq == NULL && raiz->dir == NULL) {
                // nao tem filho
                if (raiz->dado > pai->dado) {
                    // filho dir
                    pai->dir = NULL;
                    free(raiz);
                } else {
                    // filho esq
                    pai->esq = NULL;
                    free(raiz);
                }
                return true;
            } else if (raiz->dir == NULL) {
                // tem um filho a esquerda
                if (raiz->dado > pai->dado) {
                    // filho dir
                    pai->dir = raiz->esq;
                    free(raiz);
                } else {
                    // filho esq
                    pai->esq = raiz->esq;
                    free(raiz);
                }
                return true;
            } else if (raiz->esq == NULL) {
                // tem um filho a direita
                if (raiz->dado > pai->dado) {
                    // filho dir
                    pai->dir = raiz->dir;
                    free(raiz);
                } else {
                    // filho esq
                    pai->esq = raiz->dir;
                    free(raiz);
                }
                return true;
            }
        } else {
            //TODO problema qdo no for raiz da arv
            // tem dois filhos
            aux = Captura_Maximo(raiz->esq); // TEM QUE VE ESSA PORRA
            raiz->dado = aux->dado;
            raiz->esq->Remove(aux->dado, raiz->esq, raiz);
            free(aux);
            return true;
        }
    } else if (valor < raiz->dado) {
        return Remove(valor, raiz->esq, raiz);
    } else {
        return Remove(valor, raiz->dir, raiz);
    }
}


// =============== MANIPULAÇÃO DE ARQUIVOS================================================

bool writeFile(ofstream& file, string strFile) { // Abrir Arquivo para Escrita NO FINAL
    file.open(strFile, ios::ate | ios::app);
    return !(file.fail() || !file.is_open() || !file.good());
}

bool writeFileFinal(ofstream& file, string strFile) { // Abrir Arquivo para Escrita NO COMEÇO
    file.open(strFile);
    return !(file.fail() || !file.is_open() || !file.good());
}

bool readFile(std::ifstream &ifile, std::string strFile) { // Abrir Arquivo para Leitura
    ifile.open(strFile);
    return !(ifile.fail() || !ifile.is_open() || !ifile.good());
}
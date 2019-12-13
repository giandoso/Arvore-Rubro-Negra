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
int rotacao;
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

void atualiza_altura(No * n) {
    int alt1 = n->esq ? n->esq->altura : 0;
    int alt2 = n->dir ? n->dir->altura : 0;
    n->altura = alt1 > alt2 ? alt1 + 1 : alt2 + 1;
}
void pre_ordem_altura(No *n) {
    if (n) {
        pre_ordem_altura(n->esq);
        pre_ordem_altura(n->dir);
        atualiza_altura(n);
    }
}
void Arvore::Estado() {
    //TODO
    int qtdf = raiz->QtdFolhas(raiz);
    cout << "_____________________________________________________" << endl;
    cout << endl << "Estado da arvore:" << endl << endl;
        cout << "Folhas                             : " << qtdf << endl;
    pre_ordem_altura(raiz);
    cout << "Nivel maximo                       : " << raiz->altura << endl;
    cout << "Nivel medio(maximo/2)              : " << raiz->altura / 2 << endl;
    cout << "Nos intermediarios(excluso a raiz) : " << (qtde - qtdf - 1) << endl;
    cout << "Rotacoes : " << rotacao << endl;
    cout << "_____________________________________________________" << endl;
}

void Arvore::Insere(int valor) {
    if (qtde == 0) {
        No *n = new No(valor); // primeiro nó, pai nulo e negro
        n->cor = 2;
        raiz = n;
        qtde++;
        return;
    }
    if (!Busca(valor)) {
        No *n = new No(valor); // Insere nó rubro, a principio sem pai
        qtde++;
        raiz = raiz->Insere(raiz, n);
        CorrigeInsercao(n);
    }
}
int Arvore::getColor(No *n) {
    if (n == NULL)
        return 2;

    return n->cor;
}

void Arvore::setColor(No *n, int cor) {
    if (n == NULL)
        return;

    n->cor = cor;
}

void Arvore::RotacaoEsq(No *n) {
    No *dir_child = n->dir;
    n->dir = dir_child->esq;

    if (n->dir != NULL)
        n->dir->pai = n;

    dir_child->pai = n->pai;

    if (n->pai == NULL)
        raiz = dir_child;
    else if (n == n->pai->esq)
        n->pai->esq = dir_child;
    else
        n->pai->dir = dir_child;

    dir_child->esq = n;
    n->pai = dir_child;
    rotacao++;
}

void Arvore::RotacaoDir(No *n) {
    No *esq_child = n->esq;
    n->esq = esq_child->dir;

    if (n->esq != NULL)
        n->esq->pai = n;

    esq_child->pai = n->pai;

    if (n->pai == NULL)
        raiz = esq_child;
    else if (n == n->pai->esq)
        n->pai->esq = esq_child;
    else
        n->pai->dir = esq_child;

    esq_child->dir = n;
    n->pai = esq_child;
    rotacao++;
}

void Arvore::CorrigeInsercao(No* n){
    No *pai = NULL;
    No *avo = NULL;
    while (n != raiz && getColor(n) == 1 && getColor(n->pai) == 1) {
        pai = n->pai;
        avo = pai->pai;
        if (pai == avo->esq) {
            No *tio = avo->dir;
            if (getColor(tio) == 1) {
                setColor(tio, 2);
                setColor(pai, 2);
                setColor(avo, 1);
                n = avo;
            } else {
                if (n == pai->dir) {
                    RotacaoEsq(pai);
                    n = pai;
                    pai = n->pai;
                }
                RotacaoDir(avo);
                swap(pai->cor, avo->cor);
                n = pai;
            }
        } else {
            No *tio = avo->esq;
            if (getColor(tio) == 1) {
                setColor(tio, 2);
                setColor(pai, 2);
                setColor(avo, 1);
                n = avo;
            } else {
                if (n == pai->esq) {
                    RotacaoDir(pai);
                    n = pai;
                    pai = n->pai;
                }
                RotacaoEsq(avo);
                swap(pai->cor, avo->cor);
                n = pai;
            }
        }
    }
    setColor(raiz, 2);
}

bool Arvore::Busca(int valor) {
    return raiz->Busca(valor, raiz);
}

bool Arvore::Remove(int valor) {
    if (raiz->Busca(valor, raiz)) {
        No *n = raiz->Remove(raiz, valor);
        
        CorrigirRemocao(n);
        return true;
    }
    return false;
}

void Arvore::CorrigirRemocao(No *n) {
    if (n == NULL)
        return;

    if (n == raiz) {
        raiz = NULL;
        return;
    }

    if (getColor(n) == 1 || getColor(n->esq) == 1 || getColor(n->dir) == 1) {
        No *child = n->esq != NULL ? n->esq : n->dir;

        if (n == n->pai->esq) {
            n->pai->esq = child;
            if (child != NULL)
                child->pai = n->pai;
            setColor(child, 2);
            delete (n);
        } else {
            n->pai->dir = child;
            if (child != NULL)
                child->pai = n->pai;
            setColor(child, 2);
            delete (n);
        }
    } else {
        No *irmao = NULL;
        No *pai = NULL;
        No *ptr = n;
        setColor(ptr, 3);
        while (ptr != raiz && getColor(ptr) == 3) {
            pai = ptr->pai;
            if (ptr == pai->esq) {
                irmao = pai->dir;
                if (getColor(irmao) == 1) {
                    setColor(irmao, 2);
                    setColor(pai, 1);
                    RotacaoEsq(pai);
                } else {
                    if (getColor(irmao->esq) == 2 && getColor(irmao->dir) == 2) {
                        setColor(irmao, 1);
                        if(getColor(pai) == 1)
                            setColor(pai, 2);
                        else
                            setColor(pai, 3);
                        ptr = pai;
                    } else {
                        if (getColor(irmao->dir) == 2) {
                            setColor(irmao->esq, 2);
                            setColor(irmao, 1);
                            RotacaoDir(irmao);
                            irmao = pai->dir;
                        }
                        setColor(irmao, pai->cor);
                        setColor(pai, 2);
                        setColor(irmao->dir, 2);
                        RotacaoEsq(pai);
                        break;
                    }
                }
            } else {
                irmao = pai->esq;
                if (getColor(irmao) == 1) {
                    setColor(irmao, 2);
                    setColor(pai, 1);
                    RotacaoDir(pai);
                } else {
                    if (getColor(irmao->esq) == 2 && getColor(irmao->dir) == 2) {
                        setColor(irmao, 1);
                        if (getColor(pai) == 1)
                            setColor(pai, 2);
                        else
                            setColor(pai, 3);
                        ptr = pai;
                    } else {
                        if (getColor(irmao->esq) == 2) {
                            setColor(irmao->dir, 2);
                            setColor(irmao, 1);
                            RotacaoEsq(irmao);
                            irmao = pai->esq;
                        }
                        setColor(irmao, pai->cor);
                        setColor(pai, 2);
                        setColor(irmao->esq, 2);
                        RotacaoDir(pai);
                        break;
                    }
                }
            }
        }
        if (n == n->pai->esq)
            n->pai->esq = NULL;
        else
            n->pai->dir = NULL;
        delete(n);
        setColor(raiz, 2);
    }
}

No * Arvore::Captura_Maximo() {
    return raiz->Captura_Maximo(raiz);
}

No::No(int valor) {
    this->dado = valor;
    this->cor = 1;
    this->esq = NULL;
    this->dir = NULL;
    this->pai = NULL;
}

No::~No() {

}

int No::QtdFolhas(No *n)  
{  
    if(n == NULL)      
        return 0;  
    if(n->esq == NULL && n->dir == NULL)  
        return 1;          
    else
        return QtdFolhas(n->esq)+  
            QtdFolhas(n->dir);  
}  

No * No::Insere(No *raiz, No * n) {
    if(!raiz) return n;
    if (n->dado < raiz->dado) {
        raiz->esq = Insere(raiz->esq, n);
        raiz->esq->pai = raiz;
    } else if (n->dado > raiz->dado) {
        raiz->dir = Insere(raiz->dir, n);
        raiz->dir->pai = raiz;
    }
    return raiz;
}


No* No::Remove(No *raiz, int dado) {
    if (raiz == NULL)
        return raiz;

    if (dado < raiz->dado)
        return Remove(raiz->esq, dado);

    if (dado > raiz->dado)
        return Remove(raiz->dir, dado);

    if (raiz->esq == NULL || raiz->dir == NULL)
        return raiz;

    No *temp = Captura_Maximo(raiz->esq);
    raiz->dado = temp->dado;
    return Remove(raiz->esq, temp->dado);
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
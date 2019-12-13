/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arvore.h
 * Author: 2019.1.08.041
 *
 * Created on 31 de Outubro de 2019, 16:16
 */

#ifndef ARVORE_H
#define ARVORE_H

#include<fstream>
#include <iostream>

using namespace std;

class No { //Nó da Árvore
public:
    No(int valor); //Construtor
    ~No(); //Destrutor
    void Pre_Ordem(No *raiz);
    void Pos_Ordem(No *raiz);
    void Em_Ordem(No *raiz);
    int QtdFolhas(No *raiz);
    bool Busca(int valor, No *raiz);
    No *Captura_Maximo(No *raiz);
    void Estado(No *raiz);
    No *Remove( No *raiz, int valor);
    No *Insere(No *raiz, No *n);
    int dado, cor, altura; //cores = 1 red, 2 black, 3 doubleblack
    No *esq, *dir, *pai;
};

class Arvore {
public:
    Arvore();
    ~Arvore();
    void Pre_Ordem();
    void Pos_Ordem();
    void Em_Ordem();
    void Insere(int valor);
    bool Busca(int valor);
    void CorrigeInsercao(No *n);
    int getColor(No *n);
    void RotacaoEsq(No *n);
    void RotacaoDir(No *n);
    void setColor(No *n, int cor);
    void Estado();
    bool Remove(int valor);
    No *Captura_Maximo();
    void CorrigirRemocao(No *n);
    No *raiz;
    int qtde;
};

class Inicio{
public:
    Inicio(No * start);
    No * start;
};

// =============== MANIPULAÇÃO DE ARQUIVOS================================================

bool readFile(std::ifstream &ifile, std::string strFile);
bool writeFile(ofstream& file, std::string strFile);
bool writeFileFinal(ofstream& file, string strFile);
#endif /* ARVORE_H */


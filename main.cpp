/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: 2019.1.08.041
 *
 * Created on 31 de Outubro de 2019, 16:15
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "arvore.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    Arvore *arv = new Arvore;

    //Controle de arquivo (Abrindo arquivo e fazendo sua leitura)
    int control = 0; // 0 for test read file, 1 for manual insertion
    if (control) {
        arv->Insere(5);
        arv->Insere(8);
        arv->Insere(7);
        arv->Insere(3);
        arv->Insere(13);
        arv->Insere(21);
        arv->Insere(17);
        arv->Insere(17);
        arv->Remove(5);
        arv->Remove(7);
        //cout << arv->Busca(16) << " ";
        //arv->Insere(99);
    } else {
        ofstream outFile;
        ifstream dados;
        bool status;
        int tam = 0;
        char op;
        int valor;

        status = readFile(dados, "arquivo2.txt");
        //Teste de abertura de arquivo
        if (!status) {
            cout << "Arquivo não pode ser aberto para leitura." << endl;
            cout << "Programa terminando..." << endl;
        } else {
            //Leitura do arquivo       
            dados >> op;
            while (!dados.eof()) {
                switch (op) {
                    case 'i':
                    { //inserir
                        dados >> tam;
                        for (int j = 0; j < tam; j++) {
                            dados >> valor;
                            arv->Insere(valor);
                            cout << "Inserindo o valor " << valor << endl;
                        }
                        dados >> op;
                        break;
                    }
                    case 'r':
                    { //remover
                        dados >> tam;
                        for (int j = 0; j < tam; j++) {
                            dados >> valor;
                            int checaRemove = arv->Remove(valor);
                            if (checaRemove)
                                cout << "O valor " << valor << " foi removido com sucesso" << endl;
                            else
                                cout << "O valor " << valor << " não está presente na arvore" << endl;
                        }
                        dados >> op;
                        break;
                    }
                    case 'b':
                    { //buscar
                        dados >> tam;
                        for (int i = 0; i < tam; i++) {
                            dados >> valor;
                            int checaBusca = arv->Busca(valor);
                            if (checaBusca)
                                cout << "O valor " << valor << " está na arvore." << endl;
                            else
                                cout << "O valor " << valor << " não está na arvore." << endl;
                        }
                        dados >> op;
                        break;
                    }
                    case 'e':
                    { // estado
                        arv->Estado();
                        cout << endl;
                        dados >> op;
                        break;
                    }
                    case 'f':
                    {
                        cout << endl << "Fim de operação" << endl << endl;
                        return 0;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
            }
        }
    }
    cout << endl << "Arvore em Ordem: " << endl;
    arv->Em_Ordem();
    cout << endl << endl << "Arvore em Pré-Ordem: " << endl;
    arv->Pre_Ordem();
    cout << endl << endl << "Arvore em Pós-Ordem: " << endl;
    arv->Pos_Ordem();
    arv->Estado();
    cout << endl;
    return 0;
}
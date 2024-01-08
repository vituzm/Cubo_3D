#ifndef CUBO_H
#define CUBO_H
#include <iostream>

#define CAMADAS 8
#define LINHAS 8
#define COLUNAS 8


class cubo
{
    public:
        cubo();
        void inic();                                //inicia os valores
        char matriz3d[CAMADAS][LINHAS][COLUNAS];    // matriz de cada img do cubo
        void animacao_0(int img);                   //altera os valores dos leds do cubo, fazendo um degradê
        void animacao_1(int img);                   //altera os valores dos leds do cubo, diminuindo-o até o centro
        void animacao_2(int img);                   //altera os valores dos leds do cubo, zerando camadas de cima e de baixo
        void animacao_3(int img);                   //altera os valores dos leds do cubo, zerando camadas dos lados
        void preenche_cubo();                       // preenche o cubo com o valor de intensidade

    protected:

    private:
        void down();                    // desloca a camada de cima para baixo
        void preenche_cam();            // preenche a camada 0
        void tira_topo(int n_img);      // zera o topo do cubo
        void tira_chao(int n_img);      // zero a parte de baixo do cubo
        void tira_lado_esq(int n_img);  // zera o lado esquerdo
        void tira_lado_dir(int n_img);  // zera o lado direito
        void tira_face(int n_img);      // zera os leds da face do cubo
        void tira_fundo(int n_img);     // zera os leds do fundo do cubo
        char intensidade;               // intensidade dos leds
};

#endif // CUBO_H

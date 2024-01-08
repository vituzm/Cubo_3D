#include "cubo.h"
#include <iostream>

cubo::cubo()
{
    inic();
}

void cubo::inic()
{
    intensidade = 0;
    preenche_cubo(); //zerando os led do cubo
    intensidade = 15; // mudando a intensidade
}
/// DEGRADÊ ///
void cubo::animacao_0(int y)
{
    down();
    preenche_cam();
}

/// DIMINUI O CUBO ATÉ O CENTRO ///
void cubo::animacao_1(int y)
{
    tira_topo(y);
    tira_lado_dir(y);
    tira_chao(y);
    tira_lado_esq(y);
    tira_face(y);
    tira_fundo(y);
}

///ZERA CAMADAS DE CIMA E DE BAIXO, ATÉ O MEIO DO CUBO
void cubo::animacao_2(int y)
{
    tira_chao(y);
    tira_topo(y);
}

///ZERA CAMADAS DOS LADOS, ATÉ O MEIO DO CUBO
void cubo::animacao_3(int y)
{
    tira_lado_dir(y);
    tira_lado_esq(y);
}


///PREENCHE UMA CAMADA COM DETERMINADA INTENSIDADE
void cubo::preenche_cam()
{
    for (int y = 0; y < LINHAS; y++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
            matriz3d[0][y][x] = intensidade;
        }
    }
    intensidade-=2;

}

///PREENCHE O CUBO INTEIRO COM DETERMINADA INTENSIDADE
void cubo::preenche_cubo()
{
    for(int z = 0; z < CAMADAS; z++){
        for (int y = 0; y < LINHAS; y++)
        {
            for (int x = 0; x < COLUNAS; x++)
            {
                matriz3d[z][y][x] = intensidade;
            }
        }
    }
}

/// DESLOCA DE CIMA PARA BAIXO
void cubo::down()
{
    for (int z = CAMADAS - 1; z > 0 ; z--)
    {
        for(int y = 0; y < LINHAS ; y++)
        {
            for (int x = 0; x < COLUNAS; x++)
            {
                matriz3d[z][y][x] = matriz3d[z- 1][y][x];
            }
        }
    }
}

/// ZERA AS PRIMEIRAS CAMADAS
void cubo::tira_topo(int var)
{
    for(int z = 0; z < LINHAS; z++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
                matriz3d[var][z][x] = 0;
        }
    }
}

/// ZERA AS ÚLTIMAS CAMADAS
void cubo::tira_chao(int var)
{
    for(int z = 0; z < LINHAS; z++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
                matriz3d[7-var][z][x] = 0;
        }
    }
}

/// ZERA O LADO ESQUERDO
void cubo::tira_lado_esq(int var)
{
    for(int z = 0; z < CAMADAS; z++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
                matriz3d[z][var][x] = 0;
        }
    }
}

/// ZERA O LADO DIREITO
void cubo::tira_lado_dir(int var)
{
    for(int z = 0; z < CAMADAS; z++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
                matriz3d[z][7 - var][x] = 0;
        }
    }
}

/// ZERA O FUNDO
void cubo::tira_fundo(int var)
{
    for(int z = 0; z < CAMADAS; z++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
                matriz3d[z][x][var] = 0;
        }
    }
}

/// ZERA A FACE
void cubo::tira_face(int var)
{
    for(int z = 0; z < CAMADAS; z++)
    {
        for (int x = 0; x < COLUNAS; x++)
        {
                matriz3d[z][x][7 - var] = 0;
        }
    }
}

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "cubo.h"
#include "protocolo.h"
#include "locale.h"

using namespace std;

void anima_1(protocolo *sr, cubo *cub)
{
    for(int x = 0; x < 8; x++)
    {
        cub->animacao_0(x);//chama a função que mudara a organização dos leds
        Sleep(20);
        sr->envia_img(0x80 + x, cub->matriz3d); //armazena a img no cubo
    }

}

void anima_2(protocolo *ser, cubo *cubo)
{
    for(int y = 0; y < 4; y++)
    {
        cubo->animacao_1(y);
        Sleep(20);
        ser->envia_img(0x88 + y, cubo->matriz3d);
    }
}

void anima_3(protocolo *ser, cubo *cubo)
{
    cubo->preenche_cubo();
    ser->envia_img(0x80, cubo->matriz3d);
    Sleep(200);

    for(int y = 0; y < 5; y++)
    {
        cubo->animacao_2(y);
        Sleep(20);
        ser->envia_img(0x81 + y, cubo->matriz3d);
    }
}

void anima_4(protocolo *ser, cubo *cubo)
{
    cubo->preenche_cubo();
    ser->envia_img(0x80, cubo->matriz3d);
    Sleep(200);

    for(int y = 0; y < 5; y++)
    {
        cubo->animacao_3(y);
        Sleep(20);
        ser->envia_img(0x81 + y, cubo->matriz3d);
    }
}



int main()
{
    setlocale(LC_ALL, "");

    protocolo serial;
    cubo cb;
    char escolha = 0;

    if(serial.AbreComm() == INVALID_HANDLE_VALUE)return -1;// abre a com. serial e checa se houve um erro


    do
    {
        int max_val = 0;

        cout << "Escolha uma animação e aperte enter" << endl << "Animações: 1 a 3 " << endl;
        cin >> escolha;


        switch (escolha)
        {
        case '1':

            anima_3(&serial, &cb);// Chama a função para fazer animação 1
            max_val = 6; // valor maximo de imagens
            break;

        case '2':
            anima_4(&serial, &cb);// Chama a função para fazer animação 2
            max_val = 6;
            break;


        case '3':
            anima_1(&serial, &cb);// Chama a função para fazer animação 3
            anima_2(&serial, &cb);// Chama a função para fazer animação 3
            max_val = 12;
            break;

        default:
            cout << endl << "Comando não reconhecido" << endl << endl;
            escolha = -1; // se não for nenhum, codigo de erro = -1
            break;
        }

        Sleep(20);

        if (escolha != -1) // se não for o codigo de erro
        {
            cout << endl <<"RODANDO ANIMAÇÃO" << endl;
            cout << "SELECIONE 'T' PARA SAIR DA ANIMAÇÃO, PODENDO TROCÁ-LA" << endl;
            cout << "SELECIONE 'S' PARA SAIR DO PROGRAMA" << endl;

            for(int u = 0; u < max_val; u++)
            {
                if(kbhit())// o usuario pressionou alguma tecla?
                {
                    escolha=getch(); //armazena no buffer
                    cout << escolha << endl;
                    if(toupper(escolha) == 'T' || toupper(escolha) == 'S')
                    {
                        break; //para sair da animação
                    }
                    else cout << "COMANDO NÃO RECONHECIDO!!!" << endl;
                }


                Sleep(599);

                if(u == max_val-1) u = 0; // se chegou na ultima imagem, repete o loop
                serial.ativa_cb(0x80 | u); // ativa a imagem
            }
        }


    }while(toupper(escolha) != 'S');

    cout << "FECHA PROGRAMA" << endl;

    return 0;
}

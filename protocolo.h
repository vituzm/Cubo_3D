#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//envios
#define SNC ('S'|0x80)
#define ATX ('X'|0x80)
#define CLR ('C'|0x80)

//Respostas:
#define ACK 'A'
#define NAK 'N'
#define MND 'M'
#define NID 'I'
#define TOUT 'T'

class protocolo
{
    public:
        protocolo();                                     // costrutor da classe
        HANDLE AbreComm();                               // abre e configura a comunicação serial
        char envia_img(char CID, char matriz3d[][8][8]); // verifica se pode enviar a img do cubo e a envia para a serial se puder
        char ativa_cb(char CID);                         //ativa a img escolhida no cubo físico, que já está salva
        HANDLE p_com;                                    //cria o ponteiro, área de memória

    protected:

    private:

        unsigned long int n; //número de bytes efetivamente recebidos
        char ncom[6];        //define nome do arquivo, no nosso caso a porta usada "COM6"
        char dado[2];        //cria o buffer
        int baudrate;

};
#endif // PROTOCOLO_H

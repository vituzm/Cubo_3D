#include "protocolo.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

protocolo::protocolo()
{
    baudrate = 115200;
    strcpy(ncom,"COM6"); //define nome do arquivo, no nosso caso a porta usada

}

HANDLE protocolo::AbreComm()
{

    DCB cdcb;    //nomeia a estrutura DCB (Device Control Block) utilizada         para definir todos os parâmetros da comunicação
    COMMTIMEOUTS comto; //nomeia a estrutura COMMTIMEOUTS (COMMon TIME OUTS) utilizada para definir os timeouts da comunicação

    p_com = CreateFile(
               ncom, //nome do arquivo
               GENERIC_READ | GENERIC_WRITE, //abre arquivo para leitura                         ou escrita
               0, //indica que o arquivo não pode ser compartilhado
               NULL, //utiliza a estrutura default para as funções de segurança
               OPEN_EXISTING, //abre o arquivo, se não existir, retorna erro
               FILE_ATTRIBUTE_NORMAL, //o arquivo deve ser utilizado                     sozinho
               NULL); //sem gabarito de atributos
    if(p_com == INVALID_HANDLE_VALUE) // testa falha na abertura do arquivo
    {
        fprintf(stderr, "Nao abriu a %s\n", ncom);
        return INVALID_HANDLE_VALUE;
    }

    GetCommState(p_com, &cdcb); //le os parâmetros de comunicação                     atuais
    cdcb.BaudRate    = baudrate; //define a taxa de transmissão
    cdcb.ByteSize    = 8; //define o tamanho do dado - 8 bits
    cdcb.StopBits    = ONESTOPBIT; //define o tamanho do stop bit - 1                     stop bit
    cdcb.Parity      = EVENPARITY;     //define o tipo de paridade - par                         paridade
    if(!SetCommState(p_com,&cdcb)) //seta os novos parâmetros de comunicação
    {
        fputs("SetCommState", stderr);
        return INVALID_HANDLE_VALUE;
    }

    GetCommTimeouts(p_com, &comto);
    //Le os parâmetros atuais de COMMTIMEOUTS
    comto.ReadIntervalTimeout         = MAXDWORD;
    //tempo máximo entre a chegada de dois caracters consecutivos(ms)
    comto.ReadTotalTimeoutMultiplier  =    0;
    comto.ReadTotalTimeoutConstant    =    0;
    comto.WriteTotalTimeoutMultiplier =    0;
    comto.WriteTotalTimeoutConstant   =    0;
    SetCommTimeouts(p_com, &comto);
    //seta os parâmetros de COMMTIMEOUTS

    return p_com;
}


char protocolo::envia_img(char CID, char matriz3d[][8][8]){

    int tentativas=10000;// numero de repetições para ler a serial

    /** VERIFICANDO SE PODDE MADAR OS DADOS */
     dado[0] = SNC;
     dado[1] = CID;

     std::cout << "ENVIANDO DADOS: " << dado[0] << "//" << dado[1] << std::endl;

     WriteFile(p_com, dado, 2, &n, NULL); // envia SNC e CID

     do{
     ReadFile(p_com, dado, 1, &n, NULL); // le um dado do buffer/porta
     //espera receber MND ou NID (se der erro)
     tentativas--;
     }while(tentativas > 0 && n==0);

     std::cout << "DA PARA MANDAR? "<< dado[0] << std::endl;
     if(dado[0] != MND) return dado[0];



     ///ENVIANDO A IMAGEM /
     WriteFile(p_com, matriz3d, 512, &n, NULL); // envia os 512 bytes
     tentativas=1000000;

     do{
     ReadFile(p_com, dado, 1, &n, NULL); // ACK?
     tentativas--;

     }while(tentativas>0 && n==0);
     std::cout << "ENVIOU? "<< dado[0] << std::endl<<std::endl;

     if(dado[0] != ACK) return dado[0]; // se não deu

    return 1;
}


/// ATIVANDO O CUBO ///
char protocolo::ativa_cb(char CID){
     int tentativas = 10000; // numero de repetições para ler a serial

     dado[0] = ATX;
     dado[1] = CID;

     Sleep(20);
     WriteFile(p_com, dado, 2, &n, NULL); // envia SNC e CID

     do{
     ReadFile(p_com, dado, 1, &n, NULL); // ACK?
     tentativas--;

     }while(tentativas>0 && n==0);
     std::cout << "ATIVOU? "<<dado[0] << std::endl;
     if(dado[0] != ACK) return dado[0]; // se não deu

     return 1;
}


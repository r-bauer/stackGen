//***************************************************************************//
//                                                                           //
//  Titulo:                                                                  //
//  Arquivo: MAIN.C                                                          //
//  Data: 16/09/2008                                                         //
//  Versao: 1.0                                                              //
//  Autor: Roberto Bauer                                                     //
//  Observacoes: Arquivo central do programa, funcaoh main()                 //
//  Historico de evolucao:                                                   //
//                                                                           //
//***************************************************************************//

#define __MAIN_C__

#include "main.h"

int main(int argc, char *argv[])
{
    int i;

    i = StackDriver(argc, argv);

    return (i);

}

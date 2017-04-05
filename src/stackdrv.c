//**************************************************************//
//  Arquivo: STACKDRV.C                                         //
//  Autor: Roberto Bauer                                        //
//  Observacoes:                                                //
//              Controlador da aplicacaoh de exemplo de pilhas. //
//**************************************************************//


#define __STACKDRV_C__

#include "main.h"


int StackDriver(int argc, char *argv[])
{
    FILE *fin;       // arquivo que sera lido
    char cBuf[512];  // carrega as linhas do arquivo neste buffer
    int iLineCount;  // contagem atual da linha
    SDATA *sdEl;     // dado temporario,
    SSTACK *stk;     // a pilha que serah usada
    char c;          // caracter a ser examinado
    int i;           // para ser usado como contador de loop

    if (argc != 2)
    {
        fprintf(stderr, "Uso: Stackgen nome.ext\n");
        return (EXIT_FAILURE);
    }

    fin = fopen(argv[1], "rt");
    if (fin == NULL) 
    {
        fprintf(stderr, 
                "Naoh conseguir encontrar/abrir o arquivo %s\n", 
                argv[1]);
        return (EXIT_FAILURE);
    }

    stk = appCreateStack(40);       // cria e inicializa a pilha
    if (stk == NULL)
    {
        fprintf(stderr, "Memoria Insuficiente\n");
        return (EXIT_FAILURE);
    }

    // cria  o elemento da pilha
    sdEl = (SDATA *) malloc(sizeof(SDATA));
    if (sdEl == NULL) 
    {
        fprintf(stderr, "Memoria Insuficiente\n");
        return (EXIT_FAILURE);
    }

    iLineCount = 0;
    while (!feof(fin))
    {
        // leh uma linha do programa C
        if (fgets(cBuf, sizeof(cBuf) - 1, fin) == NULL)
            break;

        ++iLineCount;

        // procura e processa colchete, chaves e parenteses
        for (i = 0; cBuf[i] != '\0'; ++i)
        {
            switch (c = cBuf[i])
            {
                case '{':
                case '[':
                case '(':
                    sdEl->cOpener = c;
                    sdEl->iLineNo = iLineCount;
                    if (!appPushData(stk, sdEl))
                    {
                        fprintf(stderr, "Acabou espacoh na pilha\n");
                        return (EXIT_FAILURE);
                    }
                    break;

                case '}':
                case ']':
                case ')':
                    if (!appPopData(stk, sdEl))
                    {
                        fprintf(stderr, 
                                "Perdeu %c na linha %d\n", 
                                 c, iLineCount);
                    }
                    else 
                    {
                        if (((c == ')') && (sdEl->cOpener != '(')) ||
                            ((c == ']') && (sdEl->cOpener != '[')) ||
                            ((c == '}') && (sdEl->cOpener != '{')))
                        {
                            fprintf(stderr, 
                                    "%c na linha %d"
                                    " naoh combina com "
                                    "%c na linha %d\n",
                                    c, iLineCount,
                                    sdEl->cOpener, sdEl->iLineNo);
                        }
                    }
                    break;

                default:
                    continue;
            }
        }
    }

    // chegou ao fim do arquivo. Existe algum item sem par ?
    if (appViewData(stk, 0) != NULL) 
    {
        while (appPopData(stk, sdEl) != 0)
        {
            fprintf(stderr, 
                    "%c na linha %d naoh combina\n", 
                    sdEl->cOpener, 
                    sdEl->iLineNo);
        }
    }

    fprintf(stderr, "Checagem de erro completada\n");
    fclose(fin);

    return (EXIT_SUCCESS);
}


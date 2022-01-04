//Julio Gabriel Profeta Otoni
//RA: 1430482021011
//------------------
//Samuel Silva Perumalswamy
//RA: 1430482011010
//------------------
//KAREN ELLEN DA SILVA
//RA: 1430481921054

#ifndef _MENUAGENDA_C
#define _MENUAGENDA_C

#include <stdio.h>

#include "usuario.h"
#include "agenda.h"

int main()
{//aqui seria a função main e nela temos as opçoes para a interação com o nosso sistema
    int op;
    do {
        printf("\n\nAgenda\n");
        printf("<1> Primeiro acesso\n");
        printf("<2> Acessar agenda\n");
        printf("<0> Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                cadastrar_usuario();
                break;
            case 2:
                autenticar_usuario();
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (op != 0);
    return 0;
}
#endif
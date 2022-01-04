//Julio Gabriel Profeta Otoni
//RA: 1430482021011
//------------------
//Samuel Silva Perumalswamy
//RA: 1430482011010
//------------------
//KAREN ELLEN DA SILVA
//RA: 1430481921054

#include <stdio.h>
#include <string.h>

#include "usuario.h"
#include "agenda.h"


void cadastrar_usuario(){
    FILE * arq;
    usuario usu;

    if ((arq = fopen(ARQ_USUARIO, "ab")) == NULL)//anexa um arquivo binário abre/cria um arquivo para gravação no final do arquivo e verifica se é possível abrí-lo
    {
        fprintf(stderr, "\nErro: nao foi possivel abrir o arquivo %s!\n", ARQ_USUARIO);
        return;
    }
    
    printf("\n\nNovo Usua'rio\n");
    fseek(arq, 0, SEEK_END);// faz a pesquisa colocando o indice no final do arquivo para registrar o cadastro do usuário
    usu.id = ftell(arq) / sizeof(usuario) + 1;//faz o id altoincrementa´vel pegando o tamanho do arquivo e dividindo pelo numero de estruturas e somando mais1

    printf("Id.: %d \n", usu.id);

    printf("Nome: ");
    scanf(" %51[^\n]", usu.nome);

    printf("Login: ");
    scanf(" %21[^\n]", usu.login);

     while(usuario_existe(usu.login, &usu) == true) //chama a função passando dois parametros para averiguação esperando que ela devova verdadeiro
        {
            printf("\nErro: Usua'rio ja' existente  (%s)!\n", &usu.login);
            printf("Digite o login novamente: ");
            scanf(" %21[^\n]", usu.login);

            
        }
        

    fwrite(&usu, sizeof(usuario), 1, arq);// Escreve no arquivo o registro do contato
    fclose(arq); // Fecha o arquivo aberto
    printf("\n Usua'rio criado com sucesso!");

    menu_agenda(usu);
       

        

}

bool usuario_existe(const char * login,  usuario * u)
{
   
         FILE * arq;//declara o arquivo que está sendo utilizado
    

        if ((arq = fopen(ARQ_USUARIO, "rb")) == NULL) {//abre o arquivo para leitura e verifica se há algo nele
        return false;//se não houver ele devolve falso
        
        }

        while (fread(u, sizeof(usuario), 1, arq) > 0 ){//faz um laço percorrendo o arquivo
          
         if(strncasecmp(u->login, login, strlen(login)) == 0)//verifica se o nome que foi passado por parametro é encontrado
         {
            fclose(arq);//fecha o arquivo 
             return true;// devolve true          
         }
               
        }
        fclose(arq);//fecha o arquivo 
        return false;// devolve true 
        

}

void autenticar_usuario(){

    FILE * arq;//declara o arquivo que está sendo utilizado
    usuario u;//declara a struct usurario pela letra u
    char login_usu[21];//cria uma variável de caracteres

    printf("\nAcessar agenda\n");
    printf("Login: ");//solicita o login
    scanf(" %21[^\n]", login_usu);//armazena o valor dos mesmos


        if (usuario_existe(login_usu, &u) == true) //chama a função passando os parametro
        {
            printf("\nSucesso: Seja bem-vindo %s!\n", login_usu);//se receu true ele devolve essa mensagem
            menu_agenda(u);//chama a func 

        }
        else
        {
            printf("\nErro: Usua'rio nao existente (%s)!\n", login_usu);//se devolver falso ele retorna essa mensagem
        }
    
}


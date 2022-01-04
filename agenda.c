//Julio Gabriel Profeta Otoni
//RA: 1430482021011
//------------------
//Samuel Silva Perumalswamy
//RA: 1430482011010
//------------------
//KAREN ELLEN DA SILVA
//RA: 1430481921054
#include "usuario.h"
#include "agenda.h"

#include <stdio.h>
#include <string.h>

    
    void menu_agenda(usuario usu){//metodo que recebe com parametro uma determinada estururtura
    
    
    int num;
    printf("\n\n---------------------------\n");
    printf("Agenda de %s\n", usu.nome);
    printf("Id.:%d\n", usu.id);
    printf("---------------------------\n");
    do {
        printf("Selecione uma opcao: \n");//solicita uma opção do usuário do sistema até q seja diferente do numero de opções
        printf("<1> Novo contato\n");
        printf("<2> Alterar contato\n");
        printf("<3> Listar contatos\n");
        printf("<4> Consultar os contatos\n");
        printf("<0> Sair da agenda\n");
        printf("Opcao: ");
        scanf("%d", &num);
        switch (num) {
            case 1:
                cadastrar_contato(usu.id);
                break;
            case 2:
                alterar_contato(usu.id);
                break;
            case 3:
                listar_contatos(usu.id);
                break;
            case 4:
                consultar_contatos(usu.id);
                break;
            case 0:
                break;
            default:
                printf("\nOpcao invalido\n");
        }
    } while (num != 0);

}

     void cadastrar_contato(int id_usu)
    {
        FILE * arq;// Para a manipulação de arquivo do contato 
        contato c;// Chama a estrutura do contato e deixa a sigla 'c' para uso padrão na função

    // Se o arquivo for nulo, mostrar a mensagem de erro, não abre o arquivo
    if ((arq = fopen(ARQ_AGENDA, "ab")) == NULL) {
        fprintf(stderr, "\nErro: nao foi possivel abrir o arquivo %s!\n", ARQ_AGENDA);
        return;
    }

    //solicita o cadastro do novo paciente
    printf("\n\nNovo contato\n");

    c.id_usuario = id_usu; //declara o id_usuario como o id do usuario que acessou

    fseek(arq, 0, SEEK_END);    // faz a pesquisa colocando o indice no final do arquivo para registrar o cadastro do contato
    c.id_contato = ftell(arq) / sizeof(contato) + 1; //faz o id altoincrementa´vel pegando o tamanho do arquivo e dividindo pelo numero de estruturas e somando mais1
    printf("IdUsuario: %d\n", c.id_usuario);

    printf("IdContato: %d\n", c.id_contato);

    printf("Nome: ");
    scanf(" %39[^\n]", c.nome);

    printf("Telefone: ");
    scanf(" %13[^\n]", c.telefone);

    printf("E-mail: ");
    scanf(" %29[^\n]", c.email);

    fwrite(&c, sizeof(contato), 1, arq);// Escreve no arquivo o registro do contato
    fclose(arq); // Fecha o arquivo aberto no if logo acima 
    printf("\nContato cadastrado com sucesso!\n");


}

    void alterar_contato(int id_usu){

    FILE * arq;// Para a manipulação de arquivo do contato 
    contato c;// Chama a estrutura do contato e deixa a sigla 'c' para uso padrão na função
    if ((arq = fopen(ARQ_AGENDA, "r+b")) == NULL) { //abre um arquivo binário para leitura/escrita e verifica se há algum contato
        printf("\nNao ha' nenhum contato cadastrado!\n");
        return;
    }
    printf("\n\nAlterar um Contato\n");    

        int id;
        printf("Insria o Id: ");
        scanf("%d", &id);
        fseek(arq, (id - 1) * sizeof(contato), SEEK_SET);//verifica se o id existe no arquivo
        fread(&c, sizeof(contato), 1, arq);//faz a leitura do arquivo
        if (id < 1 || feof(arq)) {//verifica se o id é menor que 1 ou se chegou no final do arquivo
            printf("\nErro: id nao encontrado (%d)!\n", id);
            fclose(arq);
            return;
        }

        c.id_usuario = id_usu;//declara o id_usuario como o id do usuario que acessou
         
        
        printf("Nome: %s\n", c.nome); //mostra o vlaor dos membros atuais
        printf("Novo nome: ");//solocita a inserção de dados para os membros
        scanf(" %39[^\n]", c.nome);//faz a captur dos novos dados

        printf("Telefone atual: %s\n", c.telefone);//mostra o vlaor dos membros atuais
        printf("Novo telefone: ");//solocita a inserção de dados para os membros
        scanf(" %13[^\n]", c.telefone);//faz a captur dos novos dados

        printf("E-mail atual: %s\n", c.email);//mostra o vlaor dos membros atuais
        printf("Novo e-mail: ");//solocita a inserção de dados para os membros
        scanf(" %29[^\n]", c.email);//faz a captur dos novos dados

        fseek(arq, -sizeof(contato), SEEK_CUR);//verifica se a estruct existe no arquivo e pesquisa atraves da posição atual
        fwrite(&c, sizeof(contato), 1, arq);//faz a escrita no arquivo
        printf("\nContato atualizado com sucesso!\n");
        fclose(arq);//fecha o arquivo

     }



     void listar_contatos(int id_usu)
{
         FILE * arq;
        contato c;
        int idusu = id_usu;
        
    if ((arq = fopen(ARQ_AGENDA, "rb")) == NULL) {//abre o arquivo para leitura e verifica se há algum valor 
        printf("\nNao ha' nenhum contato cadastrado\n");
        return;
    }
    printf("\n\nContatos Cadastrados\n");
    printf("-----------------------------------------------------------\n");
    printf("Id  Nome                 Telefone         E-mail\n");
    printf("-----------------------------------------------------------\n");
    while (fread(&c, sizeof(contato), 1, arq) > 0)
    {
        if (c.id_usuario == idusu) {
        printf("%03d %-20.20s %-13s %s\n", c.id_contato, c.nome, c.telefone, c.email);
        }
    }
    printf("-----------------------------------------------------------\n");
    fclose(arq);//fecha o arquivo
}

     void consultar_contatos(int id_usu)
     {
         FILE * arq;
        contato c;

       int idusu = id_usu;

        if ((arq = fopen(ARQ_AGENDA, "rb")) == NULL) {//abre o arquivo para leitura e verifica se há algum valor 
        printf("\nNao ha' nenhum contato cadastrado!\n");
        return;
        }

        printf("\n\nConsultar um contato\n"); 

        char nome[40];
        printf("\nInsira o nome de um contato: \n"); //solicita um nome para pesquisa
        scanf(" %39[^\n]", nome);//armazena o valor da pesquisa
        printf("Contatos que comecam com nome %s\n", nome);
        printf("-----------------------------------------------------------\n");
        printf("Id  Nome                 Telefone         E-mail\n");
        printf("-----------------------------------------------------------\n");
  //
        while (fread(&c, sizeof(contato), 1, arq) > 0) {//faz a leitura da esturutura no arquivo
            if (strncasecmp(c.nome, nome, strlen(nome)) == 0 && c.id_usuario == idusu) {// e verifica se é igual ao ao nome inserido
                printf("%03d %-20.20s %-13s %s\n", c.id_contato, c.nome, c.telefone, c.email);//printa os dados dos membros  
            }
        }
        printf("-----------------------------------------------------------\n");

        fclose(arq);//fecha o arquivo
    }
    
       
   
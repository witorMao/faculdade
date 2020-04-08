/*
	Programa desenvolvido como projeto final para a disciplina de Modelagem 
	Computacional em Grafos, oferecida no primeiro semestre de 2019 pelo 
	professor Dr. Thiago A. S. Pardo e utilizando algumas funções criadas por ele.

	Desenvolvedores:
	Bruno dos Santos, N° USP 10786170
	Henrique de Souza Q. dos Santos, Nº USP 10819029
	Witor Matheus A. de Oliveira, Nº USP 10692190

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista_adj.h"

void options(bool logado){

    if(logado){
        printf("\n***OPCOES***\n");
        printf("3. Vizualizar meus amigos\n");
        printf("4. Excluir seu usuário\n");
        printf("5. Enviar solicitação de amizade\n");
        printf("6. Visualizar minhas solicitações de amizade\n");
        printf("7. PROGRAMA TINDER 2.0: Meu namorado ideal\n");
        printf("8. Quem não deveria ser meu amigo???\n");
        printf("9. Sugestoes de amizade\n");
        printf("10. Logout\n");
        printf("0. Sair\n\n");
        printf("Sua opcao: ");
    }
    else{
        printf("\n***OPCOES***\n");
        printf("1. Criar usuario\n");
        printf("2. Efetuar login\n");
        printf("0. Sair\n\n");
        printf("Sua opcao: ");
    }
}

int main(int argc, char const *argv[]){

    Grafo *g = criaGrafo();
    char string[200], senha[200], nome[200];
    int opcao = 1, tentativas = 3, pos = -1, *amigos = NULL, res = 0, confirm = -1, loop = 1;
    bool logado = false;

    options(logado);
    scanf("%d", &opcao);

    while(loop){
        
        switch(opcao){
        
            case 1: // criar usuario

                if(logado) printf("Por favor, deslogue antes de continuar.\n");
                else{
                    res = addUsuario(g); // recebendo resultado da funcao de criacao de usuario

                    if(res == -1){
                        printf("Nome de usuario já existe. Por favor, recomece.\n");
                        break;
                    }
                    else if(res == -2){
                        printf("\nRede social está cheia. Por favor, remova algum usuário.\n");
                        break;
                    }
                    else printf("\nUsuario criado com sucesso!\n");
                }

                options(logado);
                scanf("%d", &opcao);
            break;

            case 2: // efetuar login
                
                if(logado) printf("\nPor favor, deslogue antes de continuar.\n");
                else{
                    // garantindo que o usuario digite um nome com menos de 100 caracteres
                    while(true){

                        printf("\nPor favor, digite o seu nome de usuario: ");
                        getchar();
                        scanf("%[^\r\n]", nome);
                        getchar();
                        if(strlen(nome) > 100) printf("Poxa, digite um nome com menos de 100 caracteres... :(\n");
                        else break;
                    }
                    pos = busca_binaria(verticesGrafo(g), nome, 0, numVertices(g));

                    if(pos == -1){
                        printf("\nUsuario inexistente! Você digitou o nome correto?\n");
                        options(logado);
                        scanf("%d", &opcao);
                        break;
                    }
                    printf("Você terá 3 tentativas para digitar a senha correta.\n\n");
                    while(tentativas > 0){
                        
                        printf("Por favor, digite a sua senha: ");
                        scanf("%s", senha);        

                        if(login(g, pos, senha)){
                            if(sexoUsuario(g, pos) == 'h') printf("\n\nLogin efetuado com sucesso. Bem-vindo, %s!\n", nomeUsuario(g, pos));
                            else printf("\n\nLogin efetuado com sucesso. Bem-vinda, %s!\n", nomeUsuario(g, pos));
                            tentativas = 3;
                            logado = true;
                            break;
                        }
                        else if(!login(g, pos, senha)){
                            tentativas--;
                            printf("Senha incorreta. Tentativas restantes: %d\n", tentativas);
                        }
                    }

                    if(tentativas == 0){
                        printf("Sem tentativas restantes. Inicie o programa novamente hahah >:D\n");
                        return 0;
                    }
                }

                options(logado);
                scanf("%d", &opcao);

            break;

            case 3: //mostra os amigos, a operação de remover algum amigo é oferecida

                if (logado) printAmigos(g, pos);
                else printf("Por favor, efetue login antes de continuar.\n");
                    
                options(logado);
                scanf("%d", &opcao);

            break;

            case 4: // deletar usuario que estiver logado

                if (logado){
    
                    printf("\nVocê deseja mesmo deletar seu usuario?\nSe sim, digite 1.\nSe não, digite 0.\n\nSua opcao: ");
                    scanf("%d", &confirm);

                    if(confirm == 0) printf("\nUfa, por um momento achamos que você queria nos abandonar! Nada foi feito. Voltando ao menu...\n\n");
                    else if(confirm == 1){
                        printf("Que pena, %s... Seu cadastro foi removido.\n", nomeUsuario(g, pos));
                        removeVertice(g, nomeUsuario(g, pos));
                        logado = false;
                    }
                    else printf("Opçao invalida. Voltando ao menu...\n");
                }
                else printf("Por favor, efetue login antes de continuar.\n");
                    
                options(logado);
                scanf("%d", &opcao);

            break;

            case 5: // enviar solicitação de amizade

                if (logado){

                    // garantindo que o usuario nao digite um nome com mais de 100 caracteres
                    while(true){

                        printf("Por favor, digite exatamente o nome do usuario que voce quer enviar a solicitação de amizade: ");
                        getchar();
                        scanf("%[^\r\n]", nome);
                        getchar();
                        if(strlen(nome) > 100) printf("Poxa, digite um nome com menos de 100 caracteres... :(\n");
                        else break;
                    }
                    enviaSolicitacaoAmizade(g, nomeUsuario(g, pos), nome);
                }
                else printf("Por favor, efetue login antes de continuar.\n");
                    
                options(logado);
                scanf("%d", &opcao);

            break;

            case 6: // visualizar minhas solicitaçoes

                if (logado) printSolicitacoes(g, pos);
                else printf("Por favor, efetue login antes de continuar.\n");
                    
                options(logado);
                scanf("%d", &opcao);

            break;    

            case 7: // namorado ideal

                if (logado) namoradoIdeal(g, nomeUsuario(g, pos));
                else printf("Por favor, efetue login antes de continuar.\n");
                    
                options(logado);
                scanf("%d", &opcao);

            break;

            case 8: // amigos 'indesejados'

                if(logado){

                    pos = busca_binaria(verticesGrafo(g), nome, 0, numVertices(g));
                    amigos = sugestaoAmizades(g, pos, 0, 1);

                    printf("Sugestão de %d amigos que nao deveriam estar na sua lista, baseando-se no seu perfil: ", NUMSUGESTOES);
                    
                    for(int i = 0; i < NUMSUGESTOES; i++){
                        for(int j = 0; j < numVertices(g); j++){
                            
                            if(idUsuario(g, j) == amigos[i]) printf("%s", nomeUsuario(g, j));
                            
                        }
                        if(i+1 == NUMSUGESTOES) printf(".");
                        else printf(", ");
                    }
                }
                else printf("Por favor, efetue login antes de continuar.\n");
                printf("\n");
                    
                // resetando as variaveis que calculam a similaridade
                for(int i = 0; i < numVertices(g); i++){ 
                    setSimilaridade(g, i, 0);
                    setVisitado(g, i, 0);
                }
                    
                options(logado);
                scanf("%d", &opcao);

            break;

            case 9: // sugestoes de amizade

               if(logado){

                    pos = busca_binaria(verticesGrafo(g), nome, 0, numVertices(g));
                    amigos = sugestaoAmizades(g, pos, 1, 0);

                    printf("\nSugestão de %d amigos para voce enviar solicitacoes, baseando-se no seu perfil: ", NUMSUGESTOES);
                    
                    for(int i = 0; i < NUMSUGESTOES; i++){
                        for(int j = 0; j < numVertices(g); j++){
                            if(idUsuario(g, j) == amigos[i]) printf("%s ", nomeUsuario(g, j));
                        }
                    }
                }
                else printf("Por favor, efetue login antes de continuar.\n");
                
                printf("\n");
                    
                // resetando as variaveis que calculam a similaridade
                for(int i = 0; i < numVertices(g); i++){ 
                    setSimilaridade(g, i, 0);
                    setVisitado(g, i, 0);
                }
                    
                options(logado);
                scanf("%d", &opcao);

            break;

            case 10: // logout
                if(logado){
                    logado = false;
                    printf("Deslogado com sucesso!\n");
                }
                else printf("Por favor, efetue login antes de continuar.\n");
                    
                options(logado);
                scanf("%d", &opcao);
            break;

            case 64: // printa todo o grafo (só pra testes)
                printGrafo(g);
                options(logado);
                scanf("%d", &opcao);
            break;

            case 0: // sair

                printf("Tem certeza que deseja finalizar o programa? Todos os dados serão deletados!\nDigite 5 caso confirme a ação\nDigite 0, caso contrário\n\nSua opcao: ");
                scanf("%d", &confirm);

                if(confirm == 0){
                    printf("Ok! Nada será feito.\n");
                    options(logado);
                    scanf("%d", &opcao);
                }
                else if(confirm == 5){
                    printf("Esperamos que tenha gostado. Até mais!!\n");
                    loop = 0;
                }
                
            break;

            default: // opcao invalida
                printf("Opção invalida. Por favor, selecione uma das opcoes validas.\n ");            
                options(logado);
                scanf("%d", &opcao);
            break;
        }        
    }

    destroiGrafo(g);
    return 0;
}
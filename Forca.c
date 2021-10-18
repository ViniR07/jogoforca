#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

  // Funções/Módulos

// Funcao Principal
int main() {

    abertura();

    do {

        escolhepalavra();

        do {

            desenhaforca();
            chuta();

        } while (!ganhou() && !enforcou());

        if (ganhou()) {

            printf("\nA palavra secreta era %s\n", palavrasecreta);
            printf("Parabens, voce ganhou! Toma aqui seu trofeu!\n\n");

            printf("       ___________      \n");
            printf("      '._==_==_=_.'     \n");
            printf("      .-\\:      /-.    \n");
            printf("     | (|:.     |) |    \n");
            printf("      '-|:.     |-'     \n");
            printf("        \\::.    /      \n");
            printf("         '::. .'        \n");
            printf("           ) (          \n");
            printf("         _.' '._        \n");
            printf("        '-------'       \n\n");

        } else {

            printf("\nF pra Você -_-\n");
            printf("A palavra era %s\n\n", palavrasecreta);

            printf("    _______________         \n");
            printf("   /               \\       \n");
            printf("  /                 \\      \n");
            printf("//                   \\/\\  \n");
            printf("\\|   XXXX     XXXX   | /   \n");
            printf(" |   XXXX     XXXX   |/     \n");
            printf(" |   XXX       XXX   |      \n");
            printf(" |                   |      \n");
            printf(" \\__      XXX      __/     \n");
            printf("   |\\     XXX     /|       \n");
            printf("   | |           | |        \n");
            printf("   | I I I I I I I |        \n");
            printf("   |  I I I I I I  |        \n");
            printf("   \\_             _/       \n");
            printf("     \\_         _/         \n");
            printf("       \\_______/           \n");
        }

    } while (repetirjogo());

    adicionarpalavra();

}

// Procedimento de Boas Vindas ao Jogo
void abertura() {

    printf("/*********************************/\n");
    printf("/* Bem Vindo(a) ao Jogo da Forca */\n");
    printf("/*********************************/\n\n");
}

// Procedimento de Sorteio da Palavra Secreta
void escolhepalavra() {

    FILE* f;

    f = fopen("palavras.txt", "r"); // (NOME DO ARQUIVO, O QUE VAI FAZER)

    if (f == 0) {  // Caso o arquivo esteja corrompido ou de problema
        printf("Desculpe, banco de dados nao disponivel.");
        exit(1);
    }

    int QtdDePalavras;
    fscanf(f, "%d", &QtdDePalavras);

    srand(time(0));
    int Nrandomico = rand() % QtdDePalavras;  // Retorna números aleatórios de [0 a Qtddepalavras - 1]

    for (int i = 0; i <= Nrandomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }


    fclose(f);
}

// Procedimento de Desenhar a Forca e as Tentativas
void desenhaforca() {

    int erros = contaerros();

    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c    \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c   \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 3 ? '/' : ' '));
    printf(" |       %c     \n", (erros >= 2 ? '|' : ' '));
    printf(" |      %c %c   \n", (erros >= 4 ? '/' : ' '), (erros >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");


    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");

}

// Procedimento de Ler e Armazenar o chute no array chutes
void chuta() {

    char chute;
    printf("Qual letra? ");
    scanf(" %c", &chute);

    chutes[(chutesdados)] = chute;
    chutesdados++;
}

// Funcao que Compara o caractere que entrar (ou letra) com os caracteres do array dos chutes
int jachutou(char letra) {

    int achou = 0;
    for(int j = 0; j < chutesdados; j++) {
        if(chutes[j] == letra) {
            achou = 1;
            break;
        }
    }

    return achou;
}

/* Funcao que percorre o array de chutes e o array da palavra secreta comparando caracter por caracter
e contabiliza se nao existir nenhum char no chutes que seja igual a um no palavrasecreta */
int contaerros(){

    int erros = 0;

	for(int i = 0; i < chutesdados; i++) {

		int existe = 0;

		for(int j = 0; j < strlen(palavrasecreta); j++) {
			if(chutes[i] == palavrasecreta[j]) {
				existe = 1;
				break;
			}
		}

		if(!existe) erros++;
	}

    return erros;
}

// Funcao que retorna se o jogador perdeu o jogo (errou 5 vezes)
int enforcou() {

	return contaerros() >= 5;
}

/* Funcao que retorna se o jogador ganhou o jogo (compara letra a letra da palavra secreta com os chutes,
se todas tiverem uma correspondencia o jogador ganha) */
int ganhou() {

	for(int i = 0; i < strlen(palavrasecreta); i++) {

		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}
	}

	return 1;
}

// Funcao para repetir o jogo (repete se o jogador inserir 'S' no fim do jogo)
int repetirjogo() {

    chutesdados = 0;

    char quer;
    printf("\nVoce gostaria de jogar de novo? (S-N)\n");
    scanf(" %c", &quer);

    if (quer == 'S') {
        return 1;
    }

    return 0;
}

// Procedimento para adicionar uma nova palavra ao banco de dados do jogo ("palavras.txt")
void adicionarpalavra() {

    char quer;
    printf("Voce deseja adicionar uma nova palavra? (S/N)\n");
    scanf(" %c", &quer);

    if (quer == 'S'){

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual nova palavra?\n");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.txt", "r+");  // Ler e Escrever

        if (f == 0){
            printf("Desculpe, nao eh possivel acessar o banco de dados.");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);  // Volta para o inicio do arquivo e imprime nova quantidade de palavras
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);  // Volta para o fim do arquivo e imprime a nova palavra
        fprintf(f, "\n%s", novapalavra);


        fclose(f);
    }

}


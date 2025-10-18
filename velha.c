#include <stdio.h>
#include <stdlib.h>


void desenhaTabuleiro(char tabuleiro[3][3]) {
{
        #ifdef _WIN32
             system("cls");
        #else        
             system("clear");
        #endif
        
        printf("\n");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf(" %c ", tabuleiro[i][j]);
                if (j < 2) {
                    printf("|");
                }
            }
            printf("\n");
            if (i < 2) {
                printf("---+---+---\n");
            }
        }
        printf("\n");
        }    
    }
    printf("\n");
}

char jogar(char tabuleiro[3][3], int posição, char jogadorAtual) {
    int linha = (posição - 1) / 3;
    int coluna = (posição - 1) % 3;

    if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
        tabuleiro[linha][coluna] = jogadorAtual;
        return 1;


    }
    return 0;
}

char verificaVitoria(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) {
            return 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) {
            return 1;
        }
    }

    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {
        return 1;
    }

    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    char tabuleiro[3][3] = {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
    };

    int jogada = 0;
    int posição;

    while (jogada < 9) {
        desenhaTabuleiro(tabuleiro);
        
        printf("Jogador %c, escolha uma posição (1-9): ", (jogada % 2 == 0) ? 'X' : 'O');
        scanf("%d", &posição);

        if (posição < 1 || posição > 9) {
            printf("Posição invalida! Escolha um numero entre 1 e 9.\n");
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
            continue;
        }

        char jogadorAtual = (jogada % 2 == 0) ? 'X' : 'O';
        if (!jogar(tabuleiro, posição, jogadorAtual)) {
            printf("Posição ja ocupada! Tente novamente\n");
            printf("Pressione Enter para continuar...");
            getchar();
            getchar();
            continue;
        }

        if (verificaVitoria(tabuleiro)) {
            desenhaTabuleiro(tabuleiro);
            printf("Jogador %c venceu!!!\n", jogadorAtual);
            break;
        }

        jogada++;
    }

    if (jogada == 9) {
        system("clear");
        desenhaTabuleiro(tabuleiro);
        printf("Empate!!!\n");
    }

    printf("Fim do jogo! Pressione Enter para sair...\n");
    getchar();
    getchar();
    
    return 0;
}
    
    return 0;

}


  printf("Você falhou! Pressione SPACE para reiniciar o jogo...\n");

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// INÍCIO DO JOGO DA SOMA! 
// O objetivo do jogo é o Jogador 1 tentar fazer a maior soma nas linhas enquanto o Jogador 2 tenta fazer a maior soma nas colunas


// antes de começarmos quero detalhar que aqui em cima esta a parte estrutural do jogo, onde eh exibido
// la em baixo esta a parte por tras do jogo, com os calculos e codigos para menu e regras
// explicado isso, vamos começar


int menu();
int regras();
int exibirTabuleiro(int tabuleiro[6][6], int somaLinhas[6], int somaColunas[6]);
int posicaoValida(int linha, int coluna, int tabuleiro[6][6]);
int atualizarSomas(int tabuleiro[6][6], int somaLinhas[6], int somaColunas[6]);
int vencedor(int somaLinhas[6], int somaColunas[6]);



// Agora vamos explicar cada vari[avel, prof
// menu: mostra as opções do jogo (Iniciar, Regras, Sair)
// regras: explica como jogar
// exibirTabuleiro: mostra o tabuleiro e as somas
// posicaoValida: verifica se a posição no tabuleiro está livre e é válida para colocar o valor da soma
// atualizarSomas: calcula as somas das linhas e colunas para cada jogador
// vencedor: determina o vencedor

int main()
{
    // Aqui, nós colocamos um loop para o jogador decidir o que quer fazer, sendo 1 para iniciar o jogo e logo em seguida quebra o loop
    // 2 para regras e volta para o loop e 3 para sair do jogo e fechar o código
    system("cls");
    while (1)
    {
        int opcao = menu();

        if (opcao == 1)
        {
            printf("\n=== Iniciando o Jogo ===\n");
            system("cls");
            break; 
            
        }
        else if (opcao == 2)
        {
            system("cls");
            regras(); // Mostra as regras
            miniMenu();
        }
        else if (opcao == 3)
        {
            printf("Ah,que pena...\n");
            system("cls");
        }
        else
        {
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    // Se a escolha for 1, continuamos por aqui o nosso código que consiste em determinar o valor de todas
    // as variáveis necessárias, como cada casa do tabuleiro, as somas de linhas e colunas
    // O jogador inicial sendo o jogador 1 e a quantidade de números utilizados

    int tabuleiro[6][6] = {0};
    int somaLinhas[6] = {0}, somaColunas[6] = {0};
    int jogadorAtual = 1, linha, coluna, numerosUsados = 0, numeroSorteado;

    // Aqui colocamos um gerador de números aleatórios, pois sem ela, o gerador usaria o mesmo ponto de partida
    // Ou seja, toda vez que o programa fosse executado, resultaria nos mesmos números aleatórios em cada execução

    srand(time(NULL));

    while (numerosUsados < 36)
    {
        exibirTabuleiro(tabuleiro, somaLinhas, somaColunas);

        // Toda vez que o loop for executado, essa função acima: exibirTabuleiro(tabuleiro, somaLinhas, somaColunas) 
        // atualiza a exibição do estado atual do jogo, podendo assim acompanhar o progresso da partida

        printf("Vez do Jogador %d.\n", jogadorAtual);
        numeroSorteado = rand() % 100 + 1;
        printf("O numero sorteado foi: %d\n", numeroSorteado);

        // A função rand() retorna um número aleatório gerado pelo sistema
        // Esse número é um valor inteiro grande e pode ser positivo ou negativo e por isso utilizamos o %100 pois aí pega 
        // os decimais finais como resto da divisão, e para ter números entre 1 e 100, precisamos colocar o + 1
        // fizemos sem esse mais um e gerava o número 0, coisa que não queríamos
        // ficando 1 a 100 ao invés de 0 a 99

        while (1)
        {
            printf("Em qual posicao deseja colocar seu numero?\nObs: escreva respectivamente a linha e coluna somente com o espaco.\n ");
            scanf("%d %d", &linha, &coluna);

            linha--; 
            coluna--;

            // Verifica se a posição é válida para ser colocada o número
            if (posicaoValida(linha, coluna, tabuleiro))
            {
                break; // Sai do loop se a posição for válida
            }
            else
            {
                printf("Posicao invalida! Verifica se esta vazia e dentro do tabuleiro.\n");
            }
        }

        // Atualiza o tabuleiro e soma após posição válida
        tabuleiro[linha][coluna] = numeroSorteado;
        // Aqui, o número sorteado é colocado na posição escolhida pelo jogador no tabuleiro
        // linha e coluna mostram onde esse número será colocado no tabuleiro
        atualizarSomas(tabuleiro, somaLinhas, somaColunas);
        // Depois de colocar o número no tabuleiro, tem que ser atualizadas as somas das linhas e colunas

        // Alterna o jogador
        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
        // Aqui, se o jogadorAtual for o jogador 1, ele vai para o jogador 2, e assim vice-versa
        // Usamos o operador ternário (? :), não sabíamos dele e estávamos utilizando outro loop
        // O que causava conflito, daí pesquisamos e esse operador faz uma verificação rápida, tipo: se o jogador atual for o 1, então passa para o 2, senão passa para o 1

        numerosUsados++;
        system("cls");
        // Aqui é para indicar que mais um número foi sorteado e colocado no tabuleiro
    }

    exibirTabuleiro(tabuleiro, somaLinhas, somaColunas);
    vencedor(somaLinhas, somaColunas);

    return 0;
}

// a variavel exibirmenu e regras pede exatamente o codigo que colocamos abaixo
// o pq de fazer separado eh como se fossemos utilizar o void, para armazenar essa linha de codigo e colocar ela em outro lugar
// ou seja, deixa o mecanismo do codigo para uma possivel atualizacao com uma forma mais "clean"

int menu()
{
    int opcao;
    printf("========       Trabalho Jogo da Soma     ==========\n");
    printf("========   Bianca Sabka e Magnum Abreu     ========\n");
    printf("=== 1 - Iniciar Jogo                       ========\n");
    printf("=== 2 - Regras do Jogo                     ========\n");
    printf("=== 3 - Sair                               ========\n");
    printf("===================================================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    return opcao;
}


int regras()
{
    printf("\n========== Regras do Jogo ==========\n");
    printf("1. O tabuleiro tem dimensao 6x6.\n");
    printf("2. O Jogador 1 joga com as LINHAS e o Jogador 2 com as COLUNAS.\n");
    printf("3. Cada numero sorteado (1 a 100) so pode ser usado uma vez.\n");
    printf("4. Vence quem tiver a maior soma em uma linha (Jogador 1) ou coluna (Jogador 2).\n");
    printf("5. Em caso de empate, nao tera vencedor.\n");
    printf("====================================\n\n");
    return 0;
}

int miniMenu()
{
    int opcao;
    while(1)
    {
        printf("\nDigite 1 para voltar ao menu inicial:\n");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            system("cls");
            return 0;
        }
        else
        {
            printf("Opcao invalida! Tente novamente.\n");
            return miniMenu();
        }
    }
}

int exibirTabuleiro(int tabuleiro[6][6], int somaLinhas[6], int somaColunas[6])

// lembrando antes que i e j, são respectivamente linha e coluna, igual na matematica
// aqui estamos declarando oq acontece no exibir tabuleiro e as somas


{
    printf("   ");
    for (int i = 0; i < 6; i++)
        printf("%2d ", i + 1);
    printf(" Soma\n");

    // aqui em cima peço para imprimir o "nada" nas posicoes numeradas de 1 a 6, seguidas de uma palavra "Soma".

    for (int i = 0; i < 6; i++)
    {
        printf("%2d ", i + 1);
        for (int j = 0; j < 6; j++)
        {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("%3d\n", somaLinhas[i]);
    }

    // aqui em cima ela imprime as linhas do tabuleiro. Então, para cada linha, ela imprime os números das casas da linha, seguidos pela soma dessa linha.

    printf("Soma ");
    for (int j = 0; j < 6; j++)
    {
        printf("%2d ", somaColunas[j]);
    }
    printf("\n\n");

    // imprime a soma de cada coluna no final do tabuleiro.

    return 0;
}

int posicaoValida(int linha, int coluna, int tabuleiro[6][6])
{
    return (linha >= 0 && linha < 6 && coluna >= 0 && coluna < 6 && tabuleiro[linha][coluna] == 0) ? 1 : 0;
}
//linha >= 0 && linha < 6: verifica se a linha está dentro dos limites de 0 a 5
//coluna >= 0 && coluna < 6: verifica se a coluna está dentro dos limites de 0 a 5
//tabuleiro[linha][coluna] == 0: verifica se a casa está vazia com o valor 0
// Essa parte é para garantir que o jogador não coloque números para fora do tabuleiro ou em posições já usadas anteriormente
// Se todas as condições forem verdadeiras, retorna 1 (verdadeiro), indicando que a posição é válida para prosseguimento do jogo
// caso contrário, retorna 0 (inválida). Por isso a utilizacao da funcao return

int atualizarSomas(int tabuleiro[6][6], int somaLinhas[6], int somaColunas[6])
{
    for (int i = 0; i < 6; i++)
        somaLinhas[i] = 0;
    for (int j = 0; j < 6; j++)
        somaColunas[j] = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            somaLinhas[i] += tabuleiro[i][j];
            somaColunas[j] += tabuleiro[i][j];
        }
    }
    // Isso garante que as somas de cada linha e coluna sempre estejam corretamente calculadas para cada casa sucessivamente, por isso o +=
    return 0;
}

int vencedor(int somaLinhas[6], int somaColunas[6])
{
    int maiorLinha = 0, maiorColuna = 0;

    // depois de iniciar as variaveis, o codigo vai percorrer as somas das linhas e das cokucas
    // e com isso encontrrar a maior soma e assim autilizar as variaveis, como vou fazer aqui em baixo
    // utilizei a logica de maior e menor que usamos em sala de aula, mas ja dando o valor pedido

    for (int i = 0; i < 6; i++)
    {
        if (somaLinhas[i] > maiorLinha)
            maiorLinha = somaLinhas[i];
        if (somaColunas[i] > maiorColuna)
            maiorColuna = somaColunas[i];
    }

    // Após isso, compara qual soma é maior
    // Se a maior soma for de uma linha, o Jogador 1 vence
    // Se for de uma coluna, o Jogador 2 vence
    // Se as somas forem iguais, há um empate

    if (maiorLinha > maiorColuna)
    {
        printf("O Jogador 1 venceu com a maior soma de linha: %d\n", maiorLinha);
    }
    else if (maiorColuna > maiorLinha)
    {
        printf("O Jogador 2 venceu com a maior soma de coluna: %d\n", maiorColuna);
    }
    else
    {
        printf("Empate!\n");
    }

    // terminamos aqui nosso código, fazendo as comparações necessarias para determinar o vencedor.
    // Vlw, prof!!! Um beijo da Bianca e do Magnum, hehhee! 
    return 0;
}

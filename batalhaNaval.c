#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para abs()

// Constantes para o tabuleiro
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Constantes para as matrizes de habilidade
#define TAMANHO_HABILIDADE 5
#define CENTRO_HABILIDADE 2 // (5-1)/2 = 2

// Protótipos das funções
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int orientacao);
void gerar_matriz_habilidade(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int tipo_habilidade);
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int centro_linha, int centro_coluna);

// Definições de Orientação para Navios (do Desafio Aventureiro)
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL_PRINCIPAL 2 // linha++, coluna++
#define DIAGONAL_SECUNDARIA 3 // linha++, coluna--

// Definições de Tipo de Habilidade
#define CONE 0
#define CRUZ 1
#define OCTAEDRO 2

/**
 * @brief Função principal que executa o Desafio Mestre de Batalha Naval.
 * O programa posiciona navios e demonstra a sobreposição de três habilidades.
 */
int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);

    // -------------------------------------------------------------------------
    // 1. Posicionamento de Navios (Reutilizando lógica do Aventureiro)
    // -------------------------------------------------------------------------
    // Navio 1: Horizontal (1, 1)
    if (posicionar_navio(tabuleiro, 1, 1, HORIZONTAL)) {
        printf("Navio 1 (Horizontal) posicionado com sucesso em (1, 1).\n");
    } else {
        printf("Falha ao posicionar Navio 1.\n");
    }

    // Navio 2: Vertical (5, 5)
    if (posicionar_navio(tabuleiro, 5, 5, VERTICAL)) {
        printf("Navio 2 (Vertical) posicionado com sucesso em (5, 5).\n");
    } else {
        printf("Falha ao posicionar Navio 2.\n");
    }

    // Navio 3: Diagonal Principal (0, 0) - Falha por sobreposição com Navio 1
    if (posicionar_navio(tabuleiro, 0, 0, DIAGONAL_PRINCIPAL)) {
        printf("Navio 3 (Diagonal Principal) posicionado com sucesso em (0, 0).\n");
    } else {
        printf("Falha ao posicionar Navio 3 (Esperado, pois colide com Navio 1).\n");
    }

    // Navio 4: Diagonal Secundária (7, 2)
    if (posicionar_navio(tabuleiro, 7, 2, DIAGONAL_SECUNDARIA)) {
        printf("Navio 4 (Diagonal Secundária) posicionado com sucesso em (7, 2).\n");
    } else {
        printf("Falha ao posicionar Navio 4.\n");
    }

    // -------------------------------------------------------------------------
    // 2. Criação e Sobreposição das Habilidades
    // -------------------------------------------------------------------------
    int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // Habilidade 1: Cone (Centrada em 2, 7)
    gerar_matriz_habilidade(matriz_habilidade, CONE);
    sobrepor_habilidade(tabuleiro, matriz_habilidade, 2, 7);
    printf("\nHabilidade Cone (5x5) sobreposta com centro em (2, 7).\n");

    // Habilidade 2: Cruz (Centrada em 7, 1)
    gerar_matriz_habilidade(matriz_habilidade, CRUZ);
    sobrepor_habilidade(tabuleiro, matriz_habilidade, 7, 1);
    printf("Habilidade Cruz (5x5) sobreposta com centro em (7, 1).\n");

    // Habilidade 3: Octaedro (Centrada em 4, 4)
    gerar_matriz_habilidade(matriz_habilidade, OCTAEDRO);
    sobrepor_habilidade(tabuleiro, matriz_habilidade, 4, 4);
    printf("Habilidade Octaedro (5x5) sobreposta com centro em (4, 4).\n");

    // -------------------------------------------------------------------------
    // 3. Exibição do Tabuleiro
    // -------------------------------------------------------------------------
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Inicializa o tabuleiro com AGUA (0).
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Tenta posicionar um navio no tabuleiro (Lógica do Aventureiro).
 */
bool posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha_inicial, int coluna_inicial, int orientacao) {
    int i;
    int dl = 0;
    int dc = 0;

    switch (orientacao) {
        case HORIZONTAL: dc = 1; break;
        case VERTICAL: dl = 1; break;
        case DIAGONAL_PRINCIPAL: dl = 1; dc = 1; break;
        case DIAGONAL_SECUNDARIA: dl = 1; dc = -1; break;
        default: return false;
    }

    // Validação de Limites e Sobreposição
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        int linha_atual = linha_inicial + i * dl;
        int coluna_atual = coluna_inicial + i * dc;

        if (linha_atual < 0 || linha_atual >= TAMANHO_TABULEIRO ||
            coluna_atual < 0 || coluna_atual >= TAMANHO_TABULEIRO ||
            tabuleiro[linha_atual][coluna_atual] == NAVIO) {
            return false;
        }
    }

    // Posicionamento
    for (i = 0; i < TAMANHO_NAVIO; i++) {
        int linha_atual = linha_inicial + i * dl;
        int coluna_atual = coluna_inicial + i * dc;
        tabuleiro[linha_atual][coluna_atual] = NAVIO;
    }

    return true;
}

/**
 * @brief Gera a matriz de habilidade (5x5) de forma dinâmica.
 * Requisito: Utilizar condicionais dentro de loops aninhados.
 */
void gerar_matriz_habilidade(int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int tipo_habilidade) {
    int i, j;
    int centro = CENTRO_HABILIDADE; // 2

    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz_habilidade[i][j] = AGUA; // Inicializa com 0

            switch (tipo_habilidade) {
                case CONE:
                    // Cone apontando para baixo (triângulo)
                    // A linha (i) define a largura. A largura é 2*i + 1, centrada em 'centro'
                    if (i >= 0 && i <= centro) {
                        int largura = i; // 0, 1, 2
                        if (j >= centro - largura && j <= centro + largura) {
                            matriz_habilidade[i][j] = 1;
                        }
                    }
                    break;

                case CRUZ:
                    // Linha central (i=2) ou Coluna central (j=2)
                    if (i == centro || j == centro) {
                        matriz_habilidade[i][j] = 1;
                    }
                    break;

                case OCTAEDRO:
                    // Losango (Manhattan distance)
                    // |i - centro| + |j - centro| <= centro
                    if (abs(i - centro) + abs(j - centro) <= centro) {
                        matriz_habilidade[i][j] = 1;
                    }
                    break;
            }
        }
    }
}

/**
 * @brief Sobrepõe a matriz de habilidade ao tabuleiro.
 * Requisito: Utilizar condicionais para garantir que a área de efeito permaneça dentro dos limites.
 */
void sobrepor_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int matriz_habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int centro_linha, int centro_coluna) {
    int i, j;
    int offset = CENTRO_HABILIDADE;

    for (i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (matriz_habilidade[i][j] == 1) {
                // Calcula a posição no tabuleiro
                int tab_linha = centro_linha + (i - offset);
                int tab_coluna = centro_coluna + (j - offset);

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (tab_linha >= 0 && tab_linha < TAMANHO_TABULEIRO &&
                    tab_coluna >= 0 && tab_coluna < TAMANHO_TABULEIRO) {

                    // Marca a posição com o valor da habilidade (5),
                    // mas apenas se não for um navio (para não sobrescrever o navio)
                    if (tabuleiro[tab_linha][tab_coluna] != NAVIO) {
                        tabuleiro[tab_linha][tab_coluna] = HABILIDADE;
                    }
                }
            }
        }
    }
}

/**
 * @brief Exibe o tabuleiro no console, usando caracteres para clareza.
 * Requisito: Utilizar caracteres diferentes para Água (0), Navio (3) e Habilidade (5).
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int i, j;

    printf("\n--- Tabuleiro de Batalha Naval (10x10) - Desafio Mestre ---\n");
    // Imprime o cabeçalho das colunas
    printf("   ");
    for (j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf(" %d", j);
    }
    printf("\n");

    for (i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Imprime o cabeçalho das linhas
        printf("%2d ", i);
        for (j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo;
            switch (tabuleiro[i][j]) {
                case AGUA:
                    simbolo = '~'; // Água
                    break;
                case NAVIO:
                    simbolo = '#'; // Navio
                    break;
                case HABILIDADE:
                    simbolo = 'X'; // Área de Efeito
                    break;
                default:
                    simbolo = '?';
            }
            printf(" %c", simbolo);
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------\n");
}

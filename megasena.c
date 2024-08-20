#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TEIMOSINHAS 8

struct megasena {
    int numeros[6];
};

typedef struct megasena MEGA[MAX_TEIMOSINHAS];

int QD() { // Quantidade de Dezenas
    int a;
    printf("Digite quantas dezenas ira apostar\n");
    printf("(valores possiveis: 6 a 15):\n"); 
    scanf("%d", &a);

    if(a >= 6 && a <= 15){
        printf("Preenchido com sucesso\n\n");
        return a;
    } else {
        printf("\n\nescolha um valor correto para quantidade de dezenas\n\n");
        return QD();
    }
}

int QM() { // Quantidade de apostas Manuais 
    int a;
    printf("Digite quantas apostas manuais ira fazer\n");
    printf("(valores possiveis: 0 a 3):\n"); 
    scanf("%d", &a);

    if(a >= 0 && a <= 3){
        printf("Preenchido com sucesso\n\n");
        return a;
    } else {
        printf("\n\nescolha um valor correto para quantidade de apostas manuais\n\n");
        return QM();
    }
}

int QS() { // Quantidade de surpresinhas
    int a;
    printf("Digite a quantidade de surpresinhas que deseja apostar\n");
    printf("(valores possíveis: 0 a 7):\n");
    scanf("%d", &a);

    if(a >= 0 && a <= 7){
        printf("Preenchido com sucesso\n\n");
        return a;
    } else {
        printf("\n\nescolha um valor correto para quantidade de apostas surpresinhas\n\n");
        return QS();
    }
}

int QT() { // Quantidade de teimosinhas
    int a;
    printf("Digite a quantidade de teimosinhas\n"); 
    printf("(concursos que deseja participar com as mesmas apostas. Valores validos: 1, 2, 4, 8):\n");
    scanf("%d", &a);

    if(a == 1 || a == 2 || a == 4 || a == 8){
        printf("Preenchido com sucesso\n\n");
        return a;
    } else {
        printf("\n\nescolha um valor correto para quantidade de teimosinhas\n\n");
        return QT();
    }
}

float VD(int v) {
    int valores[10][2] = {
        {6, 5}, {7, 35}, {8, 140}, {9, 420}, {10, 1050}, 
        {11, 2310}, {12, 4620}, {13, 8580}, {14, 15015}, {15, 25025}
    };
    return valores[v-6][1];
}

float premios(int d, int a, int *senas, int *quinas, int *quadras) {
    float mega[3] = {118265926.76 , 32797.02 , 834.93};

    if(a == 4) {
        printf("QUADRA!\n");
        int quadra1[10] = {1,3,6,10,15,21,28,36,45,55};
        *quadras = quadra1[d-6];
        printf("Premios: %d quadras.\n\n", *quadras);
    } else if(a == 5) {
        printf("QUINA!\n");
        int quadra2[10] = {0,5,15,30,50,75,105,140,180,225};
        int quina1[10] = {1,2,3,4,5,6,7,8,9,10};
        *quadras = quadra2[d-6];
        *quinas = quina1[d-6];
        printf("Premios: %d quadras , %d quinas.\n\n", *quadras, *quinas);
    } else if(a == 6) {
        printf("SENA!\n");
        int quadra3[10] = {0,0,15,45,90,150,225,315,420,540};
        int quina2[10] = {0,6,12,18,24,30,36,42,48,54};
        *quadras = quadra3[d-6];
        *quinas = quina2[d-6];
        *senas = 1;
        printf("Premios: %d quadras , %d quinas , %d senas.\n\n", *quadras, *quinas, *senas);
    }

    return (*senas * mega[0]) + (*quinas * mega[1]) + (*quadras * mega[2]);
}

void AM(int n, int q, int **m) { // Apostas Manuais
    if (n > 0) {
        for(int i = 0; i < n; i++) {
            printf("Escreva os valores da %d aposta com %d dezenas\n\n", i+1, q);
            printf("(valores entre 1 e 60):\n");
            for(int j = 0; j < q; j++) {
                int num;
                int unique;
                do {
                    unique = 1;
                    printf("Escreva o %d numero\n", j+1);
                    scanf("%d", &num);

                    if (num < 1 || num > 60) {
                        printf("Numero fora do intervalo permitido. Digite um numero entre 1 e 60.\n");
                        unique = 0;
                        continue;
                    }

                    for(int k = 0; k < j; k++) {
                        if (m[i][k] == num) {
                            unique = 0;
                            printf("Numero repetido. Digite um número diferente.\n");
                            break;
                        }
                    }
                } while (!unique);
                m[i][j] = num;
            }
        }
    } else {
        printf("Você não fez apostas manuais\n");
    }
}

void AS(int n, int d, int **m) { // Aposta Surpresinha

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < d; j++) {
            int num;
            int unique;
            do {
                unique = 1;
                num = (rand() % 60) + 1; // Gera um número aleatório entre 1 e 60
                for (int k = 0; k < j; k++) {
                    if (m[i][k] == num) {
                        unique = 0;
                        break;
                    }
                }
            } while (!unique);
            m[i][j] = num;
        }
    }
}

void megaS(MEGA resultados, int q_teimosinhas) { // Sorteia os números premiados
    
    for(int k = 0; k < q_teimosinhas; k++){     
        for(int i = 0; i < 6; i++) {
            int num;
            int unique;
            do {
                unique = 1;
                num = (rand() % 60) + 1;
                for (int j = 0; j < i; j++) {
                    if (resultados[k].numeros[j] == num) {
                        unique = 0;
                        break;
                    }
                }
            } while (!unique);
            resultados[k].numeros[i] = num;
        }
    }
}

void acertos(MEGA resultados, int **manuais, int **surpresinhas, int q_manuais, int q_surpresinhas, int q_dezenas, int *certo_m, int *certo_s, int concurso) { // Ver os acertos  
    for(int i = 0; i < q_manuais; i++) { // Inicializar a função para contar os acertos de apostas manuais
        certo_m[i] = 0;
    }
    for(int i = 0; i < q_surpresinhas; i++) { // Inicializar a função para contar os acertos de apostas surpresinhas
        certo_s[i] = 0;
    }

    for(int i = 0; i < q_manuais; i++) { // Conferir os acertos das apostas manuais
        for(int j = 0; j < 6; j++) {
            for(int k = 0; k < q_dezenas; k++) {
                if (resultados[concurso].numeros[j] == manuais[i][k]) {
                    certo_m[i]++;
                }
            }
        }
    }

    for(int i = 0; i < q_surpresinhas; i++) { // Conferir os acertos das apostas surpresinhas
        for(int j = 0; j < 6; j++) {
            for(int k = 0; k < q_dezenas; k++) {
                if (resultados[concurso].numeros[j] == surpresinhas[i][k]) {
                    certo_s[i]++;
                }
            }
        }
    }    
}

void ImprimirMega(MEGA resultados, int q_teimosinhas, int concurso) {
    printf("\n\nDezenas sorteadas no concurso %d:\n", concurso + 1);
    for(int i = 0; i < 6; i++) {
        printf(" %d ", resultados[concurso].numeros[i]);
    }
    printf("\n");
}

void imprimir(int **manuais, int **surpresinhas, int *acerto_m, int *acerto_s, MEGA resultados, int q_dezenas, int q_manuais, int q_surpresinhas, int q_teimosinhas, float valor) {
    for(int i = 0; i < q_manuais; i++) { // Imprimir as apostas manuais
        printf("\n\nAposta %d (manual):\n", i+1);
        for(int j = 0; j < q_dezenas; j++) {
            if(manuais[i][j] < 10) {
                printf(" 0%d ", manuais[i][j]);
            } else {
                printf(" %d ", manuais[i][j]);
            }
        }
    }

    for(int i = 0; i < q_surpresinhas; i++) { // Imprimir as apostas surpresinhas
        printf("\n\nAposta %d (surpresinha):\n", i+1);
        for(int j = 0; j < q_dezenas; j++) {
            if(surpresinhas[i][j] < 10) {
                printf(" 0%d ", surpresinhas[i][j]);
            } else {
                printf(" %d ", surpresinhas[i][j]);
            }
        }
    }

    printf("\n\nTeimosinhas: %d\n\n", q_teimosinhas); // Quantidade de teimosinhas

    printf("Valor total das apostas:\n"); // Preço
    printf("%.2f\n", valor);

    char resposta;
    printf("\n\nDeseja continuar (S/N)?\n");
    getchar(); // Consumir o newline residual
    scanf("%c", &resposta);

    if(resposta == 'N' || resposta == 'n') {
        printf("Obrigado por participar das Loterias Caixa.\n");
    } 
    else if(resposta == 'S' || resposta == 's') {
        int num_premios = 0;
        float premio[100] = {0}; // Supondo no máximo 100 prêmios

        for(int k = 0; k < q_teimosinhas; k++) {
            printf("\n\nConcurso 000%d\n", k+1);
            
            // Atualizar acertos para o novo sorteio
            acertos(resultados, manuais, surpresinhas, q_manuais, q_surpresinhas, q_dezenas, acerto_m, acerto_s, k);

            if(q_manuais > 0) { 
                for(int i = 0; i < q_manuais; i++) {
                    int senas = 0, quinas = 0, quadras = 0;
                    printf("Aposta %d: %d/6 acertos\n\n", i+1, acerto_m[i]);
                    premio[num_premios] = premios(q_dezenas, acerto_m[i], &senas, &quinas, &quadras);
                    num_premios++;
                }
            }
            if(q_surpresinhas > 0) { 
                for(int i = 0; i < q_surpresinhas; i++) {
                    int senas = 0, quinas = 0, quadras = 0;
                    printf("Aposta %d: %d/6 acertos\n\n", i+1, acerto_s[i]);
                    premio[num_premios] = premios(q_dezenas, acerto_s[i], &senas, &quinas, &quadras);
                    num_premios++;
                }
            }

            ImprimirMega(resultados, q_teimosinhas, k); // Imprimir os números sorteados no concurso
        }

        printf("\n\ntotal da aposta:\n"); // Preço novamente
        printf("%.2f\n", valor);

        printf("\n\nTotal de premios:\n"); // preço total de ganhos 
        float s_premios = 0;
        for(int i = 0; i < num_premios; i++) {
            s_premios += premio[i];
        }
        printf("%.2f\n", s_premios);

        printf("\n\nValor liquido:\n"); // valor dos premios diminuido com os custos da aposta

        printf("%.2f\n", s_premios - valor);

        printf("\n\nObrigado por participar das Loterias Caixa.\n");
    }
}

int main() {
    srand(time(NULL));


    float valor;
    int quadras = 0, quinas = 0, senas = 0, q_d_certas;
    int q_dezenas, q_manuais, q_surpresinhas, q_teimosinhas, v_dezenas;

    q_dezenas = QD(); // Quantidade de dezenas
    v_dezenas = VD(q_dezenas); // Valor da escolha das dezenas
    q_manuais = QM(); // Quantidade de apostas manuais
    q_surpresinhas = QS(); // Quantidade de surpresinhas
    q_teimosinhas = QT(); // Quantidade de teimosinhas

    int **manuais = malloc(q_manuais * sizeof(int *));//aloca memoria para a funcao que armazena as apostas manuais
    for (int i = 0; i < q_manuais; i++) {
        manuais[i] = malloc(q_dezenas * sizeof(int));
    }

    int **surpresinhas = malloc(q_surpresinhas * sizeof(int *));//aloca memoria para a funcao que armazena as apostas do tipo surpresinha
    for (int i = 0; i < q_surpresinhas; i++) {
        surpresinhas[i] = malloc(q_dezenas * sizeof(int));
    }

    MEGA resultados;
    
    AM(q_manuais, q_dezenas, manuais); // Preenchimento das apostas manuais 
    AS(q_surpresinhas, q_dezenas, surpresinhas); // Preencher as surpresinhas

    // Sorteia os números premiados
    megaS(resultados, q_teimosinhas);

    int certo_m[q_manuais];
    int certo_s[q_surpresinhas];
    acertos(resultados, manuais, surpresinhas, q_manuais, q_surpresinhas, q_dezenas, certo_m, certo_s, 0); // Acertos em apostas manuais e surpresinhas
   
    valor = q_teimosinhas * (v_dezenas * (q_manuais + q_surpresinhas)); // Valor da aposta feita

    imprimir(manuais, surpresinhas, certo_m, certo_s, resultados, q_dezenas, q_manuais, q_surpresinhas, q_teimosinhas, valor); // Imprime tudo que foi feito 

    for (int i = 0; i < q_manuais; i++) { // libera memoria
        free(manuais[i]);
    }
    free(manuais);

    for (int i = 0; i < q_surpresinhas; i++) {// libera memoria 
        free(surpresinhas[i]);
    }
    free(surpresinhas);

    return 0;
}

#include <stdio.h>

#define MAX 5 

typedef struct {
    int dados[MAX];
    int topo;       
} Pilha;

void inicializar(Pilha *p) { p->topo = -1; }
int  vazia(Pilha *p)       { return p->topo == -1; }
int  cheia(Pilha *p)       { return p->topo == MAX - 1; }

int empilhar(Pilha *p, int valor) {
    if (cheia(p)) return 0;
    p->dados[++p->topo] = valor;
    return 1;
}

int desempilhar(Pilha *p, int *valor) {
    if (vazia(p)) return 0;
    *valor = p->dados[p->topo--];
    return 1;
}

int lerInt(const char *msg, int *v) {
    printf("%s", msg);
    if (scanf("%d", v) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

void alterar(Pilha *hist, int *valorAtual, int novo) {
    if (!empilhar(hist, *valorAtual)) {
        printf("Historico cheio: alteracao rejeitada. Valor atual mantido em %d.\n", *valorAtual);
        return;
    }
    printf("Valor alterado de %d para %d.\n", *valorAtual, novo);
    *valorAtual = novo;
}

void desfazer(Pilha *hist, int *valorAtual) {
    int anterior;
    if (!desempilhar(hist, &anterior)) {
        printf("Sem historico: nao e possivel desfazer.\n");
        return;
    }
    printf("Desfeito: %d -> %d.\n", *valorAtual, anterior);
    *valorAtual = anterior;
}

void consultar(Pilha *hist, int valorAtual) {
    printf("Valor atual: %d\n", valorAtual);
    if (vazia(hist)) { printf("Historico: (vazio)\n"); return; }
    printf("Historico (mais recente -> mais antigo): ");
    for (int i = hist->topo; i >= 0; i--) printf("%d ", hist->dados[i]);
    printf("\n");
}

int main(void) {
    Pilha hist;
    int valorAtual = 0, op, novo;
    inicializar(&hist);

    do {
        printf("\n1-Alterar valor 2-Desfazer 3-Consultar 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1: if (lerInt("Novo valor: ", &novo)) alterar(&hist, &valorAtual, novo); break;
            case 2: desfazer(&hist, &valorAtual); break;
            case 3: consultar(&hist, valorAtual); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}
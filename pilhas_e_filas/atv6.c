#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int inicio; 
    int fim;   
} Fila;

void inicializar(Fila *f) { f->inicio = 0; f->fim = 0; }
int  vazia(Fila *f)       { return f->inicio == f->fim; }
int  cheia(Fila *f)       { return f->fim == MAX; }

int lerInt(const char *msg, int *v) {
    printf("%s", msg);
    if (scanf("%d", v) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

void inserir(Fila *f, int valor) {
    if (cheia(f)) { printf("Fila cheia! Nao foi possivel inserir %d.\n", valor); return; }
    f->dados[f->fim++] = valor;
    printf("%d inserido.\n", valor);
}

void remover(Fila *f) {
    if (vazia(f)) { printf("Fila vazia! Nada a remover.\n"); return; }
    printf("%d removido.\n", f->dados[f->inicio++]);
}

void mostrar(Fila *f) {
    if (vazia(f)) { printf("Fila vazia.\n"); return; }
    printf("Fila (inicio -> fim): ");
    for (int i = f->inicio; i < f->fim; i++) printf("%d ", f->dados[i]);
    printf("\n");
}

void consultarInicio(Fila *f) {
    if (vazia(f)) { printf("Fila vazia: nao ha proximo elemento.\n"); return; }
    printf("Proximo elemento: %d\n", f->dados[f->inicio]);
}

int quantidade(Fila *f) { return f->fim - f->inicio; }

int main(void) {
    Fila f;
    int op, valor;
    inicializar(&f);

    do {
        printf("\n1-Inserir 2-Remover 3-Mostrar 4-Consultar proximo 5-Quantidade 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1: if (lerInt("Valor: ", &valor)) inserir(&f, valor); break;
            case 2: remover(&f); break;
            case 3: mostrar(&f); break;
            case 4: consultarInicio(&f); break;
            case 5: printf("Elementos aguardando: %d\n", quantidade(&f)); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}
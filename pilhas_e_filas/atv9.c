#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int inicio; 
    int fim;    
} Fila;

void inicializar(Fila *f) { f->inicio = 0; f->fim = 0; }
int  vazia(Fila *f)       { return f->fim == 0; }
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

int remover(Fila *f, int *valor) {
    if (vazia(f)) return 0;
    *valor = f->dados[0];
    for (int i = 1; i < f->fim; i++)   
        f->dados[i - 1] = f->dados[i];
    f->fim--;
    f->inicio = 0;
    return 1;
}

void mostrar(Fila *f) {
    if (vazia(f)) { printf("Fila vazia.\n"); return; }
    printf("Fila (inicio -> fim): ");
    for (int i = f->inicio; i < f->fim; i++) printf("%d ", f->dados[i]);
    printf(" [inicio=%d, fim=%d]\n", f->inicio, f->fim);
}

int main(void) {
    Fila f;
    int op, valor;
    inicializar(&f);

    do {
        printf("\n1-Inserir 2-Remover 3-Mostrar 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1: if (lerInt("Valor: ", &valor)) inserir(&f, valor); break;
            case 2:
                if (remover(&f, &valor)) printf("%d removido.\n", valor);
                else printf("Fila vazia! Nada a remover.\n");
                break;
            case 3: mostrar(&f); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}
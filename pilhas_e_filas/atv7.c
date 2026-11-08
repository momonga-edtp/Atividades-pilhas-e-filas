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

void gerarSenha(Fila *f, int *proximaSenha) {
    if (cheia(f)) {
        printf("Fila de atendimento cheia. Aguarde para retirar senha.\n");
        return;
    }
    f->dados[f->fim++] = *proximaSenha;
    printf("Senha %d gerada. Aguarde ser chamado.\n", *proximaSenha);
    (*proximaSenha)++;
}

void chamarProxima(Fila *f) {
    if (vazia(f)) { printf("Nenhuma senha aguardando atendimento.\n"); return; }
    printf(">>> Chamando senha %d <<<\n", f->dados[f->inicio++]);
}

void consultarProxima(Fila *f) {
    if (vazia(f)) { printf("Nenhuma senha aguardando atendimento.\n"); return; }
    printf("Proxima senha a ser chamada: %d\n", f->dados[f->inicio]);
}

void mostrarSenhas(Fila *f) {
    if (vazia(f)) { printf("Nenhuma senha aguardando atendimento.\n"); return; }
    printf("Senhas aguardando: ");
    for (int i = f->inicio; i < f->fim; i++) printf("%d ", f->dados[i]);
    printf("\n");
}

int main(void) {
    Fila f;
    int op, proximaSenha = 1;
    inicializar(&f);

    do {
        printf("\n=== Secretaria ===\n");
        printf("1-Gerar senha 2-Chamar proxima 3-Consultar proxima 4-Mostrar aguardando 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1: gerarSenha(&f, &proximaSenha); break;
            case 2: chamarProxima(&f); break;
            case 3: consultarProxima(&f); break;
            case 4: mostrarSenhas(&f); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}
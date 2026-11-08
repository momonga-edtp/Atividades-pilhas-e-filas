#include <stdio.h>

#define MAX 5

typedef struct {
    int dados[MAX];
    int topo;      
} Pilha;

void inicializar(Pilha *p) { p->topo = -1; }
int  vazia(Pilha *p)       { return p->topo == -1; }
int  cheia(Pilha *p)       { return p->topo == MAX - 1; }

int lerInt(const char *msg, int *v) {
    printf("%s", msg);
    if (scanf("%d", v) != 1) {
        int c; while ((c = getchar()) != '\n' && c != EOF) {}
        return 0;
    }
    return 1;
}

void adicionarBandeja(Pilha *p, int num) {
    if (cheia(p)) {
        printf("Suporte cheio (%d bandejas). Bandeja %d nao cabe.\n", MAX, num);
        return;
    }
    p->dados[++p->topo] = num;
    printf("Bandeja %d colocada no suporte.\n", num);
}

int retirarBandeja(Pilha *p, int *num) {
    if (vazia(p)) {
        printf("Nao ha bandejas disponiveis no momento.\n");
        return 0;
    }
    *num = p->dados[p->topo--];
    return 1;
}

void proximaBandeja(Pilha *p) {
    if (vazia(p)) { printf("Nao ha bandejas disponiveis no momento.\n"); return; }
    printf("Proxima bandeja disponivel: %d\n", p->dados[p->topo]);
}

void mostrarBandejas(Pilha *p) {
    if (vazia(p)) { printf("Suporte de bandejas vazio.\n"); return; }
    printf("Bandejas (topo -> base): ");
    for (int i = p->topo; i >= 0; i--) printf("%d ", p->dados[i]);
    printf("\n");
}

int main(void) {
    Pilha p;
    int op, num;
    inicializar(&p);

    do {
        printf("\n=== Lanchonete: suporte de bandejas ===\n");
        printf("1-Adicionar bandeja 2-Retirar bandeja 3-Proxima bandeja 4-Mostrar bandejas 0-Sair\n");
        if (!lerInt("Opcao: ", &op)) { op = -1; continue; }
        switch (op) {
            case 1:
                if (lerInt("Numero da bandeja: ", &num)) adicionarBandeja(&p, num);
                break;
            case 2:
                if (retirarBandeja(&p, &num)) printf("Bandeja %d retirada. Bom apetite!\n", num);
                break;
            case 3: proximaBandeja(&p); break;
            case 4: mostrarBandejas(&p); break;
            case 0: printf("Encerrando.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !feof(stdin));
    return 0;
}
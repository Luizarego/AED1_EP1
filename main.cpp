#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// elemento da lista
typedef struct estr {
	int valor;
   	struct estr* prox;
} NO;


NO* uniao(NO* p1, NO* p2);   //funcao principal, devolve resposta
NO* criarNo(int valor);   //cria e devolve um no
int estaVazio(NO* lista);   //verifica se a lista esta vazia
int buscaSeq(NO* p, int ch, NO** ant);   //busca sequencial, retorna 1 se achar e 0 se nao achar
int inserir(NO** p, int ch);   //insere elementos na lista
void mostrar(NO* p);   //exibe a lista na tela

NO* criarNo(int valor) {
	NO* novoNo = (NO*)malloc (sizeof (NO));
	if (novoNo) {
		novoNo->valor = valor;
		novoNo->prox = NULL;
	}
	return novoNo;
}

int estaVazio(NO* lista) {  //se a lista estiver vazia, retornaria falso. !lista retorna verdadeiro
	return !lista;
}

int buscaSeq(NO* p, int ch, NO** ant){  //ponteiro duplo guarda o valor do primeiro ponteiro, porque precisa alterar p
	NO* p1 = p;
    while (p1 != NULL) {
        if (p1->valor >= ch)
			break;
        *ant = p1;
        p1 = p1->prox;
    }

   	if (p1 && p1->valor == ch)
		return 1;
    return 0;
}

int inserir(NO** p, int ch) {

	NO* novo = criarNo(ch);

  	if(!*p) {
    	*p = novo;
    	return 1;
  	}

  	NO* ant = NULL;
  	int existeNaLista = buscaSeq (*p, ch, &ant);
  	if (!existeNaLista) {
		if (ant) {
    		novo->prox = ant->prox;
    		ant->prox = novo;
			return 1;
		}

		if ((*p)->valor < ch)
			(*p)->prox = novo;
		else {
			novo->prox = *p;
			*p = novo;
		}

    	return 1;
  	}
	return 0;
}

void mostrar(NO* p) {
	while (p) {
		printf ("%d ", p->valor);
		p = p->prox;
	}
	printf("\n");
}

NO* uniao(NO* p1, NO* p2) {

	NO* resp = NULL;

	NO* p1_atual = p1;
	NO* p2_atual = p2;

	while(p1_atual && p2_atual) {
		if(p1_atual->valor < p2_atual->valor) {
			inserir (&resp, p1_atual->valor);
			p1_atual = p1_atual->prox; continue;
		}

		if(p1_atual->valor > p2_atual->valor) {
			inserir (&resp, p2_atual->valor);
			p2_atual = p2_atual->prox; continue;
		}

		if(p1_atual->valor == p2_atual->valor) {
			inserir (&resp, p1_atual->valor);
			p1_atual = p1_atual->prox;
			p2_atual = p2_atual->prox;
		}
	}

	while(p1_atual) {
		inserir(&resp, p1_atual->valor);
		p1_atual = p1_atual->prox;
	}

	while(p2_atual) {
		inserir(&resp, p2_atual->valor);
		p2_atual = p2_atual->prox;
	}

	return resp;
}


int main() {

	NO* p1 = NULL;
	NO* p2 = NULL;

	inserir(&p1, 1);
	inserir(&p1, 4);
	inserir(&p1, 3);
	inserir(&p1, 2);

	mostrar(p1);

	inserir(&p2, 1);
	inserir(&p2, 4);
	inserir(&p2, 9);
	inserir(&p2, 8);
	inserir(&p2, 4);
	inserir(&p2, 6);
	inserir(&p2, 5);

	mostrar(p2);

	NO* teste = NULL;
	teste = uniao(p1,p2);
	mostrar(teste);
}

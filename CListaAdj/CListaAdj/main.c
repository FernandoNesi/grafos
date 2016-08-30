//
//  main.c
//  CListaAdj
//
//  Created by Fernando Nesi on 29/08/16.
//  Copyright © 2016 Fernando Nesi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct grafo{
//    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
}Grafo;


Grafo *cria_grafo(int nro_vertices, int grau_max);
void libera_grafo(Grafo* g);
int insere_aresta(Grafo* g, int orig, int dest);
int remove_aresta(Grafo* g, int orig, int dest, int eh_digrafo);
void buscaProfundidade_grafo(Grafo* g, int ini, int *visitado);
void buscaProfundidade(Grafo* g, int ini, int *visitado, int cont);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    
    
    Grafo *g;
    g = cria_grafo(5, 5);
    insere_aresta(g, 0, 1);
    insere_aresta(g, 1, 2);
    insere_aresta(g, 1, 3);
    insere_aresta(g, 2, 4);
    insere_aresta(g, 3, 0);
    insere_aresta(g, 3, 4);
    insere_aresta(g, 4, 1);
    int vis[5];
    
    buscaProfundidade_grafo(g, 0, vis);
    
    libera_grafo(g);
    return 0;
}

/**
 Busca em profundidade
 - Partindo de um vértico inicial, ela explora o máximo
 possível cada um dos seus ramos antes de retroceder ("backtracking")
 - Encontrar componentes conectados e fortemente conectados
 - Ordenação topológica de um grafo
 - Resolver quebra-cabeças (Ex: labirinto)
 */

void buscaProfundidade_grafo(Grafo* g, int ini, int *visitado){
    int cont = 1;
    for (int i = 0; i < g->nro_vertices; i++) {
        visitado[i] = 0;
    }
    buscaProfundidade(g, ini, visitado, cont);
}

void buscaProfundidade(Grafo* g, int ini, int *visitado, int cont){
    visitado[ini] = cont;
    printf("\n");
    for (int i = 0; i < g->grau[ini]; i++) {
        printf(" %d ", ini);
        if (!visitado[g->arestas[ini][i]]) {
            buscaProfundidade(g, g->arestas[ini][i], visitado, cont+1);
        }
        
    }
    printf("\n");
}

int remove_aresta(Grafo* g, int orig, int dest, int eh_digrafo){
    if (g == NULL) {
        return 0;
    }if (orig < 0 || orig >= g->nro_vertices) {
        return 0;
    }if (dest < 0 || dest >= g->nro_vertices) {
        return 0;
    }
    int i = 0;
    while (i < g->grau[orig] && g->arestas[orig][i] != dest) {
        i++;
    }if (i == g->grau[orig]) {//elemento não encontrado
        return 0;
    }
    g->grau[orig]--;
    g->arestas[orig][i]=g->arestas[orig][g->grau[orig]];
    if (eh_digrafo == 0) { //remove outra aresta se não for digrafo
        remove_aresta(g, dest, orig, 1);
    }
    
    return 1;
}

int insere_aresta(Grafo* g, int orig, int dest){
    if (g == NULL) {
        return 0;
    }if (orig < 0 || orig >= g->nro_vertices) {
        return 0;
    }if (dest < 0 || dest >= g->nro_vertices) {
        return 0;
    }
    g->arestas[orig][g->grau[orig]] = dest;
    g->grau[orig]++;
    
    return 1;
}

Grafo *cria_grafo(int nro_vertices, int grau_max){
    Grafo *g = (Grafo*) malloc(sizeof(struct grafo));
    if (g != NULL) {
        g->nro_vertices = nro_vertices;
        g->grau_max = grau_max;
        g->grau=(int*)calloc(nro_vertices,sizeof(int));
        g->arestas=(int**)malloc(nro_vertices*sizeof(int*));
        for (int i=0; i<nro_vertices; i++) {
            g->arestas[i]=(int*)malloc(grau_max*sizeof(int));
        }
    }
    return g;
}

void libera_grafo(Grafo* g){
    if (g != NULL) {
        for (int i=0; i<g->nro_vertices; i++) {
            free(g->arestas[i]);
        }
        free(g->arestas);
        free(g);
    }
}

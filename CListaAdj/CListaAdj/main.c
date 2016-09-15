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
void buscaProfundidade(Grafo* g, int ini, int *visitado, int dist);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    int NV;
    
    
    Grafo *piramide;
    piramide = cria_grafo(8, 8);
    insere_aresta(piramide, 0, 1);
    insere_aresta(piramide, 0, 3);
    insere_aresta(piramide, 0, 4);
    insere_aresta(piramide, 1, 2);
    insere_aresta(piramide, 1, 5);
    insere_aresta(piramide, 2, 3);
    insere_aresta(piramide, 2, 6);
    insere_aresta(piramide, 3, 7);
    insere_aresta(piramide, 4, 5);
    insere_aresta(piramide, 4, 7);
    insere_aresta(piramide, 5, 6);
    insere_aresta(piramide, 6, 7);
    int visPiramide[8];
    NV = 8;
    
    buscaProfundidade_grafo(piramide, 0, visPiramide);
    for (int i = 0; i < NV; i++){
        printf("[%d]", visPiramide[i]);
    }
    printf(" - visitados\n\n");
    for (int i = 0; i<NV; i++){
        for (int ii = 0; ii < NV; ii++) {
            if(visPiramide[ii]==i)
                printf("%d: (nível %d)\n",ii, visPiramide[ii]);
        }
    }
            
    
    printf("\n\nARVORE\n\n");
            
    Grafo *arvore;
    arvore = cria_grafo(8, 8);//(nro_vertices, grau_max)
    insere_aresta(arvore, 0, 1);//1
    insere_aresta(arvore, 0, 3);//2
    insere_aresta(arvore, 0, 6);//3
    insere_aresta(arvore, 1, 2);//4
    insere_aresta(arvore, 3, 4);//5
    insere_aresta(arvore, 4, 5);//6
    insere_aresta(arvore, 6, 7);//7
    int visArvore[8];
    NV = 8;
    
    buscaProfundidade_grafo(arvore, 0, visArvore);
    
    for (int i = 0; i < NV; i++){
        printf("[%d]", visArvore[i]);
    }
    printf(" - visitados\n\n");
    for (int i = 0; i<NV; i++){
        for (int ii = 0; ii < NV; ii++) {
            if(visArvore[ii]==i)
                printf("%d: (nível %d)\n",ii, visArvore[ii]);
        }
    }
    
    libera_grafo(piramide);
    libera_grafo(arvore);
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
    int dist = 1;
    for (int i = 0; i < g->nro_vertices; i++) {
        visitado[i] = 0;
    }
    buscaProfundidade(g, ini, visitado, dist);
}

void buscaProfundidade(Grafo* g, int ini, int *visitado, int dist){
    visitado[ini] = dist;
    printf("\n");
    for (int i = 0; i < g->grau[ini]; i++) {
        printf(" %d ", ini);
        if (!visitado[g->arestas[ini][i]]) {
            buscaProfundidade(g, g->arestas[ini][i], visitado, dist+1);
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
    g->arestas[orig][g->grau[orig]++] = dest;
    g->arestas[dest][g->grau[dest]++] = orig;
    
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

//cintura(Grafo G)
//    cintura = INFINITO;
//    para cada v em V(G) faça:
//        dist[v] = -1;
//    para cada v em V(G) faça:
//        se dist[v] == -1 faça:
//            pai[v] = v;
//            dist[v] = 0;
//            DFS(G, v)
//
//
//DFS(Grafo G, Vertive v)
//    para cada w vizinho de v faça:
//        se dist[w] == -1 faça:
//            pai[w] = v;
//            dist[w] = dist[v] + 1;
//            DFS(G, v)
//        senão
//            se w != pai[v] && cintura > (dist[v] - dist[w] + 1) faça:
//                cintura = (dist[v] - dist[w] + 1)




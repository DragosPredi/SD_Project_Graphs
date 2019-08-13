#include "header.h"

Graph initGraph(int size) {
	Graph g;
	int i;
	g = (Graph) malloc(sizeof(struct graph));
	g->size = size;
	g->adjLists = (List*) malloc(size * sizeof(List));
	for (i = 0; i < size; i++) {
		g->adjLists[i] = NULL;
	}
	g->visited = calloc(size, sizeof(int));
	return g;
}
Graph freeGraph(Graph g){
	int i;
	for(i = 0 ; i < g->size; i++)
		freeList(g->adjLists[i]);
	free(g->adjLists);
	free(g->visited);
	free(g);
	return NULL;
}
Graph insertEdge(Graph g, int u, int v) {
	if(isElement(g->adjLists[u], v) == 0)
	{
		g->adjLists[u] = addLast(g->adjLists[u], v);
		g->adjLists[v] = addLast(g->adjLists[v], u);
	}

	return g;
}

Graph insertEdgeWCost(Graph g, int u, int v, int cost)
{

	g->adjLists[u] = addLastWCost(g->adjLists[u], v, cost);
	g->adjLists[v] = addLastWCost(g->adjLists[v], u, cost);

	return g;	
}
/*Graph insertEdgeWCost(Graph g, int u, int v, int cost)
{
	if(isElement(g->adjLists[u], v) == 0)
	{
		g->adjLists[u] = addLastWCost(g->adjLists[u], v, cost);
		g->adjLists[v] = addLastWCost(g->adjLists[v], u, cost);
	}
	if(isElement(g->adjLists[u], v) != 0)
	{
		List temp = g->adjLists[u];
		while(temp != NULL)
		{
			if(temp->data == v && temp->cost > cost)
			{
				temp->cost = cost;
				List aux = g->adjLists[v];
				while(aux != NULL)
				{
					if(aux->data == u)
						aux->cost = cost;
					aux = aux->next;
				}
			}
			temp = temp->next;
		}
	}

	return g;	
}*/
Graph dfs(Graph g, int start) {
	int i;
	List tmp;
	g->visited[start] = 1;
	tmp = g->adjLists[start];
	while (tmp != NULL) {
		i = tmp->data;
		if (g->visited[i] == 0)
			g = dfs(g, i);
		tmp = tmp->next;
	}
	return g;
}

int elemConexe(Graph g)
{
	int i, cont = 0;
	for(i = 0; i < g->size; i++)
	{
		if(g->visited[i] ==0){
			//printf("nodul %d \n", i);
			dfs(g, i), cont++;
		}
	}
	return cont;
}
void drawGraph(Graph g, char *name)
{
	int i;
	FILE *stream;
	char *buffer;
	List tmp;

	if (g == NULL || name == NULL)
		return;
	stream = fopen(name, "w");
	fprintf(stream, "graph G {\n");
	fprintf(stream, "    node [fontname=\"Arial\", shape=circle, style=filled, fillcolor=yellow];\n");
	for (i = 0; i < g->size; i++) {
		tmp = g->adjLists[i];
		while (tmp != NULL) {
			if (tmp->data > i)
				fprintf(stream, "    %d -- %d;\n", i, tmp->data);
			tmp = tmp->next;
		}
	}
	fprintf(stream, "}\n");
	fclose(stream);
	buffer = (char*) malloc(200*sizeof(char));
	sprintf(buffer, "dot %s | neato -n -Tpng -o graph.png", name);
	system(buffer);
	free(buffer);
}
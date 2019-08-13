
typedef struct graph {
	int size;
	List *adjLists;
	int *visited;
}*Graph;

Graph initGraph(int size);
Graph insertEdge(Graph g, int u, int v);
Graph insertEdgeWCost(Graph g, int u, int v, int cost);
void drawGraph(Graph g, char *name);
Graph bfs(Graph g, int start);
Graph dfs(Graph g, int start);
int elemConexe(Graph g);
Graph freeGraph(Graph graph);

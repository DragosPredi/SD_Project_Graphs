#include "header.h"
//afisarea cu ajutorul unei funciti recursive
void afisareRecurs(FILE *fisier_output, int *parent, int index, int start)
{
    if(index == start)
        fprintf(fisier_output, "%d ", start);
    else
    {
        afisareRecurs(fisier_output, parent, parent[index], start);
        fprintf(fisier_output, "%d ", index);
    }
}
void Dijkstra(Graph graphWCost, List *politist, int *infoNodes, int u)
{
    //initializare si alocare memorie variabile
    int cont = 0, i = 0, min = INF, size = graphWCost->size;
    int *distance = malloc(size * sizeof(int));
    int *parent = malloc (size * sizeof(int));
    int *minDistIesire = malloc(size * sizeof(int));
    int start = u;

    for(i = 0 ; i < size ; i++)
    {
        distance[i] = INF;
        minDistIesire[i] = INF;
        parent[i] = -1;
    }
    distance[u] = 0;

    while(cont < size - 1)
    {

        for(i = 0; i < size; i++)
            if(infoNodes[i] == 1 && distance[i] < minDistIesire[i]){
                //daca este gasit un portal
                //este pastrat cel mai mic cost pana la el
                minDistIesire[i] = distance[i];
            }
        //updatam costurile in care exista gardieni
        List auxPolitist = NULL;
        for(i = 0; i < size; i++)
        {
            if(politist[i] != NULL)
                auxPolitist = politist[i];
            while(auxPolitist != NULL)
            {
                if(infoNodes[i] == 0 && distance[i] == auxPolitist->data)
                    distance[i]++;
                auxPolitist = auxPolitist->next;
            }
        } 

        min = INF;
        //alegem nodul cu distanta minima care nu a fost inca vizitat
        for(i = 0; i < size; i++)
            if(min > distance[i] && graphWCost->visited[i] == 0)
                min = distance[i], u = i;
        //marcam ca si vizitat
        graphWCost->visited[u] = 1 , cont++;

        List vecin = graphWCost->adjLists[u];

        while(vecin != NULL)
        {
            //relaxam daca gasim o distanta mai mica
            int v = vecin->data, cost = vecin->cost;
            if(graphWCost->visited[v] == 0 && distance[u] != INF && distance[v] > distance[u] + cost)
                distance[v] = distance[u] + cost , parent[v] = u;
            vecin = vecin->next;
        }

    }

    int index;
    FILE *fisier_output = fopen("labirint.out", "w");
    min = INF;
    //aflare cost minim
    for(i = 1 ; i < size ; i++){
        if(infoNodes[i] == 1 && min > minDistIesire[i]){
            min = minDistIesire[i];
            index = i;
        }
    }
    //afisare 
    fprintf(fisier_output, "%d\n", min);
    afisareRecurs(fisier_output, parent, index, start);
    fprintf(fisier_output, "\n");
    fclose(fisier_output);
    //eliberare memorie
    free(distance);
    free(parent);
    free(minDistIesire);

}   

void labirint()
{
    //citirea si initializarea tuturor variabilelor necesare pentru
    //apelarea functiei Djikstra
    int n, m, s, v, u, cost, i, j;
    FILE *fisier_input = fopen("labirint.in", "r");

    fscanf(fisier_input, "%d%d%d", &n, &m, &s);

    Graph graphWCost = initGraph(n+1);
    //creeare graf
    for(i = 0 ; i < m ; i++)
    {
        fscanf(fisier_input, "%d%d%d", &u, &v, &cost);
        graphWCost = insertEdgeWCost(graphWCost, u, v, cost);
    }

    int *infoNodes = NULL;
    //variabila care retine daca exista portal
    infoNodes = (int *)calloc((n+1),  sizeof(int));
    //variabila care retine secundele la care exista gardieni in camera
    List *politist = malloc((n+1) * sizeof(List));
    for (i = 0 ; i <= n ; i++)
        politist[i] = NULL;
    char garbage;
    fscanf(fisier_input, "%c", &garbage);//citire endline
    //citire
    for(i = 1 ; i <= n ; i++)
    {
        char iesire;
        int p;
        fscanf(fisier_input, "%c%d", &iesire, &p);
        infoNodes[i] = (iesire == 'N') ? 0 : 1;
        for(j = 0 ; j < p ; j++)
        {
            int x;
            fscanf(fisier_input, "%d", &x);
            politist[i] = addLast(politist[i], x);
        }
       
        fscanf(fisier_input, "%c", &garbage);//citire endline
    }

    fclose(fisier_input);
    //rezolvarea propriu-zisa
    Dijkstra(graphWCost, politist, infoNodes, s);
    //eliberare memorie
    freeGraph(graphWCost);
    free(infoNodes);
    for(i = 0; i <= n ; i++)
        freeList(politist[i]);
    free(politist);

}
int main()
{
    labirint();
}
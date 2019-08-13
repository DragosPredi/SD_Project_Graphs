#include "header.h"

char **lista_actori(char *fisier_input, int *contRealloc)
{
    FILE *input = fopen(fisier_input, "r");

    int i, j, nrFilme, nrActori, capRealloc = 40, k;
    char *film, *actor, garbage, **listaActori = NULL;

    //alocare memorie variabile 
    film = (char *) malloc(100 * sizeof(char));
    actor = (char *) malloc(1000 * sizeof(char));
    listaActori = (char **) malloc(capRealloc * sizeof(char *));
    
    fscanf(input, "%d", &nrFilme);
    fscanf(input, "%c", &garbage);
    //citesc toti actorii si ii bag intr-un vector de cuvinte
    //indicele unde se afla in vector v-a reprezenta id-ul lor in graf
    for(i = 0; i < nrFilme; i++)
    {
        fgets(film, 100, input);
        fscanf(input, "%d", &nrActori);
        fscanf(input, "%c", &garbage);

        for(j = 0; j < nrActori; j++)
        {
            fgets(actor, 100, input);
            int ok = 0;

            for(k = 0; k < *contRealloc; k++)
                if(strcmp(listaActori[k], actor) == 0)
                    ok = 1; //in caz ca a fost deja adaugat trec peste

            if(*contRealloc >= (capRealloc - 1)) //realocare memorie daca este necesar
            {
                capRealloc = capRealloc * 2;
                listaActori = realloc(listaActori, capRealloc * sizeof(char *));
            }

            if(ok == 0)
            {
                listaActori[*contRealloc] = strdup(actor);
                (*contRealloc)++;
            }   
        }
    }
    free(film);
    free(actor);

    fclose(input);
    return listaActori;
}

Graph citire(char *fisier_input, int cerinta2, int *u, int *v, char ***listaActori)
{
    FILE *input = fopen(fisier_input, "r");

    int nrFilme , nrActori, i, j, k, edge, *indexActori, contRealloc = 0;
    char *film = NULL, *actor = NULL, garbage;

    film = (char *) malloc(100 * sizeof(char));
    actor = (char *) malloc(100 * sizeof(char));  
    indexActori = (int *) malloc(500 * sizeof(int));

    *listaActori = lista_actori(fisier_input, &contRealloc);
    Graph graph = initGraph(contRealloc);
    fscanf(input, "%d", &nrFilme);
    fscanf(input, "%c", &garbage);
    //citesc toti actorii si in functie de indicele lor in vectorul de cuvinte
    //ii bag in grar
    for(i = 0; i < nrFilme; i++)
    {
        fgets(film, 100, input);
        fscanf(input, "%d", &nrActori);
        fscanf(input, "%c", &garbage); 
        for(j = 0; j < nrActori; j++)
        {
            fgets(actor, 100, input);

            for(k = 0; k < contRealloc; k++)
                if(strcmp(listaActori[0][k], actor) == 0)
                    indexActori[j] = k;

            edge = indexActori[j];
            for(k = j-1; k >= 0 ; k--)
                graph = insertEdge(graph, edge, indexActori[k]);       
        }         
    }
    //gasire indice actori pentru cerinta 2
    if(cerinta2 == 1)
    {
        fgets(actor, 100, input);
        for(k = 0; k < contRealloc; k++)
            if(strcmp(listaActori[0][k], actor) == 0)
                *u = k;

        fgets(actor, 100, input);
        for(k = 0; k < contRealloc; k++)
            if(strcmp(listaActori[0][k], actor) == 0)
                *v = k;
    }
    else
    {
        *u = 0;
        *v = 0;
    }
    //eliberare memorie
    free(film);
    free(actor);
    free(indexActori);
    fclose(input);
    
    return graph;
}

int sixGradesOfKevinBacon(Graph graph, int u, int v)
{
    int *dist = calloc(graph->size, sizeof(int));
    
    Queue que = initQueue(u);//bagam in coada elementul de la care pornim
    dist[u] = 0;//distanta de unde plecam este evident 0
    graph->visited[u] = 1;//il notam ca si vizitat

    while(!isEmptyQueue(que))
    {
        int firstElem = first(que);//extragem primul elem din coada
        que = dequeue(que);//il eliminam din coada
        List vecini = graph->adjLists[firstElem];//luam lista de adiacenta pt elem curent
        while(vecini != NULL)
        {
            if(graph->visited[vecini->data] == 1)//daca este nod visitat trecem peste
                vecini = vecini->next;
            else//daca nu, updatam distanta si adaugam in coada + notam nodul ca si vizitat
            {
                dist[vecini->data] = dist[firstElem] + 1;
                que = enqueue(que, vecini->data);
                graph->visited[vecini->data] = 1;
            }
        }
    }

    int valoare = dist[v];//valoarea cautata
    free(dist);
    freeQueue(que);
    return valoare;
}
//functie de sortare a unui vector de cuvinte
void sortArray(char ** actoriArticulati, int n)
{
    int i,j;
    char temp[100];
    for (i = 0; i < n - 1 ; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(actoriArticulati[i], actoriArticulati[j]) > 0) 
            {
                strcpy(temp, actoriArticulati[i]);
                strcpy(actoriArticulati[i], actoriArticulati[j]);
                strcpy(actoriArticulati[j], temp);
            }
        }
    }
}
void DFSrecurs(Graph graph, int u, int *timpDeDescoperire, int *low, int *parent, int *isArticulated)
{
    static int time = 0;//pentru calcularea timpului de descoperire

    int copchil = 0; // vairabila pentru calcularea numarului de copii

    graph->visited[u] = 1;//marcam nodul curent ca si vizitat
    timpDeDescoperire[u] = ++time;//crestem timpul de descoperire
    low[u] = time;

    List aux = graph->adjLists[u];//iteram prin vecinii lui u
    while(aux != NULL)
    {
        int v = aux->data;
        if(graph->visited[v] == 0)//daca nodul nu a fost vizitat
        {
            copchil++;//crestem nr de copii
            parent[v] = u;//ii actualizam parintii
            DFSrecurs(graph, v, timpDeDescoperire, low, parent, isArticulated);
            //verificam daca subarborele dominat de v este conectat cu un 
            //stramos al lui u
            low[u] = (low[u] < low[v]) ? low[u] : low[v];
            //u este pct de articulatie daca:
            //daca u este radacina in arbore si are mai multi de 2 copii
            if(parent[u] == -1 && copchil > 1)
                isArticulated[u] = 1;
            //u nu este radacina si are un copi v in T a.i nici un nod din
            //subarborele dominat de u nu este conectat cu un stramos al lui v
            //printr-o muchie inapoi
            if(parent[u] != -1 && low[v] >= timpDeDescoperire[u])
                isArticulated[u] = 1;
        }//altfel updatam variabila low 
        else if(v != parent[u])
            low[u] = (low[u] < timpDeDescoperire[v]) ? low[u] : timpDeDescoperire[v];

        aux = aux->next;
    }
}

void puncteDeArticulatie(Graph graph, char **listaActori, FILE *fisier_output)
{
    //initializare variabile necesare pt algoritm
    int i, cont = 0, temp = 0;
    int *low = calloc(graph->size, sizeof(int));
    int *timpDeDescoperire = calloc(graph->size, sizeof(int));
    int *parent = calloc(graph->size, sizeof(int));
    int *isArticulated = calloc(graph->size, sizeof(int));

    for(i = 0; i < graph->size; i++)
        parent[i] = -1;
    
    //pornim functia pentru a gasi punctele de articulatie din 
    //arborele de adancime cu radainca "i"
    for(i = 0; i < graph->size; i++)
        if(graph->visited[i] == 0)
            DFSrecurs(graph, i, timpDeDescoperire, low, parent, isArticulated);
    //aflam numarul de puncte articulate
    for(i = 0; i < graph->size; i++)
        if(isArticulated[i] == 1)
            cont++;   
    //alocare memorie vector de cuvinte pentru actori
    char **actoriArticulati = malloc(cont * sizeof(char *));
    for(i = 0; i < cont; i++)
        actoriArticulati[i] = malloc(100 * sizeof (char));
    
    //afisare nr puncte
    fprintf(fisier_output, "%d\n", cont);
    //creeare vector
    for(i = 0; i < graph->size; i++)
        if(isArticulated[i] == 1){
            actoriArticulati[temp] = strcpy(actoriArticulati[temp], listaActori[i]);
            temp = temp + 1;
        }
    
    //sortare
    sortArray(actoriArticulati, cont);
    //afisare
    for(i = 0; i < cont; i++)
        fprintf(fisier_output, "%s", actoriArticulati[i]);
    //eliberare
    free(low);
    free(timpDeDescoperire);
    free(parent);
    free(isArticulated);
    for(i = 0; i < cont; i++)
        free(actoriArticulati[i]);
    free(actoriArticulati);
}
//o tentativa de aplicare a algoritmului BronnKerbosch
void BronnKerbosch(Graph g, List R, List P, List X, char **listaActori, FILE *fisier_output)
{
    //tinand cont ca BronnKerbosch tinde sa aleaga clicile maximale
    //am zis sa afisez prima clica gasita dar tot este prea ineficient
    //si primeste timeout. Nu am mai avut timp sa fac afisarea eficient
    //sortarea vectorului de cuvinte fiind ceea ce trage mult in jos cred
    if(P == NULL && X == NULL){
        fprintf(fisier_output, "%d\n", sizeOfList(R));
        List temp = R;
        char **actori = malloc(sizeOfList(R) * sizeof(char *));
        int i;
        for(i = 0; i < sizeOfList(R) ; i++)
        {
            actori[i] = strdup(listaActori[temp->data]);
            temp = temp->next;
        }
        sortArray(actori, sizeOfList(R));
         for(i = 0; i < sizeOfList(R) ; i++)
        {
            fprintf(fisier_output,"%s",actori[i]);
        }
        return;
    }
    
    List aux = P;
    while(aux != NULL)
    {
        R = addLast(R, aux->data);
        List vecini = g->adjLists[aux->data];
        List auxP = intersection(P, vecini);
        List auxX = intersection(X, vecini);

        BronnKerbosch(g, R, auxP, auxX, listaActori, fisier_output);

        P = deleteItem(P, aux->data);
        X = addLast(X, aux->data);

        aux = aux->next;
    }
}
int main(int argc, char **argv)
{
    char *fisier_input = argv[2];
    char *fisier_output_citire = argv[3];
    char *comanda = argv[1];
    char **listaActori = NULL;

    int cerinta2 = 0, u = 0, v = 0;
    if(strcmp(comanda, "-c2") == 0)
        cerinta2 = 1;
    //creeare graf
    Graph graph = citire(fisier_input, cerinta2, &u, &v, &listaActori);
    FILE *fisier_output = fopen(fisier_output_citire, "w");
    //rezolvare in functie de comanda primita
    if(strcmp(comanda, "-c1") == 0)
        fprintf(fisier_output, "%d\n", elemConexe(graph));  
    if(strcmp(comanda, "-c2") == 0)
        fprintf(fisier_output, "%d\n", sixGradesOfKevinBacon(graph, u, v)); 
    if(strcmp(comanda, "-c3") == 0)
        puncteDeArticulatie(graph, listaActori, fisier_output);
    if(strcmp(comanda, "-b") == 0)
    {
        List R = NULL, X = NULL, P = NULL;
        int i;
        for(i = 0 ; i < graph->size; i++)
            if(graph->adjLists[i] != NULL)
                P = addLast(P, i);
            
        BronnKerbosch(graph, R, P, X, listaActori, fisier_output);
    }

    fclose(fisier_output);
    int i;
    for(i = 0; i < graph->size; i++)
        free(listaActori[i]);
    free(listaActori);

    graph = freeGraph(graph);
    
    return 0;
}
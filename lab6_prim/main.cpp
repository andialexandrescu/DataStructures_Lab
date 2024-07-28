#include <iostream>
#include <climits> // pt INT_MAX

using namespace std;

#define V 5 // nr vf graf

int minKey(int key[], bool mstSet[]) // gaseste vf cu cea mica cheie/ cost din multimea de vf care inca nu sunt incluse in parborele minim partial curent construit
{
    // se init variabilele pt minim
    int min = INT_MAX, min_index;
    for(int v = 0; v < V; v++)
    {
        if(mstSet[v] == false && key[v] < min) // vf cu cel mai mic cost si negasit
        {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[V][V])
{
    cout << "Muchie \tGreutate\n";
    for(int i = 1; i < V; i++)
    {
        cout<<parent[i]<<" - "<<i<<" \t"<<graph[i][parent[i]]<<endl;
    }
}

void primMST(int graph[V][V])
{
    int parent[V]; // pt a stoca MST-ul construit
    int key[V]; // val cheilor folosite pentru a alege muchia cu greutatea minima
    bool mstSet[V]; // mulțimea de vf incluse in MST
    // conventie: init toate cheile cu infinity
    for(int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    key[0] = 0; // se cheia 0 astfel incat acest vf sa fie selectat primul (start_node)
    parent[0] = -1; // nu are parinte start_node
    for(int count = 0; count < V - 1; count++) // V-1 vf pt MST care va rezulta
    {
        int u = minKey(key, mstSet); // se alege vf cu cheia minima
        mstSet[u] = true; // se adauga in multimea de vf din MST-ul curent
        for(int v = 0; v < V; v++)
        {
            // graph[u][v] este nenul doar pt vf adiacente
            // mstSet[v] este fals pentru vf care nu sunt inca incluse in MST
            // se actualizeaza cheia doar daca val de la graph[u][v] este mai mica decat key[v]
            if(graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printMST(parent, graph);
}

int main()
{
    // matricea de adiacenta
    int graph[V][V] = { { 0, 2, 0, 6, 0 },
                        { 2, 0, 3, 8, 5 },
                        { 0, 3, 0, 0, 7 },
                        { 6, 8, 0, 0, 9 },
                        { 0, 5, 7, 9, 0 } };
    primMST(graph);
    return 0;
}

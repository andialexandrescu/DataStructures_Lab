#include <iostream>
#include <vector>
#include <algorithm> // pt sortare

using namespace std;

// DSU (disjoint set union) cu o cale care indica parintele si rangul curent
class DSU {
private:
    int *parent;
    int *rank;
public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = -1; // fiecare element e propriul sau părinte la inceput
            rank[i] = 1; // rang init e 1
        }
    }
    int find(int i) // gasirea caii parcurse recursiv
    {
        if(parent[i] == -1)
        {
            return i;
        }
        return parent[i] = find(parent[i]);
    }
    void unite(int x, int y) // reuniune 2 set-uri
    {
        int s1 = find(x);
        int s2 = find(y);
        if(s1 != s2)
        {
            // se reunesc pe baza rangului
            if(rank[s1] < rank[s2])
            {
                parent[s1] = s2;
            } else if(rank[s1] > rank[s2])
            {
                parent[s2] = s1;
            } else
            {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

class Graph {
    vector<vector<int>> edgelist; // Listă de muchii
    int V; // Numărul de vârfuri

public:
    Graph(int V){ this->V = V;}
    void addEdge(int x, int y, int w)
    {
        edgelist.push_back({ w, x, y }); // ghreutatea w intre vf x si y
    }
    void kruskals_mst()
    {
        // sortare dupa weight
        sort(edgelist.begin(), edgelist.end());
        DSU s(V);
        int cost = 0; // cost total al arborelui de acoperire minima
        cout << "Muchiile in MST sunt:" << endl;
        for (auto edge : edgelist)
        {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];
            if (s.find(x) != s.find(y)) // nu are voie sa formeze cicluri
            {
                s.unite(x, y); // reuniune set-uri cu vf x si y
                cost += w;
                cout<<x<<" -- "<<y<<" == "<<w<<endl;
            }
        }
        cout<<"Costul minim al MST-ului: "<<cost<<endl;
    }
};

int main() {
    Graph g(4); // 4 vf
    g.addEdge(0, 1, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);
    g.addEdge(2, 0, 6);
    g.addEdge(0, 3, 5);
    g.kruskals_mst();
    return 0;
}

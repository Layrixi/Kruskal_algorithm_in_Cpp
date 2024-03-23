#include <iostream>
#include <fstream>
#include "dynamic_arr.h"
using namespace std;
class node {
public:
    double x, y;
    friend ostream& operator<<(ostream& os, const node elem1)
    {
        os << elem1.x << ", " << elem1.y;
        return os;
    }
};
class edge {
public:
    int node1, node2;
    double weight;
    edge()
    {
        node1 = NULL;
        node2 = NULL;
        weight = 0;
    }
    edge(int n1, int n2, int w)
    {
        node1 = n1;
        node2 = n2;
        weight = w;
    }
    friend bool operator>(const edge& elem1, const edge& elem2)
    {
        return elem1.weight > elem2.weight;
    }
    friend bool operator<(const edge& elem1, const edge& elem2)
    {
        return elem1.weight < elem2.weight;
    }
    friend bool operator==(const edge& elem1, const edge& elem2)
    {
        return elem1.weight == elem2.weight;
    }
    edge& operator=(const edge& elem1) {
        if (this != &elem1) { 
            node1 = elem1.node1;
            node2 = elem1.node2;
            weight = elem1.weight;
        }
        return *this;
    }
   
};

class graph {
public:
    int points_count;
    int edge_count;
    dynamic_arr<edge> edges;
    dynamic_arr<edge> MSTedges;
    dynamic_arr<node> points;
    void sort_by_weight()
    {
        edges.quickSort(0,edges.size-1);
    }
    void MakeMST();
    void print_graph()
    {
        for (int i = 0; i < edges.size; i++)
        {
            cout << " {\t " << edges[i].node1 << " ( " << points[(edges[i].node1)] << " ) " << ",\t" << edges[i].node2 << " ( " << points[(edges[i].node2)] << " ),\t " << edges[i].weight << " }" << endl;
        }
    }
    void print_MST()
    {
        for (int i = 0; i < MSTedges.size; i++)
        {
            cout << " {\t " << MSTedges[i].node1 << " ( " << points[(MSTedges[i].node1)] << " ) " << ",\t" << MSTedges[i].node2 << " ( " << points[(MSTedges[i].node2)] << " ),\t " << MSTedges[i].weight << " }" << endl;
        }
    }
    graph(int point, int edge)
    {
        points_count = point;
        edge_count = edge;
        edges.resize(edge_count);
        points.resize(points_count);
    }
    graph(string nazwa)
    {
        string sciezka = "C:\\Users\\Lenovo\\Desktop\\studia\\2_Rok\\1Semestr\\Algorytmy\\Ostatni program chyba yay\\UFKruskal\\excercises\\";
        string sciezka2 = nazwa;
        string sciezka_full = sciezka + sciezka2;
        std::ifstream plik(sciezka_full);

        if (!plik.is_open())
        {
            cout << "Nie udalo sie otworzyc pliku.\n";
            exit(0);
        }

        plik >> points_count;

        points.resize(points_count);
        for (int i = 0; i < points_count; i++) {
            plik >> points[i].x >> points[i].y;
        }

        
        plik >> edge_count;

        edges.resize(edge_count);
        for (int i = 0; i < edge_count; i++)
        {
            plik >> edges[i].node1 >> edges[i].node2 >> edges[i].weight;
        }

        plik.close();
        

    }
};

class UnionFind {
public:
    dynamic_arr<int> parents;
    dynamic_arr<int> ranks;
    void Union(int n1,int n2);
    void Union_by_rank(int n1,int n2);
    int Find(int i);
    int FindCompression(int i);
    UnionFind(int n)
    {
        parents.resize(n);
        ranks.resize(n);
        for (int i = 0; i < n; i++)
            parents[i] = i;
        for (int i = 0; i < n; i++)
            ranks[i] = 0;
    }
};

int UnionFind::Find(int i)//zwroc korzen swojego drzewa, jesli nie jest nim 'i' to jest nim rodzic, jesli nie rodzic to rodzic rodzica itd
{
    if (i == parents[i])
        return i;
    else
        return Find(parents[i]);
}
int UnionFind::FindCompression(int i)
{
    if (i == parents[i])
        return i;
    int root = FindCompression(parents[i]);
    if (root != parents[i])
        parents[i] = root;
    return root;

}
void UnionFind::Union(int n1, int n2)
{
    int n1_root = Find(n1);
    int n2_root = Find(n2);
    parents[n2_root] = n1_root;
}

void UnionFind::Union_by_rank(int n1, int n2)
{
    int n1_root = Find(n1);
    int n2_root = Find(n2);
    if (ranks[n1_root] < ranks[n2_root])
        parents[n1_root] = n2_root;
    else if (ranks[n1_root] > ranks[n2_root])
        parents[n2_root] = parents[n1_root];
    else
    {
        parents[n1_root] = parents[n2_root];
        ranks[n1_root] += 1;
    }
}

void graph::MakeMST()
{
    sort_by_weight();
    UnionFind unia(edge_count);
    for (int i = 0; i < edge_count; i++)
    {
        edge path = edges[i];
        int n1_root = unia.FindCompression(path.node1);
        int n2_root = unia.FindCompression(path.node2);
        if (n1_root != n2_root)
        {
            MSTedges.push(path);
            unia.Union_by_rank(n1_root, n2_root);
        }
    }
    print_MST();
}
int main()
{
        graph mapa("g1.txt");
        mapa.MakeMST();
        //Unia.Union()

        return 0;
}

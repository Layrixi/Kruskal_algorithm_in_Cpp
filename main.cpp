#include <iostream>
#include <fstream>
#include "dynamic_arr.h"
using namespace std;
class wezel {
public:
    double x, y;
    friend ostream& operator<<(ostream& os, const wezel klasa1)
    {
        os << klasa1.x << ", " << klasa1.y;
        return os;
    }
};
class krawedz {
public:
    int node1, node2;
    double waga;
    krawedz()
    {
        node1 = NULL;
        node2 = NULL;
        waga = 0;
    }
    krawedz(int n1, int n2, int w)
    {
        node1 = n1;
        node2 = n2;
        waga = w;
    }
    friend bool operator>(const krawedz& klasa1, const krawedz& klasa2)
    {
        return klasa1.waga > klasa2.waga;
    }
    friend bool operator<(const krawedz& klasa1, const krawedz& klasa2)
    {
        return klasa1.waga < klasa2.waga;
    }
    friend bool operator==(const krawedz& klasa1, const krawedz& klasa2)
    {
        return klasa1.waga == klasa2.waga;
    }
    krawedz& operator=(const krawedz& klasa1) {
        if (this != &klasa1) { 
            node1 = klasa1.node1;
            node2 = klasa1.node2;
            waga = klasa1.waga;
        }
        return *this;
    }
   
};

class graf {
public:
    int lWierzch;
    int lKraw;
    dynamic_arr<krawedz> krawedzie;
    dynamic_arr<krawedz> krawedzieMST;
    dynamic_arr<wezel> wierzcholki;
    void sortuj_wagami()
    {
        krawedzie.quickSort(0,krawedzie.size-1);
    }
    void zrobMST();
    void print_graf()
    {
        for (int i = 0; i < krawedzie.size; i++)
        {
            cout << " {\t " << krawedzie[i].node1 << " ( " << wierzcholki[(krawedzie[i].node1)] << " ) " << ",\t" << krawedzie[i].node2 << " ( " << wierzcholki[(krawedzie[i].node2)] << " ),\t " << krawedzie[i].waga << " }" << endl;
        }
    }
    void print_MST()
    {
        for (int i = 0; i < krawedzieMST.size; i++)
        {
            cout << " {\t " << krawedzieMST[i].node1 << " ( " << wierzcholki[(krawedzieMST[i].node1)] << " ) " << ",\t" << krawedzieMST[i].node2 << " ( " << wierzcholki[(krawedzieMST[i].node2)] << " ),\t " << krawedzieMST[i].waga << " }" << endl;
        }
    }
    graf(int wierzch, int kraw)
    {
        lWierzch = wierzch;
        lKraw = kraw;
        krawedzie.resize(lKraw);
        wierzcholki.resize(lWierzch);
    }
    graf(string nazwa)
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

        plik >> lWierzch;

        wierzcholki.resize(lWierzch);
        for (int i = 0; i < lWierzch; i++) {
            plik >> wierzcholki[i].x >> wierzcholki[i].y;
        }

        
        plik >> lKraw;

        krawedzie.resize(lKraw);
        for (int i = 0; i < lKraw; i++)
        {
            plik >> krawedzie[i].node1 >> krawedzie[i].node2 >> krawedzie[i].waga;
        }

        plik.close();
        

    }
};

class UnionFind {
public:
    dynamic_arr<int> rodzice;
    dynamic_arr<int> rangi;
    void Union(int n1,int n2);
    void Union_by_rank(int n1,int n2);
    int Find(int i);
    int FindKompresja(int i);
    UnionFind(int n)
    {
        rodzice.resize(n);
        rangi.resize(n);
        for (int i = 0; i < n; i++)
            rodzice[i] = i;
        for (int i = 0; i < n; i++)
            rangi[i] = 0;
    }
};

int UnionFind::Find(int i)//zwroc korzen swojego drzewa, jesli nie jest nim 'i' to jest nim rodzic, jesli nie rodzic to rodzic rodzica itd
{
    if (i == rodzice[i])
        return i;
    else
        return Find(rodzice[i]);
}
int UnionFind::FindKompresja(int i)
{
    if (i == rodzice[i])
        return i;
    int root = FindKompresja(rodzice[i]);
    if (root != rodzice[i])
        rodzice[i] = root;
    return root;

}
void UnionFind::Union(int n1, int n2)
{
    int n1_root = Find(n1);
    int n2_root = Find(n2);
    rodzice[n2_root] = n1_root;
}

void UnionFind::Union_by_rank(int n1, int n2)
{
    int n1_root = Find(n1);
    int n2_root = Find(n2);
    if (rangi[n1_root] < rangi[n2_root])
        rodzice[n1_root] = n2_root;
    else if (rangi[n1_root] > rangi[n2_root])
        rodzice[n2_root] = rodzice[n1_root];
    else
    {
        rodzice[n1_root] = rodzice[n2_root];
        rangi[n1_root] += 1;
    }
}

void graf::zrobMST()
{
    sortuj_wagami();
    UnionFind unia(lKraw);
    for (int i = 0; i < lKraw; i++)
    {
        krawedz droga = krawedzie[i];
        int n1_root = unia.FindKompresja(droga.node1);
        int n2_root = unia.FindKompresja(droga.node2);
        if (n1_root != n2_root)
        {
            krawedzieMST.push(droga);
            unia.Union_by_rank(n1_root, n2_root);
        }
    }
    print_MST();
}
int main()
{
        graf mapa("g1.txt");
        mapa.zrobMST();
        //Unia.Union()

        return 0;
}

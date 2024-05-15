#include <iostream>
#include <vector>
#define COUNT 10

using namespace std;

struct node{
    int val;
    // un arbore binar are maxim 2 copii
    node *l_child; // copil stanga -> subarbore stanga
    node *r_child; // copil dreapta -> subarbore dreapta
};

// interclasarea a doi arbori echilibrati presupune parcurgerea in-ordine a fieacrui arbore si retinerea elementelor intr-un array comun, apoi construirea unui arbore balansat
    node *create_node(int data)
    {
        node *aux = new node; // declararea unui nod si alocarea memoriei
        aux->val = data;
        aux->l_child = nullptr; // adresa campului prev e necunoscuta
        aux->r_child = nullptr; // adresa urmatorului camp e necunoscuta
        return aux; // returnare nod aux creat
    }
    // functia de construire a bst va returna nodul radacina convenabil folosind divide et impera
    // array-ul se injumatateste, radacina arborelui fiind elementul din mijloc, apoi se parcurge subarray-urile din stanga si dreapta recursiv
    node *dei_build_balanced_bst_from_sorted_arr(vector<int> v, int start, int end) // limitele vectorului; inferioara, superioara
    {
        if(start > end) // caz de baza recursivitate
        {
            return nullptr;
        }
        int middle = (start + end) / 2;
        //cout<<v[middle]<<" ";
        node *subtree_root = create_node(v[middle]);
        subtree_root -> l_child = dei_build_balanced_bst_from_sorted_arr(v, start, middle-1);
        subtree_root -> r_child = dei_build_balanced_bst_from_sorted_arr(v, middle+1, end);
        return subtree_root;
    }
    // parcurgere in-ordine, insemnand ca radacina fiecarui subarbore e visitata dupa ce subarborele sau stang a fost parcurs, dar inainte de inceperea parcurgerii subarborelui drept
    vector<int> create_array_inorder(node *root, vector<int> &aux)
    {
        if(root != nullptr)
        {
            create_array_inorder(root->l_child, aux);
            aux.push_back(root->val);
            create_array_inorder(root->r_child, aux);
        }
        return aux;
    }
    void display_inorder(node *root)
    {
        if(root != nullptr)
        {
            display_inorder(root->l_child);
            cout<<root->val<<" ";
            display_inorder(root->r_child);
        }
    }
    vector<int> merge(vector<int> &a, vector<int> &b)
    {
        int i = 0, j = 0, k = 0;
        vector<int> c;
        c.resize(a.size() + b.size());
        while(i < a.size() && j < b.size())
        {
            if(a[i] < b[j])
            {
                c[k] = a[i];
                k++; i++;
            } else
            {
                c[k] = b[j];
                k++; j++;
            }
        }
        while(i < a.size())
        {
            c[k] = a[i];
            k++; i++;
        }
        while(j < b.size())
        {
            c[k] = b[j];
            k++; j++;
        }
        return c;
    }
    // fac interclasarea a doi arbori cu toate ca as fi putut sa interclasez vectorii cu ajutorul carora sunt creati arborii si sa evit cativa pasi
    void merge_balanced_bsts(node *root_t1, node *root_t2)
    {
        vector<int> aux1, aux2, merged;
        // reordonarea elementelor din ambii arbori
        create_array_inorder(root_t1, aux1);
        create_array_inorder(root_t2, aux2);
        merged.resize(aux1.size() + aux2.size()); // din cauza accesarii prin index, as fi putut sa implementez cu push_back()
        merged = merge(aux1, aux2);
        /*cout<<"Interclasarea celor doi vectori rezultati din arborii echilibrati binari de cautare:"<<endl;
        for(int i = 0; i < merged.size(); i++)
        {
            cout<<merged[i]<<" ";
        }*/
        // crearea unui nou arbore in functie de vectorul care are valorile comune sortate crescator; parcurgerea in-ordine a unui arbore binar respecta conditia
        node *root_merged = dei_build_balanced_bst_from_sorted_arr(merged, 0, merged.size()-1);
        cout<<endl<<"Arborele rezultat parcurs in in-ordine:"<<endl;
        display_inorder(root_merged);
    }

int main()
{
    vector<int> a = {2, 2, 4, 5, 6, 7, 9, 11};
    /*
                         5
                      2     7
                    2  4   6  9
                               11
    */
    vector<int> b = {2, 5, 6, 8, 9, 10, 12, 12, 15, 17, 18};
    /*
                        10
                    5          15
                  2    9     12   18
                      6          17
                       8
    */
    // conexiuni radacini-noduri vectori pt fiecare arbore construit, desi puteam sa ii construiesc manual
    node *root_t1 = dei_build_balanced_bst_from_sorted_arr(a, 0, a.size()-1);
    node *root_t2 = dei_build_balanced_bst_from_sorted_arr(b, 0, b.size()-1);
    merge_balanced_bsts(root_t1, root_t2);
    /*
                        8
              5                 12
          2       6        9          15
         2 2     5 6      9 10       12 17
            4       7         11          18
    */
    return 0;
}

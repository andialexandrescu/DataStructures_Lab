#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

struct node{
    int val;
    // un arbore binar are maxim 2 copii
    node *l_child; // copil stanga -> subarbore stanga
    node *r_child; // copil dreapta -> subarbore dreapta
};

// pentru ca un arbore binar sa fie balansat, ar trebui sa existe un numar egal de noduri pentru fiecare subarbore, de aceea ar trebui gasita o radacina care sa respecte conditia
// valorile din subarborele din stanga sunt mai mici decat cea a nodului curent, iar valorile subarborilor din dreapta sunt mai mari
// diferenta de inaltime dintre subarborii din stanga si dreapta sa nu depaseasca 1

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
    node *dei_build_balanced_bst_from_sorted_arr(int v[], int start, int end) // limitele vectorului; inferioara, superioara
    {
        if(start > end) // caz de baza recursivitate
        {
            return nullptr;
        }
        int middle = (start + end) / 2;
        cout<<v[middle]<<" ";
        node *subtree_root = create_node(v[middle]);
        subtree_root -> l_child = dei_build_balanced_bst_from_sorted_arr(v, start, middle-1);
        subtree_root -> r_child = dei_build_balanced_bst_from_sorted_arr(v, middle+1, end);
        return subtree_root;
    }
    // parcurgere in-ordine, insemnand ca radacina fiecarui subarbore e visitata dupa ce subarborele sau stang a fost parcurs, dar inainte de inceperea parcurgerii subarborelui drept
    void display_inorder(node *root)
    {
        if(root != nullptr)
        {
            display_inorder(root->l_child);
            cout<<root->val<<" ";
            display_inorder(root->r_child);
        }
    }
    void display_preorder(node *root)
    {
        if(root != nullptr)
        {
            cout<<root->val<<" ";
            display_preorder(root->l_child);
            display_preorder(root->r_child);
        }
    }
    void display_postorder(node *root)
    {
        if(root != nullptr)
        {
            display_postorder(root->l_child);
            display_postorder(root->r_child);
            cout<<root->val<<" ";
        }
    }

int main()
{
    int v[]={2, 2, 4, 5, 6, 7, 9, 11};
    /*
                         5
                      2     7
                    2  4   6  9
                               11
    */
    int n = sizeof(v)/sizeof(v[0]);
    node *root = dei_build_balanced_bst_from_sorted_arr(v, 0, n-1);
    cout<<endl<<"Parcurgerea in-ordine:"<<endl;
    display_inorder(root);
    cout<<endl<<"Parcurgerea pre-ordine:"<<endl;
    display_preorder(root);
    cout<<endl<<"Parcurgerea post-ordine:"<<endl;
    display_postorder(root);
    return 0;
}

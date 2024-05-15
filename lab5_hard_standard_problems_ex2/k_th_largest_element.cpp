#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/kth-largest-element-in-bst-when-modification-to-bst-is-not-allowed/?ref=lbp
// sa se gaseasca al k-lea cel mai mare element
// din moment ce o parcurgere in-ordine afiseaza valorile nodurilor in ordine crescatoare, trebuie realizata o parcurge in-ordine inversa pentru a gasi cele mai mari elemente
// cand contorul devine k, a fost gasita nodul respectiv

struct node{
    int val;
    // un arbore binar are maxim 2 copii
    node *l_child; // copil stanga -> subarbore stanga
    node *r_child; // copil dreapta -> subarbore dreapta
};

// cautare recursiva a nodului cu valoarea data
void search_reverse_inorder(node *root, int k, int &count)
{
    if(root == nullptr || count > k)
    {
        return;
    }
    // parcurgere inversa a parcurgerii in-ordine
    search_reverse_inorder(root->r_child, k, count); // e vizitat cel mai mare element
    // e vizitat elementul curent deci se incrementeaza count
    count++;
    if(count == k)
    {
        cout<<"Al k-lea cel mai mare element este: "<<root->val;
        return;
    }
    search_reverse_inorder(root->l_child, k, count); // e vizitat cel mai mic element
}

node *create_node(int data)
{
    node *aux = new node; // declararea unui nod si alocarea memoriei
    aux->val = data;
    aux->l_child = nullptr; // adresa campului prev e necunoscuta
    aux->r_child = nullptr; // adresa urmatorului camp e necunoscuta
    return aux; // returnare nod aux creat
}

node *insert(node *aux, int data) // inserare arbore binar
{
    if(aux == nullptr) // daca nu exista e creat pt a adauga noduri copii la stanga sau dreapta nodului curent
    {
        return create_node(data);
    }
    if(data < aux->val) // valorile mai mici sunt in stanga
    {
        aux->l_child = insert(aux->l_child, data);
    } else // valorile mai mari sunt in dreapta
    {
        aux->r_child = insert(aux->r_child, data);
    }
    return aux;
}

int main() {
    /* Let us create following BST
               50
            /     \
           30      70
          /  \    /  \
        20   40  60   80 */
    node *root = create_node(50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    int k, count = 0;
    cout<<"Valoarea lui k: "; cin>>k;
    search_reverse_inorder(root, k, count);

    return 0;
}

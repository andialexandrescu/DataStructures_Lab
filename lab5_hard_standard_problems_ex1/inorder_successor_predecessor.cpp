#include <iostream>

using namespace std;

// https://www.geeksforgeeks.org/inorder-predecessor-successor-given-key-bst/?ref=lbp
// gasirea succesorului si predecesorului inorder al unei valori din bst
// caz particular: cheia nu e gasita, se intoarc valorile intre care se afla cheia
// predecesor: copilul cel mai din dreapta al subarborelui stang, pt ca intr-un bst ar fi valoarea maxima care e mai mica decat val din nodul al carui predecesor e cautat
// succesor: copilul cel mai din stanga al subarborelui drept, pt ca ar fi valoarea minima care e mai mare decat valoarea nodului curent
// cheie == radacina curenta, atunci se poate realiza algoritmul de parcurgere
// cheie < radacina curenta, atunci inseamna ca o pt a gasi valori apropiate se cauta in subarborele din stanga care va avea elemente mai mici decat radacina
// de fapt succesorul e chiar radacina (copilul cel mai din stanga al subarborelui drept), algoritmul operand in subarborele stang (pt a gasi predecesorul)
// cheie > radacina curenta, atunci inseamna ca o pt a gasi valori apropiate se cauta in subarborele din dreapta care va avea elemente mai mari decat radacina
// de fapt redecesorul e chiar radacina (copilul cel mai din dreapta al subarborelui stang), algoritmul operand in subarborele drept (pt a gasi succesorul)

struct node{
    int val;
    // un arbore binar are maxim 2 copii
    node *l_child; // copil stanga -> subarbore stanga
    node *r_child; // copil dreapta -> subarbore dreapta
};

node *find_predecessor(node *subtree_root, int data) // caz general predecesor
{
    node *curr = subtree_root;
    node *pre = new node;
    pre->l_child = nullptr;
    pre->r_child = nullptr;
    // curr va parcurge subarborele stang curent, prioritate avand pozitia din dreapta
    while(curr != nullptr)
    {
        if(curr->val <= data)
        {
            pre = curr;
            curr = curr->r_child; // dreapta
        } else
        {
            curr = curr->l_child; // stanga
        }
    }
    return pre;
}

node *find_successor(node *subtree_root, int data) // caz general succesor
{
    node *curr = subtree_root;
    node *suc = new node;
    suc->l_child = nullptr;
    suc->r_child = nullptr;
    // curr va parcurge subarborele dreapt curent, prioritate avand pozitia din stanga
    while(curr != nullptr)
    {
        if(curr->val >= data)
        {
            suc = curr;
            curr = curr->l_child; // stanga
        } else
        {
            curr = curr->r_child; // dreapta
        }
    }
    return suc;
}

// cautare recursiva a nodului cu valoarea data
void search(node *root, node *&suc, node *&pre, int data)
{
    if(root == nullptr) // atentie!!!
    {
        return;
    }
    if(root->val == data) // a fost gasit nodul cu valoarea data ale carui predecesor si succesor urmeaza a fi cautate
    {
        suc = find_successor(root, data);
        pre = find_predecessor(root, data);
    } else if(root->val > data) // cautare stanga
    {
        suc = root;
        search(root->l_child, suc, pre, data);
    } else // cautare dreapta
    {
        pre = root;
        search(root->r_child, suc, pre, data);
    }
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
    int key = 65;    //Key to be searched in BST

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

    node *predecessor = nullptr, *successor = nullptr;
    search(root, successor, predecessor, key);
    if(successor != nullptr)
    {
        cout<<"Succesorul este: "<<successor->val<<endl;
    }
    if(predecessor != nullptr)
    {
        cout<<"Predecesorul este: "<<predecessor->val<<endl;
    }

    return 0;
}
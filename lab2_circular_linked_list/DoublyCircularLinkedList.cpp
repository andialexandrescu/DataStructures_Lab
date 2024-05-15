#include <iostream>

using namespace std;

struct node{
    node *prev;
    int val;
    node *next;
};

// ultimul nod din lista are pointerul next care indica spre primul nod, iar primul nod din lista are pointerul prev care indica spre ultimul nod
class DoublyCircularLinkedList{
private:
    node *head;
public:
    DoublyCircularLinkedList()
    {
        head = nullptr;
    }
    node *get_head()
    {
        return head;
    }
    node *get_nth_node(int i)
    {
        node *curr = head;
        int count = 0;
        do{
            if(count == i)
            {
                return curr;
            }
            count++;
            curr = curr->next;
        } while(curr != head);
    }
    node *create_node(int data)
    {
        node *aux = new node; // declararea unui nod si alocarea memoriei
        aux->val = data;
        aux->prev = nullptr; // adresa campului prev e necunoscuta
        aux->next = nullptr; // adresa urmatorului camp e necunoscuta
        return aux; // returnare nod aux creat
    }
    void create_list(int n)
    {
        int x;
        for(int i = 0; i < n; i++)
        {
            cout<<"Valoarea nodului curent: "; cin>>x;
            node *aux = create_node(x);
            if(head == nullptr) // daca lista e vida, capul va reprezenta primul element introdus
            {
                head = aux;
                // evidentierea circularitatii
                aux->prev = head;
                aux->next = head;
            }
            else // daca exista cel putin un element in lista, inseamna ca se modifica campul next al penultimului element din lista, elementul curent devenind ultimul la fiecare iteratie
            {
                // nu mai trebuie parcursa lista folosind acel nod curr, deoarece se creeaza usor conexiuni circulare de data asta
                aux->prev = head->prev; // elementul curent e mereu legat de head; echivalent cu aux->prev = curr
                aux->next = head; // reconstituirea conexiunii circulare pt nodul curent
                head->prev->next = aux; // head->prev ajunge la ultimul anterior element din lista ce va crea o legatura cu noul ultim element din lista aux, cel adaugat
                head->prev = aux;
            }
        }
    }
    void display()
    {
        node *curr = head;
        if(head == nullptr)
        {
            cout<<"Lista e vida"<<endl;
        } else
        {
            cout<<curr->val<<" -> "; // se afiseaza valoarea din nodul curent
            curr = curr->next;
            while(curr != head)
            {
                cout<<curr->val<<" -> ";
                curr = curr->next;
            }
            if(curr == head)
            {
                cout<<"NULL"<<endl;
            }
        }
    }
    void display_reversed() // iterativ; implementarea recursiva de la simply linked list a fost necesara din cauza lipsei campului prev
    {
        node *curr = head;
        if(head == nullptr)
        {
            cout<<"Lista e vida"<<endl;
        } else
        {
            do{
                curr = curr->prev; // head->prev e tail-ul, deci afisarea se face de la ultimul element la primul datorita buclei while conditionate posterior
                cout<<curr->val<<" -> ";
            } while(curr != head); // continua afisarea pana se revine la capul listei
        }
    }
    void insert_node_end(int data) // similar cu implementarea pt create_list()
    {
        node *aux = create_node(data);
        if(head == nullptr)
        {
            head = aux;
            aux->prev = head;
            aux->next = head;
        } else
        {
            aux->prev = head->prev; // elementul curent e mereu legat de head; echivalent cu aux->prev = curr
            aux->next = head; // reconstituirea conexiunii circulare pt nodul curent
            head->prev->next = aux; // head->prev ajunge la ultimul anterior element din lista ce va crea o legatura cu noul ultim element din lista aux, cel adaugat
            head->prev = aux;
        }
    }
    void insert_node_front(int data)
    {
        node *aux = create_node(data);
        if(head == nullptr)
        {
            head = aux;
            aux->prev = head;
            aux->next = head;
        } else
        {
            aux->prev = head->prev; // elementul curent e mereu legat de head; echivalent cu aux->prev = curr
            aux->next = head; // reconstituirea conexiunii circulare pt nodul curent
            head->prev->next = aux; // head->prev ajunge la ultimul anterior element din lista ce va crea o legatura cu noul ultim element din lista aux, cel adaugat
            head->prev = aux;
            head = aux; // noul head e nodul curent
        }
    }
    void insert_node_after(node *prev_node, int data) // inserarea unui nod dupa nodul prev_node
    {
        if(prev_node == nullptr) // trebuie sa existe ca sa fie inserat un alt nod dupa el
        {
            return;
        }
        node *aux = new node;
        aux->val = data;
        aux->prev = prev_node;
        aux->next = prev_node->next; // campul next al lui aux e acelasi cu cel al lui prev_node
        prev_node->next->prev = aux; // actualizare camp prev pentru nodul urmator
        prev_node->next = aux; // actualizare camp next pentru nodul anterior
    }
    node *search_node(int data) // nimic schimbat fata de simply linked list
    {
        node *curr = head; // cautarea iterativa incepe din capul listei
        do{ // parcurgere de la stanga la dreapta
            if(curr->val == data)
            {
                return curr;
            }
            curr = curr->next;
        } while(curr != head); // conditionat posterior pentru ca nu ar intra in bucla deloc daca cautarea incepe de la head; primul pas al cautarii incepe de la head
        return nullptr; // nodul cu valoarea data nu e gasit
    }
    void remove_node(int data)
    {
        node *del_node = search_node(data); // cautare nod bazata pe gasirea pozitiei in care se afla in lista
        if(del_node == head) // daca nodul care trebuie sters e capul listei, noul cap al listei e elementul care urmeaza dupa head
        {
            head = head->next; // se muta doar capul listei, restul elementelor nu sunt afectate
        }
        if(del_node != nullptr) // trebuie sa fie doar gasit in lista, partile de unlinking functioneaza pentru stergerea unui element aflat in orice pozitie, fara sa mai existe restrictii
        {
            del_node->prev->next = del_node->next; // unlinking pt campul next al elementului aflat inaintea lui del_node
            del_node->next->prev = del_node->prev; // unlinking pt campul prev al elementului curent care e inaintea val care trebuie stearsa
        }
        delete del_node; // stergerea efectiva pt eliberarea zonei de memorie
    }
    node *max()
    {
        if(head == nullptr) // lista e vida
        {
            return nullptr;
        }
        node *max_node = head;
        // de data asta curr e nodul care urmeaza dupa head, deoarece se parcurge lista folosind doua variabile care mereu isi incrementeaza pozitiile succesiv
        node *curr = head->next; // daca max_node e primul element din lista, vor fi verificate restul elementelor din lista incepand cu al doilea, adica head->next
        do{
            if(max_node->val < curr->val)
            {
                max_node = curr;
            }
            curr = curr->next;
        } while(curr != head);
        return max_node;
    }
    node *min() // similar cu functia max
    {
        if(head == nullptr)
        {
            return nullptr;
        }
        node* min_node = head;
        node* curr = head->next;
        do{
            if(min_node->val > curr->val)
            {
                min_node = curr;
            }
            curr = curr->next;
        } while(curr != head);
        return min_node;
    }
    node *successor(int data)
    {
        if(head == nullptr) // lista e vida
        {
            return nullptr;
        }
        node *curr = head;
        do{
            if(curr->val == data)
            {
                return curr->next;
            }
            curr = curr->next; // deplasare
        } while(curr != head);
        return nullptr; // nodul cu val data nu a fost gasit
    }
    node *predecessor(int data)
    {
        if(head == nullptr) // lista e vida
        {
            return nullptr;
        }
        node *curr = head;
        do{
            if(curr->val == data)
            {
                return curr->prev;
            }
            curr = curr->next; // deplasare
        } while(curr != head);
        return nullptr; // nodul cu val data nu a fost gasit
    }
};

int main() {
    DoublyCircularLinkedList list;
    int choice, x, i;

    do{
        cout<<endl;
        cout<<"1. Crearea unei liste dublu circulare inlantuite\n2. Inserarea unui nod la sfarsitul listei\n3. Inserarea unui nod la inceputul listei\n4. Inserarea unui nod dupa un alt nod existent din lista\n5. Cautarea unui nod in functie de valoare\n6. Stergerea unui nod in functie de valoare\n7. Cautarea minimului si a maximului din lista\n8. Afisarea elementelor curente din lista\n 9. Afisarea inversa a elementelor din lista\n 10. Cautarea succesorului unui element\n 11. Cautarea predecesorului unui element\n 12. Iesire meniu\n Tastati varianta aleasa: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                int n;
                if(list.get_head() == nullptr) // daca lista nu a fost initializata inca
                {
                    cout<<"Nr. de noduri ale listei dublu circulare inlantuite: "; cin>>n;
                    list.create_list(n);
                } else
                {
                    cout<<"Lista exista deja"<<endl;
                }
                break;
            case 2:
                cout<<"Valoarea nodului: "; cin>>x;
                list.insert_node_end(x);
                break;
            case 3:
                cout<<"Valoarea nodului: "; cin>>x;
                list.insert_node_front(x);
                break;
            case 4:
                cout<<"Valoarea nodului: "; cin>>x;
                cout<<endl<<"Pozitia nodului dupa care sa fie inserat: "; cin>>i;
                list.insert_node_after(list.get_nth_node(i), x);
                break;
            case 5:
                cout<<"Valoarea de cautat in lista: "; cin>>x;
                if(list.search_node(x) == nullptr)
                {
                    cout<<"Valoarea nu a fost gasita in lista"<<endl;
                } else
                {
                    cout<<"Valoarea a fost gasita in lista"<<endl;
                }
                break;
            case 6:
                cout<<"Valoarea de sters din lista: "; cin>>x;
                list.remove_node(x);
                break;
            case 7:
                cout<<"Valoarea minima din lista este: "<<list.min()->val<<endl;
                cout<<"Valoarea maxima din lista este: "<<list.max()->val<<endl;
                break;
            case 8:
                cout<<"Elementele curente ale listei dublu circulare inlantuite sunt:"<<endl;
                list.display();
                break;
            case 9:
                cout<<"Elementele curente ale listei dublu circulare inlantuite in ordine inversa sunt:"<<endl;
                list.display_reversed();
                break;
            case 10:
                cout<<"Valoarea elementului al carui succesor trebuie returnat: "; cin>>x;
                if(list.successor(x) != nullptr)
                {
                    cout<<"Succesorul are valoarea "<<list.successor(x)->val<<endl;
                } else
                {
                    cout<<"Elementul selectat nu are succesor"<<endl;
                }
                break;
            case 11:
                cout<<"Valoarea elementului al carui predecesor trebuie returnat: "; cin>>x;
                if(list.predecessor(x) != nullptr)
                {
                    cout<<"Predecesorul are valoarea "<<list.predecessor(x)->val<<endl;
                } else
                {
                    cout<<"Elementul selectat nu are predecesor"<<endl;
                }
                break;
            case 12:
                break;
            default:
                cout<<"Invalid"<<endl;
                return 1;
        }
    } while(choice != 12);

    return 0;
}
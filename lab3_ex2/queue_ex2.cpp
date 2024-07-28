#include <iostream>
#include <vector>

using namespace std;

struct node
{
    int val;
    node *next;
};

class Stack{ // LIFO
private:
    node *top; // avem acces numai la varful stivei, top reprezinta de fapt tail-ul listei simplu inlantuite
    node *head;
public:
    // constructor pt o stiva vida, pt care pointer-ul top nu va pointa catre nimic
    Stack()
    {
        head = nullptr;
        top = nullptr;
    }
    node *get_top()
    {
        return top;
    }
    node *create_node(int data)
    {
        node *aux = new node;
        aux->val = data;
        aux->next = nullptr;
        return aux;
    }
    void push(int data) // cout<<"Valoarea de introdus pe stiva: "; cin>>aux->val; // dereferentiere // nu functioneaza pt ca prelucrez caracter cu caracter o expresie introdusa de la tastatura
    {
        cout<<"Valoarea elementului care a fost introdus la finalul stivei: "<<data<<endl;
        node *aux = create_node(data);
        if(head == nullptr)
        {
            head = aux;
            top = aux; // vf stivei e chiar head-ul listei formate dintr-un singur element
        } else
        {
            node *curr = head;
            while(curr->next != nullptr)
            {
                curr = curr->next;
            }
            curr->next = aux;
            top = aux; // vf stivei
        }
    }
    void pop()
    {
        if(top == nullptr)
        {
            cout<<"A avut loc underflow"<<endl;
            return;
        }
        if(head->next == nullptr) // daca exista un singur element care urmeaza a fi scos de pe stiva
        {
            head = nullptr;
            cout<<"Valoarea elementului care a fost scos de pe stiva: "<<top->val<<endl;
            delete top;
            top = nullptr;
        } else
        {
            node *curr = head;
            while(curr->next != top) // parcurgere linked list pana la penultimul element pentru a putea exprima, dupa ce e sters ultimul element din stiva, top in functie de curr (nu exista campul prev)
            {
                curr = curr->next; // deplasare
            }
            curr->next = nullptr;
            cout<<"Valoarea elementului care a fost scos de pe stiva: "<<top->val<<endl;
            delete top;
            top = curr;
        }
    }
    void display()
    {
        if(head == nullptr)
        {
            cout<<"Stiva e goala"<<endl;
        } else
        {
            node *curr = head;
            cout<<"| "; // baza stivei
            while(curr != top->next) // sau while(curr != nullptr)
            {
                cout<<curr->val<<" -> "; // se afiseaza valoarea din nodul curent
                curr = curr->next;
            }
        }
    }
    bool empty() const
    {
        return top == nullptr; // true daca e vida, false altfel
    }
};

class Queue { // FIFO
private:
    node *tail; // operatia de enqueue, adaugarea elementelor unei cozi se face la sfarsitul acesteia
    node *head; // operatia de dequeue, eliminarea elementelor unei cozi se face la inceputul acesteia
public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
    }
    node *get_head()
    {
        return head;
    }
    node *create_node(int data)
    {
        node *aux = new node;
        aux->val = data;
        aux->next = nullptr;
        return aux;
    }
    void enqueue(int data)
    {
        cout<<"Valoarea elementului care a fost introdus la finalul cozii: "<<data<<endl;
        node *aux = create_node(data);
        if(head == nullptr)
        {
            head = aux;
        } else
        {
            tail->next = aux; // se adauga la sfarsitul cozii
        }
        tail = aux;
    }
    void dequeue()
    {
        if(head == nullptr)
        {
            cout<<"Coada e goala"<<endl;
        }
        node *aux = head;
        cout<<"Valoarea elementului care a fost scos de la inceputul cozii: "<<aux->val<<endl;
        head = head->next;
        delete aux;
    }
    void display()
    {
        if(head == nullptr)
        {
            cout<<"Coada e goala"<<endl;
        } else
        {
            node *curr = head;
            while(curr != nullptr)
            {
                cout<<curr->val<<" -> "; // se afiseaza valoarea din nodul curent
                curr = curr->next;
            }
        }
    }
    bool empty()
    {
        return head == nullptr;
    }
};

int main() {
    vector<int> v;
    vector<int> aux;
    Stack stack;
    Queue queue_max;
    Queue queue_prev;
    int n;

    cout<<"Nr. de elemente pe care le contine vectorul: "; cin>>n;
    v.resize(n);
    for(int i = 0; i < n; i++)
    {
        cout<<"v["<<i<<"]="; cin>>v[i];
    }
    // fiecare element din vector trebuie adaugat pe stiva, iar in momentul in care un element curent din vector e mai mare decat valoarea din vf stivei, se realizeaza pop si se continua verificarea conditiei pana cand stiva ramane goala sau noul varf e mai mare decat val din vector, iar valoarea imediat mai mare e adaugata in queue_max
    for(int i = 0; i < n; i++)
    {
        cout<<endl<<"Pasul "<<i<<":"<<endl;
        // functionalitatea while-ului se aplica numai daca exista mai multe valori la rand egale pe stiva ale caror prim mai mare element nu a fost gasit
        while(!stack.empty() && v[i] > stack.get_top()->val) // top = val din vf stivei care trebuie comparata cu fiecare element pana e gasit primul mai mare decat el
        {
            queue_max.enqueue(v[i]); // in coada se afla toate solutiile, deoarece afisarea valorilor elementelor din vector va fi usoara datorita operatiei de dequeue, deoarece se vor potrivi atribuirile
            queue_prev.enqueue(stack.get_top()->val);
            stack.pop(); // o data ce e gasit primul cel mai mare element pt o valoare anterioara aflata pe stiva, aceasta va fi scoasa de pe stiva, deoarece nu mai trebuie comparata cu nimic
            cout<<endl<<"Afisarea stivei: ";
            stack.display();
            cout<<endl<<"Afisarea cozii: "<<endl;
            queue_max.display();
            cout<<endl;
        }
        stack.push(v[i]);
    }
    // daca raman elemente pe stack, inseamna ca nu le-a fost gasit primul cel mai mare element, pentru ca se afla la sfarsitul vectorului
    while(!stack.empty())
    {
        queue_max.enqueue(-1);
        queue_prev.enqueue(stack.get_top()->val);
        stack.pop();
    }
    cout<<endl<<endl<<endl;
    while(!queue_prev.empty() && !queue_max.empty())
    {
        cout<<"Primul cel mai mare element al lui "<<queue_prev.get_head()->val<<" este "<<queue_max.get_head()->val<<endl;
        queue_max.dequeue();
        queue_prev.dequeue();
    }

    return 0;
}
/*10
9 2 3 10 11 4 6 23 23 3
 11
 9 8 7 8 5 4 3 6 10 10 10*/

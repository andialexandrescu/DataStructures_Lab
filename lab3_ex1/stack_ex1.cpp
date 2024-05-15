#include <iostream>
#include <string>

using namespace std;

struct node
{
    char val;
    node *next; // fiind o stiva nu ar avea campul prev
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
    node *create_node(char data)
    {
        node *aux = new node;
        aux->val = data;
        aux->next = nullptr;
        return aux;
    }
    void push(char data) // cout<<"Valoarea de introdus pe stiva: "; cin>>aux->val; // dereferentiere // nu functioneaza pt ca prelucrez caracter cu caracter o expresie introdusa de la tastatura
    {
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

int main()
{
    Stack current_stack, aux_stack; // pe curent_stack se adauga numai parantezele deschise, aux_stack il folosesc doar pentru a afisa mesaje exacte legate de ce ramane pe stiva, altfel nu are nicio functionalitate reala
    string expr;
    cout<<"Expresia matematica care foloseste paranteze (), {}, [] este: "<<endl;
    cin>>expr;
    /*for(unsigned long long i=0; i<expr.length(); i++)
    {
        current_stack.push(expr[i]);
    }
    current_stack.display();*/
    bool ok = true; // presupun ca expresia e scrisa corect
    for(char c: expr)
    {
        if(c=='(' || c=='[' || c=='{')// introduc pe stiva doar caracterul curent, care e o paranteza deschisa
        {
            current_stack.push(c);
        } else if (c==')' || c==']' || c=='}')
        {
            aux_stack.push(c); // doar pt a trata cazul in care parantezele inchise nu au corespondente paranteze deschise
            char top;
            node *top_stack = current_stack.get_top();
            if(top_stack != nullptr) // daca nu are loc underflow, adica lista inlantuita nu e vida
            {
                top = top_stack->val;
            }
            // la fiecare pas scot ce am pe stiva current_stack in momentul in care intalnesc o paranteza corespondenta inchisa
            if((c==')' && top=='(') || (c==']' && top=='[') || (c=='}' && top=='{'))
            {
                current_stack.pop(); // imbricare corecta, pop de pe stiva la parantezele deschise
                aux_stack.pop(); // pop la parantezele inchise
            } else
            {
                ok = false; // de retinut ca despre caracterul curent din expresie stim ca e o paranteza inchisa, insa nu corespunde tipul parantezei referitor la paranteza deschisa din vf stivei current_stack
                cout<<"Expresia nu are corect imbricate parantezele: ";
                if(c==')')
                {
                    cout<<"()"<<endl;
                } else if(c==']')
                {
                    cout<<"[]"<<endl;
                } else
                {
                    cout<<"{}"<<endl;
                }
            }
        }
    }
    if(!current_stack.empty()) // raman paranteze deschise pe stiva, carora nu le-am dat pop
    {
        ok = false;
        cout<<"Ce a ramas pe stiva current_stack:"<<endl;
        current_stack.display();
    }
    if(!aux_stack.empty())
    {
        ok = false;
        cout<<"Ce a ramas pe stiva aux_stack:"<<endl;
        aux_stack.display();
    }

    if(ok)
    {
        cout<<"Expresia e scrisa corect";
    } else
    {
        cout<<"Expresia nu e scrisa corect";
    }

    return 0;
}
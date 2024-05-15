#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

class Stack {
private:
    node *top; // avem acces numai la varful stivei, adica tail-ul listei simplu inlantuite
    node *head;
public:
    // constructor pt o stiva vida, pt care pointer-ul top nu va pointa catre nimic
    Stack()
    {
        head = nullptr;
        top = nullptr;
    }
    node *create_node(int data)
    {
        node *aux = new node;
        aux->val = data;
        aux->next = nullptr;
        return aux;
    }
    void push(int data)
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
};

int main() {
    Stack stack;
    int choice, x;

    do{
        cout<<endl;
        cout<<"1. Push\n2. Pop\n3. Afisare stiva\n4. Iesire meniu\n Tastati varianta aleasa: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Valoarea elementului care va fi introdus pe stiva: "; cin>>x;
                stack.push(x);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                cout<<"Elementele curente de pe stiva sunt:"<<endl;
                stack.display();
                break;
            case 4:
                break;
            default:
                cout<<"Invalid"<<endl;
                return 1;
        }
    } while(choice != 4);

    return 0;
}

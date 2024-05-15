#include <iostream>

using namespace std;

struct node
{
    int val;
    node *next;
};

class Queue {
private:
    node *tail; // operatia de enqueue, adaugarea elementelor unei cozi se face la sfarsitul acesteia
    node *head; // operatia de dequeue, eliminarea elementelor unei cozi se face la inceputul acesteia
public:
    Queue()
    {
        head = nullptr;
        tail = nullptr;
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
};

int main() {
    Queue queue;
    int choice, x;

    do{
        cout<<endl;
        cout<<"1. Enqueue\n2. Dequeue\n3. Afisare coada\n4. Iesire meniu\n Tastati varianta aleasa: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Valoarea elementului care va fi introdus la sfarsitul cozii: "; cin>>x;
                queue.enqueue(x);
                break;
            case 2:
                queue.dequeue();
                break;
            case 3:
                cout<<"Elementele curente de pe stiva sunt:"<<endl;
                queue.display();
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

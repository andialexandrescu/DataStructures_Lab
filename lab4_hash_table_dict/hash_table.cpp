#include <iostream>
#include <vector>
#include <string>

using namespace std;

// un dictionar e o colectie de perechi (key, value) deci un nod va avea doua campuri care contin informatii si un pointer next
struct node { // pt a trata coliziunile, folosim simply linked list pt usurinta
    char key; // una dintre cele 26 de litere din alfabet
    string val; // orice cuvant
    node *next;
};

// un hash table e un array de simply linked lists, iar fiecare lista contine elementele cu aceeasi cheie
// functia de hashing produce acelasi index/ aceeasi cheie pentru fiecare cuvant, referitor la litera cu care incepe fiecare
// aceasta coliziune e rezolvata folosind o lista simplu inlantuita pentru cuvintele care incep cu aceeasi litera, adica fiecarei chei ii corespunde o lista
// indexul din array e indicat de valoarea functiei hash_function(value)

class HashTable {
private:
    // table[index] e de fapt un pointer la un nod (nullptr sau nu), acel nod putand avea campul next care sa pointeze catre un alt nod etc.
    vector<node *> table; // o tabela hash interpretata drept vector care pointeaza la elemente de tip node, separate chaining
    int table_size;
public:
    HashTable(int size) : table_size(size), table(size)
    {
        for(int i = 0; i < table_size; i++)
        {
            table[i] = nullptr;
        }
    }
    ~HashTable()
    {
        for (int i = 0; i < table_size; i++)
        {
            node* curr = table[i];
            while(curr != nullptr)
            {
                node* aux = curr->next;
                delete curr;
                curr = aux;
            }
        }
    }
    int hash_function(char letter)
    {
        return toupper(letter) - 'A';
    }
    char convert_to_letter(int index) // doar pt afisare
    {
        if (index >= 0 && index < 26)
        {
            return static_cast<char>(index + 'A');
        }
    }
    node *create_node(string data) // caz general: create_node(char key, string data)
    {
        node *aux = new node;
        aux->key = toupper(data[0]);
        aux->val = data;
        aux->next = nullptr;
        return aux;
    }
    void display_list(char letter)
    {
        int index = hash_function(letter);
        node *curr = table[index];
        if(curr == nullptr) // nu exista niciun cuvant inserat in dictionar care sa inceapa cu litera specificata
        {
            cout<<"Nu exista niciun cuvant cu litera "<<convert_to_letter(index)<<endl;
        } else
        {
            cout<<"Litera "<<curr->key<<": ";
            while(curr != nullptr)
            {
                cout<<curr->val<<" -> "; // se afiseaza valoarea din nodul curent
                curr = curr->next;
            }
            cout<<endl;
        }
    }
    void display()
    {
        for(char letter = 'a'; letter <= 'z'; letter++)
        {
            display_list(letter);
        }
    }
    void insert_node(string data) // insert_node_end() din lab2
    {
        int index = hash_function(data[0]); // gasirea indexului in functie de hash_function pt a introduce nodul in table
        node *aux = create_node(data); // crearea nodului, in care este specificata perechea (key, value)
        // verificarea coliziunilor
        if(table[index] == nullptr) // daca pe pozitia index din tabel nu exista niciun nod, table[index] va fi initializat cu datele necesare
        {
            table[index] = aux;
        } else // partea de chaining intre noduri, adaugarea lor intr-o lista
        {
            node *curr = table[index];
            while(curr->next != nullptr) // parcurgerea listei de la inceput pana la ultimul element din lista
            {
                curr = curr->next;
            }
            curr->next = aux;
        }
    }
    node *search_node(string data) // avand un tabel de noduri, cautarea se face dupa cuvant si vor returna toate valorile asociate
    {
        // trebuie gasit indexul corespunzator cuvantului introdus pt a putea localiza lista prin care trebuie iterat
        int index = hash_function(data[0]);
        node *curr = table[index]; // cautarea iterativa incepe din capul listei, adica nodul head corespunzator intrarii de pe pozitia index din tabel
        // cautarea e asemenea intr-o lista simplu inlantuita pnetru a gasi daca un cuvant apartine hash table-ului sau nu
        while(curr != nullptr)
        {
            if(curr->val == data)
            {
                return curr;
            }
            curr = curr->next; // urmatorul nod
        }
        return nullptr; // nodul cu valoarea data nu e gasit
    }
    void remove_node(string data)
    {
        int index = hash_function(data[0]);
        node *del_node = search_node(data);
        node *curr = table[index];
        if(del_node == table[index]) // daca nodul care trebuie sters e capul listei, noul cap al listei e elementul care urmeaza dupa head
        {
            table[index] = table[index]->next; // se muta doar capul listei, restul elementelor nu sunt afectate
        } else
        {
            if(del_node != nullptr) // daca nodul care trebuie sters exista in lista, adica functia search_node nu returneaza nullptr, atunci se vor deplasa restul elementelor
            {
                while(curr != nullptr) // parcurgere linked list pana la tail pentru a gasi nodul aflat imediat inaintea nodului care trebuie sters
                {
                    if(curr->next == del_node)
                    {
                        // partea de unlinking
                        curr->next = del_node->next; // in mom in care campul next al nodului curent pointeaza catre nodul care trebuie sters, se reconstituie legatura pentru a sari peste del_node
                    }
                    curr = curr->next; // deplasare
                }
            }
        }
        delete del_node; // stergerea efectiva pt eliberarea zonei de memorie
    }
};

int main() {
    HashTable dict(26);

    int choice;
    string x;
    char ch;

    do{
        cout<<endl;
        cout<<"1. Inserarea unui cuvant in dictionar\n2. Cautarea unui cuvant\n3. Stergerea unui cuvant\n4. Afisarea cuvintelor curente de la o sectiune\n5. Afisarea dictionarului curent\n6. Iesire meniu\n Tastati varianta aleasa: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Cuvantul de introdus: "; cin>>x;
                dict.insert_node(x);
                break;
            case 2:
                cout<<"Cuvantul de cautat in dictionar: "<<endl; cin>>x;
                if(dict.search_node(x) == nullptr)
                {
                    cout<<"Valoarea nu a fost gasita in lista"<<endl;
                } else
                {
                    cout<<"Valoarea a fost gasita in lista"<<endl;
                }
                break;
            case 3:
                cout<<"Cuvantul de sters din dictionar: "; cin>>x;
                dict.remove_node(x);
                break;
            case 4:
                cout<<"Litera de inceput a cuvintelor: "; cin>>ch;
                cout<<endl<<"Cuvintele curente aflate la sectiunea cu litera "<<ch<<" sunt:"<<endl;
                dict.display_list(ch);
                break;
            case 5:
                cout<<"Cuvintele curente ale dictionarului sunt:"<<endl;
                dict.display();
                break;
            case 6:
                break;
            default:
                cout<<"Invalid"<<endl;
                return 1;
        }
    } while(choice != 6);

    return 0;
}
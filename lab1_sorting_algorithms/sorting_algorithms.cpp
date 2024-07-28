#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void display_array(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void display_subarray(const vector<int> &v, int start, int end)
{
    for(int i = start; i <= end; i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

// bubble sort
void bubble_sort(vector<int> &v)
{
    int length = v.size();
    bool swapped;
    int pass = 0;
    do{
        swapped = false;
        pass++; // nr de parcurgeri complete ale vectorului
        cout<<"Parcurgerea "<<pass<<":"<<endl;
        for(int i = 0; i < length-1; i++)
        {
            if(v[i] > v[i+1])
            {
                swap(v[i], v[i+1]);
                swapped = true;
            }
            display_array(v);
        }
        length--; // se reduce lungimea pt ca fiecare maxim corespunzator fiecarei treceri complete prin vector va fi plasat la final (e iredundant sa parcurgem acea secventa deja sortata)
    } while(swapped);
}

// selection sort
void selection_sort_min(vector<int> &v) // prin selectia minimului
{
    int pass = 0;
    for(int i = 0; i < v.size() - 1; i++)
    {
        pass++;
        cout<<"Parcurgerea "<<pass<<":"<<endl;
        int p = i; // pivotul e initializat cu indexul curent deoarece elementele din vector de un index mai mic decat cel curent au fost deja sortate
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[j] < v[p])
            {
                p = j;// pivotul e de fapt indexul celui mai mic element din vector, care se plaseaza pe prima pozitie
            }
        }
        if(p != i)// daca am gasit minimul curent din vectorul ramas nesortat, interschimbam val curenta cu cea a minimului
        {
            swap(v[i], v[p]);
        }
        display_array(v);
    }
}

// insertion sort
void insertion_sort(vector<int> &v)
{
    int pass = 0;
    for(int i = 1; i < v.size(); i++)
    {
        pass++;
        cout<<"Parcurgerea "<<pass<<":"<<endl;
        int poz = i;
        while(poz > 0 && v[poz-1] > v[poz]) // v[poz]  ar putea fi inlocuita cu o variabila currentvalue pt readability
        {
            swap(v[poz], v[poz-1]);
            poz--;
            display_array(v);
        }
    }
}

// merge sort
void merge(vector<int> &v, int start, int mid, int end)
{
    vector<int> temp(end - start + 1);
    // i e indexul pentru subvectorul din stanga, iar j pentru cel din dreapta
    int i = start, j = mid+1;
    int k = 0; // index pentru temp (temporary vector)

    // strict pt afisare (cum arata subvectorii inainte de merging (dupa ce sunt sortati, dar inca "separati"))
    cout<<"Merging/ Impera: "<<endl;
    display_subarray(v, start, mid);
    display_subarray(v, mid+1, end);

    // imbinare vectori pana cand se ajunge la sfarsitul oricaruia
    while(i <= mid && j <= end)
    {
        // plasare element cel mai mic dintre cei doi subvectori in temp[]
        if(v[i] < v[j])
        {
            temp[k++] = v[i++];
            // incrementare indecsi pt testarea urmatoarelor valori (indexul care ramane neincrementat coresp val care 
            // nu a fost pusa in temp[] la pasul curent, dar care va fi pusa la un mom dat)

            // SAU
            // temp[k] = v[i];
            // k++; i++;
        } else
        {
            temp[k++] = v[j++];
        }
    }

    // daca ne aflam la sfarsitul subvectorului din stanga, inseamna ca vom completa temp cu val ramase in subvectorul din dreapta
    if(i > mid)
    {
        while(j <= end)
        {
            temp[k++] = v[j++];
        }
    } else // sf subvectorului din dreapta => completare val din subvectorul din stanga
    {
        while(i <= mid)
        {
            temp[k++] = v[i++];
        }
    }

    // suprascrierea vectorului v cu elem din temp
    for(int index = 0; index <= end - start; index++)
    {
        v[index + start] = temp[index];
    }

    // vectorul merged
    display_subarray(v, start, end);
}

void merge_sort(vector<int> &v, int start, int end) // sortarea in sine a subvectorilor - divide et impera
{
    if(start >= end) // caz de baza
    {
        return;
    } else // if(start < end)
    {
        int mid = (start+end) / 2;
        // partea de spliting/ divide, apeluri recursive pt formarea de subvectori

        // strict pt afisare:
        cout<<"Spliting/ Divide: "<<endl;
        display_subarray(v, start, mid);
        display_subarray(v, mid+1, end);

        merge_sort(v, start, mid); // sortare prima jumatate a vectorului, vazut ca subvectorul din stanga
        merge_sort(v, mid + 1, end);  // sortare a dous jumatate, subvector dreapta

        // partea de merging/ interclasare a subvectorilor deja sortati
        merge(v, start, mid, end);
    }
}

// quick sort
// elementele mai mari sau egale cu pivotul vor fi mutate in dreapta vectorului, in timp ce celelalte vor fi mutate in stanga
int partition_middle_pivot(vector<int> &v, int start, int end) // stabilim ca val din mijl vectorului este pozitia initiala a pivotului (se alege aleatoriu in general SAU ultima val SAU prima val)
{
    int pivot = v[(start+end)/2], i = start, j = end;

    // strict pt afisare
    cout<<"Inainte de partitionare:"<<endl;
    display_subarray(v, start, end);
    cout<<"Pivot:"<<endl<<pivot<<endl;

    while(i <= j) // se opreste cand i > j
    {
        while(v[j] > pivot) // gasire element din dreapta care ar trebui sa fie in partea stanga
        {
            j--;
            // prima aparitie a unei val mai mici decat pivotul
        }
        while(v[i] < pivot) // gasire element din stanga care ar trebui sa fie in partea dreapta
        {
            i++; // indicele i este mutat spre dreapta pana cand se gaseste un element cu o valoare mai mare decat cea a pivotului
            // prima aparitie a unei val mai mari decat pivotul
        }
        if(i <= j)
        {
            swap(v[i], v[j]);
            // urm pozitii de verificat
            i++;
            j--;

            // strict pt afisare
            cout<<"Dupa partitionare:"<<endl;
            display_subarray(v, start, end);
        }
    }
    return i;
}

void quick_sort(vector<int> &v, int start, int end)
{
    if(start < end)
    {
        int pivot_index = partition_middle_pivot(v, start, end); // pivot_index e indexul de partitionare
        // apeluri recursive pentru a testa valorile aflate pe poz de dinaintea pivotului si dupa el
        quick_sort(v, start, pivot_index - 1); // sortare subvector din stanga
        quick_sort(v, pivot_index, end); // sortare subvector din dreapta
    }
}

// heap sort
// length - lungime vector v
void display_heap(vector<int> v, int length)
{
    for(int i = 0; i < length/2; i++)
    {
        cout<<"Nod parinte: "<<v[i]<<"\t";
        if(2*i+1 < length)
        {
            cout<<"Copil stanga nod<"<<i<<">: " <<v[2*i+1]<<"\t";
        }
        if(2*i+2 < length)
        {
            cout<<"Copil dreapta nod<"<<i<<">: " <<v[2*i+2]<<"\t";
        }
        cout<<endl;
    }
}

void heapify(vector<int> &v, int length, int i) // max_heapify()
{
    // gasire elem maxim intre radacina, copil stang si drept
    int largest = i; // presupunem ca rad e maxima
    int left = 2*i + 1; // stanga
    int right = 2*i + 2; // dreapta

    if(left < length && v[left] > v[largest])
    {
        largest = left;
    }

    if(right < length && v[right] > v[largest])
    {
        largest = right;
    }

    // swap + heapify, daca radacina nu e cea mai mare val
    if(largest != i)
    {
        swap(v[i], v[largest]); // val din radacina se interschimba cu copilul de valoare maxima (stang sau drept)
        heapify(v, length, largest); // recursiv pt fiecare nivel (in adancime)
    }

    // strict pt afisare
    cout<<"Parcurgere:"<<endl;
    display_heap(v, length);
}

void build_heap(vector<int> &v, int length) // curs - buildMaxHeap()
{
    for(int i = length/2-1; i >= 0; i--)
    {
        heapify(v, length, i); // aplicam heapify pt fiecare nod incepand cu penultimul nivel (care in practica are copii (aflati pe ultimul nivel))
    }
}

void heap_sort(vector<int> &v, int length)
{
    build_heap(v, length);
    for(int i = length-1; i >= 0; i--)
    {
        swap(v[0], v[i]); // interschimbarea elementului de la pasul curent cu primul (radacina heap-ului format), insemnand ca acum maximul curent se afla la final
        // v[i] e asadar un element sortat, plasat acum pe poz lui corespunzatoare, eliminat din heap

        // se aplica heapify pt radacina (care acum e v[i]) pt a obtine din nou cel mai mare element pozitionat la radacina heap-ului
        heapify(v, i, 0); // se reduce pt fiecare pas lungimea heap-ului din moment ce unele elemente sunt scoase din heap, ele fiind sortate
    }
}

int main()
{
    vector<int> a;
    /*const int vec_length = 20; // nr maxim de elemente din vector
    const int val_max = 100; // elem din vector sa aiba valori cuprinse intre 0 si 99 (ne vom folosi de restul impartirii la 100)
    srand(time(nullptr)); // un seed pt un generator de numere
    for(int i = 0; i <= vec_length; i++)
    {
        a.push_back(rand() % val_max);
    }*/
    int vec_length;
    cout<<"Introduceti nr de elemente pentru vector:"<<endl; cin>>vec_length;
    for(int i = 0; i < vec_length; i++)
    {
        int val;
        cin>>val;
        a.push_back(val);
    }

    cout<<"Inainte de sortare:"<<endl;
    display_array(a);

    int choice;
    cout<<"1. Selection Sort\n2. Bubble Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n6. Heap Sort\nTastati varianta de sortare aleasa: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
            cout<<"Selection Sort:"<<endl;
            selection_sort_min(a);
            break;
        case 2:
            cout<<"Bubble Sort:"<<endl;
            bubble_sort(a);
            break;
        case 3:
            cout<<"Insertion Sort:"<<endl;
            insertion_sort(a);
            break;
        case 4:
            cout<<"Merge Sort:"<<endl;
            merge_sort(a, 0, a.size() - 1);
            break;
        case 5:
            cout<<"Quick Sort:"<<endl;
            quick_sort(a, 0, a.size() - 1);
            break;
        case 6:
            cout<<"Heap Sort:"<<endl;
            heap_sort(a, a.size());
            break;
        default:
            cout<<"Invalid"<<endl;
            return 1;
    }
    cout<<endl<<"Final:"<<endl;
    display_array(a);

    return 0;
}
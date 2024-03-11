#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector> // std::vector<dataType> vectorName;
#include <ctime>

using namespace std;

void afisareVector(vector<int> v)
{
    size_t length = v.size();
    for(int i = 0; i < length; i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void afisareSubvector(const vector<int> &v, int start, int end)
{
    for(int i = start; i <= end; i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

/** BUBBLE SORT **/
void bubbleSort(vector<int> &v) 
{
    size_t length = v.size();
    bool swapped;
    int pass = 0;
    do {
        swapped = false;
        pass++; // nr de parcurgeri complete ale vectorului
        cout<<"Parcurgerea "<<pass<<":"<<endl;
        for (size_t i = 0; i < length-1; i++) 
        {
            if (v[i] > v[i+1]) 
            {
                swap(v[i], v[i+1]);
                swapped = true;
            }
            afisareVector(v);
        }
        length--; // se reduce lungimea pt ca fiecare maxim corespunzator fiecarei treceri complete prin vector va fi plasat la final (e iredundant sa parcurgem acea secventa deja sortata)
    } while (swapped==true);
}

/** SELECTION SORT **/
void selectionSort_Min(vector<int> &v) // prin selectia minimului
{
    size_t length = v.size();
    int pass = 0;
    for (size_t i = 0; i < length - 1; i++) 
    {
        pass++;
        cout<<"Parcurgerea "<<pass<<":"<<endl;
        size_t p = i; // pivotul e initializat cu indexul curent deoarece elementele din vector de un index mai mic decat cel curent au fost deja sortate
        for (size_t j = i+1; j < length; j++) 
        {
            if (v[j] < v[p]) 
            {
                p = j;// pivotul e de fapt indexul celui mai mic element din vector, care se plaseaza pe prima pozitie
            }
        }
        if (p != i)// daca am gasit minimul curent din vectorul ramas nesortat, interschimbam val curenta cu cea a minimului
        {
            swap(v[i], v[p]);
        }
        afisareVector(v);
    }
}

/** INSERTION SORT **/
void insertionSort(vector<int> &v) 
{
    size_t length = v.size();
    int pass = 0;
    for (size_t i = 1; i < length; i++) 
    {
        pass++;
        cout<<"Parcurgerea "<<pass<<":"<<endl;
        int poz = i;
        while (poz > 0 && v[poz-1] > v[poz]) // v[poz]  ar putea fi inlocuita cu o variabila currentvalue pt readability
        {
            swap(v[poz], v[poz-1]);
            poz--;
            afisareVector(v);
        }
    }
}

/** MERGE SORT **/
void merge(vector<int> &v, int start, int mid, int end)
{   
    vector<int> temp(end - start + 1);
    // i e indexul pentru subvectorul din stanga, iar j pentru cel din dreapta
    int i = start, j = mid+1;
    int k = 0; // index pentru temp (temporary vector)

    // strict pt afisare (cum arata subvectorii inainte de merging (dupa ce sunt sortati, dar inca "separati"))
    cout<<"Merging/ Impera: "<<endl;
    afisareSubvector(v, start, mid);
    afisareSubvector(v, mid+1, end);
    
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
    afisareSubvector(v, start, end);
}

void mergeSort(vector<int> &v, int start, int end) // sortarea in sine a subvectorilor - divide et impera
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
        afisareSubvector(v, start, mid);
        afisareSubvector(v, mid+1, end);

        mergeSort(v, start, mid); // sortare prima jumatate a vectorului, vazut ca subvectorul din stanga
        mergeSort(v, mid+1, end);  // sortare a dous jumatate, subvector dreapta

        // partea de merging/ interclasare a subvectorilor deja sortati
        merge(v, start, mid, end);
    }
}

/** QUICK SORT **/
// elementele mai mari sau egale cu pivotul vor fi mutate in dreapta vectorului, in timp ce celelalte vor fi mutate in stanga
int partition_middlePivot(vector<int> &v, int start, int end) // stabilim ca val din mijl vectorului este pozitia initiala a pivotului (se alege aleatoriu in general SAU ultima val SAU prima val)
{
    int pivot = v[(start+end)/2], i = start, j = end;

    // strict pt afisare
    cout<<"Inainte de partitionare:"<<endl;
    afisareSubvector(v, start, end);
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
            afisareSubvector(v, start, end);
        }
    }
    return i;
}

void quickSort(vector<int> &v, int start, int end)
{
    if(start < end)
    {
        int pivot_index = partition_middlePivot(v, start, end); // pivot_index e indexul de partitionare
        // apeluri recursive pentru a testa valorile aflate pe poz de dinaintea pivotului si dupa el
        quickSort(v, start, pivot_index-1); // sortare subvector din stanga
        quickSort(v, pivot_index, end); // sortare subvector din dreapta
    }
}

/** HEAP SORT **/
// length - lungime vector v
void afisareHeap(vector<int> v, int length)
{
    for (int i = 0; i < length/2; i++) 
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

void heapify(vector<int> &v, int length, int i) // maxHeapify()
{
    // gasire elem maxim intre radacina, copil stang si drept
    int largest = i; // presupunem ca rad e maxima
    int left = 2*i + 1; // stanga
    int right = 2*i + 2; // dreapta
  
    if (left < length && v[left] > v[largest])
    {
        largest = left;
    }

    if (right < length && v[right] > v[largest])
    {
        largest = right;
    }
  
    // swap + heapify, daca radacina nu e cea mai mare val
    if (largest != i) 
    {
        swap(v[i], v[largest]); // val din radacina se interschimba cu copilul de valoare maxima (stang sau drept)
        heapify(v, length, largest); // recursiv pt fiecare nivel (in adancime)
    }

    // strict pt afisare
    cout<<"Parcurgere:"<<endl;
    afisareHeap(v, length);
}

void buildHeap(vector<int> &v, int length) // curs - buildMaxHeap()
{
    for (int i = length/2-1; i >= 0; i--)
    {
        heapify(v, length, i); // aplicam heapify pt fiecare nod incepand cu penultimul nivel (care in practica are copii (aflati pe ultimul nivel))
    }
}

void heapSort(vector<int> &v, int length)
{
    buildHeap(v, length);
    for (int i = length-1; i >= 0; i--) 
    {
        swap(v[0], v[i]); // interschimbarea elementului de la pasul curent cu primul (radacina heap-ului format), insemnand ca acum maximul curent se afla la final
        // v[0] e asadar un element sortat, plasat acum pe poz lui corespunzatoare, eliminat din heap
    
        // se aplica heapify pt radacina (care acum e v[i]) pt a obtine din nou cel mai mare element pozitionat la radacina heap-ului
        heapify(v, i, 0); // se reduce pt fiecare pas lungimea heap-ului din moment ce unele elemente sunt scoase din heap, ele fiind sortate
    }
}

/** Sorting Comprehensive Low-Level Visualisation**/
int main()
{
    vector<int> a;
    const size_t vec_length = 20; // nr maxim de elemente din vector
    const size_t val_max = 100; // elem din vector sa aiba valori cuprinse intre 0 si 99 (ne vom folosi de restul impartirii la 100)
    srand(time(nullptr)); // un seed pt un generator de numere
    for(size_t i = 0; i <= vec_length; i++)
    {
        a.push_back(rand() % val_max);
    }

    cout<<"Inainte de sortare:"<<endl;
    afisareVector(a);

    int choice;
    cout<<"1. Selection Sort\n2. Bubble Sort\n3. Insertion Sort\n4. Merge Sort\n5. Quick Sort\n6. Heap Sort\nTastati varianta de sortare aleasa: ";
    cin>>choice;

    switch(choice)
    {
        case 1:
            cout<<"Selection Sort:"<<endl;
            selectionSort_Min(a);
            break;
        case 2:
            cout<<"Bubble Sort:"<<endl;
            bubbleSort(a);
            break;
        case 3:
            cout<<"Insertion Sort:"<<endl;
            insertionSort(a);
            break;
        case 4:
            cout<<"Merge Sort:"<<endl;
            mergeSort(a, 0, a.size()-1);
            break;
        case 5:
            cout<<"Quick Sort:"<<endl;
            quickSort(a, 0, a.size()-1);
            break;
        case 6:
            cout<<"Heap Sort:"<<endl;
            heapSort(a, a.size());
            break;
        default:
            cout<<"Invalid"<<endl;
            return 1;
    }
    cout<<endl<<"Final:"<<endl;
    afisareVector(a);

    return 0;
}
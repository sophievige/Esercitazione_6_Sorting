#include <iostream>
#include <vector>
#include <chrono>
#include "SortingAlgorithm.hpp"
#include <numeric>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
double testBubbleSort (vector<T>& v){

    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now(); //tempo adesso, ora va convertito nell'unità di misura che mi interessa
    SortLibrary::BubbleSort(v);
    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
    double duration= std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_begin).count();

    return duration;
}

template <typename T>
double testMergeSort (vector<T>& v){

    std::chrono::steady_clock::time_point t_begin = std::chrono::steady_clock::now(); //tempo adesso, ora va convertito nell'unità di misura che mi interessa
    SortLibrary::MergeSort(v);
    std::chrono::steady_clock::time_point t_end = std::chrono::steady_clock::now();
    double duration= std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_begin).count();

    return duration;
}

template <typename T>
void stampaVettore (vector<T>& v){ //per verificare
    for (unsigned int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int argc, char **argv) //argc è il numero di argomenti della command line, argv il vettore di tali argomenti
{   unsigned int n;
    stringstream ss;
    ss << argv[1];
    ss >> n;

    unsigned int numIter=10;

    //primo test: vettori già ordinati in modo crescente (bubblesort dovrebbe essere O(n) e mergesort O(nlog_2(n)))
    double mediaBS =0.0;
    double mediaMS = 0.0;
    vector <int> v(n);
    iota(v.begin(), v.end(), 0);
    for (unsigned int i=0; i<numIter; i++){
        mediaBS = mediaBS + testBubbleSort(v); //non serve copiare v perché in questo caso è già ordinato, quindi non lo cambia
        mediaMS = mediaMS + testMergeSort(v);
    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori gia' ordinati: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori gia' ordinati: " << mediaMS << " nanosecondi" << endl;

    //secondo test: vettori ordinati in modo decrescente
    mediaBS =0.0;
    mediaMS = 0.0;
    vector <int> v1(n);
    vector <int> v2(n);
    for (unsigned int i=0; i<numIter; i++){
        int dim=n;
        generate(v1.begin(), v1.end(), [&dim] () {return dim--;});
        v2=v1;
        mediaBS = mediaBS + testBubbleSort(v1); //copio il vettore perché la funzione test (e anche BubbleSort) lo modificano
        mediaMS = mediaMS + testMergeSort(v2);

    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori ordinati in ordine inverso: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori ordinati in ordine inverso: " << mediaMS << " nanosecondi" << endl;


    //terzo test: vettori in ordine crescente con primo quarto randomico
    mediaBS =0.0;
    mediaMS = 0.0;
    for (unsigned int i=0; i<numIter; i++){
        v1=v; //per riordinarlo
        for (unsigned int j=0; j<(n/4); j++){
            v1[j]=rand() % n; //così li ho tra 0 e n
        }
        v2=v1;
        mediaBS = mediaBS + testBubbleSort(v1);
        mediaMS = mediaMS + testMergeSort(v2);
    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori con primo quarto randomico: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori con primo quarto randomico: " << mediaMS << " nanosecondi" << endl;

    //quarto test: vettori in ordine crescente con ultimo quarto randomico
    mediaBS =0.0;
    mediaMS = 0.0;
    for (unsigned int i=0; i<numIter; i++){
        v1=v; //per riordinarlo
        for (unsigned int j=n-1; j>(0.75*n); j--){
            v1[j]=rand() % n; //così li ho tra 0 e n
        }
        v2=v1;
        mediaBS = mediaBS + testBubbleSort(v1);
        mediaMS = mediaMS + testMergeSort(v2);
    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori con ultimo quarto randomico: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori con ultimo quarto randomico: " << mediaMS << " nanosecondi" << endl;

    //quinto test: vettori in ordine crescente con prima metà randomica
    mediaBS =0.0;
    mediaMS = 0.0;
    for (unsigned int i=0; i<numIter; i++){
        v1=v; //per riordinarlo
        for (unsigned int j=0; j<(n/2); j++){
            v1[j]=rand() % n; //così li ho tra 0 e n
        }
        v2=v1;
        mediaBS = mediaBS + testBubbleSort(v1);
        mediaMS = mediaMS + testMergeSort(v2);
    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori con prima meta' randomica: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori con prima meta' randomica: " << mediaMS << " nanosecondi" << endl;

    //sesto test: vettori in ordine crescente con ultima metà randomica
    mediaBS =0.0;
    mediaMS = 0.0;
    for (unsigned int i=0; i<numIter; i++){
        v1=v; //per riordinarlo
        for (unsigned int j=n-1; j>((n-1)/2); j--){
            v1[j]=rand() % n; //così li ho tra 0 e n
        }
        v2=v1;
        mediaBS = mediaBS + testBubbleSort(v1);
        mediaMS = mediaMS + testMergeSort(v2);
    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori con ultima meta' randomica: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori con ultima meta' randomica: " << mediaMS << " nanosecondi" << endl;

    //settimo test: vettori completamente randomici
    mediaBS =0.0;
    mediaMS = 0.0;
    for (unsigned int i=0; i<numIter; i++){
        v1=v; //per riordinarlo
        for (unsigned int j=0; j<n; j++){
            v1[j]=rand() % n; //così li ho tra 0 e n
        }
        v2=v1;
        mediaBS = mediaBS + testBubbleSort(v1);
        mediaMS = mediaMS + testMergeSort(v2);
    }
    mediaBS=mediaBS/numIter;
    mediaMS=mediaMS/numIter;

    cout << "BS su vettori randomici: " << mediaBS << " nanosecondi" << endl;
    cout << "MS su vettori randomici: " << mediaMS << " nanosecondi" << endl;

    return 0;
}

//risultati (con dimensione del vettore 1000):
//merge è abbastanza stabile ed è più veloce di bubble in tutti i casi tranne in quello del vettore già ordinato
//(in quello con solo primo quarto ordinato è comunque più veloce, ma sono abbstanza vicini)
//bubble invece è rallentato in particolare quando la parte finale del vettore diventa non ordinata

//con dimensione del vettore inferiore, in alcuni casi bubblesort è comunque più veloce di mergesort (ad esempio con 100 è sempre più veloce)

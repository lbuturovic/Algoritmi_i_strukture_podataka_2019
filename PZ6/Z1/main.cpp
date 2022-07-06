#include <iostream>
#include <fstream>
#include <ctime>
template <typename Tip>
void bubble_sort (Tip* niz, int vel)
{
    for(int i = vel - 1; i>=1; i--) {
        for(int j = 1; j<=i; j++) {
            if(niz[j-1]>niz[j]) {
                Tip pom = niz[j-1];
                niz[j-1] = niz[j];
                niz[j] = pom;
            }

        }
    }
}

template<typename Tip>
void zamijeni(Tip& el1, Tip& el2)
{
    Tip pom = el1;
    el1 = el2;
    el2 = pom;
}

/*template<typename Tip>
int particija(Tip* niz, int poc, int kraj){
    Tip pivot = niz[poc];
    int i = poc + 1;
    while(i<=kraj && niz[i]<pivot)
    i++;
    for(int j=i+1; j<kraj; j++){
        if(niz[j]<pivot){
            zamijeni(niz[j],niz[i]);
            i++;
        }
    }
    zamijeni(niz[poc],niz[i-1]);
    return (i-1);
} */
template<typename Tip>
int particija(Tip* niz, int poc,int kraj)
{
    int i = poc - 1;
    Tip pivot = niz[kraj];
    for(int j = poc; j<=kraj-1; j++) {
        if(niz[j]<=pivot) {
            i++;
            zamijeni(niz[i],niz[j]);

        }

    }
    zamijeni(niz[i+1],niz[kraj]);
    return i+1;

}
template <typename Tip>
void quick_sort_pom(Tip* niz, int poc, int kraj)
{
//   vel = vel-1; //da postane indeks
    if(poc<kraj) {
        int indeks = particija(niz,poc,kraj);
        quick_sort_pom(niz,poc,indeks-1);
        quick_sort_pom(niz,indeks+1,kraj);

    }

}
template<typename Tip>
void quick_sort(Tip* niz, int vel)
{
    quick_sort_pom(niz,0,vel-1);
}
template < typename Tip>
void selection_sort(Tip* niz, int vel)
{
    int min_indeks = 0;
    for(int i=0; i< vel - 1; i++) {
        min_indeks = i;
        Tip min = niz[i];
        for(int j = i+1; j< vel; j++) {
            if(niz[j]<niz[min_indeks]) {
                min = niz[j];
                min_indeks = j;
            }
        }
        niz[min_indeks] = niz[i];
        niz[i] = min;

    }
}

template <typename Tip>
void merge(Tip* niz,int pocetak, int sredina, int kraj)
{

    int n1 = sredina - pocetak + 1; //velicina lijevog podniza
    int n2 = kraj - sredina; //veicina desnog podniza
    Tip* lijevi = new Tip[n1];
    Tip* desni = new Tip [n2];
    int i = 0;
    int j = 0;
    int k = 0;
    for(i=0; i<n1; i++)
        lijevi[i] = niz[pocetak+i]; // pocinje od pocetka

    for(j=0; j<n2; j++)
        desni[j] = niz[sredina+1+j]; // pocinje od prvog elementa nakon srednjeg clana

    i = 0;
    j = 0;
    k = pocetak;
    while(i<n1 && j<n2) {
        if(lijevi[i]<=desni[j]) {
            niz[k] = lijevi[i];
            i++;
        } else {
            niz[k] = desni[j];
            j++;
        }

        k++;
    }

    while(i<n1)
        niz[k++] = lijevi[i++];   //upisuje preostale elemente
    while(j<n2)
        niz[k++] = desni[j++];
    delete[] lijevi;
    delete[] desni;

}

template <typename Tip>
void merge_sort_pom(Tip* niz, int kraj, int poc=0)   //vel je kraj, poc je pocetak
{
    // vel = vel-1; // da postane indeks posljednjeg
    if(poc<kraj) {

        int sredina = poc + (kraj-poc)/2;
        merge_sort_pom(niz,sredina,poc);
        merge_sort_pom(niz,kraj,sredina+1);
        merge(niz,poc,sredina,kraj);


    }

}
template<typename Tip>
void merge_sort(Tip* niz, int vel)
{
    merge_sort_pom(niz,vel-1);
}


void ucitaj(std::string datoteka, int*&niz, int &velicina)
{

    std::ifstream ulaz(datoteka);
    if(!ulaz) {
        std::cout << "Neuspjesno otvaranje datoteke";
        return;
    }
    int br;
    int vel = 0;
    int i = 0;
    while(ulaz>>br) {
        vel++;
        if(ulaz.eof()) break;
    }
    niz = new int[vel];
    ulaz.seekg(0,std::ios::beg);
    while(ulaz>>br)
        niz[i++] = br;
    velicina = vel;
    ulaz.close();
    /*  std::cout << "Ucitaj: ";
      for(int i=0; i<velicina; i++)
      std::cout << niz[i] << " "; */

}
void generisi(std::string datoteka, int vel)
{
    std::ofstream izlaz(datoteka);
    if(!izlaz) {
        std::cout << "Neuspjesno otvaranje datoteke";
        return;
    }
    for(int i=0; i<vel; i++) {
        izlaz << rand()%15000;
        if (i<vel-1) izlaz <<" ";

    }
    izlaz.close();
}
void funkcija(std::string datoteka)
{
    int* niz;
    int vel;
    ucitaj(datoteka,niz,vel);
    std::cout << "Odaberite algoritam sortiranja: \n";
    std::cout << "Za bubble_sort pritisnite 1\n";
    std::cout << "Za selection_sort pritisnite 2\n";
    std::cout << "Za quick_sort pritisnite 3\n";
    std::cout << "Za merge_sort pritisnite 4\n";
    int izbor=0;
    do {
        std::cin >> izbor;
    } while(izbor<1 || izbor>4);

    clock_t poc;
    clock_t kraj;
    if(izbor==1) {
        poc = clock();
        bubble_sort(niz,vel);
        kraj = clock();
    }

    if(izbor==2) {
        poc = clock();
        selection_sort(niz,vel);
        kraj = clock();
    }
    if(izbor==3) {
        poc = clock();
        quick_sort(niz,vel);
        kraj = clock();
    }
    if(izbor==4) {
        poc = clock();
        merge_sort(niz,vel);
        kraj = clock();
    }
    for(int i=1; i<vel; i++)
        if(niz[i]<niz[i-1]) {
            std::cout << "Niz nije sortiran!";
            return;
        }
    std::ofstream izlazni("izlazna.txt");
    for(int i=0; i<vel; i++) {
        izlazni << niz[i] << " ";
    }

    int izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000);
    std::cout << "Sortiranje se izvrsavalo " << izvrsenje << " ms." << std::endl;
    delete [] niz;
    izlazni.close();
}





int main()
{
    /*  generisi("lejla.txt",150);
      int* niz;
      int velicina;
      // generisi("lejla.txt",250);
       ucitaj("lejla.txt",niz,velicina);
       for(int i=0; i< velicina; i++)
       std::cout << niz[i] << " ";
       delete [] niz;*/
    generisi("lejla.txt",15000);
    generisi("izlazna.txt",0);
    funkcija("lejla.txt");
    return 0;
}

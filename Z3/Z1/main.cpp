#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

void radixSort(vector<int> &a)
{
    int n = a.size();
    int max = *(std::max_element(a.begin(),a.end()));
    list<int> lista[10];
    int brojCifara=0;
    do {
        max = max/10;
        brojCifara++;
    } while(max!=0);


    int trenutnaCifra;
    int m=1;
    for(int j=0; j<brojCifara; j++) {
        if(j==0) m=1;
        else m*=10;
        for(int i=0; i<n; i++) {
            trenutnaCifra = (a[i]/m)%10;
            lista[trenutnaCifra].push_back(a[i]);
        }
        int brojac = 0;
        for(int i=0; i<10; i++) {  //prolazak kroz liste sa trenutnom cifrom
            while(!lista[i].empty()) {
                a[brojac++] = *(lista[i].begin());  //ovisno od iteracije stavlja elemente na "svoje" mjesto
                lista[i].erase(lista[i].begin());
            }

        }
    }

}
int roditelj(int i)
{
    int r = (i-1)/2;
    return r;
}

int lijevoDijete(int i)
{
    return 2*i+1;
}
int desnoDijete(int i)
{
    return 2*i+2;
}
bool jeLiList(int velicina,int i)
{
    return i>=velicina/2 && i<velicina;
}
void popraviGore(vector<int> &v, int i)
{
    while(i>0 && v[i]>v[roditelj(i)]) {
        int r = roditelj(i);
        int pom = v[i];
        v[i] = v[r];
        v[r] = pom;
        i = r;
    }
}
void popraviDole(vector<int> &v,int i,int velicina)
{
    int indeksVeceg;
    int indeksManjeg;
    while(!jeLiList(velicina,i)) {

        indeksVeceg = lijevoDijete(i);
        indeksManjeg = desnoDijete(i);
        if(indeksManjeg<velicina && v[indeksManjeg]>v[indeksVeceg]) {
            indeksManjeg = indeksVeceg;
            indeksVeceg = desnoDijete(i);
        }
        if(v[i]>v[indeksVeceg]) return;  //sve je okej, ne treba dalje provjeravati
        int pom = v[i];
        v[i] = v[indeksVeceg];
        v[indeksVeceg] = pom;
        i = indeksVeceg;
    }
}
void stvoriGomilu(vector<int> &a)
{
    for(int i=a.size()/2; i>=0; i--) {
        popraviDole(a,i,a.size());
    }

}
void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina)
{
    if(velicina==a.size()) a.push_back(umetnuti);
    else a[velicina] = umetnuti;
    velicina++;
    popraviGore(a,velicina-1);
}
int izbaciPrvi(vector<int> &a, int &velicina)
{
    if(velicina==0) cout << "Gomila je prazna\n";
    int pom = a[0];
    a[0] = a[velicina-1];
    a[velicina-1] = pom;
    velicina--;
    if(velicina!=0) popraviDole(a,0,velicina);
    return a[0];
}

void gomilaSort(vector<int> &a)
{
    stvoriGomilu(a);
    int velicina = a.size();
    int pom;
    for(int i=velicina-1; i>0; i--) {
        pom = a[0];
        a[0] = a[velicina - 1];
        a[velicina-1] = pom;
        velicina--;
        popraviDole(a,0,velicina);
    }
}
int main()
{
    vector<int> v = {12,45828,2,1,3};
    gomilaSort(v);
    for(int i=0; i<v.size(); i++)
        cout << v[i] <<" ";
    return 0;
}

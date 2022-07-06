#include <iostream>
#include <cmath>
#include<vector>
#include<string>
#include <ctime>
unsigned int djbhash(std::string ulaz, unsigned int max) {
	unsigned int suma=5381; 
// 5381 je pocetna vrijednost 
// koja poboljsava distribuciju
	for (int i(0); i<ulaz.length(); i++)
		suma = suma*33 + ulaz[i];
	return suma % max;
}
template <typename Tip1, typename Tip2>
class Mapa
{
public:
    Mapa() {}
    virtual ~Mapa() {}
    virtual int brojElemenata() const = 0;
    virtual Tip2& operator[](Tip1 kljuc) = 0;
    virtual const Tip2 operator[](const Tip1 kljuc) const = 0;
    virtual void obrisi() = 0;
    virtual  void obrisi(const Tip1& kljuc) = 0;
    Mapa (const Mapa& m) {}
    Mapa& operator = (const Mapa& m) {}

};

template <typename Tip1, typename Tip2>
class NizMapa : public Mapa<Tip1,Tip2>
{
    int brojEl=0;
    std::pair<Tip1,Tip2>* mapa;
    int kapacitet = 20;

public:
    NizMapa()
    {
        mapa = new std::pair<Tip1, Tip2> [20];
    }

    ~NizMapa()
    {
        delete [] mapa;
    }

    int brojElemenata() const
    {
        return brojEl;
    }

    Tip2& operator[] (Tip1 kljuc)
    {
        int i = 0;
        for(i = 0; i<brojEl; i++) {
            if(mapa[i].first==kljuc) return mapa[i].second;
        }

        if(brojEl>=kapacitet) {
            kapacitet = kapacitet*2;
            std::pair<Tip1,Tip2>* nova = new std::pair<Tip1, Tip2> [kapacitet];
            for(int i = 0; i<brojEl; i++) {
                nova[i].first = mapa[i].first;
                nova[i].second = mapa[i].second;
            }
            delete [] mapa;
            mapa = nova;
        }
        mapa[i].first = kljuc;
        mapa[i].second = Tip2();
        brojEl++;
        return mapa[i].second;
    }

    const Tip2 operator[](const Tip1 kljuc) const
    {
        for(int i = 0; i<brojEl; i++) {
            if(mapa[i].first==kljuc) {
                return mapa[i].second;
            }
        }

        return Tip2();

    }

    void obrisi()
    {
        delete [] mapa;
        mapa = new std::pair<Tip1, Tip2> [20];
        brojEl = 0;
        kapacitet = 20;

    }

    void obrisi(const Tip1& kljuc)
    {

        for(int i = 0; i<brojEl; i++) {

            if(mapa[i].first == kljuc) {

                for(int j=i+1; j<brojEl; j++)
                    mapa[j-1] = mapa[j];

                brojEl--;
                return;
            }


        }
    }

    NizMapa (const NizMapa& m)
    {
        kapacitet = m.kapacitet;
        brojEl = m.brojEl;
        // delete [] mapa;
        mapa = new std::pair<Tip1, Tip2> [kapacitet];
        for(int i = 0; i<brojEl; i++) {
            mapa[i] = m.mapa[i];
        }
    }

    NizMapa& operator = (const NizMapa& m)
    {
        if(this == &m) return *this;
        kapacitet = m.kapacitet;
        brojEl = m.brojEl;
        delete [] mapa;
        mapa = new std::pair<Tip1, Tip2> [kapacitet];
        for(int i = 0; i<brojEl; i++) {
            mapa[i] = m.mapa[i];
        }

        return *this;
    }


};

template <typename Tip1, typename Tip2>
struct Cvor {
    Tip1 kljuc;
    Tip2 element;
    Cvor *lijevo=nullptr, *desno=nullptr, *roditelj=nullptr;
    Cvor(Tip1 k)
    {
        kljuc = k;
        element = Tip2();
        lijevo = nullptr;
        desno = nullptr;
        roditelj = nullptr;
    }
    Cvor(){} 
    
};

template <typename Tip1, typename Tip2>
class BinStabloMapa : public Mapa<Tip1, Tip2>
{
    Cvor<Tip1,Tip2>* korijen;
    int brojelemenata;

public:
    void brisi(Cvor<Tip1,Tip2>* k)
    {
            if(!k) return;
            brisi(k->lijevo);
            brisi(k->desno);
            delete k;
            k = nullptr;
        
    }
    void obrisi()
    {
        brisi(korijen);
        korijen = nullptr;
        brojelemenata = 0;
    }
    ~BinStabloMapa()
    {
        brisi(korijen);
        //obrisi();
        
    }
    BinStabloMapa()
    {
        korijen = nullptr;
        brojelemenata = 0;
    }
    int brojElemenata() const
    {
        return brojelemenata;
    }
    Cvor<Tip1, Tip2>* traziKljuc(Cvor<Tip1,Tip2>* k, Tip1 kljuc) const
    {
        if(!k || k->kljuc==kljuc) return k;
        else if(kljuc>k->kljuc) return traziKljuc(k->desno, kljuc);
        else if(kljuc<k->kljuc) return traziKljuc(k->lijevo, kljuc);
    }
    Cvor<Tip1,Tip2>* umetni2 (Tip1 &kljuc, Cvor<Tip1,Tip2>* &c){
        if(!c){
            c = new Cvor<Tip1,Tip2>(kljuc);
            if(korijen==nullptr) korijen = c;
            brojelemenata++;
        }
        if(kljuc==c->kljuc) return c;
        if(kljuc<c->kljuc) return umetni2(kljuc,c->lijevo);
        return umetni2(kljuc,c->desno);
    }
    void umetni(Cvor<Tip1,Tip2>* &k, Cvor<Tip1,Tip2>* &novi)
    {
        /*   if(k==nullptr) return new Cvor<Tip1,Tip2>(kljuc);
           if(kljuc<k->kljuc){
               Cvor<Tip1, Tip2>* lijevi = umetni(k->lijevo,kljuc);
               k->lijevo = lijevi;
               lijevi->roditelj = k;
               return lijevi;
           }
           if(kljuc>k->kljuc){
               Cvor<Tip1, Tip2>* desni = umetni(k->desno,kljuc);
               k->desno = desni;
               desni->roditelj = k;
               return desni;
           } */
        Tip1 kljuc = novi->kljuc;
        Cvor<Tip1,Tip2>* tekuci = k;
        Cvor<Tip1,Tip2>* roditeljTekuceg = nullptr;
        while(tekuci!=nullptr) {
            roditeljTekuceg = tekuci;
            if(kljuc<tekuci->kljuc) {
                tekuci = tekuci->lijevo;
            } else tekuci = tekuci->desno;
        }
        if(roditeljTekuceg==nullptr) korijen = novi;
        else if(kljuc<roditeljTekuceg->kljuc) roditeljTekuceg->lijevo = novi;
        else roditeljTekuceg->desno = novi;
       // novi->roditelj = roditeljTekuceg;
      //  return novi;
    }
    Tip2& operator [](Tip1 kljuc)
    {
     /*   Cvor<Tip1, Tip2>* c = traziKljuc(korijen, kljuc);
        if(c) return c->element;
        Cvor<Tip1,Tip2>* novi = new Cvor<Tip1,Tip2>(kljuc);
        if(!korijen) korijen = novi;
        else umetni(korijen,novi);
        // if(brojelemenata==0) korijen = novi;
        brojelemenata++;
        return novi->element; */
        Cvor<Tip1,Tip2>* novi = umetni2(kljuc,korijen);
       // if(!korijen) korijen = novi;
        return novi->element;
    }

    const Tip2 operator [](const Tip1 kljuc) const
    {
        Cvor<Tip1, Tip2>* c = traziKljuc(korijen, kljuc);
        if(c) return c->element;
        /* Cvor<Tip1, Tip2>* cc = umetni(korijen,kljuc);
         brojelemenata++;
         return cc->element;*/
        return Tip2();
    }

    Cvor<Tip1,Tip2>* kopirajStablo(Cvor<Tip1,Tip2>* k)
    {
        Cvor<Tip1, Tip2>* noviC  = nullptr;
        if (!k) return nullptr;
        else {
        noviC = new Cvor<Tip1, Tip2>(k->kljuc);
        noviC->element = k->element;
       // Cvor<Tip1, Tip2>* lijevi = kopirajStablo(k->lijevo);
        noviC->lijevo = kopirajStablo(k->lijevo);
      //  lijevi->roditelj = noviC;
       // Cvor<Tip1, Tip2>* desni = kopirajStablo(k->desno);
        noviC->desno = kopirajStablo(k->desno);
        }
      //  desni->roditelj = noviC;
        return noviC;

    }
    BinStabloMapa (const BinStabloMapa& m)
    {
        korijen = kopirajStablo(m.korijen);
        brojelemenata = m.brojelemenata;
    }
    BinStabloMapa& operator =(const BinStabloMapa& m)
    {
        if(m.korijen==korijen) return *this;
        korijen = nullptr;
        obrisi();
        korijen = kopirajStablo(m.korijen);
        brojelemenata = m.brojelemenata;
        return *this;
    }
    void obrisi(const Tip1& kljuc)
    {
        if(!korijen) return;
        Cvor<Tip1,Tip2>* p = korijen;
        Cvor<Tip1,Tip2>* roditelj = nullptr;
        Cvor<Tip1,Tip2>* q = nullptr;
        Cvor<Tip1,Tip2>* tmp = nullptr;
        Cvor<Tip1,Tip2>*m = nullptr;
        Cvor<Tip1,Tip2>*rp = nullptr;
        Cvor<Tip1,Tip2>*pm = nullptr;

        while(p!=nullptr && kljuc!=p->kljuc) {
            roditelj = p;
            if(kljuc<p->kljuc)  p = p->lijevo;
            else p = p->desno;
        }
        if(p==nullptr) return; //nije pronadjen
        if(p->lijevo==nullptr) m = p->desno;
        else {
            if(p->desno==nullptr) m = p->lijevo;
            else { //ako ima oba djeteta
                pm = p;
                m = p->lijevo;
                tmp = m->desno;
                while (tmp!=0) {
                    pm = m;
                    m = tmp;
                    tmp = m->desno; // m je najdesniji u desnom podstablu lijevog podtabla, a pm mu je parent
                }
                if(pm!=p) {
                    pm->desno = m->lijevo;
                   // pm->desno->roditelj = pm;
                     m->lijevo = p->lijevo;
                }
                m->desno = p->desno;
                // p->desno->roditelj = m;
                //p->lijevo->roditelj= m;
            }
        }
        if(roditelj==nullptr) {

            korijen = m;
             //  m->roditelj = nullptr;
        } else {
            if(p == roditelj->lijevo) roditelj->lijevo = m;
            else roditelj->desno = m;
        }
      //  if(m->desno!=nullptr) m->desno->roditelj = roditelj;
      //    if(m->lijevo!=nullptr) m->lijevo->roditelj = roditelj;
        brojelemenata--;
        delete p;
        p = nullptr;

    }

};

template<typename Tip1, typename Tip2>
class HashMapa: public Mapa<Tip1, Tip2>
{

    int brojelemenata;
    mutable int zabrisanje = -1;
    Tip1** kljucevi;
    Tip2** vrijednosti;
    int kapacitet = 20;
    unsigned int (*hash)(Tip1,unsigned int);

public:

    HashMapa()
    {
        brojelemenata = 0;
        kapacitet = 20;
        kljucevi = new Tip1*[20] {};
        vrijednosti = new Tip2*[20] {};
        /*for(int i=0; i<kapacitet; i++) {
            kljucevi[i] = new Tip1;
            vrijednosti[i] = new Tip2;
        } */
        // mapa = new std::pair<Tip1, Tip2>* [20];
        hash = nullptr;
    }

    ~HashMapa()
    {
        obrisi();
        delete [] kljucevi;
        kljucevi = nullptr;
        delete [] vrijednosti;
        vrijednosti = nullptr;
    }

    void obrisi(const Tip1& kljuc)
    {
        try {
            std::pair<Tip1, Tip2>* par = hash_trazi(kljuc);
            if(par) {
                delete par;
                *kljucevi[zabrisanje] = Tip1();
                *vrijednosti[zabrisanje] = Tip2();
                brojelemenata--;
            }
        } catch(std::logic_error e) {
            throw;
        }


    }
    void obrisi()
    {
        for(int i=0; i<kapacitet; i++) {
            delete kljucevi[i];
            kljucevi[i] = nullptr;
            delete vrijednosti[i];
            vrijednosti[i] = nullptr;
        }

        brojelemenata = 0;
    }
    int brojElemenata() const
    {
        return brojelemenata;
    }

    HashMapa(const HashMapa& m)
    {

        brojelemenata = m.brojelemenata;
        kapacitet = m.kapacitet;
        hash = m.hash;
        kljucevi = new Tip1* [kapacitet];
        vrijednosti = new Tip2*[kapacitet];
        for(int i=0; i<kapacitet; i++) {
            if(m.kljucevi[i]==nullptr) kljucevi[i] = nullptr;
            else
                kljucevi[i] = new Tip1(*(m.kljucevi[i]));
            if(m.vrijednosti[i]==nullptr) vrijednosti[i] = nullptr;
            else
                vrijednosti[i] = new Tip2(*(m.vrijednosti[i]));
        }
    }

    HashMapa& operator =(const HashMapa& m)
    {
        if(this==&m) return *this;
        obrisi();
        kapacitet = m.kapacitet;
        brojelemenata = m.brojelemenata;
        hash = m.hash;
        delete [] kljucevi;
        delete [] vrijednosti;
        kljucevi = new Tip1* [kapacitet];
        vrijednosti = new Tip2*[kapacitet];
        for(int i=0; i<kapacitet; i++) {
            if(m.kljucevi[i]==nullptr) kljucevi[i] = nullptr;
            else
                kljucevi[i] = new Tip1(*(m.kljucevi[i]));
            if(m.vrijednosti[i]==nullptr) vrijednosti[i] = nullptr;
            else
                vrijednosti[i] = new Tip2(*(m.vrijednosti[i]));
        }

        return *this;
    }

    void definisiHashFunkciju (unsigned int (*fun)(Tip1,unsigned int))
    {
        hash = fun;
    }

    std::pair<Tip1,Tip2>* hash_trazi (Tip1 kljuc) const
    {
        std::pair<Tip1,Tip2>* par = nullptr;
        unsigned int i = 0;
        unsigned int j = 0;
        if(hash==nullptr) throw std::logic_error ("Hash funkcija nije definisana.");
        j = (*hash)(kljuc,kapacitet);
        /*   if(kljucevi[j]==nullptr) return nullptr;
           if(*(kljucevi[j]) == kljuc) {
               par = new std::pair<Tip1, Tip2>;
               par->first = kljuc;
               par->second = *vrijednosti[j];
               zabrisanje = j;
               return par;
           } */
        int pozicija = j;
        int brojac = 0;
        do {
            if(kljucevi[j]==nullptr) return nullptr;
            if(*(kljucevi[j])==kljuc) {
                par = new std::pair<Tip1, Tip2>;
                par->first = kljuc;
                par->second = *vrijednosti[j];
                zabrisanje = j;
                return par;
            }
            if(j==kapacitet-1) j = 0;
            else j++;
            if(brojac==kapacitet) break;
            brojac++;
        } while(j!=pozicija);
        return nullptr;
    }

    Tip2& operator [](Tip1 kljuc)
    {
        try {
            std::pair<Tip1, Tip2>* par = hash_trazi(kljuc);
            if(par) {
                delete par;
                return *vrijednosti[zabrisanje];
            }
        } catch(...) {
            throw;
        }

        unsigned int j = 0;
        if(!hash) throw std::logic_error("Hash funkcija nije definisana.");
        if(brojelemenata==kapacitet) {
            Tip1** novikljucevi = new Tip1* [kapacitet*2] {};
            Tip2** novevrijednosti = new Tip2* [kapacitet*2] {};
            int i = 0;
            for(i=0; i<kapacitet; i++) {
                if(kljucevi[i])
                    novikljucevi[i] = new Tip1 (*kljucevi[i]);
                if(vrijednosti[i])
                    novevrijednosti[i] = new Tip2 (*vrijednosti[i]);
                delete kljucevi[i];
                delete vrijednosti[i];
            }
            delete [] kljucevi;
            delete [] vrijednosti;
            kljucevi = novikljucevi;
            vrijednosti = novevrijednosti;
            kapacitet = kapacitet*2;
        }
        j = (*hash)(kljuc,kapacitet);
        /*    if(kljucevi[j]==nullptr || ((*vrijednosti[j])) == Tip2() && (*(kljucevi[j]))==Tip1()) {
                delete kljucevi[j];
                delete vrijednosti[j];
                kljucevi[j] = new Tip1(kljuc);
                vrijednosti[j] = new Tip2();
                brojelemenata++;
                return *vrijednosti[j];
            } else if(*(kljucevi[j])== kljuc) return *vrijednosti[j]; */
        //  else {
        int brojac = 0;
        int pozicija = j;
        do {
            if(kljucevi[j]!=nullptr && (*(kljucevi[j]))==kljuc) return *vrijednosti[j];
            if(kljucevi[j]==nullptr|| ((*vrijednosti[j])) == Tip2() && (*(kljucevi[j]))==Tip1()) {
                delete kljucevi[j];
                delete vrijednosti[j];
                kljucevi[j] = new Tip1(kljuc);
                vrijednosti[j] = new Tip2();
                brojelemenata++;
                return *vrijednosti[j];
            }
            if(j==kapacitet-1) j = 0;
            else j++;
            if(brojac==kapacitet) break;
            brojac++;
        } while(j!=pozicija);
        return *vrijednosti[j];
        //  }


    }

    const Tip2 operator[](const Tip1 kljuc) const
    {
        try {
            std::pair<Tip1, Tip2>* par = hash_trazi(kljuc);
            if(par) {
                delete par;
                return *vrijednosti[zabrisanje];
            }
            zabrisanje = -1;
        } catch(std::logic_error e) {
            throw;
        }
        return Tip2();
    }



};


void Test1()
{
    NizMapa<std::string, int> studenti;
    studenti["Amina"] = 18425;
    studenti["Vildana"] = 88888;
    studenti["Lejla"] = 33;
    studenti["Vildana"] = 18460;
    studenti["Lejla"] = 18433;
    if(studenti["Amina"]==18425 && studenti["Vildana"]==18460 && studenti["Lejla"]==18433) std::cout << "Test1 USPJESAN\n";
    else std::cout << "Test1 NEUSPJESAN\n";
}

void Test2()
{
    NizMapa<std::string, std::vector<int>> ocjene;
    std::vector<int> v = {10,9,10,9};
    std::vector<int> l = {7,8,9};
    ocjene["Amina"];
    ocjene["Vildana"] = v;
    ocjene["Lejla"] = l;
    if(ocjene["Amina"].size()==0 && ocjene["Vildana"].size()==4 && ocjene["Lejla"][0]==7 && ocjene["Lejla"][1]==8
            && ocjene["Lejla"][2]==9) std::cout << "Test2 USPJESAN\n";
    else std::cout << "Test2 NEUSPJESAN\n";
}

void Test3()
{
    NizMapa<int,std::string> predmeti;
    std::string predmet = "ASP";
    for(int i=0; i<22; i++)
        predmeti[i] = predmet;
    bool uspjesan = false;
    if(predmeti.brojElemenata()==22) uspjesan = true;
    predmeti.obrisi(2);
    if(uspjesan && predmeti.brojElemenata()==21) std::cout << "Test3 USPJESAN\n";
    else std::cout << "Test3 NEUSPJESAN\n";
}

void Test4()
{
    NizMapa<double, int> najbliziCijeli;
    najbliziCijeli[3.2] = std::round(3.2);
    najbliziCijeli[2.8] = std::round(2.8);
    najbliziCijeli[183.381] = std::round(183.381);
    if(najbliziCijeli.brojElemenata()==3 && najbliziCijeli[3.2]==3 && najbliziCijeli[2.8]==3
            && najbliziCijeli[183.381]==183) std::cout << "Test4 USPJESAN\n";
    else std::cout << "Test4 NEUSPJESAN\n";

}

void Test5()
{
    NizMapa<std::string,std::pair<std::string,double>> narudzba;
    narudzba["Vildana"] =std:: make_pair("mala s mlijekom",1.5);
    narudzba["Amina"] = std::make_pair("cedevita",2);
    narudzba["Lejla"] = std::make_pair("velika s mlijekom",2);
    if(narudzba["Amina"].second+narudzba["Vildana"].second+narudzba["Lejla"].second==5.5) std::cout << "Test5 USPJESAN\n";
    else std::cout << "Test5 NEUSPJESAN\n";
} 
unsigned int mojhash(int ulaz, unsigned int max) {
	unsigned int suma=23; 
	suma = suma*31 + ulaz;
	return suma % max;
}
int main()
{
   /* Test1();
    Test2();
    Test3();
    Test4();
    Test5(); */
   
    int niz[10000];
    for(int i=0; i<10000; i++)
    niz[i] = (int)(rand()%(2*10000)-10000);
    std::cout << "NizMapa: ";
    NizMapa<int, int> mapa;
    clock_t poc = clock();
    for(int i=0; i<10000; i++)
    mapa[niz[i]] = i;
    clock_t kraj = clock();
    int izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000);
    std::cout << "Pretraga se izvrsavala " << izvrsenje << " ms." << std::endl;
    BinStabloMapa<int, int> binmapa;
   
    poc = clock();
    for(int i=0; i<10000; i++)
    binmapa[niz[i]] = i;
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000);
    std::cout << "Binarno stablo: Pretraga se izvrsavala " << izvrsenje << " ms." << std::endl;
    HashMapa<int, int> hashmapa;
    hashmapa.definisiHashFunkciju(mojhash);
    poc = clock();
     for(int i=0; i<10000; i++)
    hashmapa[niz[i]] = i;
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000);
    std::cout << " HashMapa: Pretraga se izvrsavala " << izvrsenje << " ms." << std::endl;
    return 0;
}

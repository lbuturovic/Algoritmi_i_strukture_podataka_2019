#include <iostream>
#include <cmath>
#include<vector>
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
class BinStabloMapa : public Mapa<Tip1, Tip2>
{
    
    int brojelemenata;

public:
Cvor<Tip1,Tip2>* korijen;
    void brisi(Cvor<Tip1,Tip2>* k)
    {
            if(!k) return;
            brisi(k->lijevo);
            brisi(k->desno);
         //   k->roditelj = nullptr;
            delete k;
          //  k = nullptr;
        
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
        return nullptr; //zbog upozorenja
    }
    Cvor<Tip1,Tip2>* umetni2 (Tip1 &kljuc, Cvor<Tip1,Tip2>* &c, Cvor<Tip1,Tip2>* r){
        if(!c){
            c = new Cvor<Tip1,Tip2>(kljuc);
            c->roditelj = r;
            if(korijen==nullptr) korijen = c;
            brojelemenata++;
        }
        if(kljuc==c->kljuc) return c;
        if(kljuc<c->kljuc) return umetni2(kljuc,c->lijevo,c);
        return umetni2(kljuc,c->desno,c);
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
        Cvor<Tip1, Tip2>* roditelj = nullptr;
        Cvor<Tip1,Tip2>* novi = umetni2(kljuc,korijen,roditelj);
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
        if(noviC->lijevo) noviC->lijevo->roditelj = noviC;
      //  lijevi->roditelj = noviC;
       // Cvor<Tip1, Tip2>* desni = kopirajStablo(k->desno);
        noviC->desno = kopirajStablo(k->desno);
        if(noviC->desno) noviC->desno->roditelj = noviC;
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
        obrisi();
        korijen = kopirajStablo(m.korijen);
        brojelemenata = m.brojelemenata;
        return *this;
    }
    void Preorder(Cvor<Tip1,Tip2>* c){
        if(c==nullptr) return;
        std::cout << c->element << " ";
        Preorder(c->lijevo);
        Preorder(c->desno);
    }
    
    void nadjiElInorder(Cvor<Tip1,Tip2>*c,int k, Cvor<Tip1,Tip2> &cvor){
        if(c==nullptr){
            return;
        }
        nadjiElInorder(c->lijevo,k,cvor);
       std::cout << c->element << " ";
        if(c->element==k) {cvor = *c;
        return; }
        nadjiElInorder(c->desno,k,cvor);
    }
    
    void obrisi(const Tip1& kljuc)
    {
        if(!korijen) return;
        Cvor<Tip1,Tip2>* p = korijen;
        Cvor<Tip1,Tip2>* roditelj = nullptr;
        Cvor<Tip1,Tip2>* tmp = nullptr;
        Cvor<Tip1,Tip2>*m = nullptr;
        Cvor<Tip1,Tip2>*pm = nullptr;

        while(p!=nullptr && kljuc!=p->kljuc) {
            roditelj = p;
            if(kljuc<p->kljuc)  p = p->lijevo;
            else p = p->desno;
        }
        if(p==nullptr) return; //nije pronadjen
        if(p->lijevo==nullptr) {m = p->desno;
         //   m->roditelj = p->roditelj;}
        }
        else {
            if(p->desno==nullptr){
                 m = p->lijevo;
              //   m->roditelj = p->roditelj;
            }
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
                    if(m!=nullptr &&m->lijevo!=nullptr)
                    m->lijevo->roditelj = pm;
                   // pm->desno->roditelj = pm;
                     m->lijevo = p->lijevo;
                     if(p!=nullptr && p->lijevo!=nullptr)
                     p->lijevo->roditelj = m;
                }
                m->desno = p->desno;
                p->desno->roditelj = m;
                // p->desno->roditelj = m;
                //p->lijevo->roditelj= m;
            }
        }
        if(roditelj==nullptr) {

            korijen = m;
             //  m->roditelj = nullptr;
        } else {
            if(m!=nullptr)
            m->roditelj = p->roditelj;
            if(p == roditelj->lijevo) roditelj->lijevo = m;
            else roditelj->desno = m;
        }
        //if(m->desno!=nullptr) m->desno->roditelj = roditelj;
        //  if(m->lijevo!=nullptr) m->lijevo->roditelj = roditelj;
        brojelemenata--;
        delete p;
        p = nullptr;

    }
};
    
    void testiranje(){
        
        int niz[10000];
    for(int i=0; i<10000; i++)
    niz[i] = rand();
    int k = rand()%10000;
    int m;
    bool ponovo = false;
    do {                // da bi se osigurali da je u pitanju zaista dodavanje 
        ponovo = false;
        m = rand();
        for(int i=0; i<10000; i++)   
        if(niz[i]==m) {
            ponovo = true;
            break;
        }
    }while(ponovo);
    NizMapa<int, int> mapa;
    clock_t poc = clock();
    for(int i=0; i<10000; i++)
    mapa[niz[i]] = i;
    clock_t kraj = clock();
    int izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000);
   // std::cout << "NizMapa se formirala " << izvrsenje << " ms." << std::endl;
   poc = clock();
    mapa[niz[k]];
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000000);
     std::cout << "NizMapa: Pretraga se izvrsavala " << izvrsenje << " mikrosekundi." << std::endl;
     poc = clock();
    mapa[m];
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000000);
     std::cout << "NizMapa: Element se dodavao " << izvrsenje << " mikrosekundi." << std::endl;
    BinStabloMapa<int, int> binmapa;
    poc = clock();
    for(int i=0; i<10000; i++)
    binmapa[niz[i]] = i;
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000);
    //std::cout << "Binarno stablo se formiralo " << izvrsenje << " ms." << std::endl;
    poc = clock();
    binmapa[niz[k]];
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000000);
     std::cout << "Binarno stablo: Pretraga se izvrsavala " << izvrsenje << " mikrosekundi." << std::endl;
      poc = clock();
    binmapa[m];
    kraj = clock();
    izvrsenje = (kraj-poc)/(CLOCKS_PER_SEC/1000000);
     std::cout << "Binarno stablo: Element se dodavao " << izvrsenje << " mikrosekundi." << std::endl;

}
int main()
{
    //testiranje();
    //dodavanje elementa je i od NizMape i kod BinStabloMape nesto brze nego trazenje elementa,
    //kod NizMape je ta razlika osjetnija, dok kod BinStabloMape i nije toliko na ovaj broj elemenata
    //pronalazenje elementa, kao i dodavanje je osjetno brze kod BinStabla nego kod NizMape
    // za ovaj broj elemenata pretraga je 3-4 puta brza kod BinStabla nego kod NizMape, a isto vrijedi
    //i za pretragu, zakljucak BinStablo mapa je mnogo efikasnija i brza od NizMape
    
    BinStabloMapa<int,int> m;
    for(int i=1; i<50; i++)
    m.umetni(i);
    Cvor<int,int> el;
   // el.element = 9;
   // m.nadjiElInorder(m.korijen,8,el);
   // std::cout << el.element;
   m.Preorder(m.korijen);
    return 0;
}

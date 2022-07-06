#include <iostream>
template<typename Tip>
class Iterator;
template <typename T>
class Lista
{
public:
    Lista<T>() {};
    virtual~ Lista() {};
    virtual int brojElemenata()const = 0;
    virtual T& trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const T& el) = 0;
    virtual void dodajIza(const T& el) = 0;
    virtual T& operator [](int broj) = 0;
    virtual const T operator [] (int broj) const = 0;
    friend class Iterator<T>;

};
template <typename T>
struct Cvor {
    T el;
    Cvor* pret;
    Cvor* sljed;
};
template <typename T>
class DvostrukaLista : public Lista<T>
{
    Cvor<T>* trenutnic;
    Cvor<T>* pocetni;
    Cvor<T>* krajnji;
    int brojelemenata;
public:
//konstruktor
    DvostrukaLista<T>()
    {
        trenutnic = nullptr;
        pocetni = nullptr;
        krajnji = nullptr;
        brojelemenata = 0;
    }
    DvostrukaLista<T>(const DvostrukaLista<T>& l)
    {
        pocetni = nullptr;
        trenutnic = nullptr;
        krajnji = nullptr;
        brojelemenata = 0;
        for(auto i=l.pocetni; i!=nullptr; i=i->sljed) {
            dodajIza(i->el);
            if(brojelemenata==1) pocetni = trenutnic;
            sljedeci();
        }
        krajnji = trenutnic;
        trenutnic = pocetni;
        brojelemenata = l.brojelemenata;
    }
    DvostrukaLista<T>& operator =(const DvostrukaLista<T>& l)
    {
        if(&l==this) return *this;
        for(auto i=l.pocetni; i!=nullptr; i=i->sljed) {
            dodajIza(i->el);
            if(brojelemenata==1) pocetni = trenutnic;
            sljedeci();
        }
        krajnji = trenutnic;
        trenutnic = pocetni;
        brojelemenata = l.brojelemenata;
        return *this;
    }
    ~DvostrukaLista<T>()
    {
        obrisiListu();
    }
    void pocetak() override
    {
        if(brojelemenata==0) throw std::logic_error("Lista je prazna");
        trenutnic = pocetni;
    }
    void kraj() override
    {
        if(brojelemenata==0) throw std::logic_error("Lista je prazna");
        trenutnic = krajnji;
    }
    void obrisiListu()
    {
        auto pom = pocetni;
        for(auto i=pocetni; i!=nullptr; i=pom) {
            pom = i->sljed;
            delete i;
        }
        brojelemenata = 0;
        pocetni = nullptr;
        trenutnic = nullptr;
        krajnji = nullptr;
    }

//dodajispred
    void dodajIspred(const T& el) override
    {
        Cvor<T>* dodani = new Cvor<T> {el,nullptr,nullptr};
        if(!pocetni) {
            trenutnic = dodani;
            pocetni = dodani;
            krajnji = dodani; //pocetni i krajnji su isti!
        } else {
            dodani->sljed = trenutnic;
            dodani->pret = trenutnic->pret;
            if(trenutnic!=pocetni) dodani->pret->sljed = dodani;
            trenutnic->pret = dodani;
            if(trenutnic==pocetni) pocetni = dodani;
        }

        brojelemenata++;
    }
    void dodajIza(const T& el) override
    {
        Cvor<T>* dodani = new Cvor<T> {el,nullptr,nullptr};
        if(!pocetni) {
            trenutnic = dodani;
            pocetni = dodani;
            krajnji = dodani; //pocetni i krajnji su isti!
        } else {
            dodani->sljed = trenutnic->sljed;
            dodani->pret = trenutnic;
            if(trenutnic!=krajnji) dodani->sljed->pret = dodani;
            trenutnic->sljed = dodani;
            if(trenutnic==krajnji) krajnji = dodani;
        }
        brojelemenata++;
    }
    void obrisi() override
    {
        if(brojelemenata==0) throw std::logic_error("Lista je prazna");
        if(pocetni==krajnji && pocetni==trenutnic) {
            krajnji=nullptr;
            pocetni = nullptr;
            delete trenutnic;
            trenutnic = nullptr;
        } else if(trenutnic==krajnji) {
            trenutnic->pret->sljed = nullptr;
            krajnji = trenutnic->pret;
            delete trenutnic;
            trenutnic = krajnji;

        } else if(pocetni==trenutnic) {
            trenutnic->sljed->pret = nullptr;
            pocetni = trenutnic->sljed;
            delete trenutnic;
            trenutnic = pocetni;
        } else {
            trenutnic->pret->sljed = trenutnic->sljed;
            trenutnic->sljed->pret = trenutnic->pret;
            auto p = trenutnic->sljed;
            delete trenutnic;
            trenutnic = p;
        }
        brojelemenata--;
    }
    bool prethodni() override
    {
        if(!pocetni) throw std::logic_error("Lista je prazna!");
        if(trenutnic==pocetni) return false;
        trenutnic=trenutnic->pret;
        return true;
    }
    bool sljedeci() override
    {
        if(!pocetni) throw std::logic_error("Lista je prazna!");
        if(trenutnic==krajnji) return false;
        trenutnic = trenutnic->sljed;
        return true;
    }
    int brojElemenata() const override
    {
        return brojelemenata;
    }
    T& trenutni()const override
    {
        if(!pocetni) throw std::logic_error("Lista je prazna!");
        return trenutnic->el;
    }
    T& operator[](int broj) override
    {
        if(broj<0 || broj>=brojElemenata()) throw std::range_error("Indeks nije odgovaajuci");
        int brojac = 0;
        // if(broj>brojelemenata/2) kon
        Cvor<T>* j = krajnji;
      //  Cvor<T>* t = trenutnic;
        for(Cvor<T>* i = pocetni; i!=nullptr; i = i->sljed) {

            if (broj==brojac) return i->el;
            if(broj==brojelemenata-brojac-1) return j->el;
            j=j->pret;
            brojac++;
        }
        return trenutnic->el; //formalno
    }
    const T operator[](int broj) const override
    {
        if(broj<0 || broj>=brojElemenata()) throw std::range_error("Indeks nije odgovaajuci");
        int brojac = 0;
        Cvor<T>* j = krajnji;
        for(Cvor<T>* i = pocetni; i!=nullptr; i = i->sljed) {

            if (broj==brojac) return i->el;
            if(broj==brojelemenata-brojac-1) return j->el;
            j=j->pret;
            brojac++;
        }
        return trenutnic->el; //formalno
        /* for(Cvor<T>* i = pocetni; i!=nullptr; i = i->sljed){
             if (broj==brojac) return i->el;
             brojac++;*/
    }
    DvostrukaLista<T> presloziElemente(int n, int k, int t){
         for(auto i= pocetni; i!=nullptr; i = i->sljed)
        std::cout << i->el << " ";
        std::cout << std::endl;
        if(n>brojelemenata || n<0 || k<0 || k>brojelemenata || t<0 || n+k>brojelemenata || n+k+t>brojelemenata)
        throw std::range_error("Van ranga!\n");
        if(k==0) return *this;
        Cvor<T>* c = krajnji;
        Cvor<T>* cn;
        Cvor<T>* ck;
        Cvor<T>* ct;
        int brojac = 0;
        for(c=krajnji; c!=nullptr; c = c->pret){
            
            if(brojac==n) cn = c;
            if(brojac==n+k) ck = c;
            if(brojac==n+k+t) ct = c;
            
            
            brojac++;
        }
        
        Cvor<T>* cnp = cn->pret;
        Cvor<T>* cks = ck->sljed;
        Cvor<T>* ctp = ct->pret;
        
        ck->sljed = cn;
        cn->pret = ck;
        cnp->sljed = ct;
        ct->pret = cnp;
        cks->pret = ctp;
        if(ctp==nullptr){
            
            pocetni = cks;
            
        }
        
        else{
            
            ctp->sljed = cks;
            
        }
        
        for(auto i= pocetni; i!=nullptr; i = i->sljed)
        std::cout << i->el << " ";
        return *this;
        
        
    }
    
    
    void polovineListi(DvostrukaLista<T> &drugaLista){
        
        auto c1 = pocetni;
        auto c2 = drugaLista.pocetni;
        int brel1 = 0;
        int brel2 = 0;
        for(c1 = pocetni; c1!=nullptr; c1 = c1->sljed){
            brel1++;
            if(c2!=nullptr) brel2++;
            c2 = c2->sljed;
        }
        
        if(c2!=nullptr){
            
            for(auto c = c2; c!=nullptr; c = c->sljed)
            brel2++;
        }
        
        int brojac = 1;
        for(c1 = pocetni; c1!=nullptr; c1 = c1->sljed){
            if(brojac == brel1/2) break;
            brojac++;
        }
        brojac = 1;
        for(c2 = drugaLista.pocetni;c2!=nullptr; c2=c2->sljed){
            if(brojac == brel2/2) break;
            brojac++;
        }
        
        auto c = c2->sljed;
        c1->sljed = drugaLista.pocetni;
        c1->sljed->pret = c1;
        c2->sljed = pocetni;
        c2->sljed->pret = c2;
        krajnji->sljed = c;
        krajnji->sljed->pret = krajnji;
        krajnji = drugaLista.krajnji;
        drugaLista.krajnji = nullptr;
        drugaLista.pocetni = nullptr;
        
        brojelemenata = brojelemenata + brel2;
        
        for(auto i= pocetni; i!=nullptr; i = i->sljed)
        std::cout << i->el << " ";
        std::cout << std::endl;
    }  
    friend class Iterator<T>;
};
template <typename T>
class Iterator
{
    const DvostrukaLista<T>* dlista;
    Cvor<T>* trenutnic;
public:
    Iterator(const DvostrukaLista<T>& lista)
    {
        if(lista.brojelemenata==0) throw std::logic_error("Lista je prazna\n");
        dlista = &lista;
        trenutnic =lista.pocetni;
    }
    const T& trenutni() const
    {
        if(dlista->brojelemenata==0) throw std::logic_error("Lista je prazna\n");
        return trenutnic->el;
    }
    Cvor<T>* begin()
    {
        if(dlista->brojelemenata==0) throw std::logic_error("Lista je prazna\n");
        return dlista->pocetni;
    }
    Cvor<T>* end()
    {
        if(dlista->brojelemenata==0) throw std::logic_error("Lista je prazna\n");
        return nullptr;  //iza kraja
    }
    Cvor<T>* next()
    {
        if(dlista->brojelemenata==0) throw std::logic_error("Lista je prazna\n");
        trenutnic = trenutnic->sljed;
        return trenutnic;
    }
    Cvor<T>* previous()
    {
        if(dlista->brojelemenata==0) throw std::logic_error("Lista je prazna\n");
        trenutnic = trenutnic->pret;
        return trenutnic;
    }


};
template <typename Tip>
Tip dajMaksimum (const Lista<Tip>& l)
{
    const DvostrukaLista<Tip>* dl = (const DvostrukaLista<Tip>*) &l;
    Iterator<Tip> it(*dl);
    Tip max = it.trenutni();
    for(auto i = it.begin(); i!=it.end(); i=it.next())
        if(max<it.trenutni()) max = it.trenutni();
    return max;

}
void TestDajMaksimum()
{
    DvostrukaLista<int> l;
    for(int i=2; i<=40; i=i+2) {
        l.dodajIspred(i);
        l.dodajIza(i-2);
    }
    std::cout << "dajMaksimum: ";
    if(dajMaksimum(l)!=40) std::cout << "TEST NEUSPJESAN\n";
    else std::cout << "TEST USPJESAN\n";

}
void TestBrojElemenata()
{
    DvostrukaLista<int> l;
    for(int i=0; i<15; i++)
        l.dodajIza(i);
    std::cout << "brojElemenata: ";
    if(l.brojElemenata()==15) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
void TestDodajIza()
{
    DvostrukaLista<int> l;
    int niz[10];
    niz[0] = 0;
    for(int i=0; i<10; i++) {
        l.dodajIza(i); //0987654321
        if(i>0) niz[i] = 10-i;
    }
    Iterator<int> it(l);
    bool uspjesan = true;
    int m = 0;
    for(auto i=it.begin(); i!=it.end(); i=it.next()) {
        if(it.trenutni()!=niz[m]) {
            uspjesan = false;
        }
        m++;
    }
    std::cout << "dodajIza: ";
    if(uspjesan) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";

}
void TestDodajIspred()
{
    DvostrukaLista<int> l;
    int niz[10];
    for(int i=0; i<10; i++) {
        l.dodajIspred(i); //1234567890
        niz[i] = i+1;
    }
    niz[9] = 0;
    Iterator<int> it(l);
    bool uspjesan = true;
    int m = 0;
    for(auto i=it.begin(); i!=it.end(); i=it.next()) {
        if(it.trenutni()!=niz[m]) {
            uspjesan = false;
        }
        m++;
    }
    std::cout << "dodajIspred: ";
    if(uspjesan) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";

}
void TestUglaste()
{
    DvostrukaLista<int> l;
    l.dodajIza(1);  //1 15 962
    l.dodajIza(2);
    l.dodajIza(6);
    l.dodajIza(9);
    l.dodajIza(15);
    std::cout <<"Operator uglastih zagrada: ";
    l[1] = 80;
    l [3] = 90;
    if(l[0]==1 && l[1]==80 && l[2]==9 && l[3]==90 && l[4]==2)
        std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
void TestObrisi()
{
    DvostrukaLista<int> l;
    for(int i=0; i<5; i++)  //04321
        l.dodajIza(i);
    l.obrisi();
    l.obrisi();
    std::cout << "obrisi: ";
    if(l.brojElemenata()==3 && l[0]==3 && l[1]==2 && l[2]==1) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
void TestTrenutni()
{
    DvostrukaLista<int> l;
    l.dodajIspred(5);
    l.dodajIspred(9);
    l.dodajIza(6);
    l.dodajIza(3);
    std::cout << "trenutni: ";
    if(l.trenutni()==5) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
void TestPrethodni()
{
    DvostrukaLista<int> l;
    l.dodajIspred(5);
    l.dodajIspred(4);
    l.dodajIspred(8);  //   4 8 5
    l.prethodni();
    std::cout<< "prethodni: ";
    if(l.trenutni()!=8) {
        std::cout << "TEST NEUSPJESAN\n";
        return;

    }
    l.prethodni();
    l.prethodni();
    if(l.trenutni()!=4) {
        std::cout << "TEST NEUSPJESAN\n";
        return;
    }
    std::cout<< "TEST USPJESAN\n";
}
void TestSljedeci(){
    DvostrukaLista<int> l;
    for(int i=1; i<=5; i++) //15432
    l.dodajIza(i);
    l.sljedeci();
    l.sljedeci();
    l.sljedeci();
    std::cout << "sljedeci: ";
    if(l.trenutni()!=3) {
        std::cout << "TEST NEUSPJESAN\n";
        return;
    }
    l.sljedeci();
    l.sljedeci();
    if(l.trenutni()!=2){
        std::cout<< "TEST NEUSPJESAN\n";
        return;
    }
    std::cout << "TEST USPJESAN\n";
}
int main()
{
    std::cout << "Testovi za dvostruku listu:\n";
  /*  TestBrojElemenata();
    TestDodajIspred();
    TestDodajIza();
    TestUglaste();
    TestObrisi();
    TestTrenutni();
    TestPrethodni();
    TestSljedeci();
    TestDajMaksimum(); */
    
    DvostrukaLista<int> l;
    for(int i = 7; i>=1; i--){
    l.dodajIza(i);
    }
    
    DvostrukaLista<int> l2;
    for(int i = 15; i>=2; i--){
    l2.dodajIza(i);
    }
 //   for(int i=0; i<8; i++)
    
 //   l.presloziElemente(0,4,2);
    l.polovineListi(l2);
    return 0;
}

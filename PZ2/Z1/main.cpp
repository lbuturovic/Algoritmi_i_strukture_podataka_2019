#include <iostream>

template <typename Tip>
class Lista
{
public:
    Lista<Tip>() {};
    virtual~ Lista() {};
    virtual int brojElemenata()const = 0;
    virtual Tip& trenutni() const = 0;
    virtual bool prethodni() = 0;
    virtual bool sljedeci() = 0;
    virtual void pocetak() = 0;
    virtual void kraj() = 0;
    virtual void obrisi() = 0;
    virtual void dodajIspred(const Tip& el) = 0;
    virtual void dodajIza(const Tip& el) = 0;
    virtual Tip& operator [](int broj) = 0;
    virtual const Tip operator [] (int broj) const = 0;

};
template <typename Tip>
struct Cvor {
    Tip el;
    Cvor* veza;
};
template <typename Tip>
class JednostrukaLista : public Lista<Tip>
{
   Cvor<Tip>* pocetni;
    Cvor<Tip>* prethodnik;
     Cvor<Tip>* trenutnic;
    int brojelemenata;
    void izuzetak()
    {
        if(!pocetni) throw std::logic_error("Lista je prazna!");
    }
public:
    void obr(){
        auto p = pocetni;
        Cvor<Tip>* pret = nullptr;
        Cvor<Tip>* pom = nullptr;
        while(p!=nullptr){
            pom = p->veza;
            p->veza = pret;
            pret = p;
            p = pom;
        }
        pocetni = pret;
        p = pocetni;
        while(p!=nullptr){
        std::cout << p->el << " ";
        p = p->veza;
        }
    }
    template< typename L>
    friend void TestBrojElemenata(const L& lista);
    JednostrukaLista<Tip>(const JednostrukaLista<Tip>& lista);
    JednostrukaLista<Tip>& operator =(const JednostrukaLista<Tip>& lista);
    Tip& operator [](int broj){
        if(broj<0 || broj>=brojElemenata()) throw std::range_error("Indeks nije odgovarajuci");
        int brojac = 0;
        for(Cvor<Tip>* i = pocetni; i!=nullptr; i = i->veza){
            if(broj==brojac) return i->el;
            brojac++;
        }
    } 
    const Tip operator[](int broj) const{
        if(broj<0 || broj>=brojElemenata()) throw std::range_error("Indeks nije odgovaajuci");
        int brojac = 0;
        for(Cvor<Tip>* i = pocetni; i!=nullptr; i = i->veza){
            if (broj==brojac) return i->el;
            brojac++;
        }
    }
  /*  Tip& operator [](int broj) {
        int poz = 0;
        for(Cvor<Tip>* i = pocetni; i!=nullptr; i = i->veza){
            
            poz++;
        }*/
        
    
    
    ~JednostrukaLista()
    {
        obrisiListu();
    }
    JednostrukaLista<Tip>()
    {
        pocetni = nullptr;
        prethodnik = nullptr;
        trenutnic = nullptr;
        brojelemenata = 0;

    }
    Cvor<Tip>* dajPocetni() const
    {
        return pocetni;
    }
    void dodajIspred(const Tip& el) override;
    void dodajIza(const Tip& el) override;
    int brojElemenata() const override;
    void obrisiListu()
    {
           // pocetak();
            if(pocetni!=nullptr){
            Cvor<Tip>* pom;
            for(Cvor<Tip>* i=pocetni; i!=nullptr; i=pom) {
                pom=i->veza;
                delete i;
                i=pom;
            }
            pocetni = nullptr;
            prethodnik = nullptr;
            trenutnic = nullptr;
            }
    }
    Tip& trenutni() const override
    {
        if(!pocetni) throw std::logic_error("Lista je prazna!");
       // izuzetak();
        if(!pocetni) throw std::logic_error("greska");
        return trenutnic->el;
    }
    bool sljedeci() override
    {
         izuzetak();
        if(!pocetni) throw std::logic_error("greska");
        if(trenutnic->veza == nullptr) return false;
        prethodnik = trenutnic;
        trenutnic = trenutnic->veza;
        return true;
    }
    bool prethodni() override
    {
        izuzetak();
        if(trenutnic==pocetni) return false;
        // dodaj ovdje jedan if problem je kod prethodnika!!!
        trenutnic = prethodnik;
        for(Cvor<Tip>* i=pocetni; i!=nullptr; i=i->veza) {
            if(i->veza==prethodnik) {
                prethodnik=i;
                break;

            }
            
        }
        if (prethodnik==trenutnic) prethodnik=nullptr;  //obrisi

        return true;
    }
    void pocetak() override
    {
        izuzetak();
        trenutnic=pocetni;
    }
    void kraj() override
    {
        izuzetak();
        Cvor<Tip>* it = pocetni;
        for(int i=0; i!=brojElemenata()-1; i++)
            it = it->veza;
        trenutnic = it;
    }
    virtual void obrisi() override
    {
        izuzetak();
        Cvor<Tip>* pok = trenutnic;
       // if(prethodnik==nullptr){
        if(pocetni==trenutnic && trenutnic->veza==nullptr){ // moze i ovo, ali onda ono gore brisem
           // prethodnik==nullptr;
            trenutnic = nullptr;
            pocetni = nullptr;
        }
       else if(trenutnic->veza==nullptr)  {
           prethodni();
           // std::cout << trenutni() << std::endl;
            trenutnic->veza = nullptr;
        } else if(trenutnic==pocetni) {
            sljedeci();
            pocetni = trenutnic;
        } else {
            prethodnik->veza = trenutnic -> veza;
            trenutnic = trenutnic -> veza;
            //sljedeci();
            }
       // pok = nullptr;
        delete pok;
        
    }
    
  void izvrni(Cvor<Tip>* poc){
      if(poc->veza==nullptr){
   //       std::cout << poc->el << " ";
      pocetni = poc;
      return;}
      izvrni(poc->veza);
      poc->veza->veza = poc;
      poc->veza = nullptr;
    //  std::cout << poc->el << " ";
      return;
  } 
  
  void funkcija(){
      
      izvrni(pocetni);
      auto p = pocetni;
      int suma = pocetni->el;
      auto zapamti = pocetni;
      while(p->veza!=nullptr){
          if(p->veza->el < suma){
              zapamti = p->veza;
              p->veza = p->veza->veza;
              delete zapamti;
              
          }
          else {
              suma+=p->veza->el;
              p = p->veza;
          }
      }
      izvrni(pocetni);
      for(auto p=pocetni; p!=nullptr; p=p->veza)
      std::cout << p->el << " ";
      
  }
};
 /*template <typename Tip>
 void izvrni(JednostrukaLista<Tip> l, Cvor<Tip>* poc = l.pocetni){
      if(poc->veza==nullptr){
          std::cout << poc->el << " ";
      l.pocetni = poc;
      return;}
      Cvor<Tip>* p = izvrni(l,poc->veza);
      poc->veza->veza = poc;
      poc->veza = nullptr;
      std::cout << poc->el << " ";
      return;
  } */
template<typename Tip>
class NizLista : public Lista<Tip>{
    int kapacitet;
    int brojelemenata;
    int indeks;
    Tip** lista;
    public:
    template<typename L>
    friend void TestBrojElemenata(const L& lista);
    NizLista<Tip>(){
        kapacitet = 10;
        brojelemenata = 0;
        indeks = 0;
        lista = new Tip*[10]{};
        }
    ~NizLista<Tip>(){
        for(int i=0; i<kapacitet; i++)
        delete lista[i];
        delete [] lista;
        
    }
    int brojElemenata() const override { return brojelemenata; }
    Tip& trenutni() const override { 
        if(brojelemenata==0) throw std::logic_error("greska");
        return *lista[indeks]; }
    bool sljedeci() override {
        if(brojelemenata==0) throw std::logic_error("greska");
        if(indeks==brojelemenata-1)  return false;
        indeks++;
        return true;
    }
    bool prethodni() override {
        if(brojelemenata==0) throw std::logic_error("greska");
        if(indeks==0) return false;
        indeks--;
        return true;
        
    }
    void pocetak() override { 
        if(brojelemenata==0) throw std::logic_error("greska");
        indeks = 0;}
    void kraj() override { 
        if(brojelemenata==0) throw std::logic_error("greska");
        indeks = brojelemenata - 1;}
    void prosiri(){
            Tip** novi = new Tip*[kapacitet+10]{};
            kapacitet+=10;
            for(int i=0; i<brojelemenata;i++){
                novi[i] = lista[i];
            }
          //  for(int i=0; i<brojelemenata; i++)
          //   delete lista[i];
            delete[] lista;
            lista = nullptr;
            lista = novi;
        }
        void dodajIspred(const Tip& el) override {
            if(brojelemenata+1>kapacitet) prosiri();
        
        if(brojelemenata==0) {
            if(lista==nullptr) {
                lista = new Tip*[10]{};
                kapacitet = 10;
                indeks = 0;
            }
            lista[0] = new Tip(el);
            
        }
        else {
            for(int i=brojelemenata-1; i>=indeks; i--){
                lista[i+1] = lista[i];
            }
           // delete lista[indeks];   //provjeri
            lista[indeks] = new Tip(el); 
            indeks ++;
        }
            brojelemenata ++;
            
        }
        void dodajIza(const Tip &el) override {
            if(brojelemenata+1>kapacitet) prosiri();
            if(brojelemenata==0) {
                if(lista==nullptr) {
                lista = new Tip*[10]{};
                kapacitet = 10;
                indeks = 0;
            }
                lista[0] = new Tip(el);
            }
            else{
                for(int i = brojelemenata-1; i>indeks;i--){
                    lista[i+1] = lista[i];
                }
              //  delete lista[indeks+1];   //provjeri
              Tip* pok = new Tip(el);
                lista[indeks+1] = pok;
              
            }
            brojelemenata++;
        }
        void obrisi() override {
            if(brojelemenata==0) throw std::logic_error("greska");
            if(brojelemenata==1) {
                brojelemenata = 0;
                delete lista[0];
                lista[0] = nullptr;
             //   delete [] lista;
             //   lista = nullptr;
            }
            else if(indeks ==brojelemenata - 1) {
                delete lista[indeks]; //
                lista[indeks] = nullptr; //
                indeks = brojelemenata - 2;
                brojelemenata--;}
            else {
                delete lista[indeks]; //
                lista [indeks] = nullptr; //
                for(int i=indeks+1; i<brojelemenata;i++){
                lista[i-1] = lista[i];
                lista[i] = nullptr;
                }
                brojelemenata--;
            }
        
        }
    NizLista(const NizLista& l){
        if(l.lista==nullptr) {
            brojelemenata = 0;
            lista = nullptr;
            indeks = 0;
            kapacitet = 10;
        }
        else {
            lista = new Tip*[l.kapacitet]{};
            for(int i = 0; i < l.brojelemenata; i++){
                lista[i] = new Tip(*l.lista[i]);
            }
            indeks = 0;
            kapacitet = l.kapacitet;
            brojelemenata = l.brojelemenata;
        }
    }
    NizLista<Tip>& operator =(const NizLista& l){
        if(&l==this) return *this;
        if(kapacitet>=l.kapacitet){
            for(int i=0; i<kapacitet; i++){
                delete lista[i];
                lista[i]== nullptr;
            }
            for(int i=0; i<l.brojelemenata; i++)
            lista[i] = new Tip (*l.lista[i]);
            brojelemenata = l.brojelemenata;
            indeks = 0;
        }
        else {
            for(int i=0; i<kapacitet; i++){
                delete lista[i];
                lista[i] = nullptr;
            }
                delete [] lista;
            
            Tip** nova = new Tip*[l.kapacitet]{};
            for(int i = 0; i<l.brojelemenata; i++)
            nova[i] = new Tip(*l.lista[i]);
            lista = nova;
            brojelemenata = l.brojelemenata;
            kapacitet = l.kapacitet;
        }
        return *this;
        
    }
    Tip& operator [](int broj) {
        if(broj<0 || broj>=brojelemenata) throw std::range_error("Indeks nije odgovarajuci.");
        return *lista[broj];
    }
    const Tip operator[](int broj) const {
        if(broj<0 || broj>=brojelemenata) throw std::range_error("Indeks nije odgovarajuci");
        return *lista[broj];
    }
    
  
    
};
template<typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista<Tip>& lista)
{
    if(lista.dajPocetni()==nullptr) {
        pocetni = nullptr;
        prethodnik = nullptr;
        trenutnic = nullptr;
    } else {
        int m=0;
        trenutnic = nullptr;
        Cvor<Tip>* i = lista.dajPocetni();
        for(Cvor<Tip>* i=lista.dajPocetni(); i!=nullptr; i=i->veza) {
            Cvor<Tip>* dodani = new Cvor<Tip>{i->el,nullptr};
            if(m==0) pocetni = dodani;
            else prethodnik->veza = dodani;
            prethodnik = dodani;
            m++;
            //dodajIza(i->el);
            
            //sljedeci();
        }
        pocetak();

    }
}
template <typename Tip>
JednostrukaLista<Tip>& JednostrukaLista<Tip>::operator = (const JednostrukaLista<Tip>& lista)
{
    if(&lista == this) return *this;
    obrisiListu();
    if(!lista.dajPocetni()) {
        pocetni = nullptr;
        prethodnik = nullptr;
        trenutnic = nullptr;
    } else {
        pocetni = nullptr;
        for(Cvor<Tip>* i = lista.dajPocetni(); i!=nullptr; i=i->veza) {
            Cvor<Tip>* dodani = new Cvor<Tip>{i->el,nullptr};
            if(!pocetni) pocetni = dodani;
            else prethodnik->veza = dodani;
            prethodnik = dodani;
        }
        pocetak();
    }
    return *this;

}
template<typename Tip>
int JednostrukaLista<Tip>::brojElemenata() const
{
    if(!pocetni) return 0;
    int broj = 0;
    for(Cvor<Tip>* i=pocetni; i!=nullptr; i=i->veza)
        broj++;
    return broj;
}
template<typename Tip>
void JednostrukaLista<Tip>::dodajIspred(const Tip& el)
{
    Cvor<Tip>* dodani = new Cvor<Tip> {el,nullptr};
    //brojelemenata++;
    if(!pocetni) {
        pocetni = dodani;
        trenutnic = pocetni;
    } else if(trenutnic == pocetni) {
        dodani->veza = trenutnic;
        pocetni = dodani;
        prethodnik = dodani;
    } else {
        dodani->veza = trenutnic;
        prethodnik->veza = dodani;
        prethodnik = dodani;
    }
  //  prethodnik = dodani;
}
template <typename Tip>
void JednostrukaLista<Tip>::dodajIza(const Tip& el)
{
    Cvor<Tip>* dodani = new Cvor<Tip> {el, nullptr};
    // brojelemenata++;
    if(!pocetni) {
        pocetni = dodani;
        trenutnic = pocetni;
    } else {
        dodani->veza = trenutnic->veza;
        trenutnic->veza = dodani;
    }
}

template <typename L>
void TestBrojElemenata (const L& l){
    L lista;
    lista.dodajIza(1);
    lista.dodajIza(7);
    lista.dodajIza(19);
    lista.dodajIza(77);
    for(int i=0; i<5000;i++)
    lista.dodajIspred(i);
    std::cout << "brojElemenata: ";
    if(lista.brojElemenata()==5004) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
    
}
template <typename L>
void TestObrisi(const L& l){
    L lista;
    lista.dodajIza(4);
    lista.dodajIza(333);
    lista.dodajIza(923);
    lista.dodajIza(21);
    lista.dodajIza(8);
    lista.obrisi();
    lista.sljedeci();
    lista.obrisi();
    bool uspjesan = true;
    std::cout << "Obrisi: ";
    if(lista.brojElemenata()!=3 || lista[0]!=8 || lista[1]!=923 || lista[2]!=333)
    std::cout << "TEST NEUSPJESAN\n";
    else std::cout << "TEST USPJESAN\n";
    
    
    
}
template<typename L>
void TestDodajIspred(const L& l){
    L lista;
    lista.dodajIspred(2);
    lista.dodajIspred(3);
    lista.dodajIspred(4);
    lista.dodajIspred(5);
    bool uspjesan = true;
    int niz[4] = {3,4,5,2};
    for(int i=3; i>=0; i--){
        if(niz[i]!=lista.trenutni()){ uspjesan = false; break; }
        lista.prethodni();
    }
    std::cout << "dodajIspred: ";
    if(uspjesan) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
    
}
template <typename L>
void TestUglaste (const L& l){
    L lista;
    lista.dodajIza(2);
    lista.dodajIza(3);
    lista.dodajIza(4);
    lista.dodajIza(5);
    std::cout << "Operator uglasih zagrada: ";
    const L lista2 = lista;
    lista[2] = 1844;
    lista[0] = 12;
    if(lista2[0]!=2 || lista[0]!=12 || lista[2]!=1844 || lista2[1]!=5 || lista2[2]!=4 || lista2[3]!=3) std::cout << "TEST NEUSPJESAN\n";
    else std::cout << "TEST USPJESAN\n";
}
template <typename L>
void TestDodajIza(const L& l){
    L lista;
    lista.dodajIza(2);
    lista.dodajIza(3);
    lista.dodajIza(4);
    lista.dodajIza(5);
    bool uspjesan = true;
    int niz[4] = {2,5,4,3};
    for(int i=0; i<4; i++){
        if(lista.trenutni()!=niz[i]) {
            uspjesan = false;
            break;
        }
        lista.sljedeci();
    }
        std::cout << "dodajIza: ";
        if(uspjesan) std::cout << "TEST USPJESAN\n";
        else std::cout << "TEST NEUSPJESAN\n";
    
    
}
template <typename L>
void TestSljedeci(const L& lista){
    L l;
    l.dodajIza(1);
    l.dodajIza(2);
    l.dodajIza(8);
    l.dodajIza(9);
    
    l.sljedeci();
    l.sljedeci();
    bool uspjesan = true;
    if(l.trenutni()!=8) uspjesan = false;
    l.sljedeci();
    l.sljedeci();
    l.sljedeci();
    if(l.trenutni()!=2) uspjesan = false;
    std::cout << "sljedeci: ";
    if(uspjesan) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
template <typename L>
void TestTrenutni(const L& lista){
    L l;
    l.dodajIspred(7);
    l.dodajIza(15);
    l.dodajIza(19);
    l.dodajIspred(77);
    std::cout << "trenutni: ";
    if(l.trenutni()==7) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
template <typename L>
void TestPrethodni(const L& lista){
    L l;
    l.dodajIspred(9);
    l.dodajIspred(4);
    l.dodajIspred(3);
    bool uspjesan = true;
    l.prethodni();
    if(l.trenutni()!=3) uspjesan = false;
    l.prethodni();
    l.prethodni();
    l.prethodni();
    if(l.trenutni()!=4) uspjesan = false;
    std::cout << "prethodni: ";
    if(uspjesan) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
int main()
{
    JednostrukaLista<int> l;
    NizLista<int> l2;
    std::cout << "Testovi za klasu JednostrukaLista:\n";
    TestBrojElemenata(l);
    TestDodajIza(l);
    TestDodajIspred(l);
    TestUglaste(l);
    TestObrisi(l);
    TestTrenutni(l);
    TestPrethodni(l);
    TestSljedeci(l);
    std::cout <<"\nTestovi za klasu NizLista:\n";
    TestBrojElemenata(l2);
    TestDodajIza(l2);
    TestDodajIspred(l2);
    TestUglaste(l2);
    TestObrisi(l2);
    TestTrenutni(l2);
    TestPrethodni(l2);
   TestSljedeci(l2);
    JednostrukaLista<int> l22;
    l22.dodajIza(450);  //1982
    l22.dodajIza(1);
    l22.dodajIza(2);
    l22.dodajIza(5);
    l22.dodajIza(15);
    l22.dodajIza(20);
    l22.dodajIza(466);
    l22.dodajIza(500);
    l22.funkcija();
    return 0;
}

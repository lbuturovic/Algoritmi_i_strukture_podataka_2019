#include <iostream>
template <typename Tip>
class Stek
{
    int kapacitet;
    int brojelemenata;
    Tip* stek;
public:
    Stek<Tip>()
    {
        kapacitet = 10;
        brojelemenata = 0;
        stek = new Tip[10] {};
    }
    Stek<Tip>(const Stek<Tip>& s)
    {
        stek = new Tip[s.kapacitet] {};
        for(int i=0; i<s.brojelemenata; i++) {
            stek[i] = s.stek[i];
        }
        brojelemenata = s.brojelemenata;
        kapacitet = s.kapacitet;
    }
    Stek<Tip>& operator = (const Stek<Tip>& s)
    {
        if(&s==this) return *this;
        if(kapacitet<s.kapacitet) {
           delete [] stek;
           Tip* novi = new Tip[s.kapacitet] {};
            for(int i=0; i<s.brojelemenata; i++) {
                novi[i] = s.stek[i];
            }
            stek = novi;
    
        } else {
            for(int i=0; i<s.brojelemenata; i++) 
                stek[i] = s.stek[i];
        }
        brojelemenata = s.brojelemenata;
        return *this;
    }
    ~Stek<Tip>()
    {
        delete [] stek;
        stek = nullptr;
    }
    void brisi()
    {
       /* for(int i=0; i<kapacitet; i++) {
            delete stek[i];
            stek[i] = nullptr;
        } */
        brojelemenata = 0;

    }
    void stavi(const Tip& el)
    {
        if(brojelemenata+1>kapacitet) {

            Tip* novi = new Tip[kapacitet+10] {};
            //kapacitet+=10;
            for(int i=0; i<kapacitet; i++) {
                novi[i] = stek[i];
            }
            delete [] stek;
            stek = nullptr;
            stek = novi;
            kapacitet+=10;
        }
        stek[brojelemenata] = el;
        brojelemenata++;
    }
    Tip skini()
    {
        if(brojelemenata==0) throw std::logic_error ("Stek je prazan!\n");
      /*  Tip element = *stek[brojelemenata-1];
        delete stek[brojelemenata-1];
        stek[brojelemenata-1] = nullptr; 
        brojelemenata--;
        return element; */
       // Tip el = stek[brojelemenata-1];
        brojelemenata--;
        return stek[brojelemenata];
    }
    Tip& vrh()
    {
        if(brojelemenata==0) throw std::logic_error("Stek je prazan!\n");
        return stek[brojelemenata-1];
    }
    int brojElemenata()
    {
        return brojelemenata;
    }
    friend void TestBrisi();
    friend void TestStavi();
    friend void TestSkini();
};
template<typename Tip>
struct Cvor {
    Tip el;
    Cvor* veza;
};
template<typename Tip>
class Red {
 Cvor<Tip>* pocetak;
 Cvor<Tip>* kraj;
 int brojelemenata;
 public:
 Red(){
     
     pocetak = nullptr;
     kraj = nullptr;
     brojelemenata = 0;
     
 }
 ~Red(){
     brisi();
 }
 Red(const Red& r){
  brojelemenata=0;
  Cvor<Tip>* pom = r.pocetak;
  while(pom!=nullptr){
   stavi(pom->el);
   pom = pom->veza;
  }
 // kraj->veza = nullptr;
  brojelemenata = r.brojelemenata;
     /*brojelemenata = r.brojelemenata;
     for(Cvor<Tip>* i=r.pocetak; i!=nullptr; i=i->veza){
     Cvor<Tip>* novi = new Cvor<Tip>{i->el,nullptr};
      if(i==r.pocetak) pocetak = novi;
      if(i==r.kraj) kraj = novi; */
   
     /* for(Cvor<Tip>* i=lista.dajPocetni(); i!=nullptr; i=i->veza) {
            Cvor<Tip>* dodani = new Cvor<Tip>{i->el,nullptr};
            if(i==r.pocetni) pocetni = dodani;
            else prethodnik->veza = dodani;
            prethodnik = dodani;
            m++;
            //dodajIza(i->el);
            
            //sljedeci();
        }
      
     } */
 
 }
 Red& operator=(const Red& r){
//  brojelemenata=0;
     if(r.pocetak==pocetak) return *this;
     brisi();
     Cvor<Tip>* pom = r.pocetak;
  while(pom!=nullptr){
   stavi(pom->el);
   pom = pom->veza;
  }
 // kraj->veza = nullptr;
   return *this;
     
 }
 Red operator=(const Red& r) const{
  //brojelemenata=0;
     if(r.pocetak==pocetak) return *this;
     brisi();
     Cvor<Tip>* pom = r.pocetak;
  while(pom!=nullptr){
   stavi(pom->el);
   pom = pom->veza;
  }
//  kraj->veza = nullptr;
   return *this;
     
 }
 void stavi(const Tip& el){
     
     Cvor<Tip>* novi = new Cvor<Tip>{el,nullptr};
     if(brojelemenata==0){
         pocetak = novi;
         kraj = novi;
     }
     else {
         kraj->veza = novi;
         kraj = kraj->veza;
     }
     brojelemenata++;
 }
 Tip skini(){
     if(brojelemenata==0) throw std::logic_error("Red je prazan.");
     Tip el = pocetak->el;
     Cvor<Tip>* c = pocetak;
     if(pocetak==kraj){
         pocetak = nullptr;
         kraj = nullptr;
     }
     else {
         pocetak = pocetak->veza;
     }
     delete c;
     brojelemenata--;
     return el;
     
 }
 
 Tip& celo(){
     if(brojelemenata==0) throw std::logic_error("Red je prazan.");
     return pocetak->el;
 }
 int brojElemenata(){
     return brojelemenata;
 }
 void brisi(){
     int i = 0;
     while(i<brojelemenata){
         Cvor<Tip>* pom = pocetak->veza;
         delete pocetak;
         pocetak = pom;
         i++;
     }
     
     
    /* if(pocetak==kraj){
         delete pocetak;
         
     }
     else{
         Cvor<Tip>* c = pocetak;
         for(Cvor<Tip>* i=pocetak; i!=nullptr; i=i->veza){
             c = i->veza;
             delete i;
             i = c;
         }
     }
     brojelemenata=0;
     pocetak = nullptr;
     kraj = nullptr;
 }
*/
brojelemenata=0;
 }
friend void TestStavi();
friend void TestCelo();
friend void TestStavi();
friend void TestBrisi();
friend void TestBrojElemenata();
//friend void Test
};

void funkcija(Stek<Red<int>> &s, Red<int> &r, Red<int> &r2){
    r = s.skini();
    int br_el;
    while(s.brojElemenata()!=0){
        br_el = s.vrh().brojElemenata();
        r2.stavi(br_el);
        for(int i=0; i<br_el; i++)
        r2.stavi(s.vrh().skini());
        s.skini();
        
    }
    r2.stavi(r.brojElemenata());
    while(r.brojElemenata()!=0)
    r2.stavi(r.skini());
    int a;
    while(r2.brojElemenata()!=0){
        a = r2.skini();
        for(int i=0; i<a; i++)
        r.stavi(r2.skini());
        s.stavi(r);
        r.brisi();
    }
}

struct Par{
    int x;
    int y;
};
void pretraga(Par** niz, int n, int m, Par tr){
    
    int p = 0;
    int k = n-1;
    int sr;
    bool nadjen = false;
    while(p<=k){
        
        sr = (k-p)/2+p;
        if(tr.x==niz[sr][0].x){
            nadjen = true;
            break;
        }
    if(tr.x>niz[sr][0].x) p = sr+1;
    else k = sr-1;
}
if(!nadjen){
    std::cout << "Takav par ne postoji";
    return;
}
nadjen = false;
int red = sr;
p=0;
k = m-1;
while(p<=k){
        
        sr = (k-p)/2+p;
        if(tr.y==niz[0][sr].y){
            nadjen = true;
            break;
        }
    if(tr.x>niz[0][sr].y) p = sr+1;
    else k = sr-1;
}
if(!nadjen){
    std::cout << "Takav par ne postoji";
    return;
}
else std::cout << "Par se nalazi na poziciji " << red << " " << sr;
}

void premjestiNeparne(Stek<int> &s, Red<int> &r, int i=-1){
    if(s.brojElemenata()==0) return;
    int a = s.skini();
    i++;
    premjestiNeparne(s,r,i);
    if(a%2==0) s.stavi(a);
    if(a%2==1) r.stavi(a);
    if(i==0){
        
        while(r.brojElemenata()!=0)
        s.stavi(r.skini());
        
    return;
    }
}
int main(){
    
    Red<int> r1, r2, r3, r4;
    r1.stavi(10);
     r1.stavi(11);
    r1.stavi(12);
    r1.stavi(13);
    r1.stavi(14);
     r2.stavi(7);
     r2.stavi(8);
     r2.stavi(9);
     r3.stavi(4);
     r3.stavi(5);
     r3.stavi(6);
     r4.stavi(1);
     r4.stavi(2);
     r4.stavi(3);
    Red<int> r5, r6;
    Stek<Red<int>> s;
    s.stavi(r1);
    s.stavi(r2);
    s.stavi(r3);
    s.stavi(r4);
    funkcija(s,r5,r6);
    r1 = s.skini();
    r2 = s.skini();
    r3 = s.skini();
    r4 = s.skini();
    
    Par** matrica;
    matrica = new Par*[3];
    for(int i=0; i<3; i++)
    matrica[i] = new Par[5];
    int a;
    int b;
    for(int i=0; i<3; i++)
     for(int j=0; j<5; j++){
         if(i==0) a = 13;
         if(i==1) a = 22;
         if(i==2) a = 31;
          if(j==0) b = 1;
         if(j==1) b = 2;
         if(j==2) b = 3;
          if(j==3) b = 4;
         if(j==4) b = 5;

         matrica[i][j].x = a;
         matrica[i][j].y = b;
     }
    Par p = {22,3};
    pretraga(matrica,3,5,p);
    
    Stek<int> szz;
    for(int i=1; i<9; i++)
    szz.stavi(i);
    Red<int> r;
    premjestiNeparne(szz,r);
    while(szz.brojElemenata()!=0)
    std::cout << szz.skini() << " ";
    
    return 0;
}







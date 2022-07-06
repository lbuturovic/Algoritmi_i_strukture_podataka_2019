#include <iostream>
template <typename Tip>
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

void TestSkini(){
 Red<int> r;
 for(int i=-3; i<1; i++)
 r.stavi(i);
 std::cout << "skini(): ";
 if(r.skini()!=-3 || r.skini()!=-2 || r.skini()!=-1){
 std::cout << "TEST NEUSPJESAN\n";
 }
 else std::cout << "TEST USPJESAN\n";
}
void TestStavi(){
 Red<int> r;
 for(int i=-3; i<1; i++)
 r.stavi(i);
 std::cout << "stavi(): ";
 if(r.brojelemenata!=4)
 std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestCelo(){
 Red<int> r;
 bool uspjesan = false;
 try{
  r.celo();
 }
 catch(...){
  uspjesan = true;
 }
 for(int i=-3; i<1; i++)
 r.stavi(i);
 std::cout << "celo(): ";
 if(r.celo()!=-3 && !uspjesan)
 std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestBrisi(){
 Red<int> r;
 for(int i=2; i<19; i++)
 r.stavi(i);
 r.brisi();
 std::cout << "brisi(): ";
 if(r.brojelemenata!=0) std::cout<<"TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
 
}
void TestBrojElemenata(){
 Red<int> r;
 for(int i=0; i<15; i++)
 r.stavi(i);
 for(int i=0; i<5; i++)
 r.skini();
 std::cout << "brojElemenata(): ";
 if(r.brojElemenata()!=10) std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestKopirajuciKonstruktor(){
 Red<int> r;
 for(int i=0; i<15; i++)
 r.stavi(i);
 Red<int> r2(r);
 bool uspjesan = true;
 if(r2.brojElemenata()!=r.brojElemenata()) uspjesan = false;
 for(int i=0; i<r2.brojElemenata();i++){
  if(r.skini()!=r2.skini()) {
   uspjesan = false;
   break;
  }
 }
 
 std::cout <<  "Kopirajuci konstruktor: ";
 if(uspjesan) std::cout << "TEST USPJESAN\n";
 else std::cout << "TEST NEUSPJESAN\n";
}
void TestDefaultKonstruktor(){
  Red<int> r;
  std::cout << "Default konstruktor: ";
  if(r.brojElemenata()!=0) std::cout << "TEST NEUSPJESAN\n";
  else std::cout << "TEST USPJESAN\n";
 }
 void TestOperatorDodjele(){
  Red<int> r;
  Red<int> r2;
 for(int i=0; i<15; i++){
 r.stavi(i);
 r2.stavi(i+2);
 }
 r2 = r;
 bool uspjesan = true;
 if(r2.brojElemenata()!=r.brojElemenata()) uspjesan = false;
 for(int i=0; i<r2.brojElemenata();i++){
  if(r.skini()!=r2.skini()) {
   uspjesan = false;
   break;
  }
 }
 
 std::cout <<  "Operator dodjele: ";
 if(uspjesan) std::cout << "TEST USPJESAN\n";
 else std::cout << "TEST NEUSPJESAN\n";
 }
 
 void modifikuj(Red<int> &a, Red<int> &b){
  
  int brojNeparnihA = 0;
   while(a.brojElemenata()!=0){
    if(a.celo()%2!=0) brojNeparnihA ++;
   b.stavi(a.skini());
   
  }
  int brojB = b.brojElemenata();
  
  while(brojB!=0){
   
   if(b.celo()%2!=0) b.stavi(b.skini());
   else a.stavi(b.skini());
   brojB--;
  }
  int brojNeparnihB = b.brojElemenata()-brojNeparnihA;
  while(brojNeparnihB!=0){
   
   b.stavi(b.skini());
   brojNeparnihB--;
  }
  
 
  
  brojB = b.brojElemenata();
  
  while(brojB!=0){
   if(b.celo()%2==0) a.stavi(b.skini());
   else b.stavi(b.skini());
   brojB--;
  }
 
 }
int main() {
  /*  std::cout << "Testovi za Red: " << std::endl;
    TestSkini();
    TestStavi();
    TestCelo();
    TestBrisi();
    TestBrojElemenata();
    TestKopirajuciKonstruktor();
    TestDefaultKonstruktor();
    TestOperatorDodjele(); */
    Red<int> a;
    Red<int> b;
    a.stavi(7);
    a.stavi(2);
    a.stavi(4);
    a.stavi(3);
    
    a.stavi(11);
    a.stavi(8);
    a.stavi(10);
    
    b.stavi(1);
    b.stavi(5);
    b.stavi(4);
    b.stavi(6);
    b.stavi(3);
    b.stavi(5);
    b.stavi(9);    
    
    modifikuj(a,b);
    while(a.brojElemenata()!=0)
    std::cout << a.skini() << " ";
    std::cout << "\n";
    
    while(b.brojElemenata()!=0)
    std::cout << b.skini() << " ";
    
    return 0;
}

#include <iostream>
template <typename Tip>
struct Cvor {
    Tip el;
    Cvor* veza;
    Cvor* pret;
};
template<typename Tip>
class DvostraniRed {
 Cvor<Tip>* pocetak;
 Cvor<Tip>* kraj;
 int brojelemenata;
 public:
 DvostraniRed(){
     
     pocetak = nullptr;
     kraj = nullptr;
     brojelemenata = 0;
     
 }
 ~DvostraniRed(){
     brisi();
 }
 DvostraniRed(const DvostraniRed& r){
  brojelemenata=0;
  Cvor<Tip>* pom = r.pocetak;
  while(pom!=nullptr){
   staviNaVrh(pom->el);
   pom = pom->veza;
  }
  brojelemenata = r.brojelemenata;
     
 }
 DvostraniRed& operator=(const DvostraniRed& r){
     if(r.pocetak==pocetak) return *this;
     brisi();
     Cvor<Tip>* pom = r.pocetak;
  while(pom!=nullptr){
   staviNaVrh(pom->el);
   pom = pom->veza;
  }
 // kraj->veza = nullptr;
   return *this;
     
 }
 DvostraniRed operator=(const DvostraniRed& r) const{
  //brojelemenata=0;
     if(r.pocetak==pocetak) return *this;
     brisi();
     Cvor<Tip>* pom = r.pocetak;
  while(pom!=nullptr){
   staviNaVrh(pom->el);
   pom = pom->veza;
  }
//  kraj->veza = nullptr;
   return *this;
     
 }
 void staviNaVrh(const Tip& el){
     
     Cvor<Tip>* novi = new Cvor<Tip>{el,nullptr,nullptr};
     if(brojelemenata==0){
         pocetak = novi;
         kraj = novi;
     }
     else {
         kraj->veza = novi;
         novi->pret = kraj;
         kraj = kraj->veza;
     }
     brojelemenata++;
 }
 void staviNaCelo(const Tip& el){
  
  Cvor<Tip>* novi = new Cvor<Tip>{el,nullptr,nullptr};
  if(brojelemenata==0){
   pocetak = novi;
   kraj = novi;
  }
  else {
   pocetak->pret = novi;
   novi->veza = pocetak;
   pocetak = novi;
  }
  brojelemenata++;
 }
 Tip skiniSaCela(){
     if(brojelemenata==0) throw std::logic_error("Red je prazan.");
     Tip el = pocetak->el;
     Cvor<Tip>* c = pocetak;
     if(pocetak==kraj){
         pocetak = nullptr;
         kraj = nullptr;
     }
     else {
         pocetak = pocetak->veza;
         pocetak->pret = nullptr;
     }
     delete c;
     brojelemenata--;
     return el;
     
 }
 Tip skiniSaVrha(){
  if(brojelemenata==0) throw std::logic_error("Red je prazan");
  Tip el = kraj->el;
  Cvor<Tip>* c = kraj;
  if(pocetak == kraj) {
     pocetak = nullptr;
     kraj = nullptr;
  }
  else {
    kraj = kraj->pret;
    kraj->veza = nullptr;
   
  }
  delete c;
  brojelemenata--;
  return el;
 }
 
 
 Tip& celo(){
     if(brojelemenata==0) throw std::logic_error("Red je prazan.");
     return pocetak->el;
 }
 Tip& vrh(){
    if(brojelemenata==0) throw std::logic_error("Red je prazan");
    return kraj->el;
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
brojelemenata=0;
 }
friend void TestStaviNaCelo();
friend void TestCelo();
friend void TestVrh();
friend void TestStaviNaVrh();
friend void TestBrisi();
friend void TestBrojElemenata();
//friend void Test
};
void TestStaviNaVrh(){
 DvostraniRed<int> r;
 for(int i = 0; i<5; i++)
 r.staviNaVrh(i);
 std::cout << "staviNaVrh(): ";
 if(r.brojelemenata!=5 || r.vrh()!=4 || r.celo()!=0) std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestStaviNaCelo(){
 DvostraniRed<int> r;
 for(int i = 0; i<5; i++)
 r.staviNaCelo(i);
 std::cout << "staviNaCelo(): ";
 if(r.brojelemenata!=5 || r.celo()!=4 || r.vrh()!=0) std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestSkiniSaVrha(){
 DvostraniRed<int> r;
 for(int i = 0; i<5; i++)
 r.staviNaVrh(i);
 std::cout << "skiniSaVrha(): ";
 if(r.skiniSaVrha()!=4 || r.skiniSaVrha()!=3 || r.skiniSaVrha()!=2
 || r.skiniSaVrha()!=1 || r.skiniSaVrha()!=0)
 std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestSkiniSaCela(){
 DvostraniRed<int> r;
 for(int i = 0; i<5; i++)
 r.staviNaVrh(i);
 std::cout << "skiniSaCela(): ";
 if(r.skiniSaCela()!=0 || r.skiniSaCela()!=1 || r.skiniSaCela()!=2
 || r.skiniSaCela()!=3 || r.skiniSaCela()!=4)
 std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
}
void TestBrojElemenata(){
 DvostraniRed<int> r;
 for(int i = 0; i<9; i++)
 r.staviNaCelo(i);
 std::cout << "brojElemenata(): ";
 if(r.brojElemenata()==9) std::cout << "TEST USPJESAN\n";
 else std::cout << "TEST NEUSPJESAN\n";
}
void TestBrisi(){
 DvostraniRed<int> r;
 for(int i = 0; i<22; i++)
 r.staviNaCelo(i);
 r.brisi();
 std::cout << "brisi(): ";
 if(r.brojelemenata!=0) std::cout << "TEST NEUSPJESAN\n";
 else std::cout << "TEST USPJESAN\n";
 
}
void TestCelo(){
 DvostraniRed<int> r;
 bool uspjelo = false;
 try {
  r.celo();
 }
 catch(...){
  uspjelo = true;
 }
 std::cout << "celo(): ";
 for(int i = 0; i<10; i++){
 r.staviNaCelo(i);
 
 if(r.celo()!=i || !uspjelo) {
  std::cout << "TEST NEUSPJESAN\n";
  return;
 }
 }
  std::cout << "TEST USPJESAN\n";
}

void TestVrh(){
 DvostraniRed<int> r;
 bool uspjelo = false;
 try {
  r.vrh();
 }
 catch(...){
  uspjelo = true;
 }
 std::cout << "vrh(): ";
 for(int i = 0; i<10; i++){
 r.staviNaVrh(i);
 
 if(r.vrh()!=i || !uspjelo) {
  std::cout << "TEST NEUSPJESAN\n";
  return;
 }
 }
  std::cout << "TEST USPJESAN\n";
}

int main() {
    std::cout << "Testovi za DvostraniRed: " << std::endl;
    TestBrojElemenata();
    TestBrisi();
    TestStaviNaCelo();
    TestStaviNaVrh();
    TestSkiniSaCela();
    TestSkiniSaVrha();
    TestCelo();
    TestVrh();
    return 0;
}

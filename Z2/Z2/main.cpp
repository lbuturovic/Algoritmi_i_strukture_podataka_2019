#include <iostream>
#include <vector>
int indeks = -1;  //zbog testiranja
int brojispod = -1; 
int vraceno = 0;
template<typename Tip>
class Iterator;
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
    friend class Iterator<Tip>;
};
/*template <typename Tip>
class Iterator {
    const Stek<Tip>* s;
    int i;
    public:
    Iterator(const Stek<Tip> &st){
        s = &st;
        i = 0;
    }
    const Tip& trenutni() const{
        return s->stek[i];
    }
    Tip* begin(){
    return &(s->stek[0]);
    }
    Tip* end(){
        return &(s->stek[s->brojelemenata-1]);
    }
    Tip* next(){
        i++;
        return &(s->stek[i]);
    }
};  */

void pretraga(Stek<std::vector<int>>&s, int trazeni,bool nadjen = false)
{
    if(nadjen) {
        return;
    }
    if(!nadjen && s.brojElemenata()==0) {
        brojispod = -2; // za potrebe testiranja
        indeks = -2;   // za potrebe testiranja
        std::cout << "Nema elementa";
        return;
    }
    std::vector<int> v = s.skini();
    nadjen = false;
    int sr;
    int p = 0, k=v.size()-1;
    while(p<=k) {
        sr = (k-p)/2 + p;
        if(v.at(sr)==trazeni) {
            nadjen = true;
            break;
        }
        if(v.at(sr)<trazeni) p = sr + 1;
        else k = sr - 1;
    }
    if(nadjen) {
        indeks = sr;  // za potrebe testiranja
        brojispod = s.brojElemenata(); // za potrebe testiranja
        std::cout << sr << " " << s.brojElemenata();

    }
    pretraga(s,trazeni,nadjen);
    s.stavi(v);
    vraceno++; // za testiranja
    return;

}
/*void pretraga(Stek<std::vector<int>>&s, int trazeni){
    Iterator<std::vector<int>> it(s);
    int br = 0;
    for(auto i=it.begin();i<=it.end();i=it.next()){
        if(it.trenutni().at(0)<=trazeni && it.trenutni().at(it.trenutni().size()-1)>=trazeni) break;
        br++;
    }
    if(br==s.brojElemenata()) {
        std::cout << "Nema elementa";
       // throw std::string("Nema elementa");
        return;
    }
    bool nadjen = false;
   int sr;
    int p = 0, k=it.trenutni().size()-1;
    while(p<=k){
        sr = (k-p)/2 + p;
        if(it.trenutni().at(sr)==trazeni) {
            nadjen = true;
            break;
        }
        if(it.trenutni().at(sr)<trazeni) p = sr + 1;
        else k = sr - 1;

    }
    if(nadjen){
    std::cout << sr << " " << br;
    std::string s;
    s.push_back(sr+'0');
    s.push_back(' ');
    s.push_back(br+'0');
  //  throw s;
}
    else {std::cout << "Nema elementa";
 //   throw  std::string ("Nema elementa");

    }

}  */
void Test1()
{
    std::cout << "TEST1     ";
    Stek<std::vector<int>> s;
    std::vector<int> v1 = {2,4,6,8,10};
    std::vector<int> v2 = {13, 16, 19, 22, 25};
    std::vector<int> v3 = {26,27,28,30,31,32};
    s.stavi(v1);
    s.stavi(v2);
    s.stavi(v3);
    std::cout << "Izlaz: ";
    pretraga(s,30);
    std::cout << " Ocekivani izlaz: 3 2";
    if(indeks==3 && brojispod==2 && vraceno == 1)
        std::cout << ", TEST1 USPJESAN\n";
    else std::cout << ", TEST1 NEUSPJESAN\n";
    brojispod = -1;
    indeks = -1;
    vraceno = 0;
}
void Test2()
{
    std::cout << "TEST2     ";
    Stek<std::vector<int>> s;
    std::vector<int> v1 = {2,4,6,8,10};
    std::vector<int> v2 = {13, 16, 19, 22, 25};
    std::vector<int> v3 = {26,27,28,30,31,32};
    s.stavi(v1);
    s.stavi(v2);
    s.stavi(v3);
    std::cout << "Izlaz: ";
    pretraga(s,20);
    std::cout << " Ocekivani izlaz: Nema elementa ";
    if(brojispod==-2 && indeks==-2 && vraceno==3 ) std::cout << ", TEST2 USPJESAN\n";
    else std::cout << ", TEST2 NEUSPJESAN\n";
    brojispod = -1;
    indeks = -1;
    vraceno = 0;
}
void Test3()
{ 
    std::cout << "TEST3     ";
    Stek<std::vector<int>> s;
    std::vector<int> v1 = {2,4,6,8,10};
    std::vector<int> v2 = {13, 16, 19, 22, 25};
    std::vector<int> v3 = {26,27,28,30,31,32};
    s.stavi(v1);
    s.stavi(v2);
    s.stavi(v3);
    std::cout << "Izlaz: ";
    pretraga(s,10800);
    std::cout << " Nije se desila promjena u steku: ";
    if(s.skini()!=v3 || s.skini()!=v2 ||  s.skini()!=v1) std::cout << "TEST3 NEUSPJESAN\n";
    else std::cout << "TEST3 USPJESAN\n";
    brojispod = -1;
    indeks = -1;
    vraceno = 0;
}
int main()
{
    Test1();
    Test2();
    Test3();
    return 0;
}

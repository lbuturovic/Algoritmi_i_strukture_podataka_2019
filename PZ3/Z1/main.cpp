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
void TestVrh(){
    Stek<int> s;
    bool uspjesan = true;
    s.stavi(3);
    if(s.vrh()!=3) uspjesan = false;
    s.stavi(88);
    if(s.vrh()!=88) uspjesan = false;
    std::cout << "vrh: ";
    if(!uspjesan) std::cout << "TEST NEUSPJESAN\n";
    else std::cout << "TEST USPJESAN\n";
}
void TestSkini(){
    Stek<int> s;
    for(int i=0; i<6; i++)
    s.stavi(i);
    int a = s.skini();
    std::cout << "skini: ";
    if(a!=5 || s.brojelemenata!=5) std::cout << "TEST NEUSPJESAN\n";
    else std::cout << "TEST USPJESAN\n";
}
void TestBrojElemenata(){
    Stek<int> s;
    for(int i=0; i<100; i++)
    s.stavi(i+2);
    std::cout << "brojElemenata: ";
    if(s.brojElemenata()!=100) std::cout << "TEST NEUSPJESAN\n";
    else std::cout << "TEST USPJESAN\n";
    
}
void TestStavi(){
    Stek<int> s;
    int niz[5] = {2,4,6,8,10};
    for(int i=2; i<=10; i=i+2){
        s.stavi(i);
    }
    bool uspjesan = true;
    std::cout << "stavi: ";
    for(int i=0; i<5; i++){
    if(s.stek[i]!=niz[i]) {
        std::cout << "TEST NEUSPJESAN\n";
        uspjesan = false;
        break;
    }
    }
    if(uspjesan) std::cout << "TEST USPJESAN\n";
}
void TestBrisi(){
    Stek<int> s;
    for(int i=0; i<10; i++){
        s.stavi(i+2);
    }
    s.brisi();
    std::cout << "brisi: ";
    if(s.brojelemenata==0) std::cout << "TEST USPJESAN\n";
    else std::cout << "TEST NEUSPJESAN\n";
}
bool provjeri_zagrade(std::string tekst){
    Stek<char> s;
    char z='0'; // = '0';
    for(int i=0; i<tekst.size();i++){
        if(tekst.at(i)=='(' || tekst.at(i)=='[' || tekst.at(i)=='{' ) s.stavi(tekst.at(i));
        else if(tekst.at(i)==')' || tekst.at(i)==']' || tekst.at(i)=='}') {
         
        char prethodni = z;  
        if(tekst.at(i)==')' && (prethodni == '0' || prethodni == ']')) z ='(';
        if(tekst.at(i)==']'&& (prethodni == '0' || prethodni == '}')) z = '[';
        if(tekst.at(i)=='}'&& (prethodni == '0')) z = '{';
        if(z!=s.vrh()) return false;
            s.skini();
            
            
        }
        
    }
    if(s.brojElemenata()!=0) return false;
    return true;
}
template <typename Tip>
Stek<Tip> spojiSortirano(Stek<Tip> s1, Stek<Tip> s2){
    
}
int pomocnaNajveciAVeciOdSume(Stek<int> st, int s, int max){
    if(st.brojElemenata()==0) return max;
    int el = st.skini();
    if(el>max && el>s) max = el;
    return pomocnaNajveciAVeciOdSume(st,s+el,max);
    st.stavi(el);
}
int najveciAveciOdSume(Stek<int> s){
    int max = s.vrh();
    return pomocnaNajveciAVeciOdSume(s,0,max);
}
int main()
{
   // std::string s ("()");
    //std::cout << provjeri_zagrade(s);
  //  TestVrh();
    //TestSkini();
    //TestStavi();
    //TestBrojElemenata();
    //TestBrisi();
    Stek<int> s;
    s.stavi(9);
    s.stavi(8);
    s.stavi(1);
    s.stavi(1);
    s.stavi(1);
    s.stavi(3);
    s.stavi(1);
    std::cout << najveciAveciOdSume(s);
    return 0;
}

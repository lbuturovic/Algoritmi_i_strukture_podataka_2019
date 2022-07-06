#include <iostream>
#include <set>
#include <tuple>
#include <list>
#include <vector>
#include<queue>
using namespace std;

template<typename Tip1, typename Tip2>
class HashMapaLan 
{
struct Cvor {
    
    Tip1 k;
    Tip2 el;
    //Cvor* pret;
    Cvor* sljed;
};

    int brojelemenata;
    mutable int zabrisanje = -1;
    Cvor** mapa;
    //Tip2** vrijednosti;
    int kapacitet = 20;
    unsigned int (*hash)(Tip1,unsigned int);

public:

    HashMapaLan()
    {
        brojelemenata = 0;
        kapacitet = 20;
        mapa = new Cvor*[20] {};
        hash = nullptr;
    }

    ~HashMapaLan()
    {
        obrisi();
        delete [] mapa;
        mapa = nullptr;
    }

    void obrisi(const Tip1& kljuc)
    {
        unsigned int j = 0;
        if(!hash) throw std::logic_error("Hash funkcija nije definisana.");
        j = (*hash)(kljuc,kapacitet);
        if(mapa[j]==nullptr || mapa[j]->k>kljuc) return;
        Cvor* prethodnik = nullptr;
        auto i = mapa[j];
        for(i=mapa[j];i!=nullptr;i=i->sljed){
            if(i->k==kljuc) break;
            
            prethodnik = i;
        }
        
        if(prethodnik==nullptr) {
            auto pom = mapa[j]->sljed;
            delete mapa[j];
            brojelemenata--;
            mapa[j] = pom;
            return;
    }
    prethodnik->sljed = i->sljed;
    delete i;
    brojelemenata--;
    }
    void obrisi()
    {
        for(int i=0; i<kapacitet; i++) {
            Cvor* c = mapa[i]; //prvi cvor
            for(auto it=mapa[i]; it!=nullptr; it=c){
                c = c->sljed;
                delete it;
                it = c; 
            }
            
            mapa[i] = nullptr;
        }

        brojelemenata = 0;
    }
    int brojElemenata() const
    {
        return brojelemenata;
    }

    HashMapaLan(const HashMapaLan& m)
    {

        brojelemenata = m.brojelemenata;
        kapacitet = m.kapacitet;
        hash = m.hash;
        mapa = new Cvor* [kapacitet]{};
        for(int i=0; i<kapacitet; i++) {
            Cvor* prethodnik = nullptr;
            for(Cvor* it=m.mapa[i]; it!=nullptr; it=it->sljed) {
            Cvor* dodani = new Cvor{it->k,it->el,nullptr};
            if(mapa[i]==nullptr) mapa[i] = dodani;
            else prethodnik->sljed = dodani;
            prethodnik = dodani;
            //dodajIza(i->el);
            
            //sljedeci();
        }
        }
    }
    

    HashMapaLan& operator =(const HashMapaLan& m)
    {
        if(this==&m) return *this;
        obrisi();
        kapacitet = m.kapacitet;
        brojelemenata = m.brojelemenata;
        hash = m.hash;
        delete [] mapa;
         
         mapa = new Cvor* [kapacitet]{};
        for(int i=0; i<kapacitet; i++) {
            Cvor* prethodnik = nullptr;
            for(Cvor* it=m.mapa[i]; it!=nullptr; it=it->sljed) {
            Cvor* dodani = new Cvor{it->k,it->el,nullptr};
            if(mapa[i]==0) mapa[i] = dodani;
            else prethodnik->sljed = dodani;
            prethodnik = dodani;
            //dodajIza(i->el);
            
            //sljedeci();
        }
        }
        return *this;
    }

    void definisiHashFunkciju (unsigned int (*fun)(Tip1,unsigned int))
    {
        hash = fun;
    }


Tip2& operator[](Tip1 kljuc) {
        unsigned int j = 0;
        if(!hash) throw std::logic_error("Hash funkcija nije definisana.");
        j = (*hash)(kljuc,kapacitet);
        if(mapa[j]==nullptr) {
            mapa[j] = new Cvor{kljuc,Tip2(),nullptr};
            brojelemenata++;
            return mapa[j]->el;
        }
        
        Cvor* prethodnik = nullptr;
        auto i = mapa[j];
        for(i = mapa[j];i!=nullptr;i=i->sljed){
            if(i->k==kljuc) return i->el;
            if(i->k>kljuc) break;
            
            prethodnik = i;
           // i = i->sljed;
            
        }
        Cvor* dodani = new Cvor{kljuc, Tip2(), i};
        brojelemenata++;
        if(!prethodnik) mapa[j] = dodani;
        else
        prethodnik->sljed = dodani;
        return dodani->el;
        
       
        
}
const Tip2 operator[](Tip1 kljuc) const {
        unsigned int j = 0;
        if(!hash) throw std::logic_error("Hash funkcija nije definisana.");
        j = (*hash)(kljuc,kapacitet);
        if(mapa[j]==nullptr) {
            return Tip2();
        }
        if(mapa[j]->k>kljuc) {
            return Tip2();}
       for(auto i = mapa[j];i!=nullptr;i=i->sljed){
            if(i->k==kljuc) return i->el;
       }
        return Tip2();
        
} 


};

template <typename TipOznake>
class UsmjereniGraf;
template<typename TipOznake>
class Cvor{
    TipOznake o;
    int r;
    UsmjereniGraf<TipOznake>* graf;
    public:
    Cvor(UsmjereniGraf<TipOznake>* g, int r, TipOznake o = TipOznake()){
        graf = g;
        this->r = r;
        this->o = o;
    }
    TipOznake dajOznaku(){
        return graf->dajOznakuCvora(r);
    }
    void postaviOznaku(TipOznake o){
        this->o = o;
        graf->postaviOznakuCvora(r,o);
    }
    int dajRedniBroj(){
        return r;
    }
};
template<typename TipOznake>
class Grana;

template<typename TipOznake>
class GranaIterator{
    int p, k;
    UsmjereniGraf<TipOznake>* graf;
    public:
    GranaIterator(UsmjereniGraf<TipOznake>* g, int p, int k){
        graf = g;
        this->p = p;
        this->k = k;
    }
    Grana <TipOznake> operator*(){
        return graf->dajGranu(p,k);
    }
    bool operator ==(const GranaIterator &iter) const{
        if(p==iter.p && k==iter.k && graf==iter.graf) return true;
        return false;
    }
     bool operator !=(const GranaIterator &iter) const{
        if(p==iter.p && k==iter.k && graf==iter.graf) return false;
        return true;
    }
    GranaIterator<TipOznake>& operator++(int){
        int i, j;
        for(i=p; i<graf->dajBrojCvorova(); i++)
            for(j=k;j<graf->dajBrojCvorova();j++){
                if(j<=k && i==p) continue;
                if(graf->postojiGrana(i,j)){
                    p = i;
                    k = j;
                    return *this;
                    break;
                }
        return *this;
    }
    }
    GranaIterator<TipOznake>& operator++(){
        int i, j;
        for(i=p; i<graf->dajBrojCvorova(); i++)
            for(j=0;j<graf->dajBrojCvorova();j++){
                if(j<=k && i==p) continue;
                if(graf->postojiGrana(i,j)){
                    p = i;
                    k = j;
                    return *this;
                    break;
                }
               // if(graf->dajGraneKraj()==*this) return *this;
            }
            //i = graf->dajBrojCvorova()-1;
            //j = graf->dajBrojCvorova()-1;
            *this = graf->dajGraneKraj();
        return *this;
    }
    
    
};
template <typename TipOznake>
class Grana {
    int p, k;
    float t;
     UsmjereniGraf<TipOznake>* graf;
    TipOznake o;
    public:
    Grana(UsmjereniGraf<TipOznake>* g,int p, int k,float t,TipOznake o = TipOznake()){
        graf = g;
        this->p = p;
        this->k = k;
        this->t = t;
        this->o = o;
    }
     TipOznake dajOznaku(){
        return graf->dajOznakuGrane(p,k);
    }
    void postaviOznaku(TipOznake o = TipOznake()){
        this->o = o;
        graf->postaviOznakuGrane(p,k,o);
    }
     float dajTezinu(){
        return graf->dajTezinuGrane(p,k);
    }
    void postaviTezinu(float t = 0){
        this->t = t;
        graf->postaviTezinuGrane(p,k,t);
    }
    Cvor<TipOznake> dajPolazniCvor(){
        return graf->dajCvor(p);
    }
    Cvor<TipOznake> dajDolazniCvor(){
        return graf->dajCvor(k);
    }
    
};
template <typename TipOznake>
class UsmjereniGraf{
    public:
    UsmjereniGraf(){}
    UsmjereniGraf(int n){}
    virtual ~UsmjereniGraf(){};
    virtual int dajBrojCvorova() const = 0;
    virtual void postaviBrojCvorova(int n) = 0;
    virtual void postaviTezinuGrane(int p, int k, float t=0) = 0;
    virtual void dodajGranu(int p, int k, float t=0) = 0;
    virtual float dajTezinuGrane(int p, int k) const = 0;
    virtual bool postojiGrana(int p, int k) const = 0;
    virtual void postaviOznakuCvora(int c, TipOznake o) = 0;
    virtual void postaviOznakuGrane(int p, int k, TipOznake o) = 0;
    virtual void obrisiGranu(int p, int k) = 0;
    virtual TipOznake dajOznakuCvora(int c) const = 0;
    virtual TipOznake dajOznakuGrane(int p, int k) const = 0;
    virtual Cvor<TipOznake> dajCvor(int c)  = 0;
    virtual Grana<TipOznake> dajGranu(int p, int k) = 0;
    virtual GranaIterator<TipOznake> dajGranePocetak() = 0;
    virtual GranaIterator<TipOznake> dajGraneKraj() = 0;
    
};
template <typename TipOznake>
class ListaGraf : public UsmjereniGraf<TipOznake>{
    int prviP, prviK, zadnjiP, zadnjiK;
    int maxBrojCvorova;
    int brojGrana;
    vector<vector<int>> lista;
    vector<vector<float>> tezine;
    vector<vector<TipOznake>> oznakeGrana;
    vector<TipOznake> oznake;
   // TipOznake *posjecen;
    
    public:
    
    ListaGraf(int n){
        maxBrojCvorova = n;
        brojGrana = 0;
        lista.resize(n);
        oznake.resize(n);
        oznakeGrana.resize(n);
        tezine.resize(n);
    }
    ListaGraf(){
        ListaGraf(20);
    }
    void obrisi(){
   
        lista.clear();
        oznake.clear();
        oznakeGrana.clear();
        tezine.clear();
        }
        
         ~ListaGraf(){
             obrisi();
         }
    int dajBrojCvorova() const{
        return maxBrojCvorova;
    }
    
    void postaviBrojCvorova(int n){
        if(n<maxBrojCvorova) throw std::logic_error("Zadani broj cvorova mora biti veci od trenutnog!");
        if(n==maxBrojCvorova) return;
        
        lista.resize(n);
        oznake.resize(n);
        oznakeGrana.resize(n);
        tezine.resize(n);
        maxBrojCvorova = n;
        
    }
    ListaGraf& operator = (const ListaGraf& m) {
        lista = m.lista;
        oznake = m.oznake;
        oznakeGrana = m.oznakeGrana;
        tezine = m.tezine;
        
        maxBrojCvorova = m.maxBrojCvorova;
        brojGrana = m.brojGrana;
        
    }
    ListaGraf(const ListaGraf &m){
        maxBrojCvorova = m.maxBrojCvorova;
        brojGrana = m.brojGrana;
        lista = m.lista;
        oznake = m.oznake;
        oznakeGrana = m.oznakeGrana;
        tezine = m.tezine;
    }
    
    
    void dodajGranu(int p, int k, float t=0){
        
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        lista[p].push_back(k);
        tezine[p].push_back(t);
        oznakeGrana[p].push_back(TipOznake());
       brojGrana++;
        
    }
    
    void postaviTezinuGrane(int p, int k, float t=0){
        int i = 0;
        for(i=0; i<lista[p].size();i++)
        if(lista[p].at(i)==k) break;
        tezine[p].at(i) = t;
        
        
    }
    void obrisiGranu(int p, int k){
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        for(int i=0; i<lista[i].size();i++){
            if(lista[p].at(i)==k){
                lista[p].erase(lista[p].begin()+i);
                tezine[p].erase(tezine[p].begin()+i);
                oznakeGrana[p].erase(oznakeGrana[p].begin()+i);
                break;
            }
        }
        
    }
    float dajTezinuGrane(int p, int k) const {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        bool nadjen = false;
        int i = 0;
        for(i=0; i<lista[p].size();i++)
        if(lista[p].at(i)==k) {
            nadjen = true;
            break;
        }
       if(nadjen) return tezine[p].at(i);
       throw std::logic_error ("Nepostojeca grana!");
        
    }
    bool postojiGrana(int p, int k) const {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
       // throw std::logic_error ("Nepostojeci cvorovi!");
       return false;
       int i = 0;
       for(i=0; i<lista[p].size();i++)
        if(lista[p].at(i)==k) return true;
        return false;
        
    }
    void postaviOznakuCvora(int c, TipOznake o){
        if(c<0 || c>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        oznake[c] = o;
    }
    TipOznake dajOznakuCvora(int c) const{
        if(c<0 || c>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        return oznake[c];
    }
    
    void postaviOznakuGrane(int p, int k, TipOznake o){
         if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        int i = 0;
        bool nadjen = false;
        for(i=0; i<lista[p].size();i++)
        if(lista[p].at(i)==k) { nadjen = true; break; }
       if(nadjen) oznakeGrana[p].at(i) = o;
    }
    TipOznake dajOznakuGrane(int p, int k) const {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        bool nadjen = false;
        int i = 0;
        for(i=0; i<lista[p].size();i++)
        if(lista[p].at(i)==k) {
            nadjen = true;
            break;
        }
       if(nadjen) return oznakeGrana[p].at(i);
       throw std::logic_error ("Nepostojeca grana!");
    }
    Cvor<TipOznake> dajCvor(int c) {
        if(c<0 || c>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        return Cvor<TipOznake>(this,c);
    }
    Grana<TipOznake> dajGranu(int p, int k) {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
       // Cvor<TipOznake> c1 = Cvor<TipOznake>(this,p,posjecen[p]);
        //Cvor<TipOznake> c2 = Cvor<TipOznake>(this,k,posjecen[k]);
        return Grana<TipOznake>(this,p,k,0);
    } 
    
    GranaIterator<TipOznake> dajGranePocetak(){
        return GranaIterator<TipOznake>(this,0,0);
    }
    GranaIterator<TipOznake> dajGraneKraj(){
        return GranaIterator<TipOznake>(this, dajBrojCvorova()-1,dajBrojCvorova()-1);
    }  
};

template<typename TipOznake>
void bfs(UsmjereniGraf<TipOznake> *g, std::vector<Cvor<TipOznake>> &bfs_obilazak,
Cvor<TipOznake> poc){
    poc.postaviOznaku(1);
    bfs_obilazak.push_back(poc);
    std::queue<Cvor<TipOznake>> red;
    red.push(poc);
    while(!red.empty()){
        Cvor<TipOznake> cvor = red.front();
        red.pop();
        
    for(GranaIterator<TipOznake> it = g->dajGranePocetak(); it!=g->dajGraneKraj(); ++it){
        Cvor<TipOznake> sus = (*it).dajDolazniCvor();
        if((*it).dajPolazniCvor().dajRedniBroj()==cvor.dajRedniBroj() &&
        sus.dajOznaku()!=1){
            sus.postaviOznaku(1);
            bfs_obilazak.push_back(sus);
            red.push(sus);
        }
    }
    }
}

int main() {
    std::cout << "Zadaća 5, Zadatak 1";
    return 0;
}

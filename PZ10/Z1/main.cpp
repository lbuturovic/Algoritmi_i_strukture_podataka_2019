#include <iostream>
#include <tuple>
#include<vector>
#include<queue>
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
class MatricaGraf : public UsmjereniGraf<TipOznake>{
    int prviP, prviK, zadnjiP, zadnjiK;
    int maxBrojCvorova;
    int brojGrana;
    std::tuple<float,TipOznake,bool> **matrica;
    TipOznake *posjecen;
    
    public:
    
    MatricaGraf(int n){
        maxBrojCvorova = n;
        brojGrana = 0;
        posjecen = new TipOznake[maxBrojCvorova];
        matrica = new std::tuple<float,TipOznake,bool>*[maxBrojCvorova];
        for(int i = 0; i<maxBrojCvorova; i++){
            matrica[i] = new std::tuple<float,TipOznake,bool>[maxBrojCvorova];
            posjecen[i] = TipOznake();
        }
        
        for(int i=0; i<maxBrojCvorova; i++)
        for(int j=0; j<maxBrojCvorova; j++){
        std::get<0>(matrica[i][j]) = 0;
        std::get<1>(matrica[i][j]) = TipOznake();
        std::get<2>(matrica[i][j]) = false;
        }
    }
    MatricaGraf(){
        MatricaGraf(20);
    }
    void obrisi(){
   
        delete[] posjecen;
        for(int i=0; i<maxBrojCvorova; i++)
        delete [] matrica[i];
        delete [] matrica;
        }
        
         ~MatricaGraf(){
             obrisi();
         }
    int dajBrojCvorova() const{
        return maxBrojCvorova;
    }
    
    void postaviBrojCvorova(int n){
        if(n<maxBrojCvorova) throw std::logic_error("Zadani broj cvorova mora biti veci od trenutnog!");
        if(n==maxBrojCvorova) return;
        
        TipOznake* posjecenNovi;
        std::tuple<float, TipOznake,bool>** matricaNovi;
        posjecenNovi = new TipOznake[n];
        matricaNovi = new std::tuple<float,TipOznake,bool>*[n];
        for(int i = 0; i<n; i++){
            matricaNovi[i] = new std::tuple<float,TipOznake,bool>[n];
            posjecenNovi[i] = TipOznake();
        }
        
        for(int i=0; i<maxBrojCvorova; i++)
        for(int j=0; j<maxBrojCvorova; j++)
        matricaNovi[i][j] = matrica[i][j];
        
        for(int i=0; i<maxBrojCvorova; i++)
        posjecenNovi[i] = posjecen[i];
        
        matrica = matricaNovi;
        posjecen = posjecenNovi;
        maxBrojCvorova = n;
        
    }
    MatricaGraf& operator = (const MatricaGraf& m) {
        if(&m.matrica==this) return *this;
        obrisi();
        TipOznake* posjecenNovi;
        std::tuple<float, TipOznake, bool>** matricaNovi;
        posjecenNovi = new TipOznake[m.maxBrojCvorova];
        matricaNovi = new std::tuple<float,TipOznake,bool>*[m.maxBrojCvorova];
        for(int i = 0; i<m.maxBrojCvorova; i++){
            matricaNovi[i] = new std::tuple<float,TipOznake,bool>[m.maxBrojCvorova];
            posjecenNovi[i] = TipOznake();
        }
        
        for(int i=0; i<m.maxBrojCvorova; i++)
        for(int j=0; j<m.maxBrojCvorova; j++)
        matricaNovi[i][j] = m.matrica[i][j];
        
        for(int i=0; i<maxBrojCvorova; i++)
        posjecenNovi[i] = m.posjecen[i];
        
        matrica = matricaNovi;
        posjecen = posjecenNovi;
        maxBrojCvorova = m.maxBrojCvorova;
        brojGrana = m.brojGrana;
        return *this;
        
    }
    MatricaGraf(const MatricaGraf &m){
        TipOznake* posjecenNovi;
        std::tuple<float, TipOznake,bool>** matricaNovi;
        posjecenNovi = new TipOznake[m.maxBrojCvorova];
        matricaNovi = new std::tuple<float,TipOznake,bool>*[m.maxBrojCvorova];
        for(int i = 0; i<m.maxBrojCvorova; i++){
            matricaNovi[i] = new std::tuple<float,TipOznake,bool>[m.maxBrojCvorova];
            posjecenNovi[i] = TipOznake();
        }
        
        for(int i=0; i<m.maxBrojCvorova; i++)
        for(int j=0; j<m.maxBrojCvorova; j++)
        matricaNovi[i][j] = m.matrica[i][j];
        
        for(int i=0; i<maxBrojCvorova; i++)
        posjecenNovi[i] = m.posjecen[i];
        
        matrica = matricaNovi;
        posjecen = posjecenNovi;
        maxBrojCvorova = m.maxBrojCvorova;
        brojGrana = m.brojGrana;
    }
    
    
    void dodajGranu(int p, int k, float t=0){
        
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        if(brojGrana==0) {
            prviP = p;
            prviK = k;
            zadnjiK = k;
            zadnjiP = p;
        }
        else {
            if(p<=prviP) prviP = p;
            if(k<=prviK) prviK = k;
            if(p>=zadnjiP) zadnjiP = p;
            if(k>=zadnjiK) zadnjiK = k;
        }
        brojGrana++;
        
        std::get<0>(matrica[p][k]) = t;
        std::get<2>(matrica[p][k]) = true;
        
    }
    
    void postaviTezinuGrane(int p, int k, float t=0){
        dodajGranu(p,k,t);
        brojGrana--;
        
    }
    void obrisiGranu(int p, int k){
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        if(std::get<2>(matrica[p][k])==true){
        std::get<2>(matrica[p][k]) = false;
        brojGrana--;
        }
    }
    float dajTezinuGrane(int p, int k) const {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        //provjeri postoji li grana
        return std::get<0>(matrica[p][k]);
        
    }
    bool postojiGrana(int p, int k) const {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
       // throw std::logic_error ("Nepostojeci cvorovi!");
       return false;
        return std::get<2>(matrica[p][k]);
    }
    void postaviOznakuCvora(int c, TipOznake o){
        if(c<0 || c>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        posjecen[c] = o;
    }
    TipOznake dajOznakuCvora(int c) const{
        if(c<0 || c>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        return posjecen[c];
    }
    
    void postaviOznakuGrane(int p, int k, TipOznake o){
         if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        std::get<1>(matrica[p][k]) = o;
    }
    TipOznake dajOznakuGrane(int p, int k) const {
        if(p<0 || p>=maxBrojCvorova || k<0 || k>=maxBrojCvorova)
        throw std::logic_error ("Nepostojeci cvorovi!");
        return std::get<1>(matrica[p][k]);
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
    std::cout << "Pripremna Zadaca Za Vjezbu 10, Zadatak 1";
    return 0;
}

#include <iostream>
//#include<math.h>
int fib2_0(int n, int pretprosli=0, int prosli=1){
    if(n==1) return prosli;
    if(n==0) return pretprosli;
    return fib2_0(n-1,prosli,pretprosli+prosli); //pret je postao prosli, prosli je postao zbir
}
int nzd(int x, int y){
    if(y==0) return x;
    if(x<0) x=-1*x;
    if(y<0) y=-1*y;
    return nzd(y,x%y);
}
double pow(double a, unsigned int n){
    
    int pom;
    if(n==0) return 1;
    pom = pow(a,n/2);
    if(n%2==0) return pom*pom;
    else return a*pom*pom;
}
int main() {
    
   // std::cout << pow(5,4);
    return 0;
}

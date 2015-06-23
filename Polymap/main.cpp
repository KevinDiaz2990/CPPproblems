#include <iostream>
#include<cstdlib>
#include<sstream>
#include<map>
#include<fstream>
using namespace std;
class Poly{
 private:
 map<int, int> p;
 string str;

 public:
 Poly(){
 }

 Poly(string s){
     str = s;
     istringstream iss(s);
     int i;
     int j;
     while(iss>>i>>j){
       insert(i, j);
     }

 }
void insert(int i, int j){
    p[j]+= i;
    if(p[j]==0)
     p.erase(j);


}
string getString(){
    return str;
}
Poly operator+(Poly poly){
   Poly temp;
   temp.p = p;
   map<int, int> :: reverse_iterator ri;
   for(ri = poly.p.rbegin(); ri!= poly.p.rend(); ri++){
       temp.p[ri->first]+= ri->second;
       if(temp.p[ri->first]==0)
       temp.p.erase(ri->first);
   }
return temp;
}

Poly operator-(Poly poly){
   Poly temp;
   temp.p = p;
   map<int, int> :: reverse_iterator ri;
   for(ri = poly.p.rbegin(); ri!= poly.p.rend(); ri++){
       temp.p[ri->first]-= ri->second;
       if(temp.p[ri->first]==0)
       temp.p.erase(ri->first);
   }
return temp;
}
Poly operator*(Poly poly){
    Poly temp;
    map<int, int> :: reverse_iterator ri;
    map<int, int> :: reverse_iterator ir;
    for(ri =p.rbegin(); ri != p.rend(); ri++){
        for(ir = poly.p.rbegin(); ir != poly.p.rend(); ir++){
            int d = ri->first + ir->first;
            int c = ri->second * ir->second;
            temp.p[d]+=c;
            if(temp.p[d]== 0)
            temp.p.erase(d);
        }
    }
    return temp;

}

 friend ostream& operator<<(ostream &, Poly);

};

  ostream& operator<<(ostream &os, Poly poly){
  map<int, int>::reverse_iterator ri;
  bool flag = false;
  for(ri = poly.p.rbegin(); ri != poly.p.rend(); ri++ ){


      os<<" "<<(*ri).second<<" "<<(*ri).first;
      flag = true;
  }
  if(!flag)
  os<<" 0 0";



  return os;
 }
int main()
{
    ifstream f("input-polynomials.txt");
    ofstream of("expectedoutput.txt");
    if(f){
        while(!f.eof()){
            string line;
            getline(f, line);
            Poly p(line);
            getline(f, line);
            Poly c(line);
            cout<<"original 1: "<<p.getString() <<endl;
            of<<"original 1: "<<p.getString()<<endl;


            cout<<"original 2: "<<c.getString()<<endl;
            of<<"original 2: "<<c.getString()<<endl;
            cout<<"canonical 1:"<<p<<endl;
            of<<"canonical 1:"<<p<<endl;
            cout<<"canonical 2:"<<c<<endl;
            of<<"canonical 2:"<<c<<endl;
            cout<<"sum:"<<p+c<<endl;
            of<<"sum:"<<p+c<<endl;
            cout<<"difference:"<<p-c<<endl;
            of<<"difference:"<<p-c<<endl;
            cout<<"product:"<<p*c<<endl;
            of<<"product:"<<p*c<<endl;
            of<<endl;
            cout<<endl;
        }
    }

    return 0;
}

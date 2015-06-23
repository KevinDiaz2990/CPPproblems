#include <iostream>
#include<cstdlib>
#include<map>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;



class InvIndex{
   private:

   map< string, map<int, int> > index;

   public:
   InvIndex(){

   }

   void insert(string s, int l){

      index[s][l]+=1;
   }

friend ostream& operator<<(ostream &, InvIndex);


};
ostream& operator<<(ostream &os, InvIndex in){
    map<string, map<int, int> > temp = in.index;

    map<string, map<int,int> >::iterator p;
    map<int, int>::iterator r;
    for(p = temp.begin(); p != temp.end(); p++){
        os<<(*p).first<<": ";
        for(r = p->second.begin();r !=p->second.end() ; r++){
            if((*r).second > 1 && r == p->second.begin()){
                os<<(*r).first<<"("<<(*r).second<<")";
            }
            else if((*r).second ==1 && r==p->second.begin() ){
                os<<(*r).first;
            }

           else if((*r).second > 1 && r != p->second.begin()){
             os<<", "<<(*r).first<<"("<<(*r).second<<")";
            }
           else
           os<<", "<<(*r).first;

        }
        os<<endl;
    }

    return os;

}


int main()
{
    InvIndex in;
    int count = 1;
    ifstream f("inputP.txt");
    ofstream of("expected-permutations.txt");
    if(f){
        while(!f.eof()){
            string line;
            getline(f, line);
            istringstream iss(line);
            string s;
            while(iss>>s)
            in.insert(s, count);
            ++count;



        }
      f.close();
    }
    else cout<<"unable to open file"<<endl;


   cout<<in;



    return 0;
}

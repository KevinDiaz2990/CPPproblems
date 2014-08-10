#include <iostream>
#include<string>
#include <sstream>
#include<fstream>



struct FirstLL;
class Inv;




struct FirstLL{
 std::string word;
  FirstLL *next;
  int line;
  int count;

    FirstLL(){
      next = 0;
      count = 0;
      line = 0;
      }



};

class Inv{
private:
FirstLL *head;

public:
  Inv(){
  head = new FirstLL();

}


void insert(std::string s="", int l =1){
     FirstLL *temp= new FirstLL();
     temp->word = s;
     temp->line = l;
     FirstLL *current = head;


}
friend std::ostream& operator <<(std:: ostream &, Inv);
    
};




int main(){
std::ifstream f("inputP.txt");
std::ofstream of("output.txt");
Inv in;
 int count = 0;
 if(f){
 while(! f.eof()){
  std:: string line;
  getline(f, line);
std::  istringstream iss(line);
std::  string s;
  while(iss>>s)
  in.insert(s, ++count);



}

}

else
  std:: cout<<"Unable to open file" <<std::endl;

return 0;





}

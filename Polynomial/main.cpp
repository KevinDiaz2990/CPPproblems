#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
#include<sstream>
using namespace std;



class Poly;
struct LL;

struct LL{//struct that is used for the Linked List
    int degree;
    int coeff;

    LL *next;


};



class Poly{
    private:

    LL *head;
    string str;
    public:

    Poly(){ //default constructor
        head = new LL;
        head ->coeff = 0;
        head ->degree = 0;
        head ->next = 0;


    }

    Poly(string s){ //One parameter that takes one string variable

        head = new LL;
        head->coeff=0;
        head ->degree = 0;
        head ->next = 0;

        str = s;

        istringstream iss(str);
        int i;
        int j ;
        while(iss>>i>>j){
            insert(i, j);

        }


    }
    Poly (const Poly &p){
        head = new LL();
        LL *copy = p.head;
        copy = copy->next;
        while(copy){
            insert(copy->coeff, copy->degree);
            copy = copy->next;
        }



    }
   ~Poly(){ // destructor for each node


       LL *cur = head;
       LL *node;
       while(cur){
           node = cur->next;
         //  cout<<"This node is being deleted" << cur->coeff<<endl; 
           delete cur;
           cur =node;
       }

   }

  void insert(int c, int d){
         LL *temp = new LL;
         temp->coeff = c;
         temp->degree = d;
         temp->next = NULL;
         LL *current = head;
         if(!current->next){
             current->next = temp;
         }
       else{
           while(current->next){

             if(1){
                 LL *temp1 = current->next;
                 bool flag = 1;
                 while(temp1){
                    if(temp1 ->degree == temp->degree){
                        temp1->coeff = temp1->coeff + temp->coeff;
                        flag = 0;
                        break;
                    }
                    else temp1 = temp1->next;

                 }
                 if(!flag)
                   break;
             }
            if(current->next->degree < temp->degree){
                temp->next = current->next;
                current->next = temp;
                break;
            }
            else{
                current = current -> next;
                if(!current->next){
                    current->next = temp;
                    break;
                }
            }
       }
       }



  }

  string getString(){ //To get the original form of the polynomial
    return str;

  }

  Poly &operator=(const Poly &p){ //not good
      if(this == &p)return *this;
      LL *node;
      LL *current = head;
      while(current){
          node = current->next;
          delete current;
          current = node;

      }

     head = new LL;
     head ->coeff = 0;
     head->degree = 0;
     current = p.head->next;
     while(current){
         insert(current->coeff, current->degree);
         current = current->next;
     }

   return *this;
  }

  Poly operator+(Poly p){ //overload addition operator
      Poly temp;
      LL *cur = head->next;
      LL *curP = p.head;
      curP = curP->next;
      while(cur){
        int c = cur->coeff;
        int d = cur->degree;
        temp.insert(c, d);
        cur = cur->next;
       }
       while(curP){
           int c = curP->coeff;
           int d = curP->degree;
           temp.insert(c, d);
           curP = curP ->next;

       }

    return temp;
}

Poly operator-(Poly p){ //overloaded sub operator. Functions like the Addition operator
      Poly temp;
      LL *cur = head->next;
      LL *curP = p.head;
      curP = curP->next;
      while(cur){
        int c = cur->coeff;
        int d = cur->degree;
        temp.insert(c, d);
        cur = cur->next;

       }
       while(curP){
           int c = curP->coeff;
           int d = curP->degree;
           temp.insert(-c, d);
           curP = curP ->next;

       }


    return temp;

}
 Poly operator*(Poly p){
     Poly temp;
     LL *ref = head->next;
     LL *refp = p.head->next;
     while(ref){

         while(refp){
             int c = ref->coeff * refp->coeff;
             int d = ref->degree + refp->degree;
             temp.insert(c, d);
             refp = refp->next;
         }
         ref = ref->next;
         refp = p.head->next;
     }

return temp;


 }



 friend ostream& operator<<(ostream& os, Poly p);


};

ostream& operator<<(ostream& os, Poly p){
    LL *current = p.head;
    current = current->next;
    bool flag = 1;
    while(current){
      if(current->coeff == 0){
          current = current->next;
      }
      else{
          os<<current->coeff<<" ";
          os<<current->degree<<" ";
          current = current->next;
          flag =0;
      }

    }
    if(flag){
        os<<"0 0";
    }



   return os;
}



int main()

{
 ifstream f("input-polynomials.txt");

  ofstream of("Expectedoutput.txt");
  if(f){


  while(!f.eof()){


      string line;
      getline(f, line);
      Poly p(line);
      getline(f, line);
      Poly c(line);
      cout<<"Original 1: "<<p.getString()<<endl;
      of<<"original 1: "<<p.getString()<<endl;
      cout<<"Original 2: "<<c.getString()<<endl;
      of<<"original 2: "<<c.getString()<<endl;
      cout<<"Canonical 1: "<<p<<endl;
      of<<"canonical 1: "<<p<<endl;
      cout<<"Canonical 2: "<<c<<endl;
      of<<"canonical 2: "<<c<<endl;
      cout<<"Addition: "<<p+c<<endl;
      of<<"sum: "<<p+c<<endl;
      cout<<"Subtraction: "<<p-c<<endl;
      of<<"difference: "<<p-c<<endl;
      cout<<"Multiplication: "<<p*c<<endl;
      of<<"product: "<<p*c<<endl;
      cout<<endl;

      of<<endl;
      }

  f.close();
  of.close();
  }
else cout<<"unable to open file"<<endl;




}

#include <iostream>
#include <cstdlib>
#include<cassert>
#include<cmath>


using namespace std;


template<class T> class SA;
template<class T>
ostream& operator<<(ostream& os, SA<T> s);
template<class T> class SM;
template<class T>
ostream& operator<<(ostream& os, SM<T> sm);
template<class T>
class SA{
   private:
   int high, low;
   T* p;
   public:

   SA(){
       low =0;
       high =-1;
       p=NULL;
   }
   SA(int l, int h){
       if((h-l+1)<=0){
           cout<<"constructor out of bounds error"<<endl;
           exit(1);
       }
       low =l;
       high =h;
       p = new T[h-l+1];

   }
   SA(int i){
       low =0;
       high = i-1;
       p = new T[i];
   }

   SA(const SA<T> & s){
       int size = s.high - s.low +1;
       p = new T[size];
       for(int i=0; i<size; i++){
           p[i] = s.p[i];
       }
       low = s.low;
       high = s.high;
   }

    ~SA(){
     delete []p;
    }

    T& operator[](int i){
        if(i<low || i>high){
            cout<<"index "<<i<<" out of range."<<endl;
            exit(1);
        }
        return p[i-low];
    }

    SA & operator=(const SA & s){
if(this==&s)return *this;
delete [] p;
int size=s.high-s.low+1;
p=new T[size];
for(int i=0; i<size; i++)
p[i]=s.p[i];
low=s.low;
high=s.high;
return *this;
}



friend ostream& operator<< <>(ostream& os, SA<T> s);

};

template <class T>
ostream& operator<<(ostream& os, SA<T> s){
    int size = s.high - s.low +1;
    for(int i = 0; i<size; i++)
    cout<<s.p[i]<<" ";

     cout<<endl;

    return os;

}

template <class T>
class SM{
    private:
    SA < SA <T> > internal;
    int RowsMin;
    int ColumnsMin;
    int RowsMax;
    int ColumnsMax;
    friend class SA<T>;

    public:
    SM(int square_size): internal(square_size){
        if(square_size<=0){
            cout<<"Constructor out of bounds error"<<endl;
            exit(1);
        }

        for(int i = 0; i<square_size; i++){
            internal[i] = SA<T>(square_size);
        }
       RowsMin = 0;
        ColumnsMin=0;
        RowsMax=square_size-1;
        ColumnsMax=square_size-1;
    }
    SM(int rows, int cols):internal(rows){
        if(rows<=0 || cols <=0){
            cout<<"Constructor out of bounds error"<<endl;
            exit(1);
        }


        for(int i = 0; i<rows; i++){
            internal[i] = SA<T>(cols);
        }
        RowsMin=0;
        RowsMax= rows -1;
        ColumnsMin= 0;
        ColumnsMax=cols -1;
    }
    SM(int rmin, int rmax, int cmin, int cmax):internal(rmin, rmax){



        for(int i = rmin; i< rmax + 1; i++){
            internal[i] = SA<T> (cmin, cmax);

        }

        RowsMin = rmin;
        RowsMax= rmax;
        ColumnsMin = cmin;
        ColumnsMax= cmax;
    }


     SA<T>& operator[](int i){
        if(i<RowsMin || i>RowsMax){
            cout<<"Index " << i << " out of bounds";
            exit(1);
        }

        return internal[i];


     }




     //matrix multiplication
    SM operator*(SM<T> sm){
        if((ColumnsMin != sm.RowsMin) || (ColumnsMax != sm.RowsMax)){
            cout<<"These two matrices can't be multiplied "<<endl;
            exit(1);
                  }
           SM<T> temp(RowsMin, RowsMax, sm.ColumnsMin, sm.ColumnsMax) ;
            for(int i= RowsMin; i<=RowsMax; i++){
              for(int j =sm.ColumnsMin; j<=sm.ColumnsMax ; j++ ){
                   temp.internal[i][j] = 0;
                 for(int k = sm.RowsMin; k<=sm.RowsMax ; k++){
                     temp.internal[i][j] += internal[i][k] * sm.internal[k][j];

                 }
              }
            }


      return temp;
    }

    ~SM(){

    }

   friend ostream& operator<< <>(ostream& os, SM<T> sm);





};
template<class T>
  ostream& operator<<(ostream& os, SM<T> sm){
      for(int i = sm.RowsMin; i<=sm.RowsMax ; i++)
              cout<<sm.internal[i];



      return os;
  }

int main()
{
 SA<int> safearray1(5); //Templatized SafeArray using int
 SA<float> safearray2(5); //Templatized SafeArray using float
 SA<int> a(3, 5); //Templatized SafeArray showing the boundaries

 float fl = 1.1;
 for(int i = 0; i<5; i++){
     safearray1[i] = i;
     safearray2[i] = fl++;
 }
 cout<<"Int SafeArray: "<<endl;
 cout<< safearray1;
 cout<<"Float SafeArray: "<<endl;
 cout<<safearray2;

 for(int i = 3; i<= 5; i++)
      a[i]= i;
  cout<<"Two parameter int SafeArray: "<<endl;
  cout<<a;

SM<int> b(5);  //  SafeMatrix templatized using int
for(int i = 0; i< 5; i++)
   for(int j = 0; j< 5 ; j++)
         b[i][j] =j;

 cout<<"Int SafeMatrix: "<<endl;
 cout<<b;

 SM<float> c(5); //SafeMatrix using float
   for(int i = 0; i<5; i++){
       for(int j = 0; j<5; j++){
           c[i][j] = fl++;
       }
   }
 cout<<"Float SafeMatrix: "<<endl;
 cout<<c;
 SM<int> d(3 , 5); // SafeMatrix two parameters
  for(int i=0; i<3; i++)
     for(int j =0; j<5; j++)
           d[i][j] =j;
  cout<<"Two Parameter SafeMatrix: "<<endl;
  cout<<"============="<<endl;
  cout<<d;

 SM<int> e(10, 20, 10, 20); //SafeMatrix four parameters
   for(int i =10; i<=20; i++){
       for(int j = 10; j<=20; j++){
           e[i][j] = j;
       }
   }
cout<<"Four Parameter SafeMatrix: "<<endl;
cout<<"============="<<endl;
cout<<e;

 cout<<"Matrix Mutliplication SafeMatrix d * b: "<<endl;
 cout<<"============="<<endl;
 cout<<d*b;//Matrix Multiplication between SafeMatrix d and b;
 cout<< b*d;  //Matrix Multiplication that will terminate the program



    return 0;
}

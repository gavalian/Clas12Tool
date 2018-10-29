#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

class hist {
  public:
    hist( int, float, float);
    void fill( float );
    void show();
    void write( ofstream &);
    
  private:
    vector<int> bins;
    float min;
    float max;
};

hist::hist( int nbins, float x, float y){
  bins.reserve( nbins );
  for( int i=0;i<nbins;i++) bins.push_back(0);
  min = x;
  max = y;
}

void hist::fill( float x){
  if( x < min || x > max ) return;
  
  int i = floor( (x-min)/(max-min)*bins.size() );
  bins[i]++;
}

void hist::show(){
  float w = (max-min)/bins.size();
  cout << min << endl;
  for( int i=0; i<bins.size();i++){
    for( int j=0;j<bins[i];j++) cout << "#";
    cout << endl ;//<< min + (i+1)*w << endl;
  }  
  cout << max << endl;
}

void hist::write( ofstream &out ){
  float w=(max-min)/bins.size();
  for( int i=0; i<bins.size();i++){
    out << min + i*w << ",";
  }
  out << max << endl;
  for( int i=0; i<bins.size()-1;i++)
    out << bins[i] <<",";
  out <<bins[bins.size()-1] << endl;
}

//int main(){

  //srand(10);
  //hist H( 10, 5., 10.);
  //for( int i=0; i<1000; i++){
    //float r = ((float) rand() / (RAND_MAX)) ;
    //float a = 10*r+0 ;
    //H.fill(a);
  //}
  //H.show();

  //ofstream of("of.txt",ios::out);
  //H.write(of);
  //of.close();
//}


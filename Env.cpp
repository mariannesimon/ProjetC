
#include "Env.hpp"

//===================================================================
//                   Constructors & Destructor
//===================================================================

Env::Env(int w, int h, double d, int a_init){
  w_ = w;
  h_ = h;
  d_ = d;
  map_a.resize(w_*h_);
  map_b.resize(w_*h_);
  map_c.resize(w_*h_);
  a_init_ = a_init;
  for ( int i = 0; i < w_*h_; i++ )
  {
    map_a[i] = a_init;
    map_b[i] = 0;
    map_c[i] = 0;
  }
}

Env::~Env(){
}

//===================================================================
//                          Methods
//===================================================================

double Env::cell_diff(const std::vector<double>& map, int x, int y)
{
  double new_c = map[x*h_+y];
  for (int i = -1; i <= 1; i++){
    for (int j = -1; j <= 1; j++){
      new_c = new_c + d_*map[((x+i+w_)%w_)*h_+(y+j+h_)%h_];
    }
  }
  new_c = new_c - 9*d_*map[x*h_+y];
  return new_c;
}

void Env::diff()
{
  std::vector<double> tmp_a(w_*h_);
  std::vector<double> tmp_b(w_*h_);
  std::vector<double> tmp_c(w_*h_);
  for ( int i = 0; i < w_*h_; i++ )
  {
    tmp_a[i] = map_a[i];
    tmp_b[i] = map_b[i];
    tmp_c[i] = map_c[i];
  }
  for ( int x = 0; x < w_; x++ )
  {
    for ( int y = 0; y < h_; y++ )
    {
      double a = cell_diff(tmp_a, x, y);
      double b = cell_diff(tmp_b, x, y);
      double c = cell_diff(tmp_c, x, y);
      map_a[x*h_+y] = a;
      map_b[x*h_+y] = b;
      map_c[x*h_+y] = c;
    }
  }
}

//===================================================================
//                          Setters
//===================================================================

void Env::reinitialize()
{
  for ( int i = 0; i < w_*h_; i++ )
  {
    map_a[i] = a_init_;
    map_b[i] = 0;
    map_c[i] = 0;
  }
}

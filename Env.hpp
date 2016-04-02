/*
 Classe contenant l'environnement
 Attributs : tableaux des concentrations a, b ou c 
*/

#ifndef Env_hpp
#define Env_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

class Env{
public:
//===================================================================
//                   Constructors & Destructor
//===================================================================
  Env();
  Env(int w, int h, double d, int a_init);
  ~Env();
//===================================================================
//                          Getters
//===================================================================
  inline int w() const;
  inline int h() const;
  inline double a_out (int x, int y) const;
  inline double b_out (int x, int y) const;
  inline double c_out (int x, int y) const;
//===================================================================
//                          Setters
//===================================================================
  inline void set_ca (int x, int y, double newc);
  inline void set_cb (int x, int y, double newc);
  inline void set_cc (int x, int y, double newc);
  inline void set_a_init(int n_a_init);
  void reinitialize ();
//===================================================================
//                          Methods
//===================================================================
  double cell_diff(const std::vector<double>& map, int x, int y);
  void diff();
protected:
//===================================================================
//                          Attributes
//===================================================================
  int w_;
  int h_;
  double d_;
  int a_init_;
  std::vector<double> map_a;
  std::vector<double> map_b;
  std::vector<double> map_c;
};

//===================================================================
//                          Inline declarations
//===================================================================

inline void Env::set_a_init(int n_a_init){
  a_init_ = n_a_init;
}

inline int Env::w() const{
  return w_;
}

inline int Env::h() const{
  return h_;
}

inline double Env::a_out(int x, int y) const{
  return map_a[x*h_+y];
}

inline double Env::b_out(int x, int y) const{
  return map_b[x*h_+y];
}

inline double Env::c_out(int x, int y) const{
  return map_c[x*h_+y];
}

inline void Env::set_ca(int x, int y, double newc){
  map_a[x*h_+y] = newc;
}

inline void Env::set_cb(int x, int y, double newc){
  map_b[x*h_+y] = newc;
}

inline void Env::set_cc(int x, int y, double newc){
  map_c[x*h_+y] = newc;
}

#endif /* Env_hpp */

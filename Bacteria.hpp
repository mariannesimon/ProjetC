/*
 Classe Bacteria
 Attributs : position, état
 Méthodes : getters, setters, métabolisme, division, mutation
*/

#ifndef Bacteria_hpp
#define Bacteria_hpp

#include <stdio.h>

#include "Env.hpp"

class Bacteria{
public:
//===================================================================
//                Constructors & destructor
//===================================================================
  Bacteria();
  Bacteria(int x, int y, int gen, double fmin, double pmut);
  Bacteria(const Bacteria& bact);
  ~Bacteria();
//===================================================================
//                          Getters
//===================================================================
  inline int x() const;
  inline int y() const;
  inline int gen() const;
  inline double fitness() const;
  inline double fmin() const;
  inline double pmut() const;
  inline double a() const;
  inline double b() const;
  inline double c() const;
  inline bool alive() const;
  inline bool mutated() const;
  inline bool divided() const;
  bool will_die() const;
  bool will_divide() const;
//===================================================================
//                          Setters
//===================================================================
  void reinitialize();
  void to_die();
  void to_divide();
  void set_fitness();
//===================================================================
//                          Methods
//===================================================================
  void replace(const Bacteria& bact);
  void dead(Env& env);
  void mutate();
  void divide();
  void met_a(Env& env, double Raa, double Rab);
  void met_b(Env& env, double Rbb, double Rbc);
  void metabolize(Env& env, double Raa, double Rab, double Rbb, double Rbc);
  
protected:
//===================================================================
//                          Attributes
//===================================================================
  int x_;
  int y_;
  int gen_;
  double fmin_;
  double pmut_;
  double fitness_;
  double a_;
  double b_;
  double c_;
  bool alive_;
  bool mutated_;
  bool divided_;
  bool to_die_;
  bool to_divide_;
};

//===================================================================
//                          Inline methods
//===================================================================

inline int Bacteria::x() const{
  return x_;
}
inline int Bacteria::y() const{
  return y_;
}
inline int Bacteria::gen() const{
  return gen_;
}
inline double Bacteria::fitness() const{
  return fitness_;
}
inline double Bacteria::fmin() const{
  return fmin_;
}
inline double Bacteria::pmut() const{
  return pmut_;
}
inline double Bacteria::a() const{
  return a_;
}
inline double Bacteria::b() const{
  return b_;
}
inline double Bacteria::c() const{
  return c_;
}
inline bool Bacteria::alive() const{
  return alive_;
}
inline bool Bacteria::mutated() const{
  return mutated_;
}
inline bool Bacteria::divided() const{
  return divided_;
}
#endif /* Bacteria_hpp */

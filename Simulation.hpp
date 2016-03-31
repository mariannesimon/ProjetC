/* 
 Classe permettant la simulation
 Attributs environnement et population
*/

#ifndef Simulation_hpp
#define Simulation_hpp

#include <stdio.h>
#include <string.h>

#include "Env.hpp"
#include "Population.hpp"


class Simulation{
public:
  //===================================================================
  //                   Constructors & Destructor
  //===================================================================
  Simulation(int tsim, int T, int w, int h, double d, int a_init,
             double pmut, double pdeath, double fmin,
             double Raa, double Rab, double Rbb, double Rbc);
  ~Simulation();
  //===================================================================
  //                          Methods
  //===================================================================
  void run();
  void save(std::string fname);
  //===================================================================
  //                          Getters
  //===================================================================
  int gen_a();
  int gen_b();
  //===================================================================
  //                          Setters
  //===================================================================
protected:
  //===================================================================
  //                          Attributes
  //===================================================================
  int tsim_;
  int T_;
  double Raa_;
  double Rab_;
  double Rbb_;
  double Rbc_;
  int a_init_;
  Env env_;
  Population pop_;
};


#endif /* Simulation_hpp */

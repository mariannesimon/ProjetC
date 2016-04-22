/*
 Classe Population
 Attribut : vecteur de bactéries
 Methodes : divisions, mort, mutations, sélections, métabolisme,
 représentation graphique
*/

#ifndef Population_hpp
#define Population_hpp

#include <stdio.h>
#include <time.h>
#include <string.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "Bacteria.hpp"
#include "Env.hpp"

class Population{
public:
//===================================================================
//                   Constructors & Destructor
//===================================================================
  Population(int w, int h, double pmut, double pdeath, double fmin);
  ~Population();
//===================================================================
//                          Methods
//===================================================================
  int moore_fitness(int x, int y);
  bool is_out(int x, int y);
  void fill_gaps();
  void death_select();
  void death(Env& env);
  void metabolism(Env& env, double Raa, double Rab, double Rbb, double Rbc);
  void save(std::string fname);
//===================================================================
//                          Getters
//===================================================================
  inline Bacteria get_bact(int x, int y) const;
  inline int dead() const;
  inline int doomed() const;
  inline int gen_a() const;
  inline int gen_b() const;
//===================================================================
//                          Setters
//===================================================================
  void reinitialize();
  inline void gen();
  
protected:
//===================================================================
//                          Attributes
//===================================================================
  std::vector<Bacteria> pop_;
  double pmut_;
  double pdeath_;
  int bact;
  int w_;
  int h_;
  unsigned char* img_;
  int gen_a_;
  int gen_b_;
};

inline Bacteria Population::get_bact(int x, int y) const
{
  for (int i=0; i<bact; i++)
  {
    if (pop_[i].x()==x && pop_[i].y()==y)
    {
      return pop_[i];
    }
  }
  return pop_[bact];
}

inline int Population::dead() const
{
  int dead = 0;
  for (int i=0; i<bact; i++)
  {
    if (!pop_[i].alive())
    {
      dead++;
    }
  }
  return dead;
}

inline int Population::doomed() const
{
  int doomed = 0;
  for (int i = 0; i<bact; i++)
  {
    if (pop_[i].will_die())
    {
      doomed++;
    }
  }
  return doomed;
}

inline void Population::gen() {
  gen_a_ = 0;
  gen_b_ = 0;
  for (int i = 0; i < bact; i++)
  {
    if (pop_[i].alive())
    {
      if (pop_[i].gen() == 0) gen_a_ += 1;
      else gen_b_ += 1;
    }
  }
}

inline int Population::gen_a() const
{
  return gen_a_;
}

inline int Population::gen_b() const
{
  return gen_b_;
}

#endif /* Population_hpp */

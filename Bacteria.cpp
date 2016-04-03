
#include "Bacteria.hpp"

//===================================================================
//                Constructors & destructor
//===================================================================

/* Constructeur */
Bacteria::Bacteria(int x, int y, int gen, double fmin, double pmut){
  x_ = x;
  y_ = y;
  gen_ = gen;
  a_ = 0;
  b_ = 0;
  c_ = 0;
  fmin_ = fmin;
  pmut_ = pmut;
  fitness_ = 0;
  alive_ = true;
  mutated_ = false;
  divided_ = false;
  to_die_ = false;
  to_divide_ = false;
}

/* Constructeur par copie */
Bacteria::Bacteria(const Bacteria& bact){
  x_ = bact.x();
  y_ = bact.y();
  gen_ = bact.gen();
  a_ = bact.a();
  b_ = bact.b();
  c_ = bact.c();
  fmin_ = bact.fmin();
  pmut_ = bact.pmut();
  fitness_ = bact.fitness();
  alive_ = bact.alive();
  mutated_ = false;
  divided_ = true;
  to_die_ = false;
  to_divide_ = false;
}

/* Destructeur */
Bacteria::~Bacteria(){
}

//===================================================================
//                          Methods
//===================================================================

/* replace : remplace une bactérie morte par une autre au moment
 de la division */
void Bacteria::replace(const Bacteria& bact)
{
  gen_ = bact.gen();
  a_ = bact.a();
  b_ = bact.b();
  c_ = bact.c();
  fitness_ = bact.fitness();
  alive_ = true;
  to_die_ = false;
  divided_ = true;
  to_divide_ = false;
}

/* dead : mort de la bactérie */
void Bacteria::dead(Env& env)
{
  alive_ = false;
  to_die_ = false;
  env.set_ca(x_, y_, env.a_out(x_, y_) + a_);
  env.set_cb(x_, y_, env.b_out(x_, y_) + b_);
  env.set_cc(x_, y_, env.c_out(x_, y_) + c_);
}

/* mutate : mutation aléatoire */
void Bacteria::mutate()
{
  if ( alive_ && divided_ )
  {
    double p = (double)rand() / (double)RAND_MAX;
    if (p < pmut_)
    {
      if (gen_ == 0) gen_ = 1;
      else gen_ = 0;
      mutated_ = true;
    }
  }
}

/* divide : division des concentrations de la cellule mère */
void Bacteria::divide()
{
  a_ = a_/2;
  b_ = b_/2;
  c_ = c_/2;
  to_divide_ = false;
  divided_ = true;
  set_fitness();
}

/* met_a : réseau métabolique pour les individus de génotype Ga */
void Bacteria::met_a(Env& env, double Raa, double Rab)
{
  double a_out = env.a_out(x_, y_);
  double dt = 0.1;
  for (int i = 0; i < 10; i++)
  {
    double na_out = a_out + dt*(-a_out*Raa);
    double na = a_ + dt*(a_out*Raa - a_*Rab);
    double nb = b_ + dt*(a_*Rab);
    a_out = na_out;
    a_ = na;
    b_ = nb;
  }
  env.set_ca(x_, y_, a_out);
}

/* met_b : réseau métabolique pour les individus de génotype Gb */
void Bacteria::met_b(Env& env, double Rbb, double Rbc)
{
  double b_out = env.b_out(x_, y_);
  double dt = 0.1;
  for (int i = 0; i < 10; i++)
  {
    double nb_out = b_out + dt*(-b_out*Rbb);
    double nb = b_ + dt*(b_out*Rbb - b_*Rbc);
    double nc = c_ +  dt*(b_*Rbc);
    b_out = nb_out;
    b_ = nb;
    c_ = nc;
  }
  env.set_cb(x_, y_, b_out);
}

/* metabolize : mise en place du réseau métabolique */
void Bacteria::metabolize(Env& env,
                          double Raa, double Rab, double Rbb, double Rbc)
{
  if ( alive_ )
  {
    if ( gen_==0 ) met_a(env, Raa, Rab);
    else met_b(env, Rbb, Rbc);
    set_fitness();
  }
}

//===================================================================
//                          Setters
//===================================================================

/* reinitialize : à chaque pas de temps, réinitialise le statut de la
 bactéries sauf si elle est morte */
void Bacteria::reinitialize()
{
  mutated_ = false;
  divided_ = false;
  to_divide_ = false;
  to_die_ = false;
}

/* set_fitness : modification de la fitness en fonction du génotype */
void Bacteria::set_fitness()
{
  if (gen_ == 0) fitness_ = b_;
  else fitness_ = c_;
  if (fitness_ < fmin_) fitness_ = 0;
}

/* to_die : bactérie sélectionnée pour la mort */
void Bacteria::to_die()
{
  to_die_ = true;
}

/* to_divide : bactérie sélectionnée pour être la cellule mère 
 d'une division */
void Bacteria::to_divide()
{
  to_divide_ = true;
}

//===================================================================
//                          Getters
//===================================================================

bool Bacteria::will_die() const
{
  return to_die_;
}

bool Bacteria::will_divide() const
{
  return to_divide_;
}


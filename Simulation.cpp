
#include "Simulation.hpp"

//===================================================================
//                   Constructors & Destructor
//===================================================================

/* Constructeur */
Simulation::Simulation(int tsim, int T, int w, int h,
                       double d, int a_init,
                       double pmut, double pdeath, double fmin,
                       double Raa, double Rab, double Rbb, double Rbc) :
tsim_(tsim), T_(T), Raa_(Raa), Rab_(Rab), Rbb_(Rbb), Rbc_(Rbc), 
a_init_(a_init), env_(w, h, d, a_init), pop_(w, h, pmut, pdeath, fmin)
{}

/* Destructeur */
Simulation::~Simulation() {}

//===================================================================
//                          Methods
//===================================================================

/* run : lancement de la simulation */
void Simulation::run()
{
  for (int i = 0; i < tsim_; i++)
  {
    std::cout << "Itération : " << i << "\n";
	  if (i%T_ == 0) env_.reinitialize();
    pop_.reinitialize();
    env_.diff();
    pop_.death_select();
    pop_.division();
    pop_.death(env_);
    pop_.metabolism(env_,Raa_,Rab_,Rbb_,Rbc_);
  }
}

/* save : enregistrer l'image associée à la population */
void Simulation::save(std::string fname)
{
  pop_.save(fname);
}

//===================================================================
//                          Getters
//===================================================================

/* gen_a : compte le nombre de bactéries de chaque génotype
 et renvoie le nombre de bactéries Ga */
int Simulation::gen_a()
{
  pop_.gen();
  return pop_.gen_a();
}

/* gen_b : renvoie le nombre de bactéries Gb */
int Simulation::gen_b()
{
  return pop_.gen_b();
}

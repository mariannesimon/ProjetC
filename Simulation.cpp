
#include "Simulation.hpp"

//===================================================================
//                   Constructors & Destructor
//===================================================================

Simulation::Simulation(int tsim, int T, int w, int h,
                       double d, int a_init,
                       double pmut, double pdeath, double fmin,
                       double Raa, double Rab, double Rbb, double Rbc) :
tsim_(tsim), T_(T), Raa_(Raa), Rab_(Rab), Rbb_(Rbb), Rbc_(Rbc), 
a_init_(a_init), env_(w, h, d, a_init), pop_(w, h, pmut, pdeath, fmin)
{}

Simulation::~Simulation() {}

//===================================================================
//                          Methods
//===================================================================

void Simulation::run()
{
  for ( int i = 0; i < tsim_; i++ )
  {
	  if ( i%T_ == 0 )
    {
      env_.reinitialize();
    }
    pop_.reinitialize();
    env_.diff();
    pop_.death_select();
    pop_.division();
    pop_.death(env_);
    pop_.metabolism(env_,Raa_,Rab_,Rbb_,Rbc_);
//    std::cout << env_.a_out(5, 5) << " " << env_.b_out(5, 5) <<
//    " " << env_.c_out(5, 5) << "\n";
  }
}

void Simulation::save(std::string fname)
{
  pop_.save(fname);
}

//===================================================================
//                          Getters
//===================================================================

int Simulation::gen_a()
{
  pop_.gen();
  return pop_.gen_a();
}

int Simulation::gen_b()
{
  return pop_.gen_b();
}

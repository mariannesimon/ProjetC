//
//  main.cpp
//  ProjetC++
//
//  Created by Marianne Simon on 17/02/2016.
//  Copyright © 2016 Marianne Simon. All rights reserved.
//

#include "Bacteria.hpp"
#include "Env.hpp"
#include "Population.hpp"
#include "Simulation.hpp"


int main() {
  //======================================================================
  //                          Files
  //======================================================================
  
  //  std::string pname = "params.txt";
  std::string pname = "/Users/Marianne/Desktop/3BIM/ProjetC++/params.txt";
  std::string fname = "params1diff6.txt";
  std::ifstream params (pname.c_str(), std::ios::in);
  std::ofstream output (fname.c_str(), std::ios::out | std::ios::trunc);
  
  //======================================================================
  //                          Attributes
  //======================================================================
  
  double Raa, Rab, Rbb, Rbc, pmut, pdeath, d, fmin;
  int w, h, tsim;
  params >> Raa >> Rab >> Rbb >> Rbc >>
            pmut >> pdeath >> w >> h >> d >> fmin >> tsim;
  
  //======================================================================
  //                          Tests
  //======================================================================

//  int T = 25;
//  int a_init = 1;
//  Env env(w, h, d, a_init);
//  Bacteria bact(5, 5, 0, 0.01, 0);
//  bact.metabolize(env, Raa, Rab, Rbb, Rbc);
//  Population pop(w, h, pmut, pdeath, fmin);
//  pop.metabolism(env, Raa, Rab, Rbb, Rbc);
//  Simulation sim(tsim, T, w, h, d, a_init, pmut, pdeath, fmin, Raa, Rab, Rbb, Rbc);
//  sim.save("init.ppm");
//  sim.run();
//  sim.save("fin.ppm");
  
  //======================================================================
  //                          Simulation
  //======================================================================
 
   for (int T = 1; T <= 1500; T += 10)
   {
     for (int a_init = 0; a_init <= 50; a_init += 1)
     {
       Simulation sim(tsim, T, w, h, d, a_init, pmut, pdeath, fmin, Raa, Rab, Rbb, Rbc);
       sim.run();
       output << T << " " << a_init << " " << sim.gen_a() <<
         " " << sim.gen_b() << "\n";
       std::cout << T << "   " << a_init << "\n";
     }
   }
  return 0;
}

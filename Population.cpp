
#include "Population.hpp"

//===================================================================
//                   Constructors & Destructor
//===================================================================

/* Constructeur */
Population::Population(int w, int h, double pmut, double pdeath, double fmin)
{
  srand((unsigned int)time(NULL));
  bact = w*h;
  w_ = w;
  h_ = h;
  pop_.resize(bact);
  for (int x = 0; x<w_; x++)
  {
    for (int y = 0; y<h_; y++)
    {
      int gen = rand()&1;
      pop_[x*h_+y] = Bacteria(x,y,gen,fmin,pmut);
    }
  }
  pmut_ = pmut;
  pdeath_ = pdeath;
  img_ = new unsigned char[w*h*3];
}

/* Destructeur */
Population::~Population()
{
  delete[] img_;
}

//===================================================================
//                          Setters
//===================================================================

/* reinitialize : réinitialisation pour toutes les bactéries */
void Population::reinitialize()
{
  for (int i=0; i<bact; i++)
  {
    pop_[i].reinitialize();
  }
}

//===================================================================
//                          Methods
//===================================================================

/* death_select : sélection des bactéries qui devront mourir lors de
 la même itération */
void Population::death_select()
{
  for (int i = 0; i < bact; i++)
  {
	  if (pop_[i].alive())
    {
	    double p = (double)rand() / (double)RAND_MAX;
      if (p < pdeath_)
      {
        pop_[i].to_die();
      }
	  }
  }
}

/* death : mort des bactéries sélectionnées */
void Population::death(Env& env)
{
  for (int i = 0; i < bact; i++)
  {
    if (pop_[i].will_die()) pop_[i].dead(env);
  }
}

/* metabolism : métabolisation pour toutes les bactéries */
void Population::metabolism(Env& env, double Raa, double Rab, double Rbb, double Rbc)
{
  for (int i = 0; i < bact; i++)
  {
    pop_[i].metabolize(env, Raa, Rab, Rbb, Rbc);
  }
}

/* fill_gaps : trouve les gaps, sélectionne les gaps où la division
 est possible et les batéries associées à la division */
void Population::fill_gaps()
{
  std::vector<int> divide_list;
  std::vector<int> gaps_list;
  std::vector<Bacteria> dead_list;
  for (int i = 0; i<bact; i++)
  {
    if (!pop_[i].alive())
    {
      dead_list.push_back(pop_[i]);
    }
  }
  std::random_shuffle(dead_list.begin(), dead_list.end());
  for (int i = 0; i<int(dead_list.size()); i++)
  {
    int x = dead_list[i].x();
    int y = dead_list[i].y();
    int div_pos = moore_fitness(x, y);
    if ( div_pos != 2000 )
    {
      pop_[div_pos].to_divide();
      divide_list.push_back(div_pos);
      gaps_list.push_back(x*h_+y);
    }
  }
  for (int i = 0; i < int(gaps_list.size()); i++)
  {
    int fst = divide_list[i];
    int scd = gaps_list[i];
    pop_[fst].divide();
    pop_[scd].replace(pop_[fst]);
    pop_[fst].mutate();
    pop_[scd].mutate();
  }
}

/* moore_fitness : retourne la position de la bactérie ayant 
 la meilleure fitness dans le voisinage de  moore du gap */
int Population::moore_fitness(int x, int y)
{
  double fit_max = pop_[0].fmin();
  int pos_max = 2000;
  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if (!is_out(x + i, y + j)
          && pop_[(x+i)*h_+y+j].alive()
          && !pop_[(x+i)*h_+y+j].will_die()
          && !pop_[(x+i)*h_+y+j].will_divide())
      {
        int pos = (x + i)*h_ + y + j;
        double new_fit = pop_[pos].fitness();
        if ( new_fit >= fit_max )
        {
          fit_max = new_fit;
          pos_max = pos;
        }
      }
    }
  }
  return pos_max;
}

/* is_out : teste si la position est en dehors des cases */
bool Population::is_out(int x, int y)
{
  if (x>=w_ || x<0 || y>=h_ || y<0) return true;
  else return false;
}

/* save : enregistre l'image en ppm */
void Population::save(std::string fname)
{
  for (int x = 0; x<w_; x++)
  {
    for (int y = 0; y<h_; y++)
    {
      if (!pop_[x*h_+y].alive())
      {
        img_[ 3*(x*h_+y) ] = 10;
        img_[ 3*(x*h_+y) + 1 ] = 10;
        img_[ 3*(x*h_+y) + 2 ] = 10;
      } 
      else {
		    if (pop_[x*h_ + y].gen()==0) {
          img_[ 3*(x*h_ + y) ] = 154;
          img_[ 3*(x*h_ + y) + 1 ] = 205;
          img_[ 3*(x*h_ + y) + 2 ] = 50;
        } 
        else {
        img_[ 3*(x*h_ + y) ] = 210;
        img_[ 3*(x*h_ + y) + 1 ] = 105;
        img_[ 3*(x*h_ + y) + 2 ] = 30;
        }
      }
    }
  }
  std::ofstream file(fname.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
  file << "P6\n" << w_  << " " << h_ << "\n" << 255 << "\n";
  file.write((char*)img_, sizeof(unsigned char)*w_*h_*3);
  file.close();
}



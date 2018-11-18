#include "hist.h"

using namespace core;

hist::hist( std::string nn, std::string tt, int nb, float bmin, float bmax) : name(nn), title(tt), nbins(nb), min(bmin), max(bmax) {} 

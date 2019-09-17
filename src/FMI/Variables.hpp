#ifndef Variables_hh_INCLUDED
#define Variables_hh_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "../EnergyPlus/EnergyPlus.hh"

namespace EnergyPlus {
namespace FMI {

enum class VariableType { 
  T, 
  V, 
  AFLO, 
  MSENFAC, 
  QCONSEN_FLOW, 
  QGAIRAD_FLOW,
  QLAT_FLOW,
  QPEO_FLOW,
  TAVEINLET,
  TRAD,
  X,
  MINLETS_FLOW
};

using VariableAttribute = std::pair<std::string, std::string>;

struct Variable {
  VariableType type;
  std::string key; 
  Real64 value;
  std::vector<VariableAttribute> scalar_attributes;
  std::vector<VariableAttribute> real_attributes;
};

std::map<unsigned int, Variable> parseVariables(const std::string & idf);

}
}

#endif // Variables_hh_INCLUDED


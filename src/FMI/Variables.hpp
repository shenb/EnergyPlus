#ifndef Variables_hh_INCLUDED
#define Variables_hh_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "../EnergyPlus/EnergyPlus.hh"

namespace EnergyPlus {
namespace FMI {

enum class VariableType { INPUT, OUTPUT, PARAMETER };

struct Variable {
  std::string name() const;

  std::string causality() const;

  std::string varName;
  std::string zoneName;
  std::string description;
  std::string variability;
  std::string initial;
  std::string quantity;
  std::string unit;
  bool relativeQuantity;
  Real64 start;
  VariableType type;
  Real64 value;
};

std::map<unsigned int, Variable> parseVariables(const std::string & idf);

}
}

#endif // Variables_hh_INCLUDED


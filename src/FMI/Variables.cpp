#include "Variables.hpp"
#include "../EnergyPlus/InputProcessing/IdfParser.hh"
#include "../EnergyPlus/InputProcessing/EmbeddedEpJSONSchema.hh"
#include "../EnergyPlus/DataStringGlobals.hh"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

namespace EnergyPlus {
namespace FMI {

std::string Variable::name() const
{
  return zoneName + "_" + varName;
}

std::string Variable::causality() const
{
  std::string result;

  switch(type) {
    case VariableType::INPUT :
      result = "input";
      break;
    case VariableType::OUTPUT :
      result = "output";
      break;
    case VariableType::PARAMETER :
      result = "parameter";
      break;
  }

  return result;
}

std::vector<std::string> zoneNames(const std::string & idfPath) {
  std::vector<std::string> result;

  std::ifstream input_stream(idfPath, std::ifstream::in);

  std::string input_file;
  std::string line;
  while (std::getline(input_stream, line)) {
    input_file.append(line + EnergyPlus::DataStringGlobals::NL);
  }
  
  IdfParser parser;
  const auto embeddedEpJSONSchema = EnergyPlus::EmbeddedEpJSONSchema::embeddedEpJSONSchema();
  const auto schema = json::from_cbor(embeddedEpJSONSchema.first, embeddedEpJSONSchema.second);
  const auto jsonidf = parser.decode(input_file, schema);

  const auto zones = jsonidf["Zone"];
  for( const auto & zone : zones.items() ) {
    result.push_back(zone.key());
  }

  std::sort(result.begin(), result.end());

  return result;
}

std::map<unsigned int, Variable> parseVariables(const std::string & idf) {
  std::map<unsigned int, Variable> result;

  const auto zones = zoneNames(idf);

  unsigned int i = 0;
  for (const auto & zone : zones) {
    {
      Variable var;
      var.varName = "T";
      var.zoneName = zone;
      var.description = "Temperature of the zone air";
      var.variability = "continuous";
      //var.initial = "";
      var.quantity = "ThermodynamicTemperature";
      var.unit = "degC";
      var.relativeQuantity = false;
      var.start = 0.0;
      var.type = VariableType::INPUT;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "QConSen_flow";
      var.zoneName = zone;
      var.type = VariableType::OUTPUT;
      var.description = "Convective sensible heat added to the zone";
      var.variability = "discrete";
      var.initial = "calculated";
      var.quantity = "Power";
      var.unit = "W";
      var.relativeQuantity = false;
      //var.start = 0.0;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "AFlo";
      var.zoneName = zone;
      var.type = VariableType::PARAMETER;
      var.description = "Floor area";
      var.variability = "fixed";
      var.initial = "exact";
      var.quantity = "area";
      var.unit = "m2";
      var.relativeQuantity = false;
      var.start = 12.0;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "V";
      var.zoneName = zone;
      var.type = VariableType::PARAMETER;
      var.description = "Volume";
      var.variability = "fixed";
      var.initial = "exact";
      var.quantity = "volume";
      var.unit = "m3";
      var.relativeQuantity = false;
      var.start = 36.0;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "mSenFac";
      var.zoneName = zone;
      var.type = VariableType::PARAMETER;
      var.description = "Factor for scaling sensible thermal mass of volume";
      var.variability = "fixed";
      var.initial = "exact";
      //var.quantity = "volume";
      //var.unit = "m3";
      var.relativeQuantity = false;
      var.start = 1.0;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "AFlo";
      var.zoneName = zone;
      var.type = VariableType::OUTPUT;
      var.description = "Floor area";
      var.variability = "fixed";
      var.initial = "exact";
      var.quantity = "area";
      var.unit = "m2";
      var.relativeQuantity = false;
      var.start = 12.0;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "V";
      var.zoneName = zone;
      var.type = VariableType::OUTPUT;
      var.description = "Volume";
      var.variability = "fixed";
      var.initial = "exact";
      var.quantity = "volume";
      var.unit = "m3";
      var.relativeQuantity = false;
      var.start = 36.0;
      result.emplace(i,std::move(var));
    }
    ++i;
    {
      Variable var;
      var.varName = "mSenFac";
      var.zoneName = zone;
      var.type = VariableType::OUTPUT;
      var.description = "Factor for scaling sensible thermal mass of volume";
      var.variability = "fixed";
      var.initial = "exact";
      //var.quantity = "volume";
      //var.unit = "m3";
      var.relativeQuantity = false;
      var.start = 1.0;
      result.emplace(i,std::move(var));
    }
    ++i;
  }

  return result;
}

}
}


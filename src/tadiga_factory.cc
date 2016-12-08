// Copyright 2015 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_XMLParameterListHelpers.hpp>
#include <Teuchos_YamlParameterListCoreHelpers.hpp>
#include <Teuchos_YamlParser_decl.hpp>

#include "aprepro.h"

#include "tadiga_factory.h"

// *****************************************************************

tadiga::TadigaFactory::TadigaFactory() {}

Teuchos::RCP<tadiga::Tadiga> tadiga::TadigaFactory::create(
    const std::string input_file,
    const Teuchos::RCP<const Teuchos::Comm<int>>& comm,
    Teuchos::RCP<Geometry> input_tadiga_geometry) {
  // Set application parameters to default values
  Teuchos::RCP<Teuchos::ParameterList> tadiga_parameters =
      Teuchos::rcp(new Teuchos::ParameterList());

  SetTadigaParameterDefaults(tadiga_parameters.ptr());

  SEAMS::Aprepro aprepro;
  std::ifstream input_file_stream(input_file.c_str());

  // get results from aprepro's parsing
  aprepro.parse_stream(
      input_file_stream,
      input_file);  // TODO(johntfosterjr@gmail.com): Check return value (bool).

  // Update parameters with data from yaml string
  Teuchos::Ptr<Teuchos::ParameterList> tadiga_parameters_ptr(
      tadiga_parameters.get());
  Teuchos::updateParametersFromYamlCString(
      (aprepro.parsing_results().str()).c_str(), tadiga_parameters_ptr);

  // Create new Tadiga object
  return rcp(
      new tadiga::Tadiga(comm, tadiga_parameters, input_tadiga_geometry));
}

Teuchos::RCP<tadiga::Tadiga> tadiga::TadigaFactory::create(
    const std::string input_file,
    const Teuchos::RCP<const Teuchos::Comm<int>>& comm) {
  Teuchos::RCP<Geometry> null_geometry;
  return create(input_file, comm, null_geometry);
}

void tadiga::TadigaFactory::SetTadigaParameterDefaults(
    Teuchos::Ptr<Teuchos::ParameterList> tadiga_parameters) {
  tadiga_parameters->set("Verbose", false);
}

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
#ifndef TADIGA_FACTORY_HPP
#define TADIGA_FACTORY_HPP

#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>

#include "tadiga.h"

namespace tadiga {

class TadigaFactory {
 public:
  //! Default constructor.
  TadigaFactory();

  //! Destructor
  virtual ~TadigaFactory() {}

  virtual Teuchos::RCP<tadiga::Tadiga> tadiga::TadigaFactory::create(
      const std::string input_file,
      const Teuchos::RCP<const Teuchos::Comm<int>>& comm,
      Teuchos::RCP<Geometry> input_tadiga_geometry);

  virtual Teuchos::RCP<tadiga::Tadiga> tadiga::TadigaFactory::create(
      const std::string input_file,
      const Teuchos::RCP<const Teuchos::Comm<int>>& comm);

 private:
  //! Private function to set default problem parameter values in lieu of
  void SetTadigaParamDefaults(
      Teuchos::Ptr<Teuchos::ParameterList> tadiga_parameters);

  //! Private copy constructor to prohibit copying.
  TadigaFactory(const TadigaFactory&);

  //! Private assignment operator to prohibit copying.
  TadigaFactory& operator=(const TadigaFactory&);

 protected:
};
}
#endif  // TADIGA_FACTORY_HPP

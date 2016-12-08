// Copyright 2016 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>

#include <Teuchos_GlobalMPISession.hpp>
#include <Tpetra_DefaultPlatform.hpp>
#include <Tpetra_Version.hpp>

//#include "tadiga_factory.hpp"

int main(int argc, char* argv[]) {
  // Initialize MPI
  Teuchos::GlobalMPISession mpi_session(&argc, &argv, NULL);

  Teuchos::RCP<const Teuchos::Comm<int>> comm =
      Tpetra::DefaultPlatform::getDefaultPlatform().getComm();

  const int rank = comm->getRank();
  const int number_of_processors = comm->getSize();

  // Banner
  if (rank == 0) {
    std::cout << "\n-- TaDIgA" << std::endl;
    if (number_of_processors > 1)
      std::cout << "MPI initialized on " << number_of_processors
                << " processors.\n"
                << std::endl;
  }

  if (argc != 2) {
    if (rank == 0) std::cout << "Usage:  tadiga <input.yaml>\n" << std::endl;
    return 1;
  }

  // std::string yaml_file_name(argv[1]);

  // Create factory object to produce main tadiga object
  // TADIGA::TadigaFactory tadigaFactory;
  // Create tadiga object
  // Teuchos::RCP<TADIGA::Tadiga> tadiga =
  // tadigaFactory.create(yaml_file_name, tadigaComm);

  return 0;
}

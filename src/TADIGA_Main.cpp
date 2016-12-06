//Copyright 2015 John T. Foster

//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

#include <iostream>

#include <Tpetra_ConfigDefs.h> // used to define HAVE_MPI
#ifdef HAVE_MPI
  #include <Tpetra_MpiComm.h>
#else
  #include <Tpetra_SerialComm.h>
#endif
#include <Teuchos_RCP.hpp>

#include "TIDIGA_Factory.hpp"


int main(int argc, char *argv[]) {

  // Initialize MPI and timer
  std::size_t mpi_id = 0;
  std::size_t mpi_size = 1;
  #ifdef HAVE_MPI
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_id);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  #endif

    // Set up communicators
  MPI_Comm tidigaComm = MPI_COMM_WORLD;


    // Banner
  if(mpi_id == 0){
    std::cout << "\n-- TIDIGA" << std::endl;
  if(mpi_size > 1)
      std::cout << "MPI initialized on " << mpi_size << " processors.\n" << std::endl;
  }

  std::size_t status = 0;
  try {
    // input file
    if(argc != 2){
      if(mpi_id == 0)
        std::cout << "Usage:  TIDIGA <input.yaml>\n" << std::endl;
      #ifdef HAVE_MPI
        MPI_Finalize();
      #endif
      return 1;
    }

    std::string yaml_file_name(argv[1]);

    // Create factory object to produce main TIDIGA object
    TIDIGA::TIDIGAFactory tidigaFactory;
    // Create peridigm object
    Teuchos::RCP<TIDIGA::Tidiga> tidiga = tidigaFactory.create(yaml_file_name, tidigaComm);

  }

  // handle any exceptions thrown
  catch (std::exception& e) {
      std::cout << e.what() << std::endl;
      status = 10;
  }
  catch (std::string& s) {
      std::cout << s << std::endl;
      status = 20;
  }
  catch (char *s) {
      std::cout << s << std::endl;
      status = 30;
  }
  catch (...) {
      std::cout << "Caught unknown exception!" << std::endl;
      status = 40;
  }

#ifdef HAVE_MPI
    MPI_Finalize() ;
#endif

  return status;
}

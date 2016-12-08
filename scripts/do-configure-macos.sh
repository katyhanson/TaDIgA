#!/usr/bin/env bash

MPI_PATH=/usr/local/openmpi/bin

cmake -DTrilinos_DIR:PATH=/usr/local/trilinos/include \
      -DCMAKE_CXX_COMPILER:PATH=$MPI_PATH/mpicxx \
      -DCMAKE_CXX_FLAGS:STRING="-std=c++14 -O2" \
      ..

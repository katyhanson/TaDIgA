/usr/bin/env bash

cmake -DTrilinos_DIR:PATH=/usr/local/trilinos/include \
      -DCMAKE_CXX_COMPILER:STRING=mpicc \
      -DCMAKE_CXX_FLAGS:STRING="-std=c++14" \
      ..

#!/usr/bin/env bash


cmake -DTrilinos_DIR:PATH=/usr/local/trilinos/lib/cmake/Trilinos \
      -DCMAKE_CXX_COMPILER:PATH=/usr/local/bin/mpicxx \
      -DCMAKE_CXX_FLAGS:STRING="-std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wno-unused-parameter" \
      -DCMAKE_BUILD_TYPE:STRING=Release \
      ..

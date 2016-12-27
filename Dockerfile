FROM johntfoster/trilinos:tadiga

MAINTAINER John Foster <johntfosterjr@gmail.com>

ENV HOME /root

#Build Tadiga
WORKDIR /
RUN git clone https://github.com/johntfoster/tadiga.git tadiga; \
    mkdir /tadiga/build

WORKDIR /tadiga/build/
RUN cmake \
    -D CMAKE_BUILD_TYPE:STRING=Release \
    -D CMAKE_INSTALL_PREFIX:PATH=/usr/local/tadiga \
    -D CMAKE_CXX_FLAGS:STRING="-std=c++14" \
    -D TRILINOS_DIR:PATH=/usr/local/trilinos/lib/cmake/Trilinos \
    -D CMAKE_CXX_COMPILER:STRING="mpicxx" \
    ..; \
    make -j8 && make install

WORKDIR /
RUN rm -rf tadiga

WORKDIR /output
ENV PATH /usr/local/tadiga/bin:$PATH

CMD    ["/usr/sbin/sshd", "-D"]

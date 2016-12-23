FROM peridigm/trilinos

MAINTAINER John Foster <johntfosterjr@gmail.com>

ENV HOME /root

WORKDIR /

RUN apt-get -yq install openmpi-bin
RUN apt-get -yq install openssh-server

#Build Peridigm
RUN git clone https://github.com/johntfoster/tadiga.git tadiga 
RUN mkdir /tadiga/build

WORKDIR /tadiga/build/
RUN cmake \
    -D CMAKE_BUILD_TYPE:STRING=Release \
    -D CMAKE_INSTALL_PREFIX:PATH=/usr/local/tadiga \
    -D CMAKE_CXX_FLAGS:STRING="-std=c++14" \
    -D TRILINOS_DIR:PATH=/usr/local/trilinos/lib/cmake/Trilinos \
    -D CMAKE_CXX_COMPILER:STRING="mpicxx" \
    ..; \
    make && make install
    cd ..; \
    rm -rf tadiga

VOLUME /output
WORKDIR /output
ENV PATH /usr/local/tadiga/bin:$PATH

RUN mkdir /var/run/sshd
EXPOSE 22
CMD    ["/usr/sbin/sshd", "-D"]

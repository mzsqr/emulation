FROM ubuntu:latest

# build verilator
RUN apt-get update -yyq && apt-get upgrade -yyq
RUN apt-get install -y git help2man perl python3 make
RUN apt-get install -y g++  # Alternatively, clang
RUN apt-get install -y libfl2  # Ubuntu only (ignore if gives error)
RUN apt-get install -y libfl-dev  # Ubuntu only (ignore if gives error)
RUN apt-get install -y zlib1g zlib1g-dev  # Ubuntu only (ignore if gives error)
RUN apt-get install -y ccache  libgoogle-perftools-dev numactl git autoconf flex bison
RUN git clone https://github.com/verilator/verilator
WORKDIR /verilator
RUN git pull        # Make sure we're up-to-date
RUN git checkout stable
RUN autoconf
RUN ./configure      # Configure and create Makefile
RUN make -j `nproc`  # Build Verilator itself (if error, try just 'make')
RUN make install

RUN apt-get install -y python3-pip
RUN pip install pysv numpy

WORKDIR /dpi_test
COPY ./hdl ./sim_main.cpp ./build ./

ENTRYPOINT [ "/bin/bash" ]
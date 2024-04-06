FROM seanpatrickobrien/openroad-ubuntu22.04-dev:latest

# gtest
RUN mkdir -p /tmp/gtest/build && \
    cd /tmp/gtest && \
    wget https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz && \
    tar -xzf release-1.12.1.tar.gz && \
    cd /tmp/gtest/build && \
    cmake /tmp/gtest/googletest-release-1.12.1 -DCMAKE_CXX_STANDARD=17 -DBUILD_SHARED_LIBS=ON && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/gtest

# abseil
RUN mkdir -p /tmp/abseil/build && \
    cd /tmp/abseil && \
    wget https://github.com/abseil/abseil-cpp/archive/refs/tags/20220623.1.tar.gz && \
    tar -xzf 20220623.1.tar.gz && \
    cd /tmp/abseil/build && \
    cmake /tmp/abseil/abseil-cpp-20220623.1 -DABSL_BUILD_TEST_HELPERS=ON -DABSL_USE_EXTERNAL_GOOGLETEST=ON -DBUILD_SHARED_LIBS=ON && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/abseil

# protobuf
RUN mkdir -p /tmp/protobuf/build && \
    cd /tmp/protobuf && \
    wget https://github.com/protocolbuffers/protobuf/archive/refs/tags/v21.12.tar.gz && \
    tar -xzf v21.12.tar.gz && \
    cd /tmp/protobuf/build && \
    cmake /tmp/protobuf/protobuf-21.12 -Dprotobuf_USE_EXTERNAL_GTEST=ON -Dprotobuf_ABSL_PROVIDER=package -Dprotobuf_BUILD_SHARED_LIBS=ON && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/protobuf

# re2
RUN mkdir -p /tmp/re2/build && \
    cd /tmp/re2 && \
    wget https://github.com/google/re2/archive/refs/tags/2023-11-01.tar.gz && \
    tar -xzf 2023-11-01.tar.gz && \
    cd /tmp/re2/build && \
    cmake /tmp/re2/re2-2023-11-01 -DBUILD_SHARED_LIBS=ON && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/re2

# glpk
RUN mkdir -p /tmp/glpk/build && \
    cd /tmp/glpk && \
    wget https://ftp.gnu.org/gnu/glpk/glpk-5.0.tar.gz && \
    tar -xzf glpk-5.0.tar.gz && \
    cd /tmp/glpk/build && \
    /tmp/glpk/glpk-5.0/configure  && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/glpk

# pybind11
RUN mkdir -p /tmp/pybind11/build && \
    cd /tmp/pybind11 && \
    wget https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz && \
    tar -xzf v2.11.1.tar.gz && \
    cd /tmp/pybind11/build && \
    cmake /tmp/pybind11/pybind11-2.11.1 -DBoost_INCLUDE_DIR=/usr/local/include -DEIGEN3_INCLUDE_DIR=/usr/local/include/eigen3 && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/pybind11

# pip
RUN apt-get update && \
    apt-get install -y python3-pip

# python packages needed by or-tools
RUN python3 -m pip install mypy_protobuf virtualenv

# Coin cbc
RUN mkdir -p /tmp/cbc/build && \
    cd /tmp/cbc && \
    wget https://www.coin-or.org/download/source/Cbc/Cbc-2.10.4.tgz && \
    tar -xzf Cbc-2.10.4.tgz && \
    cd /tmp/cbc/build && \
    /tmp/cbc/Cbc-2.10.4/configure --build=$(arch)-unknown-linux-gnu --prefix=/usr/local -C --enable-static && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/cbc

# pkg-config
RUN apt-get install -y pkg-config

# swig4
RUN mkdir -p /tmp/swig4/build && \
    cd /tmp/swig4 && \
    wget https://github.com/swig/swig/archive/refs/tags/rel-4.0.2.tar.gz && \
    tar -xzf rel-4.0.2.tar.gz && \
    cd /tmp/swig4/swig-rel-4.0.2 && \
    ./autogen.sh && \
    cd /tmp/swig4/build && \
    /tmp/swig4/swig-rel-4.0.2/configure --without-tcl && \
    make && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/swig4

# or-tools
RUN mkdir -p /tmp/patches
COPY ./patches/* /tmp/patches
RUN mkdir -p /tmp/ortools/build && \
    cd /tmp/ortools && \
    wget https://github.com/google/or-tools/archive/refs/tags/v9.4.tar.gz && \
    tar -xzf v9.4.tar.gz && \
    cd /tmp/ortools/or-tools-9.4 && \
    patch -p1 < /tmp/patches/fix-stringview-compile.patch && \
    cd /tmp/ortools/build && \
    cmake /tmp/ortools/or-tools-9.4 -DBUILD_DEPS=OFF -DBUILD_PYTHON=ON -DBUILD_pybind11=OFF -DFETCH_PYTHON_DEPS=OFF -DUSE_GLPK=ON -DUSE_SCIP=OFF && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/ortools

# Remove version of or-tools provided by OpenROAD Docker (wrong architecture)
RUN rm -rf /opt/or-tools

# deps
RUN apt-get install -y python3-tk valgrind help2man

# verilator
RUN mkdir -p /tmp/verilator && \
    cd /tmp/verilator && \
    git clone https://github.com/verilator/verilator.git -b v5.018 && \
    cd verilator && \
    autoconf && \
    ./configure --prefix=/usr/local && \
    make && \
    make install && \
    cd /tmp && \
    rm -rf /tmp/verilator

# deps
RUN apt-get install -y libcurl4-openssl-dev libpng-dev

# klayout python
RUN pip install klayout==0.28.17.post1

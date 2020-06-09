# How to configure protobuf env for Test
## Reference
* https://judynewyork.tistory.com/73
## Preference
* apt update && apt upgrade
* apt install -y pkg-config autoconf automake libtool curl make g++ unzip
  * -y? : ignore install permission message [Y/n]
  * for protobuf
* apt install -y build-essential autoconf libtool git curl
  * for grpc
## Install protobuf package
* curl -OL https://github.com/google/protobuf/releases/download/v3.3.0/protoc-3.3.0-linux-x86_64.zip
* unzip protoc-3.3.0-linux-x86_64.zip -d protoc3
* mv protoc3/bin/* /usr/local/bin/
* mv protoc3/include/* /usr/local/include/
* chown $USER /usr/local/bin/protoc
* chown -R $USER /usr/local/include/google
## Install protobuf
* git clone https://github.com/google/protobuf.git
* cd protobuf
* git submodule update --init --recursive
* ./autogen.sh
* ./configure
* make
* make check
* make install
* ldconfig
## Install grpc
* cd /usr/local/src
* git clone -b $(curl -L http://grpc.io/release) https://github.com/grpc/grpc
* cd grpc
* git sudmodule update --init
* make
* make install
## Test
* which protoc
* cd examples/cpp/helloworld
* make (or make clean + make)
* run
  * server
    * ./greeter_server
  * client
    * ./greeter_client

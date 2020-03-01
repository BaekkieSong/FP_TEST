# GTest with conan
## Conan install
* sudo apt install python-pip
* pip install conan
* shell-command: conan
## Generate Conan Profile
* conan profile new default --detect  # Generates default profile detecting GCC and sets old ABI
* conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI
  * recommend this
## GTest install
* pip install --upgrade pip
* conan search *gtest* -r=conan-center
* conan install [GTest version]
  * ex) conan install gtest/1.8.1@bincrafters/stable
## Make conanfile.txt
* move to cpp DIR.
* vim conanfile.txt
  * reference: <https://github.com/choiwooseok/fpUtil/blob/master/FpStrUtil/conanfile.txt> 
```
[requires]
gtest/1.8.1@bincrafters/stable
[generators]
cmake
```
## Add conan to CMakeLists.txt
* vim CMakeLists.txt
  * reference: <https://github.com/choiwooseok/fpUtil/blob/master/FpStrUtil/CMakeLists.txt> 
```
INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
```
## build
* mkdir build & cd build
* conan install ..
* cmake ..
* make
* ./bin/[executable name]
## CORS
* bin파일이 build/bin/ 경로에 자동으로 떨어지므로 관리가 편리함
* main을 따로 작성해주지 않아도 됨

# GoogleTest(GTest) Usage Guide

## googletest
### Downloads
* move to install path. 
  * ex)cd ~/
* git clone https://github.com/google/googletest.git
### Generate gtest lib-files
* cd googletest/googletest
* mkdir build & cd build
* cmake ..
* make
### Check
* Check genegated lib-files. (libgtest.a & libgtest_main.a)
* They're located in build/lib.
### Generate gmock(not used here)
* U can generate gmock lib-files like gtest.
* path: googletest/googlemock

## GTest Usage
### build gtest.exe
* move to GTest DIR
* open CMakeLists.txt and change USER or GTEST_DIR if need.
* mkdir build
* cd build
* cmake ..
* make
### Check
* find gtest.exe
* run gtest.exe
  * ./gtest.exe
### Filter
* U can execute filtered gtest.exe
  * ex) ./gtest.exe --gtest_filter=CASE_SUM*
  * ex) ./gtest.exe --gtest_filter=CASE_EXPECT.FALSE
### Tip
* just include <gtest/gtest.h> in file. test_main.cc can find it.

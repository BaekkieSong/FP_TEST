#include "string16s.h"
#include <iostream>

int main(int argc, char** argv) {
  const wchar_t* str = L"abcdegf";
  std::cout << "memchar: " << wmemchr(str, wchar_t(L'd'), sizeof(str)) << std::endl;
  return 0;
}

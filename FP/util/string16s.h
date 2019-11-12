#ifdef __STRING16__
#define __STRING16__

#define OS_WIN 1
#if defined(OS_WIN)
  #define WCHAR_T_IS_UTF16 1
#elif defined(OS_FUCHSIA)
  #define WCHAR_T_IS_UTF32 1
#else
  #error Please add support for your compiler in build/build_config.h
#endif

#include <string>
#if defined(WCHAR_T_IS_UTF16)
  typedef wchar_t char16;
  typedef std::wstring string16;
#elif defined(WCHAR_T_IS_UTF32)
  typedef uint16_t char16;
#endif

static int c16memcmp(const char16* s1, const char16* s2, size_t n);
static size_t c16len(const char16* s);
static const char16* c16memchr(const char16* s, char16 c, size_t n);
//char16* c16memmove(char16* s1, const char16* s2, size_t n);
//char16* c16memcpy(char16* s1, const char16* s2, size_t n);
//char16* c16memset(char16* s, char16 c, size_t n);

int c16memcmp(const char16* s1, const char16* s2, size_t n) {
  //return
  // 1: s1 > s2
  // 0: s1 == s2
  // -1: s1 < s2
  int result;
  while (n-- > 0) {
    if (*s1 < *s2) {
      result = -1;
    } else if (*s1 > *s2) {
      result = 1;
    } else {
      result = 0;
    }
    ++s1;
    ++s2;
  }
  return result;
}
size_t c16len(const char16* s) {
  size_t size = 0;
  char c = *s;
  while (s != NULL)
    ++size;
  return size;
}
const char16* c16memchr(const char16* s, char16 c, size_t n) {
  if (n-- > 0 ) {
    if (*s == c) {
      return s;
    } else {
      ++s;
    }
  }
  return nullptr;
}
//char16* c16memmove(char16* s1, const char16* s2, size_t n);
//char16* c16memcpy(char16* s1, const char16* s2, size_t n);
//char16* c16memset(char16* s, char16 c, size_t n);


#endif

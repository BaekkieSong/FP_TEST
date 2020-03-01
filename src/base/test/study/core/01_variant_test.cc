#include <gtest/gtest.h>
#if defined(STD_VERSION17)
#include <variant>
#else
//#include <variant>
#endif

TEST(CaseTypeTest, Variant_VS_Union) {
#if defined(STD_VERSION17)
  std::variant<int, char, std::string, double> vrt;
  vrt = 3;
  EXPECT_EQ(3, std::get<int>(vrt));
  std::cout << sizeof(vrt) << std::endl;
#else
  union Variant {
    int i;
    char c;
  };
  Variant vrt;
  vrt.i = 3;
  EXPECT_EQ(3, vrt.i);
  vrt.c = 'a';
  EXPECT_NE(3, vrt.i);
  EXPECT_EQ('a', vrt.c);
#endif
}

TEST(CoreVariantTest, VariantSemantic) {
  std::variant<int, double, char> vrt;
  vrt = 3;
  EXPECT_EQ(3, std::get<int>(vrt));
  EXPECT_EQ(3, std::get<0>(vrt));
  vrt = 'a';
  //EXPECT_EQ(3, std::get<int>(vrt));  //error! 'std::bad_variant_access' occured.
  //EXPECT_EQ(3, std::get<0>(vrt));
  EXPECT_EQ('a', std::get<char>(vrt));
  EXPECT_EQ('a', std::get<2>(vrt));

}

TEST(CoreVariantTest, TupleSemantic) {
  std::tuple tp = std::make_tuple(3, 1.12, 'a', "asdf");
  //std::tuple tp = std::make_tuple(3, 'a', 'b', "asdf"); //error! overlaped type - 'a', 'b'
  EXPECT_EQ(std::get<int>(tp), 3);
  EXPECT_EQ(std::get<double>(tp), 1.12);
  EXPECT_EQ(std::get<char>(tp), 'a');
  EXPECT_EQ(std::get<const char*>(tp), "asdf");
}

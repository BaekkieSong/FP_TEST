#include <gtest/gtest.h>
#include <thread>

void func1(int cnt, int sum) {
  for (int i = 0; i < cnt; i++)
    sum += i;
  EXPECT_EQ(sum, 3);
}

class Functor {
  public:
    Functor(int cnt) : cnt_(cnt) {}
    void operator()() const {
      int sum = 0;
      for (int i = 0; i < cnt_; i++)
        sum += i;
      EXPECT_EQ(sum, 3);
    }
  private:
    int cnt_;
};

class Normal {
  public:
    Normal(int cnt) : cnt_(cnt){}
    void method() {
      int sum = 0;
      for (int i = 0; i < cnt_; i++)
        sum += i;
      EXPECT_EQ(sum, 3);
    }
  private:
    int cnt_;
};

TEST(ModernThreadTest, Join) {
  int sum = 0;
  std::thread th(func1, 3, sum);
  th.join();
  EXPECT_EQ(sum, 0);
}

TEST(MordernThreadTest, Functor) {
  //uniform Initialize 문법
  std::thread th{Functor(3)};
  th.join();
  //객체 선언 후
  Functor f(3);
  std::thread th2(f);
  th2.join();
  //임시 객체
  std::thread th3(Functor(3));//생성된 obj(임시객체)가 넘어가 obj()를 수행
  th3.join();
}

TEST(MordernThreadTest, Ramda) {
  std::thread th([](int cnt) {
        int sum = 0;
        for (int i = 0; i < cnt; i++)
          sum += i;
        EXPECT_EQ(sum, 3);
      }, 3);
  th.join();
}

TEST(MordernThreadTest, NormalClass) {
  Normal n(3);
  std::thread th(&Normal::method, &n);
  th.join();
}

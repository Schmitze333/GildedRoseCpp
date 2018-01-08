#include "gmock/gmock.h"

TEST(it, works) {
  ASSERT_TRUE(false);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

#include "test.h"

TEST(Getters, Rows) {
  S21Matrix matrix(5, 3);
  ASSERT_EQ(matrix.GetRows(), 5);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
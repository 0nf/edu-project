#include "list.h"
#include <limits.h>
#include "gtest/gtest.h"

TEST(GetTest, correct){
  list l = list_create();
  EXPECT_EQ(l->m->isempty(l), 1);
}

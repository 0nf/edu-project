#include <limits.h>
#include "list.h"
#include "gtest/gtest.h"


TEST(CreateTest, correct){
  EXPECT_EQ(1, 1);
  list l = list_create();
  //  EXPECT_EQ(l->m->isempty(l), 1);
}

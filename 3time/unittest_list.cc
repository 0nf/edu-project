#include <limits.h>
#include "list.h"
#include "gtest/gtest.h"


TEST(InitDestroy, CorrectEmpty){
  EXPECT_EQ(1, 1);
  list l = list_create();
  EXPECT_TRUE(l->m->isempty()==1);
}

TEST(InitDestroy, Free){
  list l = list_create();
  l->m->free(l);
  EXPECT_TRUE(l->m==NULL);
}

TEST(DataManipulation, Insert){
  list l = list_create();
  l->m->insert(l, (elem) 4);
  l->m->insert(l, (elem) 5);
  iter it;
  it.l = l->m->first();
  EXPECT_TRUE(l->m->iter_get(it.l)==(elem) 4);
}

// TEST(DataManipulation, Delete){
//   list l = list_create();
//   l->m->insert(l, (elem) 4);
//   l->m->insert(l, (elem) 5);
//   iter it;
//   it.l = l->m->first();
//   l->m->del(it.l);
//   EXPECT_TRUE(l->m->iter_get(it.l)==(elem) 5);
// }

TEST(DataManipulation, IterInc){
  list l = list_create();
  l->m->insert(l, (elem) 4);
  l->m->insert(l, (elem) 5);
  iter it;
  it.l = l->m->first();
  it.l = l->m->iter_inc(it.l);
  EXPECT_TRUE(l->m->iter_get(it.l)==(elem) 5);
}

TEST(DataManipulation, IterSwap){
  list l = list_create();
  l->m->insert(l, (elem) 4);
  l->m->insert(l, (elem) 5);
  iter it1, it2;
  it1.l = l->m->first();
  it2.l = l->m->last();
  l->m->swap(it1.l, it2.l);
  EXPECT_TRUE(l->m->iter_get(it1.l)==(elem) 5);
}

void inc(int * a){
  *a = *a + 1;
}

TEST(DataManipulation, Foreach){
  list l = list_create();
  l->m->insert(l, (elem) 4);
  l->m->insert(l, (elem) 5);
  int t = 1;
  inc(&t);
  EXPECT_EQ(t, 2);
  l->m->foreach(l, inc);
  iter it1;
  it1.l = l->m->first();
  EXPECT_TRUE(l->m->iter_get(it1.l)==(elem) 5);
}

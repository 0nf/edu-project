#include "list2.h"
typedef iter_list iter;

#define insert m->insert
#define first m->first
#define last m->last
#define iter_inc m->iter_inc
#define iter_dec m->iter_dec
#define iter_get m->iter_get

void swap(iter * a, iter * b){
  iter c = *a;
  *a = *b;
  *b = c;
}

int main(){
  iter it1, it2;
  list l = list_create(l);
  int i, j;
  l->insert(l, 1);
  printf("%d\n", l->iter_get(l->first));
  return 0;
  for (i = 0; i < 10; i++){
    l->insert(l, i);//insert(l, rand(1, 100));
  }
  for (it1 = l->first(l); it1 != l->last(l); it1 = l->iter_inc(it1))
    printf("%d ", l->iter_get(it1));
  printf("\n");
  //common iter_inc for list and vec 
  for (it1 = l->first(l); it1 != l->last(l); it1 = l->iter_inc(it1)){
    for (it2 = l->first(l); it2 != l->last(l); it2 = l->iter_inc(it2)){
      if (l->iter_get(it1) < l->iter_get(it2))
        swap(&it1, &it2);
    }
  }
  for (it1 = l->first(l); it1 != l->last(l); it1 = l->iter_inc(it1))
    printf("%d ", l->iter_get(it1));
  printf("\n");
  return 0;
}

#include "list2.h"
typedef iter_list iter;

void swap(iter * a, iter * b){
  iter c = *a;
  *a = *b;
  *b = c;
}

int main(){
  iter it1, it2;
  list l = list_create(l);
  int i, j;
  for (i = 0; i < 10; i++){
    l->m->insert(l, rand(1, 100));
  }
  for (it1 = l->m->first(l); it1 != l->m->last(l); it1 = l->m->iter_inc(it1))
    printf("%d ", l->m->iter_get(it1));
  printf("\n");
  //common iter_inc for list and vec 
  for (it1 = l->m->first(l); it1 != l->m->last(l); it1 = l->m->iter_inc(it1)){
    for (it2 = l->m->first(l); it2 != l->m->last(l); it2 = l->m->iter_inc(it2)){
      if (l->m->iter_get(it1) < l->m->iter_get(it2))
        swap(&it1, &it2);
    }
  }
  for (it1 = l->m->first(l); it1 != l->m->last(l); it1 = l->m->iter_inc(it1))
    printf("%d ", l->m->iter_get(it1));
  printf("\n");
  return 0;
}

#include "list2.h"
typedef iter_list iter;

void swap(iter * a, iter * b){
  iter c = *a;
  *a = *b;
  *b = c;
}

int main(){
  iter it1, it2;
  flist l = list_create(l);
  int i, j;
  for (i = 0; i < 10; i++){
    l->m->insert(l, rand(1, 100));
  }
  //common iter_inc for list and vec 
  for (it1 = l->m->begin(l); it1 != l->m->end(l); it1->m->iter_inc(it1)){
    for (it2 = l->m->begin(l); it2 != l->m->end(l); it2->m->iter_inc(it2)){
        if (l->m->get(l, it1) < l->m->get(l, it2))
          swap(&it1, &it2);
      }
    }
  for (it1 = l->m->begin(l); it1 != l->m->end(l); it1 = l->m->iter_inc(it1))
    printf("%d ", l->m->get(l, it1));
  printf("\n");
  return 0;
}

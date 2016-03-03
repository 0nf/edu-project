#include <stdio.h>
#include "list.h"

int main(){
  list l1 = list_create("1");
  list_insert(l1, "2");
  list_insert(l1, "hello\n");
  list_insert(l1, "3");
  list_delete(iter_dec(list_last(l1)));
  iter_list it;
  for (it  = list_first(l1); it != list_last(l1); it = iter_inc(it))
    printf("%s ", iter_get(it));
  printf("\n");
  iter_list_free(it);
  list_free(l1);
  return 0;//current state: working but segm err on free
}

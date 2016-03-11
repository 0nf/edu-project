#include <stdlib.h>
#include "list.h"
#include "vector.h"

/* typedef struct List_m { */
/*   //list and iterator methods */
/*   void list_free(list l); */
/*   iter_list iter_list_create(elem e); */
/*   void iter_list_free(iter_list l); */

/*   iter_list list_first(list l); */
/*   iter_list list_last(list l); */

/*   void* list_insert(list l, elem e);  */
/*   void list_delete(iter_list p); */
/*   elem iter_get(iter_list p); */

/*   iter_list iter_inc(iter_list l); */
/*   iter_list iter_dec(iter_list l); */
/* } list_m; */

/* typedef struct { */
/*   list_m * m; */
/* } list; */

typedef union Iter {
  iter_list l;
  iter_vec v;
  char x[256];
} iter;

enum {START, END};

typedef struct Node {
  elem val;
  struct Node *prev, *next;
  struct List *host;
} *node;

typedef  struct FullList {
  list_m m;
  node first, last;
  int num, size;
} *flist;

iter_list list_first(list p){
  flist l = (flist) p;
  return l->first;
}

iter_list list_last(list p){
  flist l = (flist) p;
  return l->last;
}

iter_list iter_inc(iter_list l){
  return (iter_list) (((node)l)->next);
}

iter_list iter_dec(iter_list l){ 
  return (iter_list) (((node)l)->prev);
}


void iter_list_free(iter_list it){
  free(it);
}

void list_free(list p){
  iter_list it;
  for (it = list_first(p); it != list_last(p); it = iter_inc(it))
    iter_list_free(it);
  free((flist)p);
}

iter_list iter_list_create(){
  iter_list p = (iter_list) malloc(sizeof(*p));//correct?
  return p;
}

/*iterator methods*/

int isemptylist(list p){
  flist l = (flist) p;
  return (l->first == l->last) ? 1:0;
}

void* list_insert(list p, elem e){ //first elem correct, fail before second
  flist l = (flist) p;
  node n;
  n = malloc(sizeof(struct Node));
  n->val = e;
  n->host = p;
  if (isemptylist(p)){
    n->prev = START;
    n->next = l->last;
    l->last->prev = n;
    l->first = n;
  } else {
    l->last->prev->next = n;
    n->prev = l->last->prev;
    n->next = l->last;
    l->last->prev = n;
  }
  l->num++;
  return n;
}

void list_delete(iter_list p){ //check working with num=1
  if (isemptylist(((node)p)->host))
    list_free(((node)p)->host);
  else {
    if ( ((node)p)->next == END)
      ((node)p)->prev->next = END;
    else
      ((node)p)->prev->next = ((node)p)->next;
    if ( ((node)p)->prev == START)
      ((node)p)->next->prev = START;
    else
      ((node)p)->next->prev = ((node)p)->prev;
    ((flist)(((node)p)->host))->num--;
  }
}



elem iter_get(iter_list p){//there should be isemptylist before
                           //calling this
  return ((node)p)->val;
}


list list_create(){
  flist l;
  l = (flist) malloc(sizeof(struct FullList));
  l->num = 0;
  l->last = (node) malloc(sizeof(struct Node));
  l->first = l->last;
  l->first->prev = START;
  l->last->next = END;
  //  l->first->next = l->last;
  //  l->last->prev = l->first;
  //  l->first->val = e;
  //  l->first->host = l;
  l->last->host = l;
  l->m = malloc(sizeof(*l->m));
  l->m->free = list_free;
  l->m->first = list_first;
  l->m->last = list_last;
  l->m->insert = list_insert;
  l->m->delete = list_delete;
  l->m->iter_create = iter_list_create;
  l->m->iter_free = iter_list_free;
  l->m->iter_inc = iter_inc;
  l->m->iter_dec = iter_dec;
  l->m->iter_get = iter_get;
  return (list) l;
}


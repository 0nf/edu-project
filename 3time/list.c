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
/*   void list_del(iter_list p); */
/*   elem iter_get(iter_list p); */

/*   iter_list iter_inc(iter_list l); */
/*   iter_list iter_dec(iter_list l); */
/* } list_m; */

/* typedef struct { */
/*   list_m * m; */
/* } list; */



enum {START, END};

typedef struct Node {
  elem val;
  struct Node *prev, *next;
  struct List *host;
} *node;

typedef  struct FullList {
  list_m m;
  node first, last;
  int num;
} *flist;

iter_list list_first(list p){
  flist l = (flist) p;
  return l->first;
}

iter_list list_last(list p){
  flist l = (flist) p;
  return l->last;
}

iter_list iter_list_inc(iter_list l){
  return (iter_list) (((node)l)->next);
}

iter_list iter_list_dec(iter_list l){ 
  return (iter_list) (((node)l)->prev);
}


void iter_list_free(iter_list it){
  free(it);
}

void list_free(void* v){
  list p = (list) v;
  iter_list it;
  for (it = list_first(p); it != list_last(p); it = iter_list_inc(it))
    iter_list_free(it);
  free((flist)p);
}

int isemptylist(list p){
  flist l = (flist) p;          /* fail begins here: this l!=list_create() */
  return (l->first == l->last) ? 1:0;
}

void* list_insert(void* v, elem e){
  list p = (list) v;
  flist l = (flist) p;
  node n;
  n = (node) malloc(sizeof(struct Node));
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

void list_del(iter_list p){ //check working with num=1
  if (isemptylist(((node)p)->host))
    list_free(((node)p)->host);
  else {
    if ( ((node)p)->next == (node)END)
      ((node)p)->prev->next = (node) END;
    else
      ((node)p)->prev->next = ((node)p)->next;//when dealing with first elem, p->prev == START and START->next causes segfault
    if ( ((node)p)->prev == START)
      ((node)p)->next->prev = START;
    else
      ((node)p)->next->prev = ((node)p)->prev;
    ((flist)(((node)p)->host))->num--;
  }
}



elem iter_list_get(iter_list p){//there should be isemptylist before
                           //calling this
  return ((node)p)->val;
}

void list_foreach(void* v, void (*func)()){
  list l = (list) v;
  flist p = (flist)l;
  int i;
  node n = p->first;
  func(&n->val);
  for (i = 1; i < p->num; i++){
    n = n->next;
    func(&n->val);
}
}


void swap_list(iter_list a, iter_list b){
  node t = (node) malloc(sizeof(*t));
  t->val = ((node)a)->val;
  ((node)a)->val = ((node)b)->val;
  ((node)b)->val = t->val;
  free(t);
}

list list_create(){
  flist l;
  l = (flist) malloc(sizeof(struct FullList));
  l->m = malloc(sizeof(*l->m));
  l->m->free = list_free;
  l->m->first = list_first;
  l->m->last = list_last;
  l->m->isempty = isemptylist;
  l->m->insert = list_insert;
  l->m->del = list_del;
  l->m->iter_free = iter_list_free;
  l->m->iter_inc = iter_list_inc;
  l->m->iter_dec = iter_list_dec;
  l->m->iter_get = iter_list_get;
  l->m->swap = swap_list;
  l->m->foreach = list_foreach;
  l->num = 0;
  l->last = (node) malloc(sizeof(struct Node));
  l->first = l->last;
  l->first->prev = (node) START;
  l->last->next = (node)  END;
  l->last->host = (list) l;

  return (list) l;
}


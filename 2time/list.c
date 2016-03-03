#include <stdlib.h>
#include "list.h"

enum {START, END};

typedef struct Node {
  elem val;
  struct Node *prev, *next;
  struct List *host;
} *node;

typedef struct List {
  node first, last;
  int num, size;
} *list;

list list_create(elem e){
  list l;
  l = malloc(sizeof(list*));
  l->num = 1;
  l->first = malloc(sizeof(node*));
  l->last = malloc(sizeof(node*));
  l->first->prev = START;
  l->last->next = END;
  l->first->next = l->last;
  l->last->prev = l->first;
  l->first->val = e;
  l->first->host = l;
  l->last->host = l;
  return l;
}

void list_free(list l){
  iter_list it;
  for (it = list_first(l); it != list_last(it); it = iter_inc(it))
    iter_list_free(it);
  free(l);
}

//iter_list iter_list_create();

void iter_list_free(iter_list it){
  free(it);
}

iter_list list_first(list l){
  return l->first;
}

iter_list list_last(list l){
  return l->last;
}

//there was an eclipse
/* void list_insert(list l, elem){ //by value, not pointer */
/*   if (num == size - 1){ */
/*     l->size += 10; */
/*     node t[] = malloc(sizeof(note) * l->size); */
/*     int i; */
/*     for (i = 0; i < (l->size - 10); i++) */
/*       t[i] = l->arr[i]; */
/*     l->arr = t; */
/*   } */
/*   l->arr[num++] = elem; */
/* } */

/*iterator methods*/

iter_list iter_inc(iter_list l){
  return (iter_list) (((node)l)->next);
}

iter_list iter_dec(iter_list l){ 
  return (iter_list) (((node)l)->prev);
}

void* list_insert(list l, elem e){
  node n;
  n = malloc(sizeof(node*));
  n->val = e;
  n->host = l;
  l->last->prev->next = n;
  n->prev = l->last->prev;
  n->next = l->last;
  l->last->prev = n;
  l->num++;
  return n;
}

void list_delete(iter_list p){ //check working with num=1
  if ( ((node)p)->next == END)
    ((node)p)->prev->next = END;
  else
    ((node)p)->prev->next = ((node)p)->next;
  if ( ((node)p)->prev == START)
    ((node)p)->next->prev = START;
  else
    ((node)p)->next->prev = ((node)p)->prev;
  ((node)p)->host->num--;
}

elem iter_get(iter_list p){
  return ((node)p)->val;
}

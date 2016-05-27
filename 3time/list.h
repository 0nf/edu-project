#ifdef __cplusplus
extern "C"{
#endif

typedef void *iter_list; 
typedef void *iter_vec;
typedef void *elem;

//typedef union Iter iter;

typedef struct List_m {
  //list and iterator methods
  void (*free)(void*);
  iter_list (*iter_create)(elem);
  void (*iter_free)(iter_list);

  iter_list (*first)();
  iter_list (*last)();

  int (*isempty)();
  //void* (*insert)();
  void* (*insert)(void*, elem); 
  void (*del)(iter_list);
  elem (*iter_get)(iter_list);

  iter_list (*iter_inc)(iter_list);
  iter_list (*iter_dec)(iter_list);
  void (*swap)(iter_list, iter_list);
  void (*foreach)(void*, void(*)(int*) );
} *list_m;

typedef struct List {
  list_m m;
} *list;

typedef union Iter {
  iter_list l;
  iter_vec v;
  char x[256];
} iter;

list list_create();

#ifdef __cplusplus
}
#endif

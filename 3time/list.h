typedef void *iter_list; 
typedef void *elem;

//typedef union Iter iter;

typedef struct List_m {
  //list and iterator methods
  void (*free)();
  iter_list (*iter_create)(elem);
  void (*iter_free)(iter_list);

  iter_list (*first)();
  iter_list (*last)();

  void* (*insert)();
  //  void* (*insert)(list, elem); 
  void (*delete)(iter_list);
  elem (*iter_get)(iter_list);

  iter_list (*iter_inc)(iter_list);
  iter_list (*iter_dec)(iter_list);
} *list_m;

typedef struct List {
  list_m m;
} *list;

list list_create();

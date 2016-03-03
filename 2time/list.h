typedef struct List *list;
typedef void *elem;

list list_create();
void list_free(list l);

typedef void *iter_list; 

iter_list iter_list_create(elem e);
void iter_list_free(iter_list l);

iter_list list_first(list l);
iter_list list_last(list l);

void* list_insert(list l, elem e); 
void list_delete(iter_list p);
elem iter_get(iter_list p);

iter_list iter_inc(iter_list l);
iter_list iter_dec(iter_list l);

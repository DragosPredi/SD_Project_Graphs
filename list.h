typedef int V;

typedef struct list {
	V data;
	V cost;
	struct list *prev, *next;
}*List;

void printList(List list);
List initList(V data);
List initListWCost(V data, V cost);
List addLast(List list, V data);
List addLastWCost(List list, V data, V cost);
List deleteItem(List l, V data);
List freeList(List list);
List intersection(List list1, List list2);
int isElement(List list, int index);
List clone(List list);
int sizeOfList(List list);
#include "header.h"

List initList(V data)
{
	List list;

	list = (List) malloc(sizeof(struct list));
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return list;
}
List initListWCost(V data, V cost)
{
	List list;

	list = (List) malloc(sizeof(struct list));
	list->data = data;
	list->cost = cost;
	list->next = NULL;
	list->prev = NULL;
	return list;
}
List addLast(List list, V data)
{
	List new, tmp;

	if (list == NULL)
		return initList(data);
	new = initList(data);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return list;
}
List addLastWCost(List list, V data, V cost)
{
	List new, tmp;

	if (list == NULL)
		return initListWCost(data, cost);
	new = initListWCost(data, cost);
	tmp = list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return list;

}

int isElement(List list, int index)
{
	List temp = list;
	while(temp != NULL){
		if(temp->data == index)
			return 1;
		temp = temp->next;
	}
	return 0;
}
List clone(List list)
{
	List temp = list;
	List clone = NULL;
	while(temp != NULL)
	{
		clone = addLast(clone, temp->data);
		temp = temp->next;
	}
	return clone;
}

int sizeOfList(List list)
{
	List temp = list;
	int cont = 0;
	while(temp != NULL)
	{
		cont++;
		temp = temp->next;
	}
	return cont;
}

List intersection(List list1, List list2)
{
    List temp = list1;
    List newList = NULL;
    while(temp != NULL)
    {
        List aux = list2;
        while(aux != NULL)
        {
            if(aux->data == temp->data){
            	if(!isElement(newList, temp->data))
                	newList = addLast(newList, temp->data);
            }
            
            aux = aux->next;
        }
        temp = temp->next;
    }
    return newList;
}

List deleteItem(List l, int frequency) {
	if(l == NULL) {
		return NULL;
	} else {
		List tmp = l, prev;
		if(tmp->data == frequency) {
			l = l->next;
			free(tmp);
			if(l == NULL)
				return NULL;
			else{
				l->prev = NULL;
				return l;
			}
		} else {
			prev = tmp;
			tmp = tmp->next;
		}
		while(tmp != NULL) {
			if(tmp->data == frequency) {
				prev->next = tmp->next;
				if (tmp->next != NULL)
					tmp->next->prev = prev;
				free(tmp);
				return l;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		return l;
	}
}

List freeList(List list)
{
	List tmp;

	if (list == NULL)
		return list;
	while (list != NULL) {
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return NULL;
}
void printList(List list)
{
	List aux = list;
	while(aux != NULL)
	{
		printf("[%d]", aux->data);
		aux = aux->next;
	}
	printf("\n");
}
/***************************************
* Author : Natty
* Reviewer : Eric
* Date : 19 / 12 / 2024
* Last update: 22 / 12 / 2024
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "dlist.h" 

#define 	NodeToIter(x)		((dlist_iter_t)x)
#define		IterToNode(x)		((dlist_node_t*)x)	

/****************struct and enum declaration*********************/

typedef struct dlist_node dlist_node_t;

struct dlist
{

	dlist_node_t *head; 
	dlist_node_t *dummy;


};

struct dlist_node 
{

	void* data;
	struct dlist_node *next;
	struct dlist_node *prev;	 

};

/** possible return values **/
typedef enum
{
	
	OPERATION_FAIL = 0,
	SUCCESS = 1
	
}dlistresult;

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/
static int CountNodes (void *data, void *user_param);
/**********End of functions declaration and definition *******/

/********************  DListCreate  ****************************/
dlist_t* DListCreate( void )
{
	dlist_t* p_dlist = NULL;
	p_dlist = (dlist_t*)malloc(sizeof(dlist_t));
	
	if ( NULL == p_dlist )
	{
		return NULL;
	}
	
	p_dlist->head =(dlist_node_t*)malloc(sizeof(dlist_node_t));
	
	if ( NULL == p_dlist->head )
	{
		free(p_dlist);
		p_dlist = NULL;
		return NULL;
	}
	
	p_dlist->dummy =(dlist_node_t*)malloc(sizeof(dlist_node_t));
	
	if ( NULL == p_dlist->dummy )
	{

		free(p_dlist->head);
		free(p_dlist);
		
		p_dlist = NULL;
		p_dlist->head = NULL;
		return NULL;
	}
	
	p_dlist->head->data = p_dlist;
	p_dlist->head->next = p_dlist->dummy;
	p_dlist->head->prev = NULL;
		
	p_dlist->dummy->data = p_dlist;
	p_dlist->dummy->next = NULL;
	p_dlist->dummy->prev = p_dlist->head;
	
	return 	p_dlist;
}	

/********************  DListIsEmpty  ****************************/
int DListIsEmpty( const dlist_t* dlist )
{
	 assert(dlist);	
	 return dlist->dummy == dlist->head->next;
}

/********************  DListBegin  ****************************/
dlist_iter_t DListBegin(const dlist_t *dlist)
{
	assert(dlist);
	return NodeToIter(dlist->head->next);
}

/********************  DListEnd  ****************************/
dlist_iter_t DListEnd(const dlist_t *dlist)
{
	assert(dlist);
	return NodeToIter(dlist->dummy);
}

/********************  DListGetData  ****************************/
void *DListGetData(dlist_iter_t iter)
{
	assert(IterToNode(iter));
	return IterToNode(iter)->data;
}

/********************  DListSetData  ****************************/ 

void DListSetData(dlist_iter_t iter, const void *data)
{
	assert(data);
	assert(IterToNode(iter));
	
	IterToNode(iter)->data = (void*)data; 
}


/********************  DListNext  ****************************/  
dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(IterToNode(iter));
	return NodeToIter(IterToNode(iter)->next);
}

/********************  DListPrev  ****************************/  
dlist_iter_t DListPrev(dlist_iter_t iter)
{
	assert(IterToNode(iter));
	return NodeToIter(IterToNode(iter)->prev);
}

/********************  DListIterIsEqual  ****************************/   
int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	
	assert(IterToNode(iter1));
	assert(IterToNode(iter2));
	
	return iter1 == iter2;

}

/********************  DListCount  ****************************/
size_t DListCount(const dlist_t *dlist)
{
	size_t size = 0;
	assert(dlist);
	DListForEach(DListBegin(dlist), DListEnd(dlist), CountNodes, &size);
	
	return size; 
}

/*******************op_func to count *********************/
static int CountNodes (void *data, void *user_param)
{
	(void)data;
	(*(size_t*)user_param)++;
	
	return SUCCESS;
}

/********************  DListDestroy  ****************************/
void DListDestroy(dlist_t *dlist)
{

	dlist_node_t* node = dlist->head->next;
	dlist_node_t* p_element = NULL;
	
	assert(dlist);
	
	while( node != dlist->dummy )
	{
		p_element = node;
		node = p_element->next;
		free(p_element);
	}
	
	free(dlist->dummy);
	dlist->dummy = NULL;
	
	free(dlist->head);
	dlist->head = NULL;
	
	free(dlist);
	dlist = NULL;
}


/******************  DListInsertBefore  ***********************/
dlist_iter_t DListInsertBefore(dlist_t *dlist, dlist_iter_t where,
								 const void *new_data)
{
	dlist_node_t* new_node = (dlist_node_t*)malloc(sizeof(dlist_node_t));

	assert(dlist); 
	assert(IterToNode(where));
		
	if ( NULL == new_node )
	{
		return DListEnd(dlist);
	}
		
	new_node->prev = IterToNode(DListPrev(where));
	new_node->data = (void*)new_data;
	new_node->next = IterToNode(where);
	
	IterToNode(DListPrev(where))->next = new_node;
	
	IterToNode(where)->prev = new_node; 		
	
	return NodeToIter(new_node);
}								 
 
/********************  DListRemove  ****************************/ 
  
dlist_iter_t DListRemove(dlist_iter_t what)
{
	dlist_node_t* temp = NULL;
	
	assert(IterToNode(what));
	
	temp = IterToNode(DListNext(what));
	
	IterToNode(DListPrev(what))->next = temp;
	
	temp->prev = IterToNode(DListPrev(what));
	
	
	free(IterToNode(what));
	what = NULL;
	
	return NodeToIter(temp);
}

/********************  DListPushFront  ****************************/ 
dlist_iter_t DListPushFront(dlist_t* dlist, const void* data)
{
	assert(dlist); 
		
	return DListInsertBefore(dlist, DListBegin(dlist), data);
}

/********************  DListPushBack  ****************************/ 
dlist_iter_t DListPushBack( dlist_t* dlist , const void* data)
{
	assert(dlist); 
	
	return DListInsertBefore(dlist, DListEnd(dlist), data);		
}

/********************  DListPopFront  ****************************/ 
void *DListPopFront(dlist_t* dlist)
{
	void* data_pop = NULL;
	
	assert(dlist);

	if( DListIsEmpty(dlist) )
	{
		return NULL;
	}
	
	data_pop = DListGetData(DListBegin(dlist));
	
	DListRemove(DListBegin(dlist));
	
	return data_pop;
	
}

/********************  DListPopBack  ****************************/ 

void *DListPopBack(dlist_t* dlist)
{
	void* data_pop = NULL;
	
	assert(dlist);

	if( DListIsEmpty(dlist) )
	{
		return NULL;
	}
	
	data_pop = DListGetData(DListPrev((DListEnd(dlist))));
	
	DListRemove(DListPrev((DListEnd(dlist))));
	
	return data_pop;
	
}

/********************  DListFind  ****************************/   

dlist_iter_t DListFind(dlist_iter_t start, dlist_iter_t end,
                       match_func_t match_func,
                       void *user_param)

{
	assert(IterToNode(start));
	assert(IterToNode(end));	
	assert(match_func); 
	
	while(!DListIterIsEqual(start, end)) 
	{
	
		if(SUCCESS == match_func(DListGetData(start), user_param))
		{
			return start;
		}
		
		start = DListNext(start);
	}

	return end;
}

/********************  DListMultiFind  ****************************/   
/*
 Applies match_func that the user inserta on every element
 in range [start:end) and inserts them to new_dlist
*/
int DListMultiFind(dlist_iter_t start, dlist_iter_t end,
                   match_func_t match_func, void* user_param,
                   dlist_t* match_dlist)
{

	dlist_iter_t new_iter = NULL;
		
	assert(IterToNode(start));
	assert(IterToNode(end));
	assert(match_dlist);	
	assert(match_func);
	
	while(!DListIterIsEqual(start, end)) 
	{
	
		if(SUCCESS == match_func(DListGetData(start), user_param))
		{		
			new_iter = DListPushBack(match_dlist, user_param);
			
			if(NULL == new_iter)
			{
				return !OPERATION_FAIL;
			}
			
		}

		start = DListNext(start);
	}

	return !SUCCESS;
} 
	
/********************  DListSplice  ****************************/ 
/*
Updates the addresses of source and targets lists acording to 
the operation of the function. 
*/
  
dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from,
                          dlist_iter_t to)

{
	
	dlist_iter_t prev_where = DListPrev(where);

	assert(IterToNode(from));
	assert(IterToNode(to));
	assert(IterToNode(where));
	
	IterToNode(DListPrev(where))->next = IterToNode(from);
	IterToNode(where)->prev = DListPrev(to);

	IterToNode(DListPrev(to))->next = IterToNode(where);

	IterToNode(DListPrev(from))->next = IterToNode(to);
	IterToNode(to)->prev = IterToNode(DListPrev(from));	

	IterToNode(from)->prev = prev_where;		
							
	return DListPrev(where);
	
}	


/********************  DListForEach  **************************/ 
/* 
 Applies a user specific operation function on all of
 the linked list's element's data
*/ 
int DListForEach(dlist_iter_t start, dlist_iter_t end,
                 operation_func_t op_func, void *user_param)

{
	
	int op_state = OPERATION_FAIL;
	
	assert(IterToNode(start));
	assert(IterToNode(end));
	assert(op_func);
	
	 
	while(!DListIterIsEqual(start, end))   
	{
	
		if(SUCCESS == op_func(DListGetData(start), user_param))
		{
			op_state = SUCCESS;
		}
		
		start = DListNext(start);
	}

	return op_state;
}                



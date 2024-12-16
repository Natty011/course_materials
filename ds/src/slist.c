/***************************************
* Author : Natty
* Reviewer : Natan
* Date : 10 / 12 / 2024
* Last update: 14 / 12 / 2024
*****************************************/


#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "slist.h" 

/****************struct and enum declaration*********************/

struct slist
{

	slist_node_t* head; /* Head of the link list*/
	slist_node_t* dummy;


};

struct slist_node /* NODE */
{

	void* data;
	struct slist_node* next; /* slist_iter_t */

};

/** possible return values **/
typedef enum
{

	SUCCESS,
	OPERATION_FAIL

}slistResult;

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/

static int CountNodes (void *data, void *user_param);
	
slist_node_t* IterToNode(slist_iter_t iter)
{
	return (slist_node_t*)iter;
}

slist_iter_t NodeToIter(slist_node_t* node) 
{
	return (slist_iter_t)node;
}

/**********End of functions declaration and definition *******/

/********************  slistCreate  ****************************/
slist_t *SlistCreate(void)
{
	slist_t* p_slist = NULL;
	p_slist = (slist_t*)malloc(sizeof(slist_t));
	
	if ( NULL == p_slist )
	{
		return NULL;
	}
	
	p_slist->head =(slist_node_t*)malloc(sizeof(slist_node_t));
	
	if ( NULL == p_slist->head )
	{
		free(p_slist);
		p_slist = NULL;
		return NULL;
	}
	
	p_slist->dummy =(slist_node_t*)malloc(sizeof(slist_node_t));
	
	if ( NULL == p_slist->dummy )
	{

		free(p_slist->head);
		free(p_slist);
		
		p_slist = NULL;
		p_slist->head = NULL;
		return NULL;
	}
	
	p_slist->head->data = NULL;
	p_slist->head->next = p_slist->dummy;
	
	p_slist->dummy->data = p_slist;
	p_slist->dummy->next = NULL;

	
	return 	p_slist;
}	

/********************  SlistIsEmpty  ****************************/
int SlistIsEmpty(const slist_t *slist)
{
	 assert(slist);	
	 return slist->dummy == slist->head->next;
}

/********************  SlistBegin  ****************************/
slist_iter_t SlistBegin(const slist_t *slist)
{
	assert(slist);
	return NodeToIter(slist->head->next);
}

/********************  SlistEnd  ****************************/
slist_iter_t SlistEnd(const slist_t *slist)
{
	assert(slist);
	return NodeToIter(slist->dummy);
}

/********************  SlistGetData  ****************************/
void *SlistGetData(slist_iter_t iter)
{
	assert(IterToNode(iter));
	return IterToNode(iter)->data;
}

/********************  SlistSetData  ****************************/ 
void SlistSetData(slist_iter_t iter, void *data)
{
	assert(data);
	assert(IterToNode(iter));
	
	IterToNode(iter)->data = data; 
}

/********************  SlistNext  ****************************/  
slist_iter_t SlistNext(slist_iter_t iter)
{
	assert(IterToNode(iter));
	return NodeToIter(IterToNode(iter)->next);
}

/********************  IsItrEqual  ****************************/   
int IsItrEqual(slist_iter_t iter1, slist_iter_t iter2)
{
	
	assert(IterToNode(iter1));
	assert(IterToNode(iter2));
	
	return iter1 == iter2;

}

/********************  SlistCount  ****************************/
size_t SlistCount(const slist_t *slist)
{
	size_t size = 0;

	SlistForEach(SlistBegin(slist), SlistEnd(slist),
	CountNodes, &size);
	
	return size; 
}

/********************  SlistDestroy  ****************************/
void SlistDestroy(slist_t *slist)
{
	slist_node_t* node = slist->head->next;
	slist_node_t* p_element;
	
	assert(slist);
	
	while( node != slist->dummy )
	{
		p_element = node;
		node = p_element->next;
		free(p_element);
	}
	
	free(slist->dummy);
	free(slist->head);
	free(slist);
	slist = NULL;
}


/******************  SlistInsertBefore  ***********************/
slist_iter_t SlistInsertBefore(slist_t *slist, slist_iter_t where,
								 const void *new_data)
{
	slist_node_t* new_node = (slist_node_t*)malloc(sizeof(slist_node_t));
	
	if ( NULL == new_node )
	{
		return SlistEnd(slist);
	}
	
	assert(slist); /*	assert(slist && where && new_data); */
	assert(IterToNode(where)); 
	new_node->data = SlistGetData(where);
	new_node->next = IterToNode(where)->next;
	
	IterToNode(where)->data = (void*)new_data;
	IterToNode(where)->next = new_node;
	
	if( NULL == new_node->next ) /* iter == dummy */
	{
		slist->dummy = new_node;
	}
	
	return where;
}								 
 
/********************  SlistRemove  ****************************/   
slist_iter_t SlistRemove(slist_iter_t what)
{
	slist_node_t* temp = NULL;
	assert(IterToNode(what));
	
	temp = IterToNode(SlistNext(what));
	IterToNode(what)->data = temp->data;
	IterToNode(what)->next = temp->next;

	if(NULL == SlistNext(what) )
	{
		((slist_t*)(IterToNode(what)->data))->dummy = IterToNode(what); 
	}
		
	free(temp);
	temp = NULL;
	
	return what;
}

/********************  SlistFind  ****************************/   

slist_iter_t SlistFind(slist_iter_t start, slist_iter_t end,
                       match_func_t match_function,
                       void *user_param)

{
	assert(IterToNode(start) && IterToNode(end) );
	assert(match_function); /* Add*/
	while(!IsItrEqual(start, end)) /* change while(start != end)  */
	{
	
		if(1 == match_function(SlistGetData(start), user_param))
		{
			return start;
		}
		
		start = SlistNext(start);
	}

	return end;
}

/********************  SlistForEach  **************************/   
int SlistForEach(slist_iter_t start, slist_iter_t end,
                 operation_func_t op_func, void *user_param)

{
	assert(IterToNode(start) && IterToNode(end) && user_param);
	
	while(!IsItrEqual(start, end))   /* change while(start != end)  */
	{
	
		if(op_func(SlistGetData(start), user_param))
		{
			return OPERATION_FAIL;
		}
		
		start = SlistNext(start);
	}

	return SUCCESS;
}                

/********************  SlistAppend  **************************/   
void SlistAppend(slist_t *dest, slist_t *src)
{
	
	assert(dest);
	assert(src);
	

	dest->dummy->data = src->head->next->data;
	dest->dummy->next = src->head->next->next;

	dest->dummy = src->dummy;
	dest->dummy->data = dest;
	
	src->head->next->next = NULL;
	src->head->next->data = src;
	src->dummy = src->head->next;
	
}

/*******************op_func to count *********************/
static int CountNodes (__attribute__((unused)) void *data,
                       void *user_param)
{
	
	(*(size_t*)user_param)++;
	return SUCCESS;
}




 

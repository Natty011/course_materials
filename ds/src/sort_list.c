/***************************************
* Author : Natty
* Reviewer : Matan
* Date : 22 / 12 / 2024
* Last update: 24 / 12 / 2024
*****************************************/

#include <assert.h> 	/* assert */
#include <stdlib.h> 	/* malloc, free */
#include "dlist.h" 
#include "sort_list.h" 

#define SRListToDList(sort_list) (sort_list->dlist)

/****************struct and enum declaration*********************/

struct sort_list
{

	dlist_t* dlist;
	cmp_func_t cmp_func;	

};

/** possible return values **/
typedef enum
{
	
	SUCCESS = 0,
	OPERATION_FAIL = 1
	
}dlistresult;

typedef enum
{
	
	FALSE = 0,
	TRUE = 1
	
}funcresult;

/***************End of struct and enum declaration *******/

/***********Functions declaration and definition*******/

/**********End of functions declaration and definition *******/

/********************  SortlistCreate  ****************************/
sort_list_t* SortlistCreate(cmp_func_t sort_func)
{

	sort_list_t* list = (sort_list_t*)malloc(sizeof(sort_list_t));
	
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dlist =  DListCreate();
	
	if(NULL == list->dlist)
	{
		free(list);
		list = NULL;
		return NULL;
	}

	list->cmp_func = sort_func;
	return list;

}

/********************  SortlistIsEmpty  ****************************/
int SortlistIsEmpty(const sort_list_t* sort_list)
{
	 assert(sort_list);	
	 return DListIsEmpty(SRListToDList(sort_list));
}

/********************  SortlistBegin  ****************************/
sort_list_iter_t SortlistBegin(const sort_list_t* sort_list)
{

	sort_list_iter_t itr;
		
	assert(sort_list);
	
	itr.iter = DListBegin(SRListToDList(sort_list));
	
	# ifndef NDEBUG
		itr.list = (sort_list_t*)sort_list;
	#endif
	 
	return itr;
}

/********************  SortlistEnd  ****************************/
sort_list_iter_t SortlistEnd(const sort_list_t* sort_list)
{
	
	sort_list_iter_t itr;
		
	assert(sort_list);
	
	itr.iter = DListEnd(SRListToDList(sort_list));
	
	# ifndef NDEBUG
		itr.list = (sort_list_t*)sort_list;
	#endif
	 
	return itr;

}

/********************  SortlistNext  ****************************/  
sort_list_iter_t SortlistNext(sort_list_iter_t iter)
{

	sort_list_iter_t itr; 
	itr.iter = DListNext(iter.iter); 
	
	# ifndef NDEBUG
		itr.list = iter.list;
		
	#endif
	
	return itr;
}

/********************  SortlistPrev  ****************************/  
sort_list_iter_t SortlistPrev(sort_list_iter_t iter)
{
	sort_list_iter_t itr; 
	itr.iter = DListPrev(iter.iter); 
	
	# ifndef NDEBUG
		itr.list = iter.list;

	#endif
	
	return itr;
}

/********************  SortlistIterIsEqual  ****************************/   
int SortlistIterIsEqual( sort_list_iter_t iter1 , sort_list_iter_t iter2 )
{
	
	int res = TRUE;
	
	# ifndef NDEBUG
		res = (iter1.list == iter2.list);
	#endif
	
	return res * DListIterIsEqual(iter1.iter, iter2.iter);
}

/********************  SortlistGetData  ****************************/
void* SortlistGetData(sort_list_iter_t iter)
{
	return DListGetData(iter.iter);
}


/********************  SortlistSize  ****************************/
size_t SortlistSize(const sort_list_t* sort_list)
{	
	assert(sort_list);	
		
	return DListCount(SRListToDList(sort_list));
}

/********************  SortlistDestroy  ****************************/
void SortlistDestroy( sort_list_t* sort_list )
{

	assert(sort_list);
	
	DListDestroy(SRListToDList(sort_list));
	free(sort_list);
	sort_list = NULL;
}


/********************  SortlistRemove  ****************************/ 
sort_list_iter_t SortlistRemove(sort_list_iter_t what )
{	
	sort_list_iter_t itr;
	
	# ifndef NDEBUG
		itr.list = what.list;
	#endif
	 
	itr.iter = DListRemove(what.iter); 	


		
	return itr; 	
}

/******************  SortlistInsert  ***********************/
sort_list_iter_t SortlistInsert(sort_list_t* sort_list ,const void *data)
{
	
	sort_list_iter_t next_iter;
	void* temp_data = NULL;
	int res_cmp = FALSE;
	
	assert(sort_list);
				
	next_iter = SortlistBegin(sort_list); 

	temp_data = SortlistGetData(next_iter);
	
	if( !SortlistIsEmpty(sort_list) )
	{
		res_cmp = sort_list->cmp_func(temp_data, (void*)data);
	}

	while( res_cmp <= FALSE &&  NULL != SortlistNext(next_iter).iter)
	{

		next_iter = SortlistNext(next_iter);
		temp_data = SortlistGetData(next_iter);
		res_cmp = sort_list->cmp_func(temp_data, (void*)data);	
		
	}
		
	next_iter.iter = DListInsertBefore(SRListToDList(sort_list),
							 next_iter.iter , data);
 								
	# ifndef NDEBUG
		next_iter.list = sort_list;
	#endif 	
  	
 	return next_iter;
 			
}

/********************  SortlistPopFront  ****************************/ 
void* SortlistPopFront( sort_list_t* sort_list )
{	
	assert(sort_list);
	
	return DListPopFront(SRListToDList(sort_list));	
}

/********************  SortlistPopBack  ****************************/ 

void* SortlistPopBack( sort_list_t* sort_list )
{
	assert(sort_list);
	
	return DListPopBack(SRListToDList(sort_list));	
 
}

/********************  SortlistForEach  **************************/ 
int SortlistForEach(sort_list_iter_t start, sort_list_iter_t end,
                     operation_func_t op_func ,void* user_param)
{
	
	assert(start.list == end.list);
	assert(op_func);
	
	return DListForEach(start.iter, end.iter, op_func, user_param);	
}                     

/********************  SortlistFindIf  **************************/ 

sort_list_iter_t SortlistFindIf( sort_list_iter_t start, sort_list_iter_t end,
                                match_func_t match_func , void* user_param )
{
	sort_list_iter_t itr;
		
	assert(start.list == end.list);
	
	assert(match_func);
			
	itr.iter = DListFind(start.iter, end.iter, match_func, user_param);

	# ifndef NDEBUG
		itr.list = start.list;
	#endif 
		
	return itr;
	
}

/********************  SortlistFind  ****************************/   
sort_list_iter_t SortlistFind(sort_list_t* sort_list , sort_list_iter_t start ,
                                  sort_list_iter_t end , void* user_param )
{		
	assert(start.list == end.list);
	assert(sort_list);	
	
	while(!SortlistIterIsEqual(start, end)) 
	{
	
		if(SUCCESS == sort_list->cmp_func(SortlistGetData(start), user_param))
		{
			return start;
		}
		
		start = SortlistNext(start);
	}

	return end;
	
} 

/********************  SortlistMerge  ****************************/   
void SortlistMerge(sort_list_t *dest, sort_list_t *src)
{
		
	sort_list_iter_t src_itr_from = SortlistBegin(src);
	sort_list_iter_t src_itr_from2 = SortlistBegin(src);

	sort_list_iter_t dest_itr_where = SortlistBegin(dest);
		
	void* src_temp_data = NULL;
	void* dest_temp_data = NULL;
	int res_cmp = FALSE;

	assert(dest);
	assert(src);
	assert(dest != src);

	src_temp_data = SortlistGetData(src_itr_from);
	dest_temp_data = SortlistGetData(dest_itr_where);
			
	res_cmp = dest->cmp_func(src_temp_data, dest_temp_data);
	/* src in not an Empty*/
	while( !SortlistIterIsEqual(src_itr_from, SortlistEnd(src) ) ) 
	{
		/* src_data(from) >= dest_data(where) */		
		if( res_cmp >= FALSE && 
			!SortlistIterIsEqual(SortlistEnd(dest), dest_itr_where ) )
		  
		{		
			dest_itr_where = SortlistNext(dest_itr_where);
			
			dest_temp_data = SortlistGetData(dest_itr_where);		

			res_cmp = dest->cmp_func(src_temp_data, dest_temp_data);
		}
		
		/* src_data(from) < dest_data(where) */		
		else
		{		
			src_itr_from2 = src_itr_from;
			src_itr_from = SortlistNext(src_itr_from);
				
			DListSplice(dest_itr_where.iter,
				src_itr_from2.iter, src_itr_from.iter);
			
			 
			if ( SortlistIterIsEqual((src_itr_from), SortlistEnd(src) ) ||
			     SortlistIterIsEqual(SortlistEnd(dest), dest_itr_where )	)		     
			 	
			{
				break;
			}

			dest_itr_where = SortlistNext(dest_itr_where);
				
		  	src_temp_data = SortlistGetData(src_itr_from);
		  	
		  	dest_temp_data = SortlistGetData(dest_itr_where);
	
		  	res_cmp = dest->cmp_func(src_temp_data, dest_temp_data);		  					 	
		}
	}
	
	/* If dest is empty and src is not */
	while( !SortlistIsEmpty(src) )
	{
			src_itr_from2 = src_itr_from;
			src_itr_from = SortlistNext(src_itr_from);
				
			DListSplice(dest_itr_where.iter,
				src_itr_from2.iter, src_itr_from.iter);
	}
	
}




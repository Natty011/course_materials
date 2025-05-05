static void AuxAVLDestroy(avl_t *tree, avl_node_t *node);



static void AuxAVLDestroy(avl_t *tree, avl_node_t *node)
{
	if( node != tree->root )
	{
		AuxAVLDestroy(tree, node->child[LEFT] );
		AuxAVLDestroy(tree, node->child[RIGHT] );
		
		free( node );
		node = NULL;
	}
}

static void AuxAVLDestroy(avl_node_t *node)
{
	assert ( node );
	
	if(NULL != node )
	{
		AuxAVLDestroy(node->child[LEFT] );
		AuxAVLDestroy(node->child[RIGHT] );
		
		free( node );
		node = NULL;
	}
}

void AVLDestroy(avl_t *tree)
{
	avl_node_t* curr_node = NULL;
	assert( tree );
	curr_node = tree->root ;
	
	if( NULL != curr_node )
	{
		puts("hi_4");
		AuxAVLDestroy( curr_node );
	}
	
	if( TRUE != AVLIsEmpty(tree) )
	{
		puts("hi_5");
	   destroy_check_avl = OPERATION_FAIL;
	}
	puts("hi_6");
	free(tree);
	tree = NULL;
	
}	

		res = tree->cmp_func( curr_node->data, new_data );
		parent = curr_node;
		what_child = res > 0 ? LEFT : RIGHT;
		
		 AuxAVLInsert(tree, curr_node->child[what_child], new_node,  new_data );
		/*
		if( res > 0 )
		{
			what_child = LEFT;
			 AuxAVLInsert(tree, curr_node->child[what_child],
									 new_node,  new_data );
									 
		    return;					 
		}	
		
		else if ( res < 0 )
		{
			what_child = RIGHT;
			 AuxAVLInsert(tree, curr_node->child[what_child],
								 new_node, new_data );
			return;					 
								 
		}
	}
	
	
	/*							 
		if( res > 0 )
		{
			what_child = LEFT;
			 AuxAVLInsert(tree, curr_node->child[what_child],
									 new_node,  new_data );
									 
		    return;					 
		}	
		
		else if ( res < 0 )
		{
			what_child = RIGHT;
			 AuxAVLInsert(tree, curr_node->child[what_child],
								 new_node, new_data );
			return;					 
								 
		}
		*/
		
		
/*printf(" node_1 = %p \n ", node);*/
		AuxAVLDestroy(tree, node->child[LEFT] );
		AuxAVLDestroy(tree, node->child[RIGHT] );
		/*
		if(node ==  tree->root )
		{
			tree->root = NULL;
		}
		*/
		
	what_child = (res > 0) ? LEFT : RIGHT;
		AuxAVLInsert(tree, curr_node->child[what_child],
									 new_node,  new_data );	
	
	
res = tree->cmp_func( curr_node->data, new_data );
		parent = curr_node;
		
		if( res > 0 )
		{
			what_child = LEFT;
			 AuxAVLInsert(tree, curr_node->child[what_child],
									 new_node,  new_data );
									 
		    return;					 
		}	
		
		else if ( res < 0 )
		{
			what_child = RIGHT;
			 AuxAVLInsert(tree, curr_node->child[what_child],
								 new_node, new_data );
			return;					 
								 
		}
	}
	
if(NULL != curr_node ) /* !AVLIsEmpty(tree) &&   */
	{
		res = tree->cmp_func( curr_node->data, new_data );
		parent = curr_node;
		
		what_child = res > 0 ? LEFT : RIGHT;
		AuxAVLInsert(tree, curr_node->child[what_child], new_node,  new_data );
	}
	
	
if(NULL != curr_node ) /* !AVLIsEmpty(tree) &&   */
	{
		res = tree->cmp_func( curr_node->data, new_data );
		parent = curr_node;
		
		what_child = res > 0 ? LEFT : RIGHT;
		AuxAVLInsert(tree, curr_node->child[what_child], new_node,  new_data );

	}	
	
if(NULL == curr_node ) /* !AVLIsEmpty(tree) &&   */
	{
		
		if( !AVLIsEmpty(tree) )
		{
			parent->child[what_child] = new_node;	
		}
	
		else 
		{
			tree->root = new_node;	
		}	
		
		new_node->child[LEFT] = NULL;
		new_node->child[RIGHT] = NULL;
		new_node->height = 0;
		
		return;
	}	
						

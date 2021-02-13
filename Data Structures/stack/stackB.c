/*
* File Name - stack.c
* Developer - Itay Adi Yosef
*/

/***********************************************************/
struct min_stack
	{
		stack_t *stack;
		stack_t *min_value_stack;
	};

/***********************************************************/

int min_stackPush(struct min_stack *stack_min, void *element)
{
	assert(stack_min);
	
 	if(*(int *)element < peek(*(int *)stack->min_value_stack))
	{
			if(!StackPush(stack->min_value_stack, element))
			{
				return (fail);
			}
	}

	if(!StackPush(stack_min->stack, element))
	{
		return (fail);
	}

	return (success);
}

/***********************************************************/

int *MinValue(struct min_stack *stack_min)
{
	return ((int *)peek(stack_min->min_value_stack));
}

/***********************************************************/

void min_StackPop(stack_t *stack_min)
{
	assert(stack_min);

	if(peek(stack_min->min_value_stack) == peek(stack_min->stack))
	{
		StackPop(stack_min->min_value_stack);
	}

	StackPop(stack_min->stack);
}

/***********************************************************/

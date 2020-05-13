#include "pile.h"

Stack *new_stack (Csg_node *node){
	if (node == NULL){
		fprintf(stderr, "Error: new_stack node.\n");
		exit(1);
	}
	Stack *stack_new = (Stack *) malloc(sizeof(Stack));
	if (stack_new == NULL){
		fprintf(stderr, "Error: new_stack stack_new.\n");
		exit(1);
	}
	stack_new->node = node;
	stack_new->next = NULL;
	return stack_new;
}


Stack *add_stack (Stack * stack, Csg_node *node){
	if (node == NULL){
		fprintf(stderr, "Error: add_stack node.\n");
		exit(1);
	}
	if (stack == NULL){
		return new_stack(node);
	}
	
	Stack *stack_add = (Stack *) malloc(sizeof(Stack));
	if (stack_add == NULL){
		fprintf(stderr, "Error: add_stack stack_add.\n");
		exit(1);
	}
	stack_add->node = node;
	stack_add->next = stack; 
	return stack_add;
}


Csg_node *pop_stack (Stack ** stack){
	if (stack == NULL && *stack == NULL){
		fprintf(stderr, "Error: pop_stack stack.\n");
		exit(1);
	}

	Csg_node *node = (*stack)->node;
	(*stack) = (*stack)->next;
	return node;
}

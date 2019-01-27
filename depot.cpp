#include <stdlib.h>
#include "depot.h"

struct DepotImplementation {
    Stack stack_of_stacks;
};

Depot create_depot() {
	Depot d = (Depot)smalloc(sizeof(DepotImplementation));
	d->stack_of_stacks = create_stack();
	return d;
}

void delete_depot(Depot depot) {
	while(get_count(depot->stack_of_stacks) != 0){
		delete_stack((Stack)pop_stack(depot->stack_of_stacks));
	}
	sfree(depot->stack_of_stacks);
	sfree(depot);
}

static void add_to_stack(Depot depot, Product *product);

void push_depot(Depot depot, Product *product) {
    if (get_count(depot->stack_of_stacks) == 0){
		add_to_stack(depot, product);
		return;
    }
	Stack curr = (Stack) peek_stack(depot->stack_of_stacks);
	if (get_count(curr) == STACK_SIZE_LIMIT){
		add_to_stack(depot, product);
		return;
	}
	push_stack(curr, product);
}

static void add_to_stack(Depot depot, Product *product) {
	Stack new_stack = create_stack();
	push_stack(new_stack, product);
	push_stack(depot->stack_of_stacks, new_stack);
}

int get_count(Depot depot) {
    return get_count(depot->stack_of_stacks);
}

Product* pop_depot(Depot depot) {
	if (get_count(depot->stack_of_stacks) == 0){
		return 0;
    }
	Stack curr_stack = (Stack) peek_stack(depot->stack_of_stacks);
	if (get_count(curr_stack) == 1) {
		curr_stack = (Stack) pop_stack(depot->stack_of_stacks);
		Product *prod = (Product*) pop_stack(curr_stack);
		delete_stack(curr_stack);
		return prod;
	}
	return (Product*) pop_stack(curr_stack);
}

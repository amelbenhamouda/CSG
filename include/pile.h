#ifndef __PILE__
#define __PILE__
#include <stdio.h>
#include <stdlib.h>

#include "csg.h"

typedef struct _stack_ {
    Csg_node *node;
    struct _stack_ *next;
} Stack;

/**
 * Créer une nouvelle pile.
 */
Stack *new_stack (Csg_node *node);

/**
 * Ajouter un objet à la pile.
 */
Stack *add_stack (Stack * stack, Csg_node *node);

/**
 * Supprimer le premier élément de la pile.
 */
Csg_node *pop_stack (Stack ** stack);

#endif

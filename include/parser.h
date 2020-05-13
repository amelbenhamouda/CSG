#ifndef __PARSER__
#define __PARSER__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pile.h"
#include "csg.h"

#define MAX_SIZE 1000

/*
 * Crée une sphére en fonction du fichier donné en argument.
 */
Object * parse_sphere(float* color);

/*
 * Crée une cube en fonction du fichier donné en argument.
 */
Object * parse_cube(float* color);

/*
 * Crée une cylindre en fonction du fichier donné en argument.
 */
Object * parse_cylindre(float* color);

/*
 * Crée une cone en fonction du fichier donné en argument.
 */
Object * parse_cone(float* color);

/*
 * Crée une tore en fonction du fichier donné en argument.
 */
Object * parse_tore(float* color);

/*
 * Crée la liste de couleur en fonction du fichier.
 */
float * parse_color(char *r, char *g, char *b, char *a);

/*
 * Ajoute une translation au noeud.
 */
void parse_translate(Csg_node *current_node, char *x, char *y, char *z);

/*
 * Ajoute une homothétie au noeud.
 */
void parse_homotate(Csg_node *current_node, char *x, char *y, char *z);

/*
 * Ajoute une rotation au noeud.
 */
void parse_rotate(Csg_node *current_node, char *axe, char *angle);

/*
 * Récupére chaque ligne du fichier et ajoute dans une pile chaque
 * élément (de la maniére d'une polonaise inverse).
 * Parse le fichier en argument.
 */
Csg_node * parse_file(FILE * file, float** final_color);

#endif

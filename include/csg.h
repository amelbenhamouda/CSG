#ifndef __CSG__
#define __CSG__

#include "object.h"

typedef struct _node_ {
    char ope; /* +,  -, *, ..., \0 */
    Object * obj; /*Objet canonique (feuille) ou null (noeud)*/
    bool neg; /*False par défaut, True si noeud = fils droit d'un '-'*/
    G3Xglmat * Md, * Mi, * Mn; /*Matrice directe, inverse, normale de translation et homothetie*/
    struct _node_ *fg, *fd; /*fils*/
} Csg_node;

/*
 * Initialise un noeud de l'arbre csg, par rapport à un objet donné
 */
Csg_node * init_node(char ope, Object * o);

/*
 * Affiche une matrice 4*4 dans le terminal
 */
void print_mat(G3Xglmat * mat);

/*
 * Ajoute une transformation "transform" à un noeud, en mettant à jour 
 * ses matrices directe, inverse et normale
 */
void add_transform(Csg_node * n, char transform, int axe, double angle, G3Xvector pt);

/*
 * Applique les transformations d'un noeud sur son objet en multipliant 
 * sa matrice directe sur tous les points de l'objet
 */
void transform(Csg_node * n);

/*
 * Regarde si un point est contenu dans un noeud en utilisant des opérateurs 
 * booléens pour représenter les différentes opérations ensemblistes
 */
bool pt_in_node(Csg_node * n, G3Xpoint * p);

/*
 * Dessine l'objet contenu dans un noeud donné
 */
void draw_node(Csg_node * n);

/*
 * Parcours l'arbre et pour tous les points de toutes les feuilles, fait 
 * des appels à pt_in_node sur la racine, pour voir si le point devra être
 * affiché au final, auquel cas le point est copié dans le noeud résultat, 
 * qui contiendra au final que les points valides
 */
void construct(Csg_node * result, long * i, Csg_node * target, Csg_node * targetdepart);

/*
 * Libere un noeud
 */
void free_node(Csg_node ** n);

#endif

#ifndef __OBJECT__
#define __OBJECT__

#include "transformation.h"
#include <math.h>

typedef struct _obj_ {
    int id;
    int N,P,NB_FACE; /*parametres annexes*/
    int size; /*Nombre total de points*/
    G3Xcolor c;
    G3Xcolor * color; /*Liste juste pour le résultat*/
    G3Xpoint * vertex; /*les sommets*/
    G3Xvector * normal; /*Leurs normales*/
    bool (*build)(struct _obj_ *); /*Constructeur*/
    bool (*pt_in)(G3Xpoint);
} Object;

/*
 * Retourne la valeur absolue d'une valeur donnée
 */
double ABS(double a);

/*
 * Construit une sphère canonique de façon regulière
 */
bool build_sphere_reg(Object *sphere);

/*
 * Construit un cube canonique de façon regulière
 */
bool build_cube_reg(Object *cube);

/*
 * Construit un cone canonique de façon regulière
 */
bool build_cone_reg(Object *cone);

/*
 * Construit un cylindre canonique de façon regulière
 */
bool build_cylindre_reg(Object *cylindre);

/*
 * Construit un tore canonique de façon regulière
 */
bool build_tore_reg(Object *tore);

/*
 * Initialise un objet avec une densité de n*p*nb_face, sa fonction de build et de pt_in
 */
Object * init_object(int n, int p, int nb_face, G3Xcolor c, bool (*b)(struct _obj_ *), bool (*ptin)(G3Xpoint));

/*
 * Initialise le noeud résultat
 * Initialisation différente car il n'a pas de fonction de build et de 
 * pt_in, et on ne peut pas savoir sa taille à l'avance
 */
Object * init_result(G3Xcolor c);

/*
 * Affiche dans le terminal les informations propres à un objet
 */
void print_object(Object * o);

/*
 * Retourne vrai si le point pt appartient à la sphère canonique
 */
bool pt_in_sphere(G3Xpoint pt);

/*
 * Retourne vrai si le point pt appartient au cube canonique
 */
bool pt_in_cube(G3Xpoint pt);

/*
 * Retourne vrai si le point pt appartient au cone canonique
 */
bool pt_in_cone(G3Xpoint pt);

/*
 * Retourne vrai si le point pt appartient au cylindre canonique
 */
bool pt_in_cylindre(G3Xpoint pt);

/*
 * Retourne vrai si le point pt appartient au tore canonique
 */
bool pt_in_tore(G3Xpoint pt);

/*
 *Libère un objet
 */
void free_obj(Object ** o);

#endif
#ifndef __TRANSFORMATIONS__
#define __TRANSFORMATIONS__

#include <g3x.h>

/*
 * Effectue la multiplication d'une matrice 4*4 par un point, et stock le résultat dans le point
 */
void dot(G3Xglmat * matrice, G3Xpoint * point);

/* 
 * Retourne la matrice identité: {1.,0.,0.,0.,0.,1.,0.,0.,0.,0.,1.,0.,0.,0.,0.,1.};
 */
G3Xglmat * get_mat_identite();

/*
 * Effectue la multiplication de deux matrices 4*4, et retourne le résultat
 */
G3Xglmat * merge_mat(G3Xglmat * matrice1, G3Xglmat * matrice2);

/*
 * Retourne la matrice de rotation directe associée à l'angle et l'axe donné
 */
G3Xglmat * get_rotate_matrice(int axe, double angle);

/*
 * Retourne la matrice de rotation inverse associée à l'angle et l'axe donné
 */
G3Xglmat * get_rotate_matrice_inv(int axe, double angle);

/*
 * Retourne la matrice de translation directe associée au point donné
 */
G3Xglmat * get_translate_matrice(G3Xvector pt);

/*
 * Retourne la matrice de translation inverse associée au point donné
 */
G3Xglmat * get_translate_matrice_inv(G3Xvector pt);

/*
 * Retourne la matrice d'homothétie directe associée au point donné
 */
G3Xglmat * get_homotate_matrice(G3Xvector pt);

/*
 * Retourne la matrice d'homothétie inverse associée au point donné
 */
G3Xglmat * get_homotate_matrice_inv(G3Xvector pt);

/*
 * Retourne la matrice d'homothétie des normales associée au point donné
 */
G3Xglmat * get_homotate_matrice_norm(G3Xvector pt);


#endif
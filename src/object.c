#include "../include/object.h"

double ABS(double a){
    if (a < ZERO){
        return -a;
    }  
    return a;
}


bool build_sphere_reg(Object *sphere){
    sphere->id = 0;
    /*Création des tableaux*/
    if(!(sphere->vertex = (G3Xpoint *)calloc(sphere->size, sizeof(G3Xpoint))))
        return false;
    if(!(sphere->normal = (G3Xvector *)calloc(sphere->size, sizeof(G3Xvector)))){
        free(sphere->vertex);
        return false;
    }

    double a = 2 * PI / sphere->N;
    double b = PI / sphere->P;
    G3Xpoint *V = sphere->vertex;
    int i, j;
    double cosa, sina;
    for (i = 0; i < sphere->N; i++){
        cosa = cos(i*a);
        sina = sin(i*a);
        for (j = 0; j < sphere->P; j++){
            (*V)[0] = cosa * sin(j * b);
            (*V)[1] = sina * sin(j * b);
            (*V)[2] = cos(j * b);
            V++;
        }
    }
    memcpy(sphere->normal, sphere->vertex, sphere->size * sizeof(G3Xpoint));
    return true;
}


bool build_cube_reg(Object *cube){
    cube->id = 0;
    /*Création des tableaux*/
    if(!(cube->vertex = (G3Xpoint *)calloc(cube->size, sizeof(G3Xpoint))))
        return false;
    if(!(cube->normal = (G3Xvector *)calloc(cube->size, sizeof(G3Xvector)))){
        free(cube->vertex);
        return false;
    }

    double n = cube->N;
    double p = cube->P;
    G3Xpoint *V = cube->vertex ; 
    int i, j;

    int x = 0;
    for (i = 0; i < cube->N; i++) {
        for (j = 0; j < cube->P; j++) {

            V[x + 0 * cube->size / 6][X] = 2. * i / n - 1;
            V[x + 0 * cube->size / 6][Y] = 2. * j / p - 1;
            V[x + 0 * cube->size / 6][Z] = 1;

            V[x + 1 * cube->size / 6][X] = 2. * i / n - 1;
            V[x + 1 * cube->size / 6][Y] = 2. * j / p - 1;
            V[x + 1 * cube->size / 6][Z] = -1;


            V[x + 2 * cube->size / 6][X] = 2. * i / n - 1;
            V[x + 2 * cube->size / 6][Y] = 1;
            V[x + 2 * cube->size / 6][Z] = 2. * j / p - 1;

            V[x + 3 * cube->size / 6][X] = 2. * i / n - 1;
            V[x + 3 * cube->size / 6][Y] = -1;
            V[x + 3 * cube->size / 6][Z] = 2. * j / p - 1;


            V[x + 4 * cube->size / 6][X] = 1;
            V[x + 4 * cube->size / 6][Y] = 2. * i / n - 1;
            V[x + 4 * cube->size / 6][Z] = 2. * j / p - 1;

            V[x + 5 * cube->size / 6][X] = -1;
            V[x + 5 * cube->size / 6][Y] = 2. * i / n - 1;
            V[x + 5 * cube->size / 6][Z] = 2. * j / p - 1;

            x++;
        }
    }

    int k, l;
    memcpy(cube->normal, cube->vertex, cube->size * sizeof(G3Xpoint));
    for(k = 0; k < cube->size; k++){
        for (l = 0; l < 3; l++){
            if(cube->normal[k][l] != -1 && cube->normal[k][l] != 1)
                cube->normal[k][l] = 0;
        }
    }
    return true;
}


bool build_cone_reg(Object *cone){ 
    if (! (cone->vertex = ((G3Xpoint*) calloc(cone->size, sizeof(G3Xpoint))))){
        return false;
    }
    if (! (cone->normal = ((G3Xvector*) calloc(cone->size, sizeof(G3Xvector))))){
        free(cone->vertex);
        return false;
    }

    G3Xpoint * v = cone->vertex;
    G3Xpoint * n = cone->normal;

    int cmpt = 0;
    double rayon;
    double x, y, z;
    double base_rayon = 1;
    double hauteur = 2;

    double ecartH = hauteur / cone->N; 
    double ecartR = base_rayon / cone->N * (2.0 * PI); 
    double ecartB = base_rayon / cone->N; 

    double i;

    for (i = ecartB; i < base_rayon; i += ecartB) {
        for (rayon = 0; rayon < 2.0 * PI * base_rayon; rayon += ecartR){
            v[cmpt][X] = cos(rayon) * i;
            v[cmpt][Y] = sin(rayon) * i;
            v[cmpt][Z] = 0;

            n[cmpt][X] = 0;
            n[cmpt][Y] = 0;
            n[cmpt][Z] = -1;

            cmpt++;
        }
    }

    double R = base_rayon;
    double currentR = base_rayon + ecartH / 2;

    for (z = 0; z < hauteur; z += ecartH) {
        currentR -= ecartH / 2 * base_rayon;
        for (rayon = 0; rayon < 2 * PI ; rayon += ecartR){
            v[cmpt][X] = cos(rayon) * currentR;
            v[cmpt][Y] = sin(rayon) * currentR;
            v[cmpt][Z] = z;

            n[cmpt][X] = cos(rayon) * currentR;
            n[cmpt][Y] = sin(rayon) * currentR;
            n[cmpt][Z] = 0;
            cmpt++;
        }
    }
    return true;
}


bool build_cylindre_reg(Object *cylindre){
    if (! (cylindre->vertex = ((G3Xpoint*) calloc(cylindre->size, sizeof(G3Xpoint))))){
        return false;
    }
    if (! (cylindre->normal = ((G3Xvector*) calloc(cylindre->size, sizeof(G3Xvector))))){
        free(cylindre->vertex);
        return false;
    }
    
    G3Xpoint *v = cylindre->vertex;  
    G3Xvector *n = cylindre->normal;

    int cmpt = 0;
    double rayon;
    double x, y, z;
    double base_rayon = 1.;
    double hauteur = 2.;
    double ecartH = hauteur / cylindre->N; /* ecart entre les cercles sur la hauteur */
    double ecartR = base_rayon / cylindre->N * (2.0 * PI); /* ecart entre les points sur les bords des cercles */
    double ecartIR = base_rayon / cylindre->N; /* ecart entre les cercles interieurs */
    double ir;

    /* création des cercles du haut et du bas (z = -1 et z = H-1) */
    for (ir = ecartIR; ir < base_rayon; ir += ecartIR) {
        for (rayon = 0; rayon < 2.0 * PI * base_rayon; rayon += ecartR){
            x = cos(rayon) * ir;
            y = sin(rayon) * ir;
            v[cmpt][X] = x;
            v[cmpt][Y] = y;
            v[cmpt][Z] = -1;

            n[cmpt][X] = 0;
            n[cmpt][Y] = 0;
            n[cmpt][Z] = -1;
            cmpt++;

            v[cmpt][X] = x;
            v[cmpt][Y] = y;
            v[cmpt][Z] = hauteur - 1;

            n[cmpt][X] = 0;
            n[cmpt][Y] = 0;
            n[cmpt][Z] = 1;
            cmpt++;
        }
    }

    /* création des contours de cercles sur toute la hauteur */
    for (z = -1; z < hauteur-1 + ecartH; z += ecartH) {
        for (rayon = 0; rayon < 2.0 * PI * base_rayon; rayon += ecartR){
            x = cos(rayon) * base_rayon;
            y = sin(rayon) * base_rayon;

            v[cmpt][X] = x;
            v[cmpt][Y] = y;
            v[cmpt][Z] = z;

            n[cmpt][X] = cos(rayon);
            n[cmpt][Y] = sin(rayon);
            n[cmpt][Z] = rayon / cylindre->P;
            cmpt++;
        }
    }
    return true;
}


bool build_tore_reg(Object *tore){ 
    int i,j;
    double a = 2 * PI / tore->N;
    double b =  2 * PI / tore->P;
    double rayon = 0.5; /* rayon du cercle */
    double r = 1; /* la distance entre le centre du tube et le centre du tore */

    if (! (tore->vertex = ((G3Xpoint*) calloc(tore->size, sizeof(G3Xpoint))))){
        return false;
    }
    if (! (tore->normal = ((G3Xvector*) calloc(tore->size, sizeof(G3Xvector))))){
        free(tore->vertex);
        return false;
    }

    G3Xpoint *vt = tore->vertex;  
    G3Xvector *vn = tore->normal;

    for(i = 0; i < tore->N; i++) {
        for (j = 0; j < tore->P; j++){
            (*vt)[X] = (r + (rayon * cos(j * a))) * cos(i * b);
            (*vt)[Y] = (r + (rayon * cos(j * a))) * sin(i * b);
            (*vt)[Z] = rayon * sin(j * a);

            (*vn)[X] = (*vt)[X];
            (*vn)[Y] = (*vt)[Y];
            (*vn)[Z] = (*vt)[Z];
            vn++;
            vt++;
        }
    }
    return true;
}


Object * init_object(int n, int p, int nb_face, G3Xcolor c, bool (*b)(struct _obj_ *), bool (*ptin)(G3Xpoint)){
    Object  * o = (Object *)malloc(sizeof(Object));
    o->N = n;
    o->P = p;
    o->NB_FACE = nb_face;
    o->size = o->N * o->P * o->NB_FACE;
    memcpy(o->c, c, 4 * sizeof(float));
    o->build = b;
    o->pt_in = ptin;
    o->build(o);
    return o;
}


Object * init_result(G3Xcolor c){
    Object  * o = (Object *)malloc(sizeof(Object));
    o->size = 0;
    if(c !=  NULL)
        memcpy(o->c, c, 4 * sizeof(float));
    else{
        memcpy(o->c, (G3Xcolor){-1., -1., -1., -1.}, 4 * sizeof(float));
    }
    o->vertex = (G3Xpoint*) calloc(o->size, sizeof(G3Xpoint));
    o->normal = (G3Xvector*) calloc(o->size, sizeof(G3Xvector));
    o->color = (G3Xcolor*) calloc(o->size, sizeof(G3Xcolor));
    return o;
}


void print_object(Object * o){
    printf("Objet: N:%d, P:%d, Nb_face:%d, size:%d\n", o->N, o->P, o->NB_FACE, o->size);
}


bool pt_in_sphere(G3Xpoint pt){
    return G3Xsqrnorm(pt) > 1. ? false : true;
}


bool pt_in_cube(G3Xpoint pt){
    return ABS(pt[X]) <= 1 && ABS(pt[Y]) <= 1 && ABS(pt[Z]) <= 1 ;
}


bool pt_in_cone(G3Xpoint pt){
    double base_rayon = 1.;
    double hauteur = 2.;

    G3Xpoint xy_pt;
    xy_pt[X] = pt[X];
    xy_pt[Y] = pt[Y];
    xy_pt[Z] = 0;

    double xy_dist = G3Xnorm(xy_pt);
    return 0 <= pt[Z] && pt[Z] < hauteur && xy_dist <= (1.0 - ((base_rayon/hauteur) * pt[Z]));
}


bool pt_in_cylindre(G3Xpoint pt){
    double base_rayon = 1.;
    double hauteur = 2.;

    G3Xpoint xy_pt;
    xy_pt[X] = pt[X];
    xy_pt[Y] = pt[Y];
    xy_pt[Z] = 0;

    return G3Xnorm(xy_pt) <= base_rayon && ABS(pt[Z]) <= hauteur / 2;
}


bool pt_in_tore(G3Xpoint pt){
    return ((pt[0] * pt[0] + pt[1] * pt[1] + pt[2] * pt[2] + 0.75) * (pt[0] * pt[0] + pt[1] * pt[1] + pt[2] * pt[2] + 0.75)) - 4 * (pt[0] * pt[0] + pt[1] * pt[1]) <= ZERO;
}


void free_obj(Object ** o){
    free((*o)->vertex);
    free((*o)->normal);
    free((*o));
    *o = NULL;
}
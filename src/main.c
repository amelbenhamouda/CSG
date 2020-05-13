#include <stdlib.h>
#include <stdio.h>
#include "../include/parser.h"

int n = 50;
char* filename;
float* final_color;
Csg_node *noeud, *result;


void Init(void){
    FILE* file = NULL;
    file = fopen(filename, "r+");

    if (file != NULL) { 
        noeud = parse_file(file, &final_color);

        fclose(file);
        transform(noeud);

        if (final_color != NULL){
        	result = init_node('\0', init_result(final_color));
	    }
	    else {
	    	result = init_node('\0', init_result(NULL));
	    }
	    long i = 0;
	    construct(result, &i, noeud, noeud);
    }
    else {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
} 


/* FONCTION DE DESSIN PRINCIPALE */
static void Draw(void){
	draw_node(result);
}


int main(int argc, char** argv){ 
    filename = argv[1];
    /* initialisation de la fenêtre graphique et paramétrage Gl */
    g3x_InitWindow(*argv,768,512);
    /* param. géométrique de la caméra. cf. gluLookAt(...) */
    g3x_SetPerspective(40.,100.,1.);
    /* position, orientation de la caméra */
    g3x_SetCameraSpheric(0.25*PI,+0.25*PI,6.,(G3Xpoint){0.,0.,0.});

    /* définition des fonctions */
    g3x_SetInitFunction(Init);     /* la fonction d'initialisation */
    g3x_SetDrawFunction(Draw);     /* la fonction de dessin        */
    g3x_SetAnimFunction(NULL);		 /* pas de fonction d'animation  */
    g3x_SetExitFunction(NULL);     /* pas de fonction de sortie    */
    g3x_SetScrollWidth(2);	
    g3x_CreateScrollv_i("n",&n,3,100,1.,"résolution");
    g3x_CreateScrollh_i("n",&n,3,100,1.,"résolution");

    /* boucle d'exécution principale */
    return g3x_MainStart();
    /* rien après ça */
}

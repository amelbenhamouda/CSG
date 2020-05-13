#include "../include/transformation.h"

void dot(G3Xglmat * matrice, G3Xpoint * point){
	int i, j;
	double cmpt;
	int taille_mat = 4;

	G3Xpoint tmp;
	for ( i = 0; i < taille_mat - 1; i++){
		tmp[i] = (*point)[i];
	}

	for (j = 0; j < taille_mat - 1; j++){
		cmpt = 0;
		for (i = 0; i < taille_mat; i++){
			if(i == (taille_mat - 1)){
				cmpt += (*matrice)[i + j * 4]; /*coordonnee homogene à 1.*/
			} else{
				cmpt += (*matrice)[i + j * 4] * tmp[i];
			}
		}
		(*point)[j] = cmpt;
	}
}


G3Xglmat * get_mat_identite(){
	G3Xglmat * mat = (G3Xglmat*)calloc(16, sizeof(double));
	int i;
	for(i = 0; i < 16; i++)
		if(i % 5 == 0)
			(*mat)[i] = 1.0;
	return mat;
}


G3Xglmat * merge_mat(G3Xglmat * matrice1, G3Xglmat * matrice2){
	int i, j, k;
	int taille_mat = 4;
	G3Xglmat * mat = (G3Xglmat*)calloc(16, sizeof(double));
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			for (k = 0; k < taille_mat; k++){
				(*mat)[j * taille_mat + i] += (*matrice1)[i + k * taille_mat] * (*matrice2)[j * taille_mat + k];
			}
		}
	}
	return mat;
}


G3Xglmat * get_rotate_matrice(int axe, double angle){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	angle *= DegToRad;

	/*Vérifications des positions des - sur les sin*/
	double valeurs[4] = {cos(angle), -sin(angle), sin(angle), cos(angle)};
	int next_val = 0;
	if(axe == Y){
		valeurs[1] *= -1;
		valeurs[2] *= -1;
	}

	/*Placement des des valeurs aux bons emplacements selon l'axe, dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if( (i == axe) || (j == axe) || (i == (taille_mat - 1)) || (j == (taille_mat - 1))){
				continue;
			}
			(*mat)[j * 4 + i] = valeurs[next_val];
			next_val += 1; 
		}
	}
	return mat;
}


G3Xglmat * get_rotate_matrice_inv(int axe, double angle){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	angle *= DegToRad;

	/*Vérifications des positions des - sur les sin*/
	double valeurs[4] = {cos(-angle), -sin(-angle), sin(-angle), cos(-angle)};
	int next_val = 0;
	if(axe == Y){
		valeurs[1] *= -1;
		valeurs[2] *= -1;
	}

	/*Placement des des valeurs aux bons emplacements selon l'axe, dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if( (i == axe) || (j == axe) || (i == (taille_mat-1)) || (j == (taille_mat-1))){
				continue;
			}
			(*mat)[j * 4 + i] = valeurs[next_val];
			next_val += 1; 

		}
	}
	return mat;
}


G3Xglmat * get_translate_matrice(G3Xvector pt){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	/*Placement des des valeurs aux bons emplacements dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if(i == 3 && j != 3){
				(*mat)[j * 4 + i] = pt[j];
			}
		}
	}
	return mat;
}


G3Xglmat * get_translate_matrice_inv(G3Xvector pt){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	/*Placement des des valeurs aux bons emplacements dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if(i == 3 && j != 3){
				(*mat)[j * 4 + i] = -pt[j];
			}
		}
	}
	return mat;
}


G3Xglmat * get_homotate_matrice(G3Xvector pt){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	/*Placement des des valeurs aux bons emplacements dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if(j == i && j != 3)
				(*mat)[j * 4 + i] = pt[j];
		}
	}
	return mat;
}


G3Xglmat * get_homotate_matrice_inv(G3Xvector pt){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	/*Placement des des valeurs aux bons emplacements dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if(j == i && j != 3)
				(*mat)[j * 4 + i] = 1./pt[j];
		}
	}
	return mat;
}


G3Xglmat * get_homotate_matrice_norm(G3Xvector pt){
	int i, j;
	G3Xglmat * mat = get_mat_identite();
	int taille_mat = 4;

	G3Xvector tmp;
	tmp[X] = pt[Y] * pt[Z];   tmp[Y] = pt[X] * pt[Z];   tmp[Z] = pt[X] * pt[Y];

	/*Placement des des valeurs aux bons emplacements dans la matrice*/
	for (j = 0; j < taille_mat; j++){
		for (i = 0; i < taille_mat; i++){
			if(j == i && j != 3)
				(*mat)[j * 4 + i] = tmp[j];
		}
	}
	return mat;
}

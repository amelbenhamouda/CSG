#include "../include/csg.h"

Csg_node * init_node(char ope, Object * o){
	Csg_node * n = (Csg_node *) malloc(sizeof(Csg_node));
	n->ope = ope;
    n->obj = o; 
    n->neg = false; 
    n->Md = get_mat_identite();
    n->Mi = get_mat_identite();
    n->Mn = get_mat_identite(); 
    n->fg = NULL;
    n->fd = NULL; 
    return n;
}


void print_mat(G3Xglmat * mat){
	int i;
	for(i = 0; i < 16; i++){
		if(i % 4 == 0)
			printf("\n");
		printf("%+2.2f ", (*mat)[i]);
	}
	printf("\n");printf("\n");
}


void add_transform(Csg_node * n, char transform, int axe, double angle, G3Xvector pt){
	if(n->ope == '\0'){
		G3Xglmat * matd;
		G3Xglmat * mati;
		G3Xglmat * matn;
		int i = 0;

		if(transform == 't'){
			matd = get_translate_matrice(pt);
			mati = get_translate_matrice_inv(pt);
			matn = get_mat_identite();
		}

		else if(transform == 'r'){
			matd = get_rotate_matrice(axe, angle);
			mati = get_rotate_matrice(axe, -angle);
			matn = get_rotate_matrice(axe, angle);
		}

		else if(transform == 'h'){
			matd = get_homotate_matrice(pt);
			mati = get_homotate_matrice_inv(pt);
			matn = get_homotate_matrice_norm(pt);
		}

		n->Md = merge_mat(n->Md, matd);
		n->Mi = merge_mat(mati, n->Mi);
		n->Mn = merge_mat(n->Mn, matn);
		return;
	}
	if(n->fg == NULL || n->fd == NULL){
		printf("ERREUR, noeud non binaire\n");
		return;
	}
	add_transform(n->fg, transform, axe, angle, pt);
	add_transform(n->fd, transform, axe, angle, pt);
}


void transform(Csg_node * n){
	if(n->ope == '\0'){
		int i = 0;
		for (i = 0; i < n->obj->size; i++) {
       		dot(n->Md, &(n->obj->vertex[i]));
        	dot(n->Mn, &(n->obj->normal[i]));
 	   	}
 	   	return;	
	}
	if(n->fg == NULL || n->fd == NULL){
		printf("ERREUR, noeud non binaire\n");
		return;
	}
	transform(n->fg);
	transform(n->fd);
}


bool pt_in_node(Csg_node * n, G3Xpoint * p){
	if(n->ope == '\0'){
		if(n->obj == NULL){
			printf("ERREUR, pas d'objet dans cette feuille\n");
			return false;
		}

		G3Xpoint p_tmp;
		p_tmp[X] = (*p)[X];
		p_tmp[Y] = (*p)[Y];
		p_tmp[Z] = (*p)[Z];

		dot(n->Mi, &p_tmp);

		return n->obj->pt_in(p_tmp);
	}
	if(n->fg == NULL || n->fd == NULL){
		printf("ERREUR, noeud non binaire\n");
		return false;
	}
	if (n->ope == '*'){
		return pt_in_node(n->fg, p) != pt_in_node(n->fd, p);
	}
	else if (n->ope == '-'){
		return pt_in_node(n->fg, p) && !pt_in_node(n->fd, p);
	}
	else if (n->ope == '+'){
		return pt_in_node(n->fg, p) && pt_in_node(n->fd, p);
	}
	printf("ERREUR, operateur inconnu\n");
	return false;
}


void draw_node(Csg_node * n){
	int i;
	glPointSize(2);
	if(n->obj->c[0] == -1){
		G3Xcolor previous = {-1., -1., -1., -1.};
		glBegin(GL_POINTS);
			for(i = 0; i < n->obj->size; i++){
				if((previous[0] != n->obj->color[i][0]) || (previous[1] != n->obj->color[i][1]) || (previous[2] != n->obj->color[i][2]) || (previous[3] != n->obj->color[i][3])){
					g3x_Material(n->obj->color[i], 0.25, 0.5, 0.5, 0.5, 1);
					memcpy(previous, n->obj->color[i], sizeof(G3Xcolor));
				}
				glNormal3dv(n->obj->normal[i]);
	        	glVertex3dv(n->obj->vertex[i]);
	        }
		glEnd();
	}
	else{
		g3x_Material(n->obj->c, 0.25, 0.7, 0.5, 0.5, 1);
		glBegin(GL_POINTS);
			for(i = 0; i < n->obj->size; i++){
        		glNormal3dv(n->obj->normal[i]);
	        	glVertex3dv(n->obj->vertex[i]);
	    	}
		glEnd();
	}
}


void construct(Csg_node * result, long * i, Csg_node * target, Csg_node * targetdepart){
	if(target->ope == '\0'){
		if((*i) + target->obj->size >= result->obj->size){
			result->obj->size = result->obj->size + target->obj->size;
			result->obj->vertex = ((G3Xpoint*) realloc(result->obj->vertex, result->obj->size * sizeof(G3Xpoint)));
			result->obj->normal = ((G3Xvector*) realloc(result->obj->normal, result->obj->size * sizeof(G3Xvector)));
			result->obj->color = ((G3Xcolor*) realloc(result->obj->color, result->obj->size * sizeof(G3Xcolor)));
		}
		G3Xpoint *Vt = target->obj->vertex;
		G3Xvector *Nt = target->obj->normal;

		while (Vt < target->obj->vertex + target->obj->size){
			if(pt_in_node(targetdepart, Vt)){
	        	memcpy(result->obj->normal[*i], *Nt, sizeof(G3Xvector));
	        	memcpy(result->obj->vertex[*i], *Vt, sizeof(G3Xpoint));
	        	memcpy(result->obj->color[*i], target->obj->c, sizeof(G3Xcolor));
	    	}
	    	(*i)++;
	    	Vt++;
	    	Nt++;
		}
		return;
	}
    if(target->fg == NULL || target->fd == NULL){
		printf("ERREUR, noeud non binaire\n");
		return;
	}
	construct(result, i, target->fg, targetdepart);
	construct(result, i, target->fd, targetdepart);	
}


void free_node(Csg_node ** n){
	if((*n)->fd != NULL)
		free_node(&((*n)->fd));
	if((*n)->fg != NULL)
		free_node(&((*n)->fg));
	if((*n)->obj != NULL)
		free_obj(&((*n)->obj));
	free((*n)->Md);
	free((*n)->Mi);
	free((*n)->Mn);
	free((*n));
	*n = NULL;
}
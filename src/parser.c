#include "../include/parser.h"

int densite = 450;

Object * parse_sphere(float* color){
	return init_object(densite, densite, 1, color, build_sphere_reg, pt_in_sphere);
}


Object * parse_cube(float* color){
	return init_object(densite, densite, 6, color, build_cube_reg, pt_in_cube);
}


Object * parse_cylindre(float* color){
	return init_object(densite, densite, 7, color, build_cylindre_reg, pt_in_cylindre);
}


Object * parse_cone(float* color){
	return init_object(densite, densite, 7, color, build_cone_reg, pt_in_cone);
}


Object * parse_tore(float* color){
	return init_object(densite, densite, 1, color, build_tore_reg, pt_in_tore);
}


float* parse_color(char *r, char *g, char *b, char *a){
	float *c = malloc(4 * sizeof(float));
	c[0] = atof(r);
	c[1] = atof(g);
	c[2] = atof(b);
	c[3] = atof(a);
	return c;
}


void parse_translate(Csg_node * current_node, char *x, char *y, char *z){
	float vect_x, vect_y, vect_z;
	vect_x = atof(x);
	vect_y = atof(y);
	vect_z = atof(z);
	add_transform(current_node, 't', 0, 0, (G3Xvector){vect_x, vect_y, vect_z});
}


void parse_homotate(Csg_node * current_node, char *x, char *y, char *z){
	float vect_x, vect_y, vect_z;
	vect_x = atof(x);
	vect_y = atof(y);
	vect_z = atof(z);
	add_transform(current_node, 'h', 0, 0, (G3Xvector){vect_x, vect_y, vect_z});
}


void parse_rotate(Csg_node * current_node, char *axe, char *angle){
	int axe_rotate = -1;
	if (strcmp(axe, "x") == 0){
		axe_rotate = 0;
	} else if (strcmp(axe, "y") == 0){
		axe_rotate = 1;
	} else if (strcmp(axe, "z") == 0){
		axe_rotate = 2;
	} else {
		fprintf(stderr, "Error: parse_rotate.\n");
		exit(1);
	}
	add_transform(current_node, 'r', axe_rotate, atoi(angle), NULL);
}


Csg_node * parse_file(FILE * file, float** final_color){
	char* line = (char *) malloc(MAX_SIZE);
	char* str = NULL;
	char *r, *g, *b, *a, *x, *y, *z, *axe, *angle;
	Csg_node *current_node = NULL;
	Stack *stack = NULL;
	float *color, *color_ope;
	while (fgets(line, MAX_SIZE, file) != NULL){
		if (strlen(line) < 0){
			return;
		}

		if ((str = strtok(line, ",")) == NULL) {
			fprintf(stderr, "Error: Syntax error str.\n");
			exit(1);
		}

		if (strcmp(str, "sph") == 0) { /* Sphere */
			/* Recupere la couleur */
			if ((r = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Sphere Syntax error r.\n");
				exit(1);
			}
			if ((g = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Sphere Syntax error g.\n");
				exit(1);
			}
			if ((b = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Sphere Syntax error b.\n");
				exit(1);
			}
			if ((a = strtok(NULL, ",")) == NULL) {
				fprintf(stderr, "Error: Sphere Syntax error a.\n");
				exit(1);
			}
			color = parse_color(r, g, b, a);

			current_node = init_node('\0', parse_sphere(color));
			while (str != NULL) { /* Pour recuperer le reste de la ligne  si existe */
				/* Recupere les transformations  */
				str = strtok(NULL, ":");
				if (str == NULL){
					break;
				}

				if (strcmp(str, "T") == 0) { /* Translate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Sphere Translate Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Sphere Translate Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Sphere Translate Syntax error z.\n");
						exit(1);
					}
					parse_translate(current_node, x, y, z);
				} else if (strcmp(str, "H") == 0){ /* Homotate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Sphere Homotate Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Sphere Homotate Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Sphere Homotate Syntax error z.\n");
						exit(1);
					}
					parse_homotate(current_node, x, y, z);
				} else if (strcmp(str, "R") == 0){ /* Rotate */
					/* Recupere le vecteur */
					if ((axe = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Sphere Rotate Syntax error axe.\n");
						exit(1);
					}
					if ((angle = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Sphere Rotate Syntax error angle.\n");
						exit(1);
					}
					parse_rotate(current_node, axe, angle);
				} else {
			   		fprintf(stderr, "Error: Sphere Unknown action transformations %s \n", str);
					exit(1);
				}
			}
			stack = add_stack(stack, current_node);

		} else if (strcmp(str, "cub") == 0) { /* Cube */
			/* Recupere la couleur */
			if ((r = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Cube Syntax error r.\n");
				exit(1);
			}
			if ((g = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Cube Syntax error g.\n");
				exit(1);
			}
			if ((b = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Cube Syntax error b.\n");
				exit(1);
			}
			if ((a = strtok(NULL, ",")) == NULL) {
				fprintf(stderr, "Error: Cube Syntax error a.\n");
				exit(1);
			}
			color = parse_color(r, g, b, a);

			current_node = init_node('\0', parse_cube(color));
			while (str != NULL) { /* Pour recuperer le reste de la ligne  si existe */
				/* Recupere les transformations  */
				str = strtok(NULL, ":");
				if (str == NULL){
					break;
				}
				/* printf("%s\n", strtok(NULL, ":"));*/
				if (strcmp(str, "T") == 0) { /* Translate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Cube Translate Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Cube Translate Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Cube Translate Syntax error z.\n");
						exit(1);
					}
					parse_translate(current_node, x, y, z);
				} else if (strcmp(str, "H") == 0){ /* Homotate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Cube Homotate Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Cube Homotate Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Cube Homotate Syntax error z.\n");
						exit(1);
					}
					parse_homotate(current_node, x, y, z);
				} else if (strcmp(str, "R") == 0){ /* Rotate */
					/* Recupere le vecteur */
					if ((axe = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Cube Rotate Syntax error axe.\n");
						exit(1);
					}
					if ((angle = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Cube Rotate Syntax error angle.\n");
						exit(1);
					}
					parse_rotate(current_node, axe, angle);
				} else {
			   		fprintf(stderr, "Error: Cube Unknown action transformations%s \n", str);
					exit(1);
				}
			}
			stack = add_stack(stack, current_node);

		} else if (strcmp(str, "cyl") == 0) { /* Cylindre */
			/* Recupere la couleur */
			if ((r = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error r.\n");
				exit(1);
			}
			if ((g = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error g.\n");
				exit(1);
			}
			if ((b = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error b.\n");
				exit(1);
			}
			if ((a = strtok(NULL, ",")) == NULL) {
				fprintf(stderr, "Error: Syntax error a.\n");
				exit(1);
			}
			color = parse_color(r, g, b, a);

			current_node = init_node('\0', parse_cylindre(color));
			while (str != NULL) { /* Pour recuperer le reste de la ligne  si existe */
				/* Recupere les transformations  */
				str = strtok(NULL, ":");
				if (str == NULL){
					break;
				}
				/* printf("%s\n", strtok(NULL, ":"));*/
				if (strcmp(str, "T") == 0) { /* Translate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error z.\n");
						exit(1);
					}
					parse_translate(current_node, x, y, z);
				} else if (strcmp(str, "H") == 0){ /* Homotate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error z.\n");
						exit(1);
					}
					parse_homotate(current_node, x, y, z);
				} else if (strcmp(str, "R") == 0){ /* Rotate */
					/* Recupere le vecteur */
					if ((axe = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error axe.\n");
						exit(1);
					}
					if ((angle = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error angle.\n");
						exit(1);
					}
					parse_rotate(current_node, axe, angle);
				}
				else {
			   		fprintf(stderr, "Error: Unknown action transformations%s \n", str);
					exit(1);
				}
			}
			stack = add_stack(stack, current_node);

		} else if (strcmp(str, "tor") == 0) { /* Tore */
			/* Recupere la couleur */
			if ((r = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error r.\n");
				exit(1);
			}
			if ((g = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error g.\n");
				exit(1);
			}
			if ((b = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error b.\n");
				exit(1);
			}
			if ((a = strtok(NULL, ",")) == NULL) {
				fprintf(stderr, "Error: Syntax error a.\n");
				exit(1);
			}
			color = parse_color(r, g, b, a);

			current_node = init_node('\0', parse_tore(color));
			while (str != NULL) { /* Pour recuperer le reste de la ligne  si existe */
				/* Recupere les transformations  */
				str = strtok(NULL, ":");
				if (str == NULL){
					break;
				}
				/* printf("%s\n", strtok(NULL, ":"));*/
				if (strcmp(str, "T") == 0) { /* Translate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error z.\n");
						exit(1);
					}
					parse_translate(current_node, x, y, z);
				} else if (strcmp(str, "H") == 0){ /* Homotate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error z.\n");
						exit(1);
					}
					parse_homotate(current_node, x, y, z);
				} else if (strcmp(str, "R") == 0){ /* Rotate */
					/* Recupere le vecteur */
					if ((axe = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error axe.\n");
						exit(1);
					}
					if ((angle = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error angle.\n");
						exit(1);
					}
					parse_rotate(current_node, axe, angle);
				} else {
			   		fprintf(stderr, "Error: Unknown action transformations%s \n", str);
					exit(1);
				}
			}
			stack = add_stack(stack, current_node);

		} else if (strcmp(str, "con") == 0) { /* Cone */
			/* Recupere la couleur */
			if ((r = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error r.\n");
				exit(1);
			}
			if ((g = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error g.\n");
				exit(1);
			}
			if ((b = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Syntax error b.\n");
				exit(1);
			}
			if ((a = strtok(NULL, ",")) == NULL) {
				fprintf(stderr, "Error: Syntax error a.\n");
				exit(1);
			}
			color = parse_color(r, g, b, a);

			current_node = init_node('\0', parse_cone(color));
			while (str != NULL) { /* Pour recuperer le reste de la ligne  si existe */
				/* Recupere les transformations  */
				str = strtok(NULL, ":");
				if (str == NULL){
					break;
				}

				if (strcmp(str, "T") == 0) { /* Translate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error z.\n");
						exit(1);
					}
					parse_translate(current_node, x, y, z);
				} else if (strcmp(str, "H") == 0){ /* Homotate */
					/* Recupere le vecteur */
					if ((x = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error x.\n");
						exit(1);
					}
					if ((y = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error y.\n");
						exit(1);
					}
					if ((z = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error z.\n");
						exit(1);
					}
					parse_homotate(current_node, x, y, z);
				} else if (strcmp(str, "R") == 0){ /* Rotate */
					/* Recupere le vecteur */
					if ((axe = strtok(NULL, ":")) == NULL) {
						fprintf(stderr, "Error: Syntax error axe.\n");
						exit(1);
					}
					if ((angle = strtok(NULL, ",")) == NULL) {
						fprintf(stderr, "Error: Syntax error angle.\n");
						exit(1);
					}
					parse_rotate(current_node, axe, angle);
				} else {
			   		fprintf(stderr, "Error: Unknown action transformations%s \n", str);
					exit(1);
				}
			}
			stack = add_stack(stack, current_node);

		} else if (strcmp(str, "+\n") == 0 || strcmp(str, "+") == 0) { /* Intersection */
			current_node = init_node('+', NULL);
		    current_node->fd = pop_stack(&stack);
		    current_node->fg = pop_stack(&stack);
		    stack = add_stack(stack, current_node);
		} else if (strcmp(str, "-\n") == 0 || strcmp(str, "-") == 0) { /* Soustraction */
			current_node = init_node('-', NULL);
		    current_node->fd = pop_stack(&stack);
		    current_node->fg = pop_stack(&stack);
		    stack = add_stack(stack, current_node);
		} else if (strcmp(str, "*\n") == 0 || strcmp(str, "*") == 0) { /* Union */
			current_node = init_node('*', NULL);
		    current_node->fd = pop_stack(&stack);
		    current_node->fg = pop_stack(&stack);
		    stack = add_stack(stack, current_node);
		} else {
			if ((r = strtok(str, ":")) == NULL) {
				fprintf(stderr, "Error: Last Syntax error r.\n");
				exit(1);
			}
			if ((g = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Last Syntax error g.\n");
				exit(1);
			}
			if ((b = strtok(NULL, ":")) == NULL) {
				fprintf(stderr, "Error: Last Syntax error b.\n");
				exit(1);
			}
			if ((a = strtok(NULL, "")) == NULL) {
				fprintf(stderr, "Error: Last Syntax error a.\n");
				exit(1);
			}
	   		*final_color = parse_color(r, g, b, a);
		}
	}
	return pop_stack(&stack);
}
#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include <math.h>

vector* vector_new(double a, double b, double c){
	printf("%f, %f, %f\n", a, b, c);
	vector* v = (vector*) malloc(sizeof(vector));
	v->x = a;
	v->y = b;
	v->z = c;

	return v;
}

vector* vector_add(vector* v1, vector* v2){
	vector* v = (vector*) malloc(sizeof(vector));
	v->x = v1->x + v2->x;
	v->y = v1->y + v2->y;
	v->z = v1->z + v2->z;

	return v;
}

vector* vector_sub(vector* v1, vector* v2){
	vector* v = (vector*) malloc(sizeof(vector));
	v->x = v1->x - v2->x;
	v->y = v1->y - v2->y;
	v->z = v1->z - v2->z;

	return v;
}

vector* vector_scale(double a, vector* v){
	v->x = v->x * a;
	v->y = v->y * a;
	v->z = v->z * a;

	return v;
}

vector* vector_vprod(vector* v1, vector* v2){
	vector* v= (vector*) malloc(sizeof(vector));

	v->x = v1->x * v2->x;
	v->y = v1->y * v2->y;
	v->z = v1->z * v2->z;

	return v;
}

double  vector_sprod(vector* v1, vector* v2){
	double a;
	double b;
	double c;

	a = v1->x * v2->x;
	b = v1->y * v2->y;
	c = v1->z * v2->z;
	c = c * b;
	c = c * a;

	return c;
}

double  vector_mod(vector* v){
	double a;
	double b;
	double c;

	a = v->x;
	b = v->y;
	c = v->z;

	c = fabs(c+a+b);

	return c;
}
/* definition of new type vector */
typedef struct {
double x;
double y;
double z;
} vector;

/* definition of the vector API */
vector* vector_new(double a, double b, double c);
vector* vector_add(vector* v1, vector* v2);
vector* vector_sub(vector* v1, vector* v2);
vector* vector_scale(double a, vector* v);
vector* vector_vprod(vector* v1, vector* v2);
double  vector_sprod(vector* v1, vector* v2);
double  vector_mod(vector* v);
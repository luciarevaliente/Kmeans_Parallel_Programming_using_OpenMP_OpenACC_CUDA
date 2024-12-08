#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

float stencil ( float v1, float v2, float v3, float v4 )
{
  return (v1 + v2 + v3 + v4) / 4;
}

void laplace_step ( float *in, float *out, int n, int m)
{
  int i, j;
  for ( i=1; i < n-1; i++ )
    for ( j=1; j < m-1; j++ )
      out[i*m+j]= stencil(in[i*m+j+1], in[i*m+j-1], in[(i-1)*m+j], in[(i+1)*m+j]);     
}

float laplace_error ( float *old, float *new, int n, int m )
{
  int i, j;
  float error=0.0f;
  for ( i=1; i < n-1; i++ )
    for ( j=1; j < m-1; j++ )
      error = fmaxf( error, sqrtf( fabsf( old[i*m+j] - new[i*m+j] )));
  return error;
}

void laplace_copy ( float *in, float *out, int n, int m )
{
  int i, j;
  for ( i=1; i < n-1; i++ )
    for ( j=1; j < m-1; j++ )
      out[i*m+j]= in[i*m+j];
}


void laplace_init ( float *in, int n, int m )
{
  int i, j;
  const float pi  = 2.0f * asinf(1.0f);
  memset(in, 0, n*m*sizeof(float));
  for (j=0; j<m; j++)  in[    j    ] = 0.f;
  for (j=0; j<m; j++)  in[(n-1)*m+j] = 0.f;
  for (i=0; i<n; i++)  in[   i*m   ] = sinf(pi*i / (n-1));
  for (i=0; i<n; i++)  in[ i*m+m-1 ] = sinf(pi*i / (n-1))*expf(-pi);
}

int main(int argc, char** argv) 
{ 
  int n = 4096, m = 4096; 
  const float pi  = 2.0f * asinf(1.0f); 
  const float tol = 3.0e-3f; 

  float error= 1.0f;; 

  int i, j, iter_max=100, iter=0; 
  float *A, *Anew;
    
  // get runtime arguments: n, m and iter_max
  if (argc>1) {  n        = atoi(argv[1]); }
  if (argc>2) {  m        = atoi(argv[2]); }
  if (argc>3) {  iter_max = atoi(argv[3]); }
  
  A    = (float*) malloc( n*m*sizeof(float) );
  Anew = (float*) malloc( n*m*sizeof(float) );

  // set boundary conditions 
  laplace_init (A, n, m);
  
  printf("Jacobi relaxation Calculation: %d rows x %d columns mesh,"
         " maximum of %d iterations\n",
         n, m, iter_max );

 
  // Main loop: iterate until error <= tol a maximum of iter_max iterations 
  while ( error > tol && iter < iter_max ) { 
    // Compute new values using main matrix and writing into auxiliary matrix 
    laplace_step (A, Anew, n, m);
    
    // Compute error = maximum of the square root of the absolute differences 
    error = 0.0f; 
    error = laplace_error (A, Anew, n, m);

    // Copy from auxiliary matrix to main matrix 
    laplace_copy (Anew, A, n, m);
    
    // if number of iterations is multiple of 10 then print error on the screen    
    iter++; 
    if (iter % (iter_max/10) == 0) 
       printf("%5d, %0.6f\n", iter, error);  
  } // while 
  
  free(A);
  free(Anew);
} 

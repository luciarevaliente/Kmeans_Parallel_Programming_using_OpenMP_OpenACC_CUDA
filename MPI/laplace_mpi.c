#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

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
  int world_size, rank; 
  float t0, t1;

  float error= 1.0f, error_global;

  int i, j, iter_max=100, iter=0;
  float *A, *Anew;
  
  MPI_Init (&argc, &argv);
  MPI_Status status;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  MPI_Comm_size (MPI_COMM_WORLD, &world_size);
  
  // get runtime arguments: n, m and iter_max
  if (argc>1) {  n        = atoi(argv[1]); }
  if (argc>2) {  m        = atoi(argv[2]); }
  if (argc>3) {  iter_max = atoi(argv[3]); }
  
  // Preparem matrius
  A    = (float*) malloc( n*m*sizeof(float) );
  Anew = (float*) malloc( n*m*sizeof(float) );
  
  
  // set boundary conditions
  laplace_init (A, n, m);
  
  if(rank == 0)
    printf("Jacobi relaxation Calculation: %d rows x %d columns mesh,"
         " maximum of %d iterations\n",
         n, m, iter_max );
  
  // Determinem posicio inicials i finals de cada proces
  int n_files = n/world_size;
  int first_row = rank*n_files;
  int final_row = (rank+1)*n_files -1;
  int posicio_inicial;
  if (rank==0){
    posicio_inicial = 0;
  }
  else{
    //Matriu emmagatzemada en MM de forma consecutiva
    posicio_inicial = m*(first_row-1);  
  }
  
  //printf("P: %d, rows: %d fr: %d, lr: %d, posin: %d\n", rank, n_files, first_row, final_row, posicio_inicial);
  
  if (rank==0){
    t0=MPI_Wtime();
  }
  
  // Main loop: iterate until error <= tol a maximum of iter_max iterations
  while ( error > tol && iter < iter_max ) {
    if (rank>0){
      //Li enviem la primera fila al proces anterior i rebem la ultima fila del proces anterior
      MPI_Send(&A[m*first_row], m, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD);
      MPI_Recv(&A[m*(first_row-1)], m, MPI_FLOAT, rank-1, 0, MPI_COMM_WORLD, &status);
    }
    
    if (rank<world_size-1){
      //Li enviem la ultima fila al seguent proces i rebem la primera fila del seguent proces
      MPI_Send(&A[m*final_row], m, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD);
      MPI_Recv(&A[m*(final_row+1)], m, MPI_FLOAT, rank+1, 0, MPI_COMM_WORLD, &status);
    }
    
    // Compute new values using main matrix and writing into auxiliary matrix
    laplace_step(A+posicio_inicial, Anew+posicio_inicial, n_files, m);
    
    // Compute error = maximum of the square root of the absolute differences
    error = laplace_error(A+posicio_inicial, Anew+posicio_inicial, n_files, m);
    MPI_Allreduce(&error, &error_global, 1, MPI_FLOAT, MPI_MAX, MPI_COMM_WORLD);
    error = error_global;
    
    // Copy from auxiliary matrix to main matrix
    laplace_copy(Anew+posicio_inicial, A+posicio_inicial, n_files, m);
    
    // if number of iterations is multiple of 10 then print error on the screen
    iter++;
    if (rank == 0 && iter % (iter_max/10) == 0)
       printf("%5d, %0.6f\n", iter, error);
    
  } // while
  
  if (rank==0){
    t1=MPI_Wtime();
    
    printf("El temps d'execucio es: %f\n", t1-t0);
  }
  
  free(A);
  free(Anew);

  MPI_Finalize();
} 

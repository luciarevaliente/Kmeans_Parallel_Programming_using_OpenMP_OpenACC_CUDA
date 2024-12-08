
# K-means Parallel Programming using OpenMP, OpenACC, CUDA, and MPI

This project is part of the Parallel Programming course (2023-24) and focuses on implementing the K-means clustering algorithm for pixel clustering in bitmap images using parallel programming techniques.

## Repository Contents

- **Source Code**: Implementation of the K-means algorithm in C.
- **Documentation**: Detailed explanations and instructions for compiling and running the code.
- **Performance Analysis**: Tools and scripts for analyzing the performance of the parallel implementations.

## Instructions

1. **Clone the repository**:
    ```bash
    git clone https://github.com/luciarevaliente/Kmeans_Parallel_Programming_using_OpenMP_OpenACC_CUDA.git
    cd Kmeans_Parallel_Programming_using_OpenMP_OpenACC_CUDA
    ```

2. **Compile the code**:
    ```bash
    make
    ```

3. **Run the K-means algorithm**:
    ```bash
    ./kmeans input_image.bmp
    ```

## Project Description

Final project for the Parallel Programming course (2023-24). The objective is to design and implement parallel versions of the K-means clustering algorithm to reduce the number of colors in a bitmap image. The project involves using different parallel programming approaches, including shared memory (OpenMP), accelerators (OpenACC/CUDA), and distributed memory (MPI).

### Key Features

- **K-means Algorithm**: An unsupervised machine learning algorithm used for clustering data points.
- **Pixel Clustering**: Application of K-means to group pixels in an image based on their RGB values.
- **Parallel Implementations**: Development of parallel versions using OpenMP, OpenACC, CUDA, and MPI to improve performance.
- **Performance Analysis**: Evaluation of the speedup and efficiency of the parallel implementations.

### Parallelization Methods

- **OpenMP**: Utilizes shared memory parallelism to distribute the workload across multiple CPU cores. This involves parallelizing loops and tasks to minimize execution time.
- **OpenACC**: Provides a high-level approach to parallelization, allowing code to be offloaded to GPUs with minimal changes.
- **CUDA**: Offers fine-grained control over GPU execution, enabling significant acceleration of compute-intensive parts of the algorithm.
- **MPI**: Uses distributed memory parallelism to enable communication between multiple processors across different nodes, allowing the algorithm to scale efficiently on large clusters.

## Contributions

This project is part of an academic course and does not accept external contributions.

## License

This project does not have a specific license and is for educational purposes only.

# Parallel K-means Clustering

This project is part of the Parallel Programming course (2023-24) and focuses on implementing the K-means clustering algorithm for pixel clustering in bitmap images using parallel programming techniques.

## Repository Contents

- **Source Code**: Implementation of the K-means algorithm in C.
- **Documentation**: Detailed explanations and instructions for compiling and running the code.
- **Performance Analysis**: Tools and scripts for analyzing the performance of the parallel implementations.

## Instructions

1. **Clone the repository**:
    ```bash
    git clone https://github.com/luciarevaliente/PP_GED_Practica_Kmeans_23_24.git
    cd PP_GED_Practica_Kmeans_23_24
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

Final project for the Parallel Programming course (2023-24). The objective is to design and implement parallel versions of the K-means clustering algorithm to reduce the number of colors in a bitmap image. The project involves using different parallel programming approaches, including shared memory (OpenMP) and accelerators (OpenACC/CUDA).

### Key Features

- **K-means Algorithm**: An unsupervised machine learning algorithm used for clustering data points.
- **Pixel Clustering**: Application of K-means to group pixels in an image based on their RGB values.
- **Parallel Implementations**: Development of parallel versions using OpenMP and OpenACC/CUDA to improve performance.
- **Performance Analysis**: Evaluation of the speedup and efficiency of the parallel implementations.

### Parallelization Methods

- **OpenMP**: Utilizes shared memory parallelism to distribute the workload across multiple CPU cores. This involves parallelizing loops and tasks to minimize execution time.
- **OpenACC/CUDA**: Uses accelerators such as GPUs to offload compute-intensive parts of the algorithm. OpenACC provides a high-level approach to parallelization, while CUDA allows for fine-grained control over GPU execution.

## Contributions

This project is part of an academic course and does not accept external contributions.

## License

This project does not have a specific license and is for educational purposes only.

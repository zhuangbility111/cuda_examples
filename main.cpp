#include <iostream>
#include <string>
#include <cuda_runtime.h>
#include "kernel.h"

// a CPU reduction function for testing
float cpu_reduction(const float* data, size_t size) {
    float sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum;
}

// fill the input data with random values
void fill_data(float* data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = static_cast<float>(rand()) / RAND_MAX;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number for reduction>" << std::endl;
        return 1;
    }

    size_t number = std::stoul(argv[1]);
    if (number < 0) {
        std::cerr << "Error: Number must be non-negative." << std::endl;
        return 1;
    }

    // check cuda device
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);
    if (deviceCount == 0) {
        std::cerr << "Error: No CUDA devices found." << std::endl;
        return 1;
    }
    cudaSetDevice(0); // Set to the first CUDA device
    std::cout << "Using CUDA device 0 for reduction." << std::endl;

    // allocate memory for input data
    float* data = new float[number];
    fill_data(data, number);
    std::cout << "Input data filled with random values." << std::endl;

    // allocate memory on the GPU
    float* d_data;
    cudaMalloc((void**)& d_data, number * sizeof(float));
    cudaMemcpy(d_data, data, number * sizeof(float), cudaMemcpyHostToDevice);
    std::cout << "Data copied to GPU." << std::endl;

    
}
#include <cuda_runtime.h>

template <int NUM_THREADS_PER_BLOCK>
__global__ void reduce_sum_v0(float *input, float *output, int n) {
    __shared__ float shared_data[NUM_THREADS_PER_BLOCK];
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tid = threadIdx.x;

    // load data to shared mem
    shared_data[tid] = input[idx];

    // sync
    __syncthreads();

    for (int stride = NUM_THREADS_PER_BLOCK; stride > 0; stride /= 2) {
        if (tid < stride) {
            shared_data[tid] += shared_data[tid + stride];
        }
        __syncthreads();
    }

    

}
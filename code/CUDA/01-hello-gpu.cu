#include <stdio.h>

void CPUFunction() {
  printf("Esta função está definida para ser executada na CPU.\n");
}

__global__ void GPUFunction() {
  printf("Esta função está definida para ser executada na GPU.\n");
}

int main() {
  CPUFunction();
  GPUFunction<<<1, 1>>>();
  cudaDeviceSynchronize();
  return 0;
}
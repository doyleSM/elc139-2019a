%%writefile testdims.cu
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "wave.h"
​
__global__
void gerarFrames(int width, int frames, unsigned char* pic){
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;

  for (int frame = 0; frame < frames; frame++) {
    for (int row = index; row < width; row += stride) {
      for (int col = 0; col < width; col++) {
        float fx = col - 1024/2;
        float fy = row - 1024/2;
        float d = sqrtf( fx * fx + fy * fy );
        unsigned char color = (unsigned char) (160.0f + 127.0f *
                                          cos(d/10.0f - frame/7.0f) /
                                          (d/50.0f + 1.0f));
        pic[frame * width * width + row * width + col] = (unsigned char) color;
      }
    }
  }
}
​
int main(int argc, char *argv[])
{
​
  if (argc != 3) {
    printf("ERRO: usar %s largura_frame num_frames\n", argv[0]);
    exit(-1);
  }
  int width = atoi(argv[1]);
  if (width < 100) {
    printf("ERRO: largura_frame deve ser maior igual a 100\n");
    exit(-1);
  }
  int frames = atoi(argv[2]);
  if (frames < 1) {
    printf("ERRO: num_frames deve ser pelo menos 1\n");
    exit(-1);
  }
  printf("Computando %d frames de dimensão %d por %d\n", frames, width, width);
​
  unsigned char* pic;
  cudaMallocManaged(&pic, frames*width*width*sizeof(unsigned char));
    
  // inicia tempo
  timeval start, end;
  gettimeofday(&start, NULL);
  int blockSize = 512;
  int numBlocks = (width + blockSize) / blockSize;
  gerarFrames<<<numBlocks, blockSize>>>(width,frames, pic);
​
  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();
​
  // termina o tempo
  gettimeofday(&end, NULL);
  double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
  printf("compute time: %.4f s\n", runtime);
​
  cudaFree(pic);
  return 0;
}
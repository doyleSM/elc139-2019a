%%writefile testdims.cu
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "wave.h"
​
__global__
void gerarFrames(int width, unsigned char* pic){
    
    for (int row = 0; row < width; row++) {
      for (int col = 0; col < width; col++) {
        float fx = col - 1024/2;
        float fy = row - 1024/2;
        float d = sqrtf( fx * fx + fy * fy );
        unsigned char color = (unsigned char) (120.0f + 127.0f *
                                          cos(d/10.0f - threadIdx.x/7.0f) /
                                          (d/50.0f + 1.0f));
        pic[threadIdx.x * width * width + row * width + col] = (unsigned char) color;
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
  int threads = frames;
  gerarFrames<<<1, threads>>>(width, pic);
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
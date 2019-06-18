#include <iostream>
#include <sys/time.h>
#include <math.h>

__global__
void calculate(int width, int frames, unsigned char* pic)
{
  //Indice de segmento dentro do bloco
  int index = threadIdx.x;

  //This variable and contains the dimensions of the block.
  int offset = blockDim.x;

  for (int frame = index; frame < frames; frame += offset) {
    for (int row = 0; row < width; row++) {
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

int main(int argc, char *argv[])
{

  // check command line
  if (argc != 3) {
    std::cout << "usage: " << std::endl;
     exit(-1);
  }
  int width = atoi(argv[1]);
  if (width < 100) {
    std::cout << "error: frame_width must be at least 100\n" << std::endl;
    exit(-1);
  }
  int frames = atoi(argv[2]);
  if (frames < 1) {
    std::cout << "error: num_frames must be at least 1\n" << std::endl; 
    exit(-1);
  }
  std::cout << "computing  " << std::cout << frames << " of " std::cout << " picture " << std::cout << width  << std::cout << " picture "  << std::endl;
  //printf("computing %d frames of %d by %d picture\n", frames, width, width);


  unsigned char* pic;

  //Allocating Unified Memory is as simple as replacing calls to malloc() or new with calls to cudaMallocManaged(), an allocation function that   returns a pointer accessible from any processor (ptr in the following).
  cudaMallocManaged(&pic, frames*width*width*sizeof(unsigned char));
    
  // start time
  timeval start, end;
  gettimeofday(&start, NULL);

  // calculate threads for frames
  calculate<<<1, frames>>>(width, frames, pic);

  // cudaDeviceSynchronize() will force the program to ensure the stream(s)'s kernels/memcpys are complete before continuing
  cudaDeviceSynchronize();

  // end time
  gettimeofday(&end, NULL);
  double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
  std::cout<< "compute time: " << runtime << std::endl;

  // verify result by writing frames to BMP files
  //if ((width <= 256) && (frames <= 100)) {
  //  for (int frame = 0; frame < frames; frame++) {
  //    char name[32];
  //  //  sprintf(name, "wave%d.bmp", frame + 1000);
  //   // writeBMP(width, width, &pic[frame * width * width], name);
  //  }
  //}
  cudaFree(pic);
  return 0;
}

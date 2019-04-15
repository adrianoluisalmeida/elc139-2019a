#include <omp.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sys/time.h>
#include "fractal/fractal.h"

static const double Delta = 0.001;
static const double xMid =  0.23701;
static const double yMid =  0.521;
//static const int nThreads = 2;

bool check_command_line(int argc, char *argv[], int width, int frames){
    
    if (argc != 4) {
        fprintf(stderr, "usage: %s frame_width num_frames\n", argv[0]); 
        return false;
    }
    if (width < 10) {
        fprintf(stderr, "error: frame_width must be at least 10\n");
        return false;
    }
  
    if (frames < 1) {
        fprintf(stderr, "error: num_frames must be at least 1\n");
        return false;
    }
    
  //  printf("computing %d frames of %d by %d fractal\n", frames, width, width);
    return true;
}

void countTime(timeval start, timeval end){
    double runtime = end.tv_sec + end.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;
    printf("%.4f\n", runtime);
}

int main(int argc, char *argv[])
{
  //printf("Fractal v1.6 [serial]\n");
  int width = atoi(argv[1]);
  int frames = atoi(argv[2]);
  int threads = atoi(argv[3]);
  int frame, col, row;
  int nThreads = threads;
  int chuck_size = frames / nThreads;

  // check command line
  if(!check_command_line(argc, argv, width, frames))
    exit(-1);

  // allocate picture array
  unsigned char* pic = new unsigned char[frames * width * width];

  // start time
  timeval start, end;
  gettimeofday(&start, NULL);

  // compute frames
    double delta = Delta;
    #pragma omp parallel private(col, row, frame) shared(pic) num_threads(nThreads)
    {
        
        #pragma omp for schedule(dynamic)

        for (frame = 0; frame < frames; frame++) {
          const double xMin = xMid - delta;
          const double yMin = yMid - delta;
          const double dw = 2.0 * delta / width;
          for (row = 0; row < width; row++) {
            const double cy = yMin + row * dw;
            for (col = 0; col < width; col++) {
              const double cx = xMin + col * dw;
              double x = cx;
              double y = cy;
              int depth = 256;
              double x2, y2;
              do {
                x2 = x * x;
                y2 = y * y;
                y = 2 * x * y + cy;
                x = x2 - y2 + cx;
                depth--;
              } while ((depth > 0) && ((x2 + y2) < 5.0));
        
        
             // int chunk_size = 20;
              
        
              //check_schedule();
            //  #pragma omp parallel num_threads(nThreads)
             // {
                  pic[frame * width * width + row * width + col] = (unsigned char)depth;
             // }
              
            }
          }
          delta *= 0.98;
        }
    }
  // end time
  gettimeofday(&end, NULL);
  countTime(start, end);
  

  // verify result by writing frames to BMP files
  if ((width <= 256) && (frames <= 100)) {
    for (int frame = 0; frame < frames; frame++) {
      char name[32];
      sprintf(name, "fractal%d.bmp", frame + 1000);
      writeBMP(width, width, &pic[frame * width * width], name);
    }
  }

  delete [] pic;
  return 0;
}
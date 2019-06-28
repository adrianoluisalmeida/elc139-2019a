CXX       = g++
CXXFLAGS  = -Wall -O3 -std=c++11 -fopenmp

PROGRAM   = mandelbrot
SRCS      = mandelbrot.cpp
OBJS      = $(SRCS:.cpp=.o)
RM        = rm -f


$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(SRCS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(PROGRAM)
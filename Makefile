NVCC = nvcc
CXXFLAGS = -std=c++11
NVCCFLAGS = $(CXXFLAGS) -O2 -arch=sm_50
TARGET = my_program

all: $(TARGET)

$(TARGET): kernel.cu main.cpp
	$(NVCC) $(NVCCFLAGS) kernel.cu main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
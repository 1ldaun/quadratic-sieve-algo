CXXFLAGS=-O3 -std=gnu++0x -Wall -pedantic
LDFLAGS=-O3
LIBS=-lgmpxx -lgmp

all: factor

factor: main.cpp qs.cpp 
	$(CXX) -c $(CXXFLAGS) -o main.o main.cpp
	$(CXX) $(LDFLAGS) -o factor main.cpp qs.cpp matrix.cpp gf/GaloisField.cpp gf/GaloisFieldElement.cpp gf/GaloisFieldPolynomial.cpp $(LIBS)

clean:
	-@rm *.o factor 2> /dev/null || true

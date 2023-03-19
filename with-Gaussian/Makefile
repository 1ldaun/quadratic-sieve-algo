CXXFLAGS=-O2 -std=gnu++0x -Wall -pedantic
LDFLAGS=-O2
LIBS=-lgmpxx -lgmp

all: factor

factor: main.cpp qs.o gf.o gf_element.o gf_polynomial.o
	$(CXX) -c $(CXXFLAGS) -o main.o main.cpp
	$(CXX) $(LDFLAGS) -o factor main.o qs.o gf/gf.o gf/gf_element.o gf/gf_polynomial.o $(LIBS)

qs.o: qs.cpp qs.h matrix.h
	$(CXX) -c $(CXXFLAGS) -o qs.o qs.cpp

gf.o: gf/GaloisField.cpp gf/GaloisField.h
	$(CXX) -c $(CXXFLAGS) -o gf/gf.o gf/GaloisField.cpp

gf_element.o: gf/GaloisFieldElement.cpp
	$(CXX) -c $(CXXFLAGS) -o gf/gf_element.o gf/GaloisFieldElement.cpp

gf_polynomial.o: gf/GaloisFieldPolynomial.cpp
	$(CXX) -c $(CXXFLAGS) -o gf/gf_polynomial.o gf/GaloisFieldPolynomial.cpp

clean:
	-@rm *.o factor 2> /dev/null || true

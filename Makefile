all: long_multiply.cpp karatsuba_multiply.cpp
	g++ -o longmultiplication long_multiply.cpp
	g++ -o karatsuba karatsuba_multiply.cpp


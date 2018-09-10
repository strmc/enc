all:enc
enc:enc.cpp
	g++ enc.cpp enc.h -o enc
clean:
	rm -f enc

all:enc
enc:enc.cpp
	g++ enc.cpp enc.h -o enc -lstdc++fs
clean:
	rm -f enc

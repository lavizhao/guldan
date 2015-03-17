ftrl : amath.o fc.o sp.o lr.o cmd.o main.o rand.o
	g++ main.o amath.o fc.o sp.o lr.o cmd.o rand.o -o ftrl.out -O3
	rm *.o 

main.o : ftrl/lr.cpp ftrl/lr.h util/cmdline.h
	g++ -c ftrl/ftrl.cpp -o main.o -O3

amath.o : util/amath.cpp util/amath.h
	g++ -c util/amath.cpp -o amath.o -O3

fc.o : util/file_control.cpp util/file_control.h
	g++ -c util/file_control.cpp -o fc.o -O3

sp.o : util/sparse_vector.cpp util/sparse_vector.h util/random.h
	g++ -c util/sparse_vector.cpp -o sp.o -O3

cmd.o : util/cmdline.cpp util/cmdline.h util/string_util.h
	g++ -c util/cmdline.cpp -o cmd.o -O3

lr.o : ftrl/lr.cpp ftrl/lr.h util/sparse_vector.h util/string_util.h util/file_control.h util/amath.h util/random.h
	g++ -c ftrl/lr.cpp -o lr.o -O3

rand.o : util/random.h util/random.cpp
	g++ -c util/random.cpp -o rand.o -O3

clean :
	rm *.o *.out

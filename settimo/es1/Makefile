LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

prova : prova.cpp funzioni.h
	g++ -o prova prova.cpp  ${INCS} ${LIBS}



clean:
	rm prova
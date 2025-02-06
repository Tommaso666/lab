LIBS:=`root-config --libs`
INCS:=`root-config --cflags`

prova : prova.cpp funzioni.h vectorop.h differenziare.h random.h
	g++ -o prova prova.cpp  ${INCS} ${LIBS}



clean:
	rm prova
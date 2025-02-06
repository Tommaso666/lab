
CFLAGS := `root-config --cflags` -fopenmp 

LIBS := `root-config --libs` -fopenmp

prova: prova.cpp funzioni.h vectorop.h differenziare.h random.h funzionivector.h
	g++ -o prova prova.cpp ${CFLAGS} ${LIBS}

clean:
	rm prova

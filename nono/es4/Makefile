# Aggiungi -fopenmp a CFLAGS per la compilazione
CFLAGS := `root-config --cflags` -fopenmp
# Aggiungi -fopenmp a LIBS per il linking
LIBS := `root-config --libs` -fopenmp

prova: prova.cpp funzioni.h vectorop.h differenziare.h random.h funzionivector.h
	g++ -o prova prova.cpp ${CFLAGS} ${LIBS}

clean:
	rm prova

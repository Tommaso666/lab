# Aggiungi -fopenmp a CFLAGS per la compilazione
CFLAGS := `root-config --cflags` -fopenmp
# Aggiungi -fopenmp a LIBS per il linking
LIBS := -ltbb `root-config --libs` -fopenmp


prova : prova.cpp funzioni.h integratori.h rand.h vectorop.h prisma.h
	g++ -o prova prova.cpp ${CFLAGS} ${LIBS}

clean:
	rm prova
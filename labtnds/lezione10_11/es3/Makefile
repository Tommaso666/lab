CFLAGS := `root-config --cflags` -fopenmp
LIBS := `root-config --libs` -fopenmp

# Lista dei file sorgenti e degli eseguibili
SOURCES := main1.cpp main2.cpp
EXECUTABLES := main1 main2

# Regola generale per compilare entrambi
all: $(EXECUTABLES)

# Regola generica per compilare ogni eseguibile
%: %.cpp funzioni.h vectorop.h differenziare.h random.h funzionivector.h
	g++ -o $@ $< ${CFLAGS} ${LIBS}

# Pulizia dei file generati
clean:
	rm -f $(EXECUTABLES)

#variables de compilation
CC=g++
CFLAGS=-Wall 
LDFLAGS=
EXEC=projet

#variable de documentation
DOC=doxygen
DOCSETUP=DoxyMake.mk
DOCERR=DoxyLog.err

#compilation
all: ./bin/$(EXEC)

./bin/$(EXEC): ./obj/main.o ./obj/graphe.o
	$(CC) -o $@ $^ $(LDFLAGS)


./obj/graphe.o: ./src/graphe.cpp
	$(CC) -o $@ -c $< $(CFLAGS)



./obj/main.o: ./src/main.cpp ./src/graphe.h
	$(CC) -o $@ -c $< $(CFLAGS)


#documentation
.PHONY: doc
doc :
	$(DOC) ./$(DOCSETUP) 2>./doc/$(DOCERR)


#nettoyeur
clean:
	rm -rf ./obj/*.o
	rm -rf ./doc/$(DOCERR)

mrproper: clean
	rm -rf ./bin/*
	rm -rf ./doc/*

#help
help:	
	@echo 
	@echo Les commandes utiles :
	@echo
	@echo make : Compile le programme $(EXEC) dans le répertoire bin.
	@echo make doc : Génère la documentation dans le répertoire doc avec $(DOC).
	@echo
	@echo
	@echo Les commandes de nettoyage : 
	@echo
	@echo make clean : Supprime les fichiers objets, et le fichier $(DOCERR).
	@echo make mrproper : Execute clean, supprime $(EXEC) et la documentation.
	@echo
	@echo
	@echo N\'hésitez pas à consulter le readme.txt !
	@echo


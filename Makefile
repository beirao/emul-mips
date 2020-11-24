
CC = gcc
CFLAGS = -g -W -Wall -ansi -pedantic
LDFLAGS = -lm
EXEC = emul_mips #UNIQUE CHANGEMENT A FAIRE EN FONCTION DU NOM VOULU POUR L'EXECUTABLE
SRC = $(wildcard $(code)/*.c) #liste de nos fichiers sources générée automatiquement (faire attention aux dépendances de ces .c)
H = $(wildcard $(header)/*.h) #liste de nos fichiers .h générée automatiquement
OBJ = $(SRC:.c=.o) #génération automatique de la liste des fichiers objets à partir de la liste des fichiers sources


all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: $(H) #déclaration des dépendances (ici tous les .o dépendent de tous les .h)

%.o: %.c #règle générique pour la construction d'un .o à partir d'un .c)
	@$(CC) -o $@ -c $< $(CFLAGS)


.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
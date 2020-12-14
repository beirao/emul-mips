CODEDIR = code
HEADERDIR = header


CC = gcc
CFLAGS = -g -W -Wall -ansi -pedantic -Iheader -Wextra 
LDFLAGS = -lm
EXEC = emul_mips #UNIQUE CHANGEMENT A FAIRE EN FONCTION DU NOM VOULU POUR L'EXECUTABLE
SRC = $(wildcard $(CODEDIR)/*.c) #liste de nos fichiers sources générée automatiquement (faire attention aux dépendances de ces .c)
H = $(wildcard $(HEADERDIR)/*.h) #liste de nos fichiers .h générée automatiquement
OBJ = $(SRC:$(CODEDIR)/%.c=./%.o) #génération automatique de la liste des fichiers objets à partir de la liste des fichiers sources


all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: $(CODEDIR)/%.c $(H)   #règle générique pour la construction d'un .o à partir d'un .c)
	@$(CC) -o $@ -c $< $(CFLAGS)


.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)

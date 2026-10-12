# Pipex

Pipex est un projet de l'école 42 qui reproduit le comportement de la commande shell suivante :

```bash
< infile cmd1 | cmd2 > outfile
```

Le programme lit un fichier d'entrée, exécute deux commandes reliées par un pipe, puis écrit le résultat dans un fichier de sortie.

## Objectif

L'objectif est de manipuler :

- les processus fils avec `fork`
- les pipes avec `pipe`
- la redirection des entrées et sorties avec `dup2`
- la recherche d'exécutables dans le `PATH`
- la gestion d'erreurs système

## Structure

- `main.c` : gestion des descripteurs, création des fils et lancement des commandes
- `pipex.h` : déclarations du projet
- `utils/` : fonctions utilitaires liées à l'exécution des commandes
- `libft/` : bibliothèque locale utilisée par le projet

## Compilation

Depuis la racine du projet :

```bash
make
```

Cela génère l'exécutable `pipex`.

## Commandes Makefile

- `make` : compile le projet
- `make clean` : supprime le dossier des objets
- `make fclean` : supprime les objets et l'exécutable `pipex`
- `make re` : reconstruit le projet depuis zéro

## Utilisation

Le programme attend exactement 4 arguments :

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Exemple :

```bash
./pipex infile.txt "cat" "wc -l" outfile.txt
```

Ce que fait la commande :

- lit `infile.txt`
- exécute `cat`
- envoie la sortie dans `wc -l`
- écrit le résultat final dans `outfile.txt`

## Gestion des commandes

- les commandes sont séparées en arguments texte
- le programme cherche l'exécutable via les variables d'environnement
- en cas d'erreur, les messages système sont affichés avec `perror`

## Notes

- Le projet est une initiation aux commandes qui vont etre approfondis dans le projet minishell
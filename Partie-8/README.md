# La chaine de compression JPEG


**Résumé**

L’objectif de cette partie est de vous confronter à l'implantation d'une application complete, une chaine de compression d'image au format JPEG. Cependant avant de manipuler une application complexe et l'intégrer éfficacement il va vous falloir en comprendre les algorihtmes. Je vous conseille donc de lire attentivement la page wikipedia suivante:

```
https://en.wikipedia.org/wiki/JPEG
```

Une fois que vous avez compris quels sont les traitements executé dans le processus de compression, vous pouvez passer à la suite...


## Q1. Simulation de la chaine de compression JPEG

La premiere étape à réaliser consiste à simuler le modele C/C++ implantant la chaine de compression complete. Pour cela:

- dans un terminal, rendez vous dans le repertoire **Question_1**;
- creez un repertoire nommé **build** car nous allons utiliser **cmake**;
- entrez dans le repertoire **build** puis tapez **cmake ..** pour générer le makefile;
- lancez la compilation des codes sources avec la commande **make**;
- maintenant, lancez l'executable **./encoder_jpeg**.

Cet executable ouvre un fichier BMP, lance le processus de compression, enregistre l'image au format JPEG (ofile.jpg) puis décompresse le flux binaire afin de recreer une image de sortie au format BMP.

- observez les 2 images créees (bon, OK, le tigre à la tete à l'envers mais c'est pas le + important);
- ouvrez les fichiers **cpp** du projet, vous vous interesserez particulierement à celui nommé **encoder.cpp** et à ses dépendances afin de retrouver tous les traitements décrits dans la page wikipedia.

Une fois que tout cela est terminé, on va essayer d'implanter cet encodeur en utilisant Vivado HLS.


## Q2. Prise en main de l'outil Vivado-HLS (ou Vitis HLS)

Nous allons maintenant nous interesser à la génération d'une architecture matérielle pour cet encodeur. Avant de cliquer partout, dessinez le schéma bloc qui sera à votre avis concu par Vivado HLS. Une fois ce dessin terminé:

- creez un projet Vivado HLS dans le repertoire de la question 2;
- ajoutez dans le projet les fichiers **encodeur.cpp**, **encodeur.h**, **dct2d.cpp** et **dct2d.h**. Vous n'oublierez pas d'ajouter les flags **-std=c++0x** aux fichiers **cpp**.
- le nom de la fonction à utiliser comme top module pour votre design est **encoder**;
- pour plus de facilité pour les comparaison vous choisierez le FPGA présent sur les cartes Nexys 4 et spécifierez une période d'horloge de 10 ns;
- lancez la synthèse d'architecture et relevé à postériori la latence globable de l'architecture matérielle et son cout matériel.

C'est la premiere architecture que vous obtenez. Elle sera votre référence pour les étapes d'optimisation qui vont suivre. Afin d'identifier les optimisations à appliquer, vous allez commencer par observer les performances de chacun des modules implantés. Vous commencerez à optimiser le plus lent, etc.

A votre disposition vous avez acces à differents type de pragma, par exemple PIPELINE, UNROLL, DATAFLOW, ARRAY, etc. Vous pouvez aussi modifier les codes sources afin d'améliorer les caracteristiques d'implantation et/ou la complexité calculatoire...

Maintenant à vous de jouer pour réduire la latence, augmenter le débit et enfin miniser les ressources :-)
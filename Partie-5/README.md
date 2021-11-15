# De la modélisation à l’implantation VHDL

1. Introduction

2. Conception de l'architecture en VHDL

Le modèle bit-accurate que vous avez décrit est très proche de la description VHDL RTL du composant. Dans cet TP nous supposerons que la finalité de l'étude est d'intégrer toute la chaîne de compression JPEG au sein d'un FPGA. Mais vous n'êtes en charge pour le moment que de l'implantation du module **RGB2YCbCr**. Vous allez donc devoir écrire le code VHDL correspondant à votre modèle C/C++ quantifié :-)

**Remarque**

Afin d'éviter des problèmes par la suite... Vous prendrez soin de respecter la spécification de l'entité ci-dessous:

```
entity RGB2YCbCr is
    port(
        clk     : in  STD_LOGIC;
        i_data  : in  STD_LOGIC_VECTOR(23 downto 0);
        o_data  : out STD_LOGIC_VECTOR(23 downto 0);
        i_valid : in  STD_LOGIC;
        o_valid : out STD_LOGIC
	);
end RGB2YCbCr;
```

De plus, pour des problèmes de compatibilité avec ModelSim & l'interface de co-simulation avec le FPGA, vous considérerez les regroupements d'information suivants en entrée :

```
b <= i_data (23 downto 16);
v <= i_data (15 downto  8);
r <= i_data ( 7 downto  0);
```

Et en sortie :

```
o_data (23 downto 16) <= cr;
o_data (15 downto  8) <= cb;
o_data ( 7 downto  0) <= y;
```

Maintenant à vous de jouer :

- Dessinez un schéma bloc du système que vous allez concevoir.
- Ecrivez le code VHDL.
- **Validez** le comportement de votre code VHDL à l'aide d'un testbench.

Une fois que votre code VHDL a été validé fonctionnellement et temporellement en simulation grace à Vivado, vous pouvez passer à l'étape suivante.

# Q2. Validation plus poussée ;-)

Les tests que vous avez appliqué sur votre composant VHDL sont minimalistes et ne permettent pas vraiment de garantir le bon fonctionnement de votre circuit. L'idéal aurait été pouvoir rejouter les tests précédents pour garantir la bonne fonctionnalité.

Dans la premiere partie de cette séquence pédagogique certaines approches méthodologiques vous ont été proposées (si, si...). Il est maintenant temps de s'en resservir. Cela vous permettra de continuer a vérifier votre composant VHDL de la même manière que précédemment (golden model). Cette approche est bien plus efficace et agréable que celle consistant à observer des dizaines ou des centaines de signaux dans l'interface de Vivado...

-	Créez un autre repertoire dans lequel vous ajouterez les fichiers nécessaires à la génération de vos stimulis (cf. Partie 3).
-	Rajouter votre fichier VHDL et votre nouveau testbench.
-	Validez fonctionnelement votre composant afin de ne pas avoir de surprise une fois sur carte...
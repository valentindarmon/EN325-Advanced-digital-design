# Synthèse d'architecture (HLS) à l'aide de l'outil Xilinx Vivado HLS


**Résumé**

L’objectif de cette partie est de vous permettre d’utiliser les connaissances acquises durant le cours dédié à la synthèse de haut niveau (HLS). Dans le cadre de ce TP nous utiliserons un outil industriel développé par Xilinx pour générer des architectures matérielles sous contraintes.

**Note**

Pour toute question spécifique à l’outil « Vivado HLS » et/ou au langage C, C++ ou SystemC supporté par ce dernier, référez vous au document UG902 fourni par Xilinx.



## Introduction

Lors des TPs précédents vous avez raffiné progressivement votre algorithme afin de le passer d’une description comportementale de type Matlab à une description matérielle de niveau RTL. Les dernières transformations que vous avez réalisées ont été particulièrement complexes et chronophages (le passage des modèles au niveau CABA).

Pour accélérer l’implantation des modèles algorithmiques décrits en C/C++, C++ ou SystemC des outils de HLS ont été développés. Ces derniers conçoivent à votre place l’architecture matérielle qui implémente l’algorithme (instanciation des ressources de calcul, des mémoires RAM, des registres et conception du séquenceur).

Afin de mieux appréhender ce type de méthodologie, vous allez dans un premier temps implanter une application « **foo** ». Dans un second temps vous vous ferez vos armes avec votre module de conversion colorimétrique « **RGB2YUV** ». Puis en fonction du temps restant vous essayerez d’implanter efficacement les différents modules de la chaine de compression JPEG.



## Q1. Prise en main de l'outil Vivado-HLS (ou Vitis HLS)

La première partie du TP vise à vous familiariser avec l’outil de HLS développé par Xilinx. Vous implanterez votre premier circuit RTL décrit en langage C/C++ et étudierez l’impact des directives de synthèse (**pragma**) supportés par l’outil sur les architectures générées. Dans un premier temps, réalisez les étapes suivantes :

- Lancez l’outil « Vivado HLS 2018.2 »

- Créez un nouveau projet « File : New project ». Nommez ce premier projet « **test_tp_3a_se** ». N’ajoutez pas de fichiers dans le projet pour le moment. Dans le dernier onglet lorsque vous devez indiquer la cible, utiliser le sous-menu « Boards » puis « Nexys-4 ». Valider et créez le projet vide.

- Maintenant commencez par ajouter 2 fichiers dans votre projets. Pour cela cliquez sur l'item « **source** » dans le panneau de gauche et faites « **Add files** ». Cherchez les fichiers nommés « **my_module.cpp** » et « **my_module.hpp** ».

- Cliquez sur votre projet à l’aide du bouton droit de la souris (dans le panneau de gauche) et sélectionnez « **project settings** » Dans le panneau nommé « **synthesis** », indiquez que le nom du module à implanter en VHDL est « **my_module** ».

- Ouvrez le le fichier nommé  « **my_module.cpp** » et décrivez une fonction nommée my_module. Cette fonction prendra en entrée “**x**” de type **const int32_t**, une sortie “**y**” de type **int32_t&**.

- Implantez le comportement suivant au sein de votre code (y = 1000 / (2 * (x * x) – 7 * x + 1)).

- Appuyez sur le bouton « **Run C synthesis** » afin de vérifier que votre code C/C++ est syntaxiquement correct. La petite flèche verte dans la barre d’outil sur laquelle vous avez cliqué vient de réaliser au passage la génération de l'architecture.

- Une fois l’opération terminée, une nouvelle fenêtre est apparue. Analysez les informations fournies par l’outil après synthèse. Une vue plus détaillée des informations post-synthèse est disponible si vous cliquez sur la perspective « **Analysis** » en haut à droite de l’outil. Activez cette perspective et analysez toutes les informations fournies (performances, ressources).

- Vous venez de générer une architecture matérielle de niveau RTL (sans vous en rendre compte). Les fichiers VHDL, Verilog et SystemC correspondant sont disponibles dans le panneau de gauche dans la sous rubrique « **solution 1** ». Ouvrez les fichiers VHDL et observez les.

- Reconstituez le circuit conçu pour vous par l’outil Vivado HLS. A partir du rapport de synthèse (ordonnancement des opérations dans le temps) + des fichiers VHDL,  **dessinez le circuit** que l’outil a conçu pour vous.

- Les caractéristiques matérielles que vous avez analysées précédemment sont des estimations faites par l’outil Vivado. Afin de connaître de manière précise les performances du système, cliquez sur le menu « **Solution** » puis sur « **Export RTL** ». Sélectionnez « **Evaluate** » et choisissez le mode « **VHDL** » puis validez. Comparez les performances fournies dans ce nouveau rapport avec les estimations fournies précédemment par l’outil.

  

## Q2. Modification des entrées sorties (1/2)

Comme vous l'avez remarqué dans la question précédente,  lors de l'étape de génération de l'architecture, l'outil ajoute des entrées et des sorties non souhaitées à l'architecture matérielle. Afin de supprimer ces E/S qui sont inutiles dans notre cas d'usage, il est nécessaire de rajouter la directive suivante dans le corps de votre fonction « **my_module** ».

```cpp
 #pragma HLS INTERFACE ap_ctrl_none port=return 
```


- Relancez ensuite la synthèse HLS afin de vérifier dans le code VHDL que les E/S du module ont disparu.

  


## Q3. Modification des entrées sorties (2/2)

Personnellement je ne trouve pas qu'utiliser des données de type int32_t pour spécifier des E/S soit tres propre. Pour cette raison, vous allez modifier votre fonction « **my_module** » de la maniere suivante:

```cpp
void stream_sorter_tcp(
		hls::stream< uint8_t >& strm_in,
		hls::stream< uint8_t >& strm_out
      )
{
	#pragma HLS INTERFACE ap_ctrl_none port=return
	#pragma HLS interface axis port=strm_in
	#pragma HLS interface axis port=strm_out

	int32_t value;
	value = strm_in.read();
	... ... ...
	strm_out.write( value + 1 );	
}
```

Le type de données **hls::stream<T>** spécifie à l'outil de synthèse HLS que l'on souhaite obtenir un port de communication de type **FIFO**. Cette spécification implique la génération automatique de signaux **empty**, **full** et **valid**. Afin d'utiliser ce type de données, vous devrez ajouter les deux lignes suivantes:

```cpp
#include <hls_stream.h>
using namespace hls;
```

- Relancez le processus de synthèse HLS afin de vérifier qu'au niveau RTL vous obtenez le composant attendu.

Dans le reste de la séquence pédégogique vous employerez ce moyen de communication pour modéliser les E/S de vos composants.



## Q4. Influence du type des données sur les performances


- Transformez votre programme source afin de faire en sorte que l'entrée « **x** » et la sortie « **y** » soient codées sur 16 bits. Faites attentation aux calculs intermédiaires ;-)
- Relancez le processus de synthèse HLS et comparez les performances obtenues (complexité matérielle et latence) avec celles de la question précédente.



## Q5. Exploration de l'espace des solutions


Pour vous simplifier la vie, je vous conseillons d’utiliser la génération de solutions multiples & la comparaison de design dans les questions suivantes...

- Transformez à nouveau votre programme source afin manipuler des données de type « **int32_t** ». Modifiez la fréquence d’horloge ciblée post-synthèse. Essayez avec les périodes 5 ns, 10 ns, 20 ns et 50 ns.

- Observez l’impact de ces modifications sur les résultats de synthèse et calculez les performances en terme de débit et de latence pour chacun des circuits générés. Mettez ces chiffres en regard avec la complexité matérielle.

- Maintenant vous allez changer la cible matérielle indiquée dans les paramètres de synthèse. Choisissez d’abord le FPGA présent sur la carte d’évaluation « cf votre enseignant ». Faites la synthèse de votre description et interprétez les résultats.

- Faites de même lorsque la cible est un XXX (cf votre enseignant).

  

## Q6. Implantation du module RGB_2_YUV

Maintenant que vous maitrisez les concepts de base de l’outil Vivado HLS, vous allez mettre en œuvre vos connaissances afin d’intégrer votre module **RGB_2_YUV** développé en durant les séances de TPs précédentes. Dans cette partie, vous focaliserez votre attention sur les performances obtenues en fonction du niveau de description de votre fonction.

- Reprenez le modèle C/C++ réalisant la conversion **RGB_2_YUV** à l’aide d’opérations flottantes.
- Adaptez cette description afin de la rendre synthétisable.
- Procédez ensuite à la synthèse du modèle à l’aide de l’outil Vivado HLS.
- Notez et analysez les résultats de synthèse.
- Procédez de la même manière avec le modèle qui réalise la conversion **RGB_2_YUV** à l’aide de données de type **ap_fixed**.
- Faites la synthèse du modèle à l’aide de l’outil Vivado HLS. Réitérez l'opération pour différents formats de codage (nombre de bits fractionnaires).
- Notez et analysez les résultats de synthèse.
- Faites de même avec le modèle réalisant la conversion **RGB_2_YUV** à l’aide de données de type **ap_int**.
- Faites la synthèse du modèle à l’aide de l’outil Vivado HLS. Réitérez l'opération pour différents formats de codage (nombre de bits fractionnaires).
- Notez et analysez les résultats de synthèse.
- Comparez les performances obtenues vis-à-vis du module VHDL que vous avec décrit à la main durant les TP précédents.



## Q7. Implantation du module RGB_2_YUV

- Afin d’améliorer les performances, il est possible de travailler sur plusieurs données en parallèle (données provenant d’itérations successives). Pour cela, étudiez les pragmas [HLS PIPELINE], [HLS INLINE] et/ou [HLS UNROLL] présentés dans la documentation de l’outil Vivado HLS.
- Améliorez les performances de votre module en prenant en considération le fait que 64 échantillons sont toujours traités.

```
Dans cette partie vous avez le temps d'analyser les conséquences de vos choix alors n'hésitez pas à expérimenter & demander de l'aide à votre enseignant.
```




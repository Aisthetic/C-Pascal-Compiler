# THE  C-PASCAL Compiler 
Un simple compilateur basé sur un langage **"C-PASCAL"** et une **Grammaire LL1** construit pour des raisons éducationnelles. Open source et construit from scratch.
## Collaboration
Sous encadrement et supervision de  
- Monsieur Souhaïl El ghazi El Houssaïni 

Avec contribution de :

 - [OUTIDRARINE Mohamed]( https://github.com/outidrarine )
 - [EZZAHED Zakaria]( https://github.com/Dreaminguy )
 - [ECHBLAOUI Yassine]( https://github.com/Testoxe )
 - [AMGHAR Souhail]( https://github.com/Ssouh )

## Structure 

 1. [x] Un parseur lexical.
 2. [x] Un parseur Synataxique.
	 - [x] Parseur Syntaxique et gesion des erreurs
 3. [x] Génération de l'arbre décoré et contrôle sémantique des types de variables.
 4. [x] Code intermédiaire :
	 - [x] Génération d'un code intermédiaire en P-machine.
	 - [x] Une machine virtuelle p-machine qui exécute les instructions p-code.
## Comment utiliser :
 
 1. Ajouter **cpc.exe** dans la variable d'evironnemment **path**
 2. Pour obtenir de l'aide tappez la commande 
 ```
 cpc.exe -h
 ```
 3. Compiler le code source **p-code** en tappant la commande 
 ```
 cpc.exe nom_du_fichier
 ```
 Le résultat de la compilation sera obtenu sous la l'architecture suivante :

```
Output
│
└───Lexical
│   └───TablesIdentif
│   |   │   main.ident (table des identifiants)
│   │
│   └───TablesMotsRes
│   |   │   main.mrs (table des mots reservés)
|   |
|   |___main.lex (résultat du lexical parsing)
│   
└───XML
|   │___ Arbre syntaxique en XML
|
|___PMachineCode
|   |
|   |___ code généré
|
|
|___TS_Table
    |
    |__ Table des symboles sémantique
```

 4. Génération du code intermediaire
 Dans le dossier output vous allez obtenir un fichier objet qui contient le code **p-code**
 5. Exécution du code intermédiaire
  Ejouter le fichier **stack-machine.exe** dans la variable d'environnement et exécuter la commande **stack-machine.exe + votre_fichier_à_exécuter**
 Après la compilation on aura obtenu un code source en language intermediaire p-code que vous pouvez exécuter en utilisant la machine virtuelle, vous pouvez exécuter un tappant la commande 
 ```
 stack-machine nom_du_fichier.o
 ```

 
## Architecture:
Nous disposons ici d'une solution divisée en deux :
- Le Compilateur C-Pascal :
Donne comme résultat les fichiers cités au-dessus
- La machine virtuelle P-Machine :
Exécute le code intermedaire généré par le générateur de code
Description des parties du compilateur C-Pascal :
### Le parseur lexical :
- Equipé par une **Table de hashage** il fait la reconnaissance des unités lexicales du language dans le code source écrit en C-Pascal
- Génère une **une table des identifiants** et une **une table des mots reservés** ainsi que un fichier **main.lex** contenant le résultat du parsing lexical
### Le parseur syntaxique :
- Génère l'arbre syntaxique en XML en se basant sur les règles de producations de la grammaire
### L'analyseur sémantique :
- Grifé dans le santaxique il génère une table des symboles contenant tous les informations à propos des symboles utilisés dans le code source en C-Pascal
### Générateur de code :
- Il génére le code intermediaire en p-code destiné à être exécuté par la machine virtual p-machine.
- Il est gréfé dans le syntaxique et se sert des règles de production pour générer le code intermediaire.
- Il  gère l'adressage des fonctions et leur appels.
### Machine virtuelle P-Machine :
- Equipée d'une pile sert à exécuter le code générer par le générateur de code.
- Equipée de deux modes, mode débuggage et mode automatique, le mode débuggage affiche graphiquement la pile d'éxécution et son évolution au cours de l'éxécution.

## Option numro 1 : Les caractères
Le language et fait de tel sorte à ce qu'il prend en main le type **caractère**
### Exemple
```
car a;				
main()  				
entier d, entier x;
{
  	a = 'n';
	si( a == 'b' ) alors{
		ecrire('y');
	}
}
```
Le code intermediaire généré par cet exemple : 
```
PILE 1
APPEL 3
FIN
ENTREE
PILE 2
EMPC n
DEPG 0
EMPG 0
EMPC b
EGAL
SIFAUX 13
EMPC y
ECRIV
```
## License:
CPC Compiler est sous la Licence Publique Générale GNU vous pouvez le redistribuer et/ou le modifier selon les termes de la license GNU. Nous avons utilisé CLI pour gérer la ligne de commande qui est aussi sous la Lisence Générale GNU.

## Comment contribuer
Si vous avez détecté des bugs ou si vous voulez suggérer des améliorations dans **C-Pascal Compiler**, n'hésitez pas à soumettre une demande pull request ou de le signaler dans issues.

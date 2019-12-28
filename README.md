# THE  C-PASCAL Compiler 
Un simple compilateur basé sur un langage **"C-PASCAL"** et une **Grammaire LL1** construit pour des raisons éducationnelles. Open source et construit from scratch.
## Collaboration
Sous encadrement et supervision de  
- Monsieur Souhaïl El ghazi El Houssaïni 

Avec contribution de :

 - OUTIDRARINE Mohamed
 - EZZAHED Zakaria
 - ECHBLAOUI Yassine
 - AMGHAR Souhail

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
 2. Exécuter la commande **cpc -h** pour l'aide
 3. Le résultat de la compilation sera ainsi obtenu sous la forme suivate :
 

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
    │   Arbre syntaxique en XML
```

 4. Génération du code intermediaire
 5. Exécution du code intermédiaire
## License:
CPC Compiler est sous la Licence Publique Générale GNU vous pouvez le redistribuer et/ou le modifier selon les termes de la license GNU. Nous avons utilisé CLI pour gérer la ligne de commande qui est aussi sous la Lisence Générale GNU.

## Comment contribuer
Si vous avez détecté des bugs ou si vous voulez suggérer des améliorations dans **C-Pascal Compiler**, n'hésitez pas à soumettre une demande pull request ou de le signaler dans issues.

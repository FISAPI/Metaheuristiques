# Metaheuristiques
The aim of this work is to complete the introduction to the concepts covered during the module's course sessions on the value of using heuristics and/or metaheuristics when the problem to be solved is ‘difficult’.


# Execution : 
```bash
g++ -o scp_solver src/main.cpp src/retrieving_data.cpp src/algorithme_glouton.cpp

```
Ensuite, execution du fichier executable scp_solver avec les options suivantes : 

```bash
./scp_solver --glouton      
```


### Question pour WILBAUT : 
Le fichier scp4x.txt fonctionne comment parce que je ne comprends pas le nombre d'éléments.

3 executables : 
scp_solver200.exe : fichier normal avec 200 elements et 1000 sous-ensembles -> Fichier de base, mais il y a 1000 éléments ?
scp_solverinv.exe : fichier inversé avec 1000 elements et 200 sous-ensembles -> il y a 1000 déclaration de coût, donc ça fonctionne pas
scp_solver1000.exe : fichier normal avec 1000 elements et 1000 sous-ensembles ->  On doit modifier le fichier de base ?
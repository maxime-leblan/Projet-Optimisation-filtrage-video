# Projet-Optimisation-filtrage-video
Ce projet est en cours de développement dans le cadre de ma formation d'ingénieur à l'ESIEE Paris, en particuliers dans le cadre du cours d'optimisation de code et d'étude de l'architecture des processeurs.

# Comment exécuter le programme avec WSL (+ caméra intégrée)
Pour pouvoir compiler puis tester le code ci-dessus, plusieurs manipulations sont nécessaires pour l'exécuter sur Windows avec l'outil WSL.

Dans un premiers temps, assurez-vous d'avoir le code source stocké dans un répertoire qui se situe dans votre répertoire WSL, dont l'adresse est censée commencer au moins par **"\\wsl.localhost\Ubuntu\home\VOTRE-NOM-D-UTILISATEUR"**.

Ouvrez d'abord un premier terminal sous WSL et un deuxième terminal sous Windows (Powershell). Nous allons associer la webcam de votre choix (intégrée au PC ou connectée par câble USB) avant de compiler le code source. Pour ce faire, nous devons premièrement récupérer l'ID USB de notre caméra en tapant la commande ci-dessous dans le Powershell Windows : 
```
usbipd list
```
Une liste de périphérique devrait s'afficher. Chercher votre caméra et relever son ID USB qui devrait être de la forme "1-NOMBRE" (par exemple "1-6").
Ensuite, il faut rattacher l'ID de notre caméra à une session WSL **préalablement ouverte**, ce qui a normalement déjà été effectué lors de la première étape. Pour cela, il faut rentrer la commande ci-dessous dans le Powershell : 
```
usbipd attach --wsl --busid <VOTRE-ID-USB>
```
Il faut ensuite donner les droits à notre session WSL pour utiliser la caméra. Pour cela, nous devons d'abord vérifier que l'on a bien créé le répertoire vidéo de la caméra en la reliant à WSL. Entrez dans le terminal WSL la commande suivante : 
```
ls -l /dev/video*
```
Vous devriez obtenir une liste de répertoire. Si le répertoire **/dev/video0** apparaît, c'est que l'étape précédente a bien fonctionné. Pour accorder tous les droits à notre session WSL, rentrez la commande suivante : 
```
sudo chmod 666 /dev/video0
```
Si le terminal n'affiche ensuite aucun message d'erreur, c'est que l'octroyation des droits a bel et bien fonctionné.
Il ne vous reste plus qu'à compiler le projet puis à l'exécuter : 
```
g++ -O0 -g projet_24_v1.cpp my_functions.cpp -o projet $(pkg-config --cflags --libs opencv4) -lm
./projet <NOMBRE>
```

**/!\ ATTENTION** : Les opérations d'associations de l'ID USB de votre caméra avec une session WSL et l'octoyation des droits sont valables uniquement tant que la session (et donc le terminal) WSL reste ouverte. A chaque nouveau redémarrage, il est nécessaire d'effectuer à nouveau ces étapes.
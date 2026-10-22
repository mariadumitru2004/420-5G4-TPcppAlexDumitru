# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de donner chemin vers le repertoire data avec l'application `bibliotheque -d <chemin verrs data>`

# Veille Technologique 

**Alex Dumitru**

# Fonctionalites choisies

- **Affichage du nom de l'emprunteur au lieu du ID dans tous les affichages des livres:** 
- **Tri des livres par auteur et puis titre au cas des doublons de titre**

# Question 1: C++ 
## Expliquez en détails une fonctionnalité / notion dans le code que ne nous avons pas ou peu vu en cours. Montrez ici l’exemple sorti du code du projet. ##

### Le journal d'activites avec le flux de fichiers et le timestamp

J'ai du apprendre comment manipuler un fichier en mode append pour stocker dedans des logs d'activite pour chaque action sur les donnees (book et user). J'ai utilise la classe std::ofstream de la bibliothque fstream pour ecrire des donnees dans un fichier. J'ai ecrit la methode FileManager::logActivity(), ou je ouvre le fichier avec ios::app pour utiliser le mode append pour ecrire des nouvelles donees au fur des sessions sans efacer les dernieres donnees de la session passee. On check aussi si le fichier a ete ouvert avec success. 

Extrait de code : 

```cpp
void FileManager::logActivity(const string &action, const string &details)
{
    ofstream file("activity.log", ios::app);

    if (!file.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le journal d'activités.\n";
        return;
    }

    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);

    file << put_time(localtime(&currentTime), "%Y-%m-%d %H:%M:%S")
         << " - [" << action << "] "
         << details << "\n";
}
```

La methode recoit 2 parametres, action, qui contient l'operation effectuee que je inscrit dans l'appel a chaque appel de la fonction dans les cases necessaires dans main.cpp, et details, qui contient les informations de l'operation. Pour obtenir le timestamp j'ai utilise chrono::system_clocl::now() pour recuperer l'heure actuelle. La fonction chrono::system_clock::to_time_t() convertit la valeur en format qui peut etre utilise par les fonctions de date et d'heure de la bibliotheque std. put_time() formatte l'heure sous la forme annee-mois-jour heure:minute:seconde. Les codes %Y %m %d %H %M %S representent l'ordre de l'annee mois etc. Finalement avec l'operateur << on ecrit le timestamp le type d'action et les details dans le fichier. La methode est appelle depuis main.cpp apres la reussite d'une operation, alors dans l'emprunt, dans l'ajout d'un livre et d'un utilisateur, dans le retour d'un livre et dans la suppression d'un livre. 

# Question 2: Options de développement possible :
## Proposez une solution plus adaptée pour la gestion de bibliothèque et faisant appel éventuellement à une technologie autre que le C++, et expliquez comment vous interfaceriez ça avec le C++. Quelle solution technologique utiliseriez-vous ? Pensez au futur de cette bibliothèque à Alexandrie qui pourrait éventuellement contenir des millions de livres.


Pour une bibliotheque avec des millions de livres il faudrait absolumment une base de donees pour stocker les donnees, car des fichiers c'est cool pour un projet personnel d'ecole mais dans un vrai contexte on aurait besoin d'une eilleure facon de faire. L'utilisation d'une base de donnees permettrait par exemple de faciliter la tache de trouver plus rapidement et facilement un livre par son isbn. J'ai trouve que PostgreSQL serait une bonne option a l'aide de la bibliotheque libpqxx, bibliotheque qui permet a c++ de communiquer avec PostgreSQL et d'envoyer des requetes sql. Sinon un site web serait aussi cool a developper avec React ou Next.js et un stack approprie pour faciliter la tache des travailleurs de la librairies et ca permettrait aussi aux utilisateurs dehors des employes a chercher des livres et a les emprunter online en format pdf ou ebook. 


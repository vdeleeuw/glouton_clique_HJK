#include "graphe.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <unistd.h>

/**
 * @file main.cpp
 * @brief Programme de test
 * @author1 Valérian De Leeuw
 * @author2 Robin Couasnet
 * @date 12 novembre 2015
 *
 * Programme de test pour la recherche de clique dans un graphe avec un algorithme glouton.
 */

int main(int argc, char* argv[]){
	//initialisation de l'aléatoire
	srand(time(NULL));
	graphe g;
	//verification du nombre de paramètres
	if(argc == 2){
		if(!g.init(argv[1]))
			return EXIT_FAILURE;
		else{
			char rep;
			std::cout << "Voulez-vous afficher la matrice à l'écran (O/N) : ";
			std::cin >> rep;
			if(rep == 'O')
				g.afficherMatrice();
			std::cout << "Voulez-vous écrire la matrice dans un fichier externe (O/N) : ";
			std::cin >> rep;
			if(rep == 'O'){
				std::string nomFic;
				std::cout << "Saisissez le nom du fichier souhaité (si il existe, il sera effacé!) : ";
				std::cin >> nomFic;
				g.afficherFichier(nomFic.c_str());
			}
			int nbRecherche;
			std::vector<int> clique;
			std::vector<int> cliqueMax;
			std::cout << "Combien de fois voulez-vous rechercher des cliques dans le graphe : ";
		 	std::cin >> nbRecherche;
			std::cout << "Voulez-vous afficher toutes les cliques trouvées (O/N) : ";
			std::cin >> rep;
			std::cout << std::endl;
			//recherche de plusieurs cliques
			for(int i=0; i<nbRecherche; ++i){
				clique = g.rechercheClique();		
				if(clique.size() > cliqueMax.size())
					cliqueMax = clique;
				if(rep == 'O'){
					std::cout << "Clique " << i+1 << " (de taille " << clique.size() << ")" << " : " << std::endl;
					g.afficherClique(clique);
					std::cout << std::endl;
				}
				//pour etre sur de ne pas avoir le meme aléatoire sur chaque recherche
				//sleep(1);
			}
			if(nbRecherche > 0){
				std::cout << "Plus grande clique trouvée (de taille " << cliqueMax.size() << ")" << " : " << std::endl;
				g.afficherClique(cliqueMax);
				std::cout << std::endl;		
			}
		}
	}else{
		std::cerr << "Nombre d'arguments incorrect." << std::endl;
		std::cerr << "Il faut seulement préciser en argument le fichier ascii DIMACS." << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

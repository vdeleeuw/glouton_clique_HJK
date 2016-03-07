#include "graphe.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

#define TAILLE_MAX 75

/**
 * @file graphe.cpp
 * @brief Code C++ de la classe graphe
 * @author { Valérian De Leeuw, Robin Couasnet }
 * @date 12 novembre 2015
 */


graphe::graphe()
	:m_nbArete(0), m_nbSommet(0){
};


bool graphe::init(char* nomFic){
	//ouverture du fichier 
	FILE* fic = fopen(nomFic, "r");
	if(fic == NULL){
		std::cerr << "Erreur lors de l'ouverture du fichier \"" << nomFic << "\" pour la lecture du graphe." << std::endl;
		return false;
	}else{
		//lecture du fichier
		char ligne[TAILLE_MAX] = "";
		int tmpArete = 0;
		while(fgets(ligne, TAILLE_MAX, fic) != NULL){
			ligne[strlen(ligne)-1] = '\0';	
			if(ligne[1] != ' ' && ligne[1] != '\0'){
				std::cerr << "Erreur lors de la lecture du fichier \"" << nomFic << "\"." << std::endl;
				std::cerr << "Format de la ligne \"" << ligne << "\" invalide. " << std::endl;
				return false;
			}else switch(ligne[0]){
				//cas d'un commentaire (commentary)
				case 'c':
					break;
				//cas d'un parametre (parameters)
				case 'p':
					if(m_nbArete == 0 || m_nbSommet == 0){
						std::string tmpStr(ligne);
						std::string typeGraphe(tmpStr.substr(2, 3+tmpStr.find(" ")));
						if(strcmp(typeGraphe.c_str(), "edge") == 0)
							tmpStr=tmpStr.substr(7);
						else if(strcmp(typeGraphe.c_str(), "col ") == 0)
							tmpStr=tmpStr.substr(6);
						else{
							std::cerr << "Erreur lors de la lecture du fichier \"" << nomFic << "\"." << std::endl;
							std::cerr << "Le graphe est de mauvais type, il faut un graphe non orienté." << std::endl;
							return false; 
						}
						m_nbSommet = atoi(tmpStr.substr(0, tmpStr.find(" ")).c_str());
						int nbArete = atoi(tmpStr.substr(1+tmpStr.find(" ")).c_str());;	
						int maxArete = (m_nbSommet*(m_nbSommet-1))/2;
						if(m_nbArete > maxArete){							
							std::cerr << "Erreur lors de la lecture du fichier \"" << nomFic << "\"." << std::endl;
							std::cerr << "Le nombre d'arêtes indiqué (" << nbArete << ") est supérieur au maximum possible (" << maxArete << ") avec " << m_nbSommet << " sommets. " << std::endl;
							return false;
						}else{
							m_nbArete = nbArete;
							for(int i=0; i<m_nbSommet; ++i)
								m_matrice.push_back(std::vector<bool>(i, false));
						} 
					}else{
						std::cerr << "Erreur lors de la lecture de la ligne \"" << ligne << "\"." << std::endl;
						std::cerr << "Une autre ligne (p col " << m_nbSommet << " " << m_nbArete << ") précisant la taille est présente ! " << std::endl;
						return false;
					}break;
				//cas d'une arete (edge)
				case 'e':
					if(m_nbArete == 0 || m_nbSommet == 0){
						std::cerr << "Erreur lors de la lecture du fichier \"" << nomFic << "\"." << std::endl;
						std::cerr << "Il faut préciser la taille du graphe avant de définir des arêtes !" << std::endl;
						return false;
					}else{
						std::string tmpStr(ligne);
						tmpStr=tmpStr.substr(2);
						int areteA = atoi(tmpStr.substr(0, tmpStr.find(" ")).c_str());
						int areteB = atoi(tmpStr.substr(1+tmpStr.find(" ")).c_str());
						if(areteA < areteB){
							std::cerr << "Erreur lors de la lecture de la ligne \"" << ligne << "\"." << std::endl;
							std::cerr << "Les arêtes sont définies du plus grand sommet vers le plus petit et non l'inverse !" << std::endl;
							return false;
						}else{
							m_matrice[areteA-1][areteB-1] = true;
							++tmpArete;
						}
					}break;
				//autre cas non traitée
				default :{
					std::cerr << "Erreur lors de la lecture du fichier \"" << nomFic << "\"." << std::endl;
					std::cerr << "Format de la ligne \"" << ligne << "\" invalide. " << std::endl;
					return false;
				}			
			}
		}
		if(tmpArete != m_nbArete){
			std::cerr << "Erreur lors de la lecture du fichier \"" << nomFic << "\"." << std::endl;			
			std::cerr << "Le nombre d'arêtes (" << tmpArete << ") lues dans le fichier est différent de celui annoncé (" << m_nbArete << ")." << std::endl;
			return false;
		}else{
			std::cout << "Initialisation réussie." << std::endl;
			afficherStats();
			std::cout << std::endl;
		}
		return true;
	}
};


std::vector<int> graphe::rechercheClique(){	
	std::vector<int> clique;
	//calcul du nombre d'arete par sommet & du plus grand
	std::vector<int> sommetChoix2;
	std::vector<int> nbAreteSommet;
	int maxAreteSommet = 0;	
	for(int i=0; i<m_nbSommet; ++i){
		int res=0;
		for(int j=0; j<i; ++j)
			if(m_matrice[i][j])
				++res;
		for(int j=i+1; j<m_nbSommet; ++j)		
			if(m_matrice[j][i])
				++res;	
		nbAreteSommet.push_back(res);
		if(res > maxAreteSommet)
			maxAreteSommet = res;
	}
	//recherche des sommets avec le plus d'arete par sommet
	std::vector<int> sommetChoix;
	for(int i=0; i<m_nbSommet; ++i)
		if(nbAreteSommet[i] == maxAreteSommet)
			sommetChoix.push_back(i);
	//premier choix aleatoire dans sommetChoix & raz
	clique.push_back(sommetChoix[rand() % sommetChoix.size()]);
	sommetChoix.clear();
	//tout les sommets adjacents du premier element de clique
	for(int i=0; i<clique[0]; ++i)
		if(m_matrice[clique[0]][i])
			sommetChoix.push_back(i);
	for(int i=clique[0]+1; i<m_nbSommet; ++i)
		if(m_matrice[i][clique[0]])
			sommetChoix.push_back(i);
	//tant que on a encore des choix
	while(!sommetChoix.empty()){
		//reinitialisation
		maxAreteSommet = 0;	
		sommetChoix2.clear();	
		//recherche du max de arrete par sommet
		for(unsigned int i=0; i<sommetChoix.size(); ++i)
			if(nbAreteSommet[sommetChoix[i]] > maxAreteSommet)
				maxAreteSommet = nbAreteSommet[sommetChoix[i]];			
		//recherche des sommets avec le plus d'arete par sommet
		for(unsigned int i=0; i<sommetChoix.size(); ++i)
			if(nbAreteSommet[sommetChoix[i]] == maxAreteSommet)
				sommetChoix2.push_back(sommetChoix[i]);	
		//ajout aleatoire parmis tout les choix
		clique.push_back(sommetChoix2[rand() % sommetChoix2.size()]);		
		//suppression du dernier ajout dans sommetChoix
		for(unsigned int i=0; i<sommetChoix.size(); ++i)
			if(clique[clique.size()-1] == sommetChoix[i])
				sommetChoix.erase(sommetChoix.begin()+i); 				
		//supprime tout les sommets qui ne sont pas adjacents au dernier element ajouté de la clique
		for(int i=0; i<static_cast<int>(sommetChoix.size()); ++i)
			if(sommetChoix[i] > clique[clique.size()-1]){
				if(!m_matrice[sommetChoix[i]][clique[clique.size()-1]]){
					sommetChoix.erase(sommetChoix.begin()+i);
					--i;
				}
			}else{
				if(!m_matrice[clique[clique.size()-1]][sommetChoix[i]]){
					sommetChoix.erase(sommetChoix.begin()+i);
					--i;
				}
			}
	}
	return triClique(clique);
};


std::vector<int> graphe::triClique(std::vector<int> &clique){
	//tri la clique par ordre croissant
	int aux = 0;
	for(unsigned int i=0; i < clique.size(); ++i)
		for(unsigned int j = i+1; j < clique.size(); ++j)
			if(clique[j] < clique[i]){
				aux = clique[i];
				clique[i] = clique[j];
				clique[j] = aux;
			}
    return clique;
};


bool graphe::testClique(std::vector<int> clique){
	//test si le vecteur d'entier est une clique de m_matrice
	for(unsigned int i=0; i < clique.size(); ++i)
		for(unsigned int j=i+1; j < clique.size(); ++j)
              		if(!m_matrice[clique[j]][clique[i]]){
	        		std::cout << "Clique non valide sur m_matrice["<< clique[j] << "][" << clique[i] << "]." <<  std::endl;
	        		return false;
	        	}
	std::cout << "Clique valide." << std::endl;
	return true;
};


void graphe::afficherClique(std::vector<int> clique){
	//affiche la clique de la maniere "sommet1 sommet2 sommet3 ... "
	for(unsigned int i=0; i < clique.size(); ++i)
		std::cout << clique[i]+1 << " ";
	std::cout << std::endl;
}

void graphe::afficherStats(){
	//affiche le nombre de sommets et d'arêtes
	std::cout << "Nombre de sommets : " << m_nbSommet << std::endl;
	std::cout << "Nombre d'arêtes : " << m_nbArete << std::endl;
};


void graphe::afficherMatrice(){
	//affiche la matrice sous forme de triangle a l'écran
	std::cout << std::endl;
	for(int i=0; i<m_nbSommet; ++i){
		for(int j=0; j<i; ++j)
			std::cout << m_matrice[i][j];
		for(int k=i;k<m_nbSommet;++k)
			std::cout << "-" ;
		std::cout << std::endl;	
	}	
	std::cout << std::endl;
};


void graphe::afficherFichier(const char* nomFic){
	//affiche la matrice dans le fichier en parametre
	std::ofstream fic(nomFic);
	if(fic) {
		for(int i=0; i<m_nbSommet; ++i){
			for(int j=0; j<i; ++j)
				fic << m_matrice[i][j];
			for(int k=i;k<m_nbSommet;++k)
				fic << "-";
			fic << std::endl;
		}
		fic << std::endl;
		fic << "Nombre de sommets : " << m_nbSommet << std::endl;
		fic << "Nombre d'arêtes : " << m_nbArete << std::endl;
		std::cout << "Ecriture de la matrice dans " << nomFic << " terminée." << std::endl;
		std::cout << std::endl;
	} else
		std::cout << "Impossible d'ouvrir le fichier" << nomFic << "pour écriture." << std::endl;
};


#ifndef GRAPHE_H
#define GRAPHE_H

#include <vector>

/**
 * @file graphe.h
 * @brief Header de la classe graphe
 * @author { Valérian De Leeuw, Robin Couasnet }
 * @date 12 novembre 2015
 */

/**
 * @class graphe
 * 
 * Le fichier graphe.h stocke les informations d'un graphe dans des variables qui sont : m_matrice qui est une matrice représentant le graphe (vecteur de 
 * vecteur de booléen), un entier représentant le nombre d'arêtes d'un graphe, et un entier représentant le nombre de sommet d'un graphe.
 * Elle dispose d'un constructeur par défaut, d'une méthode d'initialisation de la matrice et des variables de classes par rapport un à un fichier de graphe,
 * d'une méthode de recherche de clique à l'intérieur de la matrice, d'une méthode qui permet de trier une clique, d'une méthode qui teste si une clique
 * est valide et de différentes méthodes d'affichages dont une méthode qui permet d'écrire la matrice dans un fichier.
 */
class graphe{

	private:
		std::vector<std::vector<bool> > m_matrice;	/**< Matrice représentant le graphe */
		int m_nbArete;					/**< Entier représentant le nombre d'arêtes du graphe */
		int m_nbSommet;					/**< Entier représentant le nombre de sommets du graphe */

	public:
		/**
		 * @fn void graphe()
		 * @brief Constructeur 
		 * 
		 *  Constructeur par défaut de la classe graphe.
		 */
		graphe();

		/**
		 * @fn bool init(char* )
		 * @param nomFic : nom du fichier contenant le graphe avec lequel sera initialisé la matrice et les variables de la classe graphe.
		 * @return Un booléen qui vaut true si l'initialisation s'est déroulée correctement, faux sinon.
		 * 
		 * C'est une méthode qui prend un nom de fichier en paramètre et qui initialise un objet de la classe graphe avec ce fichier.
		 * 
		 */
		bool init(char* );	

		/**
		 * @fn vector<int> rechercheClique()
		 * @return Un vecteur d'entier contenant une clique trouvé par la méthode.
		 * 
		 * C'est une méthode qui recherche une clique dans la matrice de la classe. Cette méthode contient un algorithme glouton qui teste
		 * chaque sommet adjacent et qui choisit le sommet possèdant le plus d'arêtes en priorité. 
		 */
		std::vector<int> rechercheClique();

		/**
		 * @fn vector<int> triClique(vector<int>& )
		 * @return Un vecteur d'entier contenant la clique triée passée en paramètre.
		 * 
		 * C'est une méthode qui d'après une clique passée en paramètre retourne cette même clique triée par ordre croissant.
		 */
		std::vector<int> triClique(std::vector<int>& );

		/**
		 * @fn bool testClique(vector<int> )
		 * @param clique : vecteur d'entier qui sera testée pour savoir s'il s'agit bien d'une clique ou non.
		 * @return Un booléen qui vaut true si la clique passée en paramètre est valide, faux sinon.
		 * 
		 * C'est une méthode qui teste une clique passée en paramètre pour savoir si elle est valide, la méthode retournera true si c'est le cas,
		 * faux sinon. La clique est comparée à la matrice pour voir si chaque sommet possède une arête en commun avec chaque élément de la clique.
		 */
		bool testClique(std::vector<int> );

		/**
		 * @fn void afficherClique(vector<int>)
		 * 
		 * C'est une méthode qui affiche la clique passée en paramètre dans le terminal.
		 */
		void afficherClique(std::vector<int> );

		/**
		 * @fn void afficherStats()
		 * 
		 * C'est une méthode qui affiche les informations concernant un graphe, c'est à dire son nombre d'arêtes et son nombre de sommets dans le terminal.
		 */
		void afficherStats();

		/**
		 * @fn void afficherMatrice()
		 * 
		 * C'est une méthode qui affiche la matrice d'un graphe dans le terminal.
		 */
		void afficherMatrice();

		/**
		 * @fn void afficherFichier(const char* )
		 * @param nomFic : nom de fichier de destination dans lequel sera écrit la matrice d'un graphe.
		 * 
		 * C'est une méthode qui affiche la matrice d'un graphe et ses statistiques dans un fichier externe.
		 */
		void afficherFichier(const char* );
};
#endif

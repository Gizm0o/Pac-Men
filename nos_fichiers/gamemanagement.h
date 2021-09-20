#ifndef GAMEMANAGEMENT_H
#define GAMEMANAGEMENT_H

/**
 * \file gamemanagement.h
 * \brief gestion du jeu
 * \author Mathys Garoui
 * \author Martin Moreira de Jesus
 * \version 1.0
 * \date 10 janvier 2020
 */

#include <vector>
#include <string>
#include "nos_fichiers/type.h"

/**
 * @brief ChangeColorSheme change la combinaison de couleurs
 * @param scheme nom du theme souhaité
 * @fn void ChangeColorSheme(const std::string & scheme);
 */
void ChangeColorSheme(const std::string & scheme);

/**
 * @brief FetchScore renvoie la valeur du score
 * @fn unsigned FetchScore();
 */
unsigned FetchScore();

/**
 * @brief KillGhost va renvoyer le fantome à l'emplacement donné au centre de la map
 * @param ghostPlace est un UPair qui contient l'emplacement du fantome à tuer
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @fn void KillGhost(UPair ghostPlace, CMat & dataMap, unsigned & totalScore, CLine & underF, std::vector<std::string> & dirF);
 */
void KillGhost(UPair ghostPlace, CMat & dataMap, unsigned & totalScore, CLine & underF, std::vector<std::string> & dirF);

/**
 * @brief ResetAllMap va réinitialiser toutes les informations enregistrées sur la carte et va réinitialiser toutes les variables du jeu à leur valeur de base
 * @param gameLost est un booleen qui determine si la partie est perdue.
 * @param underPacMen est un CLine qui contient pour chaque PacMen le caractère présent en dessous.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param desiredDir est un vecteur de string qui contient pour chaque joueur la direction voulue.
 * @param activeDir est un vecteur de string qui contient pour chaque joueur la direction actuelle.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @fn void ResetAllMap(bool & gameLost, CLine & underPacMen, CLine & underF, std::vector<std::string> & desiredDir,
                 std::vector<std::string> & activeDir, std::vector<std::string> & dirF, unsigned & powerRemainingTime);
 */
void ResetAllMap(bool & gameLost, CLine & underPacMen, CLine & underF, std::vector<std::string> & desiredDir,
                 std::vector<std::string> & activeDir, std::vector<std::string> & dirF, unsigned & powerRemainingTime);

/**
 * @brief GameLost va afficher le menu de fin de jeu
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @fn void GameLost();
 */
void GameLost();

/**
 * @brief GameFinished determine s'il reste des points sur la carte
 * @return vrai si le jeu s'est terminé
 * @fn bool GameFinished(CMat & dataMap);

 */
bool GameFinished(CMat & dataMap);

/**
 * @brief VectorContains
 * @param vector est le vecteur de caractère dans lequel on veut savoir s'il y a le caratcère
 * @param character est le caractère recherché
 * @return vrai si le vecteur contient le char
 * @fn bool VectorContains(std::vector<char> vector, char character);
 */
bool VectorContains(std::vector<char> vector, char character);

/**
 * @brief IsAimedForPacMen
 * @param player est un string qui determine quel joueur est étudié
 * @param aimedPos est un UPair qui donne la position visée par le joueur
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @return vrai si le joueur capte un item récupérable (étoile ou point)
 * @fn bool IsAimedForPacMen(std::string  player, UPair & aimedPos, std::vector<std::vector<char>> & dataMap, unsigned & totalScore,
                      unsigned & powerRemainingTime, CLine & underF, std::vector<std::string> & dirF);
 */
bool IsAimedForPacMen(std::string  player, UPair & aimedPos, std::vector<std::vector<char>> & dataMap, unsigned & totalScore,
                      unsigned & powerRemainingTime, CLine & underF, std::vector<std::string> & dirF);

/**
 * @brief IsAimedForGhost
 * @param aimedPos est un UPair qui donne la position visée par le fanrome
 * @param activePos est un UPair qui donne la position actuelle du fantome
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @return vrai si le fantome capte un joueur
 * @fn bool IsAimedForGhost(UPair & aimedPos, UPair activePos, CMat & dataMap, unsigned & totalScore, CLine & underF,
                     std::vector<std::string> & dirF, unsigned & powerRemainingTime);
 */
bool IsAimedForGhost(UPair & aimedPos, UPair activePos, CMat & dataMap, unsigned & totalScore, CLine & underF,
                     std::vector<std::string> & dirF, unsigned & powerRemainingTime);

/**
 * @brief GenerateMatriceFromTxt va remplir la CMat dataMap à partir d'un fichier texte dataMap
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param string qui contient le chemin d'accès de la carte à ouvrir
 * @param freshGame donne vrai si on lance le jeu à 0
 * @fn void GenerateMatriceFromTxt(CMat & dataMap, const std::string & mapToOpen, bool freshGame);
 */
void GenerateMatriceFromTxt(CMat & dataMap, const std::string & mapToOpen, bool freshGame);


/**
 * @brief MovePlayerInDataMap va deplacer le joueur à l'emplacement donné sur la carte
 * @param activePos est un UPair qui donne la position actuelle du joueur
 * @param nextPos est un UPair qui donne la prochaine position du joueur
 * @param done1 retourne vrai si le joueur 1 a été déplacé lors du tour
 * @param done2 retourne vrai si le joueur 2 a été déplacé lors du tour
 * @param forced retourne vrai si le joueur se déplace dans la direction non désirée
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param underPacMen est un CLine qui contient pour chaque PacMen le caractère présent en dessous.
 * @param desiredDir est un vecteur de string qui contient pour chaque joueur la direction voulue.
 * @param activeDir est un vecteur de string qui contient pour chaque joueur la direction actuelle.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @fn void MovePlayerInDataMap(UPair activePos, UPair nextPos, bool & done1, bool & done2, bool forced, CMat & dataMap,
                         unsigned & totalScore, CLine & underPacMen, std::vector<std::string> & desiredDir,
                         std::vector<std::string> & activeDir, CLine & underF, std::vector<std::string> & dirF,
                         unsigned & powerRemainingTime);
 */
void MovePlayerInDataMap(UPair activePos, UPair nextPos, bool & done1, bool & done2, bool forced, CMat & dataMap,
                         unsigned & totalScore, CLine & underPacMen, std::vector<std::string> & desiredDir,
                         std::vector<std::string> & activeDir, CLine & underF, std::vector<std::string> & dirF,
                         unsigned & powerRemainingTime);

/**
 * @brief MovePacMen va determiner les déplacements des joueurs sur la carte
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param desiredDir est un vecteur de string qui contient pour chaque joueur la direction voulue.
 * @param activeDir est un vecteur de string qui contient pour chaque joueur la direction actuelle.
 * @param pacManMouth est un booleen qui determine le statut des bouches des PacMen (ouvertes ou fermées).
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param underPacMen est un CLine qui contient pour chaque PacMen le caractère présent en dessous.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @param freshStart retourne vrai si le jeu est lancé à 0
 * @fn void MovePacMen(CMat & dataMap, std::vector<std::string> & desiredDir, std::vector<std::string> & activeDir,
                bool & pacManMouth, unsigned & totalScore, CLine & underPacMen, CLine & underF, std::vector<std::string> & dirF,
                unsigned & powerRemainingTime, const bool freshStart);
 */
void MovePacMen(CMat & dataMap, std::vector<std::string> & desiredDir, std::vector<std::string> & activeDir,
                bool & pacManMouth, unsigned & totalScore, CLine & underPacMen, CLine & underF, std::vector<std::string> & dirF,
                unsigned & powerRemainingTime, const bool freshStart);

/**
 * @brief RefreshPacMenAnimation va faire l'animation d'ouverture et de fermeture de bouche des pacmen
 * @param Player est un char qui contient le joueur à rafraichir
 * @param activeDir est un vecteur de string qui contient pour chaque joueur la direction actuelle.
 * @param pacManMouth est un booleen qui determine le statut des bouches des PacMen (ouvertes ou fermées).
 * @fn void RefreshPacMenAnimation(char Player, std::vector<std::string> & activeDir, bool & pacManMouth);
 */
void RefreshPacMenAnimation(char Player, std::vector<std::string> & activeDir, bool & pacManMouth);

/**
 * @brief DirectionsAvailableForGhost va determiner quelles directions peuvent être empruntées par les fantomes
 * @param ghost est un char qui donne le caractère du fantome à déplacer
 * @param activePos est un UPair qui donne la position actuelle du fantome sur la carte
 * @param refusedDirection est un string qui donne la direction non privilégiée par le fantome
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @return un vecteur de string qui contient toutes les directions empruntables par le fantome.
 * @fn std::vector<std::string> DirectionsAvailableForGhost(char & ghost, UPair & activePos, std::string & refusedDirection,
                                                     CMat & dataMap, std::vector<std::string> & dirF);
 */
std::vector<std::string> DirectionsAvailableForGhost(char & ghost, UPair & activePos, std::string & refusedDirection,
                                                     CMat & dataMap, std::vector<std::string> & dirF);

/**
 * @brief MoveGhostToNextPos va réaliser le déplacement d'un fantome
 * @param nextDirection est un string qui donne la prochaine direction du fantome
 * @param ghost est un char qui donne le caractère du fantome à déplacer
 * @param activePos est un UPair qui donne la position actuelle du fantome sur la carte
 * @param nextPosition est un UPair qui donne la prochaine position du fantome sur la carte
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 *  @param freshStart retourne vrai si le jeu est lancé à 0
 * @fn void MoveGhostToNextPos(std::string & nextDirection, char & ghost, UPair & activePos, UPair & nextPosition, CMat & dataMap,
                        CLine & underF, std::vector<std::string> & dirF, unsigned & totalScore, unsigned & powerRemainingTime, const bool freshStart);
 */
void MoveGhostToNextPos(std::string & nextDirection, char & ghost, UPair & activePos, UPair & nextPosition, CMat & dataMap,
                        CLine & underF, std::vector<std::string> & dirF, unsigned & totalScore, unsigned & powerRemainingTime, const bool freshStart);
/**
 * @brief MoveGhost va determiner le déplacement d'un fantome
 * @param activePos est un UPair qui donne la position actuelle du fantome sur la carte
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @param freshStart retourne vrai si le jeu est lancé à 0
 * @fn void MoveGhost(UPair activePos, CMat & dataMap, std::vector<std::string> & dirF, CLine & underF, unsigned & totalScore,
               unsigned & powerRemainingTime, const bool freshStart);
 */
void MoveGhost(UPair activePos, CMat & dataMap, std::vector<std::string> & dirF, CLine & underF, unsigned & totalScore,
               unsigned & powerRemainingTime, const bool freshStart);

/**
 * @brief SearchForGhostsInDataMap va retrouver chaqun des fantomes sur la carte et appeler leur déplacement
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @param freshStart retourne vrai si le jeu est lancé à 0
 * @fn void SearchForGhostsInDataMap(CMat & dataMap, std::vector<std::string> & dirF, CLine & underF, unsigned & totalScore,
                              unsigned & powerRemainingTime, const bool freshStart);
 */
void SearchForGhostsInDataMap(CMat & dataMap, std::vector<std::string> & dirF, CLine & underF, unsigned & totalScore,
                              unsigned & powerRemainingTime, const bool freshStart);

/**
 * @brief ShowScore affiche le score à l'écran
 * @param dataMap est une CMat qui contient tous les elements de gameplay présents sur carte
 * @param gameLost est un booleen qui determine si la partie est perdue.
 * @param powerRemainingTime est un entier naturel qui donne le nombre d'images restantes en possession du pouvoir.
 * @param desiredDir est un vecteur de string qui contient pour chaque joueur la direction voulue.
 * @param activeDir est un vecteur de string qui contient pour chaque joueur la direction actuelle.
 * @param pacManMouth est un booleen qui determine le statut des bouches des PacMen (ouvertes ou fermées).
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @param underPacMen est un CLine qui contient pour chaque PacMen le caractère présent en dessous.
 * @param underF est un CLine qui contient pour chaque fantome le caractère présent en dessous.
 * @param dirF est un vecteur de string qui contient pour chaque fantome la direction actuelle.
 * @param freshStart retourne vrai si le jeu est lancé à 0
 * @fn void DrawMap(CMat & dataMap, bool & gameLost, unsigned & powerRemainingTime, std::vector<std::string> & desiredDir,
             std::vector<std::string> & activeDir, bool & pacManMouth, unsigned & totalScore, CLine & underPacMen,
             CLine & underF, std::vector<std::string> & dirF, const bool freshStart);
 */
void DrawMap(CMat & dataMap, bool & gameLost, unsigned & powerRemainingTime, std::vector<std::string> & desiredDir,
             std::vector<std::string> & activeDir, bool & pacManMouth, unsigned & totalScore, CLine & underPacMen,
             CLine & underF, std::vector<std::string> & dirF, const bool freshStart);

/**
 * @brief ShowScore affiche le score à l'écran
 * @param character est un entier qui correspond à l'input du joueur.
 * @param gameLost est un booleen qui determine si la partie est perdue.
 * @param desiredDir est un vecteur de string qui contient pour chaque joueur la direction voulue.
 * @fn void InputInterpretation(int character, bool & gameLost, std::vector<std::string> & desiredDir);
 */
void InputInterpretation(int character, bool & gameLost, std::vector<std::string> & desiredDir);

/**
 * @brief ShowScore affiche le score à l'écran
 * @param totalScore est un entier naturel qui donne le score des joueurs.
 * @fn void ShowScore(unsigned & totalScore);
 */
void ShowScore(unsigned & totalScore);

/**
 * @brief LaunchPacMen permet le démarrage du jeu et l'affichage continuel de la carte
 * @param freshGame donne vrai si le jeu est lancé pour la première fois.
 * @fn void LaunchPacMen(const bool freshGame, const bool & soloPlayer);
 */
void LaunchPacMen(const bool freshGame, const bool & soloPlayer);

/**
 * @brief SaveMap
 * @fn void SaveMap(const CMat & matrixToSave);
 */
void SaveMap(const CMat & matrixToSave);

/**
  * @brief RESET : Caractère unicode utilisé pour réinitialiser la couleur d'affichage
  */
const wchar_t RESET[] = L"\033[1;0m";

/**
  * @brief RED : Caractère unicode utilisé pour afficher en rouge
  */
const wchar_t  RED[] = L"\033[1;31m";

/**
  * @brief GREEN : Caractère unicode utilisé pour afficher en vert
  */
const wchar_t GREEN[] = L"\033[1;32m";

/**
  * @brief YELLOW : Caractère unicode utilisé pour afficher en jaune
  */
const wchar_t YELLOW[] = L"\033[1;33m";

/**
  * @brief BLUE : Caractère unicode utilisé pour afficher en bleu
  */
const wchar_t BLUE[] = L"\033[1;34m";

/**
  * @brief MAGENTA : Caractère unicode utilisé pour afficher en magenta
  */
const wchar_t MAGENTA[] = L"\033[1;35m";

/**
  * @brief CYAN : Caractère unicode utilisé pour afficher en cyan
  */
const wchar_t CYAN[] = L"\033[1;36m";

/**
  * @brief TL : Caractère unicode utilisé pour les murs en haut à gauche
  */
const wchar_t TL[] = L"╔"; //A

/**
  * @brief TR : Caractère unicode utilisé pour les murs en haut à droite
  */
const wchar_t TR[] = L"╗"; //E

/**
  * @brief DL : Caractère unicode utilisé pour les murs en bas à gauche
  */
const wchar_t DL[] = L"╚"; //Q

/**
  * @brief DR : Caractère unicode utilisé pour les murs en bas à droite
  */
const wchar_t DR[] = L"╝"; //D

/**
  * @brief H : Caractère unicode utilisé pour les murs horizontaux
  */
const wchar_t H[] = L"═"; //S

/**
  * @brief V : Caractère unicode utilisé pour les murs verticaux
  */
const wchar_t V[] = L"║"; //Z

/**
  * @brief Star : Caractère unicode utilisé pour les étoiles
  */
const wchar_t Star[] = L"★"; //2

/**
  * @brief Point : Caractère unicode utilisé pour les points du joueur 1
  */
const wchar_t Point[] = L"•"; //1

/**
  * @brief Point2 : Caractère unicode utilisé pour les points du joueur 2
  */
const wchar_t Point2[] = L"•"; //3

/**
  * @brief walkableChars : Tous les caractères sur lesquels peuvent marcher les PacMen
  */
const std::vector<char> walkableChars = {'G', 'T', '1', '2', '3', 'O', 'P', 'H', 'J', 'K', 'L'};

/**
  * @brief walkableCharsGhosts : Tous les caractères sur lesquels peuvent marcher les fantomes
  */
const std::vector<char> walkableCharsGhosts = {'G', 'T', '1', '2', '3', 'P', 'O', 'x', 'F'};

/**
  * @brief OL : Caractère unicode utilisé pour PacMen quand sa bouche est ouverte et que sa direction est vers la gauche
  */
const wchar_t OL[] = L"ᐴ";

/**
  * @brief OR : Caractère unicode utilisé pour PacMen quand sa bouche est ouverte et que sa direction est vers la droite
  */
const wchar_t OR[] = L"ᐹ";

/**
  * @brief OU : Caractère unicode utilisé pour PacMen quand sa bouche est ouverte et que sa direction est vers le haut
  */
const wchar_t OU[] = L"ᐻ";

/**
  * @brief OD : Caractère unicode utilisé pour PacMen quand sa bouche est ouverte et que sa direction est vers le bas
  */
const wchar_t OD[] = L"ᐽ";

/**
  * @brief CL : Caractère unicode utilisé pour PacMen quand sa bouche est fermée et que sa direction est vers la gauche
  */
const wchar_t CL[] = L"―";

/**
  * @brief CR : Caractère unicode utilisé pour PacMen quand sa bouche est fermée et que sa direction est vers la droite
  */
const wchar_t CR[] = L"―";

/**
  * @brief CU : Caractère unicode utilisé pour PacMen quand sa bouche est fermée et que sa direction est vers le haut
  */
const wchar_t CU[] = L"|";

/**
  * @brief CD : Caractère unicode utilisé pour PacMen quand sa bouche est fermée et que sa direction est vers le bas
  */
const wchar_t CD[] = L"|";

/**
  * @brief powerDuration : Durée en nombre d'images du pouvoir provoqué par l'étoile
  */
const unsigned powerDuration = 30;

/**
  * @brief F : caractère unicode utilisé pour tous les fantomes
  */
const wchar_t F[] = L"ɷ";

#endif // GAMEMANAGEMENT_H

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

/**
 * \file scoreboard.h
 * \brief Extraction d'informations dans un fichier, convertion en listes, affichage de score et ajout de scores
 * \author Martin Moreira de Jesus
 * \version 4.0
 * \date 21 Janvier 2021
 */

#include "nos_fichiers/type.h"

/**
 * @brief ExtractScoreBoardCoop Lis le fichier contenant le scoreboard et reinjecte les strings (noms) dans un vecteur de paires de string et les entiers (scores) dans un vecteur d'entiers
 * @param scoreList [in/out] vecteur d'entiers contenant les 5 meilleurs scores
 * @param nameList [in/out] listName vecteur de paires de strings contenant les 5 duos de noms attribuées aux 5 meilleurs scores
 * @fn void ExtractScoreBoardCoop(VUnsigned & scoreList, VPString & nameList);
 */
void ExtractScoreBoardCoop(VUnsigned & scoreList, VPString & nameList);

/**
 * @brief InsertNewScoreCoop insère, si le score y a sa place, le nouveau score dans le scoreboard pour le mode coop
 * @param scoreList [in/out] vecteur d'entiers contenant les 5 meilleurs scores
 * @param nameList [in/out] listName vecteur de paires de strings contenant les 5 duos de noms attribuées aux 5 meilleurs scores
 * @param totalScore [in] score du joueur pour la partie actuelle
 * @fn void InsertNewScoreCoop(VUnsigned & scoreList, VPString & nameList, const unsigned & totalScore);
 */
void InsertNewScoreCoop(VUnsigned & scoreList, VPString & nameList, const unsigned & totalScore);

/**
 * @brief SaveScoreBoardCoop sauvegarde dans un fichier le scoreboard du mode coop
 * @param scoreList [in] vecteur d'entiers contenant les 5 meilleurs scores
 * @param nameList [in] listName vecteur de paires de strings contenant les 5 duos de noms attribuées aux 5 meilleurs scores
 * @fn void SaveScoreBoardCoop(const VUnsigned & scoreList, VPString & nameList);
 */
void SaveScoreBoardCoop(const VUnsigned & scoreList, VPString & nameList);

/**
 * @brief ShowScoreBoardCoop montre le scoreboard du mode coop
 * @param listScore [in] vecteur d'entiers contenant les 5 meilleurs scores
 * @param listName [in] vecteur de paires de strings contenant les 5 duos de noms attribuées aux 5 meilleurs scores
 * @fn void ShowScoreBoardCoop(const VUnsigned & listScore, const VPString & listName);
 */
void ShowScoreBoardCoop(const VUnsigned & listScore, const VPString & listName);

/**
 * @brief ScoreBoardRoutineCoop Appelle les différentes fonctions nécéssaires au l'affichage et l'intégration du score du joueur dans le scoreboard pour le mode coop
 * @param totalScore [in/out] score du joueur pour la partie actuelle
 * @fn void ScoreBoardRoutineCoop(const unsigned & totalScore);
 */
void ScoreBoardRoutineCoop(const unsigned & totalScore);

/**
 * @brief ExtractScoreBoardSolo Lis le fichier contenant le scoreboard et reinjecte les strings (noms) dans un vecteur de string et les entiers (scores) dans un vecteur d'entiers
 * @param scoreList [in/out] vecteur d'entiers contenant les 5 meilleurs scores
 * @param nameList [in/out] vecteur de strings contenant les 5 noms attribuées aux 5 meilleurs scores
 * @fn void ExtractScoreBoardSolo(VUnsigned & scoreList, VString & nameList);
 */
void ExtractScoreBoardSolo(VUnsigned & scoreList, VString & nameList);

/**
 * @brief PlaceNewScoreInScoreBoardSolo renvoie la position du nouveau score dans le scoreboard pour le mode solo
 * @param scoreList [in]vecteur d'entiers contenant les 5 meilleurs scores
 * @param totalScore [in] score du joueur pour la partie actuelle
 * @return renvoie la position dans le scoreboard du nouveau score
 * @fn int PlaceNewScoreInScoreBoardSolo(VUnsigned & scoreList, const unsigned & totalScore);
 */
int PlaceNewScoreInScoreBoardSolo(VUnsigned & scoreList, const unsigned & totalScore);

/**
 * @brief InsertNewScoreSolo insère, si le score y a sa place, le nouveau score dans le scoreboard pour le mode solo
 * @param scoreList [in/out] vecteur d'entiers contenant les 5 meilleurs scores
 * @param nameList [in/out] vecteur de strings contenant les 5 noms attribuées aux 5 meilleurs scores
 * @param totalScore [in] score du joueur pour la partie actuelle
 * @fn void InsertNewScoreSolo(VUnsigned & scoreList, VString & nameList, const unsigned & totalScore);
 */
void InsertNewScoreSolo(VUnsigned & scoreList, VString & nameList, const unsigned & totalScore);

/**
 * @brief SaveScoreBoardSolo sauvegarde le scoreboard modifié dans un fichier pour le mode solo
 * @param scoreList [in] vecteur d'entiers contenant les 5 meilleurs scores
 * @param nameList [in] vecteur de strings contenant les 5 noms attribuées aux 5 meilleurs scores
 * @fn void SaveScoreBoardSolo(const VUnsigned & scoreList, VString & nameList);
 */
void SaveScoreBoardSolo(const VUnsigned & scoreList, VString & nameList);

/**
 * @brief ShowScoreBoardSolo Affiche le scoreboard pour le solo
 * @param listScore [in] vecteur d'entiers contenant les 5 meilleurs scores
 * @param listName [in] vecteur de strings contenant les 5 noms attribuées aux 5 meilleurs scores
 * @fn void ShowScoreBoardSolo(const VUnsigned & listScore, const VString & listName):
 */
void ShowScoreBoardSolo(const VUnsigned & listScore, const VString & listName);

/**
 * @brief ScoreBoardRoutineSolo Appelle les différentes fonctions nécéssaires au l'affichage et l'intégration du score du joueur dans le scoreboard pour le mode solo
 * @param totalScore [in] Score du joueur envoyé depuis pacman.cpp
 * @fn void ScoreBoardRoutineSolo(const unsigned & totalScore);
 */
void ScoreBoardRoutineSolo(const unsigned & totalScore);

#endif // SCOREBOARD_H

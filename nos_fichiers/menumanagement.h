#ifndef MENUMANAGEMENT_H
#define MENUMANAGEMENT_H

/**
 * \file menumanagement.h
 * \brief Convertion de fichiers en matrice, affichage de matrice, navigation des menus
 * \author Martin Moreira de Jesus
 * \author Loncaric Léon
 * \author Felix Deltenre
 * \version 2.0
 * \date 10 Janvier 2021
 */

#include "nos_fichiers/type.h"

/**
 * @brief ClearScreen efface l'écran
 * @fn void ClearScreen();
 */
void ClearScreen();

/**
 * @brief ReadMatrix Lis et affiche la matrice
 * @param matrixToRead [in] matrice qui doit être lue
 * @fn void ReadMatrix (const CMat & matrixToRead);
 */
void ReadMatrix (const CMat & matrixToRead);

/**
 * @brief ConvertTxtToMatrix Lis le texte attribuée au menu et le converti en matrice pour les autres fonctions
 * @param matrixToFill [in/out] matrice qu'on souhaite remplir
 * @param fileToRead [in] fichier à convertir en matrice
 * @fn void ConvertTxtToMatrix(CMat & matrixToFill, const std::string & fileToRead);
 */
void ConvertTxtToMatrix(CMat & matrixToFill, const std::string & fileToRead);

/**
 * @brief SeekCurrentPointersPos chercher la position des pointeurs ('>' et '<') pour connaître leur position sur les colonnes et les lignes afin de les supprimer dans le cas de changement de position des pointeurs
 * @param matrixToRead [in] matrice ou on souhaite trouver les pointeurs
 * @fn void SeekCurrentPointersPos(const CMat & matrixToRead);
 */
void SeekCurrentPointersPos(const CMat & matrixToRead);

/**
 * @brief UpdatePointers bouger les pointeurs en haut ou en bas en fonction de la position visée (aimedPointerXPos)
 * @param matrixToUpdate [in/out] matrice ou on souhaite mettre a jour la position des pointeurs
 * @param aimedPointersXPos [in] position visée des pointeurs
 * @param minPos [in] valeur minimale que peut attenindre les pointeurs, si la position visée est inférieure à minPos, on envoie les pointeurs à l'opposé (maxPos-1)
 * @param maxPos [in] valeur maximale que peut atteindre les pointeurs, si la position visée est supérieure à maxPos, on envoie les pointeurs à l'opposé (minPos+1)
 * @fn void UpdatePointers(CMat & matrixToUpdate, unsigned aimedPointersXPos, const unsigned & minPos, const unsigned & maxPos);
 */
void UpdatePointers(CMat & matrixToUpdate, unsigned aimedPointersXPos, const unsigned & minPos, const unsigned & maxPos);

/**
 * @brief SelectOption selectionne la bonne option en fonction du menu ouvert
 * @param menuName [in] nom du menu ouvert, sert à savoir quelle option les pointeurs visent en fonction du menu
 * @fn void SelectOption(std::string menuName);
 */
void SelectOption(std::string menuName);

/**
 * @brief PreviousPage selectionne la page précédente en fonction du menu sur le quel on se trouve
 * @param menuName nom du menu ouvert, sert à savoir sur quelle page on va retourner
 * @fn void PreviousPage(const std::string & menuName);
 */
void PreviousPage(const std::string & menuName);

/**
 * @brief NavigateMenu Initialise et permet de naviguer le menu sélectionné
 * @param fileName [in] nom du fichier ou se trouve le menu, on le donnera en paramètre à ConvertTxtToMatrix
 * @param menuName [in] nom du menu ouvert, sert à renseigner le menu dans le quel on se trouve pour les fonctions SelectOption et PreviousPage
 * @param minPosMenu [in] on renseigne la position minimale des pointeurs dans le menu pour transférer plus tard l'info à la fonction UpdatePointers
 * @param maxPosMenu [in] on renseigne la position maximale des pointeurs dans le menu pour transférer plus tard l'info à la fonction UpdatePointers
 * @fn void NavigateMenu(const std::string & fileName, const std::string & menuName, const unsigned & minPosMenu, const unsigned & maxPosMenu);
 */
void NavigateMenu(const std::string & fileName, const std::string & menuName, const unsigned & minPosMenu, const unsigned & maxPosMenu);

#endif // MENUMANAGEMENT_H

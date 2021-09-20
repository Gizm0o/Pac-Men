#ifndef TYPE_H
#define TYPE_H

/**
 * \file type.h
 * \brief Définition des types
 * \author Martin Moreira de Jesus
 * \version 1.0
 * \date 13 Janvier 2021
 */

#include <vector>
#include <string>

typedef std::vector<char> CLine;
typedef std::vector<CLine> CMat;
typedef std::pair<unsigned,unsigned> UPair;
typedef std::vector<unsigned> VUnsigned;
typedef std::vector<std::pair<std::string,std::string>> VPString;
typedef std::vector<std::string> VString;

#endif // TYPE_H

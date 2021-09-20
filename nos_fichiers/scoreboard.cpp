#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include "nos_fichiers/menumanagement.h"
#include "nos_fichiers/scoreboard.h"
#include "nos_fichiers/type.h"

using namespace std;

void ExtractScoreBoardCoop(VUnsigned & scoreList, VPString & nameList)
{
    ifstream readFile ("../PacMen/Data/scorelistCoop.txt");
    if (!readFile.is_open()) {
        wcout << "il y a eu un problème";
        exit(0);
    }
    pair <string, string> names;
    unsigned readScore;
    while (readFile >> names.first >> names.second >> readScore) {
        nameList.push_back(make_pair(names.first, names.second));
        scoreList.push_back(readScore);
    }
}

void ExtractScoreBoardSolo(VUnsigned & scoreList, VString & nameList)
{
    ifstream readFile ("../PacMen/Data/scorelistSolo.txt");
    if (!readFile.is_open()) {
        wcout << "il y a eu un problème";
        exit(0);
    }
    string names;
    unsigned readScore;
    while (readFile >> names >> readScore) {
        nameList.push_back(names);
        scoreList.push_back(readScore);
    }
}

int PlaceNewScoreInScoreBoard(VUnsigned & scoreList, const unsigned & totalScore)
{
    unsigned scorePlace (0);
    for (unsigned i (0); i < scoreList.size()-1; ++i){
        if (scoreList[i] > totalScore) {
            scorePlace = i+1;
        } else if (scoreList[i] == totalScore) {
            scorePlace = i;
            return scorePlace;
        }
    }
    return scorePlace;
}

void InsertNewScoreSolo(VUnsigned & scoreList, VString & nameList, const unsigned & totalScore)
{
    string givenNames;
    wcout << "What is the player's name ? : ";
    cin >> givenNames;
    while (givenNames.size() > 11) {
        wcout << "Choose a name with less than 11 characters : ";
        cin >> givenNames;
    }
    unsigned newScorePlace (PlaceNewScoreInScoreBoard(scoreList, totalScore));
    for (unsigned i (scoreList.size()-1); i > newScorePlace; --i)
    {
        scoreList[i]=scoreList[i-1];
        nameList[i]=nameList[i-1];
    }
    nameList[newScorePlace] = givenNames;
    scoreList[newScorePlace] = totalScore;
}

void InsertNewScoreCoop(VUnsigned & scoreList, VPString & nameList, const unsigned & totalScore)
{
    pair<string, string> givenNames;
    wcout << "What is the first player's name ? : ";
    cin >> givenNames.first;
    while (givenNames.first.size() > 11) {
        wcout << "Choose a name with less than 11 characters : ";
        cin >> givenNames.first;
    }
    wcout << "What is the second player's name ? : ";
    cin >> givenNames.second;
    while (givenNames.second.size() > 11) {
        wcout << "Choose a name with less than 11 characters : ";
        cin >> givenNames.second;
    }
    unsigned newScorePlace (PlaceNewScoreInScoreBoard(scoreList, totalScore));
    for (unsigned i (scoreList.size()-1); i > newScorePlace; --i)
    {
        scoreList[i]=scoreList[i-1];
        nameList[i]=nameList[i-1];
    }
    nameList[newScorePlace] = givenNames;
    scoreList[newScorePlace] = totalScore;
}

void SaveScoreBoardSolo(const VUnsigned & scoreList, VString & nameList)
{
    ofstream saveFile("../PacMen/Data/scorelistSolo.txt"/*, ios::out | ios::trunc*/);
    if (!saveFile.is_open()){
        wcout << "il y a eu un problème";
        exit(0);
    }
    for (unsigned i (0); i < scoreList.size(); ++i)
    {
        saveFile << nameList[i] << ' ' << scoreList[i] << endl;
    }
    saveFile.close();
}

void SaveScoreBoardCoop(const VUnsigned & scoreList, VPString & nameList)
{
    ofstream saveFile("../PacMen/Data/scorelistCoop.txt");
    if (!saveFile.is_open()){
        wcout << "il y a eu un problème";
        exit(0);
    }
    for (unsigned i (0); i < scoreList.size(); ++i)
    {
        saveFile << nameList[i].first << ' ' << nameList[i].second << ' ' << scoreList[i] << endl;
    }
    saveFile.close();
}

void ShowCharByChar(string listName)
{
    for (const auto & val: listName)
    {
        wcout << val;
    }
}

void ShowScoreBoardSolo(const VUnsigned & listScore, const VString & listName)
{
    wcout << "\033[H\033[2J";
    wcout << '\t' << '\t' << '\t' << "Scoreboard" << endl << endl;
    for (unsigned i (0); i < listScore.size(); ++i)
    {
        wcout << '\t' << '\t' << '\t';
        ShowCharByChar(listName[i]);
        wcout << " : " << listScore[i] << endl;
    }
    wcout << endl;
}

void ShowScoreBoardCoop(const VUnsigned & listScore, const VPString & listName)
{
    wcout << "\033[H\033[2J";
    wcout << '\t' << '\t' << '\t' << "Scoreboard" << endl << endl;
    for (unsigned i (0); i < listScore.size(); ++i)
    {
        wcout << '\t' << '\t';
        ShowCharByChar(listName[i].first);
        wcout << " and ";
        ShowCharByChar(listName[i].second);
        wcout << " : " << listScore[i] << endl;
    }
    wcout << endl;
}

void ScoreBoardRoutineSolo(const unsigned & totalScore)
{
    endwin();
    VUnsigned scoreList (0);
    VString nameList (0);
    ExtractScoreBoardSolo(scoreList, nameList);
    ShowScoreBoardSolo(scoreList, nameList);
    InsertNewScoreSolo(scoreList, nameList, totalScore);
    ShowScoreBoardSolo(scoreList, nameList);
    SaveScoreBoardSolo(scoreList, nameList);
    wcout << "returning to title screen in 5 seconds..." << endl;
    usleep(5000000);
    NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
}

void ScoreBoardRoutineCoop (const unsigned & totalScore)
{
    erase();
    endwin();
    VUnsigned scoreList (0);
    VPString nameList (0);
    ExtractScoreBoardCoop(scoreList, nameList);
    ShowScoreBoardCoop(scoreList, nameList);
    InsertNewScoreCoop(scoreList, nameList, totalScore);
    ShowScoreBoardCoop(scoreList, nameList);
    SaveScoreBoardCoop(scoreList, nameList);
    wcout << "returning to title screen in 5 seconds..." << endl;
    usleep(5000000);
    NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
}

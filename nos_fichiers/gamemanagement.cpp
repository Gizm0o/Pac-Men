#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include <bits/stdc++.h>
#include "nos_fichiers/menumanagement.h"
#include "nos_fichiers/kbhit.h"
#include "nos_fichiers/gamemanagement.h"
#include "nos_fichiers/type.h"

using namespace std;

unsigned totalScore = 0;
bool otherColorSheme = false;

void ChangeColorSheme(const string & scheme){
    if (scheme == "jungle" || otherColorSheme){
        otherColorSheme = !otherColorSheme;
    } else if (scheme == "classic" || !otherColorSheme) {
        otherColorSheme = !otherColorSheme;
    }
}


unsigned FetchScore(){
    return totalScore;
}

void KillGhost(UPair ghostPlace, CMat & dataMap, unsigned & totalScore, CLine & underF, vector<string> & dirF){
    char ghost = dataMap[ghostPlace.first][ghostPlace.second];
    if(ghost == 'H' || ghost == 'J' || ghost == 'K' || ghost == 'L'){
        totalScore+=10;
        pair<unsigned, unsigned> ghostBasePlace;
        switch (ghost) {
            case 'H':
            dataMap[ghostPlace.first][ghostPlace.second] = underF[0];
            dirF[0] = "up";
            underF[0] = 'F';
            break;
            case 'J':
            dataMap[ghostPlace.first][ghostPlace.second] = underF[1];
            dirF[1] = "up";
            underF[1] = 'F';
            break;
            case 'K':
            dataMap[ghostPlace.first][ghostPlace.second] = underF[2];
            dirF[2] = "up";
            underF[2] = 'F';
            break;
            case 'L':
            dataMap[ghostPlace.first][ghostPlace.second] = underF[3];
            dirF[3] = "up";
            underF[3] = 'F';
            break;
        }
        ifstream ifs ("../PacMen/Data/dataMap2.txt");
        char ch;
        pair<unsigned, unsigned> activeCase = make_pair(0,0);
        while (!ifs.eof()) {
            ifs.get(ch);
            if (ch == '\n'){
                activeCase.first = activeCase.first + 1;
                activeCase.second = 0;
            }
            else if(ch == 'F'){
                ghostBasePlace = make_pair(activeCase.first, activeCase.second-1) ;
                break;
            }
            activeCase.second+=1;
        }
        dataMap[ghostBasePlace.first][ghostBasePlace.second] = ghost;
    }

}

void ResetAllMap(bool & gameLost, CLine & underPacMen, CLine & underF, vector<string> & desiredDir, vector<string> & activeDir, vector<string> & dirF, unsigned & powerRemainingTime){
    gameLost = false;
    underPacMen = {'G', 'G'};
    underF = {'F', 'F', 'F', 'F'};
    desiredDir = {"", ""};
    activeDir = {"", ""};
    dirF = {"up","up","up","up"};
    powerRemainingTime = 0;
    totalScore = 0;
}

void GameLost(){
    usleep(2500);
    erase();
    NavigateMenu("../PacMen/Data/gameover.txt", "gameover", 23, 26);
}

bool GameFinished(CMat & dataMap){
    for(unsigned line = 0; line < dataMap.size(); ++line){
        for(unsigned column = 0; column < dataMap[line].size(); ++column){
            if(dataMap[line][column] == '1'  || dataMap[line][column] == '2' || dataMap[line][column] == '3' ){
                return false;
            }
        }
    }
    return true;
}

bool VectorContains(vector<char> vector, char character){
    return count(vector.begin(), vector.end(), character);
}

bool IsAimedForPacMen(string  player, UPair & aimedPos, vector<vector<char>> & dataMap, unsigned & totalScore, unsigned & powerRemainingTime, CLine & underF, vector<string> & dirF)
{
    if(dataMap[aimedPos.first][aimedPos.second] == '2'){
        powerRemainingTime = powerDuration;
        return true;
    }
    else if((player =="player2" && dataMap[aimedPos.first][aimedPos.second] == 'P')
            || (player =="player1" && dataMap[aimedPos.first][aimedPos.second] == 'O')){
        GameLost();
        return false;
    }
    else if((dataMap[aimedPos.first][aimedPos.second] == 'H' || dataMap[aimedPos.first][aimedPos.second] == 'J'
            || dataMap[aimedPos.first][aimedPos.second] == 'K' || dataMap[aimedPos.first][aimedPos.second] == 'L') && powerRemainingTime > 0){
        KillGhost(make_pair(aimedPos.first, aimedPos.second), dataMap, totalScore,  underF,  dirF);
        return false;
    }
    else if((dataMap[aimedPos.first][aimedPos.second] == 'H' || dataMap[aimedPos.first][aimedPos.second] == 'J'
             || dataMap[aimedPos.first][aimedPos.second] == 'K' || dataMap[aimedPos.first][aimedPos.second] == 'L')){
        GameLost();
        return false;
    }
    else if (player =="player1" && dataMap[aimedPos.first][aimedPos.second] == '1')
        return true;
    else if (player =="player2" && dataMap[aimedPos.first][aimedPos.second] == '3')
        return true;
    return false;
}

bool IsAimedForGhost(UPair & aimedPos, UPair activePos, CMat & dataMap, unsigned & totalScore, CLine & underF, vector<string> & dirF, unsigned & powerRemainingTime)
{
    if ((dataMap[aimedPos.first][aimedPos.second] == 'P' || dataMap[aimedPos.first][aimedPos.second] == 'O') && powerRemainingTime == 0) {
        GameLost();
        return true;
    }
    else if(dataMap[aimedPos.first][aimedPos.second] == 'P' || dataMap[aimedPos.first][aimedPos.second] == 'O') {
        KillGhost(activePos, dataMap, totalScore, underF,  dirF);
        return true;
    }
    return false;
}

void GenerateMatriceFromTxt(CMat & dataMap, const string & mapToOpen, bool freshGame){
    dataMap.clear();
    setlocale(LC_ALL, "");
    ifstream ifs (mapToOpen);
    char ch;
    dataMap.push_back({});
    unsigned column = 0;
    while (!ifs.eof()) {
        ifs.get(ch);
        if((ch == '\n'&& freshGame) ||( ch =='\r' && !freshGame)){
            dataMap.push_back({});
            column = 0;
        }
        else{
            dataMap[dataMap.size()-1].push_back(ch);
            column+=1;
        }
    }
}

void MovePlayerInDataMap(UPair activePos, UPair nextPos, bool & done1, bool & done2, bool forced, CMat & dataMap, unsigned & totalScore, CLine & underPacMen, vector<string> & desiredDir, vector<string> & activeDir, CLine & underF, vector<string> & dirF, unsigned & powerRemainingTime){
    char player = dataMap[activePos.first][activePos.second];
    if((player == 'P' && !done1) || (player == 'O' && !done2)){
        if (player == 'P'){
            dataMap[activePos.first][activePos.second] = underPacMen[0];
            if (!IsAimedForPacMen("player1", nextPos, dataMap,  totalScore,  powerRemainingTime,  underF,  dirF)) {
                underPacMen[0] = dataMap[nextPos.first][nextPos.second];
            } else {
                underPacMen[0] = 'G';
                totalScore+=1;
            }
        } else {
            dataMap[activePos.first][activePos.second] = underPacMen[1];
            if (!IsAimedForPacMen("player2", nextPos, dataMap,  totalScore,  powerRemainingTime,  underF,  dirF)) {
                underPacMen[1] = dataMap[nextPos.first][nextPos.second];
            } else {
                underPacMen[1] = 'G';
                totalScore+=1;
            }
        }
    dataMap[nextPos.first][nextPos.second] = player;
    if(!forced){
        player == 'P' ? activeDir[0] = desiredDir[0] : activeDir[1] = desiredDir[1];
    }
    player == 'P' ? done1 = true : done2 = true;
   }
}

void MovePacMen(CMat & dataMap, vector<string> & desiredDir, vector<string> & activeDir, bool & pacManMouth, unsigned & totalScore, CLine & underPacMen, CLine & underF, vector<string> & dirF, unsigned & powerRemainingTime, const bool freshStart){
    bool done = false;
    bool done2 = false;
    for(unsigned line = 0; line < dataMap.size(); ++line){
        for(unsigned column = 0; column < dataMap[line].size(); ++column){
            pair<unsigned, unsigned> activePos (line, column);
            if(done && done2){
                break;
            }
            else if(dataMap[line][column] == 'P' || dataMap[line][column] == 'O'){
                if(((desiredDir[0] == "up" && dataMap[line][column] == 'P') || (desiredDir[1] == "up" && dataMap[line][column] == 'O'))
                        && VectorContains(walkableChars, dataMap[line-1][column])){
                    pair<unsigned, unsigned> nextPos (line-1, column);
                    MovePlayerInDataMap(activePos, nextPos, done, done2, false,  dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                }
                else if(((desiredDir[0] == "down" && dataMap[line][column] == 'P') || (desiredDir[1] == "down" && dataMap[line][column] == 'O')) && VectorContains(walkableChars, dataMap[line+1][column])){
                    pair<unsigned, unsigned> nextPos (line+1, column);
                    MovePlayerInDataMap(activePos, nextPos, done, done2, false, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                }
                else if(((desiredDir[0] == "left" && dataMap[line][column] == 'P') || (desiredDir[1] == "left" && dataMap[line][column] == 'O')) && VectorContains(walkableChars, dataMap[line][column-2])){
                    if(dataMap[line][column-2] == 'T'){

                        pair<unsigned, unsigned> nextPos;
                        nextPos.first = line;
                        if( freshStart){
                            nextPos.second = dataMap[nextPos.first].size()-4;
                        }
                        else{
                            nextPos.second = dataMap[nextPos.first].size()-3;
                        }
                        MovePlayerInDataMap(activePos, nextPos, done, done2, false, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                    else{
                        pair<unsigned, unsigned> nextPos (line, column-2);
                        MovePlayerInDataMap(activePos, nextPos, done, done2, false, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                }
                else if(((desiredDir[0] == "right" && dataMap[line][column] == 'P') || (desiredDir[1] == "right" && dataMap[line][column] == 'O')) && VectorContains(walkableChars, dataMap[line][column+2])){
                    if(dataMap[line][column+2] == 'T'){
                        pair<unsigned, unsigned> nextPos (line, 2);
                        MovePlayerInDataMap(activePos, nextPos, done, done2, false, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                    else{
                        pair<unsigned, unsigned> nextPos (line, column+2);
                        MovePlayerInDataMap(activePos, nextPos, done, done2, false, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                }
                else if(((activeDir[0] == "up" && dataMap[line][column] == 'P') || (activeDir[1] == "up" && dataMap[line][column] == 'O'))
                        && VectorContains(walkableChars, dataMap[line-1][column])){
                    pair<unsigned, unsigned> nextPos (line-1, column);
                    MovePlayerInDataMap(activePos, nextPos, done, done2, true, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                }
                else if(((activeDir[0] == "down" && dataMap[line][column] == 'P') || (activeDir[1] == "down" && dataMap[line][column] == 'O'))
                        && VectorContains(walkableChars, dataMap[line+1][column])){
                    pair<unsigned, unsigned> nextPos (line+1, column);
                    MovePlayerInDataMap(activePos, nextPos, done, done2, true, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                }
                else if(((activeDir[0] == "left" && dataMap[line][column] == 'P') || (activeDir[1] == "left" && dataMap[line][column] == 'O'))
                        && VectorContains(walkableChars, dataMap[line][column-2])){
                    if(dataMap[line][column-2] == 'T'){
                        pair<unsigned, unsigned> nextPos;
                        nextPos.first = line;
                        if( freshStart){
                            nextPos.second = dataMap[nextPos.first].size()-4;
                        }
                        else{
                            nextPos.second = dataMap[nextPos.first].size()-3;
                        }
                        MovePlayerInDataMap(activePos, nextPos, done, done2, true, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                    else{
                        pair<unsigned, unsigned> nextPos (line, column-2);
                        MovePlayerInDataMap(activePos, nextPos, done, done2, true, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                }
                else if(((activeDir[0] == "right" && dataMap[line][column] == 'P') || (activeDir[1] == "right" && dataMap[line][column] == 'O'))
                        && VectorContains(walkableChars, dataMap[line][column+2])){
                    if(dataMap[line][column+2] == 'T'){
                        pair<unsigned, unsigned> nextPos (line, 2);
                        MovePlayerInDataMap(activePos, nextPos, done, done2, true, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                    else{
                        pair<unsigned, unsigned> nextPos (line, column+2);
                        MovePlayerInDataMap(activePos, nextPos, done, done2, true, dataMap, totalScore,  underPacMen, desiredDir,  activeDir,  underF,  dirF, powerRemainingTime);
                    }
                }
                else{ //Stuck
                    dataMap[line][column] == 'P' ? done = true : done2 = true;
                }
            }
        }
    }
    pacManMouth = !pacManMouth;

}

void RefreshPacMenAnimation(char Player, vector<string> & activeDir, bool & pacManMouth){

    if(Player == 'P'){
        if(activeDir[0] == "up"){
            if(pacManMouth){
                if(otherColorSheme){
                    wcout << YELLOW << OU << RESET;
                }
                else{
                    wcout << GREEN << OU << RESET;
                }
            }
            else{
                if(otherColorSheme){
                    wcout << YELLOW << CU << RESET;
                }
                else{
                    wcout << GREEN << CU << RESET;
                }                  }
        }
        else if(activeDir[0] == "down"){
            if(pacManMouth){
                if(otherColorSheme){
                    wcout << YELLOW << OD << RESET;
                }
                else{
                    wcout << GREEN << OD << RESET;
                }                  }
            else{
                if(otherColorSheme){
                    wcout << YELLOW << CD << RESET;
                }
                else{
                    wcout << GREEN << CD << RESET;
                }                  }
        }
        else if(activeDir[0] == "right"){
            if(pacManMouth){
                if(otherColorSheme){
                    wcout << YELLOW << OR << RESET;
                }
                else{
                    wcout << GREEN << OR << RESET;
                }                  }
            else{
                if(otherColorSheme){
                    wcout << YELLOW << CR << RESET;
                }
                else{
                    wcout << GREEN << CR << RESET;
                }                  }
        }
        else if(activeDir[0] == "left"){
            if(pacManMouth){
                if(otherColorSheme){
                    wcout << YELLOW << OL << RESET;
                }
                else{
                    wcout << GREEN << OL << RESET;
                }                  }
            else{
                if(otherColorSheme){
                    wcout << YELLOW << CL << RESET;
                }
                else{
                    wcout << GREEN << CL << RESET;
                }
            }
        }
        else{
            if(otherColorSheme){
                wcout << YELLOW << CR << RESET;
            }
            else{
                wcout << GREEN << CR << RESET;
            }
        }
    }
    else{
        if(activeDir[1] == "up"){
            if(!pacManMouth){
                if(otherColorSheme){
                    wcout << RED << OU << RESET;
                }
                else{
                    wcout << MAGENTA << OU << RESET;
                }
            }
            else{
                if(otherColorSheme){
                    wcout << RED << CU << RESET;
                }
                else{
                    wcout << MAGENTA << CU << RESET;
                }            }

        }
        else if(activeDir[1] == "down"){
            if(!pacManMouth){
                if(otherColorSheme){
                    wcout << RED << OD << RESET;
                }
                else{
                    wcout << MAGENTA << OD << RESET;
                }            }
            else{
                if(otherColorSheme){
                    wcout << RED << CD << RESET;
                }
                else{
                    wcout << MAGENTA << CD << RESET;
                }            }
        }
        else if(activeDir[1] == "right"){
            if(!pacManMouth){
                if(otherColorSheme){
                    wcout << RED << OR << RESET;
                }
                else{
                    wcout << MAGENTA << OR << RESET;
                }            }
            else{
                if(otherColorSheme){
                    wcout << RED << CR << RESET;
                }
                else{
                    wcout << MAGENTA << CR << RESET;
                }            }
        }
        else if(activeDir[1] == "left"){
            if(!pacManMouth){
                if(otherColorSheme){
                    wcout << RED << OL << RESET;
                }
                else{
                    wcout << MAGENTA << OL << RESET;
                }            }
            else{
                if(otherColorSheme){
                    wcout << RED << CL << RESET;
                }
                else{
                    wcout << MAGENTA << CL << RESET;
                }            }
        }
        else{
            if(otherColorSheme){
                wcout << RED << CR << RESET;
            }
            else{
                wcout << MAGENTA << CR << RESET;
            }        }
    }
}
vector<string> DirectionsAvailableForGhost(char & ghost, UPair & activePos, string & refusedDirection, CMat & dataMap, vector<string> & dirF){
    vector<string> availableDirections = {};
    if(VectorContains(walkableCharsGhosts ,dataMap[activePos.first+1][activePos.second])  ){

        if((ghost == 'H' && dirF[0] != "up") || (ghost == 'J' && dirF[1] != "up")
               || (ghost == 'K' && dirF[2] != "up") || (ghost == 'L' && dirF[3] != "up")){
            availableDirections.push_back("down");

        }
        else{
            refusedDirection = "down";
        }
    }
    if(VectorContains(walkableCharsGhosts ,dataMap[activePos.first-1][activePos.second])){
        if((ghost == 'H' && dirF[0] != "down") || (ghost == 'J' && dirF[1] != "down")
                || (ghost == 'K' && dirF[2] != "down") || (ghost == 'L' && dirF[3] != "down")){
            availableDirections.push_back("up");

        }
        else{
            refusedDirection = "up";
        }

    }
    if(VectorContains(walkableCharsGhosts ,dataMap[activePos.first][activePos.second+2])){
        if((ghost == 'H' && dirF[0] != "left") || (ghost == 'J' && dirF[1] != "left")
                || (ghost == 'K' && dirF[2] != "left") || (ghost == 'L' && dirF[3] != "left")){
            availableDirections.push_back("right");

        }
        else{
            refusedDirection = "right";
        }

    }
    if(VectorContains(walkableCharsGhosts ,dataMap[activePos.first][activePos.second-2])){
        if((ghost == 'H' && dirF[0] != "right") || (ghost == 'J' && dirF[1] != "right")
                || (ghost == 'K' && dirF[2] != "right") || (ghost == 'L' && dirF[3] != "right")){
            availableDirections.push_back("left");
        }
        else{
            refusedDirection = "left";
        }
    }

    if(availableDirections.size() == 0){
        availableDirections.push_back(refusedDirection);
    }

    return availableDirections;
}

void MoveGhostToNextPos(string & nextDirection, char & ghost, UPair & activePos, UPair & nextPosition, CMat & dataMap, CLine & underF, vector<string> & dirF, unsigned & totalScore, unsigned & powerRemainingTime, const bool freshStart){
    if(nextDirection == "right"){
        if(dataMap[nextPosition.first][nextPosition.second] == 'T'){
            nextPosition.second = 2;
        }
    }
    else if(nextDirection == "left"){
        if(dataMap[nextPosition.first][nextPosition.second] == 'T'){
            if(freshStart){
                nextPosition.second = dataMap[nextPosition.first].size()-4;
            }
            else{
                nextPosition.second = dataMap[nextPosition.first].size()-3;

            }
        }
    }

    if(nextDirection.size() > 0){

        if(!IsAimedForGhost(nextPosition, activePos, dataMap,  totalScore,  underF,  dirF,  powerRemainingTime)) {
            switch (ghost) {
                case 'H':
                dirF[0] = nextDirection;
                dataMap[activePos.first][activePos.second] = underF[0];
                underF[0] = dataMap[nextPosition.first][nextPosition.second];
                dataMap[nextPosition.first][nextPosition.second] = 'H';
                break;
                case 'J':
                dirF[1] = nextDirection;
                dataMap[activePos.first][activePos.second] = underF[1];
                underF[1] = dataMap[nextPosition.first][nextPosition.second];
                dataMap[nextPosition.first][nextPosition.second] = 'J';
                break;
                case 'K':
                dirF[2] = nextDirection;
                dataMap[activePos.first][activePos.second] = underF[2];
                underF[2] = dataMap[nextPosition.first][nextPosition.second];
                dataMap[nextPosition.first][nextPosition.second] = 'K';
                break;
                case 'L':
                dirF[3] = nextDirection;
                dataMap[activePos.first][activePos.second] = underF[3];
                underF[3] = dataMap[nextPosition.first][nextPosition.second];
                dataMap[nextPosition.first][nextPosition.second] = 'L';
                break;
            }
        }


    }
}

void MoveGhost(UPair activePos, CMat & dataMap, vector<string> & dirF, CLine & underF, unsigned & totalScore, unsigned & powerRemainingTime, const bool freshStart){
    char ghost = dataMap[activePos.first][activePos.second];
    vector<string> availableDirections = {};
    string nextDirection = "";
    string refusedDirection = "";
    pair<unsigned, unsigned> nextPosition = make_pair(0,0);
    availableDirections = DirectionsAvailableForGhost(ghost, activePos, refusedDirection,  dataMap, dirF);
    srand((unsigned) time(0));
    int result = 1 + (rand() % availableDirections.size());
    switch (result) {
        case 1:
        nextDirection = availableDirections[0];
        break;
        case 2:
        nextDirection = availableDirections[1];
        break;
        case 3:
        nextDirection = availableDirections[2];
        break;
        case 4:
        nextDirection = availableDirections[3];
        break;
    }
    if(nextDirection == "up" ) {
        nextPosition = make_pair(activePos.first-1, activePos.second);
    }
    else if(nextDirection == "down" ){
        nextPosition = make_pair(activePos.first+1, activePos.second);
    }
    else if(nextDirection == "left" ){
        nextPosition = make_pair(activePos.first, activePos.second-2);
    }
    else if(nextDirection == "right" ){
        nextPosition = make_pair(activePos.first, activePos.second+2);
    }
    MoveGhostToNextPos(nextDirection, ghost, activePos, nextPosition,  dataMap,  underF,  dirF,  totalScore,  powerRemainingTime, freshStart);
}

void SearchForGhostsInDataMap(CMat & dataMap, vector<string> & dirF, CLine & underF, unsigned & totalScore, unsigned & powerRemainingTime, const bool freshStart){
    bool done1 = false;
    bool done2 = false;
    bool done3 = false;
    bool done4 = false;
    for(unsigned line = 0; line < dataMap.size(); ++line){
        for(unsigned column = 0; column < dataMap[line].size(); ++column){
            if(dataMap[line][column] == 'H' || dataMap[line][column] == 'J'|| dataMap[line][column] == 'K' || dataMap[line][column] == 'L'){

                switch (dataMap[line][column]) {
                case 'H':
                    if(!done1){
                        pair<unsigned, unsigned> ghostPos = make_pair(line, column);
                        MoveGhost(ghostPos, dataMap, dirF,  underF,  totalScore,  powerRemainingTime, freshStart);
                    }
                    done1 = true;
                    break;
                case 'J':
                    if(!done2){
                        pair<unsigned, unsigned> ghostPos = make_pair(line, column);
                        MoveGhost(ghostPos, dataMap, dirF,   underF,  totalScore,  powerRemainingTime, freshStart);
                    }
                    done2 = true;
                    break;
                case 'K':
                    if(!done3){
                        pair<unsigned, unsigned> ghostPos = make_pair(line, column);
                        MoveGhost(ghostPos, dataMap, dirF,   underF,  totalScore,  powerRemainingTime, freshStart);
                    }
                    done3 = true;
                    break;
                case 'L':
                    if(!done4){
                        pair<unsigned, unsigned> ghostPos = make_pair(line, column);
                        MoveGhost(ghostPos, dataMap, dirF,   underF,  totalScore,  powerRemainingTime, freshStart);
                    }
                    done4 = true;
                    break;
                }
            }
        }
    }
}

void DrawMap(CMat & dataMap, bool & gameLost, unsigned & powerRemainingTime, vector<string> & desiredDir, vector<string> & activeDir, bool & pacManMouth, unsigned & totalScore, CLine & underPacMen, CLine & underF, vector<string> & dirF, const bool freshStart){
    if (!gameLost){
        MovePacMen( dataMap,  desiredDir, activeDir,  pacManMouth,  totalScore,  underPacMen,  underF,  dirF, powerRemainingTime, freshStart);
        SearchForGhostsInDataMap(dataMap, dirF,  underF,  totalScore, powerRemainingTime, freshStart);
    }
    setlocale(LC_ALL, "");
    ifstream ifs ("../PacMen/Data/map2.txt");
    char ch;
    pair<unsigned, unsigned> activeCase = make_pair(0,0);
    while (!ifs.eof()) {
        ifs.get(ch);
        if (ch == '\n'){
            activeCase.first = activeCase.first + 1;
            activeCase.second = 0;
            wcout << '\n';
        }
        else{
            if(dataMap[activeCase.first][activeCase.second] == 'P'){
                RefreshPacMenAnimation('P', activeDir,  pacManMouth);
            }
            else if((dataMap[activeCase.first][activeCase.second] == 'H'
                    || dataMap[activeCase.first][activeCase.second] == 'J'
                    || dataMap[activeCase.first][activeCase.second] == 'K'
                    || dataMap[activeCase.first][activeCase.second] == 'L')
                    && powerRemainingTime > 0){
                if(otherColorSheme){
                    wcout << BLUE << F << RESET;
                }
                else{
                    wcout << BLUE << F << RESET;
                }            }
            else if(dataMap[activeCase.first][activeCase.second] == 'H'){
                if(otherColorSheme){
                    wcout << YELLOW << F << RESET;
                }
                else{
                    wcout << GREEN << F << RESET;
                }            }
            else if(dataMap[activeCase.first][activeCase.second] == 'J'){
                if(otherColorSheme){
                    wcout << GREEN << F << RESET;
                }
                else{
                    wcout << YELLOW << F << RESET;
                }            }
            else if(dataMap[activeCase.first][activeCase.second] == 'K'){
                if(otherColorSheme){
                    wcout << BLUE << F << RESET;
                }
                else{
                    wcout << RED << F << RESET;
                }            }
            else if(dataMap[activeCase.first][activeCase.second] == 'L'){
                if(otherColorSheme){
                    wcout << CYAN << F << RESET;
                }
                else{
                    wcout << MAGENTA << F << RESET;
                }
            }
            else if(dataMap[activeCase.first][activeCase.second] == 'O'){

                RefreshPacMenAnimation('O', activeDir,  pacManMouth);
            }
            else if(isdigit(dataMap[activeCase.first][activeCase.second] )){
                switch (dataMap[activeCase.first][activeCase.second]) {
                case '1':
                    if(otherColorSheme){
                        wcout << YELLOW << Point << RESET;
                    }
                    else{
                        wcout << GREEN << Point << RESET;
                    }
                    break;
                case '2':
                    if(otherColorSheme){
                        wcout << BLUE << Star << RESET;
                    }
                    else{
                        wcout << YELLOW << Star << RESET;
                    }
                    break;
                case '3':
                    if(otherColorSheme){
                        wcout << RED << Point2 << RESET;
                    }
                    else{
                        wcout << MAGENTA << Point2 << RESET;
                    }
                    break;
                }
            }
            else{
                switch (ch)
                {
                case 'A':
                    if(otherColorSheme){
                        wcout << GREEN << TL << RESET;
                    }
                    else{
                        wcout << BLUE << TL << RESET;
                    }
                    break;
                case 'E':
                    if(otherColorSheme){
                        wcout << GREEN << TR << RESET;
                    }
                    else{
                        wcout << BLUE << TR << RESET;
                    }
                    break;
                case 'Q':
                    if(otherColorSheme){
                        wcout << GREEN << DL << RESET;
                    }
                    else{
                        wcout << BLUE << DL << RESET;
                    }
                    break;
                case 'D':
                    if(otherColorSheme){
                        wcout << GREEN << DR << RESET;
                    }
                    else{
                        wcout << BLUE << DR << RESET;
                    }
                    break;
                case 'S':
                    if(otherColorSheme){
                        wcout << GREEN << H << RESET;
                    }
                    else{
                        wcout << BLUE << H << RESET;
                    }
                    break;
                case 'Z':
                    if(otherColorSheme){
                        wcout << GREEN << V << RESET;
                    }
                    else{
                        wcout << BLUE << V << RESET;
                    }
                    break;
                default:
                    wcout << ch;
                    break;
                }
            }
            activeCase.second = activeCase.second+1;
        }
    }



}

void InputInterpretation(const CMat & dataMap, int character, bool & gameLost, vector<string> & desiredDir){
    if (!gameLost) {
        switch (character) {
        case 'z':
            desiredDir[0] = "up";
            break;
        case 's':
            desiredDir[0] = "down";
            break;
        case 'q':
            desiredDir[0] = "left";
            break;
        case 'd':
            desiredDir[0] = "right";
            break;
        case KEY_LEFT:
            desiredDir[1] = "left";
            break;
        case KEY_RIGHT:
            desiredDir[1] = "right";
            break;
        case KEY_UP:
            desiredDir[1] = "up";
            break;
        case KEY_DOWN:
            desiredDir[1] = "down";
            break;
        case 'i':
            SaveMap(dataMap);
            erase();
            NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
            break;
        default:
            break;
        }
    } else {
        switch (character) {
        case KEY_RIGHT:
            //ShowScoreBoard();
            break;
        default:
            break;
        }
    }
}

void SaveMap(const CMat & dataMap){
    ofstream dest("../PacMen/Data/dataMapSave.txt");
    for(unsigned line = 0; line < dataMap.size(); ++line){
        for(unsigned column = 0; column < dataMap[line].size(); ++column){
            if(dataMap[line][column] == '\n' || dataMap[line][column] == '\r'){
                dest << "\r\n";
            }
            else{
                dest << dataMap[line][column];
            }
        }
    }
    dest.close();
}

void ShowScore(unsigned & totalScore){
    wcout << "Score : " << totalScore << "\n\r";
}

void LaunchPacMen(const bool freshGame, const bool & soloPlayer){
    unsigned powerRemainingTime = 0;
    bool pacManMouth;
    bool gameLost;
    CLine underPacMen = {'G', 'G'};
    CLine underF = {'F', 'F', 'F', 'F'};
    vector<string> desiredDir = {"", ""};
    vector<string> activeDir = {"", ""};
    vector<string> dirF = {"up","up","up","up"};
    CMat dataMap;
    if (freshGame) {
        if (soloPlayer)
        {
            ResetAllMap( gameLost,  underPacMen,  underF,  desiredDir,  activeDir,  dirF,  powerRemainingTime);
            GenerateMatriceFromTxt(dataMap, "../PacMen/Data/dataMap2solo.txt", freshGame);
        } else {
            ResetAllMap( gameLost,  underPacMen,  underF,  desiredDir,  activeDir,  dirF,  powerRemainingTime);
            GenerateMatriceFromTxt(dataMap, "../PacMen/Data/dataMap2.txt", freshGame);
        }
    } else {
        GenerateMatriceFromTxt(dataMap, "../PacMen/Data/dataMapSave.txt", freshGame);
    }
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    int timer = 0;
    while (true) {
        if(kbhit()){
            InputInterpretation(dataMap, getch(),  gameLost,  desiredDir);
        }
        usleep(1); // Attends 1 microseconde
        timer++;
        if(timer == 5000){ //Au bout de 0,5secondes on raffraichit la page
            timer = 0;
            ClearScreen();
            if(powerRemainingTime > 0){
                powerRemainingTime-=1;
            }
            ShowScore(totalScore);
            DrawMap(dataMap,  gameLost,  powerRemainingTime,  desiredDir,  activeDir,  pacManMouth,  totalScore,  underPacMen,  underF,  dirF, freshGame); //redessinne la map par dessus l'ancienne
            if(GameFinished(dataMap)){
                underPacMen = {'G', 'G'};
                underF = {'F', 'F', 'F', 'F'};
                desiredDir = {"", ""};
                activeDir = {"", ""};
                dirF = {"up","up","up","up"};
                if (soloPlayer)
                {
                    GenerateMatriceFromTxt(dataMap, "../PacMen/Data/dataMap2solo.txt", freshGame);
                } else {
                    GenerateMatriceFromTxt(dataMap, "../PacMen/Data/dataMap2.txt", freshGame);
                }
            }
        }
        else{
            move(0,0);
            refresh();
        }
    }
    endwin();
}

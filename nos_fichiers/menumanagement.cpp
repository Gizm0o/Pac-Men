#include <iostream>
#include <fstream>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include <string>
#include "nos_fichiers/type.h"
#include "nos_fichiers/kbhit.h"
#include "nos_fichiers/menumanagement.h"
#include "nos_fichiers/gamemanagement.h"
#include "nos_fichiers/scoreboard.h"

using namespace std;

float framerate = 0.2; //In seconds
unsigned currentPointersXPos;
UPair currentPointersYPos = make_pair(0,0);
string currentPointersSelection;

bool soloMode;

void ClearScreen(){
    wcout << "\033[H\033[2J";
}

void ReadMatrix (const CMat & matrixToRead)
{
    for (const auto & val: matrixToRead)
    {
        for (const auto & val2: val)
        {
            echochar(val2);
        }
        echochar('\n');
    }
}

void ConvertTxtToMatrix(CMat & matrixToFill, const string & fileToRead)
{
    matrixToFill.push_back({});
    ifstream readFile (fileToRead);
    char readChar;
    if (!readFile.is_open())
    {
        wcout << "il y a eu un souci" << endl;
        return;
    }
    while (readFile.get(readChar))
    {
        if (readChar == '\n')
        {
            matrixToFill.push_back({});
            continue;
        }
        matrixToFill[matrixToFill.size()-1].push_back(readChar);
    }
}

void SeekCurrentPointersPos(const CMat & matrixToRead){
    for (unsigned i (0); i < matrixToRead.size(); ++i){
        for (unsigned j (0); j < matrixToRead[i].size(); ++j){
            if (matrixToRead[i][j] == '>'){
                currentPointersXPos = i;
                currentPointersYPos.first = j;
            }
            else if (matrixToRead[i][j] == '<'){
                currentPointersYPos.second = j;
                return;
            }
        }
    }
}

void UpdatePointers(CMat & matrixToUpdate, unsigned aimedPointersXPos, const unsigned & minPos, const unsigned & maxPos)
{
    matrixToUpdate[currentPointersXPos][currentPointersYPos.first] = ' ';
    matrixToUpdate[currentPointersXPos][currentPointersYPos.second] = ' ';
    if (aimedPointersXPos == minPos)
    {
        aimedPointersXPos = maxPos - 1;
        currentPointersXPos = aimedPointersXPos;
    } else if (aimedPointersXPos == maxPos) {
        aimedPointersXPos = minPos + 1;
        currentPointersXPos = aimedPointersXPos;
    } else if (aimedPointersXPos > currentPointersXPos){
        currentPointersXPos++;
    } else {
        currentPointersXPos--;
    }
    for (unsigned i (0); i < matrixToUpdate[aimedPointersXPos].size()-2; ++i) {
        if (matrixToUpdate[aimedPointersXPos][i] == ' ' && isalpha(matrixToUpdate[aimedPointersXPos][i+1])) {
            matrixToUpdate[aimedPointersXPos][i] = '>';
            currentPointersYPos.first = i;
            matrixToUpdate[aimedPointersXPos][matrixToUpdate[aimedPointersXPos].size()-1] = '<';
            currentPointersYPos.second = matrixToUpdate[aimedPointersXPos].size()-1;
            break;
        }
    }
}

void SelectOption(string menuName)
{
    if (menuName == "main") {
        switch (currentPointersXPos) {
        case 7:
            erase();
            NavigateMenu("../PacMen/Data/modeselection.txt", "gamemode", 1, 4);
            break;
        case 8:
            LaunchPacMen(false, false);
            break;
        case 9:
            erase();
            NavigateMenu("../PacMen/Data/rules.txt", "rules", 23, 25);
            break;
        case 10:
            erase();
            NavigateMenu("../PacMen/Data/settings1.txt", "settings", 1,4);
            break;
        case 11:
            exit(0);
            break;
        }
    } else if (menuName == "gamemode") {
        switch (currentPointersXPos) {
        case 2:
            erase();
            soloMode = true;
            LaunchPacMen(true, true);
            break;
        case 3:
            erase();
            soloMode = false;
            LaunchPacMen(true, false);
            break;
        }
    } else if (menuName == "rules") {
        switch (currentPointersXPos) {
        case 24:
            NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
            break;
        }
    } else if (menuName == "settings") {
        switch (currentPointersXPos){
        case 2:
            ChangeColorSheme("classic");
            NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
            break;
        case 3:
            ChangeColorSheme("jungle");
            NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
            break;
        }
    } else if (menuName == "gameover") {
        switch (currentPointersXPos){
        case 24:
            erase();
            if (soloMode)
                ScoreBoardRoutineSolo(FetchScore());
            ScoreBoardRoutineCoop(FetchScore());
            break;
        case 25:
            erase();
            NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
            break;
        }
    }
}

void PreviousPage(const string & menuName)
{
    if (menuName == "gamemode" || menuName == "rules" || menuName == "settings" || menuName == "gameover")
    {
        erase();
        NavigateMenu("../PacMen/Data/menu.txt", "main", 6, 12);
    }
}

void NavigateMenu(const string & fileName, const string & menuName, const unsigned & minPosMenu, const unsigned & maxPosMenu)
{
    CMat menuMatrix (0);
    ConvertTxtToMatrix(menuMatrix, fileName);
    SeekCurrentPointersPos(menuMatrix);
    initscr();
    keypad(stdscr, TRUE);
    int c;
    int timer = 0;
    while (true) {
        if(kbhit()){
            c=getch();
            switch (c) {
            case KEY_UP:
                UpdatePointers(menuMatrix, currentPointersXPos-1, minPosMenu, maxPosMenu);
                break;
            case KEY_DOWN:
                UpdatePointers(menuMatrix, currentPointersXPos+1, minPosMenu, maxPosMenu);
                break;
            case KEY_RIGHT:
                SelectOption(menuName);
                break;
            case KEY_LEFT:
                PreviousPage(menuName);
                break;
            }
        }
        usleep(1); // Attends 1 microseconde
        timer++;
        if(timer == framerate * 10000){ //Au bout de 0,5secondes on raffraichit la page
            timer = 0;
            ReadMatrix(menuMatrix);
        }
        else{
            move(0,0);
            refresh();
        }
    }
    endwin();
}

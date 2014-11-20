#ifndef AI_HPP
#define AI_HPP

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
//#include <Windows.h>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
#define BOARD_W 15
#define BOARD_L 15

class AI_Manager {
  public:
    enum { REG,DL,DW,TL,TW};

    int SCORE_A;
    int SCORE_B;
    char BOARD[BOARD_W][BOARD_L];
    class alphabet {
      public:
        const char letter;
        int count;
        const int val;
        alphabet(char letter,int count,int val): letter(letter), count(count),val(val) {};
        alphabet& operator--() {
            count--;
        }
    };
    char LETTERS[7];
    int mult[6][6];
    alphabet * aList[27];
    std::unordered_map<std::string,int> dict;
    bool gameON;
    AI_Manager();
    ~AI_Manager();
    void init_alphabet(void);
    void init_board(void);
    void init_dictionary(void);
    int modif(int col, int row);
    void getAllWords(void);
    int getPointsAt(char*word,int length,int x, int y, bool right );
    int getPoints(const char* word, int length);
    int val(char x);
    void AI_Manager::printBoard(void);
    void AI_Manager::printLetters(void);
};


#endif // !AI_HPP

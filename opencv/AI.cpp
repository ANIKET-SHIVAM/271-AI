#include "AI.hpp"

void AI_Manager::init_alphabet() {
    aList[0] = new alphabet('_',2,0);
    aList[1] = new alphabet('A',9,1);
    aList[2] = new alphabet('B',2,4);
    aList[3] = new alphabet('C',2,4);
    aList[4] = new alphabet('D',5,2);
    aList[5] = new alphabet('E',13,1);
    aList[6] = new alphabet('F',2,4);
    aList[7] = new alphabet('G',3,3);
    aList[8] = new alphabet('H',4,3);
    aList[9] = new alphabet('I',8,1);
    aList[10] = new alphabet('J',1,10);
    aList[11] = new alphabet('K',1,5);
    aList[12] = new alphabet('L',4,2);
    aList[13] = new alphabet('M',2,4);
    aList[14] = new alphabet('N',5,2);
    aList[15] = new alphabet('O',8,1);
    aList[16] = new alphabet('P',2,4);
    aList[17] = new alphabet('Q',1,10);
    aList[18] = new alphabet('R',6,1);
    aList[19] = new alphabet('S',5,1);
    aList[20] = new alphabet('T',7,1);
    aList[21] = new alphabet('U',4,2);
    aList[22] = new alphabet('V',2,5);
    aList[23] = new alphabet('W',2,4);
    aList[24] = new alphabet('X',1,8);
    aList[25] = new alphabet('Y',2,3);
    aList[26] = new alphabet('Z',1,10);
    for (int i=0; i <7; i++)
        for (int j=0; j<7; j++)
            mult[i][j]=0;
//first quadrant BOARD positions with modifiers
// Note, the other three quandrants have modifiers at posititions that are 90 degree rotations of the first quadrant.
    mult[0][3]= TW;
    mult[0][6]= TL;
    mult[1][2]= DL;
    mult[1][5]= DL;
    mult[2][1]= DL;
    mult[2][4]= DL;
    mult[3][0]= TW;
    mult[3][3]= TL;
    mult[3][7]= DW;
    mult[4][2]= DL;
    mult[4][6]= DL;
    mult[5][1]= DW;
    mult[5][5]= DL;
    mult[6][0]= TL;
    mult[6][4]= DL;
}

void AI_Manager::init_board() {
    // BOARD = (char*)malloc(sizeof(char)*BOARD_W*BOARD_L);  //Allocate space for 15x15 gameBOARD
    for (int i = 0; i < BOARD_W; i++)
        for (int j = 0; j < BOARD_L; j++)
            BOARD[i][j]= '-';
}

void AI_Manager::init_dictionary() {
    std::ifstream f;
    f.open ("dict.txt");
    std::string word="";
    if (f.is_open())
        while(std::getline(f,word))
            dict[word]=getPoints(word.c_str(),word.length()); //We'll need to use a trie instead for efficient search and lookup
    f.close();
}

//return modifier if present at tile (col,row)
int AI_Manager::modif(int col, int row) {
    if (col >BOARD_W/2)
        col=-BOARD_W/2;
    if (row > BOARD_W/2)
        row -= BOARD_W/2;
    return mult[row][col];
}

AI_Manager::AI_Manager() : gameON(true), SCORE_A(0), SCORE_B(0)

{
    init_board();
    init_alphabet();
    init_dictionary();
}

void AI_Manager::getAllWords() {
    //search trie
    for (int i = 0; i <7; i++) {
        LETTERS[i];
    }
}

//checks score if placing word at location (x=col,y=row) in either right (true) or downward(false) direction
int AI_Manager::getPointsAt(char*word,int length,int x, int y, bool right ) {
    int sum = 0;
    int mod = 0;
    for (int i = 0; i < length; i++) {
        int v = val(word[length]);
        mod = modif(x + (right ? i : 0),y + (right ? 0: i));
        if (  mod == DL)
            sum += 2*v;
        if ( mod == TL)
            sum += 3*v;
        else
            sum+=v;
    }
    if  (mod == DW) return 2*sum;
    if (mod == TW) return 3*sum;
    return sum;
}

//get points, ignore modifiers
int AI_Manager::getPoints(const char* word, int length) {
    int sum=0;
    while(length--)
        sum+= val(word[length]);
    return sum;
}

//get point value of letters 'A'-'Z'. Wild Cards count as 0 points.
int AI_Manager::val(char x) {
    if (x >= 'A' && x <= 'Z')
        return aList[x-'A'+1]->val;
    return 0;
}

void AI_Manager::printBoard() {
    for (int i=0; i<BOARD_L; i++) {
        for(int j=0; j<BOARD_W; j++)
            cout << string(1,BOARD[j][i]) << " ";
        cout << endl;
    }
    cout <<endl<<endl;
}

void AI_Manager::printLetters() {
    cout << "LETTERS: ";
    for (int i =0; i <7; i++) {
        cout << LETTERS[i] << " ";
    }
    cout << endl << endl;
}

/// modified by Aniket:Nov 29

////////Utility functions

string AI_Manager::removed(string hand, string remove){
    for (i=0;i<strlen(remove);i++){
        for (j=0;j<strlen(hand);j++){
            if (remove[i]==hand[j])
            { hand.erase(j,1);break;}
        }
    }
    return hand;
}

void AI_Manager::transpose(){
    for (i=0;i<BOARD_L;i++){
        for(j=0;i<BOARD_L;j++)
            BOARD[j][i]=BOARD[i][j];
    }
}


////////PLAY FUNCTIONS

void AI_Manager::setAnchors(){
    for (int i=0; i<BOARD_L; i++) {
        for(int j=0; j<BOARD_W; j++){
            if (BOARD[i,j] != ""){
                if (BOARD[i,j-1] == "")
                    BOARD[i,j-1] = "?";
                if (BOARD[i,j+1] == "")
                    BOARD[i,j+1] = "?";
            }
        }
    }
    
}



void AI_Manager::findPrefixes(){
    
    
}































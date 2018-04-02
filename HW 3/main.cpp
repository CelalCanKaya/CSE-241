// Commentlerimi fonksiyonlarýn baþýna ekledim. Genel olarak nasýl çalýþtýðýyla alakalý bilgi verdim.

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef enum {EMPTY, X, O, x, o} grid;


class ConnectFour{      // Main Classýmda oyunla ilgili tüm verileri tutuyorum
    public:
        ConnectFour();
        void playGame();
        void sizeInput();
        void typeInput();
        void initBoard();
        const int isDone();
        const bool compare(const ConnectFour& game)const;
        static void livingCells();
        const inline int getWidth() const{
            return width;
        };
        const inline int getHeight() const{
            return height;
        };
        inline void setMode(string mode){
            gameMode=mode;
        }
    private:
        class Cell{
            public:
                Cell();
                Cell(grid t, int x, int y);
                const inline grid getType()const{
                    return type;
                }
                const inline int getPosX() const{
                    return posx;
                }
                const inline int getPosY()const {
                    return posy;
                }
                inline void setType(grid x){
                    type=x;
                }
            private:
                grid type;
                int posx;
                int posy;
        };
        void clearBoard();
        void printBoard() const;
        void play();
        const int play(int x);
        const int gameInput();
        const int isGameFinished();
        const int isGameDraw() const;
        const int isValid(int i, int j)const;
        const int computer4InARow(const int i, const int j)const;
        const int player4InARow(const int i, const int j)const;
        const int computer3InARow(const int i, const int j)const;
        const int player3InARow(const int i,const int j)const;
        const int computer2InARow(const int i, const int j)const;
        const int player2InARow(const int i, const int j)const;
        void saveGame(const string filename)const;
        void loadGame(const string filename);
        int currentCell;
        int width;
        int height;
        int turn;
        static int livingCell;
        string gameType;
        string gameMode;
        vector< vector<Cell> > gameCells;

};

int ConnectFour::livingCell=0;

// Main Fonksiyonumda Multi Yada Single Moduna Göre Ýþlem Yapýyorum. Önce Modu Alýyorum. Daha sonra o moda göre playGame fonksiyonumu çaðýrýyorum
int main(){
    const int MAX_OBJECT = 5;
    string mode;
    string gameMode;
    int status=1;
    cout << endl << "Press 'M' For Multi Games, Press 'S' For Single Game: ";
    while(status){
        cin >> mode;
        if(mode=="M" || mode=="m"){
            gameMode = "M";
            status = 0;
        }
        else if(mode=="S" || mode=="s"){
            gameMode = "S";
            status = 0;
        }
        if(status==1){
            cout << endl << "Please Enter A Valid Game Mode: ";
        }
    }
    if(gameMode == "S"){
        ConnectFour game;
        game.setMode(gameMode);
        game.playGame();
    }
    else if(gameMode == "M"){
        ConnectFour game[MAX_OBJECT];
        for(int i=0; i<MAX_OBJECT; i++){
            game[i].setMode(gameMode);
            cout << endl << "Object " << i+1 << endl;
            game[i].sizeInput();
            game[i].typeInput();
            game[i].initBoard();
        }
        int status = 1;
        while(status==1){
            int obj, objStatus=1, done=1;
            for(int i=0; i<MAX_OBJECT; i++){
                if(!(game[i].isDone())){
                    done=0;
                }
            }
            if(done==0){
                cout << endl << endl << "Select Object Number: ";
                if(!(cin >> obj)){
                    while(objStatus){
                        cout << endl << "Please Enter A Valid Object Number: ";
                        cin.clear();
                        cin.ignore(10000,'\n');
                        if(cin >> obj){
                            objStatus=0;
                        }
                    }
                }
                if(obj>MAX_OBJECT){
                    cout << endl << "Please Enter A Valid Object Number!";
                }
                else if(game[obj-1].isDone()){
                    cout << endl << "This Game Already Finished!";
                }
                else{
                    game[obj-1].playGame();
                    if(obj-1==4){
                        if(game[4].compare(game[1])){
                            cout << endl << "g5>g1";
                        }
                        else{
                            cout << endl << "g5<=g1";
                        };
                    }
                    else{
                        if(game[obj-1].compare(game[4])){
                            cout << endl << "g" << obj << ">g5";
                        }
                        else{
                            cout << endl << "g" << obj << "<=g5";
                        }
                    }
                }
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}

// Classýmýn default constructorýný tanýmladým.Ýlk deðerleri atýyorum
ConnectFour::ConnectFour(){
    width = 10;
    height = 10;
    turn = 1;
    gameType = "P";
    currentCell = 0;
}

// Bu constructer ý kullanarak vectore Cell tipini push_back ederken gereken ilk deðerleri atýyorum.
ConnectFour::Cell::Cell(grid t, int x, int y){
    type = t;
    posx = x;
    posy = y;
}

// Cell clasýmýn default constructerý
ConnectFour::Cell::Cell(){
    type = EMPTY;
    posx = 0;
    posy = 0;
}

// Bu fonksiyonum sayesinde kullanýcýdan width ve height deðerlerini alýyorum.Tip kontrolü ve geçersiz deðerleri kontrol ediyorum
void ConnectFour::sizeInput(){
    int sizeStatus=1;
    cout << endl << "Please Enter Width Size: ";
    if(!(cin >> height) || height < 4){
        while(sizeStatus){
            cout << endl << "Please Enter A Valid Width Size: ";
            cin.clear();
            cin.ignore(10000,'\n');
            if(cin >> height && height >= 4){
                sizeStatus=0;
            }
       }
    }
    sizeStatus=1;
    cout << endl << "Please Enter Height Size: ";
    if(!(cin >> width) || width < 4){
        while(sizeStatus){
            cout << endl << "Please Enter A Valid Height Size: ";
            cin.clear();
            cin.ignore(10000,'\n');
            if(cin >> width && width >=4){
                sizeStatus=0;
            }
       }
    }
}

// Bu fonksiyonum sayesinde kullanýcýdan pvp yada pvc oynamak isteyip istemediðini alýyorum.Tip kontrolü ve geçersiz deðerleri kontrol ediyorum
void ConnectFour::typeInput(){
    string type;
    int status=1;
    cout << endl << "Press 'C' For Playing Against Computer, Press 'P' For Playing Against Player: ";
    while(status){
        cin >> type;
        if(type=="P" || type=="p"){
            gameType = "P";
            status = 0;
        }
        else if(type=="C" || type=="c"){
            gameType = "C";
            status = 0;
        }
        if(status==1){
            cout << endl << "Please Enter A Valid Game Type: ";
        }
    }
}

// Vectorüme ilk deðerleri initialize ediyorum
void ConnectFour::initBoard(){
    vector<Cell> temp;
    for(int i=0; i<width; i++){
        temp.clear();
        for(int j=0; j<height; j++){
            Cell tmp(EMPTY, i, j);
            temp.push_back(tmp);
        }
        gameCells.push_back(temp);
    }
}

// Bu fonksiyonumla dolu vectorümü pop_back ediyorum ve tamamen boþ hale getiriyorum
void ConnectFour::clearBoard(){
    for(int i=0; i<width; i++){
        gameCells.pop_back();
    }
}

// Bu fonksiyonumla board ý ekrana bastýrýyorum
void ConnectFour::printBoard()const{
    char characters = 'A';
    cout << endl << endl;
    for(int k=0; k<height; k++){
        cout << "  " << characters++ << " ";
    }
    for(int i=width-1; i>-1; i--){
        cout << endl;
        for(int k=0; k<height; k++){
            cout << " ---";
        }
        cout << endl << "|";
        for(int j=0; j<height; j++){
            if(gameCells[i][j].getType()==EMPTY){
                cout << " . |" ;
            }
            if(gameCells[i][j].getType()==X){
                cout << " X |";
            }
            if(gameCells[i][j].getType()==O){
                cout << " O |";
            }
            if(gameCells[i][j].getType()==x){
                cout << " x |";
            }
            if(gameCells[i][j].getType()==o){
                cout << " o |";
            }
       }
    }
    cout << endl;
    for(int k=0; k<height; k++){
        cout << " ---";
    }
}

// Overload ettiðim play fonksiyonunda kullanýcýdan aldýðým inputu boardda geçerli olan bölgeye atýyorum
const int ConnectFour::play(int x){
    if(turn==-1){
        return -1;
    }
    for(int i=0; i<width; i++){
        if(gameCells[i][x].getType()==EMPTY){
            if(turn==1){
                gameCells[i][x].setType(X);
                currentCell += 1;
                return 1;
                break;
            }
            else if(turn==2){
                gameCells[i][x].setType(O);
                currentCell += 1;
                return 1;
                break;
            }
        }
    }
    return 0;
}

// Overload ettiðim play fonksiyonunda bilgisayar yapabileceði en iyi hamleyi hesaplýyor ve hamlesini yapýyor
void ConnectFour::play(){
  int i ,j, tempX=-1, tempY=-1, bestMove=0;
  for(j=0; j<height; j++){
     for(i=0; i<width; i++){
        if(gameCells[i][j].getType()==EMPTY){
           if(computer4InARow(i, j)>bestMove){
                bestMove = computer4InARow(i, j);
                tempX=i;
                tempY=j;
           }
           if(player4InARow(i, j)>bestMove){
                bestMove = player4InARow(i, j);
                tempX=i;
                tempY=j;
           }
           if(computer3InARow(i, j)>bestMove){
                bestMove = computer3InARow(i, j);
                tempX=i;
                tempY=j;
           }
           if(player3InARow(i, j)>bestMove){
                bestMove = player3InARow(i, j);
                tempX=i;
                tempY=j;
           }
           if(computer2InARow(i, j)>bestMove){
                bestMove = computer2InARow(i, j);
                tempX=i;
                tempY=j;
           }
           if(player2InARow(i, j)>bestMove){
                player2InARow(i, j);
                tempX=i;
                tempY=j;
           }
            break;
        }
    }
  }

    char col = 'A';

    if(bestMove>0){
        col += tempY;
        cout << endl << endl << "Computer Move: " << col;
        gameCells[tempX][tempY].setType(O);
    }
    else if(gameCells[0][height/2].getType()==EMPTY){
        col += width/2;
        cout << endl << endl << "Computer Move: " << col;
        gameCells[0][height/2].setType(O);
    }
    else if(gameCells[0][height/2].getType()==X){
        col += 'A' + width/2;
        cout << endl << endl << "Computer Move: " << col;
        gameCells[0][height/2-1].setType(O);
    }
}

// Bu fonksiyonumda kullanýcýdan gireceði operasyonu alýyorum(SAVE, LOAD, MOVE) ve eðer hamle yapmak istiyorsa atacaðý column u return ediyorum
const int ConnectFour::gameInput(){
    string op, line;
    char column;
    int status=1, status2=1;
    while(status==1){
        status2 = 1;
        if(turn==1){
            cout << endl << endl << "PLAYER 1 - Select Move: ";
        }
        if(turn==2){
            cout << endl << endl << "PLAYER 2 - Select Move: ";
        }
        cin >> op;
        if(op=="SAVE"){
            getline(cin, line);
            saveGame(line);
        }
        else if(op=="LOAD"){
            if(turn==1){
                getline(cin,line);
                livingCell=livingCell-currentCell;
                loadGame(line);
                livingCell=livingCell+currentCell;
                cout << endl << endl << "Game Loaded!";
                if(turn==2){
                    return -1;
                }
                else{
                    printBoard();
                }
            }
            else if(turn==2){
                getline(cin,line);
                livingCell=livingCell-currentCell;
                loadGame(line);
                livingCell=livingCell+currentCell;
                cout << endl << endl << "Game Loaded!";
                if(turn==1){
                    return -1;
                }
                else{
                    printBoard();
                }
            }
        }
        else{
            if(op[1]=='\0'){
                column=op[0];
            }
            else{
                status2=0;
            }
            if(status2){
                if(column<='z' && column>='a'){
                    column = column - 'a';
                }
                else if(column<='Z' && column>='A'){
                    column = column - 'A';
                }
                if(column>height-1 || column<0){
                    cout << endl << "Please Enter A Valid Location!";
                }
                else{
                    status=0;
                }
            }
        }
    }
    return static_cast <int> (column);
}

// Class fonksiyonlarýmý kullanarak oyunun iþleniþini kontrol ediyorum.
void ConnectFour::playGame(){
    if(gameMode == "S"){
        sizeInput();
        typeInput();
        initBoard();
    }
    printBoard();
    int status = 1, status1 = 1, status2 = 1;
    while(status==1){
        status1 = 1;
        while(status1==1){
                turn = 1;
                status1 = play(gameInput());
                if(status1==0){
                    cout << endl << "There are no spaces in this column!" << endl ;
                    status1=1;
                }
                else if(status1==-1){
                    status1=0;
                }
                else{
                    status1=0;
                    livingCells();
                }
        }
        if(isGameFinished()){
            printBoard();
            cout << endl << endl << "GAME OVER! PLAYER 1 WIN!" << endl;
            status=0;
            break;
        }
        if(!isGameDraw()){
            printBoard();
            cout << endl << endl << "GAME OVER!  DRAW!" << endl;
            status=0;
            break;
        }
        printBoard();
        if(gameType=="P"){
                status2 = 1;
                while(status2==1){
                    turn = 2;
                    status2 = play(gameInput());
                    if(status2==0){
                        cout << endl << "There are no spaces in this column!" << endl ;
                        status2=1;
                    }
                    else if(status2==-1){
                        status2=0;
                    }
                    else{
                        status2=0;
                        livingCells();
                    }
                }
            }
            if(gameType=="C"){
                play();
                livingCells();
            }
            if(isGameFinished()){
                printBoard();
                if(gameType=="P"){
                    cout << endl << endl << "GAME OVER! PLAYER 2 WIN!" << endl;
                }
                else{
                    cout << endl << endl << "GAME OVER! COMPUTER WIN!" << endl;
                status=0;
                break;
                }
            }
            else if(!isGameDraw()){
                printBoard();
                cout << endl << endl << "GAME OVER!  DRAW!" << endl;
                status=0;
                break;
            }
            printBoard();
            if(gameMode=="M"){
                break;
            }
    }
}

// Bu fonksiyonumla parametre olarak gönderilen i ve j deðerlerinin vector üzerinde olup olmadýðýný kontrol ediyorum
const int ConnectFour::isValid(int i, int j)const{
    if(i<0 || i>width-1 || j<0 || j>height-1){
        return 0;
    }
    return 1;
}

// Bu fonksiyonda oyunda 4'lü oluþup oluþmadýðýný kontrol ediyorum
const int ConnectFour::isGameFinished(){
    int i, j, k;
    for(i=0; i<width; i++){
        for(j=0; j<height; j++){
            if(isValid(i,j) && isValid(i+1,j) && isValid(i+2, j) && isValid(i+3, j)){
                if(gameCells[i][j].getType() == X && gameCells[i+1][j].getType() == X &&gameCells[i+2][j].getType() == X && gameCells[i+3][j].getType() == X){
                    for(k=0; k<4; k++){
                        gameCells[i+k][j].setType(x);
                    }
                    return 1;
                }
            }
           if(isValid(i,j) && isValid(i,j+1) && isValid(i, j+2) && isValid(i, j+3)){
                if(gameCells[i][j].getType() == X && gameCells[i][j+1].getType() == X && gameCells[i][j+2].getType() == X && gameCells[i][j+3].getType() == X){
                    for(k=0; k<4; k++){
                        gameCells[i][j+k].setType(x);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j+1) && isValid(i+2, j+2) && isValid(i+3, j+3)){
                if(gameCells[i][j].getType() == X && gameCells[i+1][j+1].getType() == X && gameCells[i+2][j+2].getType() == X && gameCells[i+3][j+3].getType() == X){
                    for(k=0; k<4; k++){
                        gameCells[i+k][j+k].setType(x);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j-1) && isValid(i+2, j-2) && isValid(i+3, j-3)){
                if(gameCells[i][j].getType() == X && gameCells[i+1][j-1].getType() == X && gameCells[i+2][j-2].getType() == X && gameCells[i+3][j-3].getType() == X){
                    for(k=0; k<4; k++){
                        gameCells[i+k][j-k].setType(x);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j) && isValid(i+2, j) && isValid(i+3, j)){
                if(gameCells[i][j].getType() == O && gameCells[i+1][j].getType() == O && gameCells[i+2][j].getType() == O && gameCells[i+3][j].getType() == O){
                    for(k=0; k<4; k++){
                        gameCells[i+k][j].setType(o);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i,j+1) && isValid(i, j+2) && isValid(i, j+3)){
                if(gameCells[i][j].getType() == O && gameCells[i][j+1].getType() == O && gameCells[i][j+2].getType() == O && gameCells[i][j+3].getType() == O){
                    for(k=0; k<4; k++){
                        gameCells[i][j+k].setType(o);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j+1) && isValid(i+2, j+2) && isValid(i+3, j+3)){
                if(gameCells[i][j].getType() == O && gameCells[i+1][j+1].getType() == O && gameCells[i+2][j+2].getType() == O && gameCells[i+3][j+3].getType() == O){
                    for(k=0; k<4; k++){
                        gameCells[i+k][j+k].setType(o);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j-1) && isValid(i+2, j-2) && isValid(i+3, j-3)){
                if(gameCells[i][j].getType() == O && gameCells[i+1][j-1].getType() == O && gameCells[i+2][j-2].getType() == O && gameCells[i+3][j-3].getType() == O){
                    for(k=0; k<4; k++){
                        gameCells[i+k][j-k].setType(o);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Bu fonksiyonumda oyun boardýnýn tamamen dolup dolmadýðýný kontrol ediyorum
const int ConnectFour::isGameDraw() const{
    int i, j;
    for(i=0; i<width; i++){
        for(j=0; j<height; j++){
            if(gameCells[i][j].getType()==EMPTY){
                return 1;
            }
        }
    }
    return 0;
}

// Bu fonksiyonumda bilgisayarýn 4'lü yapýp yapamayacaðýný kontrol ediyorum
const int ConnectFour::computer4InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2) && isValid(i, j+3)){
        if(gameCells[i][j+1].getType()==O && gameCells[i][j+2].getType()==O && gameCells[i][j+3].getType()==O){
            return 6;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j-3)){
        if(gameCells[i][j-1].getType()==O && gameCells[i][j-2].getType()==O && gameCells[i][j-3].getType()==O){
            return 6;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1) && isValid(i, j+2)){
        if(gameCells[i][j-1].getType()==O && gameCells[i][j+1].getType()==O && gameCells[i][j+2].getType()==O){
            return 6;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j+1)){
        if(gameCells[i][j-1].getType()==O && gameCells[i][j-2].getType()==O && gameCells[i][j+1].getType()==O){
            return 6;
        }
    }
    if(isValid(i-1,j) && isValid(i-2,j) && isValid(i-3, j)){
        if(gameCells[i-1][j].getType()==O && gameCells[i-2][j].getType()==O && gameCells[i-3][j].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i+3, j+3)){
        if(gameCells[i+1][j+1].getType()==O && gameCells[i+2][j+2].getType()==O && gameCells[i+3][j+3].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i-1, j-1)){
        if(gameCells[i+1][j+1].getType()==O && gameCells[i+2][j+2].getType()==O && gameCells[i-1][j-1].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameCells[i+1][j+1].getType()==O && gameCells[i-1][j-1].getType()==O && gameCells[i-2][j-2].getType()==O){
            return 6;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2,j-2) && isValid(i-3, j-3)){
        if(gameCells[i-1][j-1].getType()==O && gameCells[i-2][j-2].getType()==O && gameCells[i-3][j-3].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i+3, j-3)){
        if(gameCells[i+1][j-1].getType()==O && gameCells[i+2][j-2].getType()==O && gameCells[i+3][j-3].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i-1, j+1)){
        if(gameCells[i+1][j-1].getType()==O && gameCells[i+2][j-2].getType()==O && gameCells[i-1][j+1].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameCells[i+1][j-1].getType()==O && gameCells[i-1][j+1].getType()==O && gameCells[i-2][j+2].getType()==O){
            return 6;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2,j+2) && isValid(i-3, j+3)){
        if(gameCells[i-1][j+1].getType()==O && gameCells[i-2][j+2].getType()==O && gameCells[i-3][j+3].getType()==O){
            return 6;
        }
    }
    return 0;
}

// Bu fonksiyonumda oyuncunun 4'lü yapýp yapamayacaðýný kontrol ediyorum
const int ConnectFour::player4InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2) && isValid(i, j+3)){
        if(gameCells[i][j+1].getType()==X && gameCells[i][j+2].getType()==X && gameCells[i][j+3].getType()==X){
            return 5;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j-3)){
        if(gameCells[i][j-1].getType()==X && gameCells[i][j-2].getType()==X && gameCells[i][j-3].getType()==X){
            return 5;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1) && isValid(i, j+2)){
        if(gameCells[i][j-1].getType()==X && gameCells[i][j+1].getType()==X && gameCells[i][j+2].getType()==X){
            return 5;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j+1)){
        if(gameCells[i][j-1].getType()==X && gameCells[i][j-2].getType()==X && gameCells[i][j+1].getType()==X){
            return 5;
        }
    }
    if(isValid(i-1,j) && isValid(i-2,j) && isValid(i-3, j)){
        if(gameCells[i-1][j].getType()==X && gameCells[i-2][j].getType()==X && gameCells[i-3][j].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i+3, j+3)){
        if(gameCells[i+1][j+1].getType()==X && gameCells[i+2][j+2].getType()==X && gameCells[i+3][j+3].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i-1, j-1)){
        if(gameCells[i+1][j+1].getType()==X && gameCells[i+2][j+2].getType()==X && gameCells[i-1][j-1].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameCells[i+1][j+1].getType()==X && gameCells[i-1][j-1].getType()==X && gameCells[i-2][j-2].getType()==X){
            return 5;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2,j-2) && isValid(i-3, j-3)){
        if(gameCells[i-1][j-1].getType()==X && gameCells[i-2][j-2].getType()==X && gameCells[i-3][j-3].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i+3, j-3)){
        if(gameCells[i+1][j-1].getType()==X && gameCells[i+2][j-2].getType()==X && gameCells[i+3][j-3].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i-1, j+1)){
        if(gameCells[i+1][j-1].getType()==X && gameCells[i+2][j-2].getType()==X && gameCells[i-1][j+1].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameCells[i+1][j-1].getType()==X && gameCells[i-1][j+1].getType()==X && gameCells[i-2][j+2].getType()==X){
            return 5;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2,j+2) && isValid(i-3, j+3)){
        if(gameCells[i-1][j+1].getType()==X && gameCells[i-2][j+2].getType()==X && gameCells[i-3][j+3].getType()==X){
            return 5;
        }
    }
    return 0;
}

// Bu fonksiyonumda bilgisayarýn 3'lü yapýp yapamayacaðýný kontrol ediyorum
const int ConnectFour::computer3InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2)){
        if(gameCells[i][j+1].getType()==O && gameCells[i][j+2].getType()==O){
            return 4;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2)){
        if(gameCells[i][j-1].getType()==O && gameCells[i][j-2].getType()==O){
            return 4;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1)){
        if(gameCells[i][j-1].getType()==O && gameCells[i][j+1].getType()==O){
            return 4;
        }
    }
    if(isValid(i-1,j) && isValid(i-2,j)){
        if(gameCells[i-1][j].getType()==O && gameCells[i-2][j].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2)){
        if(gameCells[i+1][j+1].getType()==O && gameCells[i+2][j+2].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1, j-1)){
        if(gameCells[i+1][j+1].getType()==O && gameCells[i-1][j-1].getType()==O){
            return 4;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameCells[i-1][j-1].getType()==O && gameCells[i-2][j-2].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2)){
        if(gameCells[i+1][j-1].getType()==O && gameCells[i+2][j-2].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1, j+1)){
        if(gameCells[i+1][j-1].getType()==O && gameCells[i-1][j+1].getType()==O){
            return 4;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameCells[i-1][j+1].getType()==O && gameCells[i-2][j+2].getType()==O){
            return 4;
        }
    }
    return 0;
}

// Bu fonksiyonumda oyuncunun 3'lü yapýp yapamayacaðýný kontrol ediyorum
const int ConnectFour::player3InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2)){
        if(gameCells[i][j+1].getType()==X && gameCells[i][j+2].getType()==X){
            return 3;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2)){
        if(gameCells[i][j-1].getType()==X && gameCells[i][j-2].getType()==X){
            return 3;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1)){
        if(gameCells[i][j-1].getType()==X && gameCells[i][j+1].getType()==X){
            return 3;
        }
    }
    if(isValid(i-1,j) && isValid(i-2,j)){
        if(gameCells[i-1][j].getType()==X && gameCells[i-2][j].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2)){
        if(gameCells[i+1][j+1].getType()==X && gameCells[i+2][j+2].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1, j-1)){
        if(gameCells[i+1][j+1].getType()==X && gameCells[i-1][j-1].getType()==X){
            return 3;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameCells[i-1][j-1].getType()==X && gameCells[i-2][j-2].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2)){
        if(gameCells[i+1][j-1].getType()==X && gameCells[i+2][j-2].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1, j+1)){
        if(gameCells[i+1][j-1].getType()==X && gameCells[i-1][j+1].getType()==X){
            return 3;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameCells[i-1][j+1].getType()==X && gameCells[i-2][j+2].getType()==X){
            return 3;
        }
    }
    return 0;
}

// Bu fonksiyonumda bilgisayarýn 2'l, yapýp yapamayacaðýný kontrol ediyorum
const int ConnectFour::computer2InARow(const int i, const int j)const{
   if(isValid(i,j+1)){
        if(gameCells[i][j+1].getType()==O){
            return 2;
        }
    }
    if(isValid(i,j-1)){
        if(gameCells[i][j-1].getType()==O){
            return 2;
        }
    }
    if(isValid(i-1,j)){
        if(gameCells[i-1][j].getType()==O){
            return 2;
        }
    }
    if(isValid(i+1,j+1)){
        if(gameCells[i+1][j+1].getType()==O){
            return 2;
        }
    }
    if(isValid(i-1, j-1)){
        if(gameCells[i-1][j-1].getType()==O){
            return 2;
        }
    }
    if(isValid(i+1,j-1)){
        if(gameCells[i+1][j-1].getType()==O){
            return 2;
        }
    }
    if(isValid(i-1,j+1)){
        if(gameCells[i-1][j+1].getType()==O){
            return 2;
        }
    }
    return 0;
}

// Bu fonksiyonumda oyuncunun 2'lü yapýp yapamayacaðýný kontrol ediyorum
const int ConnectFour::player2InARow(const int i, const int j)const{
   if(isValid(i,j+1)){
        if(gameCells[i][j+1].getType()==X){
            return 1;
        }
    }
    if(isValid(i,j-1)){
        if(gameCells[i][j-1].getType()==X){
            return 1;
        }
    }
    if(isValid(i-1,j)){
        if(gameCells[i-1][j].getType()==X){
            return 1;
        }
    }
    if(isValid(i+1,j+1)){
        if(gameCells[i+1][j+1].getType()==X){
            return 1;
        }
    }
    if(isValid(i-1, j-1)){
        if(gameCells[i-1][j-1].getType()==X){
            return 1;
        }
    }
    if(isValid(i+1,j-1)){
        if(gameCells[i+1][j-1].getType()==X){
            return 1;
        }
    }
    if(isValid(i-1,j+1)){
        if(gameCells[i-1][j+1].getType()==X){
            return 1;
        }
    }
    return 0;
}

// Classýmýn member fonksiyonlarý ve vectorümdeki deðerleri dosyaya kaydediyorum
void ConnectFour::saveGame(const string filename)const{
    ofstream myFile;
    myFile.open(filename);
    if (!myFile.is_open()) {
        cerr << endl << "Unable To Open File" << endl;
    }
    else{
        myFile << width << endl;
        myFile << height << endl;
        myFile << gameType << endl;
        myFile << turn << endl;
        myFile << currentCell << endl;
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                if(gameCells[i][j].getType()==EMPTY){
                    myFile << "EMPTY" << endl;
                }
                else if(gameCells[i][j].getType()==X){
                    myFile << "X" << endl;
                }
                else if(gameCells[i][j].getType()==O){
                    myFile << "O" << endl;
                }
            }
        }
        cout << endl << "Game Saved!";
        myFile.close();
    }
}

// Kaydettiðim deðerleri dosyadan yükleyerek oyunun devam etmesini saðlýyorum
void ConnectFour::loadGame(const string filename){
    ifstream myFile;
    string line;
    myFile.open(filename);
    if (!myFile.is_open()){
        cerr << endl << "Unable To Open File" << endl;
    }
    else{
        clearBoard();
        myFile >> width;
        myFile >> height;
        myFile >> gameType;
        myFile >> turn;
        myFile >> currentCell;
        initBoard();
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                myFile >> line;
                if(line=="EMPTY"){
                    gameCells[i][j].setType(EMPTY);
                }
                else if(line=="X"){
                    gameCells[i][j].setType(X);
                }
                else if(line=="O"){
                    gameCells[i][j].setType(O);
                }
            }
        }
        myFile.close();
    }
}

// Multi oyunda geçiþ yaparken oyunun bitip bitmediðini kontrol ediyorum. Bu sayede eðer oyun bitmiþse o objeye geçiþ yapmasýný engelliyorum
const int ConnectFour::isDone(){
    if(!isGameDraw()){
        return 1;
    }
    else{
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                if(gameCells[i][j].getType()==x ||gameCells[i][j].getType()==o){
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Static deðiþkenimi 1 arttýrýyorum. Ayný zamanda living cell sayýsýný 1 arttýrýyorum
void ConnectFour::livingCells(){
    livingCell++;
    cout << endl << "Living Cells: " << livingCell;
}

// Ýki oyunu karþýlaþtýrýyorum. Eðer ilk oyunda 3 lü yaptýysak ve parametre olarak verilen oyunda 3'lü yapmadýysak True return ediyorum. Eðer bu kondisyonu saðlamýyorum false return ediyorum
const bool ConnectFour::compare(const ConnectFour& game)const{
    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            if(isValid(i,j+1) && isValid(i,j+2) && isValid(i, j+3)){
                if(gameCells[i][j+1].getType()==X && gameCells[i][j+2].getType()==X && gameCells[i][j+3].getType()==X){
                    if(!(game.gameCells[i][j+1].getType()==X && game.gameCells[i][j+2].getType()==X && game.gameCells[i][j+3].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j-3)){
                if(gameCells[i][j-1].getType()==X && gameCells[i][j-2].getType()==X && gameCells[i][j-3].getType()==X){
                    if(!(game.gameCells[i][j-1].getType()==X && game.gameCells[i][j-2].getType()==X && game.gameCells[i][j-3].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i,j-1) && isValid(i,j+1) && isValid(i, j+2)){
                if(gameCells[i][j-1].getType()==X && gameCells[i][j+1].getType()==X && gameCells[i][j+2].getType()==X){
                    if(!(game.gameCells[i][j-1].getType()==X && game.gameCells[i][j+1].getType()==X && game.gameCells[i][j+2].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j+1)){
                if(gameCells[i][j-1].getType()==X && gameCells[i][j-2].getType()==X && gameCells[i][j+1].getType()==X){
                    if(!(game.gameCells[i][j-1].getType()==X && game.gameCells[i][j-2].getType()==X && game.gameCells[i][j+1].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i-1,j) && isValid(i-2,j) && isValid(i-3, j)){
                if(gameCells[i-1][j].getType()==X && gameCells[i-2][j].getType()==X && gameCells[i-3][j].getType()==X){
                    if(!(game.gameCells[i-1][j].getType()==X && game.gameCells[i-2][j].getType()==X && game.gameCells[i-3][j].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i+3, j+3)){
                if(gameCells[i+1][j+1].getType()==X && gameCells[i+2][j+2].getType()==X && gameCells[i+3][j+3].getType()==X){
                    if(!(game.gameCells[i+1][j+1].getType()==X && game.gameCells[i+2][j+2].getType()==X && game.gameCells[i+3][j+3].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i-1, j-1)){
                if(gameCells[i+1][j+1].getType()==X && gameCells[i+2][j+2].getType()==X && gameCells[i-1][j-1].getType()==X){
                    if(!(game.gameCells[i+1][j+1].getType()==X && game.gameCells[i+2][j+2].getType()==X && game.gameCells[i-1][j-2].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i+1,j+1) && isValid(i-1,j-1) && isValid(i-2, j-2)){
                if(gameCells[i+1][j+1].getType()==X && gameCells[i-1][j-1].getType()==X && gameCells[i-2][j-2].getType()==X){
                    if(!(game.gameCells[i+1][j+1].getType()==X && game.gameCells[i-1][j-1].getType()==X && game.gameCells[i-2][j-3].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i-1,j-1) && isValid(i-2,j-2) && isValid(i-3, j-3)){
                if(gameCells[i-1][j-1].getType()==X && gameCells[i-2][j-2].getType()==X && gameCells[i-3][j-3].getType()==X){
                    if(!(game.gameCells[i-1][j-1].getType()==X && game.gameCells[i-2][j-2].getType()==X && game.gameCells[i-3][j-3].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i+3, j-3)){
                if(gameCells[i+1][j-1].getType()==X && gameCells[i+2][j-2].getType()==X && gameCells[i+3][j-3].getType()==X){
                    if(!(game.gameCells[i+1][j-1].getType()==X && game.gameCells[i+2][j-2].getType()==X && game.gameCells[i+3][j-3].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i-1, j+1)){
                if(gameCells[i+1][j-1].getType()==X && gameCells[i+2][j-2].getType()==X && gameCells[i-1][j+1].getType()==X){
                    if(!(game.gameCells[i+1][j-1].getType()==X && game.gameCells[i+2][j-2].getType()==X && game.gameCells[i-1][j+1].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i+1,j-1) && isValid(i-1,j+1) && isValid(i-2, j+2)){
                if(gameCells[i+1][j-1].getType()==X && gameCells[i-1][j+1].getType()==X && gameCells[i-2][j+2].getType()==X){
                    if(!(game.gameCells[i+1][j-1].getType()==X && game.gameCells[i-1][j+1].getType()==X && game.gameCells[i-2][j+2].getType()==X)){
                        return true;
                    }
                }
            }
            if(isValid(i-1,j+1) && isValid(i-2,j+2) && isValid(i-3, j+3)){
                if(gameCells[i-1][j+1].getType()==X && gameCells[i-2][j+2].getType()==X && gameCells[i-3][j+3].getType()==X){
                    if(!(game.gameCells[i-1][j+1].getType()==X && game.gameCells[i-2][j+2].getType()==X && game.gameCells[i-3][j+3].getType()==X)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

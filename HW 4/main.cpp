#include <iostream>
#include <fstream>

using namespace std;

typedef enum {EMPTY, INVALID, X, O, x, o} grid;
typedef enum {EMP, USER1, USER2, COMPUTER} user;

class ConnectFour{
	public:    // Fonksiyonum için gerekli olan constructor - destructor - fonksiyon prototipleri - overloadları - datalarımı ConnectFour classımda public ve private ayırdım.
		ConnectFour();
		ConnectFour(int row, int column);
		ConnectFour(string& filename);
        ~ConnectFour();
        ConnectFour(ConnectFour& object);
        ConnectFour& operator=(const ConnectFour& game);
        friend bool operator==(ConnectFour& c1, ConnectFour& c2);
        friend bool operator!=(ConnectFour& c1, ConnectFour& c2);
        void playGame();
        void typeInput();
        const int isDone();
        static void livingCells();
        inline void setMode(string mode){
            gameMode=mode;
        }
	private:
		class Cell{       // ConnectFour classımın inner class'ı - 
			public:
                Cell();
                bool operator==(Cell& c);
                friend ostream& operator <<(ostream& outputstream, Cell& c){
                    outputstream << c.type << c.row << c.column;
                    return outputstream;
                }
                friend istream& operator >>(istream& inputstream, Cell& c){
                    inputstream >> c.column >> c.row;
                    return inputstream;     
                }
                const Cell& operator++(){   // Prefix increment
                    if(u==EMP){
                        u=USER1;
                    }
                    else if(u==USER1){
                        u=USER2;
                    }
                    else if(u==USER2){
                        u=COMPUTER;
                    }
                    else if(u==COMPUTER){
                        u=EMP;
                    }
                    return *this;
                }
                const Cell& operator--(){   // Prefix decrement
                    if(u==EMP){
                        u=COMPUTER;
                    }
                    else if(u==USER1){
                        u=EMP;
                    }
                    else if(u==USER2){
                        u=USER1;
                    }
                    else if(u==COMPUTER){
                        u=USER2;
                    }
                    return *this;
                }
                const Cell operator++(int){     //Prefix increment
                    Cell temp = *this;
                    if(u==EMP){
                        u=USER1;
                    }
                    else if(u==USER1){
                        u=USER2;
                    }
                    else if(u==USER2){
                        u=COMPUTER;
                    }
                    else if(u==COMPUTER){
                        u=EMP;
                    }
                    return temp;
                }
                const Cell operator--(int){     // Prefix decrement
                    Cell temp = *this;
                    if(u==EMP){
                        u=COMPUTER;
                    }
                    else if(u==USER1){
                        u=EMP;
                    }
                    else if(u==USER2){
                        u=USER1;
                    }
                    else if(u==COMPUTER){
                        u=USER2;
                    }
                    return temp;              
                }
                // Setter ve getterlar
                inline void setType(grid x){
                    type=x;
                }
                inline void setColumn(int i){
                	column=static_cast<char>('A'+i);
                }
				inline void setRow(int i){
					row=i;
				}
                inline void setUser(user x){
                    u=x;
                }
                const inline grid getType()const{
                    return type;
                }
                const inline char getColumn() const{
                    return column;
                }
                const inline int getRow()const {
                    return row;
                }
                const inline user getUser()const{
                    return u;
                }
			private:
				grid type;
				char column;
				int row;
                user u;
		};
        void initBoard(const string& filename);
        void printBoard();      
        const int play(int x);
        int gameInput();
		Cell ** gameBoard;        // Dinamik array
        static int livingCell;
        const int isGameFinished();
        const int isGameDraw() const;
		const int isValid(int i, int j)const;
        void play();
        void saveGame(const string& filename)const;
        void loadGame(const string& filename);
        const int computer4InARow(const int i, const int j)const;
        const int player4InARow(const int i, const int j)const;
        const int computer3InARow(const int i, const int j)const;
        const int player3InARow(const int i,const int j)const;
        const int computer2InARow(const int i, const int j)const;
        const int player2InARow(const int i, const int j)const;
        void resizeBoard(const string& filename);
        int currentCell;
		int width;
		int height;
		int turn;
        string gameType;
        string gameMode;
};

int ConnectFour::livingCell=0;      // Static değişkenimi initialize ediyorum

int main(){
        const int MAX_OBJECT=5;
        int status=1;
        string mode;
        cout << endl << "Press 'M' For Multi Games, Press 'S' For Single Game: ";
        while(status){
            cin >> mode;
            if(mode=="M" || mode=="m"){
                mode="M";
                status = 0;
            }
            else if(mode=="S" || mode=="s"){
                mode="S";
                status = 0;
            }
            if(status==1){
                cout << endl << "Please Enter A Valid Game Mode: ";
            }
        }
        if(mode == "S"){        // Oyun modum single ise
            ConnectFour game;
            game.setMode(mode);
            game.playGame();
        }
        else if(mode == "M"){       // Oyun modum multi ise
            // 5 Tane obje oluşturdum.
            string fileName;
            cout << endl << "Object 1 File: ";
            cin >> fileName;
            ConnectFour game1(fileName);
            game1.setMode(mode);
            game1.typeInput();

            cout << endl << "Object 2 File: ";
            cin >> fileName;
            ConnectFour game2(fileName);
            game2.setMode(mode);
            game2.typeInput();

            cout << endl << "Object 3 File: ";
            cin >> fileName;
            ConnectFour game3(fileName);
            game3.setMode(mode);
            game3.typeInput();

            cout << endl << "Object 4 File: ";
            cin >> fileName;
            ConnectFour game4(fileName);
            game4.setMode(mode);
            game4.typeInput();

            cout << endl << "Object 5 File: ";
            cin >> fileName;
            ConnectFour game5(fileName);
            game5.setMode(mode);
            game5.typeInput();

        int status = 1;
        while(status==1){
            int obj, objStatus=1, done=1;
                if(game1.isDone() && game2.isDone() && game3.isDone() && game4.isDone() && game5.isDone()){
                    done=1;
                }
                else{
                    done=0;
                }
            if(done==0){
                cout << endl << endl << "Select Object Number: ";
                if(!(cin >> obj)){
                    while(objStatus){
                        if(cin.eof()){
                            exit(0);
                        }
                        cout << endl << "Please Enter A Valid Object Number: ";
                        cin.clear();
                        cin.ignore(10000,'\n');
                        if(cin >> obj){
                            objStatus=0;
                        }
                    }
                }
                if(obj>MAX_OBJECT || obj < 0){
                    cout << endl << "Please Enter A Valid Object Number!";
                }
                else{
                    if(obj==1){
                        game1.playGame();
                        if(game1==game2){
                            cout << "Game 1 is same as Game 2";
                        }
                        else{
                            cout << "Game 1 is not same as Game 2";
                        }
                    }
                    if(obj==2){
                        game2.playGame();
                        if(game1==game2){
                            cout << "Game 1 is same as Game 2";
                        }
                        else{
                            cout << "Game 1 is not same as Game 2";
                        }
                    }
                    if(obj==3){
                        game3.playGame();
                        if(game1==game2){
                            cout << "Game 1 is same as Game 2";
                        }
                        else{
                            cout << "Game 1 is not same as Game 2";
                        }
                    }
                    if(obj==4){
                        game4.playGame();
                        if(game1==game2){
                            cout << "Game 1 is same as Game 2";
                        }
                        else{
                            cout << "Game 1 is not same as Game 2";
                        }
                    }
                    if(obj==5){
                        game5.playGame();
                        if(game1==game2){
                            cout << "Game 1 is same as Game 2";
                        }
                        else{
                            cout << "Game 1 is not same as Game 2";
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

// ConnectFour class'ımın default constructorında private'taki gerekli memberları doldurdum ve dinamik array için 5-5'lik yer aldım.
ConnectFour::ConnectFour(){
    gameBoard = new Cell*[5];
    for(int i=0; i<5; i++){
        gameBoard[i] = new Cell[5];
    }
    gameType = "P";
    turn = 1;
    width = 5;
    height = 5;
    currentCell=0;
}

// Default constructorımla aynı işleve sahip fakat 5-5'lik yer yerine parametrede verilen değerler kadar yer alıyorum.
ConnectFour::ConnectFour(int row, int column){
    gameBoard = new Cell*[row];
    for(int i=0; i<row; i++){
        gameBoard[i] = new Cell[column];
    }
    gameType = "P";
    turn = 1;
    height=row;
    width=column;
    currentCell=0;
}

// Parametre olarak verilen dosyadaki boardın width ve heightini hesaplayıp o değerlere göre yer alıyorum ve initBoard fonksiyonumla ayırdığım yere dosyadaki boardı, gameBoard ıma aktarıyorum.
ConnectFour::ConnectFour(string& filename){
    ifstream file;
    file.open(filename);
    if(!(file.is_open())){
        cout << "Invalid File Name!" << endl << "Aborting!" << endl;
        exit(0);
    }
    else{
        string line;
        int counter=0;
        getline(file, line);
        width = line.length();
        while(!(file.eof())){
            getline(file, line);
            counter ++;
        }
        height = counter;
        gameBoard = new Cell*[height];
        for(int i=0; i<height; i++){
            gameBoard[i] = new Cell[width];
        }
    }
    gameType = "P";
    turn = 1;
    currentCell=0;
    initBoard(filename);
    file.close();
}

// Destructorımda dinamik array için aldığım memory i delete ile geri verdim
ConnectFour::~ConnectFour(){
    for(int i=0; i<height; i++){
         delete [] gameBoard[i];
    }
    delete [] gameBoard;
}

// Cell class ımın içindeki dataları karşılaştırarak eşit olup olmadıklarını kontrol ediyorum.
bool ConnectFour::Cell::operator==(Cell& c){
    return(type==c.type && column==c.column && row==c.row);
}

// Cell classımın constructor ı
ConnectFour::Cell::Cell(){
    type=EMPTY;
    column=0;
    row=0;
    u=EMP;
}

// ConnectFour objelerimin eşit olup olmadığını kontrol eden operatörüm. Eşitse true dönüyor
bool operator==(ConnectFour& c1, ConnectFour& c2){
    if(c1.width==c2.width && c1.height==c2.height){
       for(int i=0; i<c1.height; i++){
           for(int j=0; j<c1.width; j++){
                if(c1.gameBoard[i][j].getType()!=c2.gameBoard[i][j].getType()){
                    return false;
                }
            }
        }
    }
    else{
        return false;
    }
    return true;
}

// ConnectFour objelerimin eşit olup olmadığını kontrol eden opeatörüm. Eşit değilse true dönüyor
bool operator!=(ConnectFour& c1, ConnectFour& c2){
    if(c1.width==c2.width && c1.height==c2.height){
       for(int i=0; i<c1.height; i++){
           for(int j=0; j<c1.width; j++){
                if(c1.gameBoard[i][j].getType()!=c2.gameBoard[i][j].getType()){
                    return true;
                }
            }
        }
    }
    else{
        return true;
    }
    return false;
}

// Dinamik array için ayırdığım yeri free ediyorum ve yeni değerler için tekrar yer alarak resize ediyorum.Daha sonra initBoard ı çağırarak initialize ediyorum.
void ConnectFour::resizeBoard(const string& filename){
    ifstream file;
    file.open(filename);
    if(!(file.is_open())){
        cout << "Invalid File Name!" << endl << "Aborting!" << endl;
        exit(0);
    }
    else{
        for(int i=0; i<height; i++){
            delete [] gameBoard[i];
        }
        delete [] gameBoard;
        string line;
        int counter=0;
        getline(file, line);
        width = line.length();
        while(!(file.eof())){
            getline(file, line);
            counter ++;
        }
        height = counter;
        gameBoard = new Cell*[height];
        for(int i=0; i<height; i++){
            gameBoard[i] = new Cell[width];
        }
    }
    initBoard(filename);
    file.close();
}

// ConnectFour objem için yazdığım assignment operator overloadu. Bu operator sayesinde iki objemi eşitleyebiliyorum
ConnectFour& ConnectFour::operator=(const ConnectFour& game){
    currentCell=game.currentCell;
    width=game.width;
    height=game.height;
    turn=game.turn;
    gameType=game.gameType;
    gameMode=game.gameMode;
    gameBoard = new Cell*[height];
    for(int i=0; i<height; i++){
        delete [] gameBoard[i];
    }
    delete [] gameBoard;
    for(int i=0; i<height; i++){
        gameBoard[i] = new Cell[width];
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            gameBoard[i][j]=game.gameBoard[i][j];
        }
    }
    return *this;   
}

// ConnectFour objem için yazdığım copy constructor
ConnectFour::ConnectFour(ConnectFour& game){
    currentCell=game.currentCell;
    width=game.width;
    height=game.height;
    turn=game.turn;
    gameType=game.gameType;
    gameMode=game.gameMode;
    gameBoard = new Cell*[height];
    for(int i=0; i<height; i++){
        gameBoard[i] = new Cell[width];
    }
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            gameBoard[i][j]=game.gameBoard[i][j];
        }
    }
}

// New ile aldığım boardın içini initialize eden fonksiyonum
void ConnectFour::initBoard(const string& filename){
    ifstream file;
    char c;
    file.open(filename);
    for(int i=0; i<height; i++){
        for(int j=0; j<=width; j++){
            file.get(c);
            if(c=='\n'){
                break;
            }
            if(c==' '){
                gameBoard[i][j].setType(INVALID);
                gameBoard[i][j].setColumn(j);
                gameBoard[i][j].setRow(i);
                gameBoard[i][j].setUser(EMP);
            }
            else if(c=='*'){
                gameBoard[i][j].setType(EMPTY);
                gameBoard[i][j].setColumn(j);
                gameBoard[i][j].setRow(i);
                gameBoard[i][j].setUser(EMP);
            }
        }
    }
    file.close();
}

// gameBoardımın içindeki değerlere göre board ımı print ediyorum
void ConnectFour::printBoard(){
    char characters = 'A';
    cout << endl;
    for(int k=0; k<width; k++){
        cout << characters++ << " ";
    }
    cout << endl;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(gameBoard[i][j].getType()==INVALID){
                cout << "  " ;
            }
            else if(gameBoard[i][j].getType()==EMPTY){
                cout << "* " ;
            }
            else if(gameBoard[i][j].getType()==X){
                cout << "X " ;
            }
            else if(gameBoard[i][j].getType()==O){
                cout << "O " ;
            }
            else if(gameBoard[i][j].getType()==x){
                cout << "x " ;
            }
            else if(gameBoard[i][j].getType()==o){
                cout << "o " ;
            }
       }
       cout << endl;
    }
}

// PVP yada PVC oyun türünü kullanıcıdan input olarak almak için yazdığım fonksiyon
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

// Fonksiyona gönderdiğim sütun numarası sayesinde o sütundaki boş olan en alttaki satıra hamlemi oynuyorum.
const int ConnectFour::play(int x){
    if(turn==-1){
        return -1;
    }
    for(int i=height-1; i>=0; i--){
        if(gameBoard[i][x].getType()==EMPTY){
            if(turn==1){
                gameBoard[i][x].setType(X);
                gameBoard[i][x].setUser(USER1);
                currentCell += 1;
                livingCells();
                return 1;
                break;
            }
            else if(turn==2){
                gameBoard[i][x].setType(O);
                gameBoard[i][x].setUser(USER2);
                currentCell += 1;
                livingCells();
                return 1;
                break;
            }
        }
    }
   return 0;
}

// Yapay zeka yapabileceği en iyi hamleyi bulup o sütundaki en alttaki boş satıra hamlesini oynuyor.
void ConnectFour::play(){
    int tempX=-1, tempY=-1, bestMove=0;
    for(int j=0; j<width; j++){
    for(int i=height-1; i>=0; i--){    
        if(gameBoard[i][j].getType()==EMPTY){
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
        gameBoard[tempX][tempY].setType(O);
        gameBoard[tempX][tempY].setUser(COMPUTER);
    }
    if(gameBoard[height-1][width/2].getType()==EMPTY){
        col += height/2;
        cout << endl << endl << "Computer Move: " << col;
        gameBoard[height-1][width/2].setType(O);
        gameBoard[height-1][width/2].setUser(COMPUTER);
    }
    else if(gameBoard[height-1][width/2].getType()==X){
        col += + height/2 - 1;
        cout << endl << endl << "Computer Move: " << col;
        gameBoard[height-1][width/2-1].setType(O);
        gameBoard[height-1][width/2-1].setUser(COMPUTER);
    }
    livingCells();
}

// Kullanıcıdan yapmak istediği operasyonu alıyorum ona göre boardı save-load ediyor veya girilen sütuna hamle yapılması için sütunu return ediyorum
int ConnectFour::gameInput(){
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
            status2=0;
            saveGame(line);
        }
        else if(op=="LOAD"){
            if(turn==1){
                getline(cin,line);
                loadGame(line);
                cout << endl << endl << "Game Loaded!";
                if(turn==2){
                    return -1;
                }
                else{
                    status2=0;
                    printBoard();
                }
            }
            else if(turn==2){
                getline(cin,line);
                loadGame(line);
                cout << endl << endl << "Game Loaded!";
                if(turn==1){
                    return -1;
                }
                else{
                    status2=0;
                    printBoard();
                }
            }
        }
        else if(op[1]=='\0'){
            column=op[0];
        }
        else{
        if(op.length()==0){
            exit(0);
        }
            status2=0;
            cout << endl << "Please Enter A Valid Location!";
        }
        if(status2){
            if(column<='z' && column>='a'){
                column = column - 'a';
            }
            else if(column<='Z' && column>='A'){
                 column = column - 'A';
            }
            if(column>width-1 || column<0){
                cout << endl << "Please Enter A Valid Location!";
            }
            else{
                status=0;
            }
        }
    }
    return static_cast <int> (column);
}

// Kullanıcıdan aldığım inputları sırasıyla işliyorum ve oyunun bitip bitmediğini kontrol ediyorum.Sonuca göre return yaparak oyunun sonlanmasını sağlıyorum.
void ConnectFour::playGame(){
    const int MAX_OBJECT = 5;
    if(gameMode == "S"){
        string fileName;
        cout << endl << "Please Enter File Name: ";
        cin >> fileName;
        resizeBoard(fileName);
        typeInput();
    }
    if(gameMode == "M"){
        if(isDone()==1){
            return;
        }
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
                else{
                    status1=0;
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
                    }
                }
            }
        else if(gameType=="C"){
            play();
        }
        if(isGameFinished()){
            printBoard();
            cout << endl << endl << "GAME OVER! PLAYER 2 WIN!" << endl;
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
        if(gameMode=="M"){
            break;
        }    
    }

}

// Girilen satır ve sütunun board üstünde geçerli olup olmadığını kontrol ediyorum
const int ConnectFour::isValid(int i, int j)const{
    if(i<0 || i>height-1 || j<0 || j>width-1 || gameBoard[i][j].getType()==INVALID){
        return 0;
    }
    return 1;
}

// 1. ve 2. oyuncu için 4 tane eşleyip eşleyemediğini kontrol ediyorum.Eğer 4 tane eşlenmiş ise oyun biteceği için 1 return ediyorum.
const int ConnectFour::isGameFinished(){
    int i, j, k;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if(isValid(i,j) && isValid(i+1,j) && isValid(i+2, j) && isValid(i+3, j)){
                if(gameBoard[i][j].getType() == X && gameBoard[i+1][j].getType() == X &&gameBoard[i+2][j].getType() == X && gameBoard[i+3][j].getType() == X){
                    for(k=0; k<4; k++){
                        gameBoard[i+k][j].setType(x);
                    }
                    return 1;
                }
            }
           if(isValid(i,j) && isValid(i,j+1) && isValid(i, j+2) && isValid(i, j+3)){
                if(gameBoard[i][j].getType() == X && gameBoard[i][j+1].getType() == X && gameBoard[i][j+2].getType() == X && gameBoard[i][j+3].getType() == X){
                    for(k=0; k<4; k++){
                        gameBoard[i][j+k].setType(x);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j+1) && isValid(i+2, j+2) && isValid(i+3, j+3)){
                if(gameBoard[i][j].getType() == X && gameBoard[i+1][j+1].getType() == X && gameBoard[i+2][j+2].getType() == X && gameBoard[i+3][j+3].getType() == X){
                    for(k=0; k<4; k++){
                        gameBoard[i+k][j+k].setType(x);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j-1) && isValid(i+2, j-2) && isValid(i+3, j-3)){
                if(gameBoard[i][j].getType() == X && gameBoard[i+1][j-1].getType() == X && gameBoard[i+2][j-2].getType() == X && gameBoard[i+3][j-3].getType() == X){
                    for(k=0; k<4; k++){
                        gameBoard[i+k][j-k].setType(x);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j) && isValid(i+2, j) && isValid(i+3, j)){
                if(gameBoard[i][j].getType() == O && gameBoard[i+1][j].getType() == O && gameBoard[i+2][j].getType() == O && gameBoard[i+3][j].getType() == O){
                    for(k=0; k<4; k++){
                        gameBoard[i+k][j].setType(o);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i,j+1) && isValid(i, j+2) && isValid(i, j+3)){
                if(gameBoard[i][j].getType() == O && gameBoard[i][j+1].getType() == O && gameBoard[i][j+2].getType() == O && gameBoard[i][j+3].getType() == O){
                    for(k=0; k<4; k++){
                        gameBoard[i][j+k].setType(o);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j+1) && isValid(i+2, j+2) && isValid(i+3, j+3)){
                if(gameBoard[i][j].getType() == O && gameBoard[i+1][j+1].getType() == O && gameBoard[i+2][j+2].getType() == O && gameBoard[i+3][j+3].getType() == O){
                    for(k=0; k<4; k++){
                        gameBoard[i+k][j+k].setType(o);
                    }
                    return 1;
                }
            }
            if(isValid(i,j) && isValid(i+1,j-1) && isValid(i+2, j-2) && isValid(i+3, j-3)){
                if(gameBoard[i][j].getType() == O && gameBoard[i+1][j-1].getType() == O && gameBoard[i+2][j-2].getType() == O && gameBoard[i+3][j-3].getType() == O){
                    for(k=0; k<4; k++){
                        gameBoard[i+k][j-k].setType(o);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Board üzerindeki tüm noktaları kontrol ediyorum.Eğer hiç empty kalmamış ise oyun berabere bitmiş olacağından gerekli değeri return ediyorum.
const int ConnectFour::isGameDraw() const{
    int i, j;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if(gameBoard[i][j].getType()==EMPTY){
                return 1;
            }
        }
    }
    return 0;
}

// Bilgisayarın sıradaki hamleyle 4 lü yapıp yapamayacağını kontrol ediyorum
const int ConnectFour::computer4InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2) && isValid(i, j+3)){
        if(gameBoard[i][j+1].getType()==O && gameBoard[i][j+2].getType()==O && gameBoard[i][j+3].getType()==O){
            return 6;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j-3)){
        if(gameBoard[i][j-1].getType()==O && gameBoard[i][j-2].getType()==O && gameBoard[i][j-3].getType()==O){
            return 6;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1) && isValid(i, j+2)){
        if(gameBoard[i][j-1].getType()==O && gameBoard[i][j+1].getType()==O && gameBoard[i][j+2].getType()==O){
            return 6;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j+1)){
        if(gameBoard[i][j-1].getType()==O && gameBoard[i][j-2].getType()==O && gameBoard[i][j+1].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j) && isValid(i+2,j) && isValid(i+3, j)){
        if(gameBoard[i+1][j].getType()==O && gameBoard[i+2][j].getType()==O && gameBoard[i+3][j].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i+3, j+3)){
        if(gameBoard[i+1][j+1].getType()==O && gameBoard[i+2][j+2].getType()==O && gameBoard[i+3][j+3].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i-1, j-1)){
        if(gameBoard[i+1][j+1].getType()==O && gameBoard[i+2][j+2].getType()==O && gameBoard[i-1][j-1].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameBoard[i+1][j+1].getType()==O && gameBoard[i-1][j-1].getType()==O && gameBoard[i-2][j-2].getType()==O){
            return 6;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2,j-2) && isValid(i-3, j-3)){
        if(gameBoard[i-1][j-1].getType()==O && gameBoard[i-2][j-2].getType()==O && gameBoard[i-3][j-3].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i+3, j-3)){
        if(gameBoard[i+1][j-1].getType()==O && gameBoard[i+2][j-2].getType()==O && gameBoard[i+3][j-3].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i-1, j+1)){
        if(gameBoard[i+1][j-1].getType()==O && gameBoard[i+2][j-2].getType()==O && gameBoard[i-1][j+1].getType()==O){
            return 6;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameBoard[i+1][j-1].getType()==O && gameBoard[i-1][j+1].getType()==O && gameBoard[i-2][j+2].getType()==O){
            return 6;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2,j+2) && isValid(i-3, j+3)){
        if(gameBoard[i-1][j+1].getType()==O && gameBoard[i-2][j+2].getType()==O && gameBoard[i-3][j+3].getType()==O){
            return 6;
        }
    }
    return 0;
}

// Oyuncunun sıradaki hamleyle 4 lü yapıp yapamayacağını kontrol ediyorum
const int ConnectFour::player4InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2) && isValid(i, j+3)){
        if(gameBoard[i][j+1].getType()==X && gameBoard[i][j+2].getType()==X && gameBoard[i][j+3].getType()==X){
            return 5;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j-3)){
        if(gameBoard[i][j-1].getType()==X && gameBoard[i][j-2].getType()==X && gameBoard[i][j-3].getType()==X){
            return 5;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1) && isValid(i, j+2)){
        if(gameBoard[i][j-1].getType()==X && gameBoard[i][j+1].getType()==X && gameBoard[i][j+2].getType()==X){
            return 5;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2) && isValid(i, j+1)){
        if(gameBoard[i][j-1].getType()==X && gameBoard[i][j-2].getType()==X && gameBoard[i][j+1].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j) && isValid(i+2,j) && isValid(i+3, j)){
        if(gameBoard[i+1][j].getType()==X && gameBoard[i+2][j].getType()==X && gameBoard[i+3][j].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i+3, j+3)){
        if(gameBoard[i+1][j+1].getType()==X && gameBoard[i+2][j+2].getType()==X && gameBoard[i+3][j+3].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2) && isValid(i-1, j-1)){
        if(gameBoard[i+1][j+1].getType()==X && gameBoard[i+2][j+2].getType()==X && gameBoard[i-1][j-1].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameBoard[i+1][j+1].getType()==X && gameBoard[i-1][j-1].getType()==X && gameBoard[i-2][j-2].getType()==X){
            return 5;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2,j-2) && isValid(i-3, j-3)){
        if(gameBoard[i-1][j-1].getType()==X && gameBoard[i-2][j-2].getType()==X && gameBoard[i-3][j-3].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i+3, j-3)){
        if(gameBoard[i+1][j-1].getType()==X && gameBoard[i+2][j-2].getType()==X && gameBoard[i+3][j-3].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2) && isValid(i-1, j+1)){
        if(gameBoard[i+1][j-1].getType()==X && gameBoard[i+2][j-2].getType()==X && gameBoard[i-1][j+1].getType()==X){
            return 5;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameBoard[i+1][j-1].getType()==X && gameBoard[i-1][j+1].getType()==X && gameBoard[i-2][j+2].getType()==X){
            return 5;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2,j+2) && isValid(i-3, j+3)){
        if(gameBoard[i-1][j+1].getType()==X && gameBoard[i-2][j+2].getType()==X && gameBoard[i-3][j+3].getType()==X){
            return 5;
        }
    }
    return 0;
}

// Bilgisayarın sıradaki hamleyle 3 lü yapıp yapamayacağını kontrol ediyorum
const int ConnectFour::computer3InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2)){
        if(gameBoard[i][j+1].getType()==O && gameBoard[i][j+2].getType()==O){
            return 4;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2)){
        if(gameBoard[i][j-1].getType()==O && gameBoard[i][j-2].getType()==O){
            return 4;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1)){
        if(gameBoard[i][j-1].getType()==O && gameBoard[i][j+1].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j) && isValid(i+2,j)){
        if(gameBoard[i+1][j].getType()==O && gameBoard[i+2][j].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2)){
        if(gameBoard[i+1][j+1].getType()==O && gameBoard[i+2][j+2].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1, j-1)){
        if(gameBoard[i+1][j+1].getType()==O && gameBoard[i-1][j-1].getType()==O){
            return 4;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameBoard[i-1][j-1].getType()==O && gameBoard[i-2][j-2].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2)){
        if(gameBoard[i+1][j-1].getType()==O && gameBoard[i+2][j-2].getType()==O){
            return 4;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1, j+1)){
        if(gameBoard[i+1][j-1].getType()==O && gameBoard[i-1][j+1].getType()==O){
            return 4;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameBoard[i-1][j+1].getType()==O && gameBoard[i-2][j+2].getType()==O){
            return 4;
        }
    }
    return 0;
}

// Oyuncunun sıradaki hamleyle 3 lü yapıp yapamayacağını kontrol ediyorum
const int ConnectFour::player3InARow(const int i, const int j)const{
    if(isValid(i,j+1) && isValid(i,j+2)){
        if(gameBoard[i][j+1].getType()==X && gameBoard[i][j+2].getType()==X){
            return 3;
        }
    }
    if(isValid(i,j-1) && isValid(i,j-2)){
        if(gameBoard[i][j-1].getType()==X && gameBoard[i][j-2].getType()==X){
            return 3;
        }
    }
    if(isValid(i,j-1) && isValid(i,j+1)){
        if(gameBoard[i][j-1].getType()==X && gameBoard[i][j+1].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j) && isValid(i+2,j)){
        if(gameBoard[i+1][j].getType()==X && gameBoard[i+2][j].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j+1) && isValid(i+2,j+2)){
        if(gameBoard[i+1][j+1].getType()==X && gameBoard[i+2][j+2].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j+1) && isValid(i-1, j-1)){
        if(gameBoard[i+1][j+1].getType()==X && gameBoard[i-1][j-1].getType()==X){
            return 3;
        }
    }
    if(isValid(i-1,j-1) && isValid(i-2, j-2)){
        if(gameBoard[i-1][j-1].getType()==X && gameBoard[i-2][j-2].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j-1) && isValid(i+2,j-2)){
        if(gameBoard[i+1][j-1].getType()==X && gameBoard[i+2][j-2].getType()==X){
            return 3;
        }
    }
    if(isValid(i+1,j-1) && isValid(i-1, j+1)){
        if(gameBoard[i+1][j-1].getType()==X && gameBoard[i-1][j+1].getType()==X){
            return 3;
        }
    }
    if(isValid(i-1,j+1) && isValid(i-2, j+2)){
        if(gameBoard[i-1][j+1].getType()==X && gameBoard[i-2][j+2].getType()==X){
            return 3;
        }
    }
    return 0;
}

// Bilgisayarın sıradaki hamleyle 2 li yapıp yapamayacağını kontrol ediyorum
const int ConnectFour::computer2InARow(const int i, const int j)const{
   if(isValid(i,j+1)){
        if(gameBoard[i][j+1].getType()==O){
            return 2;
        }
    }
    if(isValid(i,j-1)){
        if(gameBoard[i][j-1].getType()==O){
            return 2;
        }
    }
    if(isValid(i+1,j)){
        if(gameBoard[i+1][j].getType()==O){
            return 2;
        }
    }
    if(isValid(i+1,j+1)){
        if(gameBoard[i+1][j+1].getType()==O){
            return 2;
        }
    }
    if(isValid(i-1, j-1)){
        if(gameBoard[i-1][j-1].getType()==O){
            return 2;
        }
    }
    if(isValid(i+1,j-1)){
        if(gameBoard[i+1][j-1].getType()==O){
            return 2;
        }
    }
    if(isValid(i-1,j+1)){
        if(gameBoard[i-1][j+1].getType()==O){
            return 2;
        }
    }
    return 0;
}

// Oyuncunun sıradaki hamleyle 2 li yapıp yapamayacağını kontrol ediyorum
const int ConnectFour::player2InARow(const int i, const int j)const{
   if(isValid(i,j+1)){
        if(gameBoard[i][j+1].getType()==X){
            return 1;
        }
    }
    if(isValid(i,j-1)){
        if(gameBoard[i][j-1].getType()==X){
            return 1;
        }
    }
    if(isValid(i+1,j)){
        if(gameBoard[i+1][j].getType()==X){
            return 1;
        }
    }
    if(isValid(i+1,j+1)){
        if(gameBoard[i+1][j+1].getType()==X){
            return 1;
        }
    }
    if(isValid(i-1, j-1)){
        if(gameBoard[i-1][j-1].getType()==X){
            return 1;
        }
    }
    if(isValid(i+1,j-1)){
        if(gameBoard[i+1][j-1].getType()==X){
            return 1;
        }
    }
    if(isValid(i-1,j+1)){
        if(gameBoard[i-1][j+1].getType()==X){
            return 1;
        }
    }
    return 0;
}

// Classımdaki gerekli data memberları ve oyun boardımı dosyaya bastırıyorum
void ConnectFour::saveGame(const string& filename)const{
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
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                if(gameBoard[i][j].getType()==INVALID){
                    myFile << " ";
                }             
                if(gameBoard[i][j].getType()==EMPTY){
                    myFile << "*";
                }
                else if(gameBoard[i][j].getType()==X){
                    myFile << "X";
                }
                else if(gameBoard[i][j].getType()==O){
                    myFile << "O";
                }
            }
            if(i!=height-1){
                myFile << endl;
            }
        }
        cout << endl << "Game Saved!";
        myFile.close();
    }
}

// Yeni oyun load edeceğim için oynadığım oyundaki memory i free ediyorum daha sonra dosyadan gerekli memberları çekip yeni boardıma yer ayırıp initialize ediyorum.
void ConnectFour::loadGame(const string& filename){
    ifstream myFile;
    char c;
    string temp;
    myFile.open(filename);
    if (!myFile.is_open()){
        cerr << endl << "Unable To Open File! Aborting!" << endl;
        exit(0);
    }
    else{
        livingCell=livingCell-currentCell;
        for(int i=0; i<height; i++){
            delete [] gameBoard[i];
        }
        delete [] gameBoard;
        myFile >> width;
        myFile >> height;
        myFile >> gameType;
        myFile >> turn;
        myFile >> currentCell;
        getline(myFile, temp);
        gameBoard = new Cell*[height];
        for(int i=0; i<height; i++){
            gameBoard[i] = new Cell[width];
        }
        livingCell=livingCell+currentCell;
        for(int i=0; i<height; i++){
            for(int j=0; j<width+1; j++){
                myFile.get(c);
                if(c=='\n'){
                    break;
                }
                if(c==' '){
                    gameBoard[i][j].setType(INVALID);
                    gameBoard[i][j].setColumn(j);
                    gameBoard[i][j].setRow(i);
                    gameBoard[i][j].setUser(EMP);
                }
                else if(c=='*'){
                    gameBoard[i][j].setType(EMPTY);
                    gameBoard[i][j].setColumn(j);
                    gameBoard[i][j].setRow(i);
                    gameBoard[i][j].setUser(EMP);
                }
                else if(c=='X'){
                    gameBoard[i][j].setType(X);
                    gameBoard[i][j].setColumn(j);
                    gameBoard[i][j].setRow(i);
                    gameBoard[i][j].setUser(USER1);
                }
                else if(c=='O'){
                    gameBoard[i][j].setType(O);
                    gameBoard[i][j].setColumn(j);
                    gameBoard[i][j].setRow(i);
                    gameBoard[i][j].setUser(USER2);
                }
           }
        }
        myFile.close();
    }
}

// Multi oyunlarda objemdeki oyunun sonlanıp sonlanmadığını kontrol eden fonksiyon. Bu fonksiyonu 5 obje için aynı anda kontrol ederek hepsi sonlanmışsa programımı sonlandırıyorum
const int ConnectFour::isDone(){
    if(!isGameDraw()){
        return 1;
    }
    else{
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                if(gameBoard[i][j].getType()==x ||gameBoard[i][j].getType()==o){
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Static değişkenim sayesinde toplam kaç cell'e hamle yapıldığını hesaplıyorum.Static değişkenim 0 lanmayacağı için multi oyunlardada bütün objelerdeki toplam hamle sayısını bulabiliyorum
void ConnectFour::livingCells(){
    livingCell++;
    cout << endl << "Living Cells: " << livingCell;
}
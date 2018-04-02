#include <fstream>
#include "connectfourabstract.h"

namespace CCKGTU{
    ConnectFourAbstract::ConnectFourAbstract(int row, int column){
        gameBoard = new Cell*[row];             // Gameboard icin dinamik yer ayiriyorum
        for(int i=0; i<row; i++){
            gameBoard[i] = new Cell[column];
        }
        gameType = "P";
        turn = 1;
        height=row;
        width=column;
    }


    ConnectFourAbstract::ConnectFourAbstract(){
        gameType = "P";
        turn = 1;
        height=10;
        width=10;
        gameBoard = new Cell*[height];      //Gameboard icin dinamik yer ayiriyorum 
        for(int i=0; i<height; i++){
            gameBoard[i] = new Cell[width];
        }
    }

    ConnectFourAbstract::~ConnectFourAbstract(){
        clearBoard();
    }

    
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& obj){   // Copy Constructor
        gameType = obj.gameType;
        turn = obj.turn;
        height=obj.height;
        width=obj.width;
        for(int i=0; i<height; i++){
            for(int j=0; j<height; j++){
                gameBoard[i][j]=obj.gameBoard[i][j];
            }
        }
    }

    ConnectFourAbstract& ConnectFourAbstract::operator==(const ConnectFourAbstract& obj){
        clearBoard();
        gameType = obj.gameType;
        turn = obj.turn;
        height=obj.height;
        width=obj.width;
        resizeBoard();
        initBoard();
        for(int i=0; i<height; i++){
            for(int j=0; j<height; j++){
                gameBoard[i][j]=obj.gameBoard[i][j];
            }
        }
        return *this;
    }


    void ConnectFourAbstract::playGame(){
        sizeInput();
        typeInput();
        resizeBoard();
        initBoard();
        printBoard();
        int status = 1, status1 = 1, status2 = 1;
        while(status==1){
            status1 = 1;
            while(status1==1){
                    turn = 1;
                    status1 = play(gameInput());    // GameInputun return degerini play fonksiyonuna parametre olarak gonderdim
                    if(status1==0){         // play fonksiyonunun return degeri 0 ise sutun dolmus olacagından hata mesajı verdim
                        cout << endl << "There are no spaces in this column!" << endl ;
                        status1=1;
                    }
                    else if(status1==-1){
                        status1=0;
                    }
                    else{
                        status1=0;
                    }
            }
            if(isGameFinished()){           // Eger oyun yukardaki hamleden sonra bittiyse player 1 kazancagı icin bilgi mesajını bastırıp donguyu sonlandirdim
                printBoard();
                cout << endl << endl << "GAME OVER! PLAYER 1 WIN!" << endl;
                status=0;
                break;
            }
            if(!isGameDraw()){      // Eger board yukardaki hamleden sonra dolduysa oyun berabere biteceginden bilgi mesajını bastırıp donguyu sonlandirdim.
                printBoard();
                cout << endl << endl << "GAME OVER!  DRAW!" << endl;
                status=0;
                break;
            }
            printBoard();
            if(gameType=="P"){      // Eger pvp modunda isek player 2 hamlesini gerceklestirecek
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
                if(gameType=="C"){      // Eger pvc modunda isek computer hamlesini gerceklestirecek
                    play();
                }
                if(isGameFinished()){   // Eger oyun yukardaki hamleden sonra bittiyse player 2 veya computer kazancagı icin bilgi mesajını bastırıp donguyu sonlandirdim
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
                else if(!isGameDraw()){         // Eger board yukardaki hamleden sonra dolduysa oyun berabere biteceginden bilgi mesajını bastırıp donguyu sonlandirdim.
                    printBoard();
                    cout << endl << endl << "GAME OVER!  DRAW!" << endl;
                    status=0;
                    break;
                }
                printBoard();
        }
    }

    void ConnectFourAbstract::sizeInput(){
        clearBoard();       // Boardimda ayirdigim yeri free ediyorum
        int sizeStatus=1;
        cout << endl << "Please Enter Height Size: ";
        if(!(cin >> height) || height < 4){   
            while(sizeStatus){          // Kullanici gecerli bir size girene kadar devam edecek dongu
                cout << endl << "Please Enter A Valid Height Size: ";
                cin.clear();
                cin.ignore(10000,'\n');
                if(cin >> height && height >= 4){
                    sizeStatus=0;
                }
           }
        }
        sizeStatus=1;
        cout << endl << "Please Enter Width Size: ";
        if(!(cin >> width) || width < 4){
            while(sizeStatus){          // Kullanici gecerli bir size girene kadar devam edecek dongu
                cout << endl << "Please Enter A Valid Width Size: ";
                cin.clear();
                cin.ignore(10000,'\n');
                if(cin >> width && width >=4){
                    sizeStatus=0;
                }
           }
        }
    }

    void ConnectFourAbstract::typeInput(){      // Kullanicinin girdigi oyun modunu gerekli member variable a atan fonksiyonum
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

    void ConnectFourAbstract::initBoard(){      // Boardimi EMPTY ile dolduran fonksiyon
        for(int i=0; i<height; i++){
            for(int j=0; j<=width; j++){
                    gameBoard[i][j].setType(EMPTY);
                    gameBoard[i][j].setColumn(j);
                    gameBoard[i][j].setRow(i);
            }
        }
    }

    void ConnectFourAbstract::resizeBoard(){    // Height ve width degerine gore dinamik olarak yer aldigim fonksiyon
        gameBoard = new Cell*[height+1];
        for(int i=0; i<height; i++){
            gameBoard[i] = new Cell[width+1];
        }   
    }

    void ConnectFourAbstract::clearBoard()const{        // Boardim icin aldigim yeri free eden fonksiyon
        for(int i=0; i<height; i++){
            delete [] gameBoard[i];
        }
        delete [] gameBoard;
    }

    int ConnectFourAbstract::isValid(int i, int j)const{    // Verilen i ve j koordinatinin board ustunde olup olmadigini kontrol eden fonksiyon
        if(i<0 || i>width-1 || j<0 || j>height-1){
            return 0;
        }
        return 1;        
    }

    int ConnectFourAbstract::isGameDraw()const{                 // Oyunun berabere bitip bitmedigini kontrol eden fonksiyon
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

    void ConnectFourAbstract::printBoard()const{                // Gameboardi ekrana bastiran fonksiyon 
        char characters = 'A';
        cout << endl << endl;
        for(int k=0; k<width; k++){
            cout << "  " << characters++ << " ";
        }
        for(int i=height-1; i>-1; i--){
            cout << endl;
            for(int k=0; k<width; k++){
                cout << " ---";
            }
            cout << endl << "|";
            for(int j=0; j<width; j++){
                if(gameBoard[i][j].getType()==EMPTY){
                    cout << " . |" ;
                }
                if(gameBoard[i][j].getType()==X){
                    cout << " X |";
                }
                if(gameBoard[i][j].getType()==O){
                    cout << " O |";
                }
                if(gameBoard[i][j].getType()==x){
                    cout << " x |";
                }
                if(gameBoard[i][j].getType()==o){
                    cout << " o |";
                }
           }
        }
        cout << endl;
        for(int k=0; k<width; k++){
            cout << " ---";
        }
    }

    int ConnectFourAbstract::play(int x){
        if(turn==-1){
            return -1;
        }
        for(int i=0; i<height; i++){        // Parametre olarak gelen sutundaki elemanlara en alttan baslayrak bakiyor ve EMPTY gordugunda hamleyi yapip donguyu bitiriyor
            if(gameBoard[i][x].getType()==EMPTY){
                if(turn==1){
                    gameBoard[i][x].setType(X);
                    return 1;
                    break;
                }
                else if(turn==2){
                    gameBoard[i][x].setType(O);
                    return 1;
                    break;
                }
            }
        }
        return 0;
    }

    int ConnectFourAbstract::gameInput(){
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
            if(cin.eof()){          // Eger dosyanin sonuna geldiysek program sonlaniyor
                exit(0);
            }
            if(op=="SAVE"){         // Eger save komutu girildiyse getline yaparak dosya ismini aliyorum ve save fonksiyonumu cagiriyorum
                getline(cin, line);
                saveGame(line);
            }
            else if(op=="LOAD"){            // Eger load komutu girildiyse getline yaparak dosya ismini aliyorum ve load fonksiyonumu cagiriyorum
                // Turn sırasına göre işlem yaparak load edilen dosyadaki sirayi kaybetmiyorum
                if(turn==1){        
                    getline(cin,line);
                    loadGame(line);
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
                    loadGame(line);
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
                if(op[1]=='\0'){        // Eger 2. karakter NULL ise kullanici gecerli bir column girmis olacagi icin column'a op[0]'i atiyorum
                    column=op[0];
                }
                else{
                    status2=0;
                }
                if(status2){        // Harf olarak girilen sutunu integera ceviriyorum
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
        }
        return static_cast <int> (column);
    }

    void ConnectFourAbstract::saveGame(const string& filename)const{
        ofstream myFile;
        myFile.open(filename);
        if (!myFile.is_open()) {
            cerr << endl << "Unable To Open File" << endl;
        }
        else{       // Private data memberlarimi dosyaya yazdiriyorum
            myFile << width << endl;
            myFile << height << endl;
            myFile << gameType << endl;
            myFile << turn << endl;
            for(int i=0; i<height; i++){        // Bu dongu icerisinde ise boardi tek tek dosyaya yazdiriyorum
                for(int j=0; j<width; j++){          
                    if(gameBoard[i][j].getType()==EMPTY){
                        myFile << "EMPTY";
                    }
                    else if(gameBoard[i][j].getType()==X){
                        myFile << "X";
                    }
                    else if(gameBoard[i][j].getType()==O){
                        myFile << "O";
                    }
                    myFile << endl;
                }
            }
            cout << endl << "Game Saved!";
            myFile.close();     // Dosyayi kapatiyorum
        }
    }

    void ConnectFourAbstract::loadGame(const string& filename){
        ifstream myFile;
        string line;
        myFile.open(filename);
        if (!myFile.is_open()){
            cerr << endl << "Unable To Open File" << endl;
        }
        else{
            clearBoard();       // Dinamik olarak aldigim yeri free ediyorum
            // Dosyadan sırasıyla private data memberlarimi atiyorum
            myFile >> width;
            myFile >> height;
            myFile >> gameType;
            myFile >> turn;
            resizeBoard();      // Yeni size a gore dinamik olarak yer aliyorum
            initBoard();    //  Aldigim yeri EMPTY ile dolduruyorum
            for(int i=0; i<height; i++){    // EMPTY ile doldurdugum yerlere X ve O'lari koyuyorum
                for(int j=0; j<width; j++){
                    myFile >> line;
                    if(line=="EMPTY"){
                        gameBoard[i][j].setType(EMPTY);
                    }
                    else if(line=="X"){
                        gameBoard[i][j].setType(X);
                    }
                    else if(line=="O"){
                        gameBoard[i][j].setType(O);
                    }
                }
            }
            myFile.close();     // Dosyayi kapatiyorum
        }
    }

    int ConnectFourAbstract::computer4InARowPlus(int i, int j)const{    // Computer 4'lü Yatay Dikey Kontroller
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
        if(isValid(i-1,j) && isValid(i-2,j) && isValid(i-3, j)){
            if(gameBoard[i-1][j].getType()==O && gameBoard[i-2][j].getType()==O && gameBoard[i-3][j].getType()==O){
                return 6;
            }
        }
        return 0;
    }

    int ConnectFourAbstract::computer4InARowDiag(int i, int j)const{    // Computer 4'lü Capraz Kontroller
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

    int ConnectFourAbstract::computer3InARowPlus(int i, int j)const{     // Computer 3'lü Yatay Dikey Kontroller
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
        if(isValid(i-1,j) && isValid(i-2,j)){
            if(gameBoard[i-1][j].getType()==O && gameBoard[i-2][j].getType()==O){
                return 4;
            }
        }
        return 0;
    }

    int ConnectFourAbstract::computer3InARowDiag(int i, int j)const{    // Computer 3'lü Capraz Kontroller
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

    int ConnectFourAbstract::computer2InARowPlus(int i, int j)const{     // Computer 2'lü Yatay Dikey Kontroller
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
        if(isValid(i-1,j)){
            if(gameBoard[i-1][j].getType()==O){
                return 2;
            }
        }
        return 0;
    }

    int ConnectFourAbstract::computer2InARowDiag(int i, int j)const{    // Computer 2'li Capraz Kontroller
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

    int ConnectFourAbstract::player4InARowPlus(int i, int j)const{    // Player 4'lü Yatay Dikey Kontroller
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
        if(isValid(i-1,j) && isValid(i-2,j) && isValid(i-3, j)){
            if(gameBoard[i-1][j].getType()==X && gameBoard[i-2][j].getType()==X && gameBoard[i-3][j].getType()==X){
                return 5;
            }
        }
        return 0;
    }

    int ConnectFourAbstract::player4InARowDiag(int i, int j)const{       // Player 4'lu Capraz Kontroller
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

    int ConnectFourAbstract::player3InARowPlus(int i, int j)const{      // Player 3'lü Yatay Dikey Kontroller
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
        if(isValid(i-1,j) && isValid(i-2,j)){
            if(gameBoard[i-1][j].getType()==X && gameBoard[i-2][j].getType()==X){
                return 3;
            }
        }
        return 0;
    }

    int ConnectFourAbstract::player3InARowDiag(int i, int j)const{       // Player 3'lu Capraz Kontroller
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

    int ConnectFourAbstract::player2InARowPlus(int i, int j)const{       // Player 2'li Yatay Dikey Kontroller
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
        if(isValid(i-1,j)){
            if(gameBoard[i-1][j].getType()==X){
                return 1;
            }
        }
        return 0;
    }

    int ConnectFourAbstract::player2InARowDiag(int i, int j)const{       // Player 2'li Capraz Kontroller
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
}
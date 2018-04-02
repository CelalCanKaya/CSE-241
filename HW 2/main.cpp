#include <iostream>
#include <limits>    // Size istedi�im zaman harf girildi�inde program sonsuz d�ng�ye giriyodu. Bu sorunu ��zmek i�in bu k�t�phaneyi ekledim.
#include <string>
#include <fstream>

using namespace std;
typedef enum {EMPTY, X, O, x, o} grid;

const int totalSize = 9;
const int maxBoardSize = 20;
const int maxColumns = 20;

// Fonksiyon prototipleri
void draw_table(grid TABLE[][maxBoardSize], int size);
void init_table(grid TABLE[][maxBoardSize], int size);
int player1_move(grid TABLE[][maxBoardSize], string gameMode, int turn, const int& size);
int player2_move(grid TABLE[][maxBoardSize], string gameMode, int turn, const int& size);
int is_valid(int i, int j, int size);
int is_game_finished(grid TABLE[][maxBoardSize], int size);
int is_game_draw(grid TABLE[][maxBoardSize], int size);
void computer_move(grid TABLE[][maxBoardSize], int size);
int computer_4_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size);
int player_4_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size);
int computer_3_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size);
int player_3_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size);
int computer_2_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size);
int player_2_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size);
void save_game(grid TABLE[][maxBoardSize], string fileName, string gameMode, int size, int Turn=1);
void load_game(grid TABLE[][maxBoardSize], string fileName, string& gameMode, int& Turn, int& size);


int main(){
    int size, i, status3;
    auto status=1, size_status=1, game_mode_status=1, turn=-1, status2=1, game_loaded=0;
    string game_mode;
    string askForLoad;
    int valid_sizes[totalSize] = {4,6,8,10,12,14,16,18,20};   // Girilebilecek size'lar� array haline getirdim.
    cout << "4 IN A ROW!" << endl << endl << "Try To Build A Row Of Four Checkers (Vertically, Horizontally, Diagonally) While Keeping Your Opponent From Doing The Same." << endl; // Oyun hakk�nda bilgilendirme sat�r�
    cout << endl << endl << "If You Want To Load A Game Type 'LOAD FILE.TXT'.If You Want To Start A New Game Press A Character Then Enter: ";
    grid TABLE[maxBoardSize][maxBoardSize];     // Oyun tablomun �ift boyutlu arrayini tan�mlad�m
    cin >> askForLoad;
    if(askForLoad=="LOAD"){
        getline(cin, askForLoad);
        load_game(TABLE, askForLoad, game_mode, turn, size);
        game_loaded=1;
        if(turn==2){
            draw_table(TABLE, size);
            while(status2){      // Player1_move fonksiyonumun return de�erine bak�larak oyun alan�n�n dolu olup olmad���n� kontrol ediyorum. E�er doluysa hata mesaj� g�sterip tekrar input al�yorum
                status3 = player2_move(TABLE, game_mode, turn, size);
                if(status3==0){
                    cerr << endl << endl << "There are no spaces in this column!" << endl;
                }
                else if(status3==1){
                    status2=0;
                }
                else if(status3==2){
                    cout << endl << "Game Saved!" << endl ;                }
            };
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmedi�ini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 2 WIN!" << endl;
                status=0;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere olup olmad�g�n� kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl <<
                endl<< "GAME OVER!  DRAW!" << endl;
                status=0;
            }
        }
    }
    if(game_loaded==0){
        while(size_status){
            cerr << endl << "Please Enter A Valid Board Size (4,6,8 ... 20) : ";
            if(!(cin >> size)){         // Burdaki if'i size'a harf girildi�i durumdaki d�ng�den kurtarmak i�in "Stackoverflow'dan" buldugum while kodunu kendim i�in if'e �evirdim.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            for(i=0; i<totalSize; i++){     // For d�ng�s�yle size'�n ge�erli olup olmad�g�na bak�yorm e�er ge�erliyse status=0 oluyor ve while d�ng�s�nden ��k�yor
                if(valid_sizes[i]==size){
                    size_status=0;
                }
            }
        }
        init_table(TABLE, size);
        while(game_mode_status){
            cout << endl << "Press 'C' For Playing Against Computer, Press 'P' For Playing Against Player: ";
            cin >> game_mode;       // E�er kullan�c� p yada c tu�lamaz ise while d�ng�s� sayesinde tekrar sorulacak.
            if(game_mode=="P" || game_mode=="p"){
                    game_mode_status=0;
            }
            if(game_mode=="C" || game_mode=="c"){
                    game_mode_status=0;
            }
        }
    }
    if(game_mode == "P" || game_mode == "p"){       // E�er oyuncuya kar�� oynamay� se�tiysek a�a��daki kod blo�u �al��acak
        while(status==1){
            draw_table(TABLE, size);
            turn = 1;
            status2=1;
            while(status2){      // Player1_move fonksiyonumun return de�erine bak�larak oyun alan�n�n dolu olup olmad���n� kontrol ediyorum. E�er doluysa hata mesaj� g�sterip tekrar input al�yorum
                status3 = player1_move(TABLE, game_mode, turn, size);
                if(status3==0){
                    cerr << endl << endl << "There are no spaces in this column!" << endl;
                }
                else if(status3==1){
                    status2=0;
                }
                else if(status3==2){
                    cout << endl << "Game Saved!" << endl ;
                }
            };
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmedi�ini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 1 WIN!" << endl;
                status=0;
                break;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere bitip bitmedi�ini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER!  DRAW!" << endl;
                status=0;
                break;
            }
            draw_table(TABLE,size);
            turn = 2;
            status2=1;
            while(status2){      // Player1_move fonksiyonumun return de�erine bak�larak oyun alan�n�n dolu olup olmad���n� kontrol ediyorum. E�er doluysa hata mesaj� g�sterip tekrar input al�yorum
                status3 = player2_move(TABLE, game_mode, turn, size);
                if(status3==0){
                    cerr << endl << endl << "There are no spaces in this column!" << endl;
                }
                else if(status3==1){
                    status2=0;
                }
                else if(status3==2){
                    cout << endl << "Game Saved!" << endl ;                }
            };
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmedi�ini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 2 WIN!" << endl;
                status=0;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere olup olmad�g�n� kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl <<
                endl<< "GAME OVER!  DRAW!" << endl;
                status=0;
            }
        }
    }
    else if(game_mode=="C" || game_mode == "c"){        // E�er bilgisayara kar�� oynamak istediysek a�a��daki kod blo�u �al��acak.
        while(status==1){
            draw_table(TABLE, size);
            status2=1;
            turn = 1;
            while(status2){      // Player1_move fonksiyonumun return de�erine bak�larak oyun alan�n�n dolu olup olmad���n� kontrol ediyorum. E�er doluysa hata mesaj� g�sterip tekrar input al�yorum
                status3 = player1_move(TABLE, game_mode, turn, size);
                if(status3==0){
                    cerr << endl << endl << "There are no spaces in this column!" << endl;
                }
                else if(status3==1){
                    status2=0;
                }
                else if(status3==2){
                    cout << endl << "Game Saved!" << endl;
                }
            };
            if(is_game_finished(TABLE, size)){
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 1 WIN!" << endl;
                status=0;
                break;
            }
            else if(!is_game_draw(TABLE, size)){
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER!  DRAW!" << endl;
                status=0;
                break;
            }
            draw_table(TABLE,size);
            computer_move(TABLE, size);         // Bilgisayar hamlesini yap�yor
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmedi�i kontrol ediliyor
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! COMPUTER WIN!" << endl;
                status=0;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere bitip bitmedi�i kontrol ediliyor
                draw_table(TABLE, size);
                cout << endl << endl<< "GAME OVER!  DRAW!" << endl;
                status=0;
            }
        }
    }
    return 0;
}

void init_table(grid TABLE[][maxBoardSize], int size){      // Oyun board�n� empty yap�yorum
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            TABLE[i][j] = EMPTY;
       }
    }
}

void draw_table(grid TABLE[][maxBoardSize], int size){      // Oyun board�n� ekrana bast�r�yorum
    int i, j, k;
    char characters = 'A';
    cout << endl << endl;
    for(k=0; k<size; k++){          // Bu for d�ng�s�yle board�n �st�ndeki s�tun harflerini bast�r�yorum
        cout << "   " << characters++ << "  ";
    }
    for(i=size-1; i>-1; i--){       // Bu for d�ng�s�yle board�mdaki harfleri noktalar� ve etraf�ndaki �er�eveyi �izdiriyorum
        cout << endl;
        for(k=0; k<size; k++){
            cout << " -----";
        }
        cout << endl << "|";
        for(j=0; j<size; j++){
            if(TABLE[i][j]==EMPTY){
                cout << "  .  |";
            }
            if(TABLE[i][j]==X){
                cout << "  X  |";
            }
            if(TABLE[i][j]==O){
                cout << "  O  |";
            }
            if(TABLE[i][j]==x){
                cout << "  x  |";
            }
            if(TABLE[i][j]==o){
                cout << "  o  |";
            }
       }
    }
    cout << endl;
    for(k=0; k<size; k++){      // Bu d�ng�yle oyun board�m�n en alt�ndaki bo�lu�u kapat�yorum
        cout << " -----";
    }
}

int player1_move(grid TABLE[][maxBoardSize], string gameMode, int turn, const int& size){         // Bu fonksiyonla 1. oyuncunun hareketini al�yorum
    string column, line;
    string columns[maxColumns] = {"A", "B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};
    int i, status=1, temp=-1;
    cout << endl << "PLAYER 1 - Select a column; ";
    while(status==1){           // Bu d�ng�m�n i�inde kullanc�dan harf al�yorum.Daha sonra ald���m harfi 'A' veya 'a' harfinden ��kararak ula�t���m sonu� atacag�m s�tunun integer de�erine e�it oluyor.
        cin >> column;
        if(column=="SAVE"){
            getline(cin, line);
            save_game(TABLE,line,gameMode,size);
            return 2;
        }
        for(int j=0; j<size; j++){
            if(columns[j]==column){
               temp=j;
            }
        }
        if(temp>size-1 || temp<0){          // E�er kalan sonu� size'dan b�y�kse yada sizedan k���kse hata mesaj�n� ekrana bast�r�yorum
            cerr << "Please Enter A Valid Location: ";
        }
        else{
            status=0;
        }
    }
    for(i=0; i<size; i++){      // Kullan�c�dan ald���m s�tundaki bo� olan en alt sat�ra yerle�tiriyorum
        if(TABLE[i][temp]==EMPTY){
            TABLE[i][temp] = X;
            return 1;
        }
    }
    return 0;
}

int player2_move(grid TABLE[][maxBoardSize], string gameMode, int turn, const int& size){         // Bu fonksiyonla 1. oyuncunun hareketini al�yorum
    string column, line;
    string columns[maxColumns] = {"A", "B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};
    int i, status=1, temp=-1;
    cout << endl << "PLAYER 2 - Select a column; ";
    while(status==1){           // Bu d�ng�m�n i�inde kullanc�dan harf al�yorum.Daha sonra ald���m harfi 'A' veya 'a' harfinden ��kararak ula�t���m sonu� atacag�m s�tunun integer de�erine e�it oluyor.
        cin >> column;
        if(column=="SAVE"){
            getline(cin, line);
            save_game(TABLE,line,gameMode,size, turn);
            return 2;
        }
        for(int j=0; j<size; j++){
            if(columns[j]==column){
               temp=j;
            }
        }
        if(temp>size-1 || temp<0){          // E�er kalan sonu� size'dan b�y�kse yada sizedan k���kse hata mesaj�n� ekrana bast�r�yorum
            cerr << "Please Enter A Valid Location: ";
        }
        else{
            status=0;
        }
    }
    for(i=0; i<size; i++){      // Kullan�c�dan ald���m s�tundaki bo� olan en alt sat�ra yerle�tiriyorum
        if(TABLE[i][temp]==EMPTY){
            TABLE[i][temp] = O;
            return 1;
        }
    }
    return 0;
}

int is_valid(int i, int j,int size){        // Yollad���m i ve j parametrelerinin boardda ge�erli bir yer olup olmad�g�n� kontrol ediyorum
    if(i<0 || i>size || j<0 || j>size){
        return 0;
    }
    return 1;
}

int is_game_finished(grid TABLE[][maxBoardSize], int size){         // Oyunun yatay, dikey yada �apraz olarak sonlan�p sonlanmad���n� kontrol ediyorum. E�er oyun sonlanm�� ise hangilerinin bitirdi�ini g�stermek i�in lower caseye d�n��t�r�yorum
    int i, j, k;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(is_valid(i,j,size) && is_valid(i+1,j, size) && is_valid(i+2, j, size) && is_valid(i+3, j, size)){
                if(TABLE[i][j] == X && TABLE[i+1][j] == X && TABLE[i+2][j] == X && TABLE[i+3][j] == X){
                    for(k=0; k<4; k++){
                        TABLE[i+k][j] = x;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i,j+1, size) && is_valid(i, j+2, size) && is_valid(i, j+3, size)){
                if(TABLE[i][j] == X && TABLE[i][j+1] == X && TABLE[i][j+2] == X && TABLE[i][j+3] == X){
                    for(k=0; k<4; k++){
                        TABLE[i][j+k] = x;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i+1,j+1, size) && is_valid(i+2, j+2, size) && is_valid(i+3, j+3, size)){
                if(TABLE[i][j] == X && TABLE[i+1][j+1] == X && TABLE[i+2][j+2] == X && TABLE[i+3][j+3] == X){
                    for(k=0; k<4; k++){
                        TABLE[i+k][j+k] = x;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i+1,j-1, size) && is_valid(i+2, j-2, size) && is_valid(i+3, j-3, size)){
                if(TABLE[i][j] == X && TABLE[i+1][j-1] == X && TABLE[i+2][j-2] == X && TABLE[i+3][j-3] == X){
                    for(k=0; k<4; k++){
                        TABLE[i+k][j-k] = x;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i+1,j, size) && is_valid(i+2, j, size) && is_valid(i+3, j, size)){
                if(TABLE[i][j] == O && TABLE[i+1][j] == O && TABLE[i+2][j] == O && TABLE[i+3][j] == O){
                    for(k=0; k<4; k++){
                        TABLE[i+k][j] = o;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i,j+1, size) && is_valid(i, j+2, size) && is_valid(i, j+3, size)){
                if(TABLE[i][j] == O && TABLE[i][j+1] == O && TABLE[i][j+2] == O && TABLE[i][j+3] == O){
                    for(k=0; k<4; k++){
                        TABLE[i][j+k] = o;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i+1,j+1, size) && is_valid(i+2, j+2, size) && is_valid(i+3, j+3, size)){
                if(TABLE[i][j] == O && TABLE[i+1][j+1] == O && TABLE[i+2][j+2] == O && TABLE[i+3][j+3] == O){
                    for(k=0; k<4; k++){
                        TABLE[i+k][j+k] = o;
                    }
                    return 1;
                }
            }
            if(is_valid(i,j,size) && is_valid(i+1,j-1, size) && is_valid(i+2, j-2, size) && is_valid(i+3, j-3, size)){
                if(TABLE[i][j] == O && TABLE[i+1][j-1] == O && TABLE[i+2][j-2] == O && TABLE[i+3][j-3] == O){
                    for(k=0; k<4; k++){
                        TABLE[i+k][j-k] = o;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

int is_game_draw(grid TABLE[][maxBoardSize], int size){         // Oyundaki t�m karelere bak�yorum.E�er empty bulamaz ise oyun berabere bitmi� demektir.
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(TABLE[i][j]==EMPTY){
                return 1;
            }
        }
    }
    return 0;
}

void computer_move(grid TABLE[][maxBoardSize], int size){           // Bilgisayar hareketlerini random yapmak yerine o anki duruma g�re �ncelikler verdim.Hepsini kontrol ediyor ve yapabilece�i en iyi hamleyi yap�yor
  int i ,j, temp_i=-1, temp_j=-1, best_move=0;
  for(j=0; j<size; j++){
     for(i=0; i<size; i++){
        if(TABLE[i][j]==EMPTY){
           if(computer_4_in_a_row(TABLE, i, j, size)>best_move){
                best_move = computer_4_in_a_row(TABLE, i, j, size);
                temp_i=i;
                temp_j=j;
           }
           if(player_4_in_a_row(TABLE, i, j, size)>best_move){
                best_move = player_4_in_a_row(TABLE, i, j, size);
                temp_i=i;
                temp_j=j;
           }
           if(computer_3_in_a_row(TABLE, i, j, size)>best_move){
                best_move = computer_3_in_a_row(TABLE, i, j, size);
                temp_i=i;
                temp_j=j;
           }
           if(player_3_in_a_row(TABLE, i, j, size)>best_move){
                best_move = player_3_in_a_row(TABLE, i, j, size);
                temp_i=i;
                temp_j=j;
           }
           if(computer_2_in_a_row(TABLE, i, j, size)>best_move){
                best_move = computer_2_in_a_row(TABLE, i, j, size);
                temp_i=i;
                temp_j=j;
           }
           if(player_2_in_a_row(TABLE, i, j, size)>best_move){
                player_2_in_a_row(TABLE, i, j, size);
                temp_i=i;
                temp_j=j;
           }
            break;
        }
    }
  }

  if(best_move>0){              // Yukardaki ko�ullardan bulaca�� en iyi hamleyi ger�ekle�tiren koordinatlara hamleyi yap�yor
    TABLE[temp_i][temp_j]=O;
  }
  else if(TABLE[0][size/2]==EMPTY){     // E�er yukardaki ko�ullara uygun bir hamle bulamad�ysa (Sadece Ba�lang�� hamlesi i�in ge�erli) avantajl� konuma ge�ebilmek i�in oyun tahtas�n�n ortas�na ilk hamleyi yap�yor
    TABLE[0][size/2]=O;
  }
  else if(TABLE[0][size/2]==X){
    TABLE[0][size/2-1]=O;
  }
}

int computer_4_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){        // Kendini 4'e e�lemek yapabilece�i en iyi hamle oldugu i�in return de�eri en y�ksek (6) olan fonksiyon. Yapabilece�i t�m hamleleri kontrol ediyor ve kendini 4'leyebiliyor ise 6 return ediyor.
    if(is_valid(i,j+1,size) && is_valid(i,j+2,size) && is_valid(i, j+3, size)){
        if(TABLE[i][j]==O && TABLE[i][j]==O && TABLE[i][j]==O){
            return 6;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j-2,size) && is_valid(i, j-3, size)){
        if(TABLE[i][j-1]==O && TABLE[i][j-2]==O && TABLE[i][j-3]==O){
            return 6;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j+1,size) && is_valid(i, j+2, size)){
        if(TABLE[i][j-1]==O && TABLE[i][j+1]==O && TABLE[i][j+2]==O){
            return 6;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j-2,size) && is_valid(i, j+1, size)){
        if(TABLE[i][j-1]==O && TABLE[i][j-2]==O && TABLE[i][j+1]==O){
            return 6;
        }
    }
    if(is_valid(i-1,j,size) && is_valid(i-2,j,size) && is_valid(i-3, j, size)){
        if(TABLE[i-1][j]==O && TABLE[i-2][j]==O && TABLE[i-3][j]==O){
            return 6;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i+2,j+2,size) && is_valid(i+3, j+3, size)){
        if(TABLE[i+1][j+1]==O && TABLE[i+2][j+2]==O && TABLE[i+3][j+3]==O){
            return 6;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i+2,j+2,size) && is_valid(i-1, j-1, size)){
        if(TABLE[i+1][j+1]==O && TABLE[i+2][j+2]==O && TABLE[i-1][j-1]==O){
            return 6;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i-1,j-1,size) && is_valid(i-2, j-2, size)){
        if(TABLE[i+1][j+1]==O && TABLE[i-1][j-1]==O && TABLE[i-2][j-2]==O){
            return 6;
        }
    }
    if(is_valid(i-1,j-1,size) && is_valid(i-2,j-2,size) && is_valid(i-3, j-3, size)){
        if(TABLE[i-1][j-1]==O && TABLE[i-2][j-2]==O && TABLE[i-3][j-3]==O){
            return 6;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i+2,j-2,size) && is_valid(i+3, j-3, size)){
        if(TABLE[i+1][j-1]==O && TABLE[i+2][j-2]==O && TABLE[i+3][j-3]==O){
            return 6;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i+2,j-2,size) && is_valid(i-1, j+1, size)){
        if(TABLE[i+1][j-1]==O && TABLE[i+2][j-2]==O && TABLE[i-1][j+1]==O){
            return 6;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i-1,j+1,size) && is_valid(i-2, j+2, size)){
        if(TABLE[i+1][j-1]==O && TABLE[i-1][j+1]==O && TABLE[i-2][j+2]==O){
            return 6;
        }
    }
    if(is_valid(i-1,j+1,size) && is_valid(i-2,j+2,size) && is_valid(i-3, j+3, size)){
        if(TABLE[i-1][j+1]==O && TABLE[i-2][j+2]==O && TABLE[i-3][j+3]==O){
            return 6;
        }
    }
    return 0;
}


int player_4_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){  // Rakibin 4'l�s�n� bozmak yapabilece�i en iyi 2. hamle oldugu i�in return de�eri 5 olan fonksiyon. Yapabilece�i t�m hamleleri kontrol ediyor ve rakibin 4'l�s�n� bozabiliyor ise 5 return ediyor.
    if(is_valid(i,j+1,size) && is_valid(i,j+2,size) && is_valid(i, j+3, size)){
        if(TABLE[i][j+1]==X && TABLE[i][j+2]==X && TABLE[i][j+3]==X){
            return 5;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j-2,size) && is_valid(i, j-3, size)){
        if(TABLE[i][j-1]==X && TABLE[i][j-2]==X && TABLE[i][j-3]==X){
            return 5;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j+1,size) && is_valid(i, j+2, size)){
        if(TABLE[i][j-1]==X && TABLE[i][j+1]==X && TABLE[i][j+2]==X){
            return 5;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j-2,size) && is_valid(i, j+1, size)){
        if(TABLE[i][j-1]==X && TABLE[i][j-2]==X && TABLE[i][j+1]==X){
            return 5;
        }
    }
    if(is_valid(i-1,j,size) && is_valid(i-2,j,size) && is_valid(i-3, j, size)){
        if(TABLE[i-1][j]==X && TABLE[i-2][j]==X && TABLE[i-3][j]==X){
            return 5;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i+2,j+2,size) && is_valid(i+3, j+3, size)){
        if(TABLE[i+1][j+1]==X && TABLE[i+2][j+2]==X && TABLE[i+3][j+3]==X){
            return 5;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i+2,j+2,size) && is_valid(i-1, j-1, size)){
        if(TABLE[i+1][j+1]==X && TABLE[i+2][j+2]==X && TABLE[i-1][j-1]==X){
            return 5;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i-1,j-1,size) && is_valid(i-2, j-2, size)){
        if(TABLE[i+1][j+1]==X && TABLE[i-1][j-1]==X && TABLE[i-2][j-2]==X){
            return 5;
        }
    }
    if(is_valid(i-1,j-1,size) && is_valid(i-2,j-2,size) && is_valid(i-3, j-3, size)){
        if(TABLE[i-1][j-1]==X && TABLE[i-2][j-2]==X && TABLE[i-3][j-3]==X){
            return 5;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i+2,j-2,size) && is_valid(i+3, j-3, size)){
        if(TABLE[i+1][j-1]==X && TABLE[i+2][j-2]==X && TABLE[i+3][j-3]==X){
            return 5;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i+2,j-2,size) && is_valid(i-1, j+1, size)){
        if(TABLE[i+1][j-1]==X && TABLE[i+2][j-2]==X && TABLE[i-1][j+1]==X){
            return 5;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i-1,j+1,size) && is_valid(i-2, j+2, size)){
        if(TABLE[i+1][j-1]==X && TABLE[i-1][j+1]==X && TABLE[i-2][j+2]==X){
            return 5;
        }
    }
    if(is_valid(i-1,j+1,size) && is_valid(i-2,j+2,size) && is_valid(i-3, j+3, size)){
        if(TABLE[i-1][j+1]==X && TABLE[i-2][j+2]==X && TABLE[i-3][j+3]==X){
            return 5;
        }
    }
    return 0;
}

int computer_3_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){        // Kendini 3'lemek yapabilece�i en iyi 3. hamle oldugu i�in return de�eri 4 olan fonksiyon. Yapabilece�i t�m hamleleri kontrol ediyor ve kendini 3'leyebiliyor ise 4 return ediyor.
    if(is_valid(i,j+1,size) && is_valid(i,j+2,size)){
        if(TABLE[i][j+1]==O && TABLE[i][j+2]==O){
            return 4;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j-2,size)){
        if(TABLE[i][j-1]==O && TABLE[i][j-2]==O){
            return 4;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j+1,size)){
        if(TABLE[i][j-1]==O && TABLE[i][j+1]==O){
            return 4;
        }
    }
    if(is_valid(i-1,j,size) && is_valid(i-2,j,size)){
        if(TABLE[i-1][j]==O && TABLE[i-2][j]==O){
            return 4;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i+2,j+2,size)){
        if(TABLE[i+1][j+1]==O && TABLE[i+2][j+2]==O){
            return 4;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i-1, j-1, size)){
        if(TABLE[i+1][j+1]==O && TABLE[i-1][j-1]==O){
            return 4;
        }
    }
    if(is_valid(i-1,j-1,size) && is_valid(i-2, j-2, size)){
        if(TABLE[i-1][j-1]==O && TABLE[i-2][j-2]==O){
            return 4;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i+2,j-2,size)){
        if(TABLE[i+1][j-1]==O && TABLE[i+2][j-2]==O){
            return 4;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i-1, j+1, size)){
        if(TABLE[i+1][j-1]==O && TABLE[i-1][j+1]==O){
            return 4;
        }
    }
    if(is_valid(i-1,j+1,size) && is_valid(i-2, j+2, size)){
        if(TABLE[i-1][j+1]==O && TABLE[i-2][j+2]==O){
            return 4;
        }
    }
    return 0;
}

int player_3_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){  // Rakibin 3'l�s�n� bozmak yapabilece�i en iyi 4. hamle oldugu i�in return de�eri 3 olan fonksiyon. Yapabilece�i t�m hamleleri kontrol ediyor ve rakibin 3'l�s� bozabiliyor ise 3 return ediyor.
    if(is_valid(i,j+1,size) && is_valid(i,j+2,size)){
        if(TABLE[i][j+1]==X && TABLE[i][j+2]==X){
            return 3;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j-2,size)){
        if(TABLE[i][j-1]==X && TABLE[i][j-2]==X){
            return 3;
        }
    }
    if(is_valid(i,j-1,size) && is_valid(i,j+1,size)){
        if(TABLE[i][j-1]==X && TABLE[i][j+1]==X){
            return 3;
        }
    }
    if(is_valid(i-1,j,size) && is_valid(i-2,j,size)){
        if(TABLE[i-1][j]==X && TABLE[i-2][j]==X){
            return 3;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i+2,j+2,size)){
        if(TABLE[i+1][j+1]==X && TABLE[i+2][j+2]==X){
            return 3;
        }
    }
    if(is_valid(i+1,j+1,size) && is_valid(i-1, j-1, size)){
        if(TABLE[i+1][j+1]==X && TABLE[i-1][j-1]==X){
            return 3;
        }
    }
    if(is_valid(i-1,j-1,size) && is_valid(i-2, j-2, size)){
        if(TABLE[i-1][j-1]==X && TABLE[i-2][j-2]==X){
            return 3;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i+2,j-2,size)){
        if(TABLE[i+1][j-1]==X && TABLE[i+2][j-2]==X){
            return 3;
        }
    }
    if(is_valid(i+1,j-1,size) && is_valid(i-1, j+1, size)){
        if(TABLE[i+1][j-1]==X && TABLE[i-1][j+1]==X){
            return 3;
        }
    }
    if(is_valid(i-1,j+1,size) && is_valid(i-2, j+2, size)){
        if(TABLE[i-1][j+1]==X && TABLE[i-2][j+2]==X){
            return 3;
        }
    }
    return 0;
}

int computer_2_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){  // Kendini 2'lemek yapabilece�i en iyi 5. hamle oldugu i�in return de�eri 2 olan fonksiyon. Yapabilece�i t�m hamleleri kontrol ediyor ve kendini 2'leyebiliyor ise 2 return ediyor.
    if(is_valid(i,j+1,size)){
        if(TABLE[i][j+1]==O){
            return 2;
        }
    }
    if(is_valid(i,j-1,size)){
        if(TABLE[i][j-1]==O){
            return 2;
        }
    }
    if(is_valid(i-1,j,size)){
        if(TABLE[i-1][j]==O){
            return 2;
        }
    }
    if(is_valid(i+1,j+1,size)){
        if(TABLE[i+1][j+1]==O){
            return 2;
        }
    }
    if(is_valid(i-1, j-1, size)){
        if(TABLE[i-1][j-1]==O){
            return 2;
        }
    }
    if(is_valid(i+1,j-1,size)){
        if(TABLE[i+1][j-1]==O){
            return 2;
        }
    }
    if(is_valid(i-1,j+1,size)){
        if(TABLE[i-1][j+1]==O){
            return 2;
        }
    }
    return 0;
}

int player_2_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){      // Rakibin 2'lisini bozmak yapabilece�i en k�t� hamle oldugu i�in return de�eri 1 olan fonksiyon. Yapabilece�i t�m hamleleri kontrol ediyor ve rakibin 2'lisini bozabiliyor ise 1 return ediyor.
    if(is_valid(i,j+1,size)){
        if(TABLE[i][j+1]==X){
            return 1;
        }
    }
    if(is_valid(i,j-1,size)){
        if(TABLE[i][j-1]==X){
            return 1;
        }
    }
    if(is_valid(i-1,j,size)){
        if(TABLE[i-1][j]==X){
            return 1;
        }
    }
    if(is_valid(i+1,j+1,size)){
        if(TABLE[i+1][j+1]==X){
            return 1;
        }
    }
    if(is_valid(i-1, j-1, size)){
        if(TABLE[i-1][j-1]==X){
            return 1;
        }
    }
    if(is_valid(i+1,j-1,size)){
        if(TABLE[i+1][j-1]==X){
            return 1;
        }
    }
    if(is_valid(i-1,j+1,size)){
        if(TABLE[i-1][j+1]==X){
            return 1;
        }
    }
    return 0;
}

void save_game(grid TABLE[][maxBoardSize], string fileName, string gameMode, int size, int Turn){
    ofstream myFile;
    myFile.open(fileName.c_str());
    if (!myFile.is_open()) {
        cerr << endl << "Unable To Open File" << endl;
    }
    else{
        myFile << size << endl;
        myFile << gameMode << endl;
        myFile << Turn << endl;
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if(TABLE[i][j]==EMPTY){
                    myFile << "EMPTY" << endl;
                }
                else if(TABLE[i][j]==X){
                    myFile << "X" << endl;
                }
                else if(TABLE[i][j]==O){
                    myFile << "O" << endl;
                }
            }
        }
        myFile.close();
    }
}

void load_game(grid TABLE[][maxBoardSize], string fileName, string& gameMode, int& Turn, int& size){
    ifstream myFile;
    string line;
    myFile.open(fileName.c_str());
    if (!myFile.is_open()) {
        cerr << endl << "Unable To Open File" << endl;
    }
    else{
    myFile >> size;
    myFile >> gameMode;
    myFile >> Turn;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            myFile >> line;
            if(line=="EMPTY"){
                TABLE[i][j]=EMPTY;
            }
            else if(line=="X"){
                TABLE[i][j]=X;
            }
            else if(line=="O"){
                TABLE[i][j]=O;
            }
        }
    }
        myFile.close();
    }
}


#include <iostream>
#include <limits>    // Size istediðim zaman harf girildiðinde program sonsuz döngüye giriyodu. Bu sorunu çözmek için bu kütüphaneyi ekledim.
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
    int valid_sizes[totalSize] = {4,6,8,10,12,14,16,18,20};   // Girilebilecek size'larý array haline getirdim.
    cout << "4 IN A ROW!" << endl << endl << "Try To Build A Row Of Four Checkers (Vertically, Horizontally, Diagonally) While Keeping Your Opponent From Doing The Same." << endl; // Oyun hakkýnda bilgilendirme satýrý
    cout << endl << endl << "If You Want To Load A Game Type 'LOAD FILE.TXT'.If You Want To Start A New Game Press A Character Then Enter: ";
    grid TABLE[maxBoardSize][maxBoardSize];     // Oyun tablomun çift boyutlu arrayini tanýmladým
    cin >> askForLoad;
    if(askForLoad=="LOAD"){
        getline(cin, askForLoad);
        load_game(TABLE, askForLoad, game_mode, turn, size);
        game_loaded=1;
        if(turn==2){
            draw_table(TABLE, size);
            while(status2){      // Player1_move fonksiyonumun return deðerine bakýlarak oyun alanýnýn dolu olup olmadýðýný kontrol ediyorum. Eðer doluysa hata mesajý gösterip tekrar input alýyorum
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
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmediðini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 2 WIN!" << endl;
                status=0;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere olup olmadýgýný kontrol ediyorum
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
            if(!(cin >> size)){         // Burdaki if'i size'a harf girildiði durumdaki döngüden kurtarmak için "Stackoverflow'dan" buldugum while kodunu kendim için if'e çevirdim.
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            for(i=0; i<totalSize; i++){     // For döngüsüyle size'ýn geçerli olup olmadýgýna bakýyorm eðer geçerliyse status=0 oluyor ve while döngüsünden çýkýyor
                if(valid_sizes[i]==size){
                    size_status=0;
                }
            }
        }
        init_table(TABLE, size);
        while(game_mode_status){
            cout << endl << "Press 'C' For Playing Against Computer, Press 'P' For Playing Against Player: ";
            cin >> game_mode;       // Eðer kullanýcý p yada c tuþlamaz ise while döngüsü sayesinde tekrar sorulacak.
            if(game_mode=="P" || game_mode=="p"){
                    game_mode_status=0;
            }
            if(game_mode=="C" || game_mode=="c"){
                    game_mode_status=0;
            }
        }
    }
    if(game_mode == "P" || game_mode == "p"){       // Eðer oyuncuya karþý oynamayý seçtiysek aþaðýdaki kod bloðu çalýþacak
        while(status==1){
            draw_table(TABLE, size);
            turn = 1;
            status2=1;
            while(status2){      // Player1_move fonksiyonumun return deðerine bakýlarak oyun alanýnýn dolu olup olmadýðýný kontrol ediyorum. Eðer doluysa hata mesajý gösterip tekrar input alýyorum
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
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmediðini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 1 WIN!" << endl;
                status=0;
                break;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere bitip bitmediðini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER!  DRAW!" << endl;
                status=0;
                break;
            }
            draw_table(TABLE,size);
            turn = 2;
            status2=1;
            while(status2){      // Player1_move fonksiyonumun return deðerine bakýlarak oyun alanýnýn dolu olup olmadýðýný kontrol ediyorum. Eðer doluysa hata mesajý gösterip tekrar input alýyorum
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
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmediðini kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! PLAYER 2 WIN!" << endl;
                status=0;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere olup olmadýgýný kontrol ediyorum
                draw_table(TABLE, size);
                cout << endl <<
                endl<< "GAME OVER!  DRAW!" << endl;
                status=0;
            }
        }
    }
    else if(game_mode=="C" || game_mode == "c"){        // Eðer bilgisayara karþý oynamak istediysek aþaðýdaki kod bloðu çalýþacak.
        while(status==1){
            draw_table(TABLE, size);
            status2=1;
            turn = 1;
            while(status2){      // Player1_move fonksiyonumun return deðerine bakýlarak oyun alanýnýn dolu olup olmadýðýný kontrol ediyorum. Eðer doluysa hata mesajý gösterip tekrar input alýyorum
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
            computer_move(TABLE, size);         // Bilgisayar hamlesini yapýyor
            if(is_game_finished(TABLE, size)){      // Oyunun bitip bitmediði kontrol ediliyor
                draw_table(TABLE, size);
                cout << endl << endl << "GAME OVER! COMPUTER WIN!" << endl;
                status=0;
            }
            else if(!is_game_draw(TABLE, size)){        // Oyunun berabere bitip bitmediði kontrol ediliyor
                draw_table(TABLE, size);
                cout << endl << endl<< "GAME OVER!  DRAW!" << endl;
                status=0;
            }
        }
    }
    return 0;
}

void init_table(grid TABLE[][maxBoardSize], int size){      // Oyun boardýný empty yapýyorum
    int i, j;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            TABLE[i][j] = EMPTY;
       }
    }
}

void draw_table(grid TABLE[][maxBoardSize], int size){      // Oyun boardýný ekrana bastýrýyorum
    int i, j, k;
    char characters = 'A';
    cout << endl << endl;
    for(k=0; k<size; k++){          // Bu for döngüsüyle boardýn üstündeki sütun harflerini bastýrýyorum
        cout << "   " << characters++ << "  ";
    }
    for(i=size-1; i>-1; i--){       // Bu for döngüsüyle boardýmdaki harfleri noktalarý ve etrafýndaki çerçeveyi çizdiriyorum
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
    for(k=0; k<size; k++){      // Bu döngüyle oyun boardýmýn en altýndaki boþluðu kapatýyorum
        cout << " -----";
    }
}

int player1_move(grid TABLE[][maxBoardSize], string gameMode, int turn, const int& size){         // Bu fonksiyonla 1. oyuncunun hareketini alýyorum
    string column, line;
    string columns[maxColumns] = {"A", "B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};
    int i, status=1, temp=-1;
    cout << endl << "PLAYER 1 - Select a column; ";
    while(status==1){           // Bu döngümün içinde kullancýdan harf alýyorum.Daha sonra aldýðým harfi 'A' veya 'a' harfinden çýkararak ulaþtýðým sonuç atacagým sütunun integer deðerine eþit oluyor.
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
        if(temp>size-1 || temp<0){          // Eðer kalan sonuç size'dan büyükse yada sizedan küçükse hata mesajýný ekrana bastýrýyorum
            cerr << "Please Enter A Valid Location: ";
        }
        else{
            status=0;
        }
    }
    for(i=0; i<size; i++){      // Kullanýcýdan aldýðým sütundaki boþ olan en alt satýra yerleþtiriyorum
        if(TABLE[i][temp]==EMPTY){
            TABLE[i][temp] = X;
            return 1;
        }
    }
    return 0;
}

int player2_move(grid TABLE[][maxBoardSize], string gameMode, int turn, const int& size){         // Bu fonksiyonla 1. oyuncunun hareketini alýyorum
    string column, line;
    string columns[maxColumns] = {"A", "B", "C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};
    int i, status=1, temp=-1;
    cout << endl << "PLAYER 2 - Select a column; ";
    while(status==1){           // Bu döngümün içinde kullancýdan harf alýyorum.Daha sonra aldýðým harfi 'A' veya 'a' harfinden çýkararak ulaþtýðým sonuç atacagým sütunun integer deðerine eþit oluyor.
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
        if(temp>size-1 || temp<0){          // Eðer kalan sonuç size'dan büyükse yada sizedan küçükse hata mesajýný ekrana bastýrýyorum
            cerr << "Please Enter A Valid Location: ";
        }
        else{
            status=0;
        }
    }
    for(i=0; i<size; i++){      // Kullanýcýdan aldýðým sütundaki boþ olan en alt satýra yerleþtiriyorum
        if(TABLE[i][temp]==EMPTY){
            TABLE[i][temp] = O;
            return 1;
        }
    }
    return 0;
}

int is_valid(int i, int j,int size){        // Yolladýðým i ve j parametrelerinin boardda geçerli bir yer olup olmadýgýný kontrol ediyorum
    if(i<0 || i>size || j<0 || j>size){
        return 0;
    }
    return 1;
}

int is_game_finished(grid TABLE[][maxBoardSize], int size){         // Oyunun yatay, dikey yada çapraz olarak sonlanýp sonlanmadýðýný kontrol ediyorum. Eðer oyun sonlanmýþ ise hangilerinin bitirdiðini göstermek için lower caseye dönüþtürüyorum
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

int is_game_draw(grid TABLE[][maxBoardSize], int size){         // Oyundaki tüm karelere bakýyorum.Eðer empty bulamaz ise oyun berabere bitmiþ demektir.
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

void computer_move(grid TABLE[][maxBoardSize], int size){           // Bilgisayar hareketlerini random yapmak yerine o anki duruma göre öncelikler verdim.Hepsini kontrol ediyor ve yapabileceði en iyi hamleyi yapýyor
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

  if(best_move>0){              // Yukardaki koþullardan bulacaðý en iyi hamleyi gerçekleþtiren koordinatlara hamleyi yapýyor
    TABLE[temp_i][temp_j]=O;
  }
  else if(TABLE[0][size/2]==EMPTY){     // Eðer yukardaki koþullara uygun bir hamle bulamadýysa (Sadece Baþlangýç hamlesi için geçerli) avantajlý konuma geçebilmek için oyun tahtasýnýn ortasýna ilk hamleyi yapýyor
    TABLE[0][size/2]=O;
  }
  else if(TABLE[0][size/2]==X){
    TABLE[0][size/2-1]=O;
  }
}

int computer_4_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){        // Kendini 4'e eþlemek yapabileceði en iyi hamle oldugu için return deðeri en yüksek (6) olan fonksiyon. Yapabileceði tüm hamleleri kontrol ediyor ve kendini 4'leyebiliyor ise 6 return ediyor.
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


int player_4_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){  // Rakibin 4'lüsünü bozmak yapabileceði en iyi 2. hamle oldugu için return deðeri 5 olan fonksiyon. Yapabileceði tüm hamleleri kontrol ediyor ve rakibin 4'lüsünü bozabiliyor ise 5 return ediyor.
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

int computer_3_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){        // Kendini 3'lemek yapabileceði en iyi 3. hamle oldugu için return deðeri 4 olan fonksiyon. Yapabileceði tüm hamleleri kontrol ediyor ve kendini 3'leyebiliyor ise 4 return ediyor.
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

int player_3_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){  // Rakibin 3'lüsünü bozmak yapabileceði en iyi 4. hamle oldugu için return deðeri 3 olan fonksiyon. Yapabileceði tüm hamleleri kontrol ediyor ve rakibin 3'lüsü bozabiliyor ise 3 return ediyor.
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

int computer_2_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){  // Kendini 2'lemek yapabileceði en iyi 5. hamle oldugu için return deðeri 2 olan fonksiyon. Yapabileceði tüm hamleleri kontrol ediyor ve kendini 2'leyebiliyor ise 2 return ediyor.
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

int player_2_in_a_row(grid TABLE[][maxBoardSize], int i, int j, int size){      // Rakibin 2'lisini bozmak yapabileceði en kötü hamle oldugu için return deðeri 1 olan fonksiyon. Yapabileceði tüm hamleleri kontrol ediyor ve rakibin 2'lisini bozabiliyor ise 1 return ediyor.
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


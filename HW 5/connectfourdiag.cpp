#include "connectfourdiag.h"


namespace CCKGTU{

    ConnectFourDiag::ConnectFourDiag(){
        gameType = "P";
        turn = 1;
        height=6;
        width=6;
        gameBoard = new Cell*[height];      // gameBoard icin dinamik olarak yer aliyorum.
        for(int i=0; i<height; i++){
            gameBoard[i] = new Cell[width];
        }
    }

    int ConnectFourDiag::isGameFinished(){      // Oyunun dikey veya yatay bitip bitmedigini kontrol eden fonksiyon
      	int i, j, k;
        for(i=0; i<height; i++){
            for(j=0; j<width; j++){
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
       
    int ConnectFourDiag::play(){        // Gerekli olan kontrolleri yapip en uygun hamleyi buluyor.
      int i ,j, tempX=-1, tempY=-1, bestMove=0;
      for(j=0; j<height; j++){
         for(i=0; i<width; i++){
            if(gameBoard[i][j].getType()==EMPTY){
               if(computer4InARowDiag(i, j)>bestMove){
                    bestMove = computer4InARowDiag(i, j);
                    tempX=i;
                    tempY=j;
               }
               if(player4InARowDiag(i, j)>bestMove){
                    bestMove = player4InARowDiag(i, j);
                    tempX=i;
                    tempY=j;
               }
               if(computer3InARowDiag(i, j)>bestMove){
                    bestMove = computer3InARowDiag(i, j);
                    tempX=i;
                    tempY=j;
               }
               if(player3InARowDiag(i, j)>bestMove){
                    bestMove = player3InARowDiag(i, j);
                    tempX=i;
                    tempY=j;
               }
               if(computer2InARowDiag(i, j)>bestMove){
                    bestMove = computer2InARowDiag(i, j);
                    tempX=i;
                    tempY=j;
               }
               if(player2InARowDiag(i, j)>bestMove){
                    player2InARowDiag(i, j);
                    tempX=i;
                    tempY=j;
               }
                break;
            }
        }
      }

        char col = 'A';

        if(bestMove>0){     // Yukarda bulunan en uygun hamleyi oynayan if
            col += tempY;
            cout << endl << endl << "Computer Move: " << col;
            gameBoard[tempX][tempY].setType(O);
            return tempY;
        }
        else if(gameBoard[0][height/2].getType()==EMPTY){       // Eger yapilacak hamle bulamadiysa boardin ortasına hamleyi yapiyor
            col += width/2;
            cout << endl << endl << "Computer Move: " << col;
            gameBoard[0][height/2].setType(O);
            return height/2;
        }
        else if(gameBoard[0][height/2].getType()==X){       // Eger boardin ortasi doluysa bir yanina hamleyi yapiyor
            col += 'A' + width/2;
            cout << endl << endl << "Computer Move: " << col;
            gameBoard[0][height/2-1].setType(O);
            return height/2-1;
        }
        else{               // Boardda buldugu ilk bos yere hamleyi yapiyor
        	for(i=0; i<height; i++){
        		for(j=0; j<width; j++){
        			if(gameBoard[i][j].getType()==EMPTY){
        				gameBoard[i][j].setType(O);
                        return j;
        			}
        		}
        	}
        }
        return 0;
    }


    int ConnectFourDiag::gameInput(){
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
            if(op=="SAVE"){        // Eger save komutu girildiyse getline yaparak dosya ismini aliyorum ve save fonksiyonumu cagiriyorum
                getline(cin, line);
                saveGame(line);
            }
            else if(op=="LOAD"){           // Eger load komutu girildiyse getline yaparak dosya ismini aliyorum ve load fonksiyonumu cagiriyorum
                if(turn==1){                // Turn sırasına göre işlem yaparak load edilen dosyadaki sirayi kaybetmiyorum
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
}
#include "connectfourplus.h"

namespace CCKGTU{

	ConnectFourPlus::ConnectFourPlus(){
		gameType = "P";
	    turn = 1;
	    height=6;
	    width=6;
	    gameBoard = new Cell*[height];
	    for(int i=0; i<height; i++){
	        gameBoard[i] = new Cell[width];
	    }
	}

	int ConnectFourPlus::isGameFinished(){		// Oyunun dikey veya yatay bitip bitmedigini kontrol eden fonksiyon
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
			    if(isValid(i,j) && isValid(i+1,j) && isValid(i+2, j) && isValid(i+3, j)){
			        if(gameBoard[i][j].getType() == O && gameBoard[i+1][j].getType() == O &&gameBoard[i+2][j].getType() == O && gameBoard[i+3][j].getType() == O){
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
		    }
		}
		return 0;
	}
	   
	int ConnectFourPlus::play(){		// Gerekli olan kontrolleri yapip en uygun hamleyi buluyor.
	  int i ,j, tempX=-1, tempY=-1, bestMove=0;
	  for(j=0; j<height; j++){
	     for(i=0; i<width; i++){
	        if(gameBoard[i][j].getType()==EMPTY){
	           if(computer4InARowPlus(i, j)>bestMove){
	                bestMove = computer4InARowPlus(i, j);
	                tempX=i;
	                tempY=j;
	           }
	           if(player4InARowPlus(i, j)>bestMove){
	                bestMove = player4InARowPlus(i, j);
	                tempX=i;
	                tempY=j;
	           }
	           if(computer3InARowPlus(i, j)>bestMove){
	                bestMove = computer3InARowPlus(i, j);
	                tempX=i;
	                tempY=j;
	           }
	           if(player3InARowPlus(i, j)>bestMove){
	                bestMove = player3InARowPlus(i, j);
	                tempX=i;
	                tempY=j;
	           }
	           if(computer2InARowPlus(i, j)>bestMove){
	                bestMove = computer2InARowPlus(i, j);
	                tempX=i;
	                tempY=j;
	           }
	           if(player2InARowPlus(i, j)>bestMove){
	                player2InARowPlus(i, j);
	                tempX=i;
	                tempY=j;
	           }
	            break;
	        }
	    }
	  }

	    char col = 'A';

	    if(bestMove>0){		// Yukarda bulunan en uygun hamleyi oynayan if
	        col += tempY;
	        cout << endl << endl << "Computer Move: " << col;
	        gameBoard[tempX][tempY].setType(O);
	        return tempY;
	    }
	    else if(gameBoard[0][height/2].getType()==EMPTY){		// Eger yapilacak hamle bulamadiysa boardin ortasına hamleyi yapiyor
	        col += width/2;
	        cout << endl << endl << "Computer Move: " << col;
	        gameBoard[0][height/2].setType(O);
	        return height/2;
	    }
	    else if(gameBoard[0][height/2].getType()==X){		// Eger boardin ortasi doluysa bir yanina hamleyi yapiyor
	        col += 'A' + width/2;
	        cout << endl << endl << "Computer Move: " << col;
	        gameBoard[0][height/2-1].setType(O);
	        return height/2-1;
	    }
	    else{				// Boardda buldugu ilk bos yere hamleyi yapiyor
	    	for(i=0; i<width; i++){
	    		for(j=0; j<height; j++){
	    			if(gameBoard[i][j].getType()==EMPTY){
	    				gameBoard[i][j].setType(O);
	    				return j;
	    			}
	    		}
	    	}
	    }
	    return 0;
	}

	int ConnectFourPlus::play(int x){			// Kullanicidan aldigim columna hamleyi yapiyor
	    if(turn==-1){
	        return -1;
	    }
	    for(int i=0; i<height; i++){
	        if(gameBoard[i][x].getType()==EMPTY){
	            if(turn==1){		// Player 1 ise
	                gameBoard[i][x].setType(X);
	                return 1;
	                break;
	            }
	            else if(turn==2){		// Player 2 ise
	                gameBoard[i][x].setType(O);
	                return 1;
	                break;
	            }
	        }
	    }
	    return 0;
	}
}
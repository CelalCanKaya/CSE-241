#include "connectfourdiag.h"
#include "connectfourplusundo.h"

using namespace CCKGTU;

int main(){
	string gameMode;
	int status=1;
	while(status){
		cout << "Please Enter Game Mode (P,D,U) : ";
		cin >> gameMode;		// Oyun modunu input olarak aliyorum ve ona uygun olan oyun modunu aciyorum.
		if(gameMode=="P" || gameMode=="p"){
			status=0;
			ConnectFourPlus obj;
			obj.playGame();
		}
		else if(gameMode=="D" || gameMode=="d"){
			status=0;
			ConnectFourDiag obj;
			obj.playGame();
		}
		else if(gameMode=="U" || gameMode=="u"){
			status=0;
			ConnectFourPlusUndo obj;
			obj.playGame();
		}
	}
	return 1;
}
#include <fstream>
#include "connectfourplusundo.h"

namespace CCKGTU{

	ConnectFourPlusUndo::ConnectFourPlusUndo(){
	    gameType = "P";
	    turn = 1;
	    height=6;
	    width=6;
	    gameBoard = new Cell*[height];      // gameBoard icin dinamik olarak yer aliyorum.
	    for(int i=0; i<height; i++){
	        gameBoard[i] = new Cell[width];
	    }
	}

	void ConnectFourPlusUndo::playGame(){
	    sizeInput();
	    typeInput();
	    resizeBoard();
	    initBoard();
	    printBoard();
	    moves = new char[width*height];
	    for(int i=0; i<width*height; i++){
	    	moves[i] = '-';
	    }
	    int status = 1, status1 = 1, status2 = 1;
	    while(status==1){
	        status1 = 1;
	        while(status1==1){
	                turn = 1;
	                int m = gameInput(moves);
	                status1 = play(m);		    // GameInputun return degerini play fonksiyonuna parametre olarak gonderdim (m)
	                if(status1==0){       // play fonksiyonunun return degeri 0 ise sutun dolmus olacagından hata mesajı verdim
	                    cout << endl << "There are no spaces in this column!" << endl ;
	                    status1=1;
	                }
	                else if(status1==-1){
	                    status1=0;
	                }
	                else{
	                	for(int i=0; i<height*width; i++){
	                		if(moves[i]=='-'){
	                			moves[i] = m + 'A';
	                			break;
	                		}
	                	}
	                    status1=0;
	                }
	        }
	        if(isGameFinished()){           // Eger oyun yukardaki hamleden sonra bittiyse player 1 kazancagı icin bilgi mesajını bastırıp donguyu sonlandirdim
	            printBoard();
	            cout << endl << endl << "GAME OVER! PLAYER 1 WIN!" << endl;
	            status=0;
	            break;
	        }
	        if(!isGameDraw()){	      // Eger board yukardaki hamleden sonra dolduysa oyun berabere biteceginden bilgi mesajını bastırıp donguyu sonlandirdim.
	            printBoard();
	            cout << endl << endl << "GAME OVER!  DRAW!" << endl;
	            status=0;
	            break;
	        }
	        printBoard();
	        if(gameType=="P"){     // Eger pvp modunda isek player 2 hamlesini gerceklestirecek
	                status2 = 1;
	                while(status2==1){
	                    turn = 2;
	               		int m = gameInput(moves);
	                    status2 = play(m);
	                    if(status2==0){
	                        cout << endl << "There are no spaces in this column!" << endl ;
	                        status2=1;
	                    }
	                    else if(status2==-1){
	                        status2=0;
	                    }
	                    else{
		                	for(int i=0; i<height*width; i++){		// moves arrayimde boş olan ilk indexe yaptigim hamleyi attim
		                		if(moves[i]=='-'){
		                			moves[i] = m + 'A';
		          	          		break;
		                		}
		                	}
		                    status2=0;
		                    }
	                }
	            }
	            if(gameType=="C"){      // Eger pvc modunda isek computer hamlesini gerceklestirecek
	                int m = play();
		              	for(int i=0; i<height*width; i++){
		                	if(moves[i]=='-'){
		                		moves[i] = m + 'A';
		          	          	break;
		                }
		            }
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
	            else if(!isGameDraw()){        // Eger board yukardaki hamleden sonra dolduysa oyun berabere biteceginden bilgi mesajını bastırıp donguyu sonlandirdim.
	                printBoard();
	                cout << endl << endl << "GAME OVER!  DRAW!" << endl;
	                status=0;
	                break;
	            }
	            printBoard();
	    }
	    delete [] moves;	
	}

	int ConnectFourPlusUndo::gameInput(char* move){			
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
	        if(cin.eof()){         // Eger dosyanin sonuna geldiysek program sonlaniyor
	            exit(0);
	        }
	        if(op=="SAVE"){          // Eger save komutu girildiyse getline yaparak dosya ismini aliyorum ve save fonksiyonumu cagiriyorum
	            getline(cin, line);
	            saveGame(line);
	        }
	        else if(op=="LOAD"){        // Eger load komutu girildiyse getline yaparak dosya ismini aliyorum ve load fonksiyonumu cagiriyorum
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
	        else if(op=="UNDO"){	// Eger UNDO Komutunu girdiyse undo fonksiyonunu cagırıp undo yapıyorum
	        	if(moves[0]=='-'){		// Eger ilk index bossa array bos olacagından hata mesajı bastırıyorum
	        		cout << "You Can't Undo!";
	        	}
	        	undo(move);
	        	printBoard();
	            if(gameType=="C"){
	                int m = play();
		              	for(int i=0; i<height*width; i++){
		                	if(moves[i]=='-'){
		                		moves[i] = m + 'A';
		          	          	break;
		                }
		            }
		           	printBoard();
		        }
	        }
	        else{ 
	            if(op[1]=='\0'){      // Eger 2. karakter NULL ise kullanici gecerli bir column girmis olacagi icin column'a op[0]'i atiyorum
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

	void ConnectFourPlusUndo::undo(char* move)const{
		for(int i=height*width; i>-1; i--){
			if(move[i]>='A' && move[i]<='Z'){	// Eger index 'A' ile 'Z' arasındaysa
				for(int j=height-1; j>-1; j--){
					if(gameBoard[j][static_cast<int>(move[i])-'A'].getType()==X || gameBoard[j][static_cast<int>(move[i])-'A'].getType()==O){
						gameBoard[j][static_cast<int>(move[i])-'A'].setType(EMPTY);	// Indexi empty yap
						move[i]='-';
						return;
					}
				}
			}
		}
	}



	void ConnectFourPlusUndo::saveGame(const string& filename)const{
	    ofstream myFile;
	    myFile.open(filename);
	    if (!myFile.is_open()) {
	        cerr << endl << "Unable To Open File" << endl;
	    }
	    else{      // Private data memberlarimi dosyaya yazdiriyorum
	        myFile << width << endl;
	        myFile << height << endl;
	        myFile << gameType << endl;
	        myFile << turn << endl;
	        for(int i=0; i<height*width; i++){       // Bu dongu icerisinde ise hamleleri tek tek dosyaya yazdiriyorum
	        	myFile << moves[i] << endl;
	        }
	        for(int i=0; i<height; i++){       // Bu dongu icerisinde ise boardi tek tek dosyaya yazdiriyorum
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

	void ConnectFourPlusUndo::loadGame(const string& filename){
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
	        for(int i=0; i<height*width; i++){	// Moves arrayimi dolduruyorum
	        	myFile >> moves[i];
	        }
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
}

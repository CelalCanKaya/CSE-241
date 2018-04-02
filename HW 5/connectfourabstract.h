#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <iostream>
#include "cell.h"

using namespace std;

namespace CCKGTU{
    class ConnectFourAbstract{
    	public:
            ConnectFourAbstract();              // Constructor
            ConnectFourAbstract(int row, int column);       // Constructor
            ConnectFourAbstract(const ConnectFourAbstract& obj); // Copy Constructor
            virtual ~ConnectFourAbstract();     // Destructor
            ConnectFourAbstract& operator==(const ConnectFourAbstract& obj); // Atama operator overloadı
            virtual void playGame();        // Oyunun oynandigi main fonksiyon tüm oyun isleyisi bu fonksiyon icerisinde oluyor
            int getWidth();         // Getter
            int getHeight();        // Getter
    	protected:
            void initBoard();           // Gameboard icini EMPTY ile dolduran fonksiyon
            void resizeBoard();         // Gameboard icin gereken yeri dinamik olarak alan fonksiyon
            void clearBoard()const;        // Gameboard icin gereken yeri delete eden fonksiyon
            void typeInput();               // Oyun tipini alip gerekli member variable a atan fonksiyon
            void sizeInput();           // Gameboardin sizeını alıp gerekli member variable a atan fonksiyon
            Cell ** gameBoard;          // Dinamik array
            int isValid(int i, int j)const;         // Verilen i ve j koordinatinin board ustunde olup olmadigini kontrol eden fonksiyon
            virtual void saveGame(const string& filename)const;         // Oyunu dosyaya kaydeden fonksiyon
            virtual void loadGame(const string& filename);          // Oyunu dosyadan yukleyen fonksiyon 
            void printBoard()const;                 // Gameboardi ekrana bastiran fonksiyon 
            int isGameDraw()const;                  // Oyunun berabere bitip bitmedigini kontrol eden fonksiyon
            int computer4InARowPlus(int i, int j)const;         // Bilgisayarin yatay yada dikey 4'lu yapip yapamadigini kontrol eden fonksiyon
            int computer4InARowDiag(int i, int j)const;         // Bilgisayarin capraz 4'lu yapip yapamadigini kontrol eden fonksiyon
            int computer3InARowPlus(int i, int j)const;         // Bilgisayarin yatay yada dikey 3'lu yapip yapamadigini kontrol eden fonksiyon
            int computer3InARowDiag(int i, int j)const;         // Bilgisayarin capraz 3'lu yapip yapamadigini kontrol eden fonksiyon
            int computer2InARowPlus(int i, int j)const;         // Bilgisayarin yatay yada dikey 2'li yapip yapamadigini kontrol eden fonksiyon
            int computer2InARowDiag(int i, int j)const;         // Bilgisayarin capraz 2'li yapip yapamadigini kontrol eden fonksiyon
            int player4InARowPlus(int i, int j)const;         // Oyuncunun yatay yada dikey 4'lu yapip yapamadigini kontrol eden fonksiyon
            int player4InARowDiag(int i, int j)const;         // Oyuncunun capraz 4'lu yapip yapamadigini kontrol eden fonksiyon
            int player3InARowPlus(int i, int j)const;         // Oyuncunun yatay yada dikey 4'lu yapip yapamadigini kontrol eden fonksiyon
            int player3InARowDiag(int i, int j)const;         // Oyuncunun capraz 3'lu yapip yapamadigini kontrol eden fonksiyon
            int player2InARowPlus(int i, int j)const;         // Oyuncunun yatay yada dikey 4'lu yapip yapamadigini kontrol eden fonksiyon
            int player2InARowDiag(int i, int j)const;         // Oyuncunun capraz 2'li yapip yapamadigini kontrol eden fonksiyon
        	int width;
            int height;
            int turn;
            string gameType;
        private:           
            virtual int isGameFinished() = 0;       // Pure virtual
            virtual int play() = 0;     // Pure virtual
            virtual int play(int x);        // Oyuncunun bir hamlesini uygulayan virtual fonksiyon
            virtual int gameInput();            // Oyuncunun girecegi hamleyi, komutu alan fonksiyon
    };
 }

#endif
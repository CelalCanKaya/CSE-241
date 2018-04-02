#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H

#include "connectfourplus.h"

namespace CCKGTU{

	class ConnectFourPlusUndo : public ConnectFourPlus{
		public:
			ConnectFourPlusUndo();
			void playGame();
		protected:
	        void saveGame(const string& filename)const;		// Save Fonk
	        void loadGame(const string& filename);		// Load fonk
			int gameInput(char* move);		// Kullanicinin girdigi komutu alan fonk
			void undo(char* move)const;		// Son hamleyi geri alan fonk
			char* moves;
			
	};
}

#endif
#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "connectfourabstract.h"

namespace CCKGTU{

	class ConnectFourPlus : public ConnectFourAbstract{		// Inherit Class
		public:
			ConnectFourPlus();		// Constructor
		protected:
			int isGameFinished();		// Oyunun dikey veya yatay olarak bitip bitmedigini kontrol eden fonksiyon
			int play();			//		Computer hamlesini yapan fonksiyon
			int play(int x);	// Kullanıcıdan alınan inputa gore oynayan fonksiyon
	};
}

#endif
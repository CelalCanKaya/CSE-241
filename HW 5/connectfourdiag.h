#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "connectfourabstract.h"

namespace CCKGTU{
	class ConnectFourDiag : public ConnectFourAbstract{
		public:
			ConnectFourDiag();
		protected:
			int gameInput();		// Kullanicidan yapilacak komutu aliyor
			int isGameFinished();		// Oyunun dikey veya yatay olarak bitip bitmedigini kontrol eden fonksiyon
			int play();			//		Computer hamlesini yapan fonksiyon
	};
}
#endif
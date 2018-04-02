#ifndef CELL_H
#define CELL_H

typedef enum {EMPTY, X, O, x, o} grid; 

namespace CCKGTU{
	class Cell{
		public:
			Cell();									// Constructor
			void setType(const grid x);				// Private datayi degistirmek icin setter
			void setColumn(char c);					// Private datayi degistirmek icin setter
			void setRow(int i);						// Private datayi degistirmek icin setter
			grid getType()const;					// Private datayi okumak icin getter
			char getColumn()const;					// Private datayi okumak icin getter
			int  getRow()const;						// Private datayi okumak icin getter
		private:
			grid type;
			char column;
			int row;
	};

}
#endif
#include <iostream>
#include "cell.h"

namespace CCKGTU{
    Cell::Cell(){
        type = EMPTY;
        row = 0;
        column = 'A';
    }
    // Setterlar
	void Cell::setType(const grid x){
  		type=x;
    }
    void Cell::setColumn(char c){
        column=static_cast<char>('A'+c);
    }
	void Cell::setRow(int i){
		row=i;
	}
    // Getterlar
    grid Cell::getType()const{
        return type;
    }
    char Cell::getColumn()const{
       	return column;
    }
    int Cell::getRow()const{
 		return row;
    }
}
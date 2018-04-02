/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw7;

import java.security.InvalidParameterException;

/**
 *
 * @author Celal Can
 * @param <T> Template
 */
public class GTUSet<T> implements GTUSetInt<T> {

    /**
     *
     */
    public class GTUIterator{       // İnner iterator classım

        /**
         * Default Constructor
         */
        public GTUIterator(){
            index = 0;
        }

        /**
         *
         * @param c Iteratorü istediğim indexe getirmemi sagliyor
         */
        public GTUIterator(int c){
            index = c;
        }

        /**
         *
         * @return Bir sonraki indexde eleman olup olmadığını kontrol ediyor
         */
        public boolean hasNext(){
            return index<elementCounter;
        }

        /**
         *
         * @return  Bir önceki indexde eleman olup olmadığını kontrol ediyor
         */
        public boolean hasPrevious(){
            if(index>0){
                return true;
            }
            else{
                return false;
            }        
        }
        T next(){
            return (T) data[index++];
        }
        T previous(){
            return (T) data[index--];
        }
        int index;
    }

    /**
     *Elemanları tuttugum array
     * 
     */
    protected T data[];

    /**
     * O an olabilecek maximum size. Size kapasiteye ulaşınca 2 katına çıkıyor
     */
    protected int capacity;

    /**
     * Array size
     */
    protected int elementCounter;

    /**
     *  Maximum olabilecek size
     */
    protected int maximum;

    /**
     *      GTUSet classımın default constructorı
     */
    public GTUSet(){
        maximum = 4096;
        capacity = 10;
        elementCounter = 0;
        data = (T[]) new Object[capacity];
    }
    
    /**
     *
     * @param other Karşılaştıracağım set
     * @return  İki setin kesişimi
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){
        GTUSetInt<T> temp = new GTUSet<>();
        for(T element : data){  // Data arrayimin üstünde dolaşan for
            if(other.count(element)==1){
                temp.insert(element);
            }
        }
        return temp;
    }

    /**
     *
     * @return Eğer size 0'a eşitse true değilse false
     */
    @Override
    public boolean empty(){
        return elementCounter == 0;
    }
    
    /**
     *
     * @return  Arrayimin sizeı return ediliyor
     */
    @Override
    public int size(){
        return elementCounter;
    }
    
    /**
     *
     * @return  Maximum olabilecek size return ediliyor
     */
    @Override
    public int max_size(){
        return maximum;
    }
 
    /**
     *
     * @param element   Silinecek eleman
     * @return  Silme işlemi başarılıysa 1 değilse 0 return ediyorum
     */
    @Override
    public int erase(T element){
        int found = 0;
        int counter; 
	for(counter=0; counter<elementCounter; counter++){    
            if(data[counter]==element){     // Eğer eleman bulunduysa found=1 yapıp foru durduruyorum
		found = 1;
                break;
            }
	}
	if(found==1){
            T[] temp;   // Temp array oluşturuyorum
            temp = (T[]) new Object[capacity];
            System.arraycopy(data, 0, temp, 0, counter);        // Data arrayimdeki sileceğim elemana olan elemanları temp arrayime atıyorum
            System.arraycopy(data, counter+1, temp, counter, elementCounter-counter-1);     // Arrayimden kalan elemanları temp arraye atıyorum
            elementCounter--;
            data = (T[]) new Object[capacity];
            System.arraycopy(temp, 0, data, 0, elementCounter); // Temp arrayimden data arrayime atıyorum
            return 1;
	}
	else{
            return 0;
	}
    }
    
    /**
     *
     * @param element Arayacağım eleman
     * @return  Iteratoru o elemanı göstericek şekilde return ediyorum
     */
    @Override
    public GTUIterator find(T element){
        int counter;
        for(counter = 0; counter < elementCounter; counter++){
            if(data[counter] == element){       // Eğer arrayimde eleman bulunduysa:
                break;
            }
        }
        return new GTUIterator(counter);
    }
    
    /**
     *  Setimi tamamen temizleyen fonksiyon
     */
    @Override
    public void clear(){        // Bütün seti temizliyorum ve kapasitemi 10'a düşürüyorum
        capacity = 10;
        elementCounter = 0;
        data = (T[]) new Object[capacity];
        begin();
    }
    
    /**
     *  Iteratorü ilk elemana getiren fonksiyon
     * @return      İlk elemanı gösteren iteratör
     */
    @Override
    public GTUIterator begin(){
        return new GTUIterator(0);
    }
    
    /**
     *
     * @return  Son elemanı gösteren iteratör
     */
    @Override
    public GTUIterator end(){
        return new GTUIterator(elementCounter);
    }
    
    /**
     *
     * @param element   Sete ekleyeceğim eleman
     */
    @Override
    public void insert(T element){
        int duplicate = 0;
	for(int i=0; i<elementCounter; i++){		// Eklemeye calistigim elemanın set icinde olup olmadigini kontrol ediyorum
            if(data[i].equals(element)){
		duplicate = 1;
            }
        }         
	if(elementCounter>=capacity){		 
            capacity=capacity*2;
            T[] temp;
            temp = (T[]) new Object[capacity]; 
            System.arraycopy(data, 0, temp, 0, elementCounter);     // Data arrayimden temp arrayine aktaran arraycopy
            data = (T[]) new Object[capacity];
            System.arraycopy(temp, 0, data, 0, elementCounter);     // Temp arrayimden data arrayime aktaran arraycopy
	}
        if(duplicate == 0 && elementCounter<=maximum){
            data[elementCounter] = element;		// Elemani setin sonuna ekleyip size'i 1 arttiriyorum ve setimi sortluyorum
            elementCounter++;
        }
	else{
            throw new InvalidParameterException("This Element Is Already In Set!");
        }
    }
    
    /**
     *
     * @param element  Sette olup olmadıgını kontrol ettigim eleman
     * @return Eger eleman varsa 1 yoksa 0 return ediyorum
     */
    @Override
    public int count(T element){
 	for(int i=0; i<elementCounter; i++){
            if(element == data[i]){
		return 1;
            }
	}
	return 0;       
    }

    /**
     *
     * @param i İndex
     * @return  Setimin i'inci elemanı return ediyorum
     */
    public T getter(int i){
        return data[i];
    }
    
    /**
     *
     * @param i Setimin i. elemanına i+1'inci elemanını atıyorum
     */
    public void setter(int i){
        data[i] = data[i+1];
    }
    
}

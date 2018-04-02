/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw7;
import hw7.GTUSet.GTUIterator;

/**
 *
 * @author Celal Can
 * @param <T>   Template
 * 
 * 
 * 
 */
public interface GTUSetInt <T> {

    /**
     *
     * @return Eğer set boşsa 1 doluysa 0 return ediyor
     */
    boolean empty();

    /**
     *
     * @return  Setimin sizeını return ediyor
     */
    int size();

    /**
     *
     * @return  Sizeımın alabileceği max kapasiteyi return ediyor
     */
    int max_size();

    /**
     *
     * @param element   Sete ekleyeceğim eleman
     */
    void insert(T element);

    /**
     *
     * @param other Kesişime bakacağım 2. set
     * @return  2 Setin kesişimini return ediyorum
     */
    GTUSetInt<T> intersection(GTUSetInt<T> other);

    /**
     *
     * @param element   Setimden sileceğim eleman
     * @return  Eğer elemanı sildiysem 1 silmediysem 0 return ediyorum
     */
    int erase(T element);

    /**
     *
     * @param element   Setimde arayacağım eleman
     * @return  Elemanın oldugu indexi iteratorle return ediyorum
     */
    GTUIterator find(T element);

    /**
     *  Setimi 0 layan fonksiyon
     */
    void clear();

    /**
     *
     * @param element   Sette olup olmadığına bakacağım eleman
     * @return  Eğer eleman bulunduysa 1 bulunmadıysa 0 return ediyorum
     */
    int count(T element);

    /**
     *
     * @return İteratorü ilk elemana döndürüyorum
     */
    GTUIterator begin();

    /**
     *
     * @return İteratorü son elemana döndürüyorum
     */
    GTUIterator end();
}

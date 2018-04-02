/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw7;

/**
 *
 * @author Celal Can
 * @param <K> Template  Pair Key elemanı
 * @param <V> Template  Pair Value elemanı
 */
public class GTUMap<K,V> extends GTUSet< javafx.util.Pair <K, V> > {
    
    /**
     *
     * @param k Key
     * @return  Keyin gösterdiği value
     */
    public V at(K k){
        int i;
	for(i = 0; i < elementCounter; i++){
		if(getter(i).getKey() == k){
                    break;
                }
        }
	return getter(i).getValue();
    }
    
    /**
     *
     * @param key Sileceğim key
     * @return  Eleman silindiyse 1 silinmediyse 0 return ediyor
     */
    @Override
    public int erase(javafx.util.Pair<K,V> key){
        int found = 0;
        int counter; 
	for(counter=0; counter<elementCounter; counter++){
            if(getter(counter).getKey()==key.getKey()){
		found = 1;
                break;
            }
	}
	if(found==1){
            for(int i = counter; i<elementCounter-1; i++){
                setter(i);
            }
            elementCounter--;
            return 1;
	}
	else{
            return 0;
	}
    }
    
    /**
     *
     * @param key   Mapte arayacağım key
     * @return      Keyi buldugum indexi iteratörle return ediyorum
     */
    @Override
    public GTUIterator find(javafx.util.Pair<K,V> key){
        int counter;
        for(counter = 0; counter < elementCounter; counter++){
            if(getter(counter).getKey()==key.getKey()){
                break;
            }
        }
        return new GTUIterator(counter);
    }    

}



/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package hw7;

import java.security.InvalidParameterException;
import javafx.util.Pair;

/**
 *
 * @author Celal Can
 */
public class HW7 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) { // Printlerle yaptığım işlemleri açıkladıgım için yorum satırıyla tekrar açıklamadım.
	GTUSet<Integer> object = new GTUSet<>();
        GTUSet<Integer>.GTUIterator iterator = object.new GTUIterator();
            
        System.out.println("Integer Set Created!\n");

        try{
        object.insert(4);
        System.out.println("4 Inserted!");
        object.insert(6);
        System.out.println("6 Inserted!");
        object.insert(8);
        System.out.println("8 Inserted!");
        object.insert(10);
        System.out.println("10 Inserted!");
        object.clear();
        System.out.println("Set Cleared!");
        object.insert(12);
        System.out.println("12 Inserted!");
        object.insert(14);
        System.out.println("14 Inserted!");
        object.insert(16);
        System.out.println("16 Inserted!");
        object.insert(18);
        System.out.println("18 Inserted!");
        object.insert(14);
        System.out.println("14 Inserted!");
        object.insert(22);
        System.out.println("22 Inserted!");
        object.insert(25);
        System.out.println("25 Inserted!");
        }
        catch(InvalidParameterException exc){
            System.out.println("EXCEPTION ----- This Element Is Already In This Set!");
        }
        System.out.printf("SET: ");
        while(iterator.hasNext()){
            System.out.print(iterator.next() + " ");
        }
        
        System.out.println("\n\n--------------------------------\n");   

	GTUSet<String> object2 = new GTUSet<>();
        GTUSet<String>.GTUIterator iterator2 = object2.new GTUIterator();
            
        System.out.println("String Set Created!\n");    
        
        try{
        object2.insert("Ankara");
        System.out.println("Ankara Inserted!");
        object2.insert("Konya");
        System.out.println("Konya Inserted!");
        object2.insert("Sivas");
        System.out.println("Sivas Inserted!");
        object2.insert("Yozgat");
        System.out.println("Yozgat Inserted!");
        object2.clear();
        System.out.println("Set Cleared!");
        object2.insert("Ankara");
        System.out.println("Ankara Inserted!");
        object2.insert("Sivas");
        System.out.println("Sivas Inserted!");
        object2.insert("Yozgat");
        System.out.println("Yozgat Inserted!");
        object2.insert("Zonguldak");
        System.out.println("Zonguldak Inserted!");
        object2.insert("Sivas");
        System.out.println("Sivas Inserted!");
        object2.insert("Yalova");
        System.out.println("Yalova Inserted!");
        object2.insert("Sakarya");
        System.out.println("Sakarya Inserted!");
        }
        catch(InvalidParameterException exc){
            System.out.println("EXCEPTION ----- This Element Is Already In This Set!");
        }
        System.out.printf("SET: ");
        while(iterator2.hasNext()){
            System.out.print(iterator2.next() + " ");
        }
        
        System.out.println("\n\n--------------------------------\n");   
         
        GTUMap<Integer, Integer> object3 = new GTUMap<>();
        GTUMap<Integer, Integer>.GTUIterator iterator3 = object3.new GTUIterator();
        
        System.out.println("Integer-Integer Map Created!\n");
        
        try{
        object3.insert(new Pair<>(3,6));
        System.out.println("Pair 3-6 Inserted!");   
        object3.clear();
        System.out.println("Map Cleared!");           
        object3.insert(new Pair<>(5,8));
        System.out.println("Pair 5-8 Inserted!");        
        object3.insert(new Pair<>(3,6));
        System.out.println("Pair 3-6 Inserted!");   
        object3.erase(new Pair<>(3,6));
        System.out.println("Pair 3-6 Erased!");        
        object3.insert(new Pair<>(10,4));
        System.out.println("Pair 10-4 Inserted!");
        object3.insert(new Pair<>(12,7));
        System.out.println("Pair 12-7 Inserted!");
        object3.insert(new Pair<>(8,8));
        System.out.println("Pair 10-4 Inserted!");
        System.out.printf("Map Size: ");
        System.out.println(object3.size());
        object3.insert(new Pair<>(10,4));
        System.out.println("Pair 10-4 Inserted!");
        }
        catch(InvalidParameterException exc){
            System.out.println("EXCEPTION ----- This Element Is Already In This Set!");
        }      
        System.out.printf("MAP: ");
        while(iterator3.hasNext()){
            System.out.print(iterator3.next() + " ");
        }
        System.out.printf("\nValue of Key 5 : ");
        System.out.print(object3.at(5));
        
        System.out.println("\n\n--------------------------------\n");
        
        GTUSet<Integer> object4 = new GTUSet<>();
        GTUSet<Integer>.GTUIterator iterator4 = object4.new GTUIterator();
            
        System.out.println("Integer Set Created!\n");

        try{
        object4.insert(2);
        System.out.println("2 Inserted!");
        object4.insert(3);
        System.out.println("3 Inserted!");
        object4.insert(4);
        System.out.println("4 Inserted!");
        object4.insert(5);
        System.out.println("5 Inserted!");
        object4.insert(12);
        System.out.println("12 Inserted!");
        object4.insert(13);
        System.out.println("13 Inserted!");
        object4.insert(14);
        System.out.println("14 Inserted!");
        }
        catch(InvalidParameterException exc){
            System.out.println("EXCEPTION ----- This Element Is Already In This Set!");
        }
        System.out.printf("SET: ");
        while(iterator4.hasNext()){
            System.out.print(iterator4.next() + " ");
        }
       
        System.out.println("\n\n--------------------------------\n");
        
        GTUMap<Integer, Integer> object5 = new GTUMap<>();
        GTUMap<Integer, Integer>.GTUIterator iterator5 = object5.new GTUIterator();
        
        System.out.println("Integer-Integer Map Created!\n");
        
        try{
        object5.insert(new Pair<>(3,6));
        System.out.println("Pair 3-6 Inserted!");   
        object5.insert(new Pair<>(5,8));
        System.out.println("Pair 5-8 Inserted!");              
        object5.insert(new Pair<>(6,4));
        System.out.println("Pair 6-4 Inserted!");
        object5.insert(new Pair<>(1,11));
        System.out.println("Pair 1-11 Inserted!");
        object5.insert(new Pair<>(8,8));
        System.out.println("Pair 8-8 Inserted!");
        }
        catch(InvalidParameterException exc){
            System.out.println("EXCEPTION ----- This Element Is Already In This Set!");
        }      
        System.out.printf("MAP: ");
        while(iterator5.hasNext()){
            System.out.print(iterator5.next() + " ");
        }
        System.out.printf("\nValue of Key 8 : ");
        System.out.print(object3.at(8));
        
        System.out.println("\n\n--------------------------------\n");
 
        GTUSet<Integer> object6;
        object6 = (GTUSet<Integer>) object4.intersection(object);
        GTUSet<Integer>.GTUIterator iterator6 = object6.new GTUIterator();
               
        System.out.printf("Intersection of 2 Set: ");
        while(iterator6.hasNext()){
            System.out.print(iterator6.next() + " ");
        }
        
    }    
}

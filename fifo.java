

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
class Replacement{
int f;
int[] runQ;
int pageF=0;
int time=0;
HashMap<Integer,Integer> map=new HashMap<>();
Replacement(int f){
this.f=f;
runQ=new int[f];
Arrays.fill(runQ,-1);
}
public void push(int m){
if(!contains(m)){
runQ[pageF%f]=m;
pageF++;
map.put(pageF,time);
System.out.println("Miss: "+m);
}else {
System.out.println("Hit: "+m);
}
time++;
System.out.println(Arrays.toString(runQ));
}
public boolean contains(int m){
for(int i=0;i< f;i++){
if(runQ[i]==m){
return true;
}
}
return false;
}
}
public class fifo {
public static void main(String[] args) {
Scanner in =new Scanner(System.in);
System.out.println("Enter string: ");
String str=in.nextLine();
int n=str.length();
int[] ref=new int[n];
for(int i=0;i<n;i++){
ref[i]=Integer.parseInt(String.valueOf(str.charAt(i)));
}
System.out.println(Arrays.toString(ref));
System.out.println("Enter number of frames");
int f= in.nextInt();
Replacement r=new Replacement(f);
for(int i=0;i<n;i++){
r.push(ref[i]);
}
System.out.println("PageFs\tTime");
for(Map.Entry<Integer,Integer> map :r.map.entrySet()){
System.out.println(map.getKey()+"\t\t"+ map.getValue());
}
}
}

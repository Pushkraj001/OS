import java.util.*;
class ReplacementLRU {
int f;
int[] runQ;
int pageF = 0;
int time = 0;
HashMap<Integer, Integer> map = new HashMap<>();
HashMap<Integer, Integer> page = new HashMap<>();
ReplacementLRU(int f) {
this.f = f;
runQ = new int[f];
Arrays.fill(runQ, -1);
}
public void push(int m) {
if (!contains(m)) {
if (pageF < f) {
runQ[pageF % f] = m;
pageF++;
page.put(pageF,time);
} else {
pageF++;
int lruIndex = 0;
int lruTime = map.get(runQ[0]);
for (int i = 1; i < f; i++) {
if (map.get(runQ[i]) < lruTime) {
lruTime = map.get(runQ[i]);
lruIndex = i;
}
}
runQ[lruIndex] = m;
page.put(pageF,time);
}
map.put(m, time);
System.out.println("Miss: " + m);
} else {
map.put(m, time);
System.out.println("Hit: " + m);
}
time++;
System.out.println(Arrays.toString(runQ));
}
public boolean contains(int m) {
for (int i = 0; i < f; i++) {
if (runQ[i] == m) {
return true;
}
}
return false;
}
}
public class lru {
public static void main(String[] args) {
Scanner in = new Scanner(System.in);
System.out.println("Enter string: ");
String str = in.nextLine();
int n = str.length();
int[] ref = new int[n];
for (int i = 0; i < n; i++) {
ref[i] = Integer.parseInt(String.valueOf(str.charAt(i)));
}
System.out.println(Arrays.toString(ref));
System.out.println("Enter number of frames");
int f = in.nextInt();
ReplacementLRU r = new ReplacementLRU(f);
for (int i = 0; i < n; i++) {
r.push(ref[i]);
}
System.out.println("PageFs\tTime");
for (Map.Entry<Integer, Integer> page : r.page.entrySet()) {
System.out.println(page.getKey() + "\t\t" + page.getValue());
}
}
}

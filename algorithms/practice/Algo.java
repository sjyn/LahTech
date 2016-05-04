import java.util.*;

public class Algo {

    public static void main(String[] args){

    }

    private static <T> void printList(List<T> any){
        for(T obj : any)
            System.out.println(any);
    }

}

class Sorts {
    public static<T> void mergeSort(List<T> list){
        if(list.size() == 1)
            return;
        List<T> newlist = new ArrayList<T>();
        for(int i = 0; i < list.size() / 2; i++){
            newlist.add(list.get(i));
        }
        mergeSort(newlist);
        List<T> nnewlist = new ArrayList<>();
        for(int j = list.size() / 2; j < list.size(); j++){
            nnewlist.add(list.get(j));
        }
        mergeSort(nnewlist);
        merge(newlist, nnewlist);
    }

    private static<T> void merge(List<T> lista, List<T> listb){
        List<T> total = new ArrayList<>();
        

    }
}

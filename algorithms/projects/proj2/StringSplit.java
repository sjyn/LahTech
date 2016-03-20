import java.util.Arrays;


public class StringSplit {

    static int[] optcuts;

    // public static int splitString(String s, ArrayList<Integer> splits){
    //     if(splits.size() == 0) {
    //         return s.length();
    //     } else {
    //         // int mid = splits.get(splits.size() / 2);
    //         int mid = splits.get(splits.size() - 1);
    //         // int mid = splits.get(0);
    //         System.out.println("Splitting " + s + " at index " + mid);
    //         ArrayList<Integer> less = new ArrayList<>();
    //         for(Integer i : splits){
    //             if(i < mid)
    //                 less.add(Math.abs(i - mid));
    //         }
    //         ArrayList<Integer> max = new ArrayList<>();
    //         for(Integer i : splits){
    //             if(i > mid)
    //                 max.add(i);
    //         }
    //         return s.length() + Math.min(
    //             splitString(s.substring(0, mid), less),
    //             splitString(s.substring(mid, s.length() - 1), max)
    //         );
    //         // return min;
    //     }
    // }

    public static int splitString(String s, int[] cuts){
        Arrays.sort(cuts);
        optcuts = new int[cuts.length];
        int cost = s.length() * cuts.length;
        for(int i = 0; i < cuts.length; i++){
            cost = Math.min(splitStringRec(cuts, s.length(), i), cost);
        }
        return cost;
    }

    public static int splitStringRec(int[] cuts, int stringlen, int init){
        if(cuts.length == 1){
            return stringlen;
        }
        int cutlen = 0;
        int cutr = 0;
        if (init > 0){
            //run as normal
            cutlen = Integer.MAX_VALUE;
            int[] cpy = Arrays.copyOfRange(cuts, 0, init);
            int first = cuts[init];
            for(int j = 0; j < cpy.length; j++){
                cutlen = Math.min(splitStringRec(cpy, first, j), cutlen);
            }
        }
        if (init < cuts.length - 1){
            cutr = Integer.MAX_VALUE;
            int[] cpy = Arrays.copyOfRange(cuts, init + 1, cuts.length);
            int newcost = stringlen - cuts[init];
            for(int i = 0; i < cpy.length; i++){
                cpy[i] = cpy[i] - cuts[init];
            }
            for(int i = 0; i < cpy.length; i++){
                cutr = Math.min(splitStringRec(cpy, newcost, i), cutr);
            }
        }
        return stringlen + cutlen + cutr;
    }

    public static void main(String[] args){
        String test = "kasdklfaslhkjfhkljasdlhkfjkladfkjkjashdfjklasdhfjk";
        int[] splits = {7,13,28,41,45};
        int res = splitString(test, splits);
        //Should get that the cost is 122
        System.out.println("The cost of splitting the string \"" + test + "\" is " + res);
    }

}

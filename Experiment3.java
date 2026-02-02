import java.util.HashMap;
import java.util.Scanner;

public class Experiment3 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int N = sc.nextInt();

        HashMap<Integer, Integer> map = new HashMap<>();

        int sum = 0;
        int maxLen = 0;

        map.put(0, -1);

        for (int i = 0; i < N; i++) {
            char ch = sc.next().charAt(0);

            if (ch == 'P')
                sum += 1;
            else
                sum -= 1;

            if (map.containsKey(sum)) {
                int length = i - map.get(sum);
                maxLen = Math.max(maxLen, length);
            } else {
                map.put(sum, i);
            }
        }
        System.out.println(maxLen);
    }
}

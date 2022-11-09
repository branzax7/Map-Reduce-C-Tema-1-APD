package doubleVectorElements;



public class Main {

    public static void main(String[] args) {
        int N = 100000013;
        int[] v = new int[N];  //cum transmit vectorul in clasa thread ca sa pot opera pe el
        int P = 4; // the program should work for any P <= N
        Thread[] threads = new Thread[P];

        for (int i = 0; i < N; i++) {
            v[i] = i;
        }


        int start, end;
        for (int i = 0; i < P; i++) {
            start = i * N / P;
            end = Math.min((i + 1) * N / P, N);
            threads[i] = new Thread(new MyThread(start, end));
            threads[i].start();
        }
        for (int i = 0; i < 2; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Parallelize me using P threads
//        for (int i = 0; i < N; i++) {
//            v[i] = v[i] * 2;
//        }

        for (int i = 0; i < N; i++) {
            if (v[i] != i * 2) {
                System.out.println("Wrong answer");
                System.exit(1);
            }
        }
        System.out.println("Correct");
    }

}

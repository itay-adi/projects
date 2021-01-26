package il.co.ilrd.waitable_pqueue;
import java.util.Comparator;

/*Developer: Itay Adi Yosef
 * Date: Nov 20th
 * Reviewer: Max Kemel 
 */

public class WPQTest <T> {
    public static void main(String[] args) throws InterruptedException {
        WaitablePriorityQueue<String> waitTest = new WaitablePriorityQueue<>(10);
        WaitablePriorityQueue<Integer> threadSafe = new WaitablePriorityQueue<>(10, new PriorityCompInt());
        waitTest.enqueue("Abra");
        waitTest.enqueue("Barbara");
        waitTest.enqueue("Cadabra");
        System.out.println("Size: " +waitTest.size());
        System.out.println("Is empty? " +waitTest.isEmpty());
        System.out.println(waitTest.dequeue()); //Abra popped
        System.out.println("Remove existing: " +waitTest.remove("Cadabra"));
        System.out.println("Remove non existing: " +waitTest.remove("ChickFilA"));

        WaitablePriorityQueue<String> waitTest2 = new WaitablePriorityQueue<>(10, new PriorityCompStr());
        //The pqueue is sorted in reverse
        waitTest2.enqueue("Abra");
        waitTest2.enqueue("Marbara");
        waitTest2.enqueue("Zadabra");
        System.out.println(waitTest2.dequeue()); //Zadabra popped
        System.out.println();

        //One thread putting, two threads popping in reverse order
        Thread enqThread = new Thread(new Runnable() {
            @Override
            public void run() {
                for(int i = 0; i < 10; ++i) {
                    try {
                        Thread.sleep(500);
                        System.out.println("Put " + i);
                        threadSafe.enqueue(i);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        Thread deqThread = new Thread(new Runnable() {
            @Override
            public void run() {
                for(int i = 0; i < 5; ++i) {
                    try {
                        Thread.sleep(500);
                        System.out.println("Out t1 " + threadSafe.dequeue());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        Thread deqThread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                for(int i = 0; i < 5; ++i) {
                    try {
                        Thread.sleep(500);
                        System.out.println("Out t2 " + threadSafe.dequeue());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        enqThread.start();
        Thread.sleep(5000);
        deqThread.start();
        deqThread2.start();

        enqThread.join();
        deqThread.join();
        deqThread2.join();
    }

    private static class PriorityCompStr implements Comparator<String> {
        @Override
        public int compare(String s1, String s2) {
            return s2.charAt(0) - s1.charAt(0);
        }
    }

    private static class PriorityCompInt implements Comparator<Integer> {
        @Override
        public int compare(Integer int1, Integer int2) {
            return int2 - int1;
        }
    }
}


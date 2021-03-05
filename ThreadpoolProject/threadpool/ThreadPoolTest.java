package il.co.ilrd.threadpool;

import java.util.concurrent.Callable;
import java.util.concurrent.Future;
import java.util.concurrent.TimeoutException;

public class ThreadPoolTest {

	public static void main(String[] args) throws TimeoutException, InterruptedException {
		ThreadPool tp = new ThreadPool(4);
		SomeCallable sc = new SomeCallable();
		SomeRunnable sr = new SomeRunnable();
		HIGH high = new HIGH();
		int i = 0;

		tp.pause();

		while(i < 5) {
			Future<Integer> some1 = tp.submit(sc);
			Future<Integer> some2 = tp.submit(high , ThreadPool.Priority.MAX);	
			Future<Integer> some4 = tp.submit(sr, ThreadPool.Priority.HIGH, 8);
			Future<Integer> some3 = tp.submit(sr, ThreadPool.Priority.LOW);
			tp.execute(sr);			
			++i;
		}

		tp.resume();

		Thread.sleep(2000);
		tp.pause();
		//tp.shutdown();
		i = 0;
		tp.setNumOfThreads(1);
		Thread.sleep(2000);

		while(i < 5) {
			Future<Integer> some1 = tp.submit(sc);
			Future<Integer> some2 = tp.submit(high , ThreadPool.Priority.HIGH);				
			Future<Integer> some3 = tp.submit(sr, ThreadPool.Priority.LOW);
			Future<Integer> some4 = tp.submit(sr, ThreadPool.Priority.LOW, 8);
			tp.execute(sr);
			++i;
		}
		tp.resume();
		tp.shutdown();
		tp.awaitTermination();
	}
}

class SomeCallable implements Callable<Integer>{
	@Override
	public Integer call() throws Exception {
		System.out.println("SomeCallable " + Thread.currentThread().getName());

		return 2;
	}		
}

class HIGH implements Callable<Integer>{
	@Override
	public Integer call() throws Exception {
		System.out.println("HIGH");

		return 2;
	}		
}

class SomeRunnable implements Runnable{
	@Override
	public void run() {
		System.out.println("SomeRunnable " + Thread.currentThread().getName());
	}
}

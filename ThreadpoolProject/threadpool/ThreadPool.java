package il.co.ilrd.threadpool;

import java.util.concurrent.*;
import il.co.ilrd.waitable_pqueue.WaitablePriorityQueue;

/*Developer: Itay Adi Yosef
 * Reviewer: Ori Komemi
 * Date: November 24th
 */

public class ThreadPool implements Executor {
	private WaitablePriorityQueue<Task<?>> wpq = new WaitablePriorityQueue<>(1024);
	boolean isPaused = false;
	boolean isShutdown = false;
	private int numOfThreads;
	private int threadsPaused = 0;
	private Semaphore semSleep = new Semaphore(0);
	private Semaphore semExit = new Semaphore(0);

	//Constructor
	public ThreadPool(int numOfThreads){
		this.numOfThreads = numOfThreads;
		for(int i = 0; i < numOfThreads; ++i) {
			Thread tempThread = new Thread(new ThreadAction());
			tempThread.start();
		}
	}

	/*--------------------------------------------------------------------------------------*/

	/* all the submit methods creates TASK with functionality +  priority 
     and push it to Q.*/
	public <T> Future<T> submit (Runnable taskToRun, Priority taskPriority){
		//Executors.callable(r, null): converting runnable task to callable
		return submit(Executors.callable(taskToRun, null),taskPriority);
	}

	public <T> Future<T> submit (Runnable taskToRun, Priority taskPriority, T result){
		return submit(Executors.callable(taskToRun, result), taskPriority);
	}

	public <T> Future<T> submit (Callable<T> taskToCall){
		return submit(taskToCall, Priority.LOW);
	}

	public <T> Future<T> submit (Callable<T> taskToCall, Priority taskPriority){
		if(isShutdown == false) {
			Task<T> task = new Task<>(taskToCall,taskPriority);
			wpq.enqueue(task);

			return task.new TaskFuture();
		} else {
			throw new RejectedExecutionException();
		}		
	}

	public void execute (Runnable taskToRun){
		submit(taskToRun, Priority.LOW);
	}

	/*--------------------------------------------------------------------------------------*/

	public void setNumOfThreads(int threadsNum_set){
		int diff_low = numOfThreads - threadsNum_set;
		int diff_high = threadsNum_set - numOfThreads;

		if(threadsNum_set < 1) {
			throw new IllegalArgumentException();
		} else if (threadsNum_set < numOfThreads)  {// need to cancel some threads
			for(int i = 0; i < diff_low; ++i){
				Runnable deathTask = new Runnable() {
					@Override
					public void run() {
						throw new CancellationException();
					}
				};

				submit(deathTask, Priority.MAX);
			}

		} else {// need to create new threads
			if(isPaused == true) {
				for(int i = 0; i < diff_high; ++i){
					submit(new GoToSleep(), Priority.MAX);					
				}
			}

			for(int i = 0; i < diff_high; ++i){
				Thread thread = new Thread(new ThreadAction());
				thread.start();
			}
		}

		this.numOfThreads = threadsNum_set;
	}

	public void pause(){
		if(isPaused == false) {
			threadsPaused = numOfThreads;

			for(int i = 0; i < numOfThreads; ++i) {
				GoToSleep sleepPeel = new GoToSleep();
				submit(sleepPeel, Priority.MAX);
			}

			isPaused = true;
		}
	}

	private class GoToSleep implements Runnable{
		@Override
		public void run() {
			try {
				semSleep.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

	public void resume(){
		if(isPaused == true) {
			semSleep.release(threadsPaused);
			threadsPaused = 0;
			isPaused = false;
		}
	}

	public void shutdown(){
		resume();

		for(int i = 0; i < numOfThreads; ++i){
			Runnable deathTask = new Runnable() {
				@Override
				public void run(){
					semExit.release();
					throw new CancellationException();
				}				
			};
			submit(deathTask, Priority.MIN);
		}
		isShutdown = true;
	}

	public void awaitTermination(){
		awaitTermination(1000, TimeUnit.DAYS);
	}

	public void awaitTermination(long timeOut, TimeUnit measurementUnit){
		try {
			semExit.tryAcquire(numOfThreads, timeOut, measurementUnit);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	private class ThreadAction implements Runnable{
		private boolean isAlive = true;

		public void run() {
			while(isAlive) {
				Task<?> task = wpq.dequeue();
				try {
					task.runTask();
				} catch (Exception e) {
					isAlive = false;
				}
			}
			System.out.println("**ShutDown: " + Thread.currentThread().getName());
		}
	}

	private class Task<T> implements Comparable<Task<?>>{
		private Priority priority;
		private Callable<T> work;
		private Semaphore taskSem = new Semaphore(0);
		private TaskState taskState = TaskState.WAITING;
		private T result;

		private Task(Callable<T> work, Priority priority) {
			this.work = work;
			this.priority = priority;
		}

		@Override
		public int compareTo(Task<?> task) {
			return task.priority.compareTo(priority);
		}

		private void runTask() throws Exception{
			if(taskState == TaskState.WAITING){
				try {
					taskState = TaskState.RUNNING;
					result = work.call();
					taskState = TaskState.DONE;
				} catch (Exception e) {
					System.out.println("Interrupted");
					throw new Exception(e);
				} finally {
					taskSem.release();
				}
			}
		}		

		private class TaskFuture implements Future<T>{
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				boolean isExists = wpq.remove(Task.this);
				if(isExists){
					taskState = TaskState.CANCEL;
				}

				return isExists;
			}

			@Override
			public boolean isCancelled() {
				return taskState == TaskState.CANCEL;
			}

			@Override
			public boolean isDone() {
				return taskState == TaskState.DONE;
			}

			@Override
			public T get() throws InterruptedException, ExecutionException {
				if(taskState == TaskState.CANCEL) {
					throw new CancellationException();
				}

				taskSem.acquire();
				
				return result;
			}

			@Override
			//long timeout: number of units
			//TimeUnit timeUnit: units
			public T get(long timeout, TimeUnit timeUnit) throws InterruptedException, ExecutionException, TimeoutException {
				if(taskState == TaskState.CANCEL) {
					throw new CancellationException();
				}

				taskSem.tryAcquire(timeout, timeUnit);
				return result;
			}
		}
	}

	public enum Priority{

		MIN(5),
		LOW(4),
		MID (3),
		HIGH(2),
		MAX(1);

		private final int priority;

		private Priority(int priority) {
			this.priority = priority;
		}
	}

	public enum TaskState{
		WAITING(1),
		RUNNING(2),
		CANCEL(3),
		DONE(4);

		private final int state;

		private TaskState(int state){
			this.state = state;
		}
	}
}

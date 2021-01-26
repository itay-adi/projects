package il.co.ilrd.waitable_pqueue;

/*Developer: Itay Adi Yosef
 * Date: Nov 20th
 * Reviewer: Max Kemel 
 */

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WaitablePriorityQueue<E>{
	private PriorityQueue<E> pQueue;
	private Lock pqLock = new ReentrantLock(true);
	private Semaphore fillCount; //count the elements left to fill
	private Semaphore emptyCount; //count the elements left to remove

	//constructor1
	public WaitablePriorityQueue(int capacity) {
		this(capacity, null);
	}

	//constructor2
	public WaitablePriorityQueue(int capacity, Comparator<E> cmptor) {
		pQueue = new PriorityQueue<>(capacity, cmptor);
		semInit(capacity);
	}

	private void semInit(int capacity) {
		emptyCount = new Semaphore(0);
		fillCount = new Semaphore(capacity);
	}

	public void enqueue(E item){
		try {
			fillCount.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		pqLock.lock();
		pQueue.add(item);
		pqLock.unlock();
		emptyCount.release();		
	}

	public E dequeue(){
		try {
			emptyCount.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		pqLock.lock();
		E ret_element = pQueue.poll();
		pqLock.unlock();
		fillCount.release();

		return ret_element;
	}

	public boolean remove(E element){
		pqLock.lock();
		boolean ret_val = pQueue.remove(element);
		pqLock.unlock();
		
		if(ret_val) {
			fillCount.release();
			try {
				emptyCount.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}	
		}

		return ret_val;
	}

	public int size() {
		return pQueue.size();
	}

	public boolean isEmpty() {
		return pQueue.isEmpty();
	}
}
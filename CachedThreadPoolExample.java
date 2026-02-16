import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CachedThreadPoolExample {
    public static void main(String[] args) {
        // Create a CachedThreadPool
        ExecutorService executor = Executors.newCachedThreadPool();

        // Submit 5 tasks
        for (int i = 0; i < 5; i++) {
            executor.submit(new SimpleTask());
        }

        executor.shutdown();
    }
}

// Your existing Runnable task
class SimpleTask implements Runnable {
    @Override
    public void run() {
        for (int i = 1; i <= 2; i++) {
            System.out.println(Thread.currentThread().getName() + ": " + i);
            try {
                Thread.sleep(1000); // 1 second sleep
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                System.out.println("Thread was interrupted");
            }
        }
    }
}

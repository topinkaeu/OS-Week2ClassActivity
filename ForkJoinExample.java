import java.util.concurrent.RecursiveTask;
import java.util.concurrent.ForkJoinPool;

// ForkJoin example
public class ForkJoinExample {
    public static void main(String[] args) {
        int[] numbers = {1,2,3,4,5,6,7,8};
        ForkJoinPool pool = new ForkJoinPool();
        SumTask task = new SumTask(numbers, 0, numbers.length);

        int result = pool.invoke(task);
        System.out.println("Sum of array: " + result);
    }
}

// RecursiveTask to split work
class SumTask extends RecursiveTask<Integer> {
    private int[] numbers;
    private int start, end;

    public SumTask(int[] numbers, int start, int end) {
        this.numbers = numbers;
        this.start = start;
        this.end = end;
    }

    @Override
    protected Integer compute() {
        if (end - start <= 2) { // small enough to compute directly
            int sum = 0;
            for (int i = start; i < end; i++) {
                sum += numbers[i];
                System.out.println(Thread.currentThread().getName() + " processing index " + i);
            }
            return sum;
        } else { // split tasks
            int mid = (start + end) / 2;
            SumTask left = new SumTask(numbers, start, mid);
            SumTask right = new SumTask(numbers, mid, end);
            left.fork(); // run left asynchronously
            int rightResult = right.compute(); // compute right in current thread
            int leftResult = left.join(); // wait for left
            return leftResult + rightResult;
        }
    }
}

#define N_TESTS 5
#define FIB_N 32
#define STACK_SIZE 2048
#define PRIORITY 1

int task_priorities[] = {1, 1, 1, 1, 2};

int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}

void do_work() {
    fib(FIB_N);
}
int fib_rec_c(int n)
{
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib_rec_c(n - 1) + fib_rec_c(n - 2) + fib_rec_c(n - 3);
    }
}


int fib_rec2_c(int n)
{
    int r;
    
    if (n == 0) {
        r = 0;
    } else if (n == 1) {
        r = 1;
    } else {
        r = fib_rec_c(n - 1) + fib_rec_c(n - 2);
    }

    return r;
}




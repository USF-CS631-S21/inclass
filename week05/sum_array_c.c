int sum_array_c(int *array, int len) {
    int i;
    int sum = 0;

    for (i = 0; i < len; i += 1) {
        sum = sum + array[i];
    }

    return sum;    
}

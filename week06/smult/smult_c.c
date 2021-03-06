void smult_c(int *array, int len, int s) {
    int i;

    for (i = 0; i < len; i += 1) {
        array[i] = array[i] * s;
    }
}

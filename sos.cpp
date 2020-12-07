//no lambda, because it won't be vectorized and will be slow
template<typename T>
void sumOnSubsets(T* arr, int bits) {
    int sz = 1<<bits;
    for (int j=bits-1;j>=0;j--) {
        int shift = 1<<(j+1);
        int len = 1<<j;
        for (int i=0;i<sz;i+=shift) {
            for (int k=i;k<i+len;k++) {
                arr[k+len] += arr[k];
            }
        }
    }
}
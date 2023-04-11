void findPeaks(int arr[], int n, int thresh) {
    int i = 1;

    while (i < n - 1) {
        while (i < n - 1 && arr[i] <= arr[i - 1]) {
            i++;
        }
        
        int localMin = i - 1;

        while (i < n - 1 && arr[i] >= arr[i - 1]) {
            i++;
        }
        
        int localMax = i - 1;
        
        while (i < n - 1 && arr[i] <= arr[i - 1]) {
            i++;
        }
        
        if (arr[localMax] - arr[localMin] > thresh && arr[localMax] - arr[i] > thresh) {
            printf("%d\n", localMax);
        }
    }
}
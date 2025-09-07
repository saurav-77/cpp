


--- Brute Force 1----

for i = 0 to < n:
    for j = i+2 to < n:
        mini = min(arr[i], arr[j]);
        maxi = INT_MIN
        for k = i+1 to < j:
            maxi = max(maxi, arr[k]);
        if (mini > maxi) ans++;



--- Brute force 2 ---

 for i = 0 to < n-1:
    maxi = arr[i+1]
    for j = i+2 to < n:
        mini = min(arr[i], arr[j]);        
        if (mini > maxi) ans++;
        maxi = max(maxi, arr[j]);



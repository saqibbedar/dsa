// Write code having following exact time complexities

// 1. 3n^2+3
void task1(int n){
    for (int i = 0; i < 3 * n; ++i){
        for (int j = 0; j < n; ++j){
            // any statement will go here
        }
    }

    for (int i = 0; i < 3; ++i){
        // any statement will go here
    }
}

// 2. 2nlog3n
void task2(int n){
    for (int i = 0; i < 2 * n; ++i){
        for (int j = 1; j < 3 * n; j *= 3){
            // any statement will go here
        }
    }
}

// 3. n(n-1)/2 = n^2/2
void task3(int n){
    for (int i = 0; i < n; ++i){
        for (int j = i; j < n; ++j){
            // any statement will go here
        }
    }
}


## Students names:
### Ryan Esperto UFID: 49218645
### Derek Camilo-Taylor UFID: 49535835

## Instructions to compile/build the code:

__Inside of git bash copy and past inside of the project directory__:

`g++ -std=c++17 -o hvlcs main.cpp`

This will create a executable called `hvlcs`

This can be run with `./hvlcs`

Follow additional instruction as prompted by terminal.

NOTE: If you are using and ide to compile and run without building an exe the pathing will be different.

### Pathing From exe Example

`examples/example1.in`

### Pathing From main.cpp Example

`../examples/example1.in`







## Question 1: Empirical Comparison
Use at least 10 nontrivial input files (i.e., contain strings of length at least 25). Graph the
runtime of the 10 files.

| Input File | Runtime  | 
|------------|----------|
| test01     | 0.103 ms | 
| test02     | 0.131 ms | 
| test03     | 0.082 ms |
| test04     | 0.073 ms | 
| test05     | 0.076 ms | 
| test06     | 0.080 ms | 
| test07     | 0.089 ms | 
| test08     | 0.076 ms | 
| test09     | 0.125 ms | 
| test09     | 0.086 ms | 






## Question 2: Recurrence Equation
Give a recurrence that is the basis of a dynamic programming algorithm to compute the
HVLCS of strings A and B. You must provide the appropriate base cases, and explain why your recurrence is correct.

Let DP[i][j] be the maximum value of a common subsequence of the first i characters of A and first j characters of B.

### Base Cases: 
DP[i][0] = 0

DP[0][j] = 0

### Recurrance

1. If A[i-1] != B[j-1]:

DP[i][j] = max(DP[i-1][j], DP[i][j-1])

2. If A[i-1] == B[j-1]:

DP[i][j] = max(DP[i-1][j],
DP[i][j-1],
DP[i-1][j-1] + value[A[i-1]])

At each position (i, j), there are three possibilities:

1. Skip character A[i]
2. Skip character B[j]
3. Use both characters if they match

The recurrence considers all valid possibilities and selects the maximum value, ensuring an optimal solution.

## Question 3: Big-Oh
Give pseudocode of an algorithm to compute the length of the HVLCS of given strings A
and B. What is the runtime of your algorithm?

Cases
Case 1:
dp[i-1][j]
skip the current character of A

Case 2:
dp[i][j-1]
skip the current character of B

Case 3:
dp[i-1][j-1] + value[A[i]]
if the characters match, include that character in the subsequence

HVLCS-Length(A, B, value)

  for i = (0 to n)
        dp[i][0] = 0

    for j = (0 to m)
        dp[0][j] = 0

    for i  = (1 to n)
        for j = (1 to m)
            dp[i][j] = max(dp[i-1][j], dp[i][j-1])

            if A[i] = B[j]
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + value[A[i]])
                
    return dp[n][m]

Runtime: O(nm)

Space: O(nm)
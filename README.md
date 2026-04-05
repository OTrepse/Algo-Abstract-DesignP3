Student Names
Ryan Esperto UFID: 49218645
Derek Camilo Taylor UFID: 

Instructions to Compile:




Instructions to run code that runs eviction policies:







Question 1: Empirical Comparison
Use at least 10 nontrivial input files (i.e., contain strings of length at least 25). Graph the
runtime of the 10 files.







Question 2: Recurrence Equation
Give a recurrence that is the basis of a dynamic programming algorithm to compute the
HVLCS of strings A and B. You must provide the appropriate base cases, and explain why your recurrence is correct.





Question 3: Big-Oh
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
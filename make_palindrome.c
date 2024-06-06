//Find out the character needed to make a string a Palindrome string.
//Warepam Mangalsana
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to find the minimum insertions needed and characters to add
char* makePalindrome(char* s) {
    int n = strlen(s);
    int dp[n][n];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1] = s[i] == s[i + 1] ? 2 : 1;
    }
    for (int i = 2; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            dp[j][j + i] = s[j] == s[j + i] ? 2 + dp[j + 1][j + i - 1] : (dp[j + 1][j + i] > dp[j][j + i - 1] ? dp[j + 1][j + i] : dp[j][j + i - 1]);
        }
    }

    // Find the minimum insertions needed
    int min_insertions = n - dp[0][n - 1];

    // Construct the palindrome by adding the required characters
    int i = 0, j = n - 1;
    int left = 0, right = n + min_insertions - 1;
    char* res = (char*)malloc((n + min_insertions + 1) * sizeof(char));
    while (i <= j) {
        if (s[i] == s[j]) {
            i++;
            j--;
        } else if (dp[i][j - 1] > dp[i + 1][j]) {
            res[left++] = s[j];
            res[right--] = s[j];
            j--;
        } else {
            res[left++] = s[i];
            res[right--] = s[i];
            i++;
        }
    }
    res[n + min_insertions] = '\0';
    i=0;
    j = strlen(res)-1;
    while(i<j)
    {
        res[i] += res[j];
        res[j] = res[i] - res[j];
        res[i] -= res[j];
        i++;
        j--;
    }
    return res;
}

int main() {
    char input[100];
    char* res;
    printf("Enter a string: ");
    scanf("%s", input);
    res = makePalindrome(input);
    printf("\nPalindrome with minimum insertions: %s\n", res);
    free(res);

    return 0;
}

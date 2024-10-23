#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to dynamically expand the array size when needed
// Takes a pointer to the current size and the array itself as arguments
// Returns a new array with double the size
int *expand_Arr(size_t *size, int *stake);

int main() {
    // Initial size of the stack (used for RPN calculation)
    size_t size = 4;

    // Dynamically allocate memory for the stack to hold integers
    int *stake = malloc(sizeof(int) * size);
    size_t i = 0;  // Index to track stack position
    char x;        // Variable to store the operator or character

    // Main loop for processing input and performing RPN calculations
    while (1) {
        // If the array is full, expand it using the expand_Arr function
        if (i == (size - 1)) {
            stake = expand_Arr(&size, stake);
        }

        // Read the next integer and store it in the stack
        int rc = scanf("%d", &stake[i]);

        // Break the loop if end of input (EOF) is detected
        if (rc == EOF) break;

        // Increment stack position if a valid integer was entered
        if (rc == 1) ++i;

        // Read the next character (operator or whitespace)
        scanf("%c", &x);

        // Process operators and perform the corresponding operation
        // 'p' - addition, 's' - subtraction, '*' - multiplication, '/' - division
        if (x == 'p' && i > 1) {
            // Perform addition with the last two values in the stack
            stake[i - 2] = stake[i - 2] + stake[i - 1];
            i = i - 1; // Decrease the stack size after the operation
        } else if (x == 's' && i > 1) {
            // Perform subtraction
            stake[i - 2] = stake[i - 2] - stake[i - 1];
            i = i - 1;
        } else if (x == '*' && i > 1) {
            // Perform multiplication
            stake[i - 2] = stake[i - 2] * stake[i - 1];
            i = i - 1;
        } else if (x == '/' && i > 1) {
            // Perform division (no check for division by zero here)
            stake[i - 2] = stake[i - 2] / stake[i - 1];
            i = i - 1;
        }
    }

    // Print the result of the RPN expression, which will be the last remaining value in the stack
    printf("%d\n", stake[0]);

    // Free the dynamically allocated memory for the stack
    free(stake);
}

// Function to expand the size of the dynamic array used as a stack
// Doubles the size of the array and copies the old data to the new array
int *expand_Arr(size_t *size, int *stake) {
    // Allocate new memory with double the size
    int *temp_arr = malloc((*size) * 2 * sizeof(int));

    // Copy the elements from the old stack to the new larger stack
    for (int i = 0; i < *size; ++i) {
        temp_arr[i] = stake[i];
    }

    // Update the size variable to reflect the new size
    *size = (*size) * 2;

    // Free the old stack memory
    free(stake);

    // Return the new, expanded stack
    return temp_arr;
}

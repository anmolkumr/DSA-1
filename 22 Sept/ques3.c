#include <stdio.h>

// Function to swap two elements in an array
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to reverse an array from start to end
void reverse(int a[], int start, int end)
{
    while (start < end)
    {
        swap(&a[start], &a[end]);
        start++;
        end--;
    }
}

// Function to find the previous permutation of an array
void previous_permutation(int a[], int n)
{
    int i = n - 2;

    // Find the largest index i such that a[i] > a[i+1]
    while (i >= 0 && a[i] <= a[i + 1])
    {
        i--;
    }

    if (i >= 0)
    {
        // Find the largest index j such that a[j] < a[i]
        int j = n - 1;
        while (a[j] >= a[i])
        {
            j--;
        }

        // Swap a[i] and a[j]
        swap(&a[i], &a[j]);
    }

    // Reverse the elements from i+1 to the end
    reverse(a, i + 1, n - 1);
}

// Function to print an array
void print_array(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
    int a[] = {1, 5, 6, 2, 3, 4};
    int n = sizeof(a) / sizeof(a[0]);

    printf("Original array: ");
    print_array(a, n);

    previous_permutation(a, n);

    printf("Previous permutation: ");
    print_array(a, n);

    return 0;
}

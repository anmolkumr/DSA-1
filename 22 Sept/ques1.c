#include <stdio.h>


void process_selection(int b[], int k, void *data)
{
    int m = 0;
    while (m < k)
    {
        printf(" %d", b[m]);
        m++;
    }
}
void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{
    int j, i;

    // Initialize the first selection as a[0..k-1]
    for (i = 0; i < k; i++)
    {
        b[i] = a[i];
    }

    while (1)
    {
        // Process the current selection
        process_selection(b, k, data);

        // Find the rightmost element in b[] that can be incremented
        j = k - 1;
        while (j >= 0 && b[j] == a[n - k + j])
        {
            j--;
        }

        // If no such element exists, we are done
        if (j < 0)
        {
            break;
        }

        // Increment the selected element
        b[j]++;

        // Update the rest of the selection
        for (i = j + 1; i < k; i++)
        {
            b[i] = b[i - 1] + 1;
        }
    }
}

int main()
{
    int a[] = {1, 2, 3};
    int b[2]; // Array to hold selections
    int data; // You can pass any data needed for your processing function

    generate_selections(a, 3, 2, b, &data, process_selection);

    return 0;
}
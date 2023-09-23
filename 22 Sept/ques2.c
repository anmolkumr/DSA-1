#include <stdio.h>

// Helper function to calculate the length of a word in the dictionary
int word_length(const char *word)
{
    int length = 0;
    while (word[length] != '\0')
    {
        length++;
    }
    return length;
}

// Helper function to copy a substring from source to buf
void copy_substring(const char *source, char *buf, int start, int end)
{
    int index = 0;
    for (int i = start; i <= end; i++)
    {
        buf[index++] = source[i];
    }
    buf[index] = '\0'; // Null-terminate the substring
}

// Helper function to generate all possible splits recursively
void generate_splits_recursive(const char *source, const char *dictionary[], int nwords, char *buf, int buf_index, int source_index, void *data, void (*process_split)(char buf[], void *data))
{
    if (source[source_index] == '\0')
    {
        // End of the source string reached, process the split
        process_split(buf, data);
        return;
    }

    for (int i = source_index; source[i] != '\0'; i++)
    {
        // Copy a potential word from source to buf
        copy_substring(source, buf + buf_index, source_index, i);

        // Check if the copied word exists in the dictionary
        int word_found = 0;
        for (int j = 0; j < nwords; j++)
        {
            int dict_word_length = word_length(dictionary[j]);
            if (dict_word_length == i - source_index + 1)
            {
                // Compare the substring with a word in the dictionary
                int match = 1;
                for (int k = 0; k < dict_word_length; k++)
                {
                    if (buf[buf_index + k] != dictionary[j][k])
                    {
                        match = 0;
                        break;
                    }
                }
                if (match)
                {
                    word_found = 1;
                    break;
                }
            }
        }

        // If the word is found in the dictionary, continue generating splits
        if (word_found)
        {
            buf[buf_index + i - source_index + 1] = ' '; // Add a space between words
            generate_splits_recursive(source, dictionary, nwords, buf, buf_index + i - source_index + 2, i + 1, data, process_split);
        }
    }
}

// Wrapper function to start generating splits
void generate_splits(const char *source, const char *dictionary[], int nwords, char *buf, void *data, void (*process_split)(char buf[], void *data))
{
    generate_splits_recursive(source, dictionary, nwords, buf, 0, 0, data, process_split);
}

// Example process_split function
void process_split(char buf[], void *data)
{
    printf("%s\n", buf);
}

int main()
{
    const char *source = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"};
    char buf[256]; // Buffer to hold splits
    int data;      // You can pass any data needed for your processing function

    generate_splits(source, dict, 5, buf, &data, process_split);

    return 0;
}

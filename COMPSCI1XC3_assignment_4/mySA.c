// Include the header file for the function prototypes
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a struct to store the word entries
struct words
{
    char *word;        // Pointer to store the word
    float score;       // Float to store the score
    float SD;          // Float to store the standard deviation
    int SIS_array[10]; // Array to store the sentiment intensity scores
};
/*
Function that reads the lines of the diconary file and populates the words struct, it into an array of words
*/
struct words *readDictionaryAndPopulateWords(const char *filename, int *counterForNumberOfWordEntries)
{

    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    // Check if the file was opened without any issues
    if (!file)
    {
        // Print an error message if there's an issue opening the file
        printf("There was an error when opening the file please, check the file name or the path\n");
        // Return NULL if the file couldn't be opened
        return NULL;
    }

    // Initialize the initial size of the array of words, being able to store 300 characters for each line
    int capacityOfArray = 300;
    // Allocate memory for the array of words, with the capacity times the size of the struct
    struct words *wordsList = malloc(capacityOfArray * sizeof(struct words));

    // Check if memory allocation was successful, if not then return and error message
    if (!wordsList)
    {
        printf("The memory allocation for the array of words was not a success\n");
        // Close the file before returning
        fclose(file);
        // Return NULL due to failed memory allocation
        return NULL;
    }

    // Initialize the counter for the number of word entries to 0
    *counterForNumberOfWordEntries = 0;
    // Buffer to hold each line, it can hold up to 1024 characters
    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        // Check if we need to increase the capacity of the array
        if (*counterForNumberOfWordEntries >= capacityOfArray)
        {
            // Double the capacity of the array
            capacityOfArray *= 2;
            // Reallocate memory for the array of words
            struct words *tempEntries = realloc(wordsList, capacityOfArray * sizeof(struct words));
            // Check if memory reallocation was successful
            if (!tempEntries)
            {
                printf("The memory reallocation for the array of words was not a success\n");
                // Free the memory allocated for the array of words
                free(wordsList);
                // Close the file before returning
                fclose(file);
                // return null meaning that the memeory reallocation was not successful
                return NULL;
            }
            // Update the pointer to the new memory location
            wordsList = tempEntries;
        }

        // Pointer to the current character in the line
        char *currentCharacterPointer = line;
        //// Track the current field word, score, SD, SIS_array being read in the current line
        int currentFieldIndexInWords = 0;
        // Temporary string to store the word, score, SD, SIS_array being read
        char tempStr[256];
        // Index to keep track of the current character in the temporary string
        int tempStrIndex = 0;

        // Loop through each character in the line
        while (*currentCharacterPointer != '\0')
        {
            /*
             Check if the current character is a tab open bracket comma close bracket or a newline
            */
            if (*currentCharacterPointer == '\t' || *currentCharacterPointer == '[' || *currentCharacterPointer == ',' ||
                *currentCharacterPointer == ']' || *currentCharacterPointer == '\n')
            {
                // Add a null terminator to the temporary string to make it a full string in C
                tempStr[tempStrIndex] = '\0';

                // Pointer to the current word entry in the array
                struct words *currentWord = &wordsList[*counterForNumberOfWordEntries];
                // Check the current field index to know which field we are reading
                switch (currentFieldIndexInWords)
                {
                // Case for if the currentFieldIndexInWords is 0 meaning that it is a word
                case 0:
                    // This code is to allocate memory for the word and copy the word into the memory
                    // The strdup function allocates memory for the string and copies the string into the memory
                    currentWord->word = strdup(tempStr);
                    break;
                // Case for if the currentFieldIndexInWords is 1 meaning that it is a score
                case 1:
                    // This code is to convert the score to a float and store it in the struct
                    // The atof function converts a string to a float and allocates memory for the float
                    // This is the same for case 2
                    currentWord->score = atof(tempStr);
                    break;
                // Case for if the currentFieldIndexInWords is 2 meaning that it is a standard deviation
                case 2:
                    currentWord->SD = atof(tempStr);
                    break;
                // Case for if the currentFieldIndexInWords is 3-12 meaning that it is a sentiment intensity score
                default:
                    if (currentFieldIndexInWords - 3 < 10)
                    {
                        // Convert the sentiment intensity score to an integer and store it in the struct
                        currentWord->SIS_array[currentFieldIndexInWords - 3] = atoi(tempStr);
                    }
                    break;
                }

                // Reset the index for the next field
                tempStrIndex = 0;
                // Move to the next field
                currentFieldIndexInWords++;

                // Check if the current character is a close bracket this means that we are at the end of the array in the dict file
                if (*currentCharacterPointer == ']')
                {
                    // Increase the counter for the number of word entries
                    *counterForNumberOfWordEntries += 1;
                    currentFieldIndexInWords = 0; // Reset the field index
                    break;
                }
            }
            // Check if the current character is not a space
            else if (*currentCharacterPointer != ' ')
            {
                // Storing the character pointed to by currentCharacterPointer
                // in the tempStr array at the position tempStrIndex  and then incrementing tempStrIndex by 1
                tempStr[tempStrIndex++] = *currentCharacterPointer;
            }
            // Move to the next character in the line
            currentCharacterPointer++;
        }
    }

    // Close the file after reading all lines
    fclose(file);
    // Return the array of words
    return wordsList;
}

// Function to compute the sentiment score for a given sentence
float computeSentimentScore(char *sentence, struct words *wordsList, int numOfWords)
{
    // Initialize the sum of scores and the word count
    float sumScore = 0.0;
    int wordCount = 0;

    // The strtok function is used to split the sentence into tokens
    // this means that the sentence is split into words based on ,.!? and newline characters
    // and it returns a pointer to the first token found in the sentence
    char *token = strtok(sentence, " ,.!?\n");

    // Loop through each token until there are no more tokens
    while (token != NULL)
    {
        // Convert the token to lowercase
        // this has to be done becuase for the analysis we are looking at insensitive cases
        for (int i = 0; token[i]; i++)
        {
            // Convert to lowercase
            token[i] = tolower(token[i]);
        }

        // Look up the token in the wordsList
        int found = 0;
        // This for loop is used to loop through the wordsList to find the token
        for (int i = 0; i < numOfWords; i++)
        {
            // Check if the token is found in the wordsList
            if (strcmp(wordsList[i].word, token) == 0)
            {
                // Add the score of the word to the sum of scores
                sumScore += wordsList[i].score;
                // Set found to 1 to indicate that the word was found
                found = 1;
                break;
            }
        }
        // If the word is not found in the wordsList then the score is 0
        if (!found)
        {
            sumScore += 0; // Add zero to the sum if not found becuase the word does not mean anything such as the word "lucas"
        }
        // Increment the word count
        wordCount++;

        // Get the next token
        token = strtok(NULL, " ,.!?\n");
    }

    // Check if any words were found
    if (wordCount > 0)
    {
        // Return the average score of the sentence
        return sumScore / wordCount;
    }
    else
    {
        // Return 0 if no words were found
        return 0;
    }
}

// Function to perform sentiment analysis on sentences from a file
void performSentimentAnalysis(const char *filename, struct words *wordsList, int numOfWords)
{
    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    // Check if the file was opened successfully
    if (!file)
    {
        perror("Error opening sentences file");
        return;
    }

    // Buffer to hold each line it can hold at most 450 characters
    char line[450];

    // Print the header for the output the -85s is used to left align the string
    printf("%-85s %s\n", "       string sample", "score");
    printf("---------------------------------------------------------------------------------------------------------\n");

    // Loop through each line in the file
    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (line[strlen(line) - 1] != '\n' && !feof(file)) // Check if the line is too long for the buffer
        {
            // Handle the error for the line exceeding buffer size
            fprintf(stderr, "Line too long for buffer and was shorted please keep note there may be issues.\n");

            // skip the rest of the line that didn't fit into the buffer
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF)
                ;
            // Continue to the next line
            continue;
        }

        // Remove the newline character from the line
        line[strcspn(line, "\r\n")] = 0;

        // Buffer to store the original line before tokenization
        char originalLine[450];
        // Copy the line
        strcpy(originalLine, line);

        // Get the sentiment score for the line
        float score = computeSentimentScore(line, wordsList, numOfWords);

        // Print the original line and the score
        printf("%-85s %.2f\n", originalLine, score);
    }

    fclose(file); // Close the file
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    { // Ensure correct number of arguments
        printf("Usage: %s <dictionary_filename> <sentences_filename>\n", argv[0]);
        return 1;
    }

    // Read the dictionary file and populate the words struct
    int counterForTheNumberOfEntriesInTheFile = 0;
    struct words *lexiconEntries = readDictionaryAndPopulateWords(argv[1], &counterForTheNumberOfEntriesInTheFile);

    // Check if there was an issue reading the lexicon or the lexicon is empty
    if (!lexiconEntries || counterForTheNumberOfEntriesInTheFile == 0)
    {
        printf("There was an error in reading the lexicon or the file.\n");
        return 1;
    }
    // Perform sentiment analysis on the sentences from the file
    performSentimentAnalysis(argv[2], lexiconEntries, counterForTheNumberOfEntriesInTheFile);

    // Free the memory allocated for the words
    for (int i = 0; i < counterForTheNumberOfEntriesInTheFile; i++)
    {
        free(lexiconEntries[i].word); // Free each word
    }
    // Free the memory allocated for the array of words
    free(lexiconEntries);

    return 0;
}
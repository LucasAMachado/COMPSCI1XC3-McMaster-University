#ifndef FUNCTION_H
#define FUNCTION_H

// Function prototypes
struct words *readDictionaryAndPopulateWords(const char *filename, int *counterForNumberOfWordEntries);
float computeSentimentScore(char *sentence, struct words *wordsList, int numOfWords);
void performSentimentAnalysis(const char *filename, struct words *wordsList, int numOfWords);

#endif // FUNCTION_H

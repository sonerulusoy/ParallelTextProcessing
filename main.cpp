#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SENTENCE_LENGTH 1000

struct Sentence {
    char text[MAX_SENTENCE_LENGTH];
};

int main() {
    FILE *file;
    struct Sentence sentences[100];
    int total_characters = 0, total_words = 0;

    file = fopen("sentences.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    int num_sentences = 0;
    while (fgets(sentences[num_sentences].text, MAX_SENTENCE_LENGTH, file) != NULL) {
        num_sentences++;
    }
    fclose(file);

    
    int thread_counts[] = {1, 2, 4, 8, 16, 32, 64, 128};
    int num_thread_counts = sizeof(thread_counts) / sizeof(thread_counts[0]);

    
    for (int i = 0; i < num_thread_counts; i++) {
        int num_threads = thread_counts[i];
        double start_time = omp_get_wtime();
        
        
        struct Sentence queue[100]; 
        int queue_size = 0;

        
        #pragma omp parallel num_threads(num_threads) reduction(+:total_characters, total_words)
        {
            int tid = omp_get_thread_num();
            int local_characters = 0, local_words = 0;
            
            
            #pragma omp for 
            for (int i = 0; i < num_sentences; i++) {
                
                int word_count = 0, char_count = 0, in_word = 0;
                for (int j = 0; sentences[i].text[j] != '\0'; j++) {
                    if (sentences[i].text[j] == ' ' || sentences[i].text[j] == '\t' || sentences[i].text[j] == '\n') {
                        if (in_word) {
                            word_count++;
                            in_word = 0;
                        }
                    } else {
                        char_count++;
                        in_word = 1;
                    }
                }
                if (in_word) {
                    word_count++;
                }
                
                local_characters += char_count;
                local_words += word_count;
            }

            #pragma omp critical
            {
                total_characters += local_characters;
                total_words += local_words;
            }
        }

        double end_time = omp_get_wtime();
        double elapsed_time = end_time - start_time;

        
        printf("Number of threads: %d, Total number of characters: %d, Total number of words: %d, Elapsed time: %f s\n",
       num_threads, total_characters, total_words, elapsed_time);

    }

    return 0;
}


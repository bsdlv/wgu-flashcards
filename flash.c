#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define MAX_CARDS 1000

typedef struct {
    char question[MAX_LINE_LENGTH];
    char answer[MAX_LINE_LENGTH];
} Flashcard;

void trim(char *str) {
    char *end;
    while(isspace((unsigned char)*str)) str++;
    if(*str == 0) return;
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';
}

void shuffle(Flashcard *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Flashcard temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }
}

int main(int argc, char *argv[]) {
    printf("Welcome to .flash\n");
    printf("Choose a flashcard set to load:\n");
    
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    int count = 0;
    char files[100][256];
    
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                char *ext = strrchr(dir->d_name, '.');
                if (ext && strcmp(ext, ".flash") == 0) {
                    printf("%d. %s\n", count + 1, dir->d_name);
                    strcpy(files[count], dir->d_name);
                    count++;
                }
            }
        }
        closedir(d);
    } else {
        perror("Error opening directory");
        return 1;
    }
    
    if (count == 0) {
        printf("No .flash files found in the current directory.\n");
        return 1;
    }
    
    int choice;
    do {
        printf("Enter the number of the file you want to open (1-%d): ", count);
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    } while (1);
    
    while (getchar() != '\n'); // Clear input buffer
    
    char *filename = files[choice - 1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    Flashcard cards[MAX_CARDS];
    int cardCount = 0;
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), file) != NULL) {
        trim(line);
        
        if (strlen(line) == 0) {
            continue;
        }
        
        if (strncmp(line, "--", 2) == 0) {
            strcpy(cards[cardCount].answer, line + 2);
            trim(cards[cardCount].answer);
            cardCount++;
        } else {
            strcpy(cards[cardCount].question, line);
        }
    }
    
    fclose(file);
    
    if (cardCount == 0) {
        printf("No cards found in the file.\n");
        return 1;
    }
    
    srand(time(NULL));  // Initialize random seed
    shuffle(cards, cardCount);
    
    printf("Flashcard set loaded and shuffled. Press Enter to start.\n");
    getchar();
    
    for (int i = 0; i < cardCount; i++) {
        printf("Card %d - Question: %s\n", i + 1, cards[i].question);
        printf("Press Enter to see the answer...\n");
        getchar();
        
        printf("Answer: %s\n", cards[i].answer);
        if (i < cardCount - 1) {
            printf("Press Enter for the next card...\n");
            getchar();
        }
    }
    
    printf("End of flashcards. Total cards: %d\n", cardCount);
    
    return 0;
}

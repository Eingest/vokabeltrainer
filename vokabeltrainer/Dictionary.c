//
//  Dictionary.c
//  vokabeltrainer
//
//  Created by Andreas Kiesel on 03.11.20.
//

#include "Dictionary.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

struct vocable *first = NULL;
struct vocable *current = NULL;
struct vocable *allocateMemory(void);

void clearBuffer(void) {
    
    while (getchar() != '\n') {
        
        ;
    }
}

void showMenuEdit(void) {
    
    puts("---------------------------");
    puts("Wähle aus, was du machen willst: ");
    puts("(A) Wörterbuch ansehen");
    puts("(B) Vokabel dem Wörterbuch hinzufügen");
    puts("(C) Vokabel aus dem Wörterbuch entfernen");
    puts("(D) Wörterbuch speichern");
    puts("(E) Bearbeiten beenden");
    puts("---------------------------");
}

void evaluateUserChoice(char choice) {
    
    switch (choice) {
            
        case 'A':
            puts("Wörterbuch ansehen");
            showDictionary();
            break;
        case 'B':
            puts("Vokabel dem Wörterbuch hinzufügen");
            addListItem();
            break;
        case 'C':
            puts("Vokabel aus dem Wörterbuch entfernen");
            removeListItem();
            break;
        case 'D':
            puts("Wörterbuch speichern");
            saveDictionary();
            break;
        case 'E':
            puts("Bearbeiten beenden");
            break;
        default:
            puts("Deine Eingabe war Murks!");
            break;
    }
}

struct vocable *allocateMemory(void) {
    
    struct vocable *pVocable = malloc(sizeof(struct vocable));
    
    if (!pVocable) {
        
        puts("malloc hat's nicht gepackt!");
        exit(1);
    }
    
    return pVocable;
}

void addListItem(void) {
    
    if (!first) {
        
        first = allocateMemory();
        current = first;
    }
    else {
        
        current = first;
        
        while (current->next) {
            
            current = current->next;
        }
        
        current->next = allocateMemory();
        current = current->next;
    }
    
    printf("english: ");
    scanf("%s", current->english);
    clearBuffer();
   
    printf("german: ");
    scanf("%s", current->german);
    clearBuffer();
    
    current->next = NULL;
    
    puts("Die Vokabel wurde deinem Wörterbuch erfolgreich hinzugefügt!");
    saveDictionary();
}

void showDictionary(void) {
    
    if (!first) { // wenn first == NULL
        
        puts("Was guckst du? Hier gibt's nichts zu sehen!");
        return;
    }
    
    int index = 1;
    current = first;
    
    puts("\nHIER IST DEIN WÖRTERBUCH:\n");
    while (current) {
        
        printf("No.%d: [%s - %s]\n", index++, current->english, current->german);
        current = current->next;
    }
}

void removeListItem(void) {
    
    if (!first) {
        
        puts("Wo nichts ist, da kannst du auch nichts entfernen");
        return;
    }
    
    struct vocable *prev = NULL;
    int removeItem;
    int count = 1;

eingabe:
    puts("Welchen Eintrag möchtest du entfernen?");
    showDictionary();
    scanf("%d", &removeItem);
    clearBuffer();
    
    if (removeItem < count) {
        
        goto eingabe;
    }
    
    current = first;
    
    while (count++ < removeItem) {
        
        prev = current;
        current = current->next;
        
        if (!current) {
            
            puts("Diesen Eintrag gibts nicht");
            return;
        }
    }
    
    if (!prev) { // prev == NULL
        
        first = current->next;
    }
    else {
        
        prev->next = current->next;
    }
    
    free(current);
    
    puts("Alles prima! Die Vokabel wurde aus dem Wörterbuch entfernt!");
    saveDictionary();
}

void saveDictionary(void) {
    
    FILE *fp = NULL;
    
    fp = fopen("dictionary.txt", "w");
    
    if (!fp) {
        
        puts("Die Datei konnte nicht geöffnet werden.\nDas Speichern des Wörterbuchs ist fehlgeschlagen.");
        exit(1);
    }
    
    current = first;
    
    while (current) {
        fprintf(fp, "%s %s\n ", current->english, current->german);
        current = current->next;
    }
    
    fclose(fp);
    
    puts("Gratuliere! Das Wörterbuch wurde soeben gespeichert!");
}

int readDictionaryFromFile(void) {
    
    FILE *fp = NULL;
    char temp[51];
    int vocableCount = 0;
    
    fp = fopen("dictionary.txt", "r");
    
    if (!fp) {
        
        return -1;
    }
    
    if (fscanf(fp, "%s", temp) != EOF) {
        
        vocableCount++;
        first = allocateMemory();
        current = first;
        
        strcpy(current->english, temp);
        fscanf(fp, "%s", temp);
        strcpy(current->german, temp);
        current->next = NULL;
        
        while (fscanf(fp, "%s", temp) != EOF) {
            
            vocableCount++;
            current->next = allocateMemory();
            current = current->next;
            
            strcpy(current->english, temp);
            fscanf(fp, "%s", temp);
            strcpy(current->german, temp);
            current->next = NULL;
        }
    }
    
    fclose(fp);
    
    return vocableCount;
}

void dictionaryBearbeiten(void) {
    
    char choice;
    
    do {
        
        showMenuEdit();
        
        choice = getchar();
        clearBuffer();
        choice = toupper(choice);
        
        evaluateUserChoice(choice);
        
    } while (choice != 'E');
}

void vokabeltrainer(void) {
    
    int auswahl = -1;
    int count = readDictionaryFromFile();

    
    for ( ; auswahl != 0; ) { //endlosschleife, solange nicht '0' gedrückt wird
        
        puts("---------------------------");
        puts("Wähle aus, was du machen willst: ");
        puts("(1) Vokabeln trainieren");
        puts("(2) Wörterbuch anlegen oder bearbeiten");
        puts("(0) Nichts tun und Kuchen essen");
        puts("---------------------------");
        
        scanf("%d", &auswahl);
        clearBuffer();
        
        switch (auswahl) {
                
            case 1:
                puts("Vokabeln tranieren");
                trainingVokabeln(count);
                break;
            case 2:
                puts("Wörterbuch anlegen oder bearbeteiten");
                dictionaryBearbeiten();
                break;
            case 0:
                puts("Okay, du hast heute frei...");
                break;
            default:
                puts("Deine Eingabe ist ungültig");
                break;
        }
    }
}

void trainingVokabeln(int count) {
    
    printf("Das Wörterbuch enthält %d %s\n", count, (count == 1) ? "Eintrag":"Einträge"); //wenn count = 1, dann 'Eintrag', wenn nicht 1 ist, dann 'Einträge'
    
    if (!first) {
        
        return;
    }
    
    int randomNumber;
    int training = 1;
    int i;
    int trainingIndex = 0;
    char answer[51];
    srand((unsigned int) time(NULL));
    
    while (training) {
        
        randomNumber = rand() % count + 1;
        current = first;
        
        for (i = 1; i < randomNumber; i++) {
            
            current = current->next;
        }
        
        printf("Gib die deutsche Übersetzung ein:\n");
        printf("[No.%d]: %s\nAntwort: ", ++trainingIndex, current->english);
        scanf("%s", answer);
        clearBuffer();
        
        if (strcasecmp(current->german, answer) == 0) {
            
            puts("Super! Deine Antwort war richtig!");
        }
        else {
            puts("Deine Antwort war leider falsch!");
        }
        
        if (trainingIndex >= 10) {
            
            trainingIndex = 0;
            printf("Möchtest du weitermachen? (0 = Abbruch)\n");
            scanf("%d", &training);
            clearBuffer();
        }
    }
}

// Idee: Variable, die die Häufigkeit der abgefragten UND richtigen Wörter zählt

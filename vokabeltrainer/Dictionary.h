//
//  Dictionary.h
//  vokabeltrainer
//
//  Created by Andreas Kiesel on 03.11.20.
//

#ifndef Dictionary_h
#define Dictionary_h

#include <stdio.h>

struct vocable {
    
    char english[51];
    char german[51];
    struct vocable *next; //zeigt auf das nächste element in der verketteten liste
};

void clearBuffer(void);
void showMenuEdit(void);
void evaluateUserChoice(char);
void addListItem(void);
void showDictionary(void);
void removeListItem(void);
void saveDictionary(void);
int readDictionaryFromFile(void);
void dictionaryBearbeiten(void);
void vokabeltrainer(void);
void trainingVokabeln(int);

#endif /* Dictionary_h */

#ifndef MISFUNCIONES_H_INCLUDED
#define MISFUNCIONES_H_INCLUDED

#ifdef __linux__
#define SO "Linux"
#elif _WIN32
#define SO "Windows"
#elif _WIN64
#define SO "MsWindows"
#endif

char stringToLwr(char* str);
char stringToUpper(char* str);
char charToLwr(char* Char);
char charToUppr(char Char);
void removeNewLine(char* string);
void removeNewLines(char* string);
void upInitialCharString (char *str);
void sortVectorUp(char vec[], int tam);
void sortVectorDown(char vec[], int tam);
void sortVectorChar(char vec[], int tam);
int getInt(char msj[], char error[], int limInf, int limSup, int attemp);
void getString(char* string, int lengh);
void osDetect(char* string);
void wait(char* string);
int optionValid();
int intValid(char* string);
int openFileReadAppend(char* string);
int openFileWrite(char* string);
int validNULL(void* string);
char reply(char* string);




#endif // MISFUNCIONES_H_INCLUDED

#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#define MASCARA_ARCHIVO "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n"
#define BUFFER buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6]
#define HEADER "file,name,lastName,sex,salary,idSection,isEmpty\n"
#define MASC "%d,%s,%s,%c,%.2f,%d,%d\n"
#define TAM_SECTION 5
#define FREE 0
#define BUSY 1


typedef struct{

int file;
char name[51];
char lastName[51];
char sex;
float salary;
int idSection;
int isEmpty;

}Employee;

typedef struct{

int id;
char description[25];

}Section;


#endif // EMPLOYEE_H_INCLUDED

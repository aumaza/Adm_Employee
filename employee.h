#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>



#include "ArrayList.h"


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



//prototipos

//funciones sobre los archivos
void employeeParser(char* path, ArrayList* lista);
void saveEmployee(char* path, ArrayList* lista);
int  searchEmployee(ArrayList* lista, int file);


//funciones de mostrar datos
void showEmployee(Employee* pEmployee, Section* pSection, int tamSection);
void showEmployees(ArrayList* lista, Section* pSection, int tamSection);
void showGreatestSalary(ArrayList* lista, Section* pSection, int tamSection);
void sortEmployeeSalary(ArrayList* lista,Section* pSection,int tamSection);
void sortEmployeeName(ArrayList* lista,Section* pSection,int tamSection);
void sortEmployeeSection(ArrayList* lista, Section* pSection,int tamSection);
void sortEmployeeSex(ArrayList* lista, Section* pSection, int tamSection);
void showSalaryPromBySector(ArrayList* lista, Section* pSection, int tamSection);


void loadDescription(Section* pSection, int tamSection, int x, char* string);
void addEmployee(ArrayList* lista, Section* pSection, int tamSection);
int selectSection(Section* pSection, int tamSection);

//funciones de administracion de datos
void eraseEmployee(ArrayList* lista, Section* pSection, int tamSection);
void editEmployeeSalary(ArrayList* lista, Section* pSection, int tamSection);
void editEmployeeName(ArrayList* lista, Section* pSection, int tamSection);
void editEmployeeLastName(ArrayList* lista, Section* pSection, int tamSection);
void editEmployeeSex(ArrayList* lista, Section* pSection, int tamSection);
void editEmployeeIdeSection(ArrayList* lista, Section* pSection, int tamSection);


//constructores
Employee* newEmployee();
Section* newSection();
void hardcoreSection(Section* pSection);
int cmpEmployeeSalary(void* x, void* y);
int cmpEmployeeName(void* x, void* y);
int cmpEmployeeSection(void* x, void* y);
int cmpEmployeeSex(void* x, void* y);

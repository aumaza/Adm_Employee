#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "misFunciones.h"
#include "employee.h"
#include "ArrayList.h"
#include "misFunciones.h"
#include "employee.h"





int cmpEmployeeName(void* x, void* y)
{

    Employee* emp1 = (Employee*)x;
    Employee* emp2 = (Employee*)y;

    return strcmp(emp1->name, emp2->name);

}

int cmpEmployeeSalary(void* x, void* y)
{

 Employee* emp1 = (Employee*)x;
 Employee* emp2 = (Employee*)y;

 int retorno;

  if(emp1->salary == emp2->salary){

    retorno = 0;
  }
  else if( emp1->salary > emp2->salary){

    retorno = 1;
  }
  else{
    retorno = -1;
  }

  return retorno;

}


int cmpEmployeeSection(void* x, void* y)
{

 Employee* emp1 = (Employee*)x;
 Employee* emp2 = (Employee*)y;

 int retorno;

  if(emp1->idSection == emp2->idSection){

    retorno = 0;
  }
  else if( emp1->idSection > emp2->idSection)
  {

    retorno = 1;
  }
  else{
    retorno = -1;
  }

  return retorno;

}


int cmpEmployeeSex(void* x, void* y)
{

 Employee* emp1 = (Employee*)x;
 Employee* emp2 = (Employee*)y;

 int retorno;

  if(emp1->sex == emp2->sex){

    retorno = 0;
  }
  else if( emp1->sex > emp2->sex)
  {

    retorno = 1;
  }
  else{
    retorno = -1;
  }

  return retorno;

}



void hardcoreSection(Section* pSection)
{
    int i;
    Section eSection[]=
    {
        {1,"RR.HH"},
        {2,"SISTEMAS"},
        {3,"CONTABILIDAD"},
        {4,"ADMINISTRACION"},
        {5,"LEGALES"},
    };

    for(i=0; i<5; i++)
    {
        *(pSection+i) = eSection[i];
    }

}

void employeeParser(char* path, ArrayList* lista)
{
    FILE* fp;

    Employee* nEmployee;

    int cant;
    char buffer[7][128];
    fp=fopen(path, "a+");

    if(fp != NULL && lista != NULL)
    {
        fscanf(fp,MASCARA_ARCHIVO,BUFFER);

        while(!feof(fp))
        {
            cant = fscanf(fp,MASCARA_ARCHIVO,BUFFER);

            if( cant == 7)
            {
                nEmployee = newEmployee();

                if(nEmployee != NULL)
                {
                    nEmployee->file = atoi(buffer[0]);
                    strcpy(nEmployee->name,buffer[1]);
                    strcpy(nEmployee->lastName,buffer[2]);
                    nEmployee->sex = buffer[3][0];
                    nEmployee->salary = atoi(buffer[4]);
                    nEmployee->idSection = atoi(buffer[5]);
                    nEmployee->isEmpty = atoi(buffer[6]);

                    lista->add(lista,nEmployee);
                }
            }
            else
            {
                break;
            }
        }
        fclose(fp);
    }
}


void saveEmployee(char* path, ArrayList* lista)
{
    FILE* fp;
    fp=fopen(path,"w");
    Employee* nEmployee;

    if(fp != NULL)
    {
        fprintf(fp,HEADER);

        for(int i=0; i<lista->len(lista); i++)
        {
            nEmployee=(Employee*)lista->get(lista,i);
            fprintf(fp,MASC,nEmployee->file,nEmployee->name,nEmployee->lastName,nEmployee->sex,nEmployee->salary,nEmployee->idSection,nEmployee->isEmpty);

        }
        fclose(fp);
    }
}




Section* newSection()
{
    Section* newSection = (Section*)malloc(sizeof(Section));

    if(newSection != NULL)
    {
        newSection->id = 0;
        strcpy(newSection->description, "");
    }
    return newSection;
}





Employee* newEmployee()
{
    Employee* newEmployee = (Employee*)malloc(sizeof(Employee));

    if(newEmployee != NULL)
    {
        newEmployee->file = 0;
        strcpy(newEmployee->name, "");
        strcpy(newEmployee->lastName, "");
        newEmployee->sex = ' ';
        newEmployee->salary = 0;
        newEmployee->idSection = 0;
        newEmployee->isEmpty = 0;
    }

    return newEmployee;

}


int searchEmployee(ArrayList* lista, int file)
{
    int i;
    int index=-1;
    Employee* nEmployee;

    for(i=0; i<lista->len(lista); i++)
    {
        nEmployee=(Employee*)lista->get(lista,i);

        if(nEmployee->file == file && nEmployee->isEmpty == BUSY)
        {
            index=i;
            break;
        }

    }
    return index;
}


void addEmployee(ArrayList* lista, Section* pSection, int tamSection)
{
    osDetect(SO);

    Employee* nEmployee;


    int is;
    int file;


    printf("\n==============================================");
    printf("\n---------- A L T A  E M P L E A D O ----------");
    printf("\n==============================================\n");


    file = intValid("Ingrese legajo");


    is=searchEmployee(lista,file);


    if(is != -1)
    {
        osDetect(SO);
        printf("\nREGISTRO EXISTENTE!!");
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee((Employee*)lista->get(lista,is),pSection,tamSection);
        printf("\n========================================================================================");
        wait(SO);
    }

    else
    {
        nEmployee=newEmployee();

        if(nEmployee != NULL)
        {

            nEmployee->file = file;
            printf("Ingrese Nombre: ");
            fflush(stdin);
            fgets(nEmployee->name,51,stdin);
            removeNewLine(nEmployee->name);
            stringToUpper(nEmployee->name);

            printf("Ingrese Apellido: ");
            fflush(stdin);
            fgets(nEmployee->lastName,51,stdin);
            removeNewLine(nEmployee->lastName);
            stringToUpper(nEmployee->lastName);

            printf("Ingrese Sexo(f/m): ");
            fflush(stdin);
            scanf("%c",&nEmployee->sex);
            nEmployee->sex = toupper(nEmployee->sex);


            printf("Ingrese Salario: ");
            fflush(stdin);
            scanf("%f", &nEmployee->salary);

            nEmployee->idSection = selectSection(pSection,tamSection);

            nEmployee->isEmpty = 1;

            lista->add(lista,nEmployee);

        }
      }
   }





void showEmployee(Employee* pEmployee, Section* pSection, int tamSection)
{
    char description[20];

    loadDescription(pSection, tamSection,pEmployee->idSection,description);

    printf("\n%d", pEmployee->file);
    printf("\t%12s", pEmployee->name);
    printf("\t%15s", pEmployee->lastName);
    printf("\t%10c", pEmployee->sex);
    printf("\t%8.2f", pEmployee->salary);
    printf("\t%6s", description);

}


void loadDescription(Section* pSection, int tamSection, int x, char* string)
{
    for(int i=0; i<tamSection; i++)
    {
        if((pSection[i].id) == x)
        {
            strcpy(string, pSection[i].description);
            break;
        }
    }
}


int selectSection(Section* pSection, int tamSection)
{
    int i;
    int idSection;
    osDetect(SO);

    printf("\n-------- Sectores --------\n");
    for(i=0; i<tamSection; i++)
    {
        printf("  %d %s\n", pSection[i].id, pSection[i].description);
    }
    idSection = getInt("Ingrese el Sector a Buscar: ","SECTOR INEXISTENTE!",1,5,5);

    return idSection;
}


void showEmployees(ArrayList* lista, Section* pSection, int tamSection)
{
    osDetect(SO);

    int i;
    Employee* oneEmployee;

    printf("\n========================================================================================");
    printf("\n--------------------------------- E M P L E A D O S ------------------------------------");
    printf("\n========================================================================================");
    printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
    printf("\n========================================================================================");

    for(i=0; i<lista->len(lista); i++)
    {
        oneEmployee = (Employee*)lista->get(lista, i);

        if(oneEmployee->isEmpty == 1)
        {

            showEmployee(oneEmployee, pSection, tamSection);
        }

    }
    printf("\n========================================================================================\n");

    wait(SO);

}



void eraseEmployee(ArrayList* lista, Section* pSection, int tamSection)
{
    osDetect(SO);

    int file;
    int index;
    char resp;
    Employee* oneEmployee;

    printf("=====================================\n");
    printf("---------- Borrar Empleado ----------\n");
    printf("=====================================\n");
    file = intValid("Ingrese Legajo");

    index = searchEmployee(lista,file);

    if( index == -1)
    {
        printf("NO EXISTE EL NUMERO DE LEGAJO: %d\n", file);
    }
    else
    {
        printf("\nEmpleado encontrado!!!\n\n");
        oneEmployee = (Employee*)lista->get(lista,index);
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");

        resp = reply("Desea borrar? s/n: ");

        if(resp != 's')
        {
            printf("Borrado cancelado\n\n");
        }
        else
        {
            oneEmployee->isEmpty = 0;
            printf("SE HA ELIMINADO EL REGISTRO\n");
        }
        wait(SO);
    }

}


void editEmployeeSalary(ArrayList* lista, Section* pSection, int tamSection)
{

    int file;
    int index;
    char resp;
    float newSalary;
    Employee* oneEmployee;

    osDetect(SO);

    file = intValid("Ingrese Legajo");

    index = searchEmployee(lista,file);

    if( index == -1)
    {
        printf("NO EXISTE EL NUMERO DE LEGAJO: %d\n", file);
    }
    else
    {
        oneEmployee = (Employee*)lista->get(lista,index);
        printf("\nREGISTRO EXISTENTE!!");
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");

        resp = reply("Modifica sueldo? s/n: ");

        if(resp != 's')
        {
            printf("Modificacion cancelada\n\n");
        }
        else
        {
            printf("Ingrese nuevo sueldo: ");
            scanf("%f", &newSalary);

            oneEmployee->salary = newSalary;
            printf("SALARIO MODIFICADO CON EXITO\n");
        wait(SO);
        osDetect(SO);

        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");
        }

        wait(SO);
    }

}


void editEmployeeName(ArrayList* lista, Section* pSection, int tamSection)
{

    int file;
    int index;
    char resp;
    char newName[51];
    Employee* oneEmployee;

    osDetect(SO);

    file = intValid("Ingrese Legajo");

    index = searchEmployee(lista,file);

    if( index == -1)
    {
        printf("NO EXISTE EL NUMERO DE LEGAJO: %d\n", file);
    }
    else
    {
        oneEmployee = (Employee*)lista->get(lista,index);
        printf("\nREGISTRO EXISTENTE!!");
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");

        resp = reply("Modifica Nombre? s/n: ");

        if(resp != 's')
        {
            printf("Modificacion cancelada\n\n");
        }
        else
        {
            printf("Ingrese nuevo Nombre: ");
            fflush(stdin);
            fgets(newName,51,stdin);
            removeNewLine(newName);
            stringToUpper(newName);

            strcpy(oneEmployee->name,newName);

            printf("NOMBRE MODIFICADO CON EXITO\n");
            wait(SO);
        osDetect(SO);
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");
        }

        wait(SO);
    }
}


void editEmployeeLastName(ArrayList* lista, Section* pSection, int tamSection)
{

    int file;
    int index;
    char resp;
    char newLastName[51];
    Employee* oneEmployee;

    osDetect(SO);

    file = intValid("Ingrese Legajo");

    index = searchEmployee(lista,file);

    if( index == -1)
    {
        printf("NO EXISTE EL NUMERO DE LEGAJO: %d\n", file);
    }
    else
    {
        oneEmployee = (Employee*)lista->get(lista,index);

        printf("\nREGISTRO EXISTENTE!!");
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");

        resp = reply("Modifica Apellido? s/n: ");

        if(resp != 's')
        {
            printf("Modificacion cancelada\n\n");
        }
        else
        {
            printf("Ingrese nuevo Apellido: ");
            fflush(stdin);
            fgets(newLastName,51,stdin);
            removeNewLine(newLastName);
            stringToUpper(newLastName);
            strcpy(oneEmployee->lastName,newLastName);

            printf("APELLIDO MODIFICADO CON EXITO\n");
            wait(SO);
            osDetect(SO);

        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");
        }

        wait(SO);
    }

}


void editEmployeeSex(ArrayList* lista, Section* pSection, int tamSection)
{

    int file;
    int index;
    char resp;
    char newSex;
    Employee* oneEmployee;

    osDetect(SO);

    file = intValid("Ingrese Legajo");

    index = searchEmployee(lista,file);

    if( index == -1)
    {
        printf("NO EXISTE EL NUMERO DE LEGAJO: %d\n", file);
    }
    else
    {
        oneEmployee = (Employee*)lista->get(lista,index);

        printf("\nREGISTRO EXISTENTE!!");
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");

        resp = reply("Modifica Sexo? s/n: ");

        if(resp != 's')
        {
            printf("Modificacion cancelada\n\n");
        }
        else
        {
            printf("Ingrese Sexo: ");
            getchar();
            scanf("%c",&newSex);
            newSex=toupper(newSex);

            oneEmployee->sex = newSex;

            printf("SEXO MODIFICADO CON EXITO\n");
            wait(SO);
            osDetect(SO);

        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");
        }

        wait(SO);
    }
}


void editEmployeeIdeSection(ArrayList* lista, Section* pSection, int tamSection)
{

    int file;
    int index;
    char resp;
    int newIdSection;
    Employee* oneEmployee;

    osDetect(SO);

    file = intValid("Ingrese Legajo");

    index = searchEmployee(lista,file);

    if( index == -1)
    {
        printf("NO EXISTE EL NUMERO DE LEGAJO: %d\n", file);
    }
    else
    {
        oneEmployee = (Employee*)lista->get(lista,index);
        printf("\nREGISTRO EXISTENTE!!");
        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");

        resp = reply("Modifica Sector? s/n: ");

        if(resp != 's')
        {
            printf("Modificacion cancelada\n\n");
        }
        else
        {

            newIdSection = selectSection(pSection,tamSection);

            oneEmployee->idSection = newIdSection;

            printf("SECTOR MODIFICADO CON EXITO\n");
            wait(SO);
            osDetect(SO);

        printf("\n========================================================================================");
        printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
        printf("\n========================================================================================");
        showEmployee(oneEmployee,pSection,tamSection);
        printf("\n========================================================================================");
        }

        wait(SO);
    }

}


void showGreatestSalary(ArrayList* lista, Section* pSection, int tamSection)
{
    osDetect(SO);
    Employee* oneEmployee;

    int flag;
    float maxSalary=0;
    char description[20];
    int i;
    int j;


                printf("\n========================================================================================");
                printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
                printf("\n========================================================================================");

    for(i=0; i <tamSection; i++)
    {
        loadDescription(pSection,tamSection,pSection->id,description);
        flag=0;

        for(j=0; j <lista->len(lista); j++)
        {
            oneEmployee = (Employee*)lista->get(lista,j);

            if((oneEmployee->salary > maxSalary && oneEmployee->isEmpty == 1 && oneEmployee->idSection == pSection[i].id) || (flag == 0 && oneEmployee->isEmpty == 1 && oneEmployee->idSection == pSection[i].id) )
            {
                maxSalary = oneEmployee->salary;
                flag = 1;
            }
        }


        for(j=0; j <lista->len(lista); j++)
        {
            oneEmployee = (Employee*)lista->get(lista,j);

            if( oneEmployee->salary == maxSalary && oneEmployee->idSection == pSection[i].id)// &&  oneEmployee->isEmpty == 1)
            {
                showEmployee(oneEmployee,pSection,tamSection);

            }
        }
    }
                printf("\n========================================================================================\n");
wait(SO);
}





void showSalaryPromBySector(ArrayList* lista, Section* pSection, int tamSection)
{
    int i;
    int idSection;
    char description[20];
    float sumSalary=0;
    float prom=0;
    int count=0;

    Employee* oneEmployee;

    idSection = selectSection(pSection,tamSection);

    osDetect(SO);
    printf("\n========================================================================================");
    printf("\n-------------------------------- E M P L E A D O S -------------------------------------");
    printf("\n========================================================================================");
    printf("\nLegajo    \tNombre    \tApellido  \tSexo  \tSalario   \tSector");
    printf("\n========================================================================================\n");

    for(i=0; i<lista->len(lista); i++)
    {
        loadDescription(pSection,tamSection,idSection,description);
        oneEmployee = (Employee*)lista->get(lista,i);


        if(oneEmployee->isEmpty == 1 && oneEmployee->idSection == idSection )
        {
            sumSalary+=oneEmployee->salary;
            count++;
            showEmployee(oneEmployee, pSection,tamSection);
        }
    }

    prom=sumSalary/count;
    printf("\n\n========================================================================================\n");
    printf("\nTOTAL DE SALARIOS DEL SECTOR: %.2f", sumSalary);
    printf("\n========================================================================================\n");
    printf("\nEL PROMEDIO DE SUELDOS DEL SECTOR %s ES: %.2f", description, prom);
    printf("\n========================================================================================\n");

    if( count == 0)
    {
        printf("NO HAY EMPLEADOS EN EL SECTOR %s\n\n", description);
    }

    wait(SO);
}

void sortEmployeeSalary(ArrayList* lista,Section* pSection,int tamSection)
{
        lista->sort(lista,cmpEmployeeSalary,1 );
        showEmployees(lista, pSection,tamSection);
}

void sortEmployeeName(ArrayList* lista,Section* pSection,int tamSection)
{

    lista->sort(lista,cmpEmployeeName,1 );
    showEmployees(lista, pSection,tamSection);
}

void sortEmployeeSection(ArrayList* lista, Section* pSection,int tamSection)
{
        lista->sort(lista,cmpEmployeeSection,1);
        showEmployees(lista,pSection,tamSection);
}

void sortEmployeeSex(ArrayList* lista, Section* pSection, int tamSection)
{
    lista->sort(lista,cmpEmployeeSex,1);
    showEmployees(lista,pSection,tamSection);
}

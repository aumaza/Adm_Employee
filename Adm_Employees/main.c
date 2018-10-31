#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "misFunciones.h"
#include "employee.h"
#include "ArrayList.h"




int main()
{
    ArrayList* list = al_newArrayList();
    // ArrayList* list2 = al_newArrayList();
    validNULL(list);

    Section eSection, *pSection;
    pSection=&eSection;
    pSection=(Section*)malloc(sizeof(eSection)*TAM_SECTION);
    hardcoreSection(pSection);

    employeeParser("empleados.csv",list);


    int opc;
    do
    {
        osDetect(SO);
        printf("\n=====================================");
        printf("\n--------------- M E N U -------------");
        printf("\n=====================================");
        printf("\n1. Altas");
        printf("\n=====================================");
        printf("\n2. Bajas");
        printf("\n=====================================");
        printf("\n3. Modificaciones");
        /*printf("\n4. Modificar Apellido Empleado");
        printf("\n5. Modificar Sector Empleado");
        printf("\n6. Modificar Salario");
        printf("\n7. Modificar Sexo");*/
        printf("\n=====================================");
        printf("\n4. Informes");
        printf("\n=====================================");
        printf("\n5. Guardar Datos");
        printf("\n=====================================");
        printf("\n6. Salir");
        opc=optionValid();


        switch(opc)
        {

        case 1:
            addEmployee(list,pSection,TAM_SECTION);
            break;

        case 2:
            eraseEmployee(list,pSection,TAM_SECTION);
            break;

        case 3:

            osDetect(SO);
            int op;

            do
            {
                osDetect(SO);

                printf("\n======================================");
                printf("\nSeleccione la Operacion a Realizar");
                printf("\n======================================\n");
                printf("\n1. Modificar Nombre Empleado");
                printf("\n2. Modificar Apellido Empleado");
                printf("\n3. Modificar Sector Empleado");
                printf("\n4. Modificar Salario");
                printf("\n5. Modificar Sexo");
                printf("\n6. Salir");
                printf("\n\n======================================\n");

                op=optionValid();
                printf("\n======================================\n");

                switch(op)
                {

                case 1:
                    editEmployeeName(list,pSection,TAM_SECTION);
                    break;
                case 2:
                    editEmployeeLastName(list,pSection,TAM_SECTION);
                    break;
                case 3:
                    editEmployeeIdeSection(list,pSection,TAM_SECTION);
                    break;
                case 4:
                    editEmployeeSalary(list,pSection,TAM_SECTION);
                    break;
                case 5:
                    editEmployeeSex(list,pSection,TAM_SECTION);
                    break;

                }
            }
            while(op != 6);
            break;


        case 4:

            osDetect(SO);
            int opcion;

            do
            {
                osDetect(SO);

                printf("\n======================================");
                printf("\nSeleccione la Operacion a Realizar");
                printf("\n======================================\n");
                printf("\n1. Listar Empleados");
                printf("\n2. Listar Empleados de Mayor Salario");
                printf("\n3. Listar Ordenado por Salario");
                printf("\n4. Listar Promedio de Salario por Sector");
                printf("\n5. Listar Alfabeticamente");
                printf("\n6. Listar por Sector");
                printf("\n7. Listar por Sexo");
                printf("\n\n======================================\n");
                printf("\n8. Salir");

                opcion=optionValid();
                printf("\n======================================\n");

                switch(opcion)
                {
                case 1:
                    showEmployees(list, pSection,TAM_SECTION);
                    break;
                case 2:
                    showGreatestSalary(list,pSection,TAM_SECTION);
                    break;
                case 3:
                    sortEmployeeSalary(list,pSection,TAM_SECTION);
                    break;
                case 4:
                    showSalaryPromBySector(list,pSection,TAM_SECTION);
                    break;
                case 5:
                    sortEmployeeName(list,pSection,TAM_SECTION);
                    break;
                case 6:
                    sortEmployeeSection(list,pSection,TAM_SECTION);
                    break;
                case 7:
                    sortEmployeeSex(list,pSection,TAM_SECTION);
                    break;
                }
            }
            while(opcion != 8);
            break;

        case 5:
            saveEmployee("empleados.csv",list);
            break;

        }

    }
    while(opc != 6);

    return 0;
}










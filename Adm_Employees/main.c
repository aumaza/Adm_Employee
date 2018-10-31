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
    printf("\n3. Modificar Nombre Empleado");
    printf("\n4. Modificar Apellido Empleado");
    printf("\n5. Modificar Sector Empleado");
    printf("\n6. Modificar Salario");
    printf("\n7. Modificar Sexo");
    printf("\n=====================================");
    printf("\n8. Listar");
    printf("\n9. Listar Empleados de Mayor Salario");
    printf("\n10. Listar Ordenado por salarios");
    printf("\n11. Promedios de Salarios por Sector");
    printf("\n12. Listar Alfabeticamente");
    printf("\n=====================================");
    printf("\n13. Guardar Datos");
    printf("\n=====================================");
    printf("\n14. Salir");
    opc=optionValid();


        switch(opc)
        {

        case 1: addEmployee(list,pSection,TAM_SECTION); break;

        case 2: eraseEmployee(list,pSection,TAM_SECTION); break;

        case 3: editEmployeeName(list,pSection,TAM_SECTION); break;

        case 4: editEmployeeLastName(list,pSection,TAM_SECTION); break;

        case 5: editEmployeeIdeSection(list,pSection,TAM_SECTION); break;

        case 6: editEmployeeSalary(list,pSection,TAM_SECTION); break;

        case 7: editEmployeeSex(list,pSection,TAM_SECTION); break;

        case 8: showEmployees(list, pSection,TAM_SECTION); break;

        case 9: showGreatestSalary(list,pSection,TAM_SECTION); break;

        case 10: list->sort(list,cmpEmployeeSalary,1 );
                 showEmployees(list, pSection,TAM_SECTION); break;

        case 11:  showSalaryPromBySector(list,pSection,TAM_SECTION); break;

        case 12:  list->sort(list,cmpEmployeeName,1 );
                  showEmployees(list, pSection,TAM_SECTION); break;

        case 13: saveEmployee("empleados.csv",list); break;
        }

    }while(opc != 14);



    return 0;
}










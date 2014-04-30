#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int dd;
    int mm;
    int aa;}t_fecha;

 typedef struct{
    char apellido[30];
    char nombre[30];
    t_fecha fnac;
    float prom;
    int p1;
    int p2;}t_alumno;

void cargaalum(FILE*,t_alumno);
void modifalum(FILE*,t_alumno);
void leealumn(FILE*,t_alumno);

void main()
{FILE*basealumno;
t_alumno varreg;
int opcion,salida=1;

while(salida!=0)
    {
    printf("Ingrese:\n\t 1-Crear base de datos.\n\t 2-Modificar base de datos.\n\t 3-Ver Base de datos\n\nOPCION: ");
    scanf("%d",&opcion);
    switch (opcion)
        {
        case 1 :
        basealumno=fopen("arch.dat","w+b");
        if(!basealumno)
            exit(1);
            else
                cargaalum(basealumno,varreg);
        break ;

        case 2 :
        basealumno=fopen("arch.dat","r+b");
        if(!basealumno)
            exit(1);
            else
                modifalum(basealumno,varreg);
        break ;

        case 3 :
        basealumno=fopen("arch.dat","rb");
            if(!basealumno)
                exit(1);
                else
                    leealum(basealumno,varreg);
        break ;

        default  :
        printf("\nOPCION INCORRECTA" );
        break ;}

fclose(basealumno);
printf("Ingrese opcion:\n\t0-Salir\n\t1-Continuar\n\nOPCION: ");
scanf("%d",&salida);
}
}

void cargaalum(FILE*basealumno,t_alumno varreg)
    {
    int salida=1;

    while(salida!=0)
        {system("cls");
        printf("Ingrese apellido: ");
        scanf("%s",varreg.apellido);
        printf("Ingrese nombre: ");
        scanf("%s",varreg.nombre);
        printf("Ingrese dia de nac.: ");
        scanf("%d",&varreg.fnac.dd);
        printf("Ingrese mes de nac.: ");
        scanf("%d",&varreg.fnac.mm);
        printf("Ingrese a�o de nac.: ");
        scanf("%d",&varreg.fnac.aa);
        printf("Ingrese nota de primero parcial: ");
        scanf("%d",&varreg.p1);
        printf("Ingrese nota de segundo parcial: ");
        scanf("%d",&varreg.p2);
        varreg.prom=(float)(varreg.p1 + varreg.p2)/2;
        fwrite(&varreg,sizeof(t_alumno),1,basealumno);
        printf("Para seguir ingresando alumnos ingrese '1', para salir '0': ");
        scanf("%d",&salida);
        }
}

void modifalum(FILE*basealumno,t_alumno varreg)
    {int opcion,nreg;
    system("cls");
    printf("Ingrese numero de registro a modificar: ");
    scanf("%d",&nreg);
    fseek(basealumno,sizeof(t_alumno)*(nreg-1),0);
    printf("Ingrese opcion para modificar:\n\t1-Modificar 1er parcial.\n\t2-Modificar 2do parcial.\n\nOPCION: ");
    scanf("%d",&opcion);

    if(opcion==1)
        {puts("Ingrese nota");
        fread(&varreg,sizeof(t_alumno),1,basealumno);
        scanf("%d",&varreg.p1);
        varreg.prom=(varreg.p1 + varreg.p2)/2;
        fseek(basealumno,-sizeof(t_alumno),1);
        fwrite(&varreg,sizeof(t_alumno),1,basealumno);
        fseek(basealumno,0,1);}
        else
            {puts("Ingrese nota");
            fread(&varreg,sizeof(t_alumno),1,basealumno);
            scanf("%d",&varreg.p2);
            fseek(basealumno,-sizeof(t_alumno),1);
            fwrite(&varreg,sizeof(t_alumno),1,basealumno);
            fseek(basealumno,0,1);}
}


void leealum(FILE*basealumno,t_alumno varreg)
    {   system("cls");
        fread(&varreg,sizeof(t_alumno),1,basealumno);
        feof(basealumno);
        printf("\nApellido: %s\nNombre: %s\nFecha Nac: %d/%d/%d\n1er parcial: %d\n2do parcial: %d\nProm.Final: %f\n\n",varreg.apellido,varreg.nombre,varreg.fnac.dd,varreg.fnac.mm,varreg.fnac.aa,varreg.p1,varreg.p2,varreg.prom);
        fread(&varreg,sizeof(t_alumno),1,basealumno);
        while(!feof(basealumno))
              {printf("\nApellido: %s\nNombre: %s\nFecha Nac: %d/%d/%d\n1er parcial: %d\n2do parcial: %d\nProm.Final: %f\n\n",varreg.apellido,varreg.nombre,varreg.fnac.dd,varreg.fnac.mm,varreg.fnac.aa,varreg.p1,varreg.p2,varreg.prom);
               fread(&varreg,sizeof(t_alumno),1,basealumno);
              }
    }




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 500
#define MAX_ID_LENGTH 500
#define MAX_DEPARTMENT_LENGTH 500
#define MAX_JOB_TITLE_LENGTH 500
#define MAX_EMPLOYEE_COUNT 200



typedef struct employee{
    char name[MAX_NAME_LENGTH];
    char id[MAX_ID_LENGTH];
    char department[MAX_DEPARTMENT_LENGTH];
    char jobTitle[MAX_JOB_TITLE_LENGTH];
    float salary;

} employee;

int employee_count = 0;

employee employees[MAX_EMPLOYEE_COUNT];


void scanEmployeeInfo(employee *param){
    printf("\nEnter employee Name: ");
    scanf(" %[^\n]", param->name);
    printf("\nEnter employee ID: ");
    scanf(" %[^\n]", param->id);
    printf("\nEnter employee Department: ");
    scanf(" %[^\n]", param->department);
    printf("\nEnter employee Job Title: ");
    scanf(" %[^\n]", param->jobTitle);
    printf("\nEnter employee salary: ");
    scanf(" %f", &param->salary);
}

void readEmployeeInfo(FILE *fileptr, employee *param){
    fscanf(fileptr, " %[^\n] ", param->name);
    fscanf(fileptr, " %[^\n] ", param->id);
    fscanf(fileptr, " %[^\n] ", param->department);
    fscanf(fileptr, " %[^\n] ", param->jobTitle);
    fscanf(fileptr, " %f ", &param->salary);
}

void printEmployeeInfo(employee *param){
    printf("%-25s: %-30s\n", "Employee Name", param->name);
    printf("%-25s: %-30s\n", "Employee ID", param->id);
    printf("%-25s: %-30s\n", "Department", param->department);
    printf("%-25s: %-30s\n", "Job Title", param->jobTitle);
    printf("%-25s: %-30.2f\n", "Salary", param->salary);

}

void writeEmployeeInfo(FILE *fileptr, employee *param){
    fprintf(fileptr, " %s\n", param->name);
    fprintf(fileptr, " %s\n", param->id);
    fprintf(fileptr, " %s\n", param->department);
    fprintf(fileptr, " %s\n", param->jobTitle);
    fprintf(fileptr, " %-.2f\n",  param->salary);

}

void fileOpenError(){
    printf("\nFile open error.\n");
    exit(0);
}

void loadEmployeeInfo(){
    FILE *fileptr = fopen("data.dat", "r");
    if (fileptr == NULL )fileOpenError();

    int employee_count_from_file;

    fscanf(fileptr, " %d", &employee_count_from_file);

    for(int i=0; i<employee_count_from_file; i++){
        readEmployeeInfo(fileptr, &employees[i + employee_count]);
    }

    employee_count += employee_count_from_file;

    fclose(fileptr);

    printf("\nSuccessfully loaded.\n");
}

void saveEmployeeInfo(){
    FILE *fileptr = fopen("data.dat", "w");
    if (fileptr == NULL )fileOpenError();

    fprintf(fileptr, " %d\n", employee_count);

    for(int i=0; i<employee_count; i++){
        writeEmployeeInfo(fileptr, &employees[i]);
    }

    fclose(fileptr);
    printf("\nSuccessfully Saved.\n");
}

int searchByName(char *name){
    for(int i=0; i < employee_count; i++){
        if(strcmp(name, employees[i].name) == 0) return i;
    }
    return -1;
}

int searchById(char *id){
    for(int i=0; i < employee_count; i++){
        if(strcmp(id, employees[i].id) == 0) return i;
    }
    return -1;
}

int (*search[])(char *param) = {
    searchByName,
    searchById
};

int findEmployee(){

    int choice = 0, index = -1;
    char data[MAX_NAME_LENGTH];
    printf("\n1. Search By name.");
    printf("\n2. Search By ID.\n");
    printf("\nEnter Choice : ");

    scanf(" %d", &choice);

    if(choice < 0 || choice > 2){
        printf("\nInvalid choice.\n");
        return -1;
    }
    else {
        choice--;
        printf("\nEnter data: ");
        scanf(" %[^\n]", data);
        index =  search[choice](data);
    }
    return index;

}

void searchEmployee(){
    int index = findEmployee();
    if(index == -1)printf("\nEmployee not found.\n");
    else printEmployeeInfo( &employees[index]);
}

void viewAllEmployee(){
    for(int i = 0; i<employee_count; i++){
        printf("\nEmployee : %d\n",i+1);
        printf("---------------\n");
        printEmployeeInfo( &employees[i]);
    }
}

void addEmployee(){
    printf("\nProvide Employee Information\n");
    scanEmployeeInfo( &employees[employee_count]);
    employee_count++;

    printf("\nEmployee Added Successfully.\n");
}


void removeEmployee() {

    int index = findEmployee();

    if (index == -1) {
        printf("\nEmployee not found.\n");
        return;
    }

    for (int i = index; i < employee_count - 1; i++) {
        employees[i] = employees[i + 1];
    }

    employee_count--;

    printf("\nEmployee removed successfully.\n");
}



void help(){
    printf("\n1. Load data from file.");
    printf("\n2. Save data to file.");
    printf("\n3. Search employee Record.");
    printf("\n4. View All Employee.");
    printf("\n5. Add an Employee.");
    printf("\n6. Remove an Employee.");
    printf("\n7. View help.");
    printf("\n8. Clear Screen.");
    printf("\n9. Exit program.\n");
}

void clear_screen(){
    system("cls");
}

void quit_program(){
    printf("\nProgram Will terminate.\n");
    exit(0);
}


void (*options[])(void) = {
    loadEmployeeInfo,
    saveEmployeeInfo,
    searchEmployee,
    viewAllEmployee,
    addEmployee,
    removeEmployee,
    help,
    clear_screen,
    quit_program

};

int option_selector(){
    int opt;
    int valid_opt = ( sizeof(options)/sizeof(options[0]) );
    printf("\nSelect an option : ");
    scanf("%d", &opt);
    if(opt > valid_opt || opt<1){
        printf("\nInvalid Option Selected.\n");
    }
    else options[opt-1]();
}


int main(){
    printf("Program started\n");
    help();
    while(1){
        option_selector();
    }
}

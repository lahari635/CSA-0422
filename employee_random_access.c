// employee_random_access.c
// Menu-driven program to store/retrieve/update Employee records using random access (binary file).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"
#define MAX_NAME 50

typedef struct {
    int id;                 // unique ID (1..n)
    char name[MAX_NAME];
    int age;
    double salary;
    int active;             // 1 => record used, 0 => empty/deleted
} Employee;

// Write an employee at given record index (0-based)
int write_employee(FILE *fp, long index, Employee *e) {
    if (fseek(fp, index * sizeof(Employee), SEEK_SET) != 0) return -1;
    if (fwrite(e, sizeof(Employee), 1, fp) != 1) return -1;
    fflush(fp);
    return 0;
}

// Read an employee at given record index (0-based)
int read_employee(FILE *fp, long index, Employee *e) {
    if (fseek(fp, index * sizeof(Employee), SEEK_SET) != 0) return -1;
    if (fread(e, sizeof(Employee), 1, fp) != 1) return -1;
    return 0;
}

// Get file size (number of records)
long record_count(FILE *fp) {
    if (fseek(fp, 0, SEEK_END) != 0) return 0;
    long size = ftell(fp);
    return size / sizeof(Employee);
}

void add_employee() {
    FILE *fp = fopen(FILENAME, "r+b");
    if (!fp) fp = fopen(FILENAME, "w+b"); // create if not exists
    if (!fp) { perror("fopen"); return; }

    Employee e;
    printf("Enter id (positive int): ");
    scanf("%d", &e.id);
    getchar();
    printf("Enter name: ");
    fgets(e.name, MAX_NAME, stdin);
    e.name[strcspn(e.name, "\n")] = '\0';
    printf("Enter age: "); scanf("%d", &e.age);
    printf("Enter salary: "); scanf("%lf", &e.salary);
    e.active = 1;

    long index = record_count(fp); // append at end
    if (write_employee(fp, index, &e) == 0)
        printf("Employee added at record index %ld\n", index);
    else
        printf("Failed to add employee\n");

    fclose(fp);
}

void display_all() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { printf("No records yet.\n"); return; }

    long n = record_count(fp);
    Employee e;
    printf("Total records: %ld\n", n);
    for (long i = 0; i < n; ++i) {
        if (read_employee(fp, i, &e) == 0 && e.active) {
            printf("Index:%ld ID:%d Name:%s Age:%d Salary:%.2lf\n", i, e.id, e.name, e.age, e.salary);
        }
    }
    fclose(fp);
}

void read_by_index() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { printf("No records.\n"); return; }
    long idx;
    printf("Enter record index (0-based): ");
    scanf("%ld", &idx);

    long n = record_count(fp);
    if (idx < 0 || idx >= n) { printf("Invalid index. Range: 0 to %ld\n", n-1); fclose(fp); return; }

    Employee e;
    if (read_employee(fp, idx, &e) == 0 && e.active) {
        printf("Index:%ld ID:%d Name:%s Age:%d Salary:%.2lf\n", idx, e.id, e.name, e.age, e.salary);
    } else {
        printf("Record empty or read error.\n");
    }
    fclose(fp);
}

void update_by_index() {
    FILE *fp = fopen(FILENAME, "r+b");
    if (!fp) { printf("No records.\n"); return; }
    long idx;
    printf("Enter record index to update (0-based): ");
    scanf("%ld", &idx);

    long n = record_count(fp);
    if (idx < 0 || idx >= n) { printf("Invalid index. Range: 0 to %ld\n", n-1); fclose(fp); return; }

    Employee e;
    if (read_employee(fp, idx, &e) != 0) { printf("Read error.\n"); fclose(fp); return; }
    if (!e.active) { printf("Record is empty.\n"); fclose(fp); return; }

    printf("Current -> ID:%d Name:%s Age:%d Salary:%.2lf\n", e.id, e.name, e.age, e.salary);
    getchar();
    printf("Enter new name (leave empty to keep): ");
    char buf[MAX_NAME];
    fgets(buf, MAX_NAME, stdin);
    buf[strcspn(buf, "\n")] = '\0';
    if (strlen(buf)) strncpy(e.name, buf, MAX_NAME);

    printf("Enter new age (0 to keep): ");
    int a; scanf("%d", &a);
    if (a > 0) e.age = a;
    printf("Enter new salary (0 to keep): ");
    double s; scanf("%lf", &s);
    if (s > 0) e.salary = s;

    if (write_employee(fp, idx, &e) == 0) printf("Updated.\n"); else printf("Update failed.\n");
    fclose(fp);
}

void delete_by_index() {
    FILE *fp = fopen(FILENAME, "r+b");
    if (!fp) { printf("No records.\n"); return; }
    long idx; printf("Enter record index to delete (0-based): "); scanf("%ld", &idx);
    long n = record_count(fp);
    if (idx < 0 || idx >= n) { printf("Invalid index.\n"); fclose(fp); return; }
    Employee e;
    if (read_employee(fp, idx, &e) != 0) { printf("Read error.\n"); fclose(fp); return; }
    e.active = 0;
    if (write_employee(fp, idx, &e) == 0) printf("Deleted (marked inactive).\n"); else printf("Delete failed.\n");
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Employee Random Access ---\n");
        printf("1. Add employee\n2. Display all\n3. Read by index\n4. Update by index\n5. Delete by index (mark inactive)\n6. Exit\nChoice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: add_employee(); break;
            case 2: display_all(); break;
            case 3: read_by_index(); break;
            case 4: update_by_index(); break;
            case 5: delete_by_index(); break;
            case 6: exit(0);
            default: printf("Invalid.\n");
        }
    }
    return 0;
}

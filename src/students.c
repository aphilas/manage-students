#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

#define META_SIZE 4

typedef struct {
	char fName[50];
	char lName[50];
} Name;

typedef struct {
    Name name;
    int age;
} Student;

Vector *students;

Student *create_student(char *fName, char *lName, int age);
Student *get_student(int index);
void print_students();
int save_students();
int read_students();
void check_input(int expected, int got);

int main() {
    students = create(sizeof(Student));

    int option, std_count, age, student_check, save_ret, read_ret;
    char fName[50], lName[50];

    printf("Select an option\n1.Enter student details\n2.Manage student details\n");
    check_input(scanf("%d",&option), 1);

    switch (option) {
        case 1:
            printf("Enter number of students:\n");
            check_input(scanf("%d",&std_count), 1);

            for (int i = 0; i < std_count; i++) {
                printf("Enter <firstName lastName age>\n");
                student_check = scanf("%s %s %d", fName, lName, &age);

                if (student_check != 3) {
                    printf("Invalid format, skipping...");
                    break;
                }

                Student *student = create_student(fName, lName, age);
                free(student);
            }

            printf("Here is the list of students:\n");
            print_students();

            printf("Saving the list of students to \"input.bin\" ...\n");
            save_ret = save_students();

            if (save_ret > 0) {
                printf("There was an error saving the data\n");
            } else {
                printf("Success!\n");
            }

            break;
        case 2:
            printf("Trying to import students from \"input.bin\" ...\n");

            read_ret = read_students();

            if (read_ret > 0) {
                printf("There was an error reading the data\n");
            }

            break;
        default:
            printf("Unknown option\n");
    }

    clear(students);
    return 0;
}

void check_input(int expected, int got) {
    if (expected != got) {
        printf("Unexpected input, exiting...\n");
        exit(1);
    }
}

/**
 * @brief Create a student object.
 * Adds the students to the students vector and returns a pointer to the student object
 *
 * @param fName First name
 * @param lName Last name
 * @param age
 * @return Student*
 */
Student *create_student(char *fName, char *lName, int age) {
    Name name;
    Student *student = malloc(sizeof(Student));
    student->age=age;
    strcpy(student->name.fName, fName);
    strcpy(student->name.lName, lName);
    push(students, student);
    return student;
}

/**
 * @brief Get a student object by index
 *
 * @param index Index in array
 * @return Student*
 */
Student* get_student(int index) {
	Student *student;

    // O(n)
	student = (Student *) get(students, index);

	if (student == NULL) {
		return NULL;
	}

	return student;
}

/**
 * @brief Prints a list of all the students
 *
 */
void print_students() {
    Student *student;
    int count;
    count = students->used;

    printf("Count: %d\n", count);

	for (int i = 0; i < count; i++) {
		student = get_student(i);

		if (student == NULL) {
			continue;
		}

		printf("%s %s, %d\n", student->name.fName, student->name.lName, student->age);
	}
}

/**
 * @brief Saves students ([]Student) to file "input.bin"
 *
 * @return int
 */
int save_students() {
    int size;
    int count;
    FILE *data;

    if ((data = fopen("input.bin", "wb")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    size = students->unitSize;
    count = students->used;

    fwrite(&size, sizeof(int), 1, data); // size of struct
    fwrite(&count, sizeof(int), 1, data); // count of structs
    fwrite(students->data, sizeof(Student), count, data);
    fclose(data);

    return 0;
}

/**
 * @brief Reads students from "input.bin" and displays the info.
 *
 * @return int
 */
int read_students() {
    int count, size, count_read;
    FILE *data;
    Student *students;

    if ((data = fopen("input.bin", "rb")) == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fread(&size, META_SIZE, 1, data);
    fread(&count, META_SIZE, 1, data);

    printf("Showing %d student(s): \n", count);
    students = malloc(sizeof(Student) * count);
    count_read = fread(students, size, count, data);

    for (int n = 0; n < count; n++) {
        printf("%s %s, %d\n", students[n].name.fName, students[n].name.lName, students[n].age);
    }

    fclose(data);
    free(students);

    return 0;
}

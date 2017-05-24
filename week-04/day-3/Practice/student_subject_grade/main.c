#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {MATH, HISTORY, ENGLISH, SCIENCE} subject_t;

typedef struct {
    subject_t subject;
    int value;
} grade_t;

typedef struct {
    char name[128];
    int age;
    grade_t* grades;
    int grade_count;
} student_t;

// TODO:
// Create a function that constructs a Student (returns a pointer to a new student)
// It should take it's name and it's age as parameter
// It should allocate 5 grades
// It should set the grade_count to 0
student_t *a_student(char* name, int age)
{
    student_t *student = malloc(sizeof(student_t));
    strcpy(student->name, name);
    student->age = age;

    grade_t *grades = calloc(4, sizeof(grade_t));
    student->grades = grades;
    student->grade_count = 0;

    return student;
}
// TODO:
// Create a function that takes 3 parameters:
// A pointer to a Student
// A Subject
// An int (1-5)
// It should set the last grade's values with the given arguments
void add_grade(student_t *student, subject_t subject, int g)
{
    student->grades[student->grade_count].subject = subject;
    student->grades[student->grade_count].value = g;
    student->grade_count++;
}
// TODO:
// Create a function that takes a Student as a pointer and returns the subject
// that the student has worst grade in
subject_t worst_grade(student_t *student)
{
    int min = 5;
    for (int i = 0; i < student->grade_count; i++) {
        if(min > student->grades[i].value)
            min = student->grades[i].value;
    }

    for (int i = 0; i < student->grade_count; i++) {
        if(min == student->grades[i].value)
            return student->grades[i].subject;
    }
}
// TODO:
// Create a function that deconstructs a Student
// It should take a pointer that points to the student
// It should free each Grade and the Student itself
void destruct(student_t *student)
{
    free(student->grades);
    free(student);
}

int main()
{
    student_t* ili = a_student("Ili", 11);
    add_grade(ili, HISTORY, 5);
    add_grade(ili, ENGLISH, 1);
    add_grade(ili, SCIENCE, 3);

    printf("%s's worst grade subject is: %d\n", ili->name, worst_grade(ili));

    return 0;
}

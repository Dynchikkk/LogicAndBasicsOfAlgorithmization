#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 20

struct Student_s
{
	int gradebook;
	char surname[STRING_SIZE];
	char name[STRING_SIZE];
	char faculty[STRING_SIZE];
	

} StudentDefault = {-1, "\n", "\n", "\n" };

typedef struct Student_s Student;

Student CreateNewStudent()
{
	Student newStudent;
	printf("Insert student surname: ");
	fgets(newStudent.surname, sizeof(newStudent.surname), stdin);
	fseek(stdin, 0, SEEK_END);
	
	printf("Insert student name: "); 
	fgets(newStudent.name, sizeof(newStudent.name), stdin);
	fseek(stdin, 0, SEEK_END);

	printf("Insert student faculty: "); 
	fgets(newStudent.faculty, sizeof(newStudent.faculty), stdin);
	fseek(stdin, 0, SEEK_END);

	printf("Insert student's gradebook number: "); 
	scanf("%d", &newStudent.gradebook);
	fseek(stdin, 0, SEEK_END);

	return newStudent;
}

Student* FindSudentByName(Student* inst, int instSize, Student wantFind)
{
	Student tester = StudentDefault;

	for (int i = 0; i < instSize; i++)
	{
		Student cur = *(inst + i*sizeof(Student));
		if (strcmp(tester.name, wantFind.name) != 0)
			if (strcmp(cur.name, wantFind.name) != 0)
				continue;

		if (strcmp(tester.surname, wantFind.surname) != 0)
			if (strcmp(cur.surname, wantFind.surname) != 0)
				continue;

		if (strcmp(tester.faculty, wantFind.faculty) != 0)
			if (strcmp(cur.faculty, wantFind.faculty) != 0)
				continue;

		if (tester.gradebook != wantFind.gradebook)
			if (cur.gradebook != wantFind.gradebook)
				continue;

		return &cur;
	}

	return NULL;
}

void Part2()
{
	fseek(stdin, 0, SEEK_END);
	printf("----------\n");

	int instSize = 2;
	printf("Count od students: ");
	scanf("%d", &instSize);
	fseek(stdin, 0, SEEK_END);
	Student* institute = (Student*)malloc(instSize * sizeof(Student));
	for (int i = 0; i < instSize; i++)
	{
		printf("----------\n");
		*(institute + i* sizeof(Student)) = CreateNewStudent();
		printf("----------\n");
	}

	printf("----------\nWhat student do you want to find?\n");
	Student wantFind = CreateNewStudent();

	Student* finded = FindSudentByName(institute, instSize, wantFind);
	if (finded == NULL)
	{
		printf("No student with this params");
		printf("----------\n");
		return;
	}

	Student stud = *finded;
	printf("----------\n");
	printf("Student Finded:\nname %ssurname %sfaculty %sgradebook %d\n", stud.name, stud.surname, stud.faculty, stud.gradebook);
	printf("----------\n");
	printf("----------\n");

	free(institute);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
    int age;
    char name[50];
    char surname[50];
    char clas[50];
};

int compareStrings(const char *str1, const char *str2) {
    return strcmp(str1, str2);
}

int compareByName(const void *a, const void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return compareStrings(studentA->name, studentB->name);
}
int compareBySurname(const void *a, const void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return compareStrings(studentA->surname, studentB->surname);
}
int compareByAge(const void *a, const void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return studentA->age - studentB->age;
}
int compareByClass(const void *a, const void *b) {
    struct Student *studentA = (struct Student *)a;
    struct Student *studentB = (struct Student *)b;
    return compareStrings(studentA->clas, studentB->clas);
}

// Добавить
struct Student* addStudent(struct Student *students, int *size) {
    *size += 1;
    students = realloc(students, *size * sizeof(struct Student));

    printf("_____________________________________________\nВведите имя: ");
    scanf("%s", students[*size - 1].name);
    printf("Введите фамилию: ");
    scanf("%s", students[*size - 1].surname);
    printf("Введите возраст: ");
    scanf("%d", &students[*size - 1].age);
    printf("Введите класс: ");
    scanf("%s", students[*size - 1].clas);

    printf("_____________________________________________\nСтудент добавлен!\n");
    return students;
}

// Удалить 
struct Student* removeStudent(struct Student *students, int *size, int index) {
    if (index < 0 || index >= *size) {
        printf("Неверный индекс!\n");
        return students;
    }

    for (int i = index; i < *size - 1; i++) {
        students[i] = students[i + 1];
    }

    *size -= 1;
    students = realloc(students, *size * sizeof(struct Student));

    printf("_____________________________________________\nСтудент вырезан\n");
    return students;
}
// Изменить
void modifyStudent(struct Student *students, int size, int index) {
    if (index < 0 || index >= size) {
        printf("Неверный индекс!\n");
        return;
    }

    int choice;
    printf("_____________________________________________\nЧто вы хотите изменить у студента #%d?\n", index + 1);
    printf("1. Имя\n");
    printf("2. Фамилия\n");
    printf("3. Возраст\n");
    printf("4. Класс\n_____________________________________________\n");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("_____________________________________________\nВведите новое имя: ");
        scanf("%s", students[index].name);
    } else if (choice == 2) {
        printf("_____________________________________________\nВведите новую фамилию: ");
        scanf("%s", students[index].surname);
    } else if (choice == 3) {
        printf("_____________________________________________\nВведите новый возраст: ");
        scanf("%d", &students[index].age);
    } else if (choice == 4) {
        printf("_____________________________________________\nВведите новый класс: ");
        scanf("%s", students[index].clas);
    } else {
        printf("_____________________________________________\nНеверный выбор\n");
    }

    printf("_____________________________________________\nИнформация о студенте изменена!\n");
}

// Сортриовка
void sortStudents(struct Student *students, int size) {
    int sortChoice;
    printf("_____________________________________________\nПо какому критерию вы хотите сортировать?\n");
    printf("_____________________________________________\n1. Имя\n");
    printf("2. Фамилия\n");
    printf("3. Возраст\n");
    printf("4. Класс\n");
    scanf("%d", &sortChoice);

    int (*compareFunc)(const void *, const void *) = NULL;

    if (sortChoice == 1) {
        compareFunc = compareByName;
    } else if (sortChoice == 2) {
        compareFunc = compareBySurname;
    } else if (sortChoice == 3) {
        compareFunc = compareByAge;
    } else if (sortChoice == 4) {
        compareFunc = compareByClass;
    } else {
        printf("Неверный выбор!\n");
        return;
    }

    qsort(students, size, sizeof(struct Student), compareFunc);
    printf("_____________________________________________\nСписок студентов отсортирован!\n");
}

// Фильтрация
void filterStudents(struct Student *students, int size) {
    int filterChoice;
    printf("_____________________________________________\nПо какому критерию вы хотите фильтровать?\n");
    printf("1. Имя\n");
    printf("2. Фамилия\n");
    printf("3. Возраст\n");
    printf("4. Класс\n_____________________________________________\n");
    scanf("%d", &filterChoice);

    if (filterChoice == 1) {
        char nameFilter[50];
        printf("_____________________________________________\nВведите имя для фильтрации: ");
        scanf("%s", nameFilter);
        printf("_____________________________________________\nСтуденты с именем %s:\n", nameFilter);
        for (int i = 0; i < size; i++) {
            if (compareStrings(students[i].name, nameFilter) == 0) {
                printf("%s %s, возраст: %d, класс: %s\n", students[i].name, students[i].surname, students[i].age, students[i].clas);
            }
        }
    } else if (filterChoice == 2) {
        char surnameFilter[50];
        printf("_____________________________________________\nВведите фамилию для фильтрации: ");
        scanf("%s", surnameFilter);
        printf("_____________________________________________\nСтуденты с фамилией %s:\n", surnameFilter);
        for (int i = 0; i < size; i++) {
            if (compareStrings(students[i].surname, surnameFilter) == 0) {
                printf("%s %s, возраст: %d, класс: %s\n", students[i].name, students[i].surname, students[i].age, students[i].clas);
            }
        }
    } else if (filterChoice == 3) {
        int ageFilter;
        printf("_____________________________________________\nВведите возраст для фильтрации: ");
        scanf("%d", &ageFilter);
        printf("_____________________________________________\nСтуденты с возрастом %d:\n", ageFilter);
        for (int i = 0; i < size; i++) {
            if (students[i].age == ageFilter) {
                printf("%s %s, возраст: %d, класс: %s\n", students[i].name, students[i].surname, students[i].age, students[i].clas);
            }
        }
    } else if (filterChoice == 4) {
        char classFilter[50];
        printf("_____________________________________________\nВведите класс для фильтрации: ");
        scanf("%s", classFilter);
        printf("_____________________________________________\nСтуденты из класса %s:\n", classFilter);
        for (int i = 0; i < size; i++) {
            if (compareStrings(students[i].clas, classFilter) == 0) {
                printf("%s %s, возраст: %d, класс: %s\n", students[i].name, students[i].surname, students[i].age, students[i].clas);
            }
        }
    } else {
        printf("Неверный выбор!\n");
    }
}

// Список
void printStudents(struct Student *students, int size) {
    if (size == 0) {
        printf("Список студентов пуст!\n");
        return;
    }

    printf("Список студентов:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s %s, возраст: %d, класс: %s\n", i + 1, students[i].name, students[i].surname, students[i].age, students[i].clas);
    }
}

int main() {
    int size = 9;
    struct Student *students = malloc(size * sizeof(struct Student));

    students[0] = (struct Student){20, "Aleks", "Gudkovs", "PX-23"};
    students[1] = (struct Student){22, "Ivan", "Petrova", "PX-23"};
    students[2] = (struct Student){19, "Olga", "Ivanovs", "PX-24"};
    students[3] = (struct Student){20, "Maria", "Gudkovs", "PX-23"};
    students[4] = (struct Student){21, "Sergey", "Sidorov", "PX-24"};
    students[5] = (struct Student){22, "Elena", "Petrova", "PX-22"};
    students[6] = (struct Student){20, "Dmitry", "Ivanovs", "PX-22"};
    students[7] = (struct Student){19, "Anna", "Gudkovs", "PX-23"};
    students[8] = (struct Student){21, "Aleks", "Sidorov", "PX-24"};

    int MoveNum;
    int ProgramExit = 0;

    while (ProgramExit != 1) {
        printf("_____________________________________________\n Введите действие которые хотите сделать: \n  Добавить студента  - - - - - - - [1] \n  Удалить студента - - - - - - - - [2] \n  Изменить информацию о студенте - [3] \n  Отсортировать список - - - - - - [4] \n  Отфильтровать список - - - - - - [5] \n  Показать список  - - - - - - - - [6]\n  Выйти из программы - - - - - - - [7]\n_____________________________________________\n");
        scanf("%d", &MoveNum);

        if (MoveNum == 1) {
            students = addStudent(students, &size);
        } else if (MoveNum == 2) {
            int index;
            printf("_____________________________________________\nВведите индекс студента для удаления (1 - %d): ", size);
            scanf("%d", &index);
            students = removeStudent(students, &size, index - 1);
        } else if (MoveNum == 3) {
            int index;
            printf("_____________________________________________\nВведите индекс студента для изменения (1 - %d): ", size);
            scanf("%d", &index);
            modifyStudent(students, size, index - 1);
        } else if (MoveNum == 4) {
            sortStudents(students, size);
        } else if (MoveNum == 5) {
            filterStudents(students, size);
        } else if (MoveNum == 6) {
            printStudents(students, size);
        } else if (MoveNum == 7) {
            ProgramExit = 1;
        }
    }

    free(students);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

// Функція для виведення анотації та інформації про розробника
void show_about() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║          Лабораторна робота 7.2        ║\n");
    printf("║  Обчислення кількості заданих чисел    ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║   Розробник: Марченко Кирило           ║\n");
    printf("║   Група: КБ-24                         ║\n");
    printf("║   Навчальний заклад: ЦНТУ              ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
}

int main(void) {
    // Налаштування локалі та консолі для роботи з UTF-8
    setlocale(LC_ALL, "uk_UA.UTF-8");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Виведення анотації
    show_about();

    int numbers[14];
    int total = 0;

    printf("Введіть 14 натуральних чисел:\n");
    for (int i = 0; i < 14; i++) {
        if (scanf("%d", &numbers[i]) != 1) {
            fprintf(stderr, "Помилка зчитування числа.\n");
            return EXIT_FAILURE;
        }
    }

    // Підрахунок чисел, рівних 150, 1000 або 10000
    for (int i = 0; i < 14; i++) {
        if (numbers[i] == 150 || numbers[i] == 1000 || numbers[i] == 10000) {
            total++;
        }
    }

    printf("\nКількість чисел, рівних 150, 1000 або 10000: %d\n", total);

    return EXIT_SUCCESS;
}

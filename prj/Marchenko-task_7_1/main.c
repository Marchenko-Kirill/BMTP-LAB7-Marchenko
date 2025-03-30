#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

// Функція виведення анотації та інформації про розробника
void show_about() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║          Лабораторна робота 7.1        ║\n");
    printf("║  Обробка символьної інформації (UTF-8) ║\n");
    printf("╠════════════════════════════════════════╣\n");
    printf("║   Розробник: Марченко Кирило           ║\n");
    printf("║   Група: КБ-24                         ║\n");
    printf("║   Навчальний заклад: ЦНТУ              ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
}

// Функція для перетворення одного символу в нижній регістр з урахуванням української мови
wchar_t ua_tolower(wchar_t c) {
    // Перетворення українських літер верхнього регістру в нижній
    if (c >= L'А' && c <= L'Я') {
        return c + (L'а' - L'А');
    }
    // Специфічні українські літери
    if (c == L'Ї') return L'ї';
    if (c == L'І') return L'і';
    if (c == L'Є') return L'є';
    if (c == L'Ґ') return L'ґ';

    return towlower(c); // Для інших символів використовуємо стандартну функцію
}

int main() {
    // Налаштування локалі та консолі для роботи з UTF-8
    setlocale(LC_ALL, "uk_UA");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Виведення анотації
    show_about();

    char input[1024];

    // Зчитування речення від користувача
    printf("Введіть речення (яке завершується на '.', '!' або '?'):\n");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Помилка зчитування введення.\n");
        return EXIT_FAILURE;
    }

    // Видалення символу нового рядка, якщо він є
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    // Перевірка коректності закінчення речення
    if (len == 0 || (input[len - 1] != '.' && input[len - 1] != '!' && input[len - 1] != '?')) {
        printf("Помилка: речення повинно завершуватися на '.', '!' або '?'.\n");
        return EXIT_FAILURE;
    }

    // Перетворення UTF-8 рядка у широкий рядок
    int wlen = MultiByteToWideChar(CP_UTF8, 0, input, -1, NULL, 0);
    if (wlen <= 0 || wlen > 1024) {
        fprintf(stderr, "Помилка перетворення кодування.\n");
        return EXIT_FAILURE;
    }
    wchar_t winput[1024];
    MultiByteToWideChar(CP_UTF8, 0, input, -1, winput, wlen);

    // Створення копії введеного тексту в нижньому регістрі
    wchar_t winput_lower[1024];
    wcscpy(winput_lower, winput);

    // Приведення широкого рядка до нижнього регістру для нечутливості до регістру
    // з використанням власної функції
    for (wchar_t *p = winput_lower; *p != L'\0'; p++) {
        *p = ua_tolower(*p);
    }

    // Також приведемо пошукове слово до нижнього регістру
    wchar_t searchWord[] = L"програма";

    // Пошук слова "програма" у широкому рядку (приведеному до нижнього регістру)
    wchar_t *found = wcsstr(winput_lower, searchWord);

    if (found != NULL) {
        printf("Речення містить слово \"програма\".\n");
    } else {
        printf("Речення не містить слово \"програма\".\n");
    }

    return EXIT_SUCCESS;
}

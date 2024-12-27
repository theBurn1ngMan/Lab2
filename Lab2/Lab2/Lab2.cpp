#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstring>

const int MAX_OBJECTS = 100; // Максимальное количество объектов (труб и КС)

std::ofstream logFile("лог.txt", std::ios::app);

void logg(const std::string& message) {
    logFile << message << std::endl;
    std::cout << message << std::endl;
}

class Object {
protected:
    static int ID;
    int id;
public:
    Object() : id(++ID) {}

    int getID() const {
        return id;
    }
};

int Object::ID = 0;

class Tub : public Object {
public:
    std::string name;
    double lenght;
    double diametr;
    bool repair;

    void vvod() {
        setlocale(LC_ALL, "Russian");
        std::cout << "Введите название трубы: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Введите длину трубы: ";
        while (!(std::cin >> lenght) || lenght < 0) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введены неправильные значения. Десятичные дроби вводятся через точку, например: 0.1" << std::endl;
            }
            else {
                std::cout << "Перепроверьте значения. Длина не может быть отрицательной." << std::endl;
            }
            std::cout << "Введите длину трубы: ";
        }

        std::cout << "Введите диаметр трубы: ";
        while (!(std::cin >> diametr) || diametr < 0) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введены неправильные значения. Десятичные дроби вводятся через точку, например: 0.1" << std::endl;
            }
            else {
                std::cout << "Перепроверьте значения. Диаметр не может быть отрицательным." << std::endl;
            }
            std::cout << "Введите диаметр трубы: ";
        }

        std::cout << "Находится ли труба в ремонте? (1 - да, 0 - нет): ";
        std::cin >> repair;

        logg("Добавлена труба с ID " + std::to_string(getID()));
    }

    void vivod() const {
        setlocale(LC_ALL, "Russian");
        std::cout << "ID трубы: " << getID() << std::endl;
        std::cout << "Название трубы: " << name << std::endl;
        std::cout << "Длина: " << lenght << " км" << std::endl;
        std::cout << "Диаметр: " << diametr << " м" << std::endl;
        std::cout << "В ремонте: " << (repair ? "Да" : "Нет") << std::endl;
    }

    void change_status() {
        setlocale(LC_ALL, "Russian");
        std::cout << "Введите новый статус ремонта (1 - да, 0 - нет): ";
        std::cin >> repair;
        logg("Изменен статус ремонта трубы с ID " + std::to_string(getID()));
    }
};

class Stantion : public Object {
public:
    std::string name;
    int kolCeh;
    int actCeh;
    double effictivity;

    void vvod() {
        setlocale(LC_ALL, "Russian");
        std::cout << "Введите название станции: ";
        std::cin.ignore();
        std::getline(std::cin, name);

        std::cout << "Введите общее количество цехов: ";
        while (!(std::cin >> kolCeh) || kolCeh < 0) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введены неправильные значения. Целые значения вводятся без запятой." << std::endl;
            }
            else {
                std::cout << "Перепроверьте значения. Количество не может быть отрицательным." << std::endl;
            }
            std::cout << "Введите общее количество цехов: ";
        }

        std::cout << "Введите количество активных цехов: ";
        while (!(std::cin >> actCeh) || actCeh > kolCeh || actCeh < 0) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введены неправильные значения. Целые значения вводятся без запятой." << std::endl;
            }
            else {
                std::cout << "Активные цеха не могут превышать общее количество или быть меньше 0." << std::endl;
            }
            std::cout << "Введите количество активных цехов: ";
        }

        std::cout << "Введите эффективность станции: ";
        while (!(std::cin >> effictivity) || effictivity < 0) {
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Введены неправильные значения. Десятичные дроби вводятся через точку, например: 0.1" << std::endl;
            }
            else {
                std::cout << "Перепроверьте значения. Эффективность не может быть отрицательной." << std::endl;
            }
            std::cout << "Введите эффективность станции: ";
        }

        logg("Добавлена компрессорная станция с ID " + std::to_string(getID()));
    }

    void vivod() const {
        setlocale(LC_ALL, "Russian");
        std::cout << "ID станции: " << getID() << std::endl;
        std::cout << "Название станции: " << name << std::endl;
        std::cout << "Общее количество цехов: " << kolCeh << std::endl;
        std::cout << "Активные цеха: " << actCeh << std::endl;
        std::cout << "Эффективность: " << effictivity << std::endl;
        std::cout << "Незадействованные цеха: " << kolCeh - actCeh << std::endl;
    }
};

// Поиск труб по названию или по признаку ремонта
int findTubs(Tub tubs[], int count_tubs, Tub* finden_tubs[], const std::string& name, bool repair = false, bool seek = true) {
    int найдено = 0;
    for (int i = 0; i < count_tubs; i++) {
        if (seek && tubs[i].name == name) {
            finden_tubs[найдено++] = &tubs[i];
        }
        else if (!seek && tubs[i].repair == repair) {
            finden_tubs[найдено++] = &tubs[i];
        }
    }

    if (найдено == 0) {
        std::cout << "Ничего не найдено, перепроверьте запрос." << std::endl;
    }

    return найдено;
}

// Пакетное редактирование труб
void пакетноеРедактирование(Tub* finden_tubes[], int finden_count) {
    setlocale(LC_ALL, "Russian");
    if (finden_count == 0) {
        std::cout << "Нет труб для редактирования." << std::endl;
        return;
    }

    std::cout << "Найдено труб: " << finden_count << ". Вы хотите отредактировать все трубы? (1 - да, 0 - нет): ";
    bool change_all;
    std::cin >> change_all;

    if (change_all) {
        for (int i = 0; i < finden_count; i++) {
            finden_tubes[i]->change_status();
        }
    }
    else {
        std::cout << "Введите индексы труб для редактирования через пробел (0 для выхода): ";
        int i;
        while (std::cin >> i && i != 0) {
            if (i > 0 && i <= finden_count) {
                finden_tubes[i - 1]->change_status();
            }
            else {
                std::cerr << "Неверный индекс." << std::endl;
            }
        }
    }

    logg("Пакетное редактирование труб завершено.");
}

// Сохранение и загрузка данных
void сохранитьВФайл(const std::string& filename, Tub tubes[], int count_tubes, Stantion stantions[], int count_stantions) {
    setlocale(LC_ALL, "Russian");
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для сохранения!" << std::endl;
        return;
    }

    file << count_tubes << std::endl;
    for (int i = 0; i < count_tubes; i++) {
        file << tubes[i].name
            << std::endl << tubes[i].lenght
            << std::endl << tubes[i].diametr
            << std::endl << tubes[i].repair << std::endl;
    }

    file << count_stantions << std::endl;
    for (int i = 0; i < count_stantions; i++) {
        file << stantions[i].name
            << std::endl << stantions[i].kolCeh
            << std::endl << stantions[i].actCeh
            << std::endl << stantions[i].effictivity << std::endl;
    }

    file.close();
    logg("Данные успешно сохранены в файл " + filename);
}

void загрузитьИзФайла(const std::string& filename, Tub tubes[], int& count_tubes, Stantion stantions[], int& count_stations) {
    setlocale(LC_ALL, "Russian");
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла для загрузки!" << std::endl;
        return;
    }

    file >> count_tubes;
    file.ignore();
    for (int i = 0; i < count_tubes; i++) {
        std::getline(file, tubes[i].name);
        file >> tubes[i].lenght >> tubes[i].diametr >> tubes[i].repair;
        file.ignore();
    }

    file >> count_stations;
    file.ignore();
    for (int i = 0; i < count_stations; i++) {
        std::getline(file, stantions[i].name);
        file >> stantions[i].kolCeh >> stantions[i].actCeh >> stantions[i].effictivity;
        file.ignore();
    }

    file.close();
    logg("Данные успешно загружены из файла " + filename);
}

// Основное меню
int main() {
    setlocale(LC_ALL, "Russian");
    Tub tubs[MAX_OBJECTS];
    Stantion stantions[MAX_OBJECTS];
    int count_tubs = 0, count_stantions = 0;
    Tub* finden_tubs[MAX_OBJECTS];
    int choise;
    std::string file_name;

    while (true) {
        std::cout << "1. Добавить трубу" << std::endl;
        std::cout << "2. Добавить компрессорную станцию" << std::endl;
        std::cout << "3. Поиск труб по фильтру" << std::endl;
        std::cout << "4. Пакетное редактирование труб" << std::endl;
        std::cout << "5. Сохранить" << std::endl;
        std::cout << "6. Загрузить" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choise;

        if (choise == 0) {
            break;
        }

        switch (choise) {
        case 1: {
            tubs[count_tubs].vvod();
            count_tubs++;
            break;
        }
        case 2: {
            stantions[count_stantions].vvod();
            count_stantions++;
            break;
        }
        case 3: {
            std::cout << "1. Поиск по названию" << std::endl;
            std::cout << "2. Поиск по статусу ремонта" << std::endl;
            int filtr;
            std::cin >> filtr;
            if (filtr == 1) {
                std::string name;
                std::cout << "Введите название: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                int fidene = findTubs(tubs, count_tubs, finden_tubs, name);
                for (int i = 0; i < fidene; i++) {
                    finden_tubs[i]->vivod();
                }
            }
            else if (filtr == 2) {
                bool repair;
                std::cout << "Труба в ремонте? (1 - да, 0 - нет): ";
                std::cin >> repair;
                int fidene = findTubs(tubs, count_tubs, finden_tubs, "", repair, false);
                for (int i = 0; i < fidene; i++) {
                    finden_tubs[i]->vivod();
                }
            }
            break;
        }
        case 4: {
            std::string name;
            std::cout << "Введите название для поиска труб: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            int finden = findTubs(tubs, count_tubs, finden_tubs, name);
            пакетноеРедактирование(finden_tubs, finden);
            break;
        }
        case 5: {
            std::cout << "Введите имя файла для сохранения: ";
            std::cin >> file_name;
            сохранитьВФайл(file_name, tubs, count_tubs, stantions, count_stantions);
            break;
        }
        case 6: {
            std::cout << "Введите имя файла для загрузки: ";
            std::cin >> file_name;
            загрузитьИзФайла(file_name, tubs, count_tubs, stantions, count_stantions);
            break;
        }
        default:
            std::cerr << "Неверная опция. Попробуйте снова." << std::endl;
        }
    }

    logFile.close();
    return 0;
}


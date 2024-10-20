# DigiPaper: Библиотека для деформации бумаги

## Описание

DigiPaper — это библиотека для расчета изгиба углов листа бумаги с помощью настраиваемого алгоритма. Библиотека позволяет работать с пространством точек и моделировать деформацию бумаги по заданным параметрам, включая радиус искривления и координаты точек сгиба.

Проект реализован с использованием библиотеки Eigen и предоставляет функционал для работы с точками, прямыми и цилиндрическими координатами, а также для вычисления углов, пересечений и изгибов на плоскости.

**Ссылка на родительский проект:** [https://github.com/BlackAWhite8/digipaper](https://github.com/BlackAWhite8/digipaper)  
**Ссылка на дочерний проект:** [https://github.com/Pretty-boy1719/misis2023f-22-03-kiselev-k-a.git](https://github.com/Pretty-boy1719/misis2023f-22-03-kiselev-k-a.git)

## Техническое задание

- Создание библиотеки для расчета изгиба углов листа бумаги.
- Входные данные:
  - Размерность листа (половина длины).
  - Пары точек, отображающие место сгиба.
  - Радиус искривления.
- Выходные данные: координаты точек, изображающие согнутую бумагу.
- Алгоритмы для расчета точек, а также функционал для работы с результатами (например, сохранение в файл).

## Установка

Для сборки проекта потребуются:

- [Eigen](https://eigen.tuxfamily.org/dox/)

### Шаги по установке

1. Клонируйте репозиторий:

    ```bash
    git clone https://github.com/Pretty-boy1719/misis2023f-22-03-kiselev-k-a.git
    ```

2. Сборка проекта с помощью CMake:

    ```bash
    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=<путь до менеджера библиотек, например до vcpkg.cmake>
    cmake --build build --config Release
    cmake --install build
    ```

   **Примечание**: Для Windows нужно запустить командную строку с правами администратора, для Linux/MacOS использовать команду с `sudo`.

## Использование

Библиотека позволяет моделировать деформацию бумаги. Пример использования:

1. Подключите заголовочный файл:

    ```cpp
    #include <digiPaper/digi_paper.hpp>
    ```

2. Создайте объект типа `Space` с указанием размерности (например, 100):

    ```cpp
    Space area(100);  // Размерность пространства
    ```

3. Определите точки и радиус изгиба:

    ```cpp
    Space::Point3 c1(-100, 10, 0);
    Space::Point3 c2(-30, 100, 0);
    double radius3 = 60;
    ```

4. Вызовите метод для выполнения изгиба:

    ```cpp
    area.cylindrical_bending(c1, c2, radius3);
    ```

5. Сохраните результат в файл:

    ```cpp
    std::ofstream output("output.txt");
    area.WriteTo(output);
    ```

### Взаимодействие с интерфейсом

Для отображения результатов можно использовать готовую визуализацию. Взаимодействие осуществляется через интерактивное меню с слайдерами для изменения углов отображения, изменения цвета модели и размера точек. Результаты можно сохранять в формате PNG.

## Структура библиотеки

Библиотека состоит из нескольких ключевых компонентов:

- **Point3**: Структура для представления точки в 3D-пространстве.
- **Line2**: Структура для работы с 2D-прямыми.
- **CylindricalCoordinate**: Структура для работы с цилиндрическими координатами.

### Методы

- `Point3 compute_midpoint(Point3 a1, Point3 a2);` — вычисление середины между двумя точками.
- `Line2 compute_perpendicular_line(Line2 line, Point3 mid);` — нахождение перпендикулярной прямой.
- `double compute_distance_to_line(Point3 m, Line2 line);` — нахождение расстояния от точки до прямой.
- `void cylindrical_bending(Point3 a1, Point3 a2, double radius);` — метод для изгиба бумаги.
- `std::ostream& WriteTo(std::ostream& ostrm);` — метод для записи результата в поток.

## Пример работы с библиотекой

### Пример 1: Создание объекта и изгиб бумаги

```cpp
#include <digiPaper/digi_paper.hpp>

int main() {
    // Создание объекта Space с размерностью 100
    Space area(100);

    // Определение точек сгиба
    Space::Point3 c1(-100, 10, 0);
    Space::Point3 c2(-30, 100, 0);
    double radius3 = 60;

    // Вызов метода для изгиба
    area.cylindrical_bending(c1, c2, radius3);

    // Запись результатов в файл
    std::ofstream output("output.txt");
    area.WriteTo(output);

    return 0;
}
```

## Лицензия

Этот проект распространяется под лицензией MIT. См. файл LICENSE для подробной информации.

---



## Cfig
Простой язык конфигурации для C++ с автоматическим определением типов. 

> ⚠️ Версия v0.1 находится на отдельной ветке и имеет тяжелый синтаксис. 
> Cfig — это полный редизайн, сохраняющий идеи, но с упрощенной архитектурой.

### Синтаксис
По умолчанию все пары *ключ:значение* хранятся в секции `main`.
```ini
; это комментарий
name: John        ; строка
port: 8080        ; целое число
ratio: 3.14       ; число с плавающей точкой
debug: true       ; булево значение
mark: 'A'         ; символ
```
Для организации сложных конфигураций используйте секции
```ini
; Глобальные настройки (секция main)
project_name: example
version: 0.1

[server]
host: localhost
port: 5432
timeout: 30.5

; Возвращаемся к main
[]
log_level: debug
```
### Основные возможности
- **Автоматическое определение типов** — не нужно явно указывать `int`, `string`, `float` или `bool`

- **INI-подобный синтаксис** — работает с привычными `.cfg`, `.ini` и `.cfig` файлами

### Работа с библиотекой `cfig.h`
`cfig.h` — это легковесная C++ библиотека для работы с конфигурационными файлами с автоопределением типов.

#### Как подключить библиотеку
В директории проекта выполните
```bash
mkdir -p libs
git submodule add https://github.com/groknut/cfig libs/cfig
git submodule init
git submodule update
```

#### Быстрый старт
```cpp
#include <iostream>
#include <string>
#include "cfig.h"

int main()
{
	// название файла, разделитель, и комментарий
	Cfig config("config.ini", Cfig::EQUAL, Cfig::HASH);

	int port = config.get("server", "port").toInt();
	std::string host = config.get("server", "host");
	bool debug = config.get("server", "debug").toBool();
	float timeout = config.get("server", "timeout").toFloat();
	
	std::cout << "Server Configuration:" << std::endl;
	std::cout << "Hostname: " << host << std::endl;
	std::cout << "Port: " << port << std::endl;
	std::cout << "Debug: " << debug << std::endl;
	std::cout << "Timeout: " << timeout << std::endl;
	
	return 0;
}
```

#### Файл `config.ini`:
```ini
[server]
port: 8080
host: localhost # или "localhost"
debug: true
timeout: 3.5
char: 'X'
```

#### Методы API
`get()` **- получение значений**

Возвращает значение по секции и ключу. Бросает исключение, если ключ не найден. 
```cpp
// Из указанной секции
std::string host = config.get("server", "host");

// Из секции main (по умолчанию)
std::string name = config.get("name");

// Явное преобразование
int port = config.get("server", "port").toInt();
bool debug = config.get("server", "debug").toBool();
float timeout = config.get("server", "timeout").toFloat();
```

`get<T>()` **- получение значений**

Возвращает значение по секции и ключу. Если ключ или секция не найдены, то возвращает значение по умолчанию, установленное вами.
```cpp
// Из указанной секции
float timeout = config.get<float>("server", "timeout", 10.25f); // ключа timeout нет в секции (for example)

// Из секции main (по умолчанию)
std::string name = config.get<std::string>("name", "John");
```

`has()` **- проверка наличия**

Проверяет существование ключа в секции
```cpp
// Проверка ключа в секции
if (config.has("server", "host")) {
    // Ключ существует
}

// Проверка существования секции
if (config.has("server")) {
    // секция существует
}
```

### Поддерживаемые типы данных
|Тип|Примеры|Метод преобразования|
|---|-------|--------------------|
|STRING|`"hello"`, `patho/to/file`|`.toString()` или неявное преобразование|
|INT|`10`, `0`|`.toInt()`|
|FLOAT|`3.14`, `-2.5`|`.toFloat()`, `toDouble()`|
|BOOL|`false`, `true`|`.toBool()`|
|CHAR|`X`, `'X'`|`.toChar()`|
|PAIR|`(10, 25)`, `(10.25, 10.30)`|`.toPair<int>()`|

### Лицензия
**MIT License**. Подробности в файле `LICENSE`.

### Роадмап
1. _Поддержка пар_
2. _Стили комментариев_
3. _Безопасные геттеры с дефолтными значениями_
4. Итерации по секциям и ключам
5. Массивы

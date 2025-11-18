

## Ic - INI-like syntax

Был написан для решения задачи муравьиного алгоритма. Пары были добавлены в версии 0.0.2 для решения задачи алгоритма LIAN.

**Текущая версия:** 0.0.2
```ic
; ================================
; 			CONFIGURATION
; ================================
; Синтаксис:
;   [секция]       - объявление секции параметров (по умолчанию `main`)
;   ключ: значение - параметр и его значение
;   ; комментарий  - строка комментария (игнорируется)
;	; если требуется вернуться из секции [graph] в секцию `main` можно просто написать `[]` или `main`
;	; в программу принимается `.ic` формат
```

**Значение может быть:**
- `bool` типа: `true` или `false`
- `int` типа: `1`
- `double` типа: `1.25`
- `pair` типа (только `int` и `double` значения!): `(10, 20)`
- `string` типа: `file.txt`

### Методы:

**Получить значение:**
```cpp
std::string val = getVal("key");
std::string val = getVal("ant", "rho");
```

**Существование секции, либо ключа:**
```cpp
if (has("ant", "key"))
	std::cout << ic.getVal("ant", "rho");
// или если мы знаем, что у ant точно есть ключ rho
if (has("ant"))
	std::cout << ic.getVal("ant", "rho");
```

**Получаем int значение:**
```cpp
int iter = ic.as_int("iters");
int iter = ic.as_int("colony", "iters");
```

**Получаем double значение:**
```cpp
double iter = ic.as_double("iters");
double iter = ic.as_double("colony", "iters");
```

**Получаем bool значение:**
```cpp
bool b = ic.as_bool("bool");
bool b = ic.as_bool("test", "bool");
```

**Получаем pair<int ,int> значение:**
```cpp
std::pair<int ,int> p = ic.as_int_pair("pair");
std::pair<int ,int> p = ic.as_int_pair("test", "pair");
```

**Получаем pair<double, double> значение:**
```cpp
std::pair<double, double> p = ic.as_double_pair("pair");
std::pair<double, double> p = ic.as_double_pair("test", "pair");
```

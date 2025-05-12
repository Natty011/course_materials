מצוין 🔍 הנה טמפלט מסודר שאתה יכול לשמור ולהשתמש בו בכל פעם שתוכנית שלך מתרסקת ב־Linux (עם `gdb`) — גם כשאין לך את קובץ המקור.

---

## 🧠 **טמפלט לניתוח קריסות ב־GDB**

### 🧱 1. זיהוי סוג הקריסה (מהפקודה הראשונה ב־gdb)

```bash
Program received signal SIGABRT, Aborted.
```

#### 📌 פירוש:
- **SIGABRT** מצביע לרוב על `abort()` של `libc`.
- לא נגרם מגישה לזיכרון לא חוקי, אלא **בעיה בזיכרון שהתגלתה ע"י malloc/free**.

---

### 📊 2. הפעל `bt` (backtrace)

```bash
(gdb) bt
```

### 🔍 מה לחפש:
- איפה הקריאה האחרונה בתוכנית שלך (`main()` או פונקציה שאתה כתבת).
- האם קיימות פונקציות מה־libc כמו:
  - `malloc_printerr`
  - `free`
  - `__GI___libc_free`
  - `munmap_chunk`

#### 🧠 ניתוח לפי מילות מפתח:
| מילה | משמעות |
|------|---------|
| `munmap_chunk(): invalid pointer` | שחרור מצביע שהוקצה לא נכון או כבר שוחרר |
| `double free` | שחרור של אותו מצביע פעמיים |
| `corrupted size vs. prev_size` | כתיבה על זיכרון שהשחיתה את המבנה של malloc |
| `invalid next size` | כנראה overflow בזיכרון |
| `SIGSEGV` במקום SIGABRT | גישה לזיכרון לא קיים (בעיה אחרת לגמרי) |

---

### 🧮 3. פקודות נוספות לניתוח

#### 🔍 מקומית — ערכים מקומיים:
```bash
(gdb) info locals
```

#### 🧱 ערכי פרמטרים:
```bash
(gdb) info args
```

#### 🧠 בדיקת המצביע:
```bash
(gdb) print px
(gdb) print *px
```

#### קפיצה לשורת קוד:
```bash
(gdb) list
```

---

### 🧯 4. דפוסי שגיאה קלאסיים

#### ✅ תקין:
```cpp
X* px = new X[10];
delete[] px;
```

#### ❌ נפוץ:
```cpp
X* px = new X[10];
delete px; // munmap_chunk(): invalid pointer
```

#### ❌ שחרור כפול:
```cpp
X* px = new X;
delete px;
delete px; // double free
```

#### ❌ העתקת struct שמכיל pointer:
```cpp
struct X { int* a; };
X x1;
x1.a = new int[10];
X x2 = x1;
delete[] x1.a;
delete[] x2.a; // שניים משחררים אותו הדבר
```

---

### 🛠 טיפים נוספים

#### 🧪 הפעלה עם שמירה על core dump:
```bash
ulimit -c unlimited
./prog.out
```

#### 📂 הפעלה של `gdb` עם core:
```bash
gdb ./prog.out core
(gdb) bt
(gdb) info locals
```

---

### 🧷 אפשר גם להכין סקריפט ניתוח:

```bash
#!/bin/bash
gdb -q ./prog.out core -ex "bt" -ex "info locals" -ex "quit"
```

---

אם תרצה גרסה של זה כ־PDF או קובץ Markdown שאתה יכול לשלב כ-cheatsheet בסביבת עבודה — תגיד ואכין לך.

הקריסה שאתה רואה נגרמת מהשורה הבאה בקובץ `intro20.cpp`, שורה 136:

```cpp
delete px; px = 0; //Destructor
```

### ⚠️ סיבת הקריסה (לפי backtrace + הקוד):

```cpp
X* px = new X(x2); // copy ctor
...
delete px; // שורה 136
```

והקריסה היא:
```
munmap_chunk(): invalid pointer
```

המשמעות של זה היא שאתה מנסה לשחרר (free/delete) מצביע שלא הופק על־ידי `new`, או שהוא **הושחת**, או שהוא **כבר שוחרר**.

---

### 🔍 ניתוח מדויק לפי הקוד:

#### 1. מחלקת `X`:
```cpp
struct X
{
	int m_a;
	const int m_b;
	X* xp; // שדה מצביע
};
```

#### 2. ב־Destructor של `X`:
```cpp
X::~X()
{
	//delete[] xp;
	std::cout << "this:" << this <<
	" X Dtor. m_a:" << m_a <<
	" m_b:" << m_b << std::endl;
}
```

> שים לב שהשורה `delete[] xp;` **מוסרת (commented out)**. אך ייתכן שבאחד מהאובייקטים `xp` מצביע לאזור מוקצה שצריך לשחרר – או ששוחרר **פעמיים**.

---

### 🧠 הסיבה הכי סבירה:

הבעיה היא **בשורה הזאת**:
```cpp
X* xp = new X[10];
...
delete xp;
```

פה ביצעת:
- **`new X[10]`** – כלומר הקצאה של מערך.
- אבל אחר כך – **`delete xp;`** במקום **`delete[] xp;`**

וזו בדיוק **שגיאה קריטית**:
- `new[]` → צריך לשחרר עם `delete[]`
- `new` → משחררים עם `delete`

#### אחרת? אתה מקבל:
```
munmap_chunk(): invalid pointer
```

וזו בדיוק ההודעה שהופיעה אצלך.

---

### ✅ תיקון:
שנה את השורה:
```cpp
delete xp;
```

ל:
```cpp
delete[] xp;
```

---

### 📌 תוספות חשובות:
1. אל תשחרר אובייקט עם `delete` אם הוא הוקצה עם `new[]`.
2. ב־Destructor של `X` אתה כרגע **לא משחרר** את `xp`, כך שאם בהמשך תשתמש בו, זה יגרום לדליפת זיכרון.

---

### רוצה עזרה באיך לשלב `xp` נכון כך שה־destructor ישחרר אותו רק אם הוא אכן הוקצה? או לבדוק אם יש עוד דליפות/שימושים כפולים?

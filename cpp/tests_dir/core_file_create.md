✅ שלבים ליצירת קובץ core אמיתי (ולא דרך apport):
1. 🔻 השבתה זמנית של apport:
bash

sudo systemctl stop apport.service
sudo systemctl disable apport.service
2. 🛠 שינוי תבנית כתיבת core:
bash

sudo sysctl -w kernel.core_pattern=core
(ככה יווצר קובץ בשם core בתיקייה הנוכחית)

3. 📏 אפשר יצירת קובץ core מה-shell שלך:
bash

ulimit -c unlimited
אם זה עדיין לא עובד (כמו שראית קודם), נסה להריץ bash חדש ב־sudo:

bash

sudo -i
ulimit -c unlimited
cd /home/natty/test/intro15_godbolt_inline\ functions\ example/
./your_program.out
💡 עכשיו אמור להיווצר core כשיש קריסה.

🧪 לאחר הקריסה:
ודא שנוצר קובץ core:

bash

ls -l core*
פתח אותו עם gdb:

bash

gdb ./your_program.out core
בתוך gdb:

gdb

bt             # הדפס את backtrace
info locals    # לראות ערכים מקומיים
❗️ שים לב
אם אתה מפתח בתוך snap או WSL – זה עלול לא לעבוד בגלל מגבלות של המערכת. במקרה כזה צריך פתרון אחר (לדוג' לעבוד מחוץ ל־snap, או על VM אמיתי).
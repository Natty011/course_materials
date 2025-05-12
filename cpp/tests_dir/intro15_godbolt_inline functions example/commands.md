שמור את שני הקבצים באותה תיקייה.

ב־טרמינל הרץ:

bash

make
תריץ objdump על כל אחד כך:

bash

objdump -d no_opt.out | less
objdump -d opt.out | less
חפש:

האם יש call Square

האם רואים imul ישירות בתוך main

🧪 למה זה חשוב?
ב־no_opt.out תראה לרוב קריאה לפונקציה (call)

ב־opt.out תראה את הקוד "מודבק" = inline בפועל

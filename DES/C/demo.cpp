// demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>
#include "Utils.h"

int main()
{
	InitDES("12345678", "87654321");
	char* aa = EncryptDES("1gygu活该活该");
	char* bb = DecryptDES(aa);
	char* cc = DecryptDES("Iq8nag+x2Bai0j2tZgo6KuM84aeeOooKNC6XW2B+eU3zl4+k64zeuuFjSL6CvDYVkRWfapaZ0HM/FMEfc83cRpIo3R92W+loAjC2IUgJtyr/Sh3MeKaE0BJe2a1l14Js/6oxXVgHH/+oXu5bmjjZcyL4Tc3iEmDNGEd1I4ZKtnsSQIPk42mv7Zi51Ade999V1OyYFJrVh5z5QpF0UC5cLFaTTQ0nkkBNiSrlPCpSLq11kxnFADjp7WTH9I0RQfOjB/wPhiojuHUK4jErz1J3LuWuhJyW/hCvCDEswCr/Q5uFdKhFZ9wtcW427tnxiqbQyx+gRJ8+XsroMqEH1IaxJm/G1KLzpl8mNH5YCZtWG/BjbtmdxraF+THrQxOX1EjAcMcWjBnhoM+zAXLJbcCmmBu6uMorOOYjDMVWOAJrCuwwoh1e48l10BVX7pUpsLLEgOQbXpDtAFMvOvFUSGbUcgOrpqfNTfFFyuC8vO2szAvpiOL3kLJK+k7khVHw/kJWH+WknLy8LLBUF+/cnUisJHDK7ruMaRoMklvt67m4qysmM4beAiPZIrU6gIU8Q/fdxl/LsR0vFAHSqZaR+dKXpNHMA9qb/xtRKdc9zuTTWVnQA0ZquTWlT0neYmitJ3xl/Yt3QElZP8rqLb97iLlehWsXs9g90eVm8tJiKF8CunX5u+PzOqmsS8aSa9voEfrNqmskQFjqln9091Nu/emxsM883tu7v50W/XQ2uZZXrM0hd6Elo/fZTUu+YvQkxHBDjcPyAk3TQ+20t5nGNYDHaY6f4PMZ1NmKYa7FSDuYjcAsxr0eT0v5i8wm8VZX4MJZn8suzB+9Z9D4Df8TQuuIvPJw6bms41KBId/dfuvsCEHyewRaUw5eWZEfYVeyxxMJ8JAd24P9pc7FSneuWgVYLg+gsNmudhCow5plKCd+GJX3aFhL/WdHsZe70TQwnqCV9aiVKv14/ehhPh+paCUgEaQMGqPM7wSd1pguI0W3KWVaoF6whLV3vt3btpK7w8eOimGmWay4EuRch3RVmZMgx/58WVnvJ8hPKAW/mXIGDxyUdlxVWgnt9wPZsyeHHh56uJ2dMAPXswipSJefdFUzTzIZpKmBAdTOYDAFxf5zuDX5e1kKthozQo4I+YF93nGXdCFIsesLmLONU7UxSwghLJNYrR+uUR5owNcx4R/mSNEJDaThu92NIt0WVCmZ4ryhnAq8q2lRPbUpbGdqi7bis4W9uM5kc2Ua4yTNJwSBLpjyy2xWwa1RB86pzDiNeSNFEJ3aRUzcwxGJj5O5lN1DLDo3XqHV8QbdZF8ln61pGi096px42Z9x859FW61iEG3o32pQW/5FcD8a2cwTeGomBD8bEqyf881DYz8Fr4cwEptKseMfTQRoD+rcI4NTR8tk3EOvsZOshSNTeRs/wqgTdzi4WbUybIS4xKl+CHCZM+closSHiehB1/4rSjSQCiMaHAnX3iLx1/I=");
	MessageBoxA(NULL, cc, "", MB_OK);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

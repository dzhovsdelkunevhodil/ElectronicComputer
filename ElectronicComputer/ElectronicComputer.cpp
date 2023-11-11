
/*В массиве из 10 чисел все элементы, стоящие левее максимального, 
заменить нулями, а элементы, стоящие правее максимального, 
заменить максимальным элементом.*/

#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	int arr[10];
	char str[] = "%d ";

	// Инициализация массива
	for (int i = 0; i < 10; i++) {
		scanf_s("%d", &arr[i]);
	}

	int maxIndex = 0;
	int maxValue = 0;

	// Находим максимальное значение и его индекс
	__asm {
		mov eax, [arr]
		mov ebx, 4

	find_max:
		cmp eax, [arr + ebx]
		jge not_max
		mov eax, [arr + ebx]
		mov maxValue, eax
		mov maxIndex, ebx

	not_max :
		add ebx,4
		cmp ebx, 40
		jle find_max

		mov maxValue,eax
	}

	cout << "Max Value = " << maxValue << endl;
	cout << "Index of max value  = " << (maxIndex/4) + 1<< endl;

	//Заменяем элементы слева от максимального на 0 и элементы справа на максимальное значение
	__asm {
		mov ebx, 0

	replace_left:
		cmp ebx, maxIndex
		jae replace_right
		mov[arr + ebx], 0
		add ebx,4
		jmp replace_left

	replace_right :
		cmp ebx, 40
		jge fin
		mov edx, maxValue
		mov [arr + ebx], edx
		add ebx,4
		jmp replace_right

	fin :
	}
	//Вывод
	cout << "display ASM" << endl;

	__asm {
		mov ebx, 0
	for1 :
		mov edx, [arr + ebx]
		push edx
		lea ecx,str
		push ecx
		call printf
		add esp, 8
		add ebx, 4
		cmp ebx, 40
		jl for1
	}
	cout << "\n\n\n";

	// Вывод
	cout << "display cout<<" << endl;
	for (int i = 0; i < 10; i++) {
		cout<< arr[i] << " ";
	}

	return 0;
}
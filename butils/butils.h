
#ifndef __BUTILS__H
#define __BUTILS__H

#include <stdint.h>
#include <stddef.h>

enum errors {
	NULLERR = 1,
	MEMERR = 2,
	SIZEERR = 3
};

const char* bstrerr(int errc); // обработчик ошибок библиотеки

void makenmem(void* source, int value, size_t size); // выдача нужного значения данным
void copy_data(void* restrict dist, const void* restrict source, size_t cpy_size); // копирование данных
void move_data(void* dist, const void* source, size_t cpy_size); // передвижение данных (безопасное копирование)

#endif // !__BUTILS__H


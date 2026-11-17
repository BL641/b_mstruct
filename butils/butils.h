
#ifndef __BUTILS__H
#define __BUTILS__H

void makenmem(void* source, int value, size_t size); // выдача нужного значения данным
void copy_data(void* dist, const void* source, size_t cpy_size); // копирование данных

#endif // !__BUTILS__H


//
//  EZsqlite3.cpp
//  nullatest01
//
//  Created by soeasyright on 2014/6/9.
//
//

#include "EZsqlite3.h"
#define QUERY_SIZE (1 << 8)
char *table_queryprintf(char *fmt, ...) {
	static char q[QUERY_SIZE];
	va_list ap;
	va_start(ap, fmt);
	sqlite3_vsnprintf(QUERY_SIZE - 1, q, fmt, ap);
	va_end(ap);
	return q;
}
void EZsqlite3::Opne()
{
    
}
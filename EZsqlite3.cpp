//
//  EZsqlite3.cpp
//  
//
//  Created by soeasyright on 2014/6/9.
//
//

#include "EZsqlite3.h"

#define QUERY_SIZE (1 << 9)
char *table_queryprintf(const char *fmt, ...) {
	static char q[QUERY_SIZE];
	va_list ap;
	va_start(ap, fmt);
	sqlite3_vsnprintf(QUERY_SIZE - 1, q, fmt, ap);
	va_end(ap);
	return q;
}


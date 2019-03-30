#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>

#include "common.h"

typedef struct stock_entry_t
{
	time_t datetime;
	f32 open, high, low, close;
	s64 volume;
} stock_entry_t;

typedef struct stock_data_t
{
	stock_entry_t* entries;
	s64 num_entries;
	time_t first_datetime, last_datetime;
}stock_data_t;

s32 count_occurrences(char* str, char c)
{
	s32 ret = 0;
	while (str) {
		if (*str == c) {
			ret++;
		}
		str++;
	}
	return ret;
}

s32 count_num_lines(FILE* fp)
{
	stock_data_t ret;

	s32 lines;
	char ch;
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (ch == '\n') {
			lines++;
		}
	}
	return lines;
}

stock_data_t read_stock_csv(char* path)
{
	bool skip_first_line;
	FILE* fp;
	char* line;
	size_t len;
	ssize_t read;

	stock_data_t ret;

	fp = fopen(path, "r");
	bail_if(fp == NULL, "Could not open %s", path);

	read = getline(&line, &len, fp);

	//It's a more or less safe assumption that, if the very first character is alpha, then the first line is
	//the names of the columns. Otherwise, it's the 0th entry. We aren't smart enough to parse the column names
	//so dont rewind, otherwise do
	if (isalpha(line[0])) {
		skip_first_line = true;
	}
	else {
		rewind(fp);
	}

	s64 num_lines = count_num_lines(fp);
	ret.num_entries = num_lines;
	ret.entries = malloc(sizeof(stock_entry_t) * num_lines);

	rewind(fp);
	if (skip_first_line) {
		getline(&line, &len, fp);
	}

}
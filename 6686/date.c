#include "date.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Date *CreateDate(int year, int month, int day)
{
    Date *new = malloc(sizeof(Date));
    new->year = year;
    new->month = month;
    new->day = day;
    return new;
}
void DestroyDate(Date **p)
{
    free(*p);
    *p = NULL;
}
Date *CopyDate(const Date *date)
{
    Date *copy = malloc(sizeof(Date));
    memcpy(copy, date, sizeof(Date));
    return copy;
}

int GetYear(const Date *date) { return date->year; }
int GetMonth(const Date *date) { return date->month; }
int GetDay(const Date *date) { return date->day; }
void SetYear(Date *date, int year) { date->year = year; }
void SetMonth(Date *date, int month) { date->month = month; }
void SetDay(Date *date, int day) { date->day = day; }
void SetDate(Date *date, int year, int month, int day)
{
    date->year = year;
    date->month = month;
    date->day = day;
}

char *GetDateString(const Date *date)
{
    char *str = calloc(10, sizeof(str));
    sprintf(str, "%04d-%02d-%02d", GetYear(date), GetMonth(date), GetDay(date));
    return str;
}
void DestroyDateString(char **p)
{
    free(*p);
    *p = NULL;
}

const int DAYS_MONTH[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int get_days_in_month(int year, int month)
{
    if (year % 4 != 0 || month != 2)
        return DAYS_MONTH[month - 1];
    else
    {
        if (year % 100 == 0)
            if (year % 400 == 0)
                return 29;
            else
                return 28;
        else
            return 29;
    }
}

void IncreaseDate(Date *date)
{
    date->day++;
    if (date->day > get_days_in_month(date->year, date->month))
    {
        date->month++;
        if (date->month > 12)
        {
            date->year++;
            date->month = 1;
        }
        date->day = 1;
    }
}
void DecreaseDate(Date *date)
{
    date->day--;
    if (date->day <= 0)
    {
        date->month--;
        if (date->month <= 0)
        {
            date->year--;
            date->month = 12;
        }
        date->day = get_days_in_month(date->year, date->month);
    }
}
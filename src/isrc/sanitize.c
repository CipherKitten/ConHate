#include <string.h>
/**
 * Trims the spaces from the beginning and end of a string
 * */
void trimstr(char** str){
    int start = 0;
    int end = strlen(*str);
    while((*str)[start] == ' ') start++;
    while((*str)[end-1] == ' ') end--;
    char trimmed[end-start];
    strncpy(trimmed, *str + start, end-start);
    trimmed[end] = '\0';
    *str = trimmed;
}

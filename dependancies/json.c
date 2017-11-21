#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../main.h"


// this function will format the name value pair passed in and append it to the current
// JSON string. It will work if curr_json is NULL but not if name or value are null
// This function will return a pointer to newly allocated
// memory which must me freed
char* add_name_value_pair(char* curr_json, const char* name,const void*  value, int data_type)
{
	// make this string large since
	// we have to send the entire map
	char formatted_npv[2000];
	int curr_json_len = (curr_json == NULL) ? 0 : strlen(curr_json);
	char* result;										     // json string after we append

	// For now since we are only printing integers and strings we can
	// just use an if else instead of a switch statment, but it can be
	// modified later to include more data types
	if(data_type == INTEGER)
		sprintf(formatted_npv, "\"%s\":%d}", name, *(int*)value);
	else
		sprintf(formatted_npv, "\"%s\":\"%s\"}", name, (char*)value);
	
	result = (char *)malloc(sizeof(char) * (curr_json_len + strlen(formatted_npv) + 1)); // allocate more memory for new entry
	if(curr_json){ 												// copy over the original data if it exits
		strcpy(result, curr_json);				  // copy over original data
		result[curr_json_len - 1] = ',';  	// set the closing brace to a comma since we are appending to it
	}
	else{
	  result[0] = '{';										// if this is the first entry, then set the first char to opening brace
		result[1] = '\0'; 
	}
	strcat(result, formatted_npv);				// copy over new entry

	if(curr_json)
		free(curr_json);									  // lets just free it here, since we wont be needing anymore

	return result;
}

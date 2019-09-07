#include "pjson.h"
#include <string.h>


void getValueFromBody(request * r, const char * field, void * arg)
{
    json_object * object;
    object = json_tokener_parse(r->body);
    struct json_object * field_object = json_object_object_get(object, field);
    enum json_type field_type = json_object_get_type(field_object);

    int iVal;
    char * sVal;
    switch(field_type){
    case json_type_int:
        iVal = (int)json_object_get_int(field_object);
        memcpy((int *)arg, &iVal, sizeof(int));
        break;

    case json_type_string:
        sVal = (char *)json_object_get_string(field_object);
        strncpy((char *)arg, sVal, strlen(sVal)); 
        break;
    }

    json_object_put(object);
    json_object_put(field_object);

    return;
}

void setValueToBody(responseWriter * w, const char * field, void * arg, int flag)
{
    json_object * new_obj;
    if (*(w->body) == '\0')
    {
        new_obj = json_object_new_object();
    }
    else 
    {
        new_obj = json_tokener_parse(w->body);
    }

    char * json_string;
    if (flag == INT_MODE)
    {
        json_object_object_add(new_obj, field, json_object_new_int((int)arg));
    }
    else if (flag == STRING_MODE)
    {
        json_object_object_add(new_obj, field, json_object_new_string((char *)arg));
    }

    json_string = (char *)json_object_to_json_string(new_obj);
    strncpy(w->body, json_string, strlen(json_string));
    
    //printf("s = %s\n", json_object_get_string(new_obj));

    json_object_put(new_obj);
    return ;
}

#ifndef _LOGIN_H__
#define _LOGIN_H__
#include <stdbool.h>
#include "phttp.h"
#include "route.h"


#define REGISTERED_SUCCESSFULLY 0
#define REGISTERED_FAILED 1
#define LOGIN_SUCCESSFULLY 0
#define USERNAME_ERROR 2
#define PASSWORD_ERROE 3

extern void * userRegister(responseWriter, request *);
extern void *userLogin(responseWriter, request *);

extern bool add_user(const char * uname, const char * password, const char * phoneNO);
extern int allow_login(const char * uname, const char * password);
extern void delete_user(const char * uname);
extern bool userExist(const char * userName);

#endif

#ifndef _LOGIN_H__
#define _LOGIN_H__
#include <stdbool.h>
#include "phttp.h"
#include "route.h"

extern void * userRegister(responseWriter, request *);
extern void *userLogin(responseWriter, request *);

extern bool add_user(const char * uname, const char * password);
extern bool allow_login(const char * uname, const char * password);
extern void delete_user(const char * uname);

#endif

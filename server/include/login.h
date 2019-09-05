#ifndef _LOGIN_H__
#define _LOGIN_H__
#include <stdbool.h>

extern bool add_user(const char * uname, const char * password);
extern bool allow_login(const char * uname, const char * password);
extern void delete_user(const char * uname);

#endif

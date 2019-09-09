#ifndef _PASSWORD_H__
#define _PASSWORD_H__

#include <stdbool.h>
#include "phttp.h"
#include "route.h"

#define REQUEST_SUCCESSFUL 0
#define USERNAME_ERROR 2
#define PHONE_NO_ERROE 3
#define VERIFICATION_CODE_ERROE 6
#define CHANGE_PASSWORD_SUCCEFUL 1

extern void * forgotPassword(responseWriter w, request * r);
extern void * sendOldPassword(responseWriter w, request * r);
extern void * changePassword(responseWriter w, request * r);

#endif 

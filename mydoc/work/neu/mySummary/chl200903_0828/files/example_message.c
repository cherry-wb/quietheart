/**
 * This file is part of maemo-examples package
 * 
 * This maemo code example is licensed under a MIT-style license,
 * that can be found in the file called "COPYING" in the same
 * directory as this file.
 * Copyright (c) 2007-2008 Nokia Corporation. All rights reserved.
 */

#include <libosso.h>

#define OSSO_EXAMPLE_NAME    "example_libosso"
#define OSSO_EXAMPLE_SERVICE "org.maemo."OSSO_EXAMPLE_NAME
#define OSSO_EXAMPLE_OBJECT  "/org/maemo/"OSSO_EXAMPLE_NAME
#define OSSO_EXAMPLE_IFACE   "org.maemo."OSSO_EXAMPLE_NAME
#define OSSO_EXAMPLE_MESSAGE "HelloWorld"

int main(int argc, char *argv[])
{
    osso_context_t *osso_context;
    osso_rpc_t retval;
    osso_return_t ret;

    /* Initialize maemo application */
    osso_context = osso_initialize(OSSO_EXAMPLE_SERVICE, "0.0.1", TRUE, NULL);

    /* Check that initialization was ok */
    if (osso_context == NULL) {
        return OSSO_ERROR;
    }

    ret = osso_rpc_run(osso_context, 
		       OSSO_EXAMPLE_SERVICE, 
		       OSSO_EXAMPLE_OBJECT, 
		       OSSO_EXAMPLE_IFACE, 
		       OSSO_EXAMPLE_MESSAGE, &retval, DBUS_TYPE_INVALID);/*关键发送消息*/

    osso_rpc_free_val(&retval);

    osso_deinitialize(osso_context);
    
    return 0;
}


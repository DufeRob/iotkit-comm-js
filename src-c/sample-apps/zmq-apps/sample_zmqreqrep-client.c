/*
 * ZMQ REQ/REP sample program through Edison API
 * Copyright (c) 2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 */

/** @file sample_zmqreqrep-client.c

    Sample client program of ZMQ REQ/REP

 */

#include <stdio.h>
#include <cJSON.h>
#include <stdbool.h>
#include <sys/types.h>
#include "edisonapi.h"
#include "util.h"

/** Callback function. To to be invoked when it receives any messages from the Service
* @param message the message received from service
* @param context a context object
 */
void reqMessageCallback(char *message, Context context) {
    fprintf(stderr,"Message received in Client: %s\n", message);
}

/** Callback function. Once the service is discovered this callback function will be invoked

* @param servQuery the client query object
* @param error_code the error code
* @param commHandle the communication handle used to invoke the interfaces
 */
void reqDiscoveryCallback(ServiceQuery *servQuery, int32_t error_code, CommClientHandle *commHandle)
{
        if (commHandle != NULL) {
        Context context;
        while (1) {
            commHandle->send("toys",context);
            commHandle->receive(reqMessageCallback);
            sleep(2);
        }
        } else {
            puts("\nComm Handle is NULL\n");
        }

}

/** The starting point. Starts browsing for the given Service name
*/
int main(void) {

	puts("Sample program to test the Edison ZMQ req/rep plugin !!");
    ServiceQuery *query = (ServiceQuery *) parseClientServiceQuery("../serviceQueries/temperatureServiceQueryZMQREQREP.json");

    if (query) {
        fprintf(stderr,"query host address %s\n",query->address);
        fprintf(stderr,"query host port %d\n",query->port);
        fprintf(stderr,"query service name %s\n",query->service_name);
	    WaitToDiscoverServices(query, reqDiscoveryCallback);
	}

	return 0;
}


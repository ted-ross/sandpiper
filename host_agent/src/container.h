#ifndef HOST_AGENT_CONTAINER_H
#define HOST_AGENT_CONTAINER_H 1
/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

typedef struct sp_container_t;

typedef enum {
    SP_CONTAINER_STATE_IDLE,
    SP_CONTAINER_STATE_PULLING,
    SP_CONTAINER_STATE_PRE_RUN,
    SP_CONTAINER_STATE_RUNNING,
    SP_CONTAINER_STATE_STOPPED
} sp_container_state_t;

typedef void (*sp_container_notify_t) (void *context, sp_container_state_t state);

/**
 * Create a new container
 *
 * @param image The name of the image
 * @param cb Callback for notifications or 0 if not needed
 * @param cb_context Opaque context for the notify callback
 * @return A pointer to the new sp_container object or 0 if there was an error.
 */
sp_container_t *sp_container(const char *image, sp_container_notify_t cb, void *cb_context);

/**
 * Free a container object
 *
 * @param c Pointer to an sp_container object created by sp_container()
 */
void sp_container_free(sp_container_t *c);

/**
 * Set the network option for the container (defaults to "none")
 *
 * @param c Pointer to an sp_container object created by sp_container()
 * @param net Network (--net) option for the container
 */
void sp_container_set_network(sp_container_t *c, const char *net);

/**
 * Set argument for container launch
 *
 * @param c Pointer to an sp_container object created by sp_container()
 * @param arg Argument text
 * @param value Argument value or 0 if no value is needed
 */
void sp_container_set_arg(sp_container_t *c, const char *arg, const char *value);

/**
 * Set an environment variable for the interior of the container
 *
 * @param c Pointer to an sp_container object created by sp_container()
 * @param var Variable name
 * @param value Variable's value
 */
void sp_container_set_env(sp_container_t *c, const char *var, const char *value);

/**
 * Start the process of running the container.  This function does not block
 * waiting for completion.  Use the notify callback to track the progress of
 * the container's lifecycle.
 *
 * @param c Pointer to an sp_container object created by sp_container()
 */
void sp_container_run(sp_container_t *c);

/**
 * Start the processe of stopping a container.
 *
 * @param c Pointer to an sp_container object created by sp_container()
 */
void sp_container_stop(sp_container_t *c);

/**
 * Get the lifecycle state of the container.
 *
 * @param c Pointer to an sp_container object created by sp_container()
 * @return Current state of the container's lifecycle
 */
sp_container_state_t sp_container_state(sp_container_t *c);


#endif

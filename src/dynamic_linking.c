/*
 * Copyright 2021-2024 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "p101_dynamic_linking/dynamic_linking.h"
#include <dlfcn.h>
#include <p101_env/wrapper.h>

static int dl_error_code(void);

static int dl_error_code(void)
{
    int err_code;

    err_code = errno;

    if(err_code == 0)
    {
        err_code = EINVAL;
    }

    return err_code;
}

int p101_dlclose(const struct p101_env *env, struct p101_error *err, void *handle)
{
    char resource_id[P101_ENV_POINTER_RESOURCE_ID_SIZE];
    int  ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_SYSTEM(env, err, ret_val, -1);
    p101_env_pointer_resource_id(resource_id, sizeof(resource_id), handle);
    errno   = 0;
    ret_val = dlclose(handle);

    if(ret_val != 0)
    {
        char       *raw_message;
        const char *str;
        int         err_code;

        err_code    = dl_error_code();
        raw_message = dlerror();
        str         = raw_message;
        P101_ERROR_RAISE_SYSTEM(err, str, err_code);
    }
    else
    {
        P101_TRACK_RESOURCE_RELEASE(env, "dynamic-library", resource_id, NULL);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

char *p101_dlerror(const struct p101_env *env)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dlerror();

    P101_TRACE_EXIT(env);
    return ret_val;
}

void *p101_dlopen(const struct p101_env *env, struct p101_error *err, const char *file, int mode)
{
    void *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_SYSTEM(env, err, ret_val, NULL);
    errno   = 0;
    ret_val = dlopen(file, mode);

    if(ret_val == NULL)
    {
        char       *raw_message;
        const char *str;
        int         err_code;

        err_code    = dl_error_code();
        raw_message = dlerror();
        str         = raw_message;
        P101_ERROR_RAISE_SYSTEM(err, str, err_code);
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, "dynamic-library", ret_val, 0U, file);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

void *p101_dlsym(const struct p101_env *env, struct p101_error *err, void *restrict handle, const char *restrict name)
{
    char       *raw_message;
    const char *msg;
    int         err_code;
    void       *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN_SYSTEM(env, err, ret_val, NULL);
    errno       = 0;
    raw_message = dlerror();
    (void)raw_message;
    ret_val     = dlsym(handle, name);
    err_code    = dl_error_code();
    raw_message = dlerror();
    msg         = raw_message;

    if(msg != NULL)
    {
        P101_ERROR_RAISE_SYSTEM(err, msg, err_code);
    }

    P101_WRAPPER_DONE(env);
    return ret_val;
}

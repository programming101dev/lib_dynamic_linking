#ifndef LIBP101_DYNAMIC_LINKING_P101_DLFCN_H
#define LIBP101_DYNAMIC_LINKING_P101_DLFCN_H

/*
 * Copyright 2026 D'Arcy Smith.
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

#ifndef LIBP101_DYNAMIC_LINKING_SHARED_DECLARATIONS
    #define LIBP101_DYNAMIC_LINKING_SHARED_DECLARATIONS
    #include <p101_env/env.h>
    #include <p101_error/attributes.h>
#endif    // LIBP101_DYNAMIC_LINKING_SHARED_DECLARATIONS

#ifdef __cplusplus
extern "C"
{
#endif

    int   p101_dlclose(const struct p101_env *env, struct p101_error *err, void *handle);
    char *p101_dlerror(const struct p101_env *env);
    void *p101_dlopen(const struct p101_env *env, struct p101_error *err, const char *file, int mode) P101_ATTR_WARN_UNUSED_RESULT;
    void *p101_dlsym(const struct p101_env *env, struct p101_error *err, void *restrict handle, const char *restrict name) P101_ATTR_WARN_UNUSED_RESULT;

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_DYNAMIC_LINKING_P101_DLFCN_H

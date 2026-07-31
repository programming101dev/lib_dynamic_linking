#include <dlfcn.h>
#include <p101_dynamic_linking/dynamic_linking.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;
    char              *message;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }

    (void)dlopen("/p101/this/library/does/not/exist", RTLD_NOW);
    /* P101_TEST_CASE(p101_dlerror) */
    message = p101_dlerror(env);

    p101_env_destroy(env);
    p101_error_destroy(err);
    return message == NULL ? EXIT_FAILURE : EXIT_SUCCESS;
}

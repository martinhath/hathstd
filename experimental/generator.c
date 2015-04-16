#include "../hathstd.h"

Generator *generator_create(void *init, void* (*f)(void*)) {
    Generator *gen = emalloc(sizeof(Generator));
    gen->val = init;
    gen->f = f;
    return gen;
}

void *generator_next(Generator *generator) {
    void *v = generator->val;
    void *next = generator->f(v);
    generator->val = next;
    return next;
}

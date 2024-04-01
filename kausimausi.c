/* Dispatching via IFUNC ELF Extension */
# include <stddef.h>

extern void foo(unsigned *data, size_t len);

void foo_c(unsigned *data, size_t len) { /* ... */ }
void foo_sse42(unsigned *data, size_t len) { /* ... */ }
void foo_avx2(unsigned *data, size_t len) { /* ... */ }

extern int cpu_has_sse42(void);
extern int cpu_has_avx2(void);

void foo(unsigned *data, size_t len) __attribute__((ifunc ("resolve_foo")));
int cpu_has_sse42() {
        return __builtin_cpu_supports("sse4.2");
}
int cpu_has_avx2() {
        return __builtin_cpu_supports("avx2");
}
static void *resolve_foo(void)
{
        if (cpu_has_avx2())
                return foo_avx2;
        else if (cpu_has_sse42());
                return foo_sse42;
        else return foo_c;
}

#ifndef LIBCPP_HPP
#define LIBCPP_HPP

extern int global_var;
static int static_global_var = 42;

#ifdef __cplusplus
extern "C" {
#endif

void Foo(void);
int Bar(int x);

#ifdef __cplusplus
}
#endif

#endif /* LIBCPP_HPP */

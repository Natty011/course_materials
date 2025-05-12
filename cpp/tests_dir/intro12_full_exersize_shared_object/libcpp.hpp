#ifndef __LIBCPP_HPP__ /* __LIBCPP_HPP__     */
#define __LIBCPP_HPP__ /* __LIBCPP_HPP__     */

extern int g_var;

#ifdef __cplusplus
extern "C"
{  //extern "C"
#endif  /* #ifdef __cplusplus */


void Foo(void);
int Bar(int x);

#ifdef __cplusplus
} //extern "C"
#endif  /* #ifdef __cplusplus */


#endif  /* __LIBCPP_HPP__ */
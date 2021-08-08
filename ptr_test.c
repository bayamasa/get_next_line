#include <stdio.h>
#include "get_next_line.h"

// void check_ptr(t_list *a)
// {
// 	a = malloc(sizeof(t_list));
// 	printf("%p\n", a);
// 	a->fd = 1;
// 	printf("%d\n", a->fd);
// }

// int main()
// {
// 	// これだとstaticの初期化なのでコンパイルが通る
// 	// かつ、aはポインタの初期化なのでNULL
// 	// ただ、check_ptrでmallocをしている。
// 	// この場合check_ptr内でmallocをしているので、main関数の中ではaに対するアドレス値をもっていない。
// 	static t_list *a;
// 	check_ptr(a);
// 	printf("%p\n", a);
// 	printf("%d\n", a->fd);
// }

void check_ptr(t_list *a)
{
	printf("%p\n", a);
	//この書き方であればアドレス値を変更することが可能
	// a->fd = 1;
	// こっちでもいけた
	// (*a).fd = 1;
	printf("%d\n", a->fd);
}

int main()
{
	// これだとstaticの初期化なのでコンパイルが通る
	// かつ、aはポインタの初期化なのでNULL
	// こっちのやり方だと、main関数で初期化しているので通る。

	static t_list *a;
	a = malloc(sizeof(t_list));

	check_ptr(a);
	printf("%p\n", a);
	printf("%d\n", a->fd);
}

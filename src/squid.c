#define TB_IMPL
#include"termbox2.h"
#include"sloth.h"
#include<stdio.h>
#include<stdint.h>

// UINTPTR_MAX lu representation is 20 characters long

// 20+2+2 for the stack (at the left)
// 20+2+2 for the return stack (at the right)
// 68 for stacks, 36 expandible for the middle part

void draw_stack(X* x) {
	int i, j;
	tb_print(0, 0, 0, 0, "┎─ Data Stack ─────────┒");
	for (i = 1; i < tb_height() - 1; i++) tb_printf(0, i, 0, 0, "│                      │");
	tb_print(0, tb_height() - 1, 0, 0, "┖──────────────────────┚");
	for (i = x->sp - 1, j = 1; i >= 0 && j < tb_height() - 4; i--, j++) {
		tb_printf(2, j, 0, 0, "%20ld", x->s[i]);
	}
	tb_present();
}

void draw_ip(X* x) {
	int i;
	tb_print(24, 0, 0, 0, "┎─ IP ");
	for (i = 30; i < tb_width() - 25; i++) {
		tb_print(i, 0, 0, 0, "─");
	}
	tb_print(tb_width() - 25, 0, 0, 0, "┒");
	tb_print(24, 1, 0, 0, "│");
	tb_print(tb_width() - 25, 1, 0, 0, "│");
	tb_print(24, 2, 0, 0, "┖");
	for (i = 25; i < tb_width() - 25; i++) {
		tb_print(i, 2, 0, 0, "─");
	}
	tb_print(tb_width() - 25, 2, 0, 0, "┚");
	tb_printf(26, 1, TB_BLACK, TB_YELLOW, "%c", *x->ip);
	tb_printf(27, 1, 0, 0, "%.*s", tb_width() - 51, x->ip + 1);
	tb_present();
}

void draw_return_stack(X* x) {
	int i, j;
	tb_print(tb_width() - 24, 0, 0, 0, "┎─ Return Stack ───────┒");
	for (i = 1; i < tb_height() - 1; i++) tb_printf(tb_width() - 24, i, 0, 0, "│                      │");
	tb_print(tb_width() - 24, tb_height() - 1, 0, 0, "┖──────────────────────┚");
	for (i = x->rp - 1, j = 1; i >= 0 && j < tb_height() - 4; i--, j++) {
		tb_printf(tb_width() - 22, j, 0, 0, "%.20s", x->r[i]);
	}
	tb_present();
}

int main(int argc, char** argv) {
	struct tb_event ev;
	X* x = S_init(x);

	S_lit(x, 7);
	S_lit(x, 11);	
	x->ip = "1 1 34[so+]t";
	x->r[x->rp++] = "[1 1+][7]?";
	x->r[x->rp++] = "\\test _[ds$]q";

	tb_init();

	draw_stack(x);
	draw_ip(x);
	draw_return_stack(x);

	tb_poll_event(&ev);
	tb_shutdown();
/*
	struct tb_event ev;
  int y = 0;

  tb_init();

  tb_printf(0, y++, TB_GREEN, 0, "hello from termbox");
  tb_printf(0, y++, 0, 0, "width=%d height=%d", tb_width(), tb_height());
  tb_printf(0, y++, 0, 0, "press any key...");
  tb_present();

  tb_poll_event(&ev);

  y++;
  tb_printf(0, y++, 0, 0, "event type=%d key=%d ch=%c", ev.type, ev.key, ev.ch);
  tb_printf(0, y++, 0, 0, "press any key to quit...");
  tb_present();

  tb_poll_event(&ev);
  tb_shutdown();

	printf("%lu\n", UINTPTR_MAX);
*/
  return 0;
}

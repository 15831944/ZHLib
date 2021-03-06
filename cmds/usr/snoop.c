// snoop.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if (! interactive(me))
		return 0;

	if (! arg)
	{
		if (objectp(ob = query_snooping(me)))
			write("你现在正在监听" + ob->query("name") +
			      "所收到的讯息。\n");
		return 1;
        } else if (arg == "-none")
	{
		snoop(me);
		write("Ok.\n");
		return 1;
	}

	ob = find_player(arg);
	if (! ob) ob = find_living(arg);
	if (! ob || ! me->visible(ob))
		return notify_fail("没有这个人。\n");

	if (! interactive(ob))
		return notify_fail("这个玩家不在线上，无法监听。\n");

        if (!wizardp(me) && ! is_sub(me->query("id"), ob->query("env/can_snoop")))
		return notify_fail("这个玩家不允许你监听。\n");

	if (wiz_level(ob) > wiz_level(me))
		return notify_fail("你的权限不够监听对方。\n");

	if (me == ob) return notify_fail("请用 snoop none 解除监听。\n");
		
	snoop(me, ob);
	write("你现在开始窃听" + ob->name(1) + "所收到的讯息。\n");
	if (playerp(ob)) log_file("snoop",
		sprintf("%s(%s-%s) snoops %s on %s.\n", me->name(1),
			geteuid(me), query_ip_number(ob), ob->name(1),
			ctime(time()) ) );

	return 1;
}

int help()
{
	write(@TEXT
指令格式：snoop <某人>|-none

监听其他使用者所收听的讯息，snoop -none 则取消监听。你监听
对方的前提是对方允许你这么做，即设置了can_snoop为你的ID。
TEXT );
	return 1;
}


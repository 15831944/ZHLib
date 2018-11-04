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
			write("���������ڼ���" + ob->query("name") +
			      "���յ���ѶϢ��\n");
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
		return notify_fail("û������ˡ�\n");

	if (! interactive(ob))
		return notify_fail("�����Ҳ������ϣ��޷�������\n");

        if (!wizardp(me) && ! is_sub(me->query("id"), ob->query("env/can_snoop")))
		return notify_fail("�����Ҳ������������\n");

	if (wiz_level(ob) > wiz_level(me))
		return notify_fail("���Ȩ�޲��������Է���\n");

	if (me == ob) return notify_fail("���� snoop none ���������\n");
		
	snoop(me, ob);
	write("�����ڿ�ʼ����" + ob->name(1) + "���յ���ѶϢ��\n");
	if (playerp(ob)) log_file("snoop",
		sprintf("%s(%s-%s) snoops %s on %s.\n", me->name(1),
			geteuid(me), query_ip_number(ob), ob->name(1),
			ctime(time()) ) );

	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��snoop <ĳ��>|-none

��������ʹ������������ѶϢ��snoop -none ��ȡ�������������
�Է���ǰ���ǶԷ���������ô������������can_snoopΪ���ID��
TEXT );
	return 1;
}


// time.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	write(sprintf("%s���ڵ�ʱ���ǣ�%s��\n" ,
                      HIR MUD_NAME NOR,
                      NATURE_D->game_time()));
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ������(��)֪�����ڵ�ʱ����

HELP
    );
    return 1;
}

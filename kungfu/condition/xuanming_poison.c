#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "xuanming_poison"; }

string chinese_name() { return "��ڤ����"; }

string update_msg_others()
{
       return MAG "$N��ɫ���ϣ�ȫ��ס�Ĳ��������ظ�����졣\n" NOR;
}

string update_msg_self()
{
        return MAG "ֻ�е�һ���溮��������Ȼ����������������������������ڤ����֮�������ˣ�\n" NOR;
}
int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 4;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 4;
}



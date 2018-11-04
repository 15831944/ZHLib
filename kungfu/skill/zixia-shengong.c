// zixia-shengong.c ��ϼ��
// By Hop

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force) { return force == "huashan-xinfa"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("zixia-shengong", 1);
        return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if (me->query("gender") == "����" &&
	    (int)me->query_skill("zixia-shengong", 1) > 49)
		return notify_fail("���޸����ԣ������������������������ϼ�񹦡�\n");

	if ((int)me->query_skill("force", 1) < 60)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ��ϼ�񹦡�\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��ϼ��ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return __DIR__"zixia-shengong/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short"   : me->name()+"�������ϣ���ɫ���أ����������뵡�",
"start_self"    : HIM"��͵���������ʹ��ϼ�����ˣ���Ϣ�������ƣ�����ģ����񽬣������أ�ߵ��������ͨ�������硣\n"NOR,
"on_self"       : MAG"�����������������ƣ�����ģ����񽬣������أ�ߵ���������ƴ��к�ת��\n"NOR,
"start_other"   : MAG+me->name()+ "�͵�������������������ʼ�˹����ˡ�\n"NOR,
"finish_self"   : HIM"�������ϼ�����˶�ʱ��һ��������������ת�ް��������Ѿ�ƽ��������վ��������\n",
"finish_other"  : MAG"����"+ me->name()+ "ͷ����������������������ʢ����Ȼ��һ����Х��վ��������\n"NOR,
"unfinish_self" : "�����������˼䣬����������飬�������̣�ֻ���ݻ����ˡ�\n",
"unfinish_other": me->name()+"��������������ȥ����������������Ϣ��\n",
"halt_self"     : "�㽫��ϼ����ѹ�����ڣ�վ��������\n",
"halt_other"    : me->name() +"��������ͻȻɢȥ��վ������������ȥ������һЩ��\n",
        ]);
}

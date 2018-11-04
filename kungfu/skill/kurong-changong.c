// kurong-changong.c ��������
#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
    return force == "duanshi-xinfa";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("kurong-changong", 1);
    return lvl * lvl * 18 * 15 / 100 / 200;
}

int valid_learn(object me)
{
    if ( me->query("gender") == "����")
    	return notify_fail("���޸����ԣ���������������������������\n");

    return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"kurong-changong/" + func;
}

mapping curing_msg(object me)
{
        return ([
"apply_short"	:me->name()+"һ����ɫ������棬һ������״�ƿݹǣ������˹����ˡ�",
"start_self"	:HIY"�����ȶ������߷�������������ʼ�˹����ˡ�\n"NOR,
"start_other"	:WHT""+me->name()+NOR+WHT+"���ȶ��������Ͽ��ٽ��棬����������棬����״�ƿݹǡ�\n"NOR,
"on_self"	:WHT"��о����������������棬һ�ɱ���һ�ɻ��ȣ��������������������𽥺�ת��\n"NOR,
"finish_self"	:HIY"��о����������������ڣ������泩�����˾�ȥ������һ����վ��������\n"NOR,
"finish_other"	:me->name()+"����һ������վ������������ȥ������棬�����ӡ�\n",
"unfinish_self"	:"�����Կ����ķ��������ˣ�����������̷��������վ���������ݻ����ˡ�\n",
"unfinish_other":me->name()+"վ������������״�ƿݹǣ�����͸��Щ���⡣\n",
"halt_self"	:"��������Ϣ��Ӳ�����ؽ���������ѹ����ȥ��վ��Ų���\n",
"halt_other"	:me->name() +"ҡ����վ�������������ݻ�֮ɫ���³�һ����Ѫ����ɫ�����ָ�������\n",
"dazuo"		:"���������£�������������������һ��һ�ȣ��б�ȫ���ܶ���ʼ��\n",
"tuna"		:"���������£���������������������������������������Բ������Ƚ��棬������̹��\n",
        ]);
}

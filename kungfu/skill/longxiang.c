//
// longxiang.c ���������
//

#include <ansi.h>
inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "mizong-neigong" ||
	       force == "xiaowuxiang";
}

int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("longxiang", 1);
    return lvl * lvl * 15 * 15 / 100 / 200;
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 70)
		return notify_fail("��Ļ����ڹ���򻹲�����\n");

	if ( me->query("gender") == "����" && (int)me->query("longxiang", 1) > 49)
		return notify_fail("���޸����ԣ���������������������������������\n");

    	if (me->query("str") < 30)
        	return notify_fail("�������������㣬�޷�ѧϰ���͵������������\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("���������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"longxiang/" + func;
}
mapping curing_msg(object me)
{
        return ([
"apply_short" :me->name()+"������ָ���������ƣ������Ķ��������������ȡ�",
"start_self" :HIW"����ϥ������������ָ���������ƣ�������������������������֮�����ˡ�\n"NOR,
"on_self" :HIM"�����Ĭ�������������������֮����ת���������������ϡ�\n"NOR,
"start_other" :HIM""+me->name()+"��Ŀ��ׯ���������ϼ䣬����ɢ��ǿ��������\n"NOR,
"finish_self" :HIW"��е�����֮����ת������������һɨ���գ�����վ��������\n"NOR,
"finish_other" :me->name()+"����˫Ŀ���ջ�����������վ����������������\n",
"unfinish_self" :"������������֮�����ˣ�����������飬���������ֻ���ݻ����ˡ�\n",
"unfinish_other":me->name()+"����˫Ŀ������վ����ɫƣ�������Ժ��ۡ�\n",
"halt_self" :"������һ����������������ǿ���ջص��վ��������\n",
"halt_other" :me->name() +"����һ������üͷ΢�壬վ��������\n",
        ]);
} 

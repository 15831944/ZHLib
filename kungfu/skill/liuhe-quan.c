// /kungfu/skill/liuhe-quan.c ����ȭ
// By Alf, Last Update 2002.03
// ����Ȫ���۵����ɡ���ɨǧ�����ӹ�����
// ����էչ����ˮ���ۡ����ͻ�𡡻������

#include <ansi.h>
inherit SKILL;

mapping *action =
({
([
        "action":   "$N������$nһת�����ĳ�ȭ��һ�С�����Ȫ����ֱ��$n��$l",
        "dodge": -10,
        "parry": -10,
        "force": 120,
        "damage_type": "����"
]),
([
        "action":   "$N��������һʽ���۵����ɡ���˫ȭ���ϻ��䣬��ȡ$n��$l",
        "dodge": -20,
        "parry": -20,
        "force": 150,
        "damage_type": "����"
]),
([
        "action":   "$N��ʽ��Ȼһ�䣬һʽ����ɨǧ����չ������$n��$l��������",
        "dodge": -10,
        "parry": -10,
        "force": 180,
        "damage_type": "����"
]),
([
        "action":   "$N��һ�䣬ʹ�С��ӹ���������˫ȭȦת�����һ���$n��$l",
        "dodge": -30,
        "parry": -30,
        "force": 210,
        "damage_type": "����"
]),
([
        "action":   "$N�˺�һ����һʽ������էչ����˫�ƻ��裬���Ʋ���$n��$l",
        "dodge": -10,
        "parry": -10,
        "force": 240,
        "damage_type": "����"
]),
([
        "action":   "$N˫ϥ΢����һ�С���ˮ���ۡ���˫ȭ���¶��ϵĻ���$n��$l",
        "dodge": -20,
        "parry": -20,
        "force": 280,
        "damage_type": "����"
]),
([
        "action":   "$N��ȭ��������������Ƴ���һ�С����ͻ�𡹣��ͻ�$n��$l",
        "dodge": -10,
        "parry": -10,
        "force": 300,
        "damage_type": "����"
]),
([
        "action":   "$N˫��ת�˼������Σ�ʹһʽ��������ҡ���бб����$n��$l",
        "dodge": -10,
        "parry": -10,
        "force": 320,
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
        return usage=="unarmed" || usage=="parry";
}

int valid_learn(object me)
{
        if(me->query_temp("weapon")||me->query_temp("secondary_weapon"))
                return notify_fail("������ȭ������֡�\n");
        if((int)me->query("max_neili") < 100)
                return notify_fail("�������̫�����޷�������ȭ��\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if((int)me->query("qi")<40)
                return notify_fail("�������̫���ˡ�\n");
        if((int)me->query("neili")<10)
                return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");
        me->receive_damage("qi",30);
        me->add("neili",-5);
        return 1;
}

string perform_action_file(string action)
{
        return "/kungfu/perform/liuhe-quan/" + action;
}




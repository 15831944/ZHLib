//kuangfeng-jian ���콣
// Made by deaner
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N����Ծ������$w��ӣ�ն��$n��",
    "force" : 140,
    "dodge" : 110,
    "attack"  : 120,
    "damage" : 90,
    "lvl"   : 0,
    "skill_name" : "��ƽ�˾�",
    "damage_type" : "����"
]),
([  "action" : "$N����$w�����������Σ���$n���ұ����ն��",
    "force" : 200,
    "dodge" : 110,
    "attack"  : 130,
    "damage" : 110,
    "lvl"   : 20,
    "skill_name" : "������ӿ",
    "damage_type" : "����"
]),
([  "action" : "$N����һ����ˢˢˢˢ�Ľ�����$n�أ������������Ĵ�����",
    "force" : 240,
    "dodge" : 110,
    "attack"  : 130,
    "damage" : 110,
    "lvl" : 40,
    "skill_name" : "������",
    "damage_type" : "����"
]),
([  "action" : "$N����һ����Х��б����ǰ��$w����ֱ����Ѹ���ޱȣ�����$n��$l",
    "damage" : 150,
    "dodge" : 100,
    "attack"  : 140,
    "force" : 275,
    "lvl"   : 60,
    "skill_name" : "������ɢ",
    "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
    if ((int)me->query_skill("sword", 1) < 60)
        return notify_fail("��Ļ�������̫ǳ��\n");

    if ((int)me->query("max_neili") < 300)
        return notify_fail("�������������\n");
    if ((int)me->query_skill("force", 1) < 60)
        return notify_fail("����ڹ��ķ����̫ǳ��\n");
    if ((int)me->query_skill("dodge", 1) < 60)
        return notify_fail("����Ṧ���̫ǳ��\n");
    if ((int)me->query_dex() < 20)
        return notify_fail("�������������\n");
    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
    if(level >= action[i]["lvl"])
        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("kuangfeng-jian",1);
    for(i = sizeof(action); i > 0; i--)
    if(level > action[i-1]["lvl"])
        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "sword")
        return notify_fail("��ʹ�õ��������ԡ�\n");
    if ((int)me->query("qi") < 50)
        return notify_fail("����������������콣��\n");
    if ((int)me->query("neili") < 100)
                return notify_fail("������������������콣����\n");
     me->add("neili", -20);
     me->receive_damage("qi", 25);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"kuangfeng-jian/" + action;
}

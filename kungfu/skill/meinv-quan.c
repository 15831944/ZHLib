// meinv-quan.c ��Ůȭ
// By Lgg,1998.9
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "ֻ��$Nʹ��"+HIM"���������¡�"+NOR"�������������һ�ݣ���$n�����ӳ�һȭ",
        "force" : 30,
        "dodge" : 30,
        "lvl" : 0,
        "damage": 5,
        "skill_name" : "��������",
        "damage_type" : "����"
]),

([      "action" : "$Nһ��"+HIM"���������ġ�"+NOR"��˫�ִ��ؿڴ���$n�ݳ�",
        "force" : 30,
        "dodge" : 25,
        "lvl" : 20,
        "damage": 20,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ��"+HIM"��������ġ�"+NOR"��˫�۽��������ɨ��$n",
        "force" : 50,
        "dodge" : 20,
        "lvl" : 40,
        "damage": 30,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ��"+HIM"������׹¥��"+NOR"���˵ع���$n����",
        "force" : 70,
        "dodge" : 15,
        "lvl" : 60,
        "damage": 35,
        "skill_name" : "����׹¥",
        "damage_type" : "����"
]),
([      "action" : "$N˫���������£�ʹ��"+HIM"���ļ��麺��"+NOR"���������಻�ϵ��ĳ�",
        "force" : 100,
        "dodge" : 10,
        "lvl" : 80,
        "damage": 45,
        "skill_name" : "�ļ��麺",
        "damage_type" : "����"
]),
([      "action" : "$N������$n��ǰչ�������������һ�㣬������$n������ȭ��������һ��"+HIM"���༧���ȡ�"+NOR,
        "force" : 130,
        "dodge" : 30,
        "lvl" : 100,
        "damage": 50,
        "skill_name" : "�༧����",
        "damage_type" : "����"
]),
([      "action" : "$N��ָ������ȴ��һ��"+HIM"��Ƽ������"+NOR"������$n����",
        "force" : 160,
        "dodge" : 25,
        "lvl" : 130,
        "damage": 55,
        "skill_name" : "Ƽ������",
        "damage_type" : "����"
]),
([      "action" : "$Nʹһ��"+HIM"���༧������"+NOR"���������ѣ�������$n��ȥ��˫��ֱ����ȭ",
        "force" : 190,
        "dodge" : 20,
        "lvl" : 160,
        "damage": 60,
        "skill_name" : "�༧����",
        "damage_type" : "ץ��"
]),
([      "action" : "$Nһ��"+HIM"���������ˡ�"+NOR"����֫��ڱܿ�$n�Ĺ�����������$n��ȥ",
        "force" : 220,
        "dodge" : 15,
        "lvl" : 190,
        "damage": 60,
        "skill_name" : "��������",
        "damage_type" : "����"
]),
([      "action" : "ֻ��$N��������$n���ԣ�����һ��"+HIM"��������̡�"+NOR"���¶�����$nֱ��",
        "force" : 240,
        "dodge" : 15,
        "lvl" : 200,
        "damage": 70,
        "skill_name" : "�������",
        "damage_type" : "����"
]),
([      "action" : "$N����������ѻ������������������ˮ��Ư��һ��ƽ�$n������$n������ȭ��ȴ��һ��"+HIM"�������貨��"+NOR,
        "force" : 280,
        "dodge" : 30,
        "lvl" : 210,
        "damage": 80,
        "skill_name" : "�����貨",
        "damage_type" : "ץ��"
]),
([      "action" : "$Nʹһ��"+HIM"����Ĺ�ľӡ�"+NOR"������֧�ã���������ӳ�����̾һ�������ּ���֮��",
        "force" : 320,
        "dodge" : 25,
        "lvl" : 220,
        "damage": 85,
        "skill_name" : "��Ĺ�ľ�",
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "cuff" || usage=="parry"; }

int vliad_combine(string combo) { return combo == "fireice-strike"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����Ůȭ������֡�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹����޷�ѧ��Ůȭ��\n");

        if ((int)me->query("max_neili") < 450)
                return notify_fail("�������̫�����޷�ѧϰ��Ůȭ��\n");

	if (me->query_skill("cuff", 1) < me->query_skill("meinv-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷������������Ůȭ����\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("meinv-quan", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("�������̫���ˣ�������ϰ��Ůȭ��\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("�������������������ϰ��Ůȭ��\n");

        me->receive_damage("qi", 35);
        me->add("neili", -41);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"meinv-quan/" + action;
}

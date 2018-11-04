// yinlong-bang.c �����޷�
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([        "action":  "$N����Ծ��һ�С�����ն�ߡ�������$w���¶��ϣ�����$n������",
        "force":  160,
        "attack": 108,
        "dodge":  40,
        "damage": 120,
        "lvl" : 15,
        "skill_name" : "����ն��",
        "damage_type":        "����"
]),
([        "action":  "$Nһ�С��������ء�������$wֱ����$n��$l",
        "force":  200,
        "attack": 128,
        "dodge":  -10,
        "damage": 150,
        "lvl" : 20,
        "skill_name" : "��������",
        "damage_type":        "����"
]),
([  "action":  "$Nһ�С�ŭ����硹������$w�ڿ�һ��һ���������࣬�͵���$n��ͷ����",
        "force":  220,
        "attack": 138,
        "dodge":  -15,
        "damage": 220,
        "lvl" : 40,
        "skill_name" : "ŭ�����",
        "damage_type":        "����"
]),
([  "action":  "$N̤��һ��������$n��٬һЦ������$wȴ����ͣ����һ�С�����Ϸ���ɨ��$n��$l",
        "force":  280,
        "attack": 148,
        "dodge":  -30,
        "damage": 260,
        "lvl" : 50,
        "skill_name" : "����Ϸ��",
        "damage_type":        "����"
]),
([  "action":  "$NԾ�ڰ�գ�һ�С����ɷ��衹������$w������ϴ�գ�����Ϸ�����������ֵ�$n����",
        "force":  350,
        "attack": 158,
        "dodge":  -35,
        "damage": 270,
        "lvl" : 60,
        "skill_name" : "���ɷ���",
        "damage_type":        "����"
]),
([  "action":  "$N��ǰ����������$wȦת��磬һ�С�ʯ���쾪��������$nǰ��",
        "force" : 420,
        "attack": 148,
        "dodge" : 20,
        "parry" : 85,
        "damage": 250,
        "lvl" : 75,
        "skill_name" : "ʯ���쾪",
        "damage_type":        "����"
])
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("���������һ�����Ӳ������޷���\n");

        if ((int)me->query("max_neili") < 600)
                return notify_fail("����������㣬û�а취�������޷�������Щ���������ɡ�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ����̫ǳ��û�а취�������޷���\n");

        if ((int)me->query_skill("whip", 1) < 80)
                return notify_fail("��Ļ����޷����̫ǳ��û�а취�������޷���\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("yinlong-bian", 1))
                return notify_fail("��Ļ����޷�ˮƽ���������޷���������������޷���\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("yinlong-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("������������������޷���\n");

        if ((int)me->query("neili") < 90)
                return notify_fail("������������������޷���\n");

        me->receive_damage("qi", 75);
        me->add("neili", -45);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yinlong-bian/" + action;
}

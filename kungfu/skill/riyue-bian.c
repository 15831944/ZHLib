// riyue-bian.c ���±޷�
// modified by Venus Oct.1997

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N����������һ�С���ʯʽ��������$w���ñ�ֱ����׼$n���ظ�Ҫ����������",
        "force" : 180,
        "attack": 60,
        "dodge" : 25,
        "parry" : 15,
        "damage": 60,
        "lvl"   : 0,
        "skill_name" : "��ʯʽ",
        "damage_type": "����"
]),
([      "action": "$N����һת��һ�С��ϴ�ʽ��������$w��������ڿ�һ�����͵���$n��ͷ����",
        "force" : 250,
        "attack": 80,
        "dodge" : 30,
        "parry" : 20,
        "damage": 90,
        "lvl"   : 80,
        "skill_name" : "�ϴ�ʽ",
        "damage_type": "����"
]),
([      "action": "$N������ң�һ�С�����ʽ��������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force" : 260,
        "attack": 95,
        "dodge" : 40,
        "parry" : 25,
        "damage": 120,
        "lvl"   : 100,
        "skill_name" : "����ʽ",
        "damage_type": "����"
]),
([      "action":"$N������ң�һ�С��ֺ�ʽ��������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force" : 280,
        "attack": 110,
        "dodge" : 65,
        "parry" : 30,
        "damage": 150,
        "lvl"   : 120,
        "skill_name" : "�ֺ�ʽ",
        "damage_type": "����"
]),
([      "action":"$N������ң�һ�С��ѿ�ʽ��������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force" : 310,
        "attack": 130,
        "dodge" : 80,
        "parry" : 45,
        "damage": 180,
        "lvl"   : 140,
        "skill_name" : "�ѿ�ʽ",
        "damage_type": "����"
]),
([      "action":"$N������ң�һ�С�������ա�������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force" : 350,
        "attack": 155,
        "dodge" : 100,
        "parry" : 50,
        "damage": 200,
        "lvl"   : 160,
        "skill_name":  "�������",
        "damage_type": "����"
]),
([      "action":"$N������ң�һ�С���շ�ħ��������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force" : 380,
        "attack": 160,
        "dodge" : 125,
        "parry" : 75,
        "damage": 220,
        "lvl"   : 180,
        "skill_name" : "��շ�ħ",
        "damage_type": "����"
]),
([      "action":"$N������ң�һ�С����ޱߡ�������$w��������Ӱ����ɽ������ɨ��$nȫ��",
        "force" : 420,
        "attack": 180,
        "dodge" : 140,
        "parry" : 85,
        "damage": 250,
        "lvl"   : 200,
        "skill_name" : "���ޱ�",
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("���������һ�����Ӳ������޷���\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("����������㣬û�а취�����±޷�������Щ���������ɡ�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫ǳ��û�а취�����±޷���\n");

        if ((int)me->query_skill("whip", 1) < 100)
                return notify_fail("��Ļ����޷����̫ǳ��û�а취�����±޷���\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("riyue-bian", 1))
                return notify_fail("��Ļ����޷�ˮƽ���������޷�������������±޷���\n");

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
        level = (int) me->query_skill("riyue-bian",1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("����������������±޷���\n");

        if ((int)me->query("neili") < 90)
                return notify_fail("����������������±޷���\n");

        me->receive_damage("qi", 75);
        me->add("neili", -85);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"riyue-bian/" + action;
}

// tianyu-qijian.c �����潣
// looo 6/14/2001
inherit SKILL;

mapping *action = ({
([      "action":"$Nʹһʽ������һ�ߡ�������$w����΢�񣬻ó�һ���������$n��$l",
        "force" : 60,
        "dodge"  : 60, 
        "lvl" : 0,
        "skill_name" : "����һ��",
        "damage_type":  "����"
]),
([      "action":"$N������ǰ��ʹ�������羪�硹������$w����һ����������$n��$l",
        "force" : 70,
        "dodge" : 60,
        "damage": 85,
        "lvl" : 30,
        "skill_name" : "���羪��",
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һ�С����ھ��졹��ббһ�������ó�������$n��$l",
        "force" : 90,
        "dodge" : 80,
        "damage": 120,
        "lvl" : 40,
        "skill_name" : "���ھ���",
        "damage_type":  "����"
]),
([      "action":"$N���н����ॳ���һ����һʽ��������ġ���һ���������$n��$l",
        "force" : 90,
        "dodge" : 100,
        "damage": 105,
        "lvl" : 50,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ��ŭ���񻨡�������$w�������������ʹ$n�Ѷ���ʵ���޿ɶ��",
        "force" : 220,
        "dodge" : 150,
        "damage": 130,
        "lvl" : 60,
        "skill_name" : "ŭ����",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬��â���£�һʽ���Ż����ա�����׼$n��$lбб����",
        "force" : 240,
        "dodge" : 105,
        "damage": 135,
        "lvl" : 70,
        "skill_name" : "�Ż�����",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ�������ѩ�������󼱶�������������⣬����$n��$l",
        "force" : 160,
        "dodge"  : 100, 
        "damage": 140,
        "lvl" : 80,
        "skill_name" : "�����ѩ",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ����ӵ�к����$w��ն�������缲�������$n���ؿ�",
        "force" : 220,
        "dodge"  : 100, 
        "damage": 145,
        "lvl" : 100,
        "skill_name" : "��ӵ�к",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ��������ɡ���$wͻȻ���������һƬ���Χ��$nȫ��",
        "force" : 240,
        "dodge" : 150,
        "damage"  : 230, 
        "lvl" : 120,
        "skill_name" : "�������",
        "damage_type":  "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if (me->query_skill("force") < 40)
                return notify_fail("����ڹ���򲻹�������ѧϰ�����潣��\n");

        if (me->query("max_neili") < 200)
                return notify_fail("�����������������ѧϰ�����潣��\n");

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
        level = (int) me->query_skill("tianyu-qijian",1);
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
                return notify_fail("������������������潣��\n");

        if ((int)me->query("neili") < 40)
                return notify_fail("������������������潣��\n");
        me->receive_damage("qi", 40);
        me->add("neili", -25);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianyu-qijian/" + action;
}

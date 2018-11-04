// quanzhen-jian.c ȫ�潣��

inherit SKILL;

mapping *action = ({
([      "action":"$Nʹһʽ��̽��������������$w�������Һ�ɨ����$n��$l",
        "force" : 30,
        "attack": 10,
        "dodge" : 10,
        "damage": 13,
        "lvl" : 0,
        "skill_name" : "̽������",
        "damage_type":  "����"
]),
([      "action":"$N̤��һ�������ɨҶ��������$w���������һ����������$n��$l",
        "force" : 40,
        "attack": 15,
        "dodge" : 20,
        "damage": 14,
        "lvl" : 9,
        "skill_name" : "�ɨҶ",
        "damage_type":  "����"
]),
([      "action":"$N����$wһ����һ�С�˳ˮ���ۡ���ббһ�������ó�������$n��$l",
        "force" : 50,
        "attack": 20,
        "dodge" : 25,
        "damage": 15,
        "lvl" : 18,
        "skill_name" : "˳ˮ����",
        "damage_type":  "����"
]),
([      "action":"$N����$w����������Ȧ��һʽ���ǳڵ�������һ���������$n��$l",
        "force" : 80,
        "attack": 25,
        "dodge" : 30,
        "damage": 25,
        "lvl" : 27,
        "skill_name" : "�ǳڵ���",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ���׺����᡹��������չ������$w����$n��$l",
        "force" : 100,
        "attack": 30,
        "dodge" : 35,
        "damage": 28,
        "lvl" : 36,
        "skill_name" : "�׺�����",
        "damage_type":  "����"
]),
([      "action":"$N����$wбָ���죬һʽ������Į��������׼$n��$lбб����",
        "force" : 120,
        "attack": 33,
        "dodge" : 45,
        "damage": 30,
        "lvl" : 44,
        "skill_name" : "����Į��",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ�������仨�������󼱶�������������⣬����$n��$l",
        "force" : 140,
        "attack": 36,
        "dodge" : 42,
        "damage": 42,
        "lvl" : 52,
        "skill_name" : "�����仨",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ����Ʒ��̨����$w��ն�������缲�������$n���ؿ�",
        "force" : 160,
        "attack": 40,
        "dodge" : 55,
        "damage": 45,
        "lvl" : 60,
        "skill_name" : "��Ʒ��̨",
        "damage_type":  "����"
]),
([      "action":"$Nʹһʽ��������ء�������$w������$n���ؿڣ������ɵ�",
        "force" : 180,
        "attack": 45,
        "dodge" : 55,
        "damage": 56,
        "lvl" : 70,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N����$w����һ�������Ļ��ߣ�����$n��$l��ȴ��һ�С���ʷ������",
        "force" : 200,
        "attack": 50,
        "dodge" : 58,
        "damage": 57,
        "lvl" : 80,
        "skill_name" : "��ʷ����",
        "damage_type":  "����"
]),
([      "action":"$N�ؽ����أ�ʹһʽ��������项���������$w��$n����",
        "force" : 230,
        "attack": 55,
        "dodge" : 65,
        "damage": 68,
        "lvl" : 90,
        "skill_name" : "�������",
        "damage_type":  "����"
]),
([      "action":"$N��������һʽ�������߶�����$w�Ӳ���˼��ĽǶȴ���$n",
        "force" : 240,
        "attack": 57,
        "dodge" : 62,
        "damage": 70,
        "lvl" : 114,
        "skill_name" : "�����߶�",
        "damage_type":  "����"
]),
([      "action":"$Nһʽ���ϵ紩�ơ���$wͻȻ���������һƬ���Χ��$nȫ��",
        "force" : 270,
        "attack": 60,
        "dodge" : 66,
        "damage": 75,
        "lvl" : 129,
        "skill_name" : "�ϵ紩��",
        "damage_type":  "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻵����޷�ѧϰȫ�潣����\n");

        if (me->query("neili") < 200)
                return notify_fail("�������̫��޷�ѧϰȫ�潣����\n");

	if (me->query_skill("sword", 1) < me->query_skill("quanzhen-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷����������ȫ�潣����\n");

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
        level = (int) me->query_skill("quanzhen-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 60)
                return notify_fail("�������������ȫ�潣����\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("�������������ȫ�潣����\n");

        me->receive_damage("qi", 55);
        me->add("neili", -53);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"quanzhen-jian/" + action;
}

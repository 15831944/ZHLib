inherit SKILL;

mapping *action = ({
([      "action": "$N���е�$w����������󽭶�ȥ���Ʋ��ɵ�",
        "force" : 250,
        "attack": 170,
        "dodge" : 30,
        "damage": 150,
        "parry" : 70,
        "lvl"   : 0,
        "damage_type": "����"
]),
([      "action": "$N̤��һ��������$w���һ����������$n��$l",
        "force" : 310,
        "attack": 180,
        "dodge" : 33,
        "parry" : 79,
        "damage": 180,
        "lvl"   : 40,
        "damage_type": "����"
]),
([      "action": "$N����$wһ����һ���̳�������$n��$l��û�а�㻨��",
        "force" : 330,
        "attack": 130,
        "dodge" : 41,
        "parry" : 85,
        "damage": 200,
        "lvl"   : 80,
        "damage_type": "����"
]),
([      "action": "$N����$w΢΢��������Ȼ�̳���һ����������$n��$l",
        "force" : 360,
        "attack": 155,
        "dodge" : 45,
        "parry" : 92,
        "damage": 200,
        "lvl"   : 120,
        "damage_type": "����"
]),
([      "action": "$N���$w����Ȼ��ɨ$n���������",
        "force" : 380,
        "attack": 147,
        "dodge" : 47,
        "parry" : 99,
        "damage": 200,
        "lvl"   : 160,
        "damage_type": "����"
]),
([      "action": "$N���е�$w�������̣��д���һ�������ӹ�$nȫ��",
        "force" : 400,
        "attack": 160,
        "dodge" : 50,
        "parry" : 100,
        "damage": 250,
        "lvl"   : 200,
        "damage_type": "����"
])
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻵����޷�ѧϰ����������\n");

        if (me->query("max_neili") < 2000)
                return notify_fail("�������̫��޷�ѧϰ����������\n");

        if (me->query_str() < 45)
                return notify_fail("����������̫��޷�ѧϰ����������\n");

        if (me->query_skill("force", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("����ڹ����ӻ��������޷��������������������\n");

        if (me->query_skill("sword", 1) < me->query_skill("xuantie-jian", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷��������������������\n");

        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("xuantie-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("�����������������������\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("�����������������������\n");

        me->receive_damage("qi", 70);
        me->add("neili", -90);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xuantie-jian/" + action;
}

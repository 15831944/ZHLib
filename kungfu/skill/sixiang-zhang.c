// sixiang-zhang.c

inherit SKILL;

mapping *action = ({
([     "action" : "$Nһʽ��ȭ��̫������������ƣ����ź����ķ�������$n��$l",
       "force" : 180,
       "dodge" : 20,
       "parry" : 50,
       "lvl" : 0,
       "damage_type" : "����"
]),
([     "action" : "$N��ȭ���գ����ƿ�����������$n��$l������һ�С���ת̫����",
       "force" : 205,
       "dodge" : 20,
       "lvl" : 0,
        "damage_type" : "����"
]),
([     "action" : "$Nʹ�С���ȡ��������˫�ƽ������ַֿ������ھ�����$n��$l",
       "force" : 240,
       "dodge" : 10,
       "parry" : 25,
       "lvl" : 10,
        "damage_type" : "����"
]),
([     "action" : "$Nʹ������ȡ������������������$n����Ӱ��˸���ѽ�$n����Χס",
       "force" : 280,
       "dodge" : 5,
       "parry" : 30,
       "lvl" : 10,
        "damage_type" : "����"
]),
([     "action" : "$N����Խ��ֱ����$n���һ�С���תǬ����˫����غ�˫�����ӳ�������$n�ĺ��ġ�",
       "force" : 290,
       "dodge" : 10,
       "parry" : 35,
       "lvl" : 30,
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
       if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
               return notify_fail("�����Ʊ�����֡�\n");

       if ((int)me->query("max_neili") < 100)
               return notify_fail("�������̫�����޷�������\n");
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
       level   = (int) me->query_skill("sixiang-zhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
       if ((int)me->query("qi") < 30)
               return notify_fail("�������̫���ˡ�\n");
       if ((int)me->query("neili") < 20)
               return notify_fail("������������������ơ�\n");
       me->receive_damage("qi", 30);
       me->add("neili", -10);
       return 1;
}
string perform_action_file(string action)
{
        return __DIR__"sixiang-zhang/" + action;
}

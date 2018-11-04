//yitian-jian.c ���콣��

inherit SKILL;

mapping *action = ({
([        "action" : "$N�ٽ�������������������һʽ�����䳤�ա���$w��$n��$l�����ȥ��",
        "force" : 220,
        "dodge" : 70,
        "attack"  : 120,
        "damage" : 200,
        "lvl" : 0,
        "damage_type" : "����"
]),
([        "action" : "ͻȻ�佣��һ�£���������һ���׺磬$Nʹ��һʽ���������¡����������ӣ�$wֱ��$n��$l",
        "force" : 240,
        "attack"  : 260,
        "dodge" : 90,
        "damage" : 150,
        "lvl" : 10,
        "damage_type" : "����"
]),
([        "action" : "$N��������һ�֣�����$w�����ӳ�һ�С��Ǻ����졹������ɭȻ����$n��$l��ȥ",
        "force" : 270,
        "attack"  : 160,
        "dodge" : 150,
        "damage" : 160,
        "lvl" : 20,
        "damage_type" : "����"
]),
([        "action" : "$Nһ���ӿ��м������£�һ�С���ҡ�Ǻ���,$w���ش���$n��$l",
        "force" : 240,
        "dodge" : 110,
        "attack"  : 180,
        "damage" : 170,
        "lvl" : 30,
        "damage_type" : "����"
]),
([        "action" : "$Nһ��$w�԰���к��������������ֱ����һ������һ�㣬һʽ��������ԡ����ڽ�ز�������ۻ��ն��$n��$l",
        "force" : 250,
        "dodge" : 110,
        "attack"  : 140,
        "damage" : 200,
        "lvl" : 40,
        "damage_type" : "����"
]),
([        "action" : "$N��������һʽ������ȡˮ����$w��Ȼһ��������ǧ�������۶�������������$n��$l",
        "force" : 280,
        "dodge" : 105,
        "attack"  : 200,
        "damage" : 190,
        "lvl" : 50,
        "damage_type" : "����"
]),
([        "action" : "$N��תһʽ�����첻������ٲȻ��ǹ��ꪣ���ɳǧ�$w������������$n���������ؽ���֮��",
        "force" : 300,
        "dodge" : 80,
        "attack" : 150,
        "damage" : 200,
        "lvl" : 60,
        "damage_type" : "����"
]),
([        "action" : "$N�������£�һ�С�˭�����桹��$w��Ȼ��תֱ�ϣ����߰㽣����$n������Ҫ������Χס",
        "force" : 360,
        "dodge" : 100,
        "attack" : 180,
        "damage" : 235,
        "lvl" : 70,
        "damage_type" : "����"
]),
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{

        if ((int)me->query("max_neili") < 600)
                return notify_fail("�������������\n");
        if ((int)me->query_skill("sword", 1) < 80)
                return notify_fail("��Ļ�������̫ǳ��\n");
        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("����ڹ����̫ǳ��\n");
        return 1;
}
mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("yitian-jian",1);
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
                return notify_fail("����������������콣����\n");
        if ((int)me->query("neili") < 100)
                return notify_fail("������������������콣����\n");

        me->receive_damage("qi", 40);
        me->add("neili", -50);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"yitian-jian/" + action;
}


// kongming.c
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nʹ�����ա��־�����ȭ������ȭʽ�������ޣ��ƺ�������������ȴ�־�ֱϮ��$n",
        "force" : 100,
        "dodge" : 5,
        "parry" : 1,
        "lvl" : 0,
        "damage" : 20,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ���������־���ȭ�к����Ϳ�����Ʋ����·�����ȭ��ȴֱָ$n��$l",
        "force" : 120,
        "dodge" : -2,
        "parry" : 2,
        "lvl" : 0,
        "damage" : 20,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ���������־�����ȭ�ƺ��ɶ��д�����������������ʽȴ���ͱ��ˣ��ݺݵػ���$n",
        "force" : 140,
        "dodge" : 3,
        "parry" : -2,
        "lvl" : 6,
        "damage" : 20,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����ɡ��־�����ȭ����������������ػ�������ƮƮ�ػ���$n��$l",
        "force" : 160,
        "dodge" : -5,
        "parry" : -1,
        "lvl" : 12,
        "damage" : 30,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����硹�־�����ȭ����������һ����磬$n�վ������壬ȭ�о���Ϯ������ǰ",
        "force" : 180,
        "dodge" : -3,
        "parry" : 2,
        "lvl" : 20,
        "damage" : 30,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ����ͨ���־���ȭ���۶���ɢ�����д�֮ͨ�Σ�ֱ��$n��$l",
        "force" : 200,
        "dodge" : 5,
        "parry" : -3,
        "lvl" : 28,
        "damage" : 30,
        "skill_name" : "ͨ�־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����ݡ��־���ȭ�߿�����������ݣ�����ʵ�أ�������$n���ض�ȥ",
        "force" : 220,
        "dodge" : 1,
        "parry" : 1,
        "lvl" : 35,
        "damage" : 40,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����Ρ��־���ȭ�����Σ����ڰ��ΰ��ѣ�$nһʱ��ڣ�ȭ����Ȼ����",
        "force" : 250,
        "dodge" : 4,
        "parry" : -1,
        "lvl" : 40,
        "damage" : 40,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����塹�־�����ȭֱ����ȭʽ�������ᣬ��$n��$l��ȥ",
        "force" : 280,
        "dodge" : 3,
        "parry" : 2,
        "lvl" : 46,
        "damage" : 40,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ������־��������ʵ�֮�Σ�ȭ����Ȼ�Գ���;ĩ·��ȴ����ɱ������$n��������ʩ��ȭ",
        "force" : 310,
        "dodge" : -3,
        "parry" : 0,
        "lvl" : 53,
        "damage" : 70,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����С��־�����ȭ������������ƫ���У�����ָ�����У�ȭ��ȴ��$n��������ס",
        "force" : 340,
        "dodge" : -3,
        "parry" : 4,
        "lvl" : 59,
        "damage" : 80,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ����Ū���־���ȭ�ж�Ȼ���Σ�������Ū$n��ȴ�ְ�������",
        "force" : 370,
        "dodge" : 1,
        "parry" : 3,
        "lvl" : 65,
        "damage" : 100,
        "skill_name" : "Ū�־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ����ͯ���־�����ȭ����ͯ������·������һ���$n��$l",
        "force" : 400,
        "dodge" : 3,
        "parry" : 4,
        "lvl" : 72,
        "damage" : 100,
        "skill_name" : "ͯ�־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ����ӹ���־�����ȭ����ʱ����򵥵���ʽ��ƽƽ���棬����ȴ��ס��$n����·",
        "force" : 440,
        "dodge" : 3,
        "parry" : -2,
        "lvl" : 78,
        "damage" : 110,
        "skill_name" : "ӹ�־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ���������־������������繭��ȭ���Ƽ���Ѹ�ݵ�Ϯ��$n",
        "force" : 480,
        "dodge" : 5,
        "parry" : 2,
        "lvl" : 85,
        "damage" : 150,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
([      "action" : "$Nʹ�����桹�־�������������棬ȭ��Ҳ�����䶯��$n���޷��ж���һȭ������",
        "force" : 530,
        "dodge" : 8,
        "parry" : -1,
        "lvl" : 95,
        "damage" : 180,
        "skill_name" : "���־�",
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "cuff" ||  usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("������ȭ������֡�\n");

	if ((int)me->query("max_neili") < 1000)
                return notify_fail("�������̫�����޷�������ȭ��\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷�������ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < 120)
                return notify_fail("��Ļ���ȭ����򲻹����޷�������ȭ��\n");

        if ((int)me->query_skill("chunyang-quan", 1) < 120)
                return notify_fail("��Ĵ���ȭ������������ʵ���޷�������ȭ��\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("kongming-quan", 1))
                return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷���������Ŀ���ȭ��\n");

	return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("kongming-quan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
                return notify_fail("������������ˡ�\n");

	me->receive_damage("qi", 50);
	me->add("neili", -60);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 250) return 0;

	if (!me->query_temp("kongming")) return 0;

        if (random(10) > 5)
        {
                victim->receive_wound("qi", (damage_bonus - 250) / 5, me);
                return HIR + me->name() + HIR + "������磬�������տ�ȭ������һ����" + victim->name() + HIR + "һ���ƺߣ��³�һ����Ѫ��\n" NOR;
        }
	return 0;
}


string perform_action_file(string action)
{
      return __DIR__"kongming-quan/" + action;
}

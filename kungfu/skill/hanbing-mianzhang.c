// hannbing-mianzhang.c ��������
// pal 1997.05.26

inherit SKILL;

mapping *action = ({
([      "action": "$N����Ʈ�����ɣ�˫���ڿ���һ��������һ�󺮷磬��$n��$l��ȥ",
        "dodge": 30,
        "force": 280,
	"parry": 15,
	"damage": 50,
        "lvl": 0,
        "skill_name": "��������",
        "damage_type": "����"
]),
([      "action": "$NͻȻ˫�ֻ���Ϊָ����$n��$l����ȥ",
        "dodge": 10,
        "force": 200,
	"parry": 20,
	"damage": 70,
        "lvl": 40,
        "skill_name": "����̹�",
        "damage_type": "����"
]),
([      "action": "$N����һ�䣬����$n�ɱ���ͬʱ˫�Ƽ��İ�$n��������Ӱֻ��",
        "dodge": -20,
        "force": 450,
	"parry": 25,
	"damage": 80,
        "lvl": 60,
        "skill_name": "��ѩ����",
        "damage_type": "����"
]),
([      "action": "$nֻ����ǰһ�����ж��Ի���ȫ���ѱ�������$N������֮��",
        "dodge": 10,
        "force": 350,
	"parry": 30,
	"damage": 100,
        "lvl": 80,
        "skill_name": "˪������",
        "damage_type": "����"
]),
([      "action": "$N������Ц,���������ĳ�������ͷ�������Ϣ��ӡ��$n������",
        "dodge": 20,
        "force": 300,
	"parry": 35,
	"damage": 110,
        "lvl": 100,
        "damage_type": "����"
]),
([      "action": "$N���ⲻ֧,��$n�������󡢾�������֮�ʣ�����Ϯ��",
        "dodge": -20,
        "force": 400,
	"parry": 15,
	"damage": 130,
        "lvl": 120,
        "damage_type": "����"
]),
([      "action": "$N�����棬���Ӻ����������������ˣ�˫�����಻���ز�����$n����,����ֱ治����ʵ",
        "dodge": 30,
        "force": 350,
	"parry": 35,
	"damage": 120,
        "lvl": 140,
        "damage_type": "����"
]),
([      "action": "$N������Σ�������ǰ,���Ʒ���һ�ɺ���Ϯ��$nС��",
        "dodge": 0,
        "force": 400,
	"parry": 15,
	"damage": 130,
        "lvl": 160,
        "damage_type": "����"
]),
});

int valid_enable(string usage)
{
	return usage=="strike" || usage=="parry";
}

int valid_learn(object me)
{
	if (me->query("gender") == "����")
		return notify_fail("���޸����ԣ��޷�ѧϰ����ĺ��������ƣ�\n");

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���������Ʊ�����֡�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���򲻹����޷����������ơ�\n");

	if ((int)me->query("max_neili") < 900)
		return notify_fail("�������̫�����޷����������ơ�\n");

        if ((int)me->query_skill("strike", 1) < 80)
		return notify_fail("��Ļ����Ʒ���򲻹����޷����������ơ�\n");

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
	level   = (int) me->query_skill("hanbing-mianzhang",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("��������������������ơ�\n");

	me->receive_damage("qi", 50);
	me->add("neili", -54);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int lvl;
        int flvl;

	lvl  = me->query_skill("hanbing-mianzhang", 1);
        flvl = me->query("jiali");
	if (lvl < 80 || flvl < 10 || ! damage_bonus)
		return;

    	if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
            victim->affect_by("ice_poison",
                              ([ "level" : flvl + random(flvl),
                                 "id"    : me->query("id"),
                                 "duration" : lvl / 50 + random(lvl / 20) ])))
        {
                return "$n��Ȼ��ɫ��䣬һ����ս�����˼�����\n";
    	}
}

string perform_action_file(string action)
{
	return __DIR__"hanbing-mianzhang/" + action;
}

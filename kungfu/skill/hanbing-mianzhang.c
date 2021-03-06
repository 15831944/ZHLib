// hannbing-mianzhang.c 寒冰绵掌
// pal 1997.05.26

inherit SKILL;

mapping *action = ({
([      "action": "$N往後飘出数丈，双掌在空中一划，带起一阵寒风，向$n的$l拍去",
        "dodge": 30,
        "force": 280,
	"parry": 15,
	"damage": 50,
        "lvl": 0,
        "skill_name": "冰冻三尺",
        "damage_type": "瘀伤"
]),
([      "action": "$N突然双手化掌为指，向$n的$l戳下去",
        "dodge": 10,
        "force": 200,
	"parry": 20,
	"damage": 70,
        "lvl": 40,
        "skill_name": "寒风刺骨",
        "damage_type": "瘀伤"
]),
([      "action": "$N身形一变，绕着$n飞奔，同时双掌疾拍把$n包裹在掌影只中",
        "dodge": -20,
        "force": 450,
	"parry": 25,
	"damage": 80,
        "lvl": 60,
        "skill_name": "冰雪连天",
        "damage_type": "瘀伤"
]),
([      "action": "$n只觉眼前一花，行动稍缓，全身已被笼罩在$N的掌力之下",
        "dodge": 10,
        "force": 350,
	"parry": 30,
	"damage": 100,
        "lvl": 80,
        "skill_name": "霜华满地",
        "damage_type": "瘀伤"
]),
([      "action": "$N纵声长笑,立即手掌拍出，抢在头里，无声无息地印向$n的胸膛",
        "dodge": 20,
        "force": 300,
	"parry": 35,
	"damage": 110,
        "lvl": 100,
        "damage_type": "瘀伤"
]),
([      "action": "$N假意不支,趁$n得意洋洋、绝不防备之际，暴起袭击",
        "dodge": -20,
        "force": 400,
	"parry": 15,
	"damage": 130,
        "lvl": 120,
        "damage_type": "瘀伤"
]),
([      "action": "$N身法诡奇，身子忽东忽西，忽进忽退，双掌连绵不绝地缠绕在$n周身,令其分辨不清虚实",
        "dodge": 30,
        "force": 350,
	"parry": 35,
	"damage": 120,
        "lvl": 140,
        "damage_type": "瘀伤"
]),
([      "action": "$N左掌虚晃，掩在面前,右掌泛起一股寒气袭向$n小腹",
        "dodge": 0,
        "force": 400,
	"parry": 15,
	"damage": 130,
        "lvl": 160,
        "damage_type": "瘀伤"
]),
});

int valid_enable(string usage)
{
	return usage=="strike" || usage=="parry";
}

int valid_learn(object me)
{
	if (me->query("gender") == "无性")
		return notify_fail("你无根无性，无法学习高深的寒冰烈焰掌！\n");

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("练寒冰绵掌必须空手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功火候不够，无法练寒冰绵掌。\n");

	if ((int)me->query("max_neili") < 900)
		return notify_fail("你的内力太弱，无法练寒冰绵掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
		return notify_fail("你的基本掌法火候不够，无法练寒冰绵掌。\n");

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
		return notify_fail("你的体力太低了。\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("你的内力不够练寒冰绵掌。\n");

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
                return "$n忽然神色大变，一个寒战，退了几步。\n";
    	}
}

string perform_action_file(string action)
{
	return __DIR__"hanbing-mianzhang/" + action;
}

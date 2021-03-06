// riyue-bian.c 日月鞭法
// modified by Venus Oct.1997

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N端坐不动，一招「裂石式」，手中$w抖得笔直，对准$n的胸腹要害连刺数鞭",
        "force" : 180,
        "attack": 60,
        "dodge" : 25,
        "parry" : 15,
        "damage": 60,
        "lvl"   : 0,
        "skill_name" : "裂石式",
        "damage_type": "刺伤"
]),
([      "action": "$N身形一转，一招「断川式」，手中$w如矫龙般腾空一卷，猛地向$n劈头打下",
        "force" : 250,
        "attack": 80,
        "dodge" : 30,
        "parry" : 20,
        "damage": 90,
        "lvl"   : 80,
        "skill_name" : "断川式",
        "damage_type": "抽伤"
]),
([      "action": "$N力贯鞭梢，一招「破云式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 260,
        "attack": 95,
        "dodge" : 40,
        "parry" : 25,
        "damage": 120,
        "lvl"   : 100,
        "skill_name" : "破云式",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「分海式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 280,
        "attack": 110,
        "dodge" : 65,
        "parry" : 30,
        "damage": 150,
        "lvl"   : 120,
        "skill_name" : "分海式",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「裂空式」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 310,
        "attack": 130,
        "dodge" : 80,
        "parry" : 45,
        "damage": 180,
        "lvl"   : 140,
        "skill_name" : "裂空式",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「佛光普照」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 350,
        "attack": 155,
        "dodge" : 100,
        "parry" : 50,
        "damage": 200,
        "lvl"   : 160,
        "skill_name":  "佛光普照",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「金刚伏魔」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 380,
        "attack": 160,
        "dodge" : 125,
        "parry" : 75,
        "damage": 220,
        "lvl"   : 180,
        "skill_name" : "金刚伏魔",
        "damage_type": "抽伤"
]),
([      "action":"$N力贯鞭梢，一招「佛法无边」，手中$w舞出满天鞭影，排山倒海般扫向$n全身",
        "force" : 420,
        "attack": 180,
        "dodge" : 140,
        "parry" : 85,
        "damage": 250,
        "lvl"   : 200,
        "skill_name" : "佛法无边",
        "damage_type": "抽伤"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("你必须先找一条鞭子才能练鞭法。\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力不足，没有办法练日月鞭法，多练些内力再来吧。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候太浅，没有办法练日月鞭法。\n");

        if ((int)me->query_skill("whip", 1) < 100)
                return notify_fail("你的基本鞭法火候太浅，没有办法练日月鞭法。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("riyue-bian", 1))
                return notify_fail("你的基本鞭法水平还不够，无法领会更高深的日月鞭法。\n");

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
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query("qi") < 80)
                return notify_fail("你的体力不够练日月鞭法。\n");

        if ((int)me->query("neili") < 90)
                return notify_fail("你的内力不够练日月鞭法。\n");

        me->receive_damage("qi", 75);
        me->add("neili", -85);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"riyue-bian/" + action;
}


// liudaolunhui-sword.c
// 华夏玩家blacksir的自创武功：六道轮回
// Modified by smallfish@huaxia Sep.1998
#include <ansi.h>

inherit SKILL;

string is_private_skill() {return "blacksir";}
int can_not_hubo() {return 1;}

mapping *action = ({
([      "skill_name":    "天界求佛",
        "action":  "$N纵身跃起，手中$w带起万道霞光，向$n的周身点去。好一招「"+HIY"天界求佛"+NOR"」",
        "dodge" : 80,
        "damage": 180,
        "force" : 330,
        "attack": 130,
        "parry" : 80,
        "lvl"   : 0,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "人间苦难",
        "action":  "$N剑意缠绵，迅速无伦地在$n周围游走，将「"+MAG"人间苦难"+NOR"」发挥的淋漓尽致！$n只见周围剑影重重，无法脱困",
        "dodge" : 90,
        "damage": 190,
        "force" : 340,
        "attack": 135,
        "parry" : 85,
        "lvl"   : 120,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "地狱受刑",
        "action":  "$N左手运起排山倒海的掌力，右手$w舞出夺目的寒光，笼罩住$n的全身。\n$n已心胆俱裂，眼见这招「"+HIM"地狱受刑"+NOR"」，却毫无招架之力",
        "dodge" : 95,
        "damage": 200,
        "force" : 350,
        "attack": 140,
        "parry" : 90,
        "lvl"   : 140,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "修罗无敌",
        "action":  "$N冲天而起，连人带剑向$n合身扑去，但见长空中青光一闪，这招「"+HIR"修罗无敌"+NOR"」已穿身而过",
        "dodge" : 105,
        "damage": 210,
        "force" : 360,
        "attack": 145,
        "parry" : 95,
        "lvl"   : 160,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "恶鬼乞食",
        "action":  "$N见状身形向前一飘，手中$w突然暴长数尺，发出青绿之光，一圈套一圈，招招不力$n的咽喉。\n待$n悟到这招名曰「"+HIB"饿鬼乞食"+NOR"」，却也为时已晚",
        "dodge" : 110,
        "damage": 220,
        "force" : 370,
        "attack": 150,
        "parry" : 100,
        "lvl"   : 180,
        "damage_type":  "刺伤"
]),
([      "skill_name":    "不堕轮回",
        "action":  "$N手腕一抖大喝一声，手中$w宛若矫龙飞在半空，一招「"+HIC"不堕轮回"+NOR"」乘势往$n的$l攻去",
        "dodge" : 115,
        "damage": 230,
        "force" : 380,
        "attack": 155,
        "parry" : 105,
        "lvl"   : 200,
        "damage_type":  "刺伤"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 1000 )
        return notify_fail("你的内力不够，没有办法练天道轮回剑法。\n");

    if( (int)me->query_skill("martial-cognize",1) < 300 )
        return notify_fail("你的武学修养不够，没有办法练六道轮回剑法。\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
        return notify_fail("你必须先找一把剑才能练剑法。\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
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
    level   = (int) me->query_skill("liudaolunhui-sword",1);
    for(i = sizeof(action); i > 0; i--)
        if(level > action[i-1]["lvl"])
            return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
        return notify_fail("你的体力不足以练习六道轮回剑法。\n");

    if ((int)me->query("neili") < 60 )
        return notify_fail("你的内力不够，没有办法练习六道轮回剑法。\n");

    me->receive_damage("qi", 50);
    me->add("neili", -50);

    return 1;
}

string perform_action_file(string action)
{
        return __DIR__"liudaolunhui-sword/" + action;
}

// meinv-quan.c 美女拳
// By Lgg,1998.9
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "只见$N使出"+HIM"「貂蝉拜月」"+NOR"，向着天空深深一拜，趁$n不备挥出一拳",
        "force" : 30,
        "dodge" : 30,
        "lvl" : 0,
        "damage": 5,
        "skill_name" : "貂蝉拜月",
        "damage_type" : "内伤"
]),

([      "action" : "$N一招"+HIM"「西子捧心」"+NOR"，双手从胸口处向$n递出",
        "force" : 30,
        "dodge" : 25,
        "lvl" : 20,
        "damage": 20,
        "skill_name" : "西子捧心",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使一招"+HIM"「红玉击鼓」"+NOR"，双臂交互快击，扫向$n",
        "force" : 50,
        "dodge" : 20,
        "lvl" : 40,
        "damage": 30,
        "skill_name" : "红玉击鼓",
        "damage_type" : "跌伤"
]),
([      "action" : "$N使一招"+HIM"「绿珠坠楼」"+NOR"，扑地攻向$n下盘",
        "force" : 70,
        "dodge" : 15,
        "lvl" : 60,
        "damage": 35,
        "skill_name" : "绿珠坠楼",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N双掌连拍数下，使出"+HIM"「文姬归汉」"+NOR"，接着连绵不断的拍出",
        "force" : 100,
        "dodge" : 10,
        "lvl" : 80,
        "damage": 45,
        "skill_name" : "文姬归汉",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N左手在$n面前展开，好像打开扇子一般，右手向$n连出数拳，这正是一招"+HIM"「班姬题扇」"+NOR,
        "force" : 130,
        "dodge" : 30,
        "lvl" : 100,
        "damage": 50,
        "skill_name" : "班姬题扇",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N伸指戳出，却是一招"+HIM"「萍姬针神」"+NOR"，插向$n面门",
        "force" : 160,
        "dodge" : 25,
        "lvl" : 130,
        "damage": 55,
        "skill_name" : "萍姬针神",
        "damage_type" : "瘀伤"
]),
([      "action" : "$N使一招"+HIM"「燕姬梦兰」"+NOR"，如梦如醒，身子向$n倒去，双手直连数拳",
        "force" : 190,
        "dodge" : 20,
        "lvl" : 160,
        "damage": 60,
        "skill_name" : "燕姬梦兰",
        "damage_type" : "抓伤"
]),
([      "action" : "$N一招"+HIM"「蛮腰纤纤」"+NOR"，腰肢轻摆避开$n的攻击，右掌向$n打去",
        "force" : 220,
        "dodge" : 15,
        "lvl" : 190,
        "damage": 60,
        "skill_name" : "蛮腰纤纤",
        "damage_type" : "瘀伤"
]),
([      "action" : "只见$N飞身贴到$n身旁，左手一招"+HIM"「紫玉成烟」"+NOR"自下而上向$n直击",
        "force" : 240,
        "dodge" : 15,
        "lvl" : 200,
        "damage": 70,
        "skill_name" : "紫玉成烟",
        "damage_type" : "跌伤"
]),
([      "action" : "$N脚下翩若惊鸦、矫若游龙，犹如在水上漂行一般逼近$n，并向$n连出数拳，却是一招"+HIM"「洛神凌波」"+NOR,
        "force" : 280,
        "dodge" : 30,
        "lvl" : 210,
        "damage": 80,
        "skill_name" : "洛神凌波",
        "damage_type" : "抓伤"
]),
([      "action" : "$N使一招"+HIM"「古墓幽居」"+NOR"，右手支颐，左手轻轻挥出，长叹一声，脸现寂寥之意",
        "force" : 320,
        "dodge" : 25,
        "lvl" : 220,
        "damage": 85,
        "skill_name" : "古墓幽居",
        "damage_type" : "内伤"
])
});

int valid_enable(string usage) { return usage == "cuff" || usage=="parry"; }

int vliad_combine(string combo) { return combo == "fireice-strike"; }

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("练美女拳必须空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的内功火候不够，无法学美女拳。\n");

        if ((int)me->query("max_neili") < 450)
                return notify_fail("你的内力太弱，无法学习美女拳。\n");

	if (me->query_skill("cuff", 1) < me->query_skill("meinv-quan", 1))
		return notify_fail("你的基本拳脚水平有限，无法领会更高深的美女拳法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("meinv-quan", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if ((int)me->query("qi") < 50)
                return notify_fail("你的体力太差了，不能练习美女拳。\n");

        if ((int)me->query("neili") < 60)
                return notify_fail("你的内力不够，不能练习美女拳。\n");

        me->receive_damage("qi", 35);
        me->add("neili", -41);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"meinv-quan/" + action;
}

// qiankun-danuoyi.c 乾坤大挪移
// by King 97.05

inherit SKILL;

#include <ansi.h>

string *parry_msg = ({
        "$N一招击在$n身上，却被$n暗运乾坤大挪移，将内力尽数移入地下。\n",
        "$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
        "$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
        "$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
        "$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
        "$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
        "$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
        "$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

string *dodge_msg = ({
        "$N一招击在$n身上，却被$n暗运乾坤大挪移，将内力尽数移入地下。\n",
        "$n轻轻一带，$N发现自己招数回击过来，吓得往后倒退几步。\n",
        "$n手臂回转，在$N手肘下轻轻一推，$N招数落空。\n",
        "$n右手伸出，在$N手腕上轻轻一拉，$N收势不住，直往前扑去。\n",
        "$n身形不动，$N一招击下，有如石沉大海，不觉呆住了。\n",
        "$n左牵右引，$N如身处漩流，连续转了好几个圈。\n",
        "$n双手回圈，$N只觉得前面好象有一堵墙，再也攻不进去。\n",
        "$n轻轻一转，$N一招击在地上，只打得尘土飞扬。\n",
});

int can_not_hubo() {return 1;}
int valid_enable(string usage)
{
        return usage == "parry";
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int layer;

        if (me->query("gender") == "无性" &&
            me->query_skill("qiankun-danuoyi", 1) >= 50)
                return notify_fail("你试图按照心法修炼大挪移，却"
                                   "觉得心中一阵迷茫，难以继续。\n");

        if (me->query_skill("shenghuo-xuanming",1) < 0)
                {
                me->delete_skill("qiankun-danuoyi");
                return notify_fail("乾坤大挪移必须有圣火玄冥内功配合才能修炼。\n");
                }

        if (me->query_condition("qiankun-except"))
                return notify_fail("你现在体内若冰、四肢皆寒、面赤"
                                   "如火，无法继续修炼神功。\n");

        layer = (int)me->query_skill("qiankun-danuoyi", 1) / 50;
        if (layer > 7) layer = 7;

        if (me->query("int") < 22 + layer)
                return notify_fail("你觉得第" + chinese_number(layer) +
                                   "层乾坤大挪移实在是深奥无比，全然无法理解。\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("你的内力太差，无法修炼乾坤大挪移。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，无法勉强修炼乾坤大挪移。\n");

        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的基本招架火候有限，无法体会更高深的乾坤大挪移。\n");

        if ((int)me->query_skill("shenghuo-xuanming", 1) < 500 &&
            (int)me->query_skill("shenghuo-xuanming",1) <= (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的圣火玄冥火候有限，无法体会更高深的乾坤大挪移。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("qiankun-danuoyi", 1))
                return notify_fail("你的基本内功火候有限，无法体会更高深的乾坤大挪移。\n");

        return 1;
}

mixed valid_damage(object target, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp;

        if ((int) me->query_skill("qiankun-danuoyi", 1) < 100)
        return;

        if (!living(me) || (me->is_busy() && random(3) == 0)) return;
        dp = target->query_skill("force");
        ap = me->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -30);
                msg = parry_msg[random(sizeof(parry_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;
                result = ([ "damage": -damage,
                            "msg"   : msg ]);
                return result;
        }
}

int practice_skill(object me)
{
        return notify_fail("乾坤大挪移只能通过学习或研读乾坤大挪移心法提高。\n");
}

string perform_action_file(string func)
{
        return __DIR__"qiankun-danuoyi/" + func;
}

void skill_improved(object me)
{
        int lvl;
        int layer;

        lvl = me->query_skill("qiankun-danuoyi", 1);
        layer = lvl / 50;
        if (layer > 7) layer = 7;

        if (! layer)
        {
                tell_object(me, HIM "你潜心修炼乾坤大挪"
                            "移心法，若有所悟。\n" NOR);
        } else
        if ((lvl % 50) == 0)
        {
                tell_object(me, HIM "你修炼成了第" + chinese_number(layer) +
                            "层的乾坤大挪移心法。\n" NOR);
        } else
                tell_object(me, HIM "你对第" + chinese_number(layer) +
                            "层的乾坤大挪移心法又加深了一层了解。\n" NOR);

        if (lvl < 500 && lvl > me->query_skill("force") * 2 / 3)
        {
                if (lvl < me->query_skill("force") * 2 / 3 + 10)
                {
                        tell_object(me, HIG "你觉得内息一阵紊乱，丹田时冷时热，不由得大吃一惊。\n"
                              "心想莫非是走火入魔？忽然你觉得丹田越来越是寒冷，极为难受。\n" NOR);
                        message("vision", HIG + me->name() + HIG "的脸色忽红忽"
                                "绿，变得不停，只是浑身颤抖，似乎十分痛苦。\n" NOR,
                                environment(me), ({ me }));
                        return;
                }

                tell_object(me, HIB "你忽然觉得丹田腾起一阵寒意，霎时间四肢"
                      "百赅一起变得寒冷无比，忍不住大声呻吟。\n" NOR);
                message("vision", HIB + me->name() + HIB "忽然一"
                        "抖，脸色忽然变得惨白，隐然笼罩了一股绿气，呻吟不止。\n" NOR,
                        environment(me), ({ me }));
        } else
        if (lvl < 350 && (lvl * 20 + 4000) > me->query("max_neili"))
        {
                if ((lvl * 20 + 4000) < me->query("max_neili") + 200)
                {
                        tell_object(me, HIR "你试着运转了一下内息，一时觉得内"
                              "力不济，看来还是不要贸然修炼大挪移神功。\n" NOR);
                        return;
                }

                tell_object(me, HIR "你试着运转了一下内息，忽然觉得一口气"
                      "竟然转不过来，顿时心中绞痛，接连吐了几口鲜血。\n" NOR);
                message("vision", HIR + me->name() + HIR "脸色忽然"
                        "一变，呕出几口鲜血，触目惊心。\n" NOR,
                        environment(me), ({ me }));
        } else
                return;

        me->apply_condition("qiankun-except", lvl + (int)me->query_condition("qiankun-except"));
}


 // douzhuan-xingyi 斗转星移

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *parry_msg = ({
        "只听见「锵」一声，$n用$p轻轻一托，化解了$N这一击。\n",
        "但是被$n用手中兵刃卸开。\n",
        "但是$n身子一侧，随手转动手中的$p，让$N感觉到有力难施。\n",
});

string *unarmed_parry_msg = ({
        "但是被$p双掌一推，$N的攻势顿时变了方向。\n",
        "$n身形一转，$N只觉得的所有的力道全部都落到了空处。\n",
        "但是$N感觉像打到棉花上一样，说不出的怪异。\n",
});

string query_parry_msg(object weapon)
{
        if( weapon )
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("zihui-xinfa", 1) < 100)
                return notify_fail("你的紫徽心法火候还不够，不能学习斗转星移。\n");

        if ((int)me->query_skill("parry", 1) < 100)
                return notify_fail("你的基本招架技巧掌握的还不够熟练，无法学习斗转星移。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("斗转星移只能用学(learn)的来增加熟练度。\n");
}

mixed valid_damage(object target, object me, int damage, object weapon)
{


        string msg;
        mapping result;
        int ap, dp;

        if ((int) me->query_skill("douzhuan-xingyi", 1) < 100)
        return;

       dp = target->query_skill("force", 1);
       ap = me->query_skill("parry", 1) + me->query_skill("zihui-xinfa", 1) / 4;



        if (ap + random(ap) > dp)
        if ((int) me->query_skill("zihui-xinfa", 1) < 280)
        {
                result = ([ "damage" : -damage ]);

                switch(random(2))
                {
                case 0:
                        result += ([ "msg" : HIC "$N" HIC  "忽然,\n" NOR ]);

                     damage = 200;   
                me->add("neili", -30);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage,2,
                       HIR "\n$N" HIR "推气引劲，试图把"
                       HIR "$n" HIR "的攻击转向"
                       HIR "$n" HIR "自己身上!\n\n"
                       HIY "$N" HIY "大吃一惊，冷不防"
                       HIY "大喝一声，奋力抵挡!!\n" NOR);
                 message_combatd(msg, me, target);

                        break;


                default:
                        result += ([ "msg" : HIC "$N" HIC "一招眼看击中了$n"
                                             HIC "，然而$n" HIC "轻轻一卸，"
                                             "将$N" HIC "的攻击化解于无形。\n" NOR ]);
                        break;
                }
                       return result;
           }

      else
           {

                result = ([ "damage" : -damage ]);

                switch(random(5))
                {
                case 0:
                        result += ([ "msg" : HIY "$N" HIY "只觉得全身受到内力震荡，脸色变的苍白。\n" NOR ]);



                        message_vision(HIR "\n\n谈笑间，" HIR "$N" HIR "竟使出" HIR "$n" HIR "成名技艺,"
                                       HIR "把" HIR "$n" HIR "的攻击转向"
                           HIR "$n" HIR "自己身上!\n\n"NOR,me,target);
                        target->receive_damage("qi", damage / 5);
                        me->add("neili", -30);

                        break;
                case 1:
                        result += ([ "msg" : HIY "$N" HIY "怎么也想不到" HIY "$n" HIY "能够使出自己的成名绝技，"
                                             HIY "只觉得全身受到内力震荡，钻心般巨痛，一口鲜血喷出!!\n"NOR ]);


                        message_vision(HIR "\n\n忽然天昏地暗，" HIR "$N" HIR "使出" HIR "$n" HIR "的绝招，"
                                       HIR "袍袖中两股内家真气向" HIR "$n" HIR "扑去！\n\n"NOR,me,target);

                        target->receive_damage("qi", damage / 2);
                         me->add("neili", -100);

                        break;

                case 2:
                        result += ([ "msg" : MAG "蓦地里一股力道飞来，将" MAG "$n" MAG "一引一带，"
                                             MAG "$n" MAG "身子轻轻越起，身行落在一旁。\n" NOR ]);
                        break;


                case 3:
                        result += ([ "msg" : MAG "当下一股内力冲向" MAG "$N" MAG "，" MAG "$N" MAG "击向"
                                             MAG "$n" MAG "的招数"
                                             MAG "莫名奇妙的溜滑向一旁 。\n" NOR ]);
                        break;


                default:
                        result += ([ "msg" : MAG "只听见「锵」一声，" MAG "$n" MAG "用手轻轻一托，"
                                             MAG "化解了" MAG "$N" MAG "这一击。\n" NOR ]);
                        break;
                }
                return result;
        }


}

string perform_action_file(string action)
{
        return __DIR__"douzhuan-xingyi/" + action;
}

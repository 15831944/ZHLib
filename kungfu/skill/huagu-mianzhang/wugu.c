// wugu.c 无骨
// smallbear 11/3/2002

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg,force;
        int ap, dp;
        int count;
        int i,j;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「无骨」只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("「无骨」只能空手使用。\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 120)
                return notify_fail("你的化骨棉掌火候不够，无法使用「无骨」绝招！\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的内功修为不够，无法使用「无骨」绝招！\n");

        if (! me->query_skill_prepare() &&
            me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("你现在没有准备使用化骨棉掌，无法使用「无骨」绝招！\n");
    if(!stringp(force = me->query_skill_mapped("force"))
                ||force!="busi-shenlong")
                return notify_fail("你没有使用神龙不死心法，无法使出绝招！\n");

        msg = HIW "只听得$N关节喀喀作响，掌心隐约透出股黑气，双臂变得柔软无骨一般！\n"NOR;
        ap = me->query_skill("strike") + me->query("str") * 10;
        if (living(target))
                 dp = target->query_skill("parry") + target->query("dex") * 10;
        else     dp = 0;
        if (ap / 2 + random(ap) > dp)
        {
                count = ap / 20;
                msg += HIW "$n见$P招式怪异，不知该怎么招架，慌乱中$N的双掌已到面前。\n"NOR;
        } 
        
        else
        {
                msg += HIW "$n抖擞精神，刹那间已看清$N的招式，从容招架。\n" NOR; 
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -200);
        j = random(6);
        if (j < 3) j = 3;
   for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }

        me->start_busy(1);
        me->add_temp("apply/attack", -count);

        return 1;
}



// tianwang.c  无形天网

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("「无形天网」只能对战斗中的对手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

        if (!living(target))
                return notify_fail("对方已经不能战斗了！\n");

        skill = me->query_skill("tianluo-diwang", 1);

        if (skill < 80)
                return notify_fail("你的天罗地网势修为有限, 不能使用「无形天网」！\n");

        if (me->query("neili") < 70)
                return notify_fail("你的真气不够，无法运用「无形天网」！\n");

        if (me->query_skill_mapped("hand") != "tianluo-diwang")
                return notify_fail("你没有激发天罗地网势, 不能使用「无形天网」！\n");

        msg = HIY "$N" HIY "双手带动劲气，幻化无数掌风，飘拂不定，宛若天网，似攻非攻."
              HIC "。\n" NOR;

        me->add("neili", -30);
        ap = me->query_skill("hand");
        dp = target->query_skill("dodge");
        if (ap / 2 + random(ap) > dp)
        {
        me->start_busy(1);
                msg += HIR "$p"
                       HIR "的眼睛一阵昏玄，竟忘了进攻！\n" NOR;
                target->start_busy(ap / 20 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "眼光一闪，看破了$P"
                       CYN "的企图，若无其事。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

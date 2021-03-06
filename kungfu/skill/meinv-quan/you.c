// you.c 美女拳-古墓幽居

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("古墓幽居只能对战斗中的对手使用。\n");
	
	if (me->query_temp("weapon"))
		return notify_fail("你只有空手才能够使出美女拳法。\n");
 
        if ((int)me->query_skill("meinv-quan", 1) < 80)
                return notify_fail("你的美女拳级别不够，不会使用古墓幽居。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的内功还未娴熟，不能利用神功伤敌。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你现在真气不够，不能使用古墓幽居。\n");

        if (me->query_skill_mapped("cuff") != "meinv-quan")
                return notify_fail("你没有激发美女拳法，不能施展古墓幽居。\n");

        msg = HIW "$N" HIW "右手支颐，左袖轻轻挥出，长叹一声，使"
              "出「古墓幽居」，一脸尽现寂寥之意。\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
                me->start_busy(random(3));

                damage = (int)me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);
		damage += (int)me->query("jiali")*2;

                me->add("neili", -100-me->query("jiali")/2);

                if (damage < 30)
                        pmsg = HIY "结果$n" HIY "被$N袍"
                               HIY "袖一拂，闷哼一声。\n" NOR;
                else if(damage < 55)
                        pmsg = HIY "结果$n" HIY "被$N"
                               HIY "以袍袖一拂，「腾腾」地退出几步。\n" NOR;
                else if (damage < 80)
                        pmsg = HIR "结果$n" HIR "被$N"
                               HIR "以袍袖一拂，胸口有如受到一记重"
                               "锤，气血为之一窒！\n" NOR;
                else
                        pmsg = RED "结果$n" RED "被$N" RED
                               "的袍袖一拂，眼前一黑，浑身气血翻腾，"
                               "竟如身入洪炉一般！\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 25, pmsg);
        } else
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企图，稳如泰山，抬手一架格开了$P"
                       CYN "这一拳。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

// wuji.c 横行无忌

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「横行无忌」只能对战斗中的对手使用。\n");
 
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("运用「横行无忌」必须手中持杖！\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("你的内功火候不够，难以运用使用「横行无忌」！\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("你现在的真气不够，无法使用「横行无忌」！\n");

        if ((int)me->query_skill("lingshe-zhangfa", 1) < 150)
                return notify_fail("你的灵蛇杖法还不到家，无法使用「横行无忌」！\n");

        if (me->query_skill_mapped("staff") != "lingshe-zhangfa") 
                return notify_fail("你没有激发灵蛇杖法，无法使用「横行无忌」！\n");

        msg = HIB"$N纵声长笑，手中的" + weapon->name() + "忽然变得另人难以琢磨，招式变换无常，光芒四处挥射，不知攻向$n何处！\n" NOR;
        ap = me->query_skill("staff");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = ap + random(ap);
                me->add("neili", -200);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIW "$n" HIW "被$P"
                                           HIW "无数毫无规律的招式弄的眼花缭乱，精疲力尽，一招命中要害，脸色苍白！\n" NOR);
                me->start_busy(3);
                target->start_busy(1);
        } else 
        {
                msg += CYN "$n" CYN "四处闪躲，总算是躲过了$P"
                       CYN "伶俐的进攻！\n" NOR;
                me->add("neili", -80);
                me->start_busy(4);
                target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}


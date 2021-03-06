// jue 绝命一踢
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
	string msg;
	int ap, dp, pp;
        int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("「绝命一踢」只能对战斗中的对手使用。\n");
 
	if (objectp(me->query_temp("weapon")))
		return notify_fail("你必须空手才能使用这一绝技。\n");

	if (me->query_skill("jueming-tui", 1) < 100)
		return notify_fail("你的「绝命腿」还不够娴熟，不能使用「绝命一踢」！\n");

	if (me->query_str() < 35)
		return notify_fail("你的膂力不够，小心踢断了腿！\n");

        if (me->query("neili") < 200)
                return notify_fail("你的内力不够，不能使用「绝命一踢」！\n");

        if (me->query_skill_mapped("unarmed") != "jueming-tui")
                return notify_fail("你没有激发绝命腿法，不能使用「绝命一踢」！\n");
 
	msg = HIC "$N" HIC "一声冷哼，右腿横扫$n" HIC "，势不可当！\n" NOR;
 
	ap = me->query_skill("unarmed") + me->query("str") * 10;
	dp = target->query_skill("dodge") + target->query("dex") * 10;
	pp = target->query_skill("parry") + target->query("str") * 10;
        
        me->start_busy(2);
        me->add("neili", -50);
        if (ap / 2 + random(ap) < pp || !living(target))
        {
                msg += HIG "$n" HIG "身子一晃，硬是架住了$N" HIG "这一击。\n" NOR;
        } else
        if (ap / 2 + random(ap) < dp || !living(target))
        {
		msg += HIG "只见$n" HIG "不慌不忙，轻轻一闪，躲过了$N" HIG "这一击！\n"NOR;
        } else
	{
		me->add("neili",-70);
                damage = ap / 4 + random(ap / 4) + me->query("jiali");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "连忙格挡，只觉得力道大得出奇，哪里抵"
                                           "挡得住！直被$N" HIR "踢得飞起数尺之高！\n" NOR);
		target->start_busy(1 + random(2));
	}

	message_combatd(msg, me, target);
	return 1;
}


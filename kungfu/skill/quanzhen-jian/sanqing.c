// hua.c 全真剑 一气化三清

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int count,is_yunv=0;

        if (userp(me) && ! me->query("can_perform/quanzhen-jian/hua"))
                return notify_fail("你还不会使用一气化三清。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("一气化三清只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if ((int)me->query_skill("quanzhen-jian", 1) < 120)
                return notify_fail("你的全真剑法不够娴熟，不能使用一气化三清。\n");

	if( me->query_skill_mapped("force") != "xiantian-gong" )
		return notify_fail("你所用的并非先天功，无法施展一剑化三清！\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 100)
                return notify_fail("你的先天功不够娴熟，无法领会一气化三清的奥秘。\n");

        if ((int)me->query("neili", 1) < 500)
                return notify_fail("你现在真气不够，不能使用一气化三清。\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("你没有激发全真剑法，不能使用一气化三清。\n");

        msg = HIC "$N" HIC "站稳马步，将内力全然运到剑上，一声长喝，" +
              weapon->name() + HIC "上" HIM "紫芒" HIC "闪耀。\n\n" NOR;

	if( me->query_skill("sword") < 200 )
		msg += HIC"$N猛然挺身前冲，"+weapon->query("name")+"平指向前，紫芒变成"+HIW+"雪亮白练"+HIC+"，一剑化为二道剑影，剑剑快似闪电！\n\n" NOR;
	else if( me->query_skill("sword") < 300 )
		msg += HIC"$N猛然挺身前冲，"+weapon->query("name")+"平指向前，紫芒变成"+HIW+"雪亮白练"+HIC+"，一剑化为三道剑影，剑剑快似闪电！\n\n" NOR;
	else if( me->query_skill("sword") < 400 )
		msg += HIC"$N猛然挺身前冲，"+weapon->query("name")+"平指向前，紫芒变成"+HIW+"雪亮白练"+HIC+"，一剑化为五、六道剑影，剑剑快似闪电！\n\n" NOR;
	else if( me->query_skill("sword") < 500 )
		msg += HIC"$N猛然挺身前冲，"+weapon->query("name")+"平指向前，紫芒变成"+HIW+"雪亮白练"+HIC+"，一剑化为八、九道剑影，剑剑快似闪电！\n\n" NOR;
	else
		msg += HIC"$N猛然挺身前冲，"+weapon->query("name")+"平指向前，紫芒变成"+HIW+"雪亮白练"+HIC+"，一剑化为无数道剑影，剑剑快似闪电！\n\n" NOR;

        ap = me->query_skill("xiantian-gong", 1) + me->query_skill("sword");
        dp = target->query_skill("force");

	//对方如果使用的是古墓的玉女剑，则增强防御
	//Add by Smallfish
	if (stringp(target->query_skill_mapped("sword")) &&
	    target->query_skill_mapped("sword") == "yunv-jian" &&
            target->query_temp("weapon") &&
            target->query_temp("weapon")->query("skill_type") == "sword")
	{
		dp += target->query_skill("yunv-jian",1);
		is_yunv = 1;
	}

        if (dp < 1) dp = 1;
        if (ap / 3 + random(ap) > dp || !living(target))
        {
                if( !target || !target->is_character() 
                  || !me->is_fighting(target) 
                    || !living (target) ) 
                {
                return -1;
                }
                target->start_busy(1 + random(2));
                me->add("neili", -200);
                if (ap / 4 + random(ap) > dp || !living(target))
                {
                        count = me->query_skill("xiantian-gong", 1) / 4;
                        me->add_temp("apply/attack", count);
                        message_combatd(msg + HIC "$N" HIC "看到$n" HIC
                                        "在这一击之下破绽迭出，身"
                                        "形前跃，“唰唰唰”就是三剑！\n" NOR,
                                        me, target);
                        COMBAT_D->do_attack(me, target, weapon);
                        COMBAT_D->do_attack(me, target, weapon);
                        COMBAT_D->do_attack(me, target, weapon);
                        me->add_temp("apply/attack", -count);
                }
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, ap / 2, 66,
                                           HIR "$n" HIR "一声惨叫，剑气及身，身上"
                                           "顿时冒出数道血柱！\n" NOR);
                me->start_busy(3);
        } else
        {
                me->start_busy(2);
		if (is_yunv)
			msg += CYN "却见$n" CYN "微微一笑，反手一招“玉女剑法”，轻松地档住了$N的剑招。\n" NOR;
		else
	                msg += CYN "可是$n" CYN "看破了$N" CYN "的企图，斜跃避开。\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}


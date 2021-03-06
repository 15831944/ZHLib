// Code of JHSH
///kungfu/skill/duanyun-bian/fengyun.c 风云变色
// sdong 09/98

#include <ansi.h>

inherit F_DBASE;
inherit F_SSERVER;

int perform(object me, object target)
{
	int str, dex, skill,power;
	string weapon;

	if( !target ) target = offensive_target(me);

	if( !target
	||	!target->is_character()
	||	!me->is_fighting(target) )
		return notify_fail("风云变色只能对战斗中的对手使用。\n");


	if( me->query_skill_mapped("force") != "xiantian-gong" )
		 return notify_fail("你所用的并非玄门先天功，施展不出风云变色！\n");

	if( me->query_skill("force") < 140 )
		return notify_fail("你的玄门先天功火候未到，无法施展风云变色！\n");

	if( me->query_skill("whip") < 135 )
		return notify_fail("风云变色需要精湛的断云鞭法方能有效施展！\n");

        if (!me->query_temp("weapon") || me->query_temp("weapon")->query("skill_type") != "whip")
                return notify_fail("你并没有装备鞭作为武器。\n");
	str = me->query_str();
	power = random( me->query("neili") / 50 ) + me->query("force")/2;
	if(power<150) power=150;
	if(power>480) power=480;

	if( me->query("neili") <= 200 + power*2 )
		return notify_fail("你的内力不够使用风云变色！\n");

	message_vision(HIW "$N运足内力，猛地一扬"NOR+"$n"+HIW"卷起无边风云遮月掩日，一股"NOR+HIM"罡风"NOR+HIW"随著漫天鞭影扑天盖地的向敌人袭来。\n\n" NOR, me, me->query_temp("weapon"));

	me->add_temp("apply/attack",power/2);
	me->add_temp("apply/damage",power/5);
	target->add_temp("apply/armor",-power/2);
	target->add_temp("apply/dodge",-power);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->add_temp("apply/attack",-power/2);
	me->add_temp("apply/damage",-power/5);
	target->add_temp("apply/armor",power/2);
	target->add_temp("apply/dodge",power);

	me->add("neili", -power*2);
	me->add("jingli", -power/2);
	me->start_busy( 2+random(2));

	return 1;
}



// jue ����һ��
 
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
		return notify_fail("������һ�ߡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ����һ������\n");

	if (me->query_skill("jueming-tui", 1) < 100)
		return notify_fail("��ġ������ȡ���������죬����ʹ�á�����һ�ߡ���\n");

	if (me->query_str() < 35)
		return notify_fail("�������������С���߶����ȣ�\n");

        if (me->query("neili") < 200)
                return notify_fail("�����������������ʹ�á�����һ�ߡ���\n");

        if (me->query_skill_mapped("unarmed") != "jueming-tui")
                return notify_fail("��û�м��������ȷ�������ʹ�á�����һ�ߡ���\n");
 
	msg = HIC "$N" HIC "һ����ߣ����Ⱥ�ɨ$n" HIC "���Ʋ��ɵ���\n" NOR;
 
	ap = me->query_skill("unarmed") + me->query("str") * 10;
	dp = target->query_skill("dodge") + target->query("dex") * 10;
	pp = target->query_skill("parry") + target->query("str") * 10;
        
        me->start_busy(2);
        me->add("neili", -50);
        if (ap / 2 + random(ap) < pp || !living(target))
        {
                msg += HIG "$n" HIG "����һ�Σ�Ӳ�Ǽ�ס��$N" HIG "��һ����\n" NOR;
        } else
        if (ap / 2 + random(ap) < dp || !living(target))
        {
		msg += HIG "ֻ��$n" HIG "���Ų�æ������һ���������$N" HIG "��һ����\n"NOR;
        } else
	{
		me->add("neili",-70);
                damage = ap / 4 + random(ap / 4) + me->query("jiali");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "$n" HIR "��æ�񵲣�ֻ����������ó��棬�����"
                                           "����ס��ֱ��$N" HIR "�ߵ÷�������֮�ߣ�\n" NOR);
		target->start_busy(1 + random(2));
	}

	message_combatd(msg, me, target);
	return 1;
}


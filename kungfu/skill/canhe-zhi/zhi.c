// zhi.c ���ָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail("�����ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("�㲻�������������ʹ�òκ�ָ�أ�\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 150)
                return notify_fail("��Ĳκ�ָ��Ϊ����, ����ʹ�á����ָ����\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("��û�м����κ�ָ, ����ʹ�á����ָ����\n");

	if( me->query_skill_prepared("finger") != "canhe-zhi" )
		return notify_fail("�������Ĳ��ǲκ�ָ������ʩչ���ָ����\n");

        if (me->query("neili") < 300)
                return notify_fail("��������������޷����á����ָ����\n");

        msg = HIY "$N" HIY "��ָ��Ȼ������������Ƿ����ؼ����ָ������"
              "ʽ���죬����$n" HIY "����ǰ��Ѩ��\n" NOR;

        ap = me->query_skill("finger");
        if(living(target))
              dp = target->query_skill("parry");
        else  dp = 0;
        if (ap / 2 + random(ap) > dp)
        {
                me->add("neili", -300);
                me->start_busy(2);
                damage = skill + random(skill) + me->query("jiali");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "�мܲ�ס�������ꡱһ�±�$P"
                                           HIR "��һָ��������ǰ����Ѫֱ����\n" NOR);
		target->start_busy(1 + random(2));
        } else
        {
                me->add("neili",-50);
                msg += CYN "����$n" CYN "������$N" CYN "����ʽ��"
                       "����ĵ�ס��$N" CYN "�Ĺ�����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

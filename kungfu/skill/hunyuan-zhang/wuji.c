// wuji.c ��Ԫ�޼�
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
	string msg;
	object weapon;
	int skill, ap, dp, damage;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! me->is_fighting(target))
		return notify_fail("����Ԫ�޼���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (me->query_temp("weapon"))
                return notify_fail("�㲻����������ô�û�Ԫ�ƣ�\n");
	skill = me->query_skill("hunyuan-zhang", 1);
	if (skill < 60)
		return notify_fail("��ġ���Ԫ�ơ��ȼ�����, ����ʹ�á���Ԫ�޼�����\n");

	if (me->query("neili") < 150)
		return notify_fail("��������������޷����á���Ԫ�޼�����\n");
 
	msg = HIC "$N" HIC "Ǳ�ˡ���Ԫ�޼�����˫ȭЮ�������ķ���֮����$n"
              HIC "��ȥ��\n" NOR;
 
	ap = me->query_skill("strike");
        if (living(target))
                dp = target->query_skill("force");
        else    dp = 0;

	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili",-100);
          	target->add("neili",-400);
		damage = 100 + random(skill);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                           HIR "$n" HIR "ֻ������ǰһ���ʹ�����ۡ���һ"
                                           "�����һ����Ѫ��\n" NOR);
		me->start_busy(1 + random(2));
        target->start_busy(1);
	} else
	{
		me->add("neili",-30);
		msg += CYN "ֻ��$n" CYN "���Ų�æ������һ�������"
                       "��$N" CYN "�ı�ɱһ����\n" NOR;
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

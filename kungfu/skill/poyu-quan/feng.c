// feng.c ����ȭ������֡�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ȭ������֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("ֻ�п��ֲ���ʹ������ȭ��\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((int)me->query_skill("poyu-quan", 1) < 80)
		return notify_fail("�������ȭ��������죬����ʹ�á�����֡���\n");

        if (me->query_skill_mapped("cuff") != "poyu-quan")
                return notify_fail("��û�м�������ȭΪȭ�����޷�ʹ�á�����֡���\n");

        if (me->query("neili") < 80)
                return notify_fail("�����������������޷�ʹ�á�����֡���\n");

        msg = HIC "ֻ��$N" HIC "������̽����ȭ쬵�һ�����Ʒ���"
              "�ʹ���������������ȭ���ľ���֮һ������֡���\n" NOR;

        me->add("neili", -30);
        if (random(me->query_skill("cuff")) > (int)target->query_skill("force") / 2 || !living(target))
        {
		msg += HIR "���$p" HIR "�����мܣ�һʱȴ����"
                       "�������ã���$P" HIR "��ס����һ������ʱ����"
                       "���ȣ��������������Ȧ�ӡ�\n" NOR;
		target->start_busy((int)me->query_skill("cuff") / 20 + 2);
	} else
        {
		msg += CYN "����$p" CYN "����һ�ܣ�Ӳ��������$P"
                       CYN "��һȭ��\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}

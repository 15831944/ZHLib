// chan.c �����޷� ���־�

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("yunlong-bian",1) < 50)
		return notify_fail("��ġ������޷�������̫ǳ��ʹ���ˡ������־���\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���ʹ���ˡ������־���\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (! living(target))
                return notify_fail("�Է��Ѿ�û��ս�������ˣ�������ʹ�á������־���\n");

	msg = CYN "$N" CYN "ʹ�������޷��������־������ӳ�����ͼ��$n"
              CYN "��ȫ���ס��\n" NOR;

	if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 2)
        {
		msg += HIY "���$p" HIY "��$P" HIY "���˸����ֲ�����\n" NOR;
		target->start_busy((int)me->query_skill("whip") / 22 + 1);
		me->start_busy(1 + random(2));
	} else
        {
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ����û���ϵ���\n" NOR;
		me->start_busy(4);
	}
	message_combatd(msg, me, target);
	return 1;
}

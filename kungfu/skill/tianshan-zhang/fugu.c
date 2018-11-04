// fugu.c ��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���������ǡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        if (!living(target))
                return notify_fail("�Է��Ѿ�����ս���ˣ�\n");

	if ((int)me->query_skill("tianshan-zhang", 1) < 80)
		return notify_fail("�����ɽ�ȷ�������죬����ʹ�á��������ǡ���\n");

	msg = HIG "$N" HIG "�����Ц�����е�" + weapon->name() +
              HIG "����Ӱ��һ��Ϯ��$n��\n" NOR;

        ap = me->query_skill("staff");
        dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
        {
		msg += HIR "���$p" HIR "��$P" HIR "����ʧ�룬"
                       "Ū����æ���ң�����Ӧ�ԣ�\n" NOR;
		target->start_busy((int)me->query_skill("staff") / 25 + 2);
	} else
        {
		msg += "����$p" HIR "������$P" HIR "����ͼ��"
                       "����һ�ˣ���ȥ��$P" HIR "��׷����\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}

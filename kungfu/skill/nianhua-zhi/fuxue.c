// fuxue.c �黨ָ ���黨��Ѩ��

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;

	if (! target) target = offensive_target(me);

        if (!target) return notify_fail("��Ҫ��˭ʹ�÷�Ѩ��\n");
/*
	if (! target || ! me->is_fighting(target))
		return notify_fail("�黨��Ѩֻ�ܶ�ս���еĶ���ʹ�á�\n");
*/

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ�黨��Ѩ��\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("�㲻��������ʹ���黨ָ��\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("���ڹ���򲻹�������ʹ���黨��Ѩ��\n");

	if ((int)me->query_skill("finger") < 150)
		return notify_fail("���ָ����Ϊ������Ŀǰ������ʹ���黨��Ѩ������\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("��������������������ʹ���黨��Ѩ��\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if (me->query_skill_mapped("finger") != "nianhua-zhi") 
		return notify_fail("��û�м����黨ָ���޷�ʹ���黨��Ѩ��\n");

	msg = HIY "$N" HIY "ʹ���黨ָ�������黨��Ѩ������ס��$n"
              HIY "��ȫ��ָ���������Ĺ���$p" HIY "��ҪѨ��\n" NOR;

        if (random(me->query("combat_exp")) > (int)target->query("combat_exp") / 3 || !living(target))
	{
		msg +=  HIG "���$p" HIG "��$P" HIG "���˸����ֲ�����\n" NOR;
		target->start_busy((int)me->query_skill("nianhua-zhi", 1) / 19 + 2);
		me->add("neili", -100);
	}
	else
	{
		msg += CYN "����$p" CYN "������$P"
                       CYN "����ʽ����æԾ�����ܿ���$P"
                       CYN "�Ĺ�����\n" NOR;
		me->add("neili", -30);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

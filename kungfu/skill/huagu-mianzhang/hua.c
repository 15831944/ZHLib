// hua.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int damage;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ֻ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ʩչ�����ơ�\n");

	if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
		return notify_fail("��Ļ������ƻ�������죬���ữ���ơ�\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������������ܻ��ǡ�\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("��û�м����������ƣ��޷�ʩչ�����ơ�\n");

        me->add("neili", -100);

	msg = MAG "$N" MAG "�Ƴ������������$n" MAG "�ļ�ͷ��\n"NOR;

        ap = me->query_skill("huagu-mianzhang", 1) + me->query_skill("strike", 1) + me->query_skill("force", 1);
        if (living(target))
                 dp = target->query_skill("force",1) + target->query_skill("parry",1) + target->query_skill("dodge",1);
        else     dp = 0;
	if (ap / 2 + random(ap) > dp)
        {
	        me->start_busy(2);
                damage = ap / 3 + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "���ֻ���˵�һ����$p" HIR "��$P"
                                           HIR "һ�����У�һʱ��$p" HIR
                                           "ֻ����ȫ��ů����ģ��е��е���Ʈ�����ᡣ\n" NOR);
                target->affect_by("sl_poison",
                               ([ "level" : me->query("jiali") + random(me->query("jiali")),
                                  "id"    : me->query("id"),
                                  "duration" : ap / 60 + random(ap / 60) ]));
	} else
        {
		msg += CYN "����$p" CYN "��æ����һ�ԣ����˿�ȥ��\n" NOR;
		me->start_busy(3);
	}

	message_combatd(msg, me, target);
	return 1;
}

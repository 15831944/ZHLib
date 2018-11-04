// xiangmo.c �޺���ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	int damage;
	string msg;
        int ap, dp;

        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	if (! target || ! me->is_fighting(target))
		return notify_fail("���޺���ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("luohan-quan", 1) < 20)
		return notify_fail("����޺�ȭ��������죬���ڻ��޷�ʹ�á��޺���ħ����\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ���޺���ħ����\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�����������������޷����á��޺���ħ����\n");
			
	if (me->query_skill_mapped("cuff") != "luohan-quan") 
		return notify_fail("��û�м����޺�ȭ���޷�ʹ���޺���ħ��\n");

	msg = HIY "$N" HIY "�˵�һ����һȭƽƽ��$n"
              HIY "����������а����ۣ��ľ߷緶��\n" NOR;

        ap = me->query_skill("cuff");
        dp = target->query_skill("parry");
        if (ap / 2 + random(ap) > dp || !living(target))
	{
		damage = 60 + ap / 5 + random(ap / 5);
		me->add("neili", -30);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "ֻ��$n" HIR "һ���м�ʧ�󣬵�ʱ"
                                           "����ȭ���˸����ţ��ƺ�һ��������һ����\n" NOR);
		me->start_busy(2);
                target->start_busy(1 + random(2));
	} else 
	{
		msg += CYN "����$p" CYN "����һ�񣬼�ס��$P"
                       CYN "����ȭ��\n" NOR;
		me->add("neili", -10);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

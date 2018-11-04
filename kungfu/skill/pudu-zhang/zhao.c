// zhao.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
        int ap, dp;
        int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail("��������ա�ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

        if (me->query_skill_mapped("force") != "hunyuan-yiqi" &&
            me->query_skill_mapped("force") != "yijinjing" &&
            me->query_skill_mapped("force") != "shaolin-xinfa" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��ʹ�õķ������ڹ����޷�ʩչ������գ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("pudu-zhang", 1) < 135)
		return notify_fail("����ն��ȷ���Ϊ������Ŀǰ����ʹ�÷�����գ�\n");

	if (me->query("neili") < 1000)
		return notify_fail("�����������������ʹ�÷�����գ�\n");

        if (me->query_skill_mapped("staff") != "pudu-zhang")
                return notify_fail("��û�м����ն��ȷ�������ʹ�÷�����գ�\n");

	msg = HIY "$N" HIY "������Ц���Ӷ����е�" + weapon->name() +
              HIY "����̩ɽһ��ѹ��$n" + HIY "������̾Ϊ��ֹ��\n" NOR;

        ap = me->query_skill("staff") + me->query("max_neili") / 10;
        dp = target->query_skill("force") + target->query("max_neili") / 10;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                damage = me->query("max_neili") - target->query("max_neili");
                if (damage < 0) damage = 0;
                damage = damage / 5 + me->query_skill("staff") / 3;
                damage += random(damage / 3);
                me->add("neili", -250);
                me->start_busy(1);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "ֻ��$p" HIR "�ƺ�һ�������ж���"
                                           "�����������ӷɵ���ȥ�����ص�ˤ���ڵ��ϣ�\n" NOR);
                target->start_busy(0);
        } else
        {
                me->add("neili", -60);
                me->start_busy(3);
                msg += CYN "����$p" CYN "����������������ס��"
                       CYN "$P" CYN "�⾪�춯�ص�һ����\n"NOR;
        }
	message_combatd(msg, me, target);

	return 1;
}

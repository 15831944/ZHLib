// you.c ��Ůȭ-��Ĺ�ľ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��Ĺ�ľ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
	
	if (me->query_temp("weapon"))
		return notify_fail("��ֻ�п��ֲ��ܹ�ʹ����Ůȭ����\n");
 
        if ((int)me->query_skill("meinv-quan", 1) < 80)
                return notify_fail("�����Ůȭ���𲻹�������ʹ�ù�Ĺ�ľӡ�\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("����ڹ���δ��죬�����������˵С�\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("��������������������ʹ�ù�Ĺ�ľӡ�\n");

        if (me->query_skill_mapped("cuff") != "meinv-quan")
                return notify_fail("��û�м�����Ůȭ��������ʩչ��Ĺ�ľӡ�\n");

        msg = HIW "$N" HIW "����֧�ã���������ӳ�����̾һ����ʹ"
              "������Ĺ�ľӡ���һ�����ּ���֮�⡣\n" NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
                me->start_busy(random(3));

                damage = (int)me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);
		damage += (int)me->query("jiali")*2;

                me->add("neili", -100-me->query("jiali")/2);

                if (damage < 30)
                        pmsg = HIY "���$n" HIY "��$N��"
                               HIY "��һ�����ƺ�һ����\n" NOR;
                else if(damage < 55)
                        pmsg = HIY "���$n" HIY "��$N"
                               HIY "������һ���������ڡ����˳�������\n" NOR;
                else if (damage < 80)
                        pmsg = HIR "���$n" HIR "��$N"
                               HIR "������һ�����ؿ������ܵ�һ����"
                               "������ѪΪ֮һ�ϣ�\n" NOR;
                else
                        pmsg = RED "���$n" RED "��$N" RED
                               "������һ������ǰһ�ڣ�������Ѫ���ڣ�"
                               "���������¯һ�㣡\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 25, pmsg);
        } else
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P" CYN
                       "����ͼ������̩ɽ��̧��һ�ܸ���$P"
                       CYN "��һȭ��\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

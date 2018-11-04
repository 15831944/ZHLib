// chan.c ���߲���

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("�����߲���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "staff")
                return notify_fail("���á����߲������б�����ȣ�\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("����ڹ���򲻹���\n");

        if ((int)me->query_skill("staff") < 80)
                return notify_fail("����ȷ��������ң��޷�ʹ�á����߲�����\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

        msg = HIG "$N���е�" + weapon->name() +"ͻȻ�����һβ���ߣ��͵�˦����βѸ�ٵĲ���$n��\n" NOR;

        ap = me->query_skill("staff");
        dp = target->query_skill("dodge");
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIB "$n������͸������������������\n" NOR;
                target->start_busy(ap / 19 + 2);
             me->start_busy(1);
        } else 
        {
                msg += HIY "�Һ�$p������$N�������������������$P�Ĺ�����Χ��\n" NOR;

                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}


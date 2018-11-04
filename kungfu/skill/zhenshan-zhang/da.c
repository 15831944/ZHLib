#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ɽ��ţֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�ø�ɽ��ţ��\n");         
                
        if ((int)me->query_skill("zhenshan-zhang", 1) < 60)
                return notify_fail("�����ɽ�Ʋ�����죬����ʹ�ø�ɽ��ţ��\n");

        if (me->query("max_neili") < 500)
                return notify_fail("����ڹ���Ϊ���㣬�޷�ʩչ��ɽ��ţ��\n");

        if (me->query("neili") < 150)
                return notify_fail("����������̫�����޷�ʩչ��ɽ��ţ��\n");
                        
        msg = WHT "$N" WHT "�Ŷ���������һ������ʹ����ɽ��ţ��˫�ƶ�׼$n"
              WHT "ƽƽ�Ƴ���\n" NOR;
        me->add("neili", -100);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
                me->start_busy(3);
                target->start_busy(random(3));
                
                damage = (int)me->query_skill("force", 1);
                damage = damage / 4 + random(damage / 4) + me->query("jiali");
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 30,
                                           HIR "$n" HIR "������æ���һ�ݣ����ֻ��"
                                           "�ؿ�һ�𣬶�ʱ����������ԭ��$N" HIR 
                                           "���ھ����ˣ�\n"
                                           ":����@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ����û���ϵ���\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}


// an.c ̫��ȭ�������־�
// Modify by haiyan

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/taiji-quan/an")) 
                return notify_fail("�㻹����ʹ�á������־���\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ�á������־���\n"); 
                
        if ((int)me->query_skill("taiji-quan", 1) < 400)
                return notify_fail("���̫��ȭ������죬����ʹ�á������־���\n");
                                
        if ((int)me->query("neili", 1) < 300)
                return notify_fail("����������̫��������ʹ�á������־���\n");
                        
        msg = HIG "$N" HIG "˫ȭ���»Ӷ���ʹ��̫��ȭ�������־���$n"
              HIG "�е�һ��ǿ��ľ�����ͷ��ѹ�䡣\n" NOR;
        me->add("neili", -200);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(3);
                target->start_busy(random(3));
                damage = (me->query("qi",1) + me->query("jing",1) * 2 + 
                         me->query("shen",1) / 500 + me->query("neili",1)) / 20; 
                damage = damage + random(damage / 3);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 50,
                                           HIY "$n" HIY "�Ǹк��������������ѵ���"
                                           HIY "��ͷһ�𣬿�������"HIR"��Ѫ"HIY"��\n"
                                           ":����@?");
        } else 
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "�����ڹ����۾����⣬ͦ��Ӳ����$P"
                       HIY "��һ�У����顱��һ�����죬˫����������������\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

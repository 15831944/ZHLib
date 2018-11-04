// suo.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/suohou-gong/suo"))
                return notify_fail("�����ڻ�����ʹ�á�������һ�У�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("����ֻ����ս���жԶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������ֲ���ʹ������\n");
                
        if ((int)me->query_skill("suohou-gong", 1) < 140)
                return notify_fail("���������������죬����ʹ������\n");
                                
        if ((int)me->query("neili", 1) < 200)
                return notify_fail("����������̫��������ʹ������\n");
                        
        msg = HIY "$N" HIY "��Цһ��������һԾ������¶�׹⣬���ֶ�Ȼץ"
              "��$n" HIY "�ĺ���\n\n" NOR;
        me->add("neili", -20);

        me->want_kill(target);
        ap = me->query_skill("claw");
        dp = target->query_skill("dodge");
        if (ap / 2 + random(ap * 2 / 3) > dp || !living(target))
        {
                me->start_busy(2);
                me->add("neili", -180);
                damage = 0;

                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                        msg += HIR "���ֻ�����������������죬$N" HIR "��ָ�ѽ�$n"
                               HIR "���������飬$n" HIR "һ���������������̱����ȥ��\n" NOR;
                        damage = -1;
                } else
                {
                        target->start_busy(1 + random(3));
        
                        damage = ap + (int)me->query_skill("force");
                        damage = damage / 2 + random(damage / 2);
                        
                        if (arrayp(limbs = target->query("limbs")))
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "Ҫ��";
                        pmsg = HIC "$n��æ��Ų������ֻ�������ꡱһ����$N"
                               HIC "��ָ������$n" HIC "��" + limb + "��$n"
                               HIC "һ���ҽУ���Ѫ�ɽ�������\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66, pmsg);
                }
        } else 
        {
                me->start_busy(2);
                msg += CYN"����$p������$P����ͼ�����μ������㿪����һץ��\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0)
        {
                target->receive_wound("qi",1,me);
                target->die();
        }

        return 1;
}


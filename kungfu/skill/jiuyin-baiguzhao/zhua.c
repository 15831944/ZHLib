// Code of JHSH
// Modified by haiyan@huaxia

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)
{
        object report;
        int damage,lvl,lvl1,k,l,ap,dp;
        string str;

        if (!target ) target = offensive_target(me);

        if (!target||!target->is_character()||!me->is_fighting(target) )
                return notify_fail("��������צ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("�������������������ʹ����������צ����\n");

        if ((lvl=(int)me->query_skill("jiuyin-baiguzhao",1))< 200)
                return notify_fail("��ľ����׹�צ��Ϊ������\n");

        if ((lvl1=(int)me->query_skill("cuixin-zhang",1))< 150)
                return notify_fail("��Ĵ�������Ϊ������\n");

        if (userp(me) && !me->query("can_perform/jiuyin-baiguzhao/shenzhao"))
                return notify_fail("�㲻��ʹ�á�������צ��������У�\n");

        if (me->query("jiali") < 50)
                return notify_fail("��ĳ�����ô�ᣬ�ֺα�ʹ��ɱ���أ�\n");

        if (me->query("neili")<=lvl*4) return notify_fail("�������������\n");

        if (me->query("jingli")<=lvl) return notify_fail("��ľ���������\n");

        message_vision(HIW "\n$NͻȻ�������һ�ƣ����ּ��졣�����ָ���������������͵ľ�������$n�����顣\n\n" NOR, me,target);

        ap = me->query_skill("claw") + me->query_skill("force") + me->query_str()*10; 
        ap += me->query("jiali")*2/3;
        dp = target->query_skill("dodge") + target->query_skill("force") + target->query_con()*10; 

        me->add("neili", -lvl);
        if (!target->is_killing(me->query("id"))) target->kill_ob(me);

        //the accurate is decied by dex and used times and exp
        if (!living(target))
        {
                message_vision(HIR "ֻ���۵�һ���죬$N�������ָ�Ѳ�����$n��ͷ����\n\n" NOR, me,target);
                target->die(me);
                return 1;
        }

        if (ap / 2 + random(ap) < dp ){  
                message_vision(CYN "$n��֪���ң�����$N������ǳ����Ȼһ�����У�ȴ����ǿ��֮ĩ����Ҳ��������ȥ�ˡ�\n\n" NOR, me,target);
                me->start_busy(2);
                return 1;
        }

        if (ap / 2 + random(ap) > dp || !living(target)) 
        {
                damage = (lvl + lvl1)*2 + me->query_str()*me->query("jiali")*3/target->query_con();
                if (damage<=100) 
                        message_vision(BLU "$n��֪��������������������㡣���ǿ����ܹ������Ѿ�����һ���亹��\n\n" NOR, me,target);
                else {
                        if ((int)damage >= target->query("eff_qi")) 
                        {
                                message_vision(HIR "ֻ���۵�һ���죬$N�������ָ�Ѳ�����$n��ͷ����\n\n" NOR, me,target);
                                target->receive_wound("qi",1,me);
                                target->die(me);
                                return 1;
                        }
                        message_vision(MAG "$n��֪��������������������㡣��Ȼ�ܹ�������Ҫ��������ȴ��ץ�����Ѫ�ۡ�\n\n" NOR, me,target);
                        target->receive_wound("qi",damage,me);
                        str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
                        message_vision("($N"+str+")\n", target);
                }
                target->start_busy(1+random(3));
                me->add("neili", -lvl);
                me->start_busy(4);
                return 1;
        }
        if (ap / 2 + random(ap) > dp * 3/2 || !living(target)){  
                damage=(2+random((me->query_str()*2+me->query("jiali"))/100))*lvl;
                if ((int)damage >= target->query("eff_qi")) {
                        message_vision(HIR "ֻ���۵�һ���죬$N�������ָ�Ѳ�����$n��ͷ����\n\n" NOR, me,target);
                        target->die(me);
                        return 1;
                }
                if ((int)damage/target->query("eff_qi")*100>=50&&(int)damage/target->query("eff_qi")*100<100)
                        message_vision(HIR "ֻ��৵�һ����$n��������ѱ�����һ���ͷƤ����ʱѪ����ע��\n\n" NOR, me,target);
                if ((int)damage/target->query("eff_qi")*100<50)
                        message_vision(HIR "ֻ�����һ����$n�������ѱ�ץ����������Ѫ�����צ�ۡ�\n\n" NOR, me,target);
                target->receive_wound("qi", damage, me);
                str = COMBAT_D->status_msg((int)target->query("eff_qi") * 100 /(int)target->query("max_qi"));
                message_vision("($N"+str+")\n", target);
                target->start_busy(1+random(3));
                me->add("neili", -lvl*2);
                me->start_busy(4);
                return 1;
        }
        message_vision(HIC "$n������������ݵ�������˰벽�����ѱܿ���$N������һ����\n\n" NOR, me,target);
        tell_object(me, HIR"�����һ����ֻ���ʹ˵��֡�����ȴ���������������������ʱ¶���˼���Ŀ��š�\n\n"NOR);
        me->start_busy(3+random(3));
        return 1;
}


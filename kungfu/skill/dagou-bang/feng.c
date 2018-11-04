// feng.c �򹷰����־�
// Rama 2001/11/11
// �����������
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
inherit F_DBASE;

int perform(object me, object target)
{
        string* msghit, msg;
        object weapon;
        int  feng_busy;
        int feng_addspeed;
        int feng_cost;
        int feng_duration;
        int feng_parry;
        int ap,dp;
        string *limb, type, limb_hurt;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) 
        ||          !living (target) )
                return notify_fail("���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( target->is_busy() ) {
                me->add("neili", -10);
                me->add("jingli", -5);
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");
        }

        if( me->query_temp("ban",1) )
                return notify_fail("������ʹ�ð��־���\n");

        if(! living(target))
                return notify_fail("�����Ѿ��������㲻����ʹ�÷��־���\n");

        if( me->query_temp("pfmfeng",1) )
                return notify_fail("������ʹ�÷��־���\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" )
                return notify_fail("�����õĲ��ǻ����������޷�ʩչ���־���\n");

        if( me->query_skill("force") < 250 )
                return notify_fail("��Ļ����������δ�����޷�ʩչ���־���\n");

        if( me->query_skill("staff") < 250 )
                return notify_fail("��Ĵ򹷰�����Ϊ���㣬������ʹ�÷��־���\n");

        if( me->query("neili") <= 1000 )
                return notify_fail("�������������\n");

        if( me->query("jingli") <= 600 )
                return notify_fail("��ľ���������\n");

        if( !objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type") != "staff")
                 return notify_fail("�������ʹ�÷��־�����\n");

        msghit = ({
                "\n$N����򹷰����еġ��⡹�־�������ȫ�Ǻ�ʹ��������������һ��"+(string)weapon->query("name")+HIG"����һƬ��ǽ���������š�\n",
                "\n$N���һ��������"+(string)weapon->query("name")+HIG"��ʹ���򹷰����ġ��⡹�־���������ס�Ż���\n",
                "\n$N����"+(string)weapon->query("name")+HIG"��ʹ���򹷰����ġ��⡹�־�����ס��ǰ����ס���ơ�\n",
                "\n$N����"+(string)weapon->query("name")+HIG"��ʹ���򹷰����е�һ�С���Ȯ��·�����������⡹�־���\n"
        });
        msg = HIG"\n"+ msghit[random(sizeof(msghit))] +"\n" NOR;
        message_vision(msg, me, target);

        ap = me->query_skill("force") + me->query_skill("staff") + me->query_str()*10 + me->query("jiali");
        dp = target->query_skill("dodge") + target->query_skill("parry") + target->query_dex()*10 + target->query("jiali");

        if (ap/3 + random(ap) > dp)
        {
                msghit = ({
                        "���⡹�־����Ǿ����ͻ���壬$n���в�֧�����¹���ȫ����ס��\n",
                        "ֻ����ӰƮƮ�����⡹�־���ʱ��$n��ǰ����֮�ؾ�����ס�ˡ�\n",
                        "$nͻ��"+(string)weapon->query("name")+HIY"���������޷���һʱ��Ȼ��������Թ��롣\n"
                });
                msg = HIY"\n"+ msghit[random(sizeof(msghit))] +"\n" NOR;
                message_vision(msg, me, target);

                feng_busy= me->query_skill("staff")/15;
                feng_parry = feng_busy * 5;
                
                me->add_temp("apply/parry", feng_parry);
                target->add("qi",-me->query_skill("staff")/5);
                target->add("jing",-me->query_skill("staff")/5);
                target->set_temp("feng",1);
                me->set_temp("pfmfeng",1);
                target->start_busy(1+random(3));

                feng_duration= 2 + feng_busy/( weapon->weight()/1000);
                
                call_out("remove_effect",feng_duration,me,target,feng_parry);
        }
        else
        {
                msghit = ({
                        "$n��ʱ������ʱ�ϣ���û�б���ס��\n",
                        "$n���ٱ��У���æ�м����������ܿ��ˡ��⡹�־���\n"
                });
                msg = CYN"\n"+ msghit[random(sizeof(msghit))] +"\n" NOR;
                me->start_busy( 2 + random(3));
                message_vision(msg, me, target);
        }

        feng_cost = me->query_skill("staff") / 2;
        me->add("neili", -feng_cost );
        me->add("jingli", -feng_cost/3 );

        return 1;
}

private int remove_effect(object me, object target, int feng_parry)
{
        int skills;
        object weapon;
        if (objectp(me))
        {
                me->add_temp("apply/parry",  -feng_parry);
                me->delete_temp("pfmfeng");
        }
        if (objectp(target))
                target->delete_temp("feng");

        if(objectp(me) && objectp(target) && target->is_fighting(me) )
                message_vision(HIG"\n$N�İ��ж��䣬�򹷰��ġ��⡹�־���Ȼ�߽⡣\n"NOR ,me,target); 
        return 1;
}


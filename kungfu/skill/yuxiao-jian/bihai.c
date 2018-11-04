#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp, lvl;
        int jing, skill, damage, jieti;
        object ob;

        if (! objectp(ob = me->query_temp("handing")) ||
            ! ob->valid_as_xiao())
                return notify_fail("������û���������޷�ʹ��������У�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(HIW "�̺�����������" NOR
                                   "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->query_skill_mapped("sword") != "yuxiao-jian") 
                return notify_fail("�㲢û��ʹ�����｣����\n"); 

	if (me->is_busy())
		return notify_fail("����һ��������û����ɣ����ܴ�����\n");

        skill = me->query_skill("yuxiao-jian", 1);

        if (skill < 150)
                return notify_fail("������｣���ȼ�����, ����ʹ��"
                                   HIW "�̺�����������" NOR "��\n");

        if (!living(target))
                return notify_fail("�Է������������㴵���ˡ�\n");

        if (me->query("neili") < 800)
                return notify_fail("��������������޷�����"
                                   HIW "�̺�����������" NOR "��\n");

        ap = me->query_skill("force") + me->query_skill("sword");
        dp = target->query_skill("force");

        lvl = (int) me->query_skill("yuxiao-jian", 1) / 5 + 1;

        jieti = me->query("tianmo_jieti/times");
        if (jieti>5) jieti = 5;

        msg = HIC "$N" HIC "�ְ������̤���Է�λ�����" NOR
              HIW "��" NOR+HIC "�̺�����������" NOR+HIW "��" NOR
              HIC "............\n" NOR;
        msg += HIG "\nֻ���������٣�����񣬷��˼�������������"
                   "���Ʈ��һ��������͵Ķ���������\n" NOR;

        if (dp < random(ap * 2))
        {
                msg += HIR "$n" HIR "��ͷһ�������ϲ��Խ���¶��΢Ц��\n" NOR;
                jing = (int) target->query("max_jing");

                damage = jing * lvl / 700;
                //Add By Smallfish:������ħ�����ɱ�����ı仯
                damage -= damage*jieti/(5+jieti);

                target->receive_wound("jing", damage, me);
                message_combatd(msg, me, target);
        } else
        {
                msg += HIY "$n" HIY "����������һ��������������Ӧ��ԣ�磡\n" NOR;
                message_vision(msg, me, target);
        }

        msg = HIG "\n�Ƕ���������Ʈ����������ת������һ��Ů��һ��"
                  "��̾Ϣ��һ���������һ����������´��\n"
                  "�����л���\n" NOR;

        if (dp < random(ap))
        {
                msg+= HIR "$nֻ��ȫ����Ѫ���ڣ���ֻ�������㵸���Ҷ�һ����\n"NOR;
                jing = (int) target->query("max_jing");
 
                damage = jing * lvl / 500;
                //Add By Smallfish:������ħ�����ɱ�����ı仯
                damage -= damage*jieti/(5+jieti);

                target->receive_wound("jing", damage, me);
                message_combatd(msg, me, target);
        } else
        {
                msg += HIY "$n" HIY "ü��΢������ɫ�������أ���������Ӧ����������������\n" NOR;
                message_vision(msg, me, target);
        }

        msg = HIG  "\n��������������󺣺��������޲���Զ����ˮ�����ƽ����������죬��������ӿ��������\n"
                   "ɽ������ˮ����Ծ�����������Ϸ�ХŸ�ɣ��ټ���ˮ�����֣�ȺħŪ����������ɽƮ��������\n"
                   "�Ⱥ���У��������֮���¡�\n" NOR;

        if (dp < random(ap / 2))
        {
                msg+= HIR "$n" HIR "ֻ����ͷ���ȣ�������\n" NOR;
                jing = (int) target->query("max_jing");

                damage = jing * lvl / 300;
                //Add By Smallfish:������ħ�����ɱ�����ı仯
                damage -= damage*jieti/(5+jieti);

                target->receive_wound("jing", damage, me);
                message_combatd(msg, me, target);
        } else
        {
                msg += HIY "$n" HIY "��ɫ��䣬����΢�Σ�Ŀ��������ʹ��֮�⣡\n" NOR;
                message_vision(msg, me, target);
        }

        msg = HIG "\n����������ϸ�������������ţ����糱�˺�ˮƽ��"
                  "��������ȴ���ǰ����ļ���\n" NOR;

        if (dp < random(ap / 3))
        {
                msg+= HIR "$n" HIR "��ʱ���ݾ�������Ҳ�޷�����\n" NOR;
                jing = (int) target->query("max_jing");

                damage = jing * lvl / 100;
                //Add By Smallfish:������ħ�����ɱ�����ı仯
                damage -= damage*jieti/(5+jieti);

                target->receive_wound("jing", damage, me);
                me->add("neili", -200);
                message_combatd(msg, me, target);
        } else
        {
                msg+= HIY "$n" HIY "���Ӵ��ζ��˼��£�����ˮ���죬��Ȼ����ȫ��֮���ŵ�ס��������\n" NOR;
                me->add("neili", -800);
                message_vision(msg, me, target);
        }

        me->start_busy(2 + random(3));
        if (target->is_busy())
                target->start_busy(1 + random(2));
        return 1;
}

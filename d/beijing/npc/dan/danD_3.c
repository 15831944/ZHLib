#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC"��Ԫ��"NOR, ({"guiyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if (time() - me->query_temp("last_eat/dan(D)") < 180)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        nl = (int)me->query("neili") + 500;
        mn = (int)me->query("max_neili") * 2;

        if (nl > mn)
        {
                write("������������Ϊ�������" + name() + "��\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        me->set_temp("last_eat/dan(D)", time());

        message_vision(HIC "$N����һ����Ԫ�����е������������䡣\n" NOR, me);
        me->add("neili", 500);

        me->start_busy(3);
        destruct(this_object());
        return 1;
}


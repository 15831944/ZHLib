#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC "������" NOR, ({"yangjing dan", "dan"}));
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

        if (time() - me->query_temp("last_eat/dan(A)") < 10)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["jing"] == my["max_jing"])
        {
                write("�����ھ���״̬�ܺã��������" + name() + "��\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        me->set_temp("last_eat/dan(A)", time());

        message_vision(HIC "$N����һ�����������е���̨��һƬ�徻��\n" NOR, me);
        me->receive_curing("jing", 50);
        me->receive_heal("jing", 50);

        me->start_busy(2);
        destruct(this_object());
        return 1;
}


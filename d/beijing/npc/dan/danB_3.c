#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(WHT"�󲹵�"NOR, ({"dabu dan", "dan"}));
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

        if (time() - me->query_temp("last_eat/dan(B)") < 10)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["qi"] == my["max_qi"])
        {
                write("�������������棬�������" + name() + "��\n");
                return 1;
        }
        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        me->set_temp("last_eat/dan(B)", time());

        message_vision(WHT "$N����һ���󲹵����е���Ϣ�õ��˱Ƚϴ�ĵ�����\n" NOR, me);
        me->receive_curing("qi", 300);
        me->receive_heal("qi", 300);

        me->start_busy(3);
        destruct(this_object());
        return 1;
}


#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIC"����"NOR+HIR"�޳�"NOR+HIY"��"NOR, ({"xiuluo dan", "dan"}));
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

        if (time() - me->query_temp("last_eat/dan(C)") < 240)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        me->set_temp("last_eat/dan(C)", time());

        message_vision(HIR "$N����һ�������޳����������õ�����ȫ�ĵ�����\n" NOR, me);
        me->set("jingli",me->query("max_jingli"));

        me->start_busy(3);
        destruct(this_object());
        return 1;
}


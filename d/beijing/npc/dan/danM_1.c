#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIM"���ѵ�"NOR, ({"longxian dan", "dan"}));
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

        if (time() - me->query_temp("last_eat/dan(M)") < 400)
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();

        if( me->is_busy() )
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        me->set_temp("last_eat/dan(M)", time());

        message_vision(HIM "$N����һ�����ѵ����е��������ۺ���һЩ��\n" NOR, me);
        me->add("max_neili", 1);

        me->start_busy(6);
        destruct(this_object());
        return 1;
}


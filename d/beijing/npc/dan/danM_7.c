#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW"���µ�"NOR, ({"yaoyue dan", "dan"}));
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

        message_vision(HIW "$N����һ�����µ����е�������Ϊ����ǰ������ߡ�\n" NOR, me);
        me->add("max_jingli", 2);

        me->start_busy(2);
        destruct(this_object());
        return 1;
}


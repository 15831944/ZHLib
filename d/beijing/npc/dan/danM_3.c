#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIY"������"NOR, ({"longwang dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("no_drop", "�������������뿪�㡣\n");
                set("no_sell", "�������������뿪�㡣\n");
                set("no_put", "�����������ܷ����Ƕ���\n");
                set("no_get", "�������������뿪�Ƕ���\n");
                set("no_steal", "�������������뿪�Ƕ���\n");
                set("no_beg", "�������������뿪�Ƕ���\n");
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

        message_vision(HIY "$N����һ�����������е��������ۺ���һЩ��\n" NOR, me);
        me->add("max_neili", 3);

        destruct(this_object());
        return 1;
}
void owner_is_killed()
{
        destruct(this_object());
}


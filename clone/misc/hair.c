// hair.c ͷ��

#include <ansi.h>

inherit ITEM;
inherit F_SILENTDEST;

int is_hair() { return 1; }

void create()
{
        set_name(RED "ͷ��" NOR, ({ "hair" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 1);
                set("no_sell", "��������Ǽٷ��꣬��һ�߶�ȥ��");
                set("long", WHT "һ��ͷ����\n" NOR);
        }
}

int set_from(object owner)
{
        set("gender", owner->query("gender"));
        if (query("gender") == "Ů��")
        {
                set("name", "��˿");
                set("long", CYN "һ����˿��\n" NOR);
        }
        return 1;
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        int r;

        if (! arg || ! id(arg))
                return notify_fail("��Ҫ��ʲô��\n");

        message_vision("$N����ͷ����ҧ�����Ū�����춼��ͷ��˿��\n",
                       this_player(), this_object());
        return 1;
}

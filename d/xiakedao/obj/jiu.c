// jiu.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_drink", "drink");
        add_action("do_drink", "he");
}
void create()
{
        set_name(HIC "�����̻��" NOR, ({"xuanbingbihuo jiu", "jiu"}));
        set("unit", "��");
        set("long", "����һ�����֮���������̻��, ��˵�ܽ�ٶ���\n");
        setup();
}
int do_drink(string arg)
{
        if (!id(arg))  return notify_fail("��Ҫ��ʲô��\n");

        this_player()->set("eff_jing",this_player()->query("max_jing"));
        this_player()->set("jing",this_player()->query("max_jing"));
        tell_object(this_player(), HIC "��ֻ��һ�����������ķΣ�����������ˬ��\n" NOR );
        destruct(this_object());
        return 1;
}

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
        set_name(HIC "玄冰碧火酒" NOR, ({"xuanbingbihuo jiu", "jiu"}));
        set("unit", "壶");
        set("long", "这是一壶珍贵之极的玄冰碧火酒, 据说能解百毒。\n");
        setup();
}
int do_drink(string arg)
{
        if (!id(arg))  return notify_fail("你要喝什么？\n");

        this_player()->set("eff_jing",this_player()->query("max_jing"));
        this_player()->set("jing",this_player()->query("max_jing"));
        tell_object(this_player(), HIC "你只觉一股清香沁入心肺，真是神意清爽！\n" NOR );
        destruct(this_object());
        return 1;
}

#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIM "素女经" NOR, ({ "sunvjing" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "本");
            set("material", "paper");
            set("long", "一本素女经。\n");
          }

    setup();
}


#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIC"卖身契"NOR, ({ "msqi" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "张");
            set("material", "cloth");
            set("long", "一张破旧的卖身契\n");
          }

    setup();
}


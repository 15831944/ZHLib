#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIC"四十二章经"NOR, ({ "ssezj" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "本");
            set("material", "stone");
            set("long", "一本佛家典籍。\n");
          }
    setup();
}


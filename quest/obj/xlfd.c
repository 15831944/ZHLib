#include <ansi.h>
#include <weapon.h>
inherit THROWING;
void create()
{
   set_name(RED"小李飞刀"NOR,({"xlfd"}));
   set_weight(200);
   if(clonep())
        set_default_object(__FILE__);
   else {
          set("unit","堆");
          set("value",1000);
          set("base_unit","把");
          set("base_weight",1);
          set("base_value",1);
          set("material","steel");
          set("long","一把人见人怕的小李飞刀! \n");
          set("wield_msg","不知何时，$N手中已突然多了一把$n! \n");        
          set("unwield_msg","$N从怀中掏出一个木像，用$n认真地刻着. \n");
        }
   set_amount(1);
   init_throwing(100);
   setup();
}


#include <ansi.h>
#include <armor.h>

inherit HEAD;
string do_wear();
string do_remove();

void create()
{
        set_name(HIM "蝶贝佳人" NOR, ({ "diebei jiaren", "jiaren" ,"hua"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", HIY "这是一朵有七种色彩地蝶贝佳人，此花堪称世间极品中的极品。\n" NOR);
                set("value", 1000000);
                set("material", "plant");
                set("armor_prop/armor", 0);
                set("armor_prop/personality", 8);
                set("wear_msg", (: do_wear :));
                set("remove_msg",(: do_remove :));
        }
        setup();
}
int deck()
{
        object me;

        me = this_player();
        me->set("per", 30);
        return 1;
}

string do_wear()
{
        object me;

        me = this_player();
        me->set_temp("deck",(: deck() :));

        message_vision(HIY "$N开始用"HIM"蝶贝佳人"HIY"来打扮自己\n"
                    HIY "戴上"HIM"蝶贝佳人"HIY"后,$N顿时散发出迷人的魅力。\n" NOR,me);
}

string do_remove()
{
        object me;
        me = this_player();
                message_vision(HIY "$N把"HIM"蝶贝佳人"HIY"摘了下来，$N魅力顿减。\n",me);
}



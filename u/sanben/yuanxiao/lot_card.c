
#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIG "�齱��" NOR, ({ "lot card", "card"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "����һ��Ԫ���ڳ齱�õĿ�Ƭ��\n"NOR);			
                set("unit", "��");
                set("value", 10);
                set("weight", 10);
                set("material", "paper");		  		  
             }	         
        setup();
}

int query_autoload() 
     { return 1; } 
		

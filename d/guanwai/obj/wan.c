// mian.c

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name("�ִ���", ({ "wan" }));
	set_weight(900);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ������Ҥ���ƵĻ��ߴ��롣\n");
		set("unit", "��");
		set("value", 50);
		set("food_supply", 10);
		set("water_supply", 25);
		set("max_liquid", 10);
        }

	set("liquid", ([
		"type": "water",
		"name": "����",
		"remaining": 6,
		"drunk_supply": 10,
	]));

        //setup();
}

void init()
{
	add_action("do_eat", "eat");
        add_action("do_eat", "drink");
}


int do_eat(string arg)
{
        if ( !(int)query("liquid/remaining") ||
             query("liquid/name") != "����" )
                return 0;

        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("����һ��������û����ɡ�\n");

        if( (int)this_player()->query("food")
           >= (int)this_player()->max_food_capacity() * 150 / 100)
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�Բ����ˡ�\n");

        this_player()->add("food", (int)query("food_supply"));
        if( (int)this_player()->query("water") <
            (int)this_player()->max_water_capacity()-(int)query("water_supply"))
                this_player()->add("water", (int)query("water_supply"));

        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        add("liquid/remaining", -1);
	if ( query("liquid/remaining") )
   		 message_vision("$N�����������ͺ��˼����ࡣ\n", this_player());
	else
   		 message_vision("$N������������ʣ�µ���ȵøɸɾ�����\n",this_player());

	return 1;
}

// giftd.c

#include <ansi.h>

inherit F_DBASE;
#define IDLE 600
static string gift_path = "/adm/daemons/gift/";

string *gift_file = ({
	"/clone/money/cash",
       "/clone/money/coin",
       "/clone/money/gold",
       "/clone/money/silver",
       "/clone/medicine/dieda",
       "/clone/money/gold",
       "/clone/city/obj/gourou",
       "/adm/daemons/gift/hongbing",
       "/adm/daemons/gift/huangqi",
       "/clone/money/gold",
       "/adm/daemons/gift/hupo-milijiu",
       "/clone/medicine/jiedu",
       "/adm/daemons/gift/jita",
       "/clone/food/jitui",
       "/clone/food/jiudai",
       "/d/city/obj/kaoya",
       "/clone/medicine/liuhe",
       "/adm/daemons/gift/mint",
       "/adm/daemons/gift/pantao-gao",
       "/clone/money/gold",
       "/clone/medicine/qingxin",
       "/d/city/obj/rrose",
       "/d/city/obj/yrose",
       "/clone/medicine/tongmai",
	"/clone/money/cash",
       "/clone/medicine/zhending",
       "/clone/misc/jinchuang",
       "/clone/misc/yanwu",
});

void ready_to_start()
{
        remove_call_out("start_gift");
        call_out("start_gift",  28800 + random(300));
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "��Ʒ��ʹ");
        CHANNEL_D->do_channel( this_object(), "sys", "����ϵͳ�Ѿ�������");
        ready_to_start();
}

int clean_up()
{
        return 1;
}

void start_gift()
{
        string the_gift;
        object ob;
        ready_to_start();
        log_file("static/gift",sprintf("\n����ϵͳ��¼��ʱ�䣺%s.\n",ctime(time())));
        foreach (object player in users()) {
                if (!interactive(player) || player->query("age") >= 20) continue;
                if (player->query("env/no_gift")) continue;
                the_gift = gift_file[random(sizeof(gift_file))];
                ob = new(the_gift);
                if (!ob) continue;
                ob->move(player);
                log_file("static/gift",sprintf("%s(%s)������%s.\n",player->name(1),player->query("id"), ob->query("name")));
                tell_object(player,HIY + "\n�����˷������������ﾫ��������������\n\n" + NOR + "��������Ϻ�����˵�ʲô��������ϸһ����ԭ����" + ob->name() + NOR + "��\n\n");
        }
}



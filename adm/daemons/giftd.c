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
        set("channel_id", "礼品天使");
        CHANNEL_D->do_channel( this_object(), "sys", "礼物系统已经启动。");
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
        log_file("static/gift",sprintf("\n礼物系统记录，时间：%s.\n",ctime(time())));
        foreach (object player in users()) {
                if (!interactive(player) || player->query("age") >= 20) continue;
                if (player->query("env/no_gift")) continue;
                the_gift = gift_file[random(sizeof(gift_file))];
                ob = new(the_gift);
                if (!ob) continue;
                ob->move(player);
                log_file("static/gift",sprintf("%s(%s)获得礼物：%s.\n",player->name(1),player->query("id"), ob->query("name")));
                tell_object(player,HIY + "\n天神浪翻云宣布：礼物精灵派送礼物啦！\n\n" + NOR + "你觉得身上好象多了点什么东西。仔细一看：原来是" + ob->name() + NOR + "！\n\n");
        }
}



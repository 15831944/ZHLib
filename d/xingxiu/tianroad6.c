// room: /d/xingxiu/tianroad6.c
// Jay 3/18/96

inherit ROOM;
#include <ansi.h>;
string look_wind();
int lian(string arg);
void create()
{
        set("short", "��ɽ����");
        set("long", @LONG
��������ɽ���塣����������Χ��ȥ�����׶���ԭ�ķ�⾡���۵ס�����
һ��С·������ɽ��ɽ��(wind)��������Ϊǿ���������޷�վ����
LONG
        );
        set("exits", ([
            "eastdown" : __DIR__"tianroad5",
        ]));
        set("item_desc", ([
            "wind" : (: look_wind :),
        ]));
        set("objects", ([
               "/clone/beast/dushe" : 2, 
        ]));
        set("outdoors", "xingxiuhai");
        setup();
}

string look_wind()
{
	return
"����һ�굽ͷ����ֹЪ�����Լ����麣�����磬����ζ���\n"
"�����ǳ���\n";
}

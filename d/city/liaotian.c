inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", "�͵�跿");
        set("long", @LONG
���������ݿ�ջ�Ĳ�¥������������µ������������죬��С�������ڿ�
���м䣬æ����ͣ�������һ��С�ţ�����ͨ���ռ������ġ�������־�����
�������ڡ�
LONG );
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("exits", ([
                "north" : __DIR__"kedian",
                "enter" : __DIR__"wfoxd",
        ]));

        setup();
}



//Room: majiu1.c 马厩
//Date: Oct. 2 1997 by That

#include <room.h>

inherit ROOM;

void create()
{
      set("short","马厩");
      set("long",@LONG
这是客店后的马厩，常年供应新鲜草料。扬州民风淳朴，马夫们会把
马牵到马厩好生照看，将它们喂饱饮足，再洗刷得干乾净净，一直伺候到
客人上路。
    马厩中堆放著几堆草料，正中有一口泔槽。
LONG);
      set("outdoors", "yangzhou");
      set("no_fight", "1");
      set("no_beg", "1");
      set("no_clean_up", 0);
      set("objects", ([
               "/clone/mapi": 10,
      ]));
      set("exits",([ /* sizeof() == 1 */
          "west"      : __DIR__"hotel",
      ]));
      setup();
}
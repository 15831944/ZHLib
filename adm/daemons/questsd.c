// quests.c
// creat by wsw 05/10/15
// 任务总管，负责分配各任务的奖励系数



#include <ansi.h>

#define X_TIMES 	1800 //计算时间，单位为秒
#define X_MIN 		300 //最小分配系数
#define X_MAX 		5000 //最大分配系数

inherit F_DBASE;
inherit F_SAVE;

int add_quest(string quest,int n);
int query_quest_x(string quest);
void announce_x();
mapping quest_x(mapping quest_sum);
void calculate_x();


static mapping quests = ([ //任务列表 李、门派、抓鬼、对诗、填海
//1.lijing 2.xue 逃犯任务 3.9mi 4.rulai 5.门派杀妖 6门派送物 7添海 8炼丹

   "li"		:	"中华挑战",
  // "jiumi"	:	"九迷任务",
  // "menpai1":	"门派寻物",
  // "menpai2":	"门派灭妖",
  // "zhongkui":	"钟馗抓鬼",
  // "kaifeng":	"开封任务",
  ]);
static mapping level = ([ //难度系数

   "li"		:	1,
  // "jiumi"	:	10,
  // "menpai1":	1,
  // "menpai2":	1,
  // "zhongkui":	1,
  // "kaifeng":	"开封任务",
  ]);

void create()
{
    	seteuid(getuid());
    	set("name", "任务总管");
   	 	set("id", "quests");
        restore();
        
        remove_call_out("calculate_x");
        call_out("calculate_x",1);
        remove_call_out("announce_x");
        call_out("announce_x",10);
}

void announce_x() //发布任务奖励系数
{
    string *klist,str;
    int i;
    object me = this_object();
	
	klist = keys(quests);
	str = HIR"【中华任务】"+HIW"浪翻云:装备任务奖励更新完毕：\n";
	for(i=0; i<sizeof(klist); i++) {
    	str +=HIW+"【"+quests[klist[i]] + "】:请大家到扬州武庙二楼接装备任务，体验新装备系统。\n";
    }
    str += NOR;

  	message("sys",str,users());
  	
  	 remove_call_out("announce_x");
     call_out("announce_x",600); //每10分钟发布一次	
}

void calculate_x() //计算任务奖励系数
{
	string *klist,str;
	int sum,x,i;
	mapping a1,a2,a3,a;
    object me = this_object();
	
	klist = keys(quests);
	
	a1 = quest_x(me->query("quest_a1"));
	a2 = quest_x(me->query("quest_a2"));
	a3 = quest_x(me->query("quest_a3"));
	a = quest_x(me->query("quest_sum"));
	
	me->set_temp("quest_a1",a);
	
	for(i=0; i<sizeof(klist); i++) {
		me->set("quest_x/"+klist[i],to_int(a1[klist[i]]*0.4+
			a2[klist[i]]*0.3+a3[klist[i]]*0.2+a[klist[i]]*0.1));
	}

	//修正
	sum = 0;
	for(i=0; i<sizeof(klist); i++) {
		sum += me->query("quest_x/"+klist[i]);
	}
	
	sum = (sum-sizeof(klist)*1000)/sizeof(klist);
	for(i=0; i<sizeof(klist); i++) {
		x = me->query("quest_x/"+klist[i])-sum;
		if (x < X_MIN) x = X_MIN;
		if (x > X_MAX) x = X_MAX;
		me->set("quest_x/"+klist[i],x);		
	}	
	//修正结束

	me->save();

  	 remove_call_out("calculate_x");
     call_out("calculate_x",600); //每10分钟计算一次	
}


int add_quest(string quest,int n) //每完成一个任务，增加n点，一般为1，quest为任务代码，见下面数组
{
	int i;
	object me = this_object();
	//不在任务列表中的不计入
	string *klist = keys(quests);
	if (member_array(quest,klist) == -1)
		return 0;
	//"quest_a"记录一定时间以内任务数量 ，一定时间以后清零。
	//"quest_a1"为上一时间段的任务完成数量
	//"quest_a2"为上上一时间段的任务完成数量
	//"quest_a3"为上上上一时间段的任务完成数量
	if (time() - me->query("quest_a/times") > X_TIMES ) {
		me->set("quest_a3",me->query("quest_a2"));
		me->set("quest_a2",me->query("quest_a1"));
		me->set("quest_a1",me->query("quest_a"));
		me->delete("quest_a");
		me->set("quest_a/times",time());
	}
	//单位时间完成任务数量
	me->add("quest_a/"+quest,n);
	//完成任务数量总量
	me->add("quest_sum/"+quest,n);
	me->save();
	return 1;
}
int query_quest_x(string quest) //查询任务当前奖励系数，此系数放大1000倍，实际计算时要除以1000。
{
	int quest_x;
	//return 1000; //测试用
	quest_x = this_object()->query("quest_x/"+quest);
	if (!quest_x) quest_x = 1000;
	return quest_x;
}

mapping quest_x(mapping quest_sum)
{
	string *klist;
	int i,sum,x;
	mapping quest_x;
	quest_x=allocate_mapping(100);
	klist = keys(quests);
	klist = sort_array(klist, "sort_keys", this_object());
	
	if (sizeof(klist) <= 1 || !mapp(quest_sum)) {//只有一个，就不用计算了
  	 	for(i=0; i<sizeof(klist); i++) {
  	 		quest_x[klist[i]]=1000;	
  	 	}
		return quest_x; 
	}
	sum = 0;
	for(i=0; i<sizeof(klist); i++) {
		sum += quest_sum[klist[i]]*level[klist[i]];
	}
	if (sum == 0) {
  	 	for(i=0; i<sizeof(klist); i++) {
  	 		quest_x[klist[i]]=1000;	
  	 	}
		return quest_x; 
	}	
	for(i=0; i<sizeof(klist); i++) {
		x = quest_sum[klist[i]]*level[klist[i]];
		x = 1000 - x + (sum-x)/(sizeof(klist)-1);
		if (x < X_MIN) x = X_MIN;
		if (x > X_MAX) x = X_MAX;
		quest_x[klist[i]]=x;
	}
	return quest_x; 
}

string query_save_file() { return DATA_DIR + "npc/quests"; }




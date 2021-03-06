// autoload.c
// From ES2
// Modified by Xiang for XKX (12/15/95)
// Updated by Doing for load unique object(inherit from F_NOCLONE)

string *autoload;
mapping newitem;

void clean_up_autoload() { autoload = 0; }
void clean_up_newitem() { newitem = 0; }

int is_save(object ob)
{
	string *item=({  //需要保存的物品文件名列表，也可根据需要设置为不保留的物品列表
						//query("changed")>=1的，保存所有属性，否则只保存文件和数量
             "/clone/newitem/baoshi/baoshi",
//             "/d/obj/drug/jinchuang",
//             "/d/obj/drug/hunyuandan",
//             "/d/playercity/obj/xiaomi",
//             "/d/playercity/obj/fan-xiaomi",
            
		});
	if (!ob) return 0;
	if (ob->query("changed")) return 1;
	//if (ob->query_autoload()) return 1;
	if ( member_array(base_name(ob),item) >= 0) return 1;
	return 0; 		
}


void save_autoload()
{
	object *inv;
        object *obs;
	int i, j;
	mixed param;

	inv = all_inventory();
        if (arrayp(obs = this_object()->query_temp("hire")))
                inv += obs - ({ 0 });
	autoload = allocate(sizeof(inv));
	for (i = 0, j = 0; i < sizeof(inv); i++)
        {
		if (! (param = inv[i]->query_autoload())) continue;
		autoload[j] = base_name(inv[i]);
		if (stringp(param)) autoload[j] += ":" + param;
		j++;
	}
	autoload = autoload[0..j - 1];
	
}

void restore_autoload()
{
	int i, j, k;
	object ob;
	string file, param, err, a, *key;
        int has_dropped;

	if (! pointerp(autoload)) return;

        has_dropped = 0;
	for (i = 0; i < sizeof(autoload); i++)
        {
	        if (! autoload[i] || autoload[i] == "")
                        continue;

		if (sscanf(autoload[i], "%s:%s", file, param) != 2)
                {
			file = autoload[i];
			param = 0;
		}
		if (file_size(file + ".c") > 0)
		{
                	err = catch(call_other(file, "???"));
                	ob = find_object(file);
		} else
		{
			err = 0;
			ob = 0;
		}
                if (ob && ! ob->is_no_clone()) ob = new(file);
		if (err || ! ob || ob->is_no_clone() && environment(ob))
                {
                        string temp;
                        if (file && sscanf(file, "/data/%*s/%s", temp))
                        {
                                if (has_dropped) continue;
                                has_dropped++;
                                write("你发现有些东西已经没有用了，随手就扔掉了。\n");
                        } else
			        write("你觉得似乎失落了什么重要的东西，最好通知一下巫师。\n");
			log_file("autoload", sprintf("Fail to autoload %s of %s, error %s(%s)\n",
				 file, this_object()->query("name"),
			         this_object()->query("id"),
                                 ob ? "The no clone object has existed" : err));
			continue;
		}
                if (ob->is_no_clone() && ob->is_not_belong_me(this_object()))
                {
                        if (! environment(ob)) destruct(ob);
                        continue;
                }

		export_uid(ob);
                if (! ob->is_character())
		        ob->move(this_object(), 1);

		ob->autoload(param, this_object());
	}
	
	clean_up_autoload();		// To save memory.
	
}



// 这里照搬dtxy

void save_newitem()
{
	object *inv;
	int i, j,k,param,loop;
	mixed *klist;
	mapping list;
	string filename;


        if( !userp(this_object()) ) return;
	newitem=allocate_mapping(1000); //先预定义为1000的大小
	inv = all_inventory();
	k=0;
	for(i=0; i<sizeof(inv); i++)
	{
	  if (is_save(inv[i]))
	  {
	   
		param=inv[i]->query_amount();
		filename = base_name(inv[i])+".c";
		if( param > 0 ) {
			filename += "=" + param;
			newitem +=(["Object"+k:filename]);
		 	k++;
		 	continue;
		} //可重叠物品只保存文件和数量
        else newitem +=(["Object"+k:filename]);
        
//        if ((int)inv[i]->query("changed")<1) {k++;continue;}//未经修改的物品只保存文件名
		list = (mapping)inv[i]->query_entire_dbase();//读出物品的dbase
		klist = keys(list);//关键字列表
		klist = sort_array(klist, "sort_keys", this_object());
		for(loop=0; loop<sizeof(klist); loop++)
		newitem["Object"+k+"_"+klist[loop]]=list[ klist[loop]];
		newitem["Object"+k+"_id"]=inv[i]->parse_command_id_list();
		k++;
	}
	else continue;  //只保存指定的物品	
		
	}
}

void restore_newitem()
{
	int i,j;
	object ob;
	string file, param, err,*key,a;
	mixed val;
	
	
	if( !mapp(newitem) ) {return;}
	
	i=0;
	while(newitem["Object"+i])//查找物品，当"Object(0~i)"存在时执行
	{
		a="Object"+i;
		if( sscanf(newitem[a], "%s=%s", file, param)!=2 ) 
		{
			file = newitem[a];
			param = "";
		}
		err = catch(ob = new(file));
		if( err || !ob  ) 
		{
		    //mon 1/20/98
		  	write("你觉得似乎失落了什么重要的东西，最好通知一下巫师。\n");
		  	log_file("AUTOLOAD", sprintf(
		    	"Fail to autoload %s of %s, error %s on %s\n",
		    	file, this_object()->query("id"), err, ctime(time())));
	 	  	i+=1;continue;
		}
		export_uid(ob);
		ob->move(this_object());
		
		if( sscanf(param, "%d", param)==1 )	ob->set_amount(param);
        //给物品set属性
 		key=keys(newitem);
   		key = sort_array(key, "sort_keys", this_object());
   		if (member_array(a+"_changed",key) == -1) {i++;continue;}
   		if (!newitem[a+"_changed"]) {i++;continue;}
		for(j=0; j<sizeof(key); j++)
		{
			if( sscanf(key[j],a+"_%s", file)==1 ) 
			{
				if (file!="equipped" && file!="id") ob->set(file,newitem[key[j]]);
				if (file=="id") ob->set_name(ob->query("name"),newitem[key[j]]);

			}
		}
		i=i+1;
	}
	
	clean_up_newitem();		// To save memory.
}



string *query_autoload_info()
{
        return autoload;
}

void set_autoload_info(string *data)
{
        autoload = data;
}

// 华夏更名者
// laoren.c
// By Dumbness, 2003-4-29 13:40

inherit NPC;

int check_legal_name(string arg, int maxlen);

void create()
{
        set_name("无名老人", ({ "laoren" }));
        set("shen_type", 1);

        set("str", 50);
        set("gender", "男性");
        set("age", 35);
        set("long","苏州城外的无名老人，传闻其人慧达天庭，妙算玄机，只可惜多泄天机，终遭天谴。\n老人此刻面泛紫金，浮肿不堪，显是痛苦异常。\n");
        set("combat_exp", 1500);
        set("attitude", "friendly");
        set("inquiry", ([
                "改名" : "这个……，名者，命也！逆天改命，必遭天谴，若无黄金万两，免开尊口。",
        ]));
        
        setup();
        carry_object("/clone/cloth/cloth")->wear(); 
}

void init()
{
        object ob;
        
        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }

        add_action("do_name","改");
}

void greeting(object ob)
{
        if (!ob || environment(ob) != environment())
                return;
        switch(random(2)) {
        case 0 :
                say("无名老人痛苦的呻吟着，你突然发现他那本混浊的眼睛中突然精光一闪。\n");
                break;
        case 1 :
                say("无名老人说道：唉！这位" + RANK_D->query_respect(ob) + 
                        "又是来逼我逆天改命的吗？\n");
                break;
        }
}

int accept_object(object who, object ob)
{
        
        if (wizardp(who) || ((ob->query("money_id") && ob->value() >= 100000000)) )
        {
                who->set_temp("fee_paid",1);
                tell_object(who, "无名老人叹了一口气说道：逆天行事，必遭天谴。你可考虑清楚了。告诉老夫你想取个什么样的新名字。\n");
                tell_object(who, "请键入：改 新的中文名字。\n");
                return 1;
        }
        else if (ob->query("money_id") && ob->value() < 100000000) 
        {
                tell_object(who, "无名老人嘿嘿一笑，说道：“多谢这位" + RANK_D->query_respect(ob) +"给我这麽多钱。老夫时日无多，\n");
                tell_object(who, "纵有倾国之富又如何。”\n");
                return 1;
        }
        return 0;
}

int do_name(string target)
{
        object me;
        string old_name,old_purename;
        string fname;
        string result;

        me = this_player();
        old_name = me->name(1);
        old_purename = me->query("purename");

        if( !me->query_temp("fee_paid") ) 
                return notify_fail("无名老人冷冷的看了你一眼，满脸不屑的表情。\n");

        if( !target ) 
                return notify_fail("无名老人迷惑不解地说道：快告诉我您新的名字呀！\n");

        if( old_purename == target )
                return notify_fail("无名老人奇怪地对你说到：您的钱是不是来得太容易了！\n");

        if (! check_legal_name(target, 4))
                return 1;
                
        fname = me->query("surname");
        if (! stringp(fname)) fname = "";
        fname += target;

        result = NAME_D->change_name(me, fname, 0);
        if (stringp(result))
        {
                me->add_temp("fake_name", 1);
                if (me->query_temp("fake_name") > 50)
                {
                        me->delete_temp("fake_name");
                        me->delete_temp("fee_paid");
                        write("无名老人恶狠狠的盯着你：“消遣老夫来了。”");
                        return 1;
                }
                write(result + "\n");
                write("请重新改名吧。\n");
                return 1;
        }
        me->set("purename", target);
        CHANNEL_D->do_channel(this_object(),"rumor",old_name + "从现在开始改名为" + me->name(1) + " 了。");
        log_file("static/changename",sprintf("%s(%s)于%s改名为%s。\n",
                                              old_name,
                                              me->query("id"),
                                              log_time(),
                                              me->name(1)));
        me->delete_temp("fake_name");
        me->delete_temp("fee_paid");

        return 1;
}

int check_legal_name(string name, int maxlen)
{
        int i;
        string *banned_name = ({
            "你", "您", "我", "他", "她", "它", 
            "巫师","天神","胡云","鱼儿","小鱼","江湖", "洛神", "魅影",
            "系统","核心","上帝","菩萨","佛祖","祖宗","皇帝",
            "爸","爸爸","他爸","她爸","它爸","爹","爹爹","他爹","她爹","它爹","老爸",
            "妈","妈妈","他妈","她妈","它妈","娘","他娘","她娘","它娘","老娘",
            "爷","爷爷","他爷","她爷","它爷","老子","大爷",
            "　","奶","奶奶","他奶","她奶","它奶",
            "屎","尿","粪","床","贱",
        });
        
        i = strlen(name);

        if ((strlen(name) < 2) || (strlen(name) > maxlen))
        {
                write("对不起，你的中文姓名不能太长或太短。\n");
                return 0;
        }

        if (! is_chinese(name))
        {
                write("对不起，请您用「中文」取名字。\n");
                return 0;
        }

        if (member_array(name, banned_name) != -1)
        {
                write("对不起，这种姓名会造成其他人的困扰。\n");
                return 0;
        }

        return 1;
}


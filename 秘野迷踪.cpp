#include<bits/stdc++.h>
#include<sstream>
#include<windows.h>
#include<conio.h>
using namespace std;
/*未经wqx同意禁止转载 
一、单位制度
	物理量名  游戏名称       实际大小
	时间      毫秒           1ms 
	长度      格             1格=2个字符
	温度      degree         1 degree=1摄氏度 
二、BUG记录 
	1、地图左边缘墙生成错误
	    1）制造、出现时间：2022.1
	    2）出现条件
	    	(1)地图总长16~17个房间，房间长5格
	    3）表现外观
	        (1)墙体显示为其他字符（全黑/门/生物/（错误的）出口）
		    (2)出错处数据记录有误 
		4）消灭时间：2022.7.14前 
	2、出口标牌输出错误
		1）制造、出现时间：2022.6.27
		2）出现条件：输出出口标牌时（char(24~27) 
		3）表现外观
			(1)程序卡死 
		4）消灭时间：2022.7.10
		   方法：换为中文字符 
	3、钥匙门开关状态错误
		1）制造时间：2022.8
		2）出现时间：2022.9
		3）出现条件：多次游戏
		4）出现原因：初始化时围绕房间生成门（doors_around_rooms）的函数没有设置门为未开启，此次游戏中打开的门再次
			游戏时开关状态会仍是开启，即同一个位置的门保持开启，可以多次累加 
		5）消灭时间：2022.9.30 
三、游戏地图
	1、概念界定
		1）格：一个位置或其长度/宽度 
		2）格点：一个位置/格（正方形）的顶点，每格与四个格点相邻，一格的左下角格点（打印显示为左上）坐标设为此格
			坐标(x,y)，左上角(x,y+1)，右下角(x+1,y)，右上角(x+1,y+1)
		3）边缘墙：满足x==1||x==length||y==1||y==width的位置的集合
		4）矩形：排成长方形的一些位置的集合 
		5）房间：存在于一个不包含墙的长宽都≥2的矩形的一些位置的集合 
	2、大小
		长length格，宽width格，高height*2层（x，y，z都从1开始编号）
		1~height层为一般游戏区，height+1~height*2层为扩展虫巢区（详见【虫子巢穴】） 
四、门与钥匙
	1、门
		1）种数：4种
		2）生成
			(1)随机（普通、越远越多）
			(2)围绕房间生成 
	2、钥匙
		1）种数：4种（对应门） 
		2）生成
			(1)随机（普通、越远越少）
			(2)房间内生成
			(3)根据门生成
				[1]模式：确保打开每扇门的钥匙都能在不打开这扇门的情况下取到
				[2]实现方法
					①准备
						BFS二件套：Q、vst
						vector<position_3D> vspace已访问、没有物品的空地	
						vector<position_3D> vdoor[4]已访问、未放对应钥匙的门（四种分别记录） 
						vector<position_3D> vkind可以选择的门的种类 
					②初始化：
						a.全部清空
						b.把玩家坐标作为起点 
					③重复执行： 
						a.BFS遍历（打开已访问、已放对应钥匙的门）能到的地方，
						更新vspace，过程中碰到未访问的门都加入vdoor
						b.为下次循环准备 
							把4种门中数量不为0、不比空地多的种类加入vkind 
							至少有一种门可以选： 
								在vkind中随机取出一种门，把这种门全部加入Q并去掉，
								在vspace中随机取出这种门数量的空地放置对应的一种钥匙
						 	否则退出循环 
					注意：所有BFS遍历不会重复访问已访问过的地方（之前循环的也不会）！  
五、玩家
	1、移动
		1）方向操控
			方向键 对应数字 坐标变化
			上     0        (x,y-1,z) 
			右     1        (x+1,y,z)
			下     2        (x,y+1,z)
			左     3        (x-1,y,z)
			【移动】模式下改变位置，【改变朝向】模式下仅改变方向 
		2）碰撞检测
		   格式：（碰到……（如果……（且/或……）就……（，然后……）（否则……（，然后……））） 
			(1)碰到墙就停下
			(2)碰到门如果有对应钥匙就进门否则停下 
		3）特殊移动
			(1)手动上下楼：按下空格键就上/下楼 自动上下楼：碰到楼梯就上/下楼
			(2)碰到电梯就跳出选楼层界面，然后移动到对应楼层
	2、侦测物品
		物品名    捡拾    使用（键1：使用1，键2：使用2，……）    特殊效果（键1：效果1，键2：效果2，……）
		钥匙      自动    自动                                    开对应门
		出口标牌  无      无                                      指向到达出口的最近路线的方向
		镜子      无      无                                      反射光线，使玩家能看到更远的地方 
	3、视野计算
		1）规则：遇到楼梯上/下楼，碰到镜子拐弯（或许还要限定最远距离？）
			墙看到表面一层，除此以外都能看穿（也许物品会阻挡视线？）
		2）准备
			int game_map[][][].in_player_sight玩家最后一次看到这个位置的时间，记为游戏地图 
			queue<position_3D> pos_in_sight现在要在屏幕上新显示的位置，记为队1 
			queue<position_2D> pos_lst_sight上次在屏幕上显示的位置（scr），记为队2
			queue<position_2D> pos_backup位置（scr）备份，为下回合的队2做准备，记为队3 
			string screen_display_coding(position_3D pos)屏幕输出编码 
			map<position_2D,string> screen_pos屏幕上的位置显示内容的编码（就用screen_display_coding） 
			map<position_2D,int> screen_z屏幕上现在需要显示的位置所处的楼层（z坐标） 
			position_3Dtoscr、position_scrto3D等各种坐标的转换函数 
			(1)初始化（all_assigned）：每次游戏开始时清空一下上面那些东西（screen_z每回合都要） 
			(2)标记已看到：
			 	[1]已经标记过游戏地图至[3]
				[2]标记游戏地图，入队1，标记screen_z，结束 
				[3]此位置是玩家位置：标记screen_z，结束 
		3）方法
			(1)十字形
				[1]简介：十字形视角（前后左右）+两侧可视范围优化 
				[2]优点：实现简单 缺点：走廊里完全够用，房间里不能看到全部范围 
			    [3]实现方法
					①先把玩家所在的位置入队1，标记一下游戏地图
					②向4个方向计算视野，入队1，标记一下游戏地图
						如果这个位置视线可以穿过，就把它两侧的位置入队1，标记已看到
						否则看两侧位置在与现在玩家视线方向相反的方向上的前一个位置，
						如果前一个位置视线可以穿过，就把它对应侧的位置入队1，标记已看到 
			(1)拟真形
				[1]简介：以玩家位置为起点进行BFS搜索，碰到墙就记录它遮挡的视线范围（坐标系方向角，以玩家位置的四格点
					为原点），不访问被完全遮挡的位置，直到所有视线范围均被遮挡
				[2]优点：更为真实的计算了视野，实现相对容易 
				   缺点：时间复杂度稍高，有精度误差（至少13格外才会产生），且暂无处理镜子的能力 
				[3]准备
					bool occlusion[4][360]记录玩家位置4个格点上被遮挡的视线方位角，0：未遮挡，1：被遮挡
					int cnt_occlusion[4]记录玩家位置4个格点上未被遮挡的视线方位角还剩几个，即occlusion[0~3]中0个数 
					int calc_angle(position_3D p)计算p相对玩家位置的方位角（0~360°） 
					bool invisible(position_3D p)返回p是否看不到 
					void mark_occlusion(position_3D p)标记p遮挡的角度范围
					queue<position_3D> visible_stair所有能看到的楼梯的位置 
					BFS二件套：Q、vst
					局部位置变量：u、v、v2 
					初始化（assigned）：每次计算前occlusion清零，cnt_occlusion[0~3]都设为360 
					方位角枚举方法（逆时针，最大359°）：for(int i=最小角度;i!=(最大角度+1)%360;i=(i+1)%360)
				[4]实现方法（player_calculate_vision2(position_3D pos=player1.pos)）
					①玩家坐标入队并标记vst
					②队列为空或cnt_occlusion[0~3]都为0至⑨，否则取出队首u  
					③不能扩展至②，否则扩展到v
					④v超出地图范围至③ 
					⑤看不到v（invisible(v)）就标记vst，至③
					⑥v是墙：标记occlusion（mark_occlusion(v)）
					⑦v入队并标记vst，在游戏地图中标记，至⑧ 
					⑧v是楼梯：把它通往的位置v2入队visible_stair；至③ 
					⑨玩家想看到楼上/下：枚举visible_stair中每个位置u，
					occlusion清零，cnt_occlusion[0~3]都设为360， 
					标记玩家通过此楼梯看到的方位角范围为可见（mark_occlusion()，改变cnt_occlusion，同时取反occlusion）， 
					调用player_calculate_vision2(u) 
		4）屏幕更新（screen_update）时
			(1)清理队2
				[1]取出队首spos 
				[2]根据spos和screen_z求出屏幕现在这个位置要打印游戏地图上哪个位置（now_pos） 
					screen_z没有屏幕这个位置的信息：把这个位置涂黑，更新screen_pos，886 
				[3]判断 
					这里now_pos的显示内容编码和现在屏幕上（未更新）的显示内容编码不同：
						重新输出now_pos（print_game_map_pos(now_pos)），更新screen_pos
					d.now_pos加入队3
			(2)处理队1
				[1]取出队首now_pos
				[2]输出（print_game_map_pos(now_pos)）
				[3]position_3Dtoscr(now_pos)加入队3 
			(3)队3的内容全部移到队2 
	4、生命体征
		1、生命值
			(1)初始：100%
			(2)减至0玩家死亡，游戏失败
		2、体力值
			(1)初始：100%
			(2)玩家移动时减少1点，否则<100%就每0.5秒回复1点
	5、食物 
		等级\效果  体力恢复ADDL  生命回复ADDS （恢复无上限） 
		1          +40%          +20%
		2          +20%          +10%
		3		   +10%          +5%
	6、武器
		1、武器能量/耐久度 
			(1)生成方法：随机生成、离玩家越远越少/多、离出口越远越少/多 
		2、种类
			(1)激光枪
				[1]使用：【奔跑】/【行走】模式下，按s键，消耗1点武器能量，向玩家朝向发出红色激光束，持续0.5秒，
					下次使用需等待这次使用完成，并冷却0.1秒 
				[2]特点：发射瞬间命中目标，碰到墙或锁上的门就中断，碰到镜子就反射，两者都会产生红色亮光，消灭敌人有红色“KO”效果
				[3]特殊效果：点燃TNT、蜡烛等 
			(2)飞镖 
				[1]使用：【奔跑】/【行走】模式下，按s键，消耗数量1，向玩家朝向扔出飞镖，速度7m/s，
					下次使用需等待0.2秒 
				[2]特点：速度较高，可回收，碰到墙或锁上的门就停止飞行，变成可捡拾的物品，消灭敌人有红色“KO”效果
				[3]特殊效果：暂无 
			(3)矛
				[1]使用：【奔跑】/【行走】模式下，每次移动/改变方向，向玩家朝向刺出长度为2的矛，保持不变直到下次，
					碰到敌人耐久度减少（与敌人速度有关） 
				[2]特点：瞬间命中目标，被击中者无法移动和攻击，碰到墙或锁上的门就停下，消灭敌人有红色“KO”效果
				[3]特殊效果：暂无 
六、距离
	1、直线距离（两点间的距离公式）
	2、曼哈顿距离（MHT_DIST）
	3、步行/搜索距离（生物从一点走到另一点的步数）
七、屏幕
	1、分区（左中右，三分天下） 
		1）玩家信息栏[0,0]->[46,48] 47*49 
		2）游戏地图区[46,0]->[142,48] 97*49
		3）玩家物品栏[142,0]->[188,48] 47*49 
			(1)格式
				[1]表格
					左上角："物品栏"
					行标签：数量、耐久、增益、使用指南等
					列标签：物品名+显示图像 
				[2]MC风格 
					第1~2行："持有物品：     数量：   耐久：   " 
					第2行："使用方法："
					第3行：所有物品的图像（按加入顺序排序） 
			(2)使用
				[1]按f键查找物品/选中物品并退出
				[2]查找物品时使用方向键选择
八、计时器、标志 
	1、准备
		map<string,int> game_timer记录未来某个事件发生时的游戏时间
		map<string,bool> game_flag记录某个事件是否发生 
	2、使用
	e.g.game_timer["玩家移动"]=game_time+1000;玩家体力值player1.vts.stg.strength_value在下一秒（1000ms）回复+1
		game_flag["清除尸体"]=true;有尸体被清理，更新屏幕 
		屏幕擦去“KO”字样 
		1秒后…… 
		if(game_timer["pvsr"]<=game_time&&……) player1.vts.stg.strength_value++;玩家体力值回复+1
九、敌人
	1、区域更新（减小计算量）
		1）初始化：队列队列（Qbug/Qghost）为空
		2）每次玩家视野计算将能看到且不在队列的敌人加入队列，并设置敌人为更新状态（.update=true） 
		3）每次更新敌人时，离玩家距离>50且玩家不能看到，这个敌人就出队，停止更新（.update=false）
			若敌人移动时碰到不更新的敌人，把它加入队列，并设置这个敌人为更新状态（.update=true） 
	2、虫子
		1）生成
			(1)位置：巢穴，一开始在随机位置 
			(2)游戏中随机频率新生成 
		2）移动
			(1)方向：初始随机，碰到墙或其它生物就转弯（会消耗时间），碰到楼梯如果楼上/下没有其他生物就上下楼，碰到巢穴就进入 
			(2)速度：1~10格/1000毫秒（生成时确定）
		3）攻击
			(1)方式：碰撞
			(2)伤害：1~20滴血（与速度有关）  
		4）血量：1点
			(1)对玩家造成伤害+1  (2)被激光/飞镖/矛击中-1
			(3)血量=0时死亡，重生至巢穴内部随机位置（没有空位就等着） 
	3、虫子巢穴
		1）生成：巢穴口位于距离玩家一定距离外的空地，离出口越近越多，同时在巢穴内部地图生成同一位置的巢穴口并对应 
		2）巢穴口血量：3点
		被激光击中-1，血量=0时被摧毁并消失，不能再作为巢穴口
		3）虫子/玩家进入可传送至巢穴内部地图 
		4）存储：game_map[1~length][1~width][height+1~height+height].items.nst 
		5）陈设：只有空地和墙，没有任何物品 
	4、鬼
		1）生成
			(1)位置：一开始在随机位置 
			(2)游戏中随机频率新生成 
		2）移动
			(1)速度：1~10格/1000毫秒（生成时确定）
			(2)分情况：
				[1]能看到玩家：若路线存储器为空，计算出最短路径并更改存储器； 
					若不为空，按照路线移动。 
				[2]听到玩家声音：向声音来源移动 
				[3]发现玩家足迹：跟着足迹方向移动 
				[4]随机模式：随机概率转弯（不消耗时间），碰到楼梯如果楼上/下没有其他生物就随机概率上下楼，碰到巢穴就随机概率进入 
		3）攻击
			(1)方式：碰撞
			(2)伤害：1~20滴血（与速度有关）  
		4）血量：5点
			(1)对玩家造成伤害+1  (2)被激光/飞镖击中-1
			(3)血量=0时死亡，重生至巢穴内部随机位置（没有空位就等着）
*/
#define PRESS_KEY_UP 72
#define PRESS_KEY_DOWN 80
#define PRESS_KEY_LEFT 75
#define PRESS_KEY_RIGHT 77
#define PRESS_KEY_ENTER 13
#define PRESS_KEY_SPACE 32
#define PRESS_KEY_E 101
#define PRESS_KEY_F 102
#define PRESS_KEY_G 103
#define PRESS_KEY_S 115 
#define PRESS_KEY_V 118
typedef long long ll;
HANDLE hout;//句柄（字体颜色专用） 
const int SMALLEST_TIME=10;//游戏时间最小单位：10毫秒
const int MAX_SCREEN_LENGTH=189,MAX_SCREEN_WIDTH=49;//ConsolePauser的最大长宽高
const int MAX_LENGTH=500,MAX_WIDTH=500,MAX_HEIGHT=10;//游戏地图的最大长宽高 
const int KINDS_OF_DOORS=4,KINDS_OF_KEYS=4;//门、钥匙的种类数量：4
const int KINDS_OF_FOOD=2,EFFECT_OF_FOOD=3;//食物的种类数：2；效果等级数：3 
const int MAX_PLAYER_SPEED=2000;//玩家的最大速度 
const int MAX_SIZE_OF_ITEM_LAB=20;//玩家物品栏的最大容量
const int MAX_BUG_NUM=100000,MAX_GHOST_NUM=10000;//虫子、鬼的最大数量 
const int INF=2e9;//游戏最大数字∞ 
const double PI=acos(-1);//Π 
bool game_pause=false,game_end=false,game_success=false,start_again=false;//是否暂停/结束游戏、成功逃脱、重新开始
int game_time,start_time;//游戏（进行、开始）时间
int lst_see_time;//上次重新计算玩家视野的时间 
void gotoxy(int x=0,int y=0); 
enum MAZE{//迷宫的墙壁、门、通道等 
	WALL,SPACE,EXIT,DOOR1,DOOR2,DOOR3,DOOR4,UPSTAIR,DOWNSTAIR,NEST,DOORS,STAIRS//前两个位置不准改 
};
enum FLOOR{//地板状况 
	NORMAL,HOLE
}; 
enum PLAYER_ENEMY{//玩家和敌人 
	NOBODY,PLAYER,BUG,GHOST
};
enum ALL_ITEM{//所有物品
	K1=1,K2,K3,K4,AS1,AS2,AS3,AL1,AL2,AL3,BX,BL,TT,CE//取首字符和尾字符 
};
enum KEY{//钥匙 
	KEY1=1,KEY2,KEY3,KEY4
};
enum FOOD_KIND{//食物
	ADDS=1,ADDL//体力恢复和生命恢复 
};
enum CHANGING_SOLID{//变化的固体 
	BOX=1,BARREL,TNT,CANDLE
};
enum LIQUID{//液体 
	WATER=1,MAGMA
};
enum WEAPON{//武器（这个改了记得去 wcnt 更新一下！） 
	LSG,DART,SPR
};
enum DIRECTION_KEY{//方向键
	STOP=0,
	UP,DOWN,LEFT,RIGHT
};
enum CHANGE_DIRECTION{//改变方向
	TURN_RIGHT,TURN_BACK,TURN_LEFT 
};
enum ACTION_KIND{//玩家的操作类型 
	RUN,WALK,CHOOSE_ITEM,CHANGE_WPN 
};
int length,width,height;//游戏地图长宽高 
int cnt_notWALL,cnt_SPACE,cnt_STAIRS;//计数 
struct position_2D{//坐标结构体（xOy） 
	int x,y;//x坐标和y坐标 
	bool operator<(position_2D a)const{//重载< 
		return x<a.x||(x==a.x&&y<a.y);
	}
	bool operator==(position_2D a)const{//重载== 
		return x==a.x&&y==a.y;	
	}
	void output1(bool enter=0){//打印坐标 
		cout<<"("<<x<<","<<y<<")";
		if(enter) cout<<endl;
	}
};
struct position_3D{//坐标结构体（xOyOz） 
	int x,y,z;//x坐标、y坐标和z坐标 
	void init(){
		x=y=z=0;
	}
	bool operator==(position_3D a)const{//重载== 
		return x==a.x&&y==a.y&&z==a.z;	
	}
	bool operator!=(position_3D a)const{//重载!=
		return x!=a.x||y!=a.y||z!=a.z;	
	}
	bool operator<(position_3D a)const{//重载<
		if(x!=a.x) return x<a.x;
		if(y!=a.y) return y<a.y;
		return z<a.z;	
	}
	void output1(bool enter=0){//打印坐标 
		cout<<"("<<x<<","<<y<<","<<z<<")";
		if(enter) cout<<endl;
	}
};
		struct pheromone{//虫子的信息素 
			int disapp,id,d;//信息素消失的时间、谁留下的、指向 
			void init(){
				disapp=d=0;id=-1;
			}
		};
	struct enemy{//敌人
		int id;//敌人的编号 
		bool dead;//生物是死是活 
		int body_disapp;//尸体消失的时间 
		pheromone phm;//信息素
		void init(){
			id=-1;dead=false;body_disapp=0;
			phm.init();
		}
	};
		struct exit_sign{//出口标牌结构体
			bool exist;//有没有出口标牌 
			int dir;//出口标牌指示的出口方向
			void init(){
				exist=dir=0;
			}
		};
		struct mirror{//镜子结构体
			bool exist;//有没有镜子 
			int dir,side;//镜子的方向和面数
			/*      0	1	2	3
			1side  ◤  ◥  ◢  ◣
			2side 	╱	╲  
			*/
			void init(){
				exist=dir=side=0;
			}
		};
		struct food{//食物结构体
			bool exist;//有没有食物 
			int kind,effect;//kind:0,ADDS,ADDL effect:1,2,3
			void init(){
				exist=kind=effect=0;
			}
		};
		struct laser{//激光束结构体
			bool exist;//有没有激光束 
			int laser_beam;//激光束的形式（0~3：各个方向—｜　4：命中目标※） 
			void init(){
				exist=laser_beam=0;
			}
		};
		struct weapon_energy_edc{//武器能量/耐久度回复
			bool exist;
			int num,kind;//哪种武器的能量/耐久度回复（0：激光枪 1：矛）
			void init(){
				exist=num=kind=0;
			}
		};
		struct dart{//飞镖结构体
			bool exist(){//有没有飞镖
				return num[0]>0||num[1]>0;
			}
			bool exist0(){//有没有地上的飞镖
				return num[0]>0;
			}
			bool exist1(){//有没有飞行的飞镖
				return num[1]>0;
			}
			int d[2],num[2];//0：（显示时用）地上 /1：（给敌人用）飞行中  的飞镖的方向、数量 
			void init(){
				d[0]=d[1]=num[0]=num[1]=0;
			} 
			int prd(){//显示时的方向（调用时需保证exist()==true） 
				if(num[1]) return d[1];
				return d[0];
			}
		}; 
		struct spear{//矛结构体
			bool exist;//有没有矛
			int d;//矛的方向
			bool head;//矛头 
			void init(){
				exist=d=head=0;
			} 
		};
		struct nest{//虫子的巢穴口
			bool exist;//有没有巢穴口 
			int id;//编号
			position_3D to;//对应的巢穴口位置（注意：可能是进去也可能是出来） 
			void init(){
				exist=0;id=-1;to.init();
			} 
		};
		struct footprint{//足迹结构体
			bool exist(){//有没有足迹
				return d!=-1;
			}
			int d;//玩家足迹方向（4：上/下楼） 
			void init(){
				d=-1;
			}
		};
	struct thing{
		int key;//0,KEY1,KEY2,KEY3,KEY4
		exit_sign exit_signs;
		mirror mirrors; 
		food foods;
		weapon_energy_edc wee;
		nest nst;  
		laser lsr;
		dart drt;
		spear spr;
		footprint fpt;//不加入存在物品判断 
		int medicine;//药品的种类（0：没有） 
		bool treasure,lamp;//有没有宝箱或灯
		int changing_solid;//0,BOX,BARREL,TNT,CANDLE
		int liquid;//0,WATER,MAGMA
		void init(){
			key=medicine=treasure=lamp=changing_solid=liquid=0;
			exit_signs.init();mirrors.init();foods.init();wee.init();nst.init();lsr.init();drt.init();spr.init();fpt.init();
		}
		bool nothing(){//表示这里是否没有东西 
			return !(key||exit_signs.exist||mirrors.exist||foods.exist||wee.exist||nst.exist||lsr.exist||drt.exist()||spr.exist||medicine||treasure||lamp||changing_solid||liquid); 
		}
	};
struct MAP{
	int maze;//WALL,SPACE,EXIT,DOOR1,DOOR2,DOOR3,DOOR4,UPSTAIR,DOWNSTAIR,LIFT
	bool door_state;//true：开，false：关（只是给钥匙门记录） 
	int floor;//NORMAL,HOLE 
	int player_enemy;//NOBODY,PLAYER,BUG,GHOST
	enemy emy;//敌人信息 
	thing things;//物品 
	int in_player_sight;//玩家最后一次看到这个位置的时间（=game_time：玩家现在看得到，≠game_time：玩家现在看不到）
}game_map[MAX_LENGTH+1][MAX_WIDTH+1][MAX_HEIGHT*2+1];
struct direction{//方向结构体 
	int d1,d2;//d1（前后）偏d2（左右）方向 
};
	struct velocity{//速度共用体（v）
		double speed;//单位：格/1000毫秒（不得为0！）
		int wait_time;//走1格停多少毫秒（不得为0！）
		void tv(){//wait_time->speed
			speed=double(1000)/wait_time;
		}
		void vt(){//speed->wait_time
			if(speed>0.1) wait_time=1000/speed+0.5;//四舍五入 
			else wait_time=10000;//speed小到一定程度就默认为0.1 
			if(wait_time<=0) wait_time=1;//防止出错 
		}
	};
		struct life_injury{//生命和受伤结构体
			int change;//下面这个变了没有（1：增加 2：减少） 
			/*    0    1    2        3        4
			虫子 不变 增加 激光命中 其他武器 ... 
			*/
			int life;//生命值（0%~100%，%省略）
			int hurt,recovery;//受伤值、回复值 
			void init(int lf){//初始化 
				life=lf;hurt=recovery=change=0;
			}
		};
		struct strength{//体力结构体
			bool change;//下面这个变了没有 
			double physical_strength;//体力值（0%~100%，%省略）
			int recovery_time;//恢复时间 
			void init(){//初始化 
				physical_strength=100;change=1;recovery_time=400;
			}
		};
	struct vital_signs{//生命体征结构体 
		life_injury lfin;//生命和受伤
		strength stg;//体力 
		void init(){//初始化 
			lfin.init(100);stg.init(); 
		}
	};
	struct score{//分数（泛指游戏结束时评级要用的指标） 
		int time_spent;//逃出花费的时间 
		bool kc_change;//击杀数是否变化 
		int kill_count,shoot_times,shoot_hit_times;//击杀数、使用射击类武器次数，命中敌人次数 
		double hit_rate;//命中率 
		int hurt_times;//遭受攻击次数 
		void init(){//初始化 
			time_spent=kill_count=shoot_times=shoot_hit_times=hit_rate=hurt_times=0;
			kc_change=false;
		}
	};
		struct key{//钥匙结构体
			int door_keys[KINDS_OF_KEYS];//存储不同种类的钥匙
			int treasure_keys;//用来开宝箱的钥匙
			void init(){//初始化 
				memset(door_keys,0,sizeof(door_keys));
				treasure_keys=0;
			} 
		};
		struct stored_food{//玩家存储的食物结构体
			int food_cnt[KINDS_OF_FOOD][EFFECT_OF_FOOD];//存储不同效果的食物 
			void init(){//初始化 
				memset(food_cnt,0,sizeof(food_cnt));
			} 
		};
			struct laser_gun{
				int energy,last_time,cool_time;//激光枪能量、持续时间、冷却时间 
				bool en_change;//上面这个变了没有
				int kind,kd_cnt;//模式、模式总数 
				bool kd_change;//上面这个变了没有
				int kd_energy[5];//模式对应的能量消耗 
				string kname[5];//模式名
				void init(){
				 	energy=en_change=kind=0;last_time=500;cool_time=200;
				 	kd_cnt=5;
				 	kd_energy[0]=1;kd_energy[1]=3;kd_energy[2]=3;kd_energy[3]=4;kd_energy[4]=8;
				 	kname[0]="正常";kname[1]="三联";kname[2]="三向";kname[3]="四处扫射";kname[4]="八面开花";
				}
			};
			struct holding_spear{//手持矛
				int endurance;//耐久度 
				void init(){
					endurance=100;
				}
			};
			struct throwing_dart{//飞镖
				int num;//数量 
				void init(){
					num=0;
				}
			};
		struct weapon{//武器
			int select_wpn,wcnt;//选择的武器，总武器数 
			//LSG,DART,SPR 
			bool sw_change;//上面这个变了没有
			laser_gun lsg;
			throwing_dart drt;
			holding_spear hsr; 
			bool data_change,mode_change;//以上武器的参数信息/模式变了没有 
			void init(){
				select_wpn=LSG;wcnt=3;sw_change=data_change=mode_change=0; 
				lsg.init();drt.init();hsr.init();
			}
			void print1();//打印选择的武器名和参数信息（能量、耐久等） 
			void print2();//打印武器模式
			void print3();//打印使用说明 
		};
	struct item{//物品结构体 
		key keys;//钥匙 
		stored_food foods;//食物 
		bool num_change;//物品数量是否变化 
		int select_number;//选中的物品在物品栏里的编号
		bool sn_change;//上面这个变了没有  
		vector<int> item_lab;//物品栏（物品编码） 
		bool il_change;//上面这个变了没有 
		weapon wpn;//武器 
		void init(){//初始化 
			keys.init();
			foods.init();
			wpn.init();
			num_change=0; 
			select_number=0;sn_change=il_change=0;
			item_lab.clear();
		}
		string item_name();//物品名字 
		int item_num();//物品数量 
		int item_endurance();//物品耐久 
		string item_method();//物品使用方法 
		void print_item(int k);//根据物品的编码打印物品 
		void print1();//打印物品栏选中的物品信息 
		void print2();//打印物品栏里的所有物品
		void print3();//给选中物体标记位置
	};
struct player{//玩家 
	position_3D pos;//坐标
	int d,color;//方向，如何显示（0：正常蓝 1：补血绿 2：受伤红 3：变方向↑↓←→） 
	vital_signs vts;//生命体征 
	score scr;//分数 
	velocity vlc;//速度 
	item items;//物品
	string name;//名字 
	void init();//初始化 
	/*以下为标志变量*/
	bool d_change,move;//方向是否改变，是否改变了位置
	bool up_down,ud_change,lst_ud,lst_enter,enter_nest;
	//是否自动上/下楼梯或者进/出巢穴口，前面这个变了没有，上次是否自动上/下楼梯，上次是否自动进/出巢穴口
	bool flash,use_weapon,enemy_move;//是否闪烁，是否使用武器，虫子/鬼（在视野里）是否改变了位置 
	int action_kind;//玩家动作（0：奔跑 1：行走 2：选择物品 3:改变方向）
	//RUN,WALK,CHOOSE_ITEM,CHANGE_WPN
	bool ak_change;//上面这个变了没有 
}player1; 
struct pos_player_see{//玩家看得见的格子 
	position_3D pos;//坐标
};
queue<position_3D> pos_in_sight,pos_change;
//玩家现在看得见的新（屏幕上对应位置没有显示）位置、在视野内自己更新的位置 
queue<position_2D> pos_lst_sight,pos_backup;
//上次屏幕上显示的位置和备份 
map<position_2D,string> screen_pos;//屏幕上的位置显示内容的编码 
map<position_2D,int> screen_z;//屏幕上现在需要显示的位置所处的楼层（z坐标） 
struct rectangle{//矩形结构体（用于屏幕区域等） 
	position_2D upper_left,lower_right;//左上角和右下角
	void init(position_2D ul,position_2D lr){//初始化 
		upper_left=ul,lower_right=lr;
	} 
	void init(int x_1,int y_1,int x_2,int y_2){//初始化 
		upper_left=(position_2D){x_1,y_1},lower_right=(position_2D){x_2,y_2};
	}
	void output_frame(string c="*",int color=0x07,int kind=1){//输出矩形边框 
		for(int x=upper_left.x;x+c.size()-1<=lower_right.x;x+=c.size()){
			int y_1=upper_left.y,y_2=lower_right.y;
			gotoxy(x,y_1);
			SetConsoleTextAttribute(hout,color);
			cout<<c;
			gotoxy(x,y_2);
			SetConsoleTextAttribute(hout,color);
			cout<<c;
		}
		if(kind)
			for(int y=upper_left.y;y<=lower_right.y;y++){
				int x_1=upper_left.x,x_2=lower_right.x;
				gotoxy(x_1,y);
				SetConsoleTextAttribute(hout,color);
				cout<<c;
				gotoxy(x_2,y);
				SetConsoleTextAttribute(hout,color); 
				cout<<c;
			}
	}
}whole_screen,game_map_area,vital_signs_area,item_area;
//整个屏幕、游戏地图区域、玩家信息栏、玩家物品栏 
queue<position_3D> laser_beams;//激光束队列 
struct flying_dart{//飞行的飞镖
	position_3D pos;//坐标 
	int d,time;//飞镖的方向、每次飞动的时间 
	velocity vlc;//速度   
	void init(position_3D u,int dir){
		pos=u; 
		d=dir;time=game_time; 
		vlc.speed=7;vlc.vt();
	} 
}; 
queue<flying_dart> darts;//飞行中的飞镖队列
queue<position_3D> spears;//上次显示在屏幕上矛的队列 
struct bug{//虫子结构体
	position_3D pos;//坐标 
	int d;//方向 
	velocity vlc;//速度  
	life_injury lfin;//生命
	int lst_ud;//上次上下楼时间（防止卡在一对楼梯里） 
	bool change_pos;//被打死了，改变位置复活 
	bool update;//是否要更新（减小计算量） 
	int enter_nest;//上次进出巢穴口时间 
	void init(position_3D u);
};
vector<bug> bugs;//编号：0~MAX_BUG_NUM-1
queue<int> Qbug;//虫子队列（编号） 
struct bug_nest{//虫子巢穴口结构体
	position_3D pos;//坐标
	life_injury lfin;//生命
	bool destroy;//是否被摧毁 
	void init(position_3D u);
};
vector<bug_nest> bug_nests;//虫子的巢穴口
queue<int> Qbug_nest;//虫子巢穴口队列（编号） 
struct ghost{//鬼结构体 
	position_3D pos;//坐标 
	int d;//方向（4：上下楼、进出巢穴口） 
	velocity vlc;//速度  
	life_injury lfin;//生命
	bool change_pos;//被打死了，改变位置复活 
	bool update;//是否要更新（减小计算量） 
	void init(position_3D u);
};
vector<ghost> ghosts;//编号：0~MAX_GHOST_NUM-1
queue<int> Qghost;//鬼队列（编号） 
queue<position_3D> pos_dead;//尸体队列 
struct barrel{//桶结构体
	position_3D pos;//坐标 
	velocity vlc;//速度 
	bool stage;//状态（静/动） 
}; 
struct tnt{//炸弹结构体 
	position_3D pos;//坐标
	bool stage;//状态（静止/引燃） 
};
queue<barrel> barrels;//桶队列
queue<tnt> TNTs;//炸弹队列
map<string,int> game_timer;//游戏计时器 
map<string,bool> game_flag;//游戏标志 
int dx4[4]={0,1,0,-1};
int dy4[4]={-1,0,1,0};
//前、右、后、左 
int dx8[8]={0,1,1,1,0,-1,-1,-1};
int dy8[8]={-1,-1,0,1,1,1,0,-1};
//前、右前、右、右后、后、左后、左、左前 
queue<position_3D> Q;
bool vst[MAX_LENGTH+1][MAX_WIDTH+1][MAX_HEIGHT*2+1];
int dis[MAX_LENGTH+1][MAX_WIDTH+1][MAX_HEIGHT*2+1];
int dis_to_exit[MAX_LENGTH+1][MAX_WIDTH+1][MAX_HEIGHT*2+1],dis_to_player[MAX_LENGTH+1][MAX_WIDTH+1][MAX_HEIGHT*2+1];
int mx_dis_to_player;
bool pos_in_room[MAX_LENGTH+1][MAX_WIDTH+1][MAX_HEIGHT*2+1];
vector<position_3D> pos_dis_to_player[(MAX_LENGTH-1)*(MAX_WIDTH-1)*(MAX_HEIGHT*2)];
vector<position_3D> pos_in_nest;
//BFS专用
int sum1[MAX_LENGTH+1][MAX_WIDTH+1],sum2[MAX_LENGTH+1][MAX_WIDTH+1];
//前缀和 
bool stair_exist[MAX_HEIGHT+1][2];//记录某层楼有没有上0/下1楼梯
//迷宫生成 
bool occlusion[4][360];
int cnt_visible[4]={360,360,360,360};
//视野计算 
//变量 
void hideCursor(){//隐藏光标 
	CONSOLE_CURSOR_INFO cursor_info1={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info1);
} 
void gotoxy(int x,int y){//移动光标
	if(x<0||x>MAX_SCREEN_LENGTH-1||y<0||y>MAX_SCREEN_WIDTH-1) return;
	COORD pos={short(x),short(y)};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
position_2D GetConsoleCursor(){
	position_2D coordScreen={0,0}; //光标位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi)){
		coordScreen.x=csbi.dwCursorPosition.X;
		coordScreen.y=csbi.dwCursorPosition.Y;
	}
	return coordScreen; //光标位置
}
void SLEEP(int x){//延时（单位：毫秒） 
	int time_now=clock();
	while(clock()-time_now<x); 
}
void CLEAR(){
	SetConsoleTextAttribute(hout,0x07);
	system("cls");
	SetConsoleTextAttribute(hout,0x07);
}
void wait_until(int key){
	while(1){
		if(_kbhit()){
			int c=_getch();
			if(c==key) return;
		}
	}
}
bool pos_in_area(int posx,int posy,int areax,int areay,int areal,int areaw){//判断坐标是否在指定范围内
	//areal 范围长 areaw 范围宽 
	return posx>=areax&&posx<=areax+areal-1&&posy>=areay&&posy<=areay+areaw-1;
}
bool pos_in_area2(int posx,int posy,int areax1,int areay1,int areax2,int areay2,int kind=1){//判断坐标是否在指定范围内
	//areal 范围长 areaw 范围宽 
	if(kind==1) return posx>=areax1&&posx<=areax2&&posy>=areay1&&posy<=areay2;
	if(kind==2) return posx>areax1&&posx<areax2&&posy>areay1&&posy<areay2;
	return false;
}
position_2D position_3Dto2D(position_3D pos){
	return (position_2D){pos.x,pos.y};
} 
position_3D position_2Dto3D(position_2D pos,int z){
	return (position_3D){pos.x,pos.y,z};
}
position_2D position_2Dtoscr(position_2D pos){
	return (position_2D){(pos.x-player1.pos.x)*2+MAX_SCREEN_LENGTH/2,(pos.y-player1.pos.y)+MAX_SCREEN_WIDTH/2};
} 
position_2D position_3Dtoscr(position_3D pos){
	return (position_2D){(pos.x-player1.pos.x)*2+MAX_SCREEN_LENGTH/2,(pos.y-player1.pos.y)+MAX_SCREEN_WIDTH/2};
} 
position_2D position_scrto2D(position_2D pos){
	return (position_2D){(pos.x-MAX_SCREEN_LENGTH/2)/2+player1.pos.x,pos.y-MAX_SCREEN_WIDTH/2+player1.pos.y};
}
position_3D position_scrto3D(position_2D pos,int z){
	return (position_3D){(pos.x-MAX_SCREEN_LENGTH/2)/2+player1.pos.x,pos.y-MAX_SCREEN_WIDTH/2+player1.pos.y,z};
}
//三维、二维和屏幕地图显示坐标互相转换 
direction ptp(position_3D a,position_3D b){//a在b的什么方向 
	direction ret;
	if(a.x>b.x) ret.d2=1;//右
	else ret.d2=3;//左
	if(a.y<b.y) ret.d1=0;//上
	else ret.d1=2;//下
	return ret; 
}
position_2D dtp2(position_2D pos,int dir,int d){
	switch(d){
		case 4:return (position_2D){pos.x+dx4[dir],pos.y+dy4[dir]};
		case 8:return (position_2D){pos.x+dx8[dir],pos.y+dy8[dir]};
		default:return (position_2D){-1,-1};
	}
}
position_3D dtp3(position_3D pos,int dir,int d){//在pos位置的d方向是什么位置 
	switch(d){
		case 4:return (position_3D){pos.x+dx4[dir],pos.y+dy4[dir],pos.z};
		case 8:return (position_3D){pos.x+dx8[dir],pos.y+dy8[dir],pos.z};
		default:return (position_3D){-1,-1,-1};
	}
}
int turn(int d,int op){//给定当前方向（d）和一个操作（op）（TURN_RIGHT,TURN_BACK,TURN_LEFT）
	switch(op){
		case TURN_RIGHT:return (d+1)%4;
		case TURN_BACK:return (d+2)%4;
		case TURN_LEFT:return (d+3)%4;
	}
	return d;
}
bool wall_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].maze==WALL;
}
bool space_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].maze==SPACE;
}
bool door_here(position_3D pos,int state=-1){
	return DOOR1<=game_map[pos.x][pos.y][pos.z].maze&&game_map[pos.x][pos.y][pos.z].maze<=DOOR4
	&&(state==-1||game_map[pos.x][pos.y][pos.z].door_state==state);
}
bool no_door_here(position_3D pos){
	return !((DOOR1<=game_map[pos.x][pos.y][pos.z].maze&&game_map[pos.x][pos.y][pos.z].maze<=DOOR4)
	||game_map[pos.x][pos.y][pos.z].maze==SPACE);//不能是钥匙门和常开门 
}
bool stair_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].maze==UPSTAIR||game_map[pos.x][pos.y][pos.z].maze==DOWNSTAIR;
}
bool nobody_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].player_enemy==NOBODY;
}
bool player_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].player_enemy==PLAYER;
}
bool enemy_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].player_enemy==BUG||game_map[pos.x][pos.y][pos.z].player_enemy==GHOST;
}
bool nothing_here(position_3D pos){
	return game_map[pos.x][pos.y][pos.z].things.nothing();
}
bool no_mirror_around(position_3D pos){//检查一个位置会不会与镜子相邻或重合
	if(game_map[pos.x][pos.y][pos.z].things.mirrors.exist) return false; 
	for(int i=0;i<4;i++){
		position_3D v=dtp3(pos,i,4);
		if(pos_in_area2(v.x,v.y,1,1,length,width,2)
		&&game_map[v.x][v.y][v.z].things.mirrors.exist) return false;
	}
	return true;
}
int count_around_pos(position_3D pos,int d,int maze,int n=length,int m=width){
	int cnt=0;
	if(maze==STAIRS){
		cnt=count_around_pos(pos,d,UPSTAIR)+count_around_pos(pos,d,DOWNSTAIR);
		return cnt;
	}
	else if(maze==DOORS){
		for(int i=0;i<4;i++) cnt+=count_around_pos(pos,d,DOOR1+i);
		return cnt;
	}
	switch(d){
		case 4:
			if(maze==NEST){
				for(int i=0;i<4;i++){
					position_3D v=dtp3(pos,i,4);
					if(game_map[v.x][v.y][v.z].things.nst.exist&&game_map[v.x][v.y][v.z].maze==SPACE) cnt++;
				}
				return cnt;
			}
			for(int i=0;i<4;i++){
				position_3D v=dtp3(pos,i,4);
				if(pos_in_area2(v.x,v.y,1,1,n,m)&&game_map[v.x][v.y][v.z].maze==maze) cnt++;
			}
			break;
		case 8:
			if(maze==NEST){
				for(int i=0;i<4;i++){
					position_3D v=dtp3(pos,i,4);
					if(game_map[v.x][v.y][v.z].things.nst.exist&&game_map[v.x][v.y][v.z].maze==SPACE) cnt++;
				}
				return cnt;
			}
			for(int i=0;i<8;i++){
				position_3D v=dtp3(pos,i,8);
				if(pos_in_area2(v.x,v.y,1,1,n,m)&&game_map[v.x][v.y][v.z].maze==maze) cnt++;
			}
			break;
	}
	return cnt;
}
bool worth_relecting(position_3D pos){//反射这个位置对玩家是有用的 
	return space_here(pos)||stair_here(pos)||door_here(pos);
} 
bool in_room(position_3D pos){//位置在某个房间内 
	if(wall_here(pos)) return false;
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(wall_here(a)) continue;
		if(wall_here(b)){
			i++;
			continue;
		}
		position_3D c=dtp3(a,j,4);//pos的i方向、j方向、i偏j方向的位置
		if(!wall_here(c)) return true; 
	}
	return false;
}
bool see_through(position_3D pos,int kind=1){//视线可以穿过这个位置
//kind=1：正视，只要是空地（没镜子）或楼梯或开着的门视线就可以穿过
//kind=2：斜视，只要是空地或楼梯或开着的门视线就可以穿过
	if(kind==1) return space_here(pos)||stair_here(pos)||door_here(pos,1);
	else return space_here(pos)||stair_here(pos)||door_here(pos,1);
}
bool light_through(position_3D pos){//光线可以穿过 
	return space_here(pos)||stair_here(pos)||door_here(pos,1);
}
bool ghost_through(position_3D u){//鬼可以穿过
	return (stair_here(u)||door_here(u,1)||space_here(u))&&nobody_here(u); 
} 
int gcd(int m,int n){//最大公约数
	if(m%n==0) return n;
	else return gcd(n,m%n);//辗转相除法 
}
int lcm(int m,int n){//最小公倍数 
	return m*n/gcd(m,n);//原数的积=最大公约数*最小公倍数 
} 
void nearest_RATIO(int a,int b,int l){//最接近的范围限制比值 
	if(a==0||b==0){
		cout<<a<<":"<<b;
		return;
	}
	int k1=1000,k2=1,min=k1*b-k2*a;
	for(int i=1;i<=l;i++){
		for(int j=1;j<=l;j++){
			if(abs(i*b-j*a)<min&&i*b>=j*a){
				k1=i;k2=j;
				min=k1*b-k2*a;
			}
		}
	}
	cout<<k1<<":"<<k2;
}
int MHT_DIST(int x1,int y1,int x2,int y2){//曼哈顿距离 
	return abs(x1-x2)+abs(y1-y2);
}
int MHT_DIST2(int x1,int y1,int z1,int x2,int y2,int z2){//三维曼哈顿距离
	return  abs(x1-x2)+abs(y1-y2)+abs(z1-z2);
}
void CUT_LINE(int length,char x){//分割线 
	for(;length>0;length--){
		cout<<x;		
	}
	cout<<endl;
}
void PRINT(rectangle area,int x,int y,string a,int times=1,int time=0,bool enter=false){
//自定义输出（重复、延时、自动换行） 
	position_2D pos;
	pos.x=x,pos.y=y;
	for(int i=1;i<=times;i++){
		for(int j=0;j<int(a.size());j++,pos.x++){
			if(pos.x>=0&&pos.y>=0&&(int(a[j])>=0||int(a[j-1]>=0))) gotoxy(pos.x,pos.y);
			if(pos_in_area2(pos.x,pos.y
			,area.upper_left.x,area.upper_left.y,area.lower_right.x,area.lower_right.y,2)){
				cout<<a[j];
				SLEEP(time);
			}
		}
		if(enter) cout<<endl,pos.y++,pos.x=x;
	}
}
string connect_str(string a,string b,string c="",string d="",string e="",string f="",string g="",string h=""){
	//连接字符串（最多8个） 
	string ret;
	ret+=a;ret+=b;ret+=c;ret+=d;ret+=e;ret+=f;ret+=g;ret+=h;
	return ret;
}
string int_to_str(int x,int y=0){//int整型转化成string字符串（y位，少位用前导0补充，y==0时代表不使用前导0） 
	string s="";string f=(x<0?"-":"");
	if(x==0){
		if(y==0) return "0"; 
		while(y--) s+='0';
		return s;
	}
	x=abs(x);
	while(x){
		s+=char(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	while(y!=0&&int(s.size())<y) s='0'+s;
	s=f+s;
	return s;
}
string ll_to_str(ll x,ll y=0){//ll整型转化成string字符串（y位，少位用前导0补充，y==0时代表不使用前导0） 
	string s=(x<0?"-":"");
	if(x==0){
		if(y==0) return "0"; 
		while(y--) s+='0';
		return s;
	}
	x=abs(x);
	while(x){
		s+=char(x%10+'0');
		x/=10;
	}
	reverse(s.begin(),s.end());
	while(y!=0&&ll(s.size())<y) s='0'+s;
	return s;
}
string double_to_str(double x,int y=0){//double浮点数转化成string字符串（保留y位小数） 
	if(y>15) y=15;
	bool negative=x<0;
	if(x<0) x=-x;
	ll a=x*pow(10,y)+0.5,b=a/pow(10,y),c=(b>0?log10(b):0)+1;
	string s=ll_to_str(a,c+y);
	if(c<ll(s.size())) s.insert(c,".");
	if(negative) s='-'+s;
	return s;
}
string to_time(int hour,int min,int sec,string k="HH小时MM分钟SS秒",bool leading0=false){
	min+=sec/60;sec%=60;hour+=min/60;min%=60;
	string ret=k,h=int_to_str(hour),m=int_to_str(min),s=int_to_str(sec);
	if(leading0){
		if(h.size()<2) h='0'+h;
		if(m.size()<2) m='0'+m;
		if(s.size()<2) s='0'+s;
	}
	int p1,p2,p3;
	p1=ret.find("HH");
	if(hour!=0) ret.replace(p1,2,h);
	else ret.erase(0,ret.find("MM")-p1);
	p2=ret.find("MM");
	if(min!=0) ret.replace(p2,2,m);
	else ret.erase(p2,ret.find("SS")-p2);
	p3=ret.find("SS");
	if(sec!=0||(hour==0&&min==0)) ret.replace(p3,2,s);
	else ret.erase(p3,ret.size()-p3);
	return ret;
}
string repeat_char(char c,int times){
	string s="";
	if(times<=0) return "";
	while(times--) s+=c;
	return s;
}
string repeat_str(string s,int times){
	string ret="";
	if(times<=0) return "";
	while(times--) ret+=s;
	return ret;
}
void formatted_output(int kind,rectangle area,int x,int y,int color,string s,int times=1,int time=0,bool enter=false){
//kind=1：正常打印 2：PRINT；color=-1：和上次一样；x=INF：跟在上次后面 
	position_2D pos;
	if(x==INF) pos=GetConsoleCursor();
	else pos.x=x,pos.y=y;
	if(color!=-1) SetConsoleTextAttribute(hout,color);
	if(kind==1){
		for(int i=0;i<int(s.size());i++,pos.x++){
			if(pos.x>=0&&pos.y>=0&&(int(s[i])>=0||int(s[i-1])>=0)) gotoxy(pos.x,pos.y);
			if(pos_in_area2(pos.x,pos.y
			,area.upper_left.x,area.upper_left.y,area.lower_right.x,area.lower_right.y,2)){
				cout<<s[i];
			}
		}
	}
	else PRINT(area,pos.x,pos.y,s,times,time,enter);
}
void print_out_of_sight(){
	SetConsoleTextAttribute(hout,0x00);
	cout<<"  "; 
}
void print_body(){
	SetConsoleTextAttribute(hout,0xcf);
	cout<<"KO";
}
void print_player_enemy(int k,int id){
	player1.name+=" ";
	int c=player1.vts.lfin.change,c2=player1.d_change&&!player1.move,c3=0;
	if(id!=-1){
		if(k==BUG) c3=bugs[id].lfin.change;
		else c3=ghosts[id].lfin.change;
	}
	switch(k){
		case PLAYER:
			if(c2){
				SetConsoleTextAttribute(hout,0x9f);
				if(game_timer["玩家图标闪烁"]<=game_time) game_timer["玩家图标闪烁"]=game_time+100;
				player1.color=3;
				switch(player1.d){
					case 0:
						cout<<"↑";
						break;
					case 1:
						cout<<"→";
						break;
					case 2:
						cout<<"↓";
						break;
					case 3:
						cout<<"←";
						break;
				}
			}
			else if(c==1){
				SetConsoleTextAttribute(hout,0xaf);
				if(game_timer["玩家图标闪烁"]<=game_time) game_timer["玩家图标闪烁"]=game_time+1000;
				player1.color=1;
				cout<<player1.name.substr(0,2);
			}
			else if(c==2){
				SetConsoleTextAttribute(hout,0xcf);
				if(game_timer["玩家图标闪烁"]<=game_time) game_timer["玩家图标闪烁"]=game_time+100;
				player1.color=2;
				cout<<player1.name.substr(0,2);
			}
			else if(c==0&&game_timer["玩家图标闪烁"]<=game_time){
				SetConsoleTextAttribute(hout,0xf9);
				player1.color=0;
				cout<<player1.name.substr(0,2);
			}
			break;
		case GHOST:
			if(c3==2) SetConsoleTextAttribute(hout,0xcf);
			else SetConsoleTextAttribute(hout,0x0f);
			cout<<"鬼";
			break;
		case BUG:
			if(c3==2) SetConsoleTextAttribute(hout,0xcf);
			else if(c3==1) SetConsoleTextAttribute(hout,0xaf);
			else SetConsoleTextAttribute(hout,0xfc);
			cout<<"虫";
			break;
	}
	player1.name.erase(player1.name.size()-1,1);
}
void print_laser_beam(int d,int ipt){
	if(ipt) SetConsoleTextAttribute(hout,0xbf);
	else SetConsoleTextAttribute(hout,0xfb);
	if(ipt) cout<<"※";
	else if(d%2==0) cout<<"｜";
	else cout<<"－";
}
void print_exit(int x,int y){
	SetConsoleTextAttribute(hout,0xaf);
	if(x==1||y==1) cout<<"E]";
	else cout<<"[E";
}
void print_wall(){
	SetConsoleTextAttribute(hout,0x77);
	cout<<"  ";
}
void print_space(){
	SetConsoleTextAttribute(hout,0xff);
	cout<<"  ";
}
void print_spear(int d,bool h){
	SetConsoleTextAttribute(hout,0xf6);
	if(h){
		switch(d){
			case 0:
				cout<<"↑";
				break;
			case 1:
				cout<<"→";
				break;
			case 2:
				cout<<"↓";
				break;
			case 3:
				cout<<"←";
				break;
		}
	}
	else if(d%2==0) cout<<"｜";
	else cout<<"－";
}
void print_dart(int d,bool nest){
	if(nest) SetConsoleTextAttribute(hout,0xfc);
	else SetConsoleTextAttribute(hout,0xf9);
	switch(d){
		case 0:
			cout<<"∧";
			break;
		case 1:
			cout<<"＞";
			break;
		case 2:
			cout<<"∨";
			break;
		case 3:
			cout<<"＜";
			break;
	}
}
void print_key(int k,int light=0xf0){//light:灯光亮度（背景色，白/浅灰/深灰/黑） 
	switch(k){
		case KEY1:
			SetConsoleTextAttribute(hout,light+0x0c);
			cout<<char(3);
			break;
		case KEY2:
			SetConsoleTextAttribute(hout,light+0x0c);
			cout<<char(4);
			break;
		case KEY3:
			SetConsoleTextAttribute(hout,light+0x00);
			cout<<char(5);
			break;
		case KEY4:
			SetConsoleTextAttribute(hout,light+0x00);
			cout<<char(6);
			break;
	}
	cout<<"="; 
}
void print_nest(int change,int life,int z){
	switch(change){
		case 0:
			SetConsoleTextAttribute(hout,0xfc);
			cout<<"巢";
			break;
		case 2:
			SetConsoleTextAttribute(hout,0xcf);
			cout<<life<<" ";
			break;
	}
	/*
	SetConsoleTextAttribute(hout,0xfc);
	cout<<z<<" ";*/
}
void print_exit_signs(int k){
	SetConsoleTextAttribute(hout,0xfa);
	switch(k){
		case 0:
			cout<<"↑";
			break;
		case 1:
			cout<<"→";
			break;
		case 2:
			cout<<"↓";
			break;
		case 3:
			cout<<"←";
			break;
	}
}
void print_mirror(int side,int d){
	SetConsoleTextAttribute(hout,0xf0);
	if(side==1)
		switch(d){
			case 0:cout<<"◤";break;
			case 1:cout<<"◥";break;
			case 2:cout<<"◢";break;
			case 3:cout<<"◣";break;
		}
	else{
		if(d==0) cout<<"╱";
		else cout<<"╲";
		cout<<" ";
	}
} 
void print_food(int kind,int effect){
	switch(effect){
		case 1:SetConsoleTextAttribute(hout,0xf6);break;
		case 2:SetConsoleTextAttribute(hout,0xf5);break;
		case 3:SetConsoleTextAttribute(hout,0xf9);break;
	}
	if(kind==ADDL) cout<<"v"; 
	else cout<<char(3);
	cout<<char(24);
}
void print_weapon_energy_endurance(int num,int kind){
	switch(kind){
		case 0:SetConsoleTextAttribute(hout,0xfb);break;
		case 1:SetConsoleTextAttribute(hout,0xf6);break;
	}
	cout<<"+"<<num; 
}
void print_door(int state,int k){
	if(!state){//门没开 
		switch(k){
			case DOOR1:
				SetConsoleTextAttribute(hout,0x6f);
				cout<<char(3);
				break;
			case DOOR2:
				SetConsoleTextAttribute(hout,0x6f);
				cout<<char(4);
				break;
			case DOOR3:
				SetConsoleTextAttribute(hout,0x6f);
				cout<<char(5);
				break;
			case DOOR4:
				SetConsoleTextAttribute(hout,0x6f);
				cout<<char(6);
				break;
		}
		cout<<"]";
	}
	else{//门开了 
		switch(k){
			case DOOR1:
				SetConsoleTextAttribute(hout,0x2f);
				cout<<char(3);
				break;
			case DOOR2:
				SetConsoleTextAttribute(hout,0x2f);
				cout<<char(4);
				break;
			case DOOR3:
				SetConsoleTextAttribute(hout,0x2f);
				cout<<char(5);
				break;
			case DOOR4:
				SetConsoleTextAttribute(hout,0x2f);
				cout<<char(6);
				break;
		}
		cout<<" ";
	}
}
void print_stair(int k){
	SetConsoleTextAttribute(hout,0xf0);
	switch(k){
		case UPSTAIR:
			cout<<char(24)<<char(24);
			break;
		case DOWNSTAIR:
			cout<<char(25)<<char(25);
			break;
	}
}
void print_error_pos(int k){
	SetConsoleTextAttribute(hout,0x6f);
	cout<<"#"<<k;
}
string item::item_name(){
	int sn=player1.items.select_number;
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return "无"; 
	int k=v[sn];
	switch(k){
		case K1:case K2:case K3:case K4:return connect_str("钥匙",int_to_str(k-K1+1)); 
		case AS1:case AS2:case AS3:return connect_str("生命回复 ",int_to_str(k-AS1+1),"级");
		case AL1:case AL2:case AL3:return connect_str("体力恢复 ",int_to_str(k-AL1+1),"级");
		case BX:return "箱子";
		case BL:return "木桶";
		case TT:return "TNT炸药";
		case CE:return "蜡烛";
	}
}
int item::item_num(){
	int sn=player1.items.select_number;
	item &ITEM=player1.items;
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return 0; 
	int k=v[sn];
	switch(k){
		case K1:case K2:case K3:case K4:return ITEM.keys.door_keys[k-K1+KEY1-1]; 
		case AS1:case AS2:case AS3:case AL1:case AL2:case AL3:
			return ITEM.foods.food_cnt[(k-AS1)/EFFECT_OF_FOOD][(k-AS1)%EFFECT_OF_FOOD];
		case BX:return 0;
		case BL:return 0;
		case TT:return 0;
		case CE:return 0;
	}
	return 0;
}
int item::item_endurance(){
	int sn=player1.items.select_number;
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return 0; 
	int k=v[sn];
	switch(k){
		case K1:case K2:case K3:case K4:return 0; 
		case AS1:case AS2:case AS3:return 0;
		case AL1:case AL2:case AL3:return 0;
		case BX:return 0;
		case BL:return 0;
		case TT:return 0;
		case CE:return 0;
	}
	return 0;
}
string item::item_method(){
	int sn=player1.items.select_number;
	vector<int> &v=player1.items.item_lab;
	if(sn<0||sn>=v.size()) return "无"; 
	int k=v[sn];
	switch(k){
		case K1:case K2:case K3:case K4:return "自动"; 
		case AS1:case AS2:case AS3:
		case AL1:case AL2:case AL3:
		case BX:case BL:case TT:case CE:return "按下e键";
	}
	return "无"; 
}
void item::print_item(int k){
	switch(k){
		case K1:case K2:case K3:case K4:
			print_key(k-K1+KEY1);
			break;
		case AS1:case AS2:case AS3:case AL1:case AL2:case AL3:
			print_food((k-AS1)/EFFECT_OF_FOOD+ADDS,(k-AS1)%EFFECT_OF_FOOD+1);
			break;
		case BX:break;
		case BL:break;
		case TT:break;
		case CE:break;
		default:cout<<"ERROR";
	}
}
void item::print1(){
	position_2D opos;
	opos.x=item_area.upper_left.x+1;opos.y=item_area.upper_left.y+1;
	if(player1.action_kind==CHOOSE_ITEM)
		formatted_output(1,item_area,opos.x,opos.y,0xf0,"物品区");
	else
		formatted_output(1,item_area,opos.x,opos.y,0x0f,"物品区");
	opos.y++;
	formatted_output(1,item_area,opos.x,opos.y,0x0f,connect_str("持有物品：",item_name(),"          "));
	opos.x+=24;
	formatted_output(1,item_area,opos.x,opos.y,0x0f,connect_str("数量：",int_to_str(item_num()),"      "));
	opos.x+=9;
	formatted_output(1,item_area,opos.x,opos.y,0x0f,connect_str("耐久：",int_to_str(item_endurance()),"      "));
	opos.x=item_area.upper_left.x+1;
	opos.y++;
	formatted_output(1,item_area,opos.x,opos.y,0x0f,connect_str("使用方法：",item_method(),"          "));
}
void item::print2(){
	position_2D opos;
	opos.x=item_area.upper_left.x+1;opos.y=item_area.upper_left.y+4;
	gotoxy(opos.x,opos.y); 
	vector<int> &v=player1.items.item_lab;
	for(int i=0;i<v.size();i++) print_item(v[i]);
	formatted_output(2,item_area,INF,0,0x00,"  ",MAX_SIZE_OF_ITEM_LAB-v.size());
}
void item::print3(){
	if(item::select_number<0) return;//没选择物品
	int sn=item::select_number;
	position_2D opos;
	opos.x=item_area.upper_left.x+1;opos.y=item_area.upper_left.y+5;
	formatted_output(2,item_area,opos.x,opos.y,0x00," ",MAX_SIZE_OF_ITEM_LAB*2);
	opos.x=item_area.upper_left.x+sn*2+1;opos.y=item_area.upper_left.y+5;//标记符放在物品栏下方 
	formatted_output(1,item_area,opos.x,opos.y,0x0b,"↑");
} 
string weapon_name(int sw){
	switch(sw){
		case LSG:return "激光枪";
		case DART:return "飞镖";
		case SPR:return "矛"; 
		default:return "ERROR";
	}
}
string weapon_mode(){
	weapon &wpn=player1.items.wpn;
	switch(wpn.select_wpn){
		case LSG:return wpn.lsg.kname[wpn.lsg.kind];
		case DART:return "正常";
		case SPR:return "正常"; 
		default:return "ERROR";
	}
}
string weapon_method(){
	weapon &wpn=player1.items.wpn;
	switch(wpn.select_wpn){
		case LSG:return "按下S键发射";
		case DART:return "按下S键投掷";
		case SPR:return "自动"; 
		default:return "ERROR";
	}
}
void weapon::print1(){
	int sw=weapon::select_wpn,col=0x0f;
	position_2D opos;
	opos.x=item_area.upper_left.x+1;opos.y=item_area.upper_left.y+6;
	switch(sw){
		case LSG:col=0x0b;break; 
		case DART:col=0x09;break; 
		case SPR:col=0x06;break;
	}
	if(player1.action_kind==CHANGE_WPN)
		formatted_output(1,item_area,opos.x,opos.y,0xf0,"武器区");
	else
		formatted_output(1,item_area,opos.x,opos.y,0x0f,"武器区");
	opos.y++;
	formatted_output(1,item_area,opos.x,opos.y,0x0f,"当前武器：<");
	formatted_output(1,item_area,INF,INF,col,weapon_name(sw));
	formatted_output(1,item_area,INF,INF,0x0f,">    ");
	opos.x+=20;
	switch(sw){
		case LSG:
			formatted_output(1,item_area,opos.x,opos.y,0x0b
			,connect_str("武器能量：",int_to_str(lsg.energy),"    "));
			break; 
		case DART:
			formatted_output(1,item_area,opos.x,opos.y,0x09
			,connect_str("数量：",int_to_str(drt.num),"        "));
			break; 
		case SPR:
			formatted_output(1,item_area,opos.x,opos.y,0x06
			,connect_str("耐久度：",int_to_str(hsr.endurance),"      "));
			break;
	}
} 
void weapon::print2(){
	int sw=weapon::select_wpn,col=0x0f;
	position_2D opos;
	opos.x=item_area.upper_left.x+1;opos.y=item_area.upper_left.y+8;
	switch(sw){
		case LSG:col=0x0b;break; 
		case DART:col=0x09;break; 
		case SPR:col=0x06;break;
	}
	formatted_output(1,item_area,opos.x,opos.y,col,connect_str("模式：",weapon_mode(),"（空格键切换）        "));
} 
void weapon::print3(){
	int sw=weapon::select_wpn,col=0x0f;
	position_2D opos;
	opos.x=item_area.upper_left.x+1;opos.y=item_area.upper_left.y+9;
	switch(sw){
		case LSG:col=0x0b;break; 
		case DART:col=0x09;break; 
		case SPR:col=0x06;break;
	}
	formatted_output(1,item_area,opos.x,opos.y,col,connect_str("使用方法：",weapon_method(),"        "));
} 
int interconnection_distance(position_3D s,position_3D e,int max_dis,position_3D no_reach){
	//从s到e的步行距离（BFS） 
	memset(vst,0,sizeof(vst));
	memset(dis,0,sizeof(dis));
	while(!Q.empty()) Q.pop();
	vst[s.x][s.y][s.z]=1;
	dis[s.x][s.y][s.z]=0;
	Q.push(s);
	while(!Q.empty()){
		position_3D u=Q.front();Q.pop();
		if(u==e) return dis[u.x][u.y][u.z];
		if(dis[u.x][u.y][u.z]>max_dis) return -1;
		for(int i=0;i<4;i++){
			position_3D v=dtp3(u,i,4);
			if(v.x>=1&&v.x<=length&&v.y>=1&&v.y<=width&&v.z>=1&&v.z<=height
				&&!(vst[v.x][v.y][v.z]&&v!=no_reach)
				&&game_map[v.x][v.y][v.z].maze!=WALL
				&&!(DOOR1<=game_map[v.x][v.y][v.z].maze&&game_map[v.x][v.y][v.z].maze<=DOOR4)
				){
				if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
				else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
				vst[v.x][v.y][v.z]=1;
				dis[v.x][v.y][v.z]=dis[u.x][u.y][u.z]+1;
				Q.push(v);
			}
		}
	}
	return -1; 
}
bool useful_door(position_2D u,int z,int dis){//判断门是否有用
	position_2D a,b;//门前、门后的位置
	a.x=0;b.x=0;
	for(int i=0;i<4;i++){
		position_2D v=dtp2(u,i,4);
		if(pos_in_area2(v.x,v.y,1,1,length,width,2)&&space_here(position_2Dto3D(v,z))){
			if(a.x==0) a=v;
			else{
				b=v;
				break;
			}
		}
	}
	if(a.x==0||b.x==0) return false;//这个位置不能连上两个空地
	position_3D no_reach={-1,-1,-1};
	int dmaze=game_map[u.x][u.y][z].maze;
	if(game_map[u.x][u.y][z].maze!=WALL) game_map[u.x][u.y][z].maze=WALL;//no_reach=position_2Dto3D(u,z);
	int connect=interconnection_distance((position_3D){a.x,a.y,z},(position_3D){b.x,b.y,z},dis,no_reach);
	game_map[u.x][u.y][z].maze=dmaze;
	if(connect==-1||connect>=dis) return true;
	return false;
}
bool cmpa(int a,int b){//角度小于 
	return (a-b+360)%360>180;
} 
int calc_angle(position_3D a,position_3D b){//a->b计算方向角 
	position_3D c=b;c.x-=a.x;c.y-=a.y;
	int angle=(c.x==0?90:atan(1.0*abs(c.y)/abs(c.x))/PI*180);
	//cout<<abs(c.y)<<"/"<<abs(c.x)<<"->"<<angle<<endl;
	if(c.x<0){
		if(c.y>0) angle=180-angle;
		else angle+=180;
	}
	else if(c.y<0) angle=360-angle;
	return angle;
}
bool invisible(position_3D p,position_3D pos){//pos看不见p位置 
	//if(abs(p.x-pos.x)<=1||abs(p.y-pos.y)<=1) return false;
	//cout<<"?"<<p.x<<","<<p.y<<endl;
	for(int i=0;i<4;i++){
		//cout<<i<<":"<<cnt_visible[i]<<endl;
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//站 
		//cout<<"u "<<u.x<<","<<u.y<<endl;
		int mn=-1,mx=-1; 
		for(int j=0;j<4;j++){
			position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//标 
			if(u==v) continue;
			int a=calc_angle(u,v);
			//cout<<"v "<<v.x<<","<<v.y<<":"<<a<<endl;
			if(mn==-1||cmpa(a,mn)) mn=a;//cout<<mn<<"<"<<a<<endl,
			if(mx==-1||cmpa(mx,a)) mx=a;//cout<<a<<"<"<<mx<<endl,
		}
		//cout<<mn<<"->"<<mx<<endl;
		for(int j=mn;j!=(mx+1)%360;j=(j+1)%360)
			if(!occlusion[i][j]) return false;
	}
	return true; 
}
void mark_occlusion(position_3D p,position_3D pos){//p位置遮挡了pos视线 
	//cout<<"√"<<p.x<<","<<p.y<<endl;
	for(int i=0;i<4;i++){
		//cout<<i<<":"<<cnt_visible[i]<<endl;
		if(!cnt_visible[i]) continue;
		position_3D u=pos;u.x+=bool(i&1);u.y+=bool(i&2);//站 
		//cout<<"u "<<u.x<<","<<u.y<<endl;
		int mn=-1,mx=-1; 
		for(int j=0;j<4;j++){
			position_3D v=p;v.x+=bool(j&1);v.y+=bool(j&2);//标 
			if(u==v) continue;
			int a=calc_angle(u,v);
			//cout<<"v "<<v.x<<","<<v.y<<":"<<a<<endl;
			if(mn==-1||cmpa(a,mn)) mn=a;//cout<<mn<<"<"<<a<<endl,
			if(mx==-1||cmpa(mx,a)) mx=a;//cout<<a<<"<"<<mx<<endl,
		}
		//cout<<mn<<"->"<<mx<<endl;
		for(int j=mn;j!=(mx+1)%360;j=(j+1)%360)
			if(!occlusion[i][j]) occlusion[i][j]=1,cnt_visible[i]--;//,cout<<j<<","
		//cout<<endl;
	}
}
void prd(){
	gotoxy(0,40);
	for(int j=0;j<360;j++) printf("%4d",j);
	//cout<<endl;
	for(int i=0;i<4;i++){
		for(int j=0;j<360;j++) printf("%4d",occlusion[i][j]);
		//cout<<endl;
	}
}
bool rand_error(int max,int min){
	if(max<min){
		formatted_output(1,whole_screen,30,30,0x0c,"随机数参数又写反了！！");
		return true;
	}
	return false;
}
int RAND(int max,int min){//随机数 
	if(rand_error(max,min)) swap(max,min);
	int num=rand()%(max-min+1)+min;
	return num;
}
bool RAND_BOOL(int a){//概率随机布尔值 
	int num=rand()%100+1;
	if(num<=a) return 1;
	else return 0;
}
int RAND_ALTO(int max,int min,int a){//群体随机数 
	if(rand_error(max,min)) swap(max,min);
	int k=min;
	for(int i=1;i<=max-min+1;i++){
		if(RAND_BOOL(a)) k++;
	}
	return k;
}
void RAND_EXIT_AROUND_GAME_MAP(int cnt,int l=length,int w=width,int h=height){//地图长宽高 
	vector<position_3D> v;//存储可能会被选到的位置
	/* l=5,w=5
	0表示不可能会被选到，1表示有可能会被选到 
		(1,1)==>01110<==(l,1)
				10001
				10001
				10001
    	(1,w)==>01110<==(l,w)
 	当然，每层楼都要算进去
 	此外，选到的位置：至少要和一个非墙格子相邻（不连上一个通道那我怎么逃出去？）*/ 
	for(int z=1;z<=height+h;z++){//找出所有可以设置出口的位置 
		for(int x=2;x<l;x++){
			if(game_map[x][2][z].maze!=WALL)
				v.push_back((position_3D){x,1,z});
			if(game_map[x][w-1][z].maze!=WALL)
				v.push_back((position_3D){x,w,z});
		}
		for(int y=2;y<w;y++){
			if(game_map[2][y][z].maze!=WALL)
				v.push_back((position_3D){1,y,z});
			if(game_map[l-1][y][z].maze!=WALL)
				v.push_back((position_3D){l,y,z});
		}
	}
	for(int i=1;i<=cnt&&v.size()>0;i++){
		int j=RAND(v.size()-1,0);
		position_3D u=v[j];
		swap(v[j],v[v.size()-1]);v.pop_back();
		game_map[u.x][u.y][u.z].maze=EXIT;
		Q.push(u);vst[u.x][u.y][u.z]=1;//为出口标牌的设置做准备 
	} 
}
int RAND_MIRROR_DIRECTION(position_3D pos){//随机选镜子方向 
	vector<int> v;//存储可能会被选到的镜子朝向 
	/*  				0◤	   1◥	  2◢	 3◣ 
	反射哪个方向的位置  1→2↓ 2↓3← 3←0↑ 0↑1→ 
	*/
	for(int i=0;i<4;i++){
		int j=turn(i,TURN_RIGHT),k=turn(i,TURN_LEFT);
		position_3D a=dtp3(pos,i,4),b=dtp3(pos,j,4);
		if(worth_relecting(a)&&worth_relecting(b)) v.push_back(k);
	}
	if(v.size()>0) return v[RAND(v.size()-1,0)];
	return -1;
}
position_3D RAND_PLAYER_IN_GAME_MAP(int l=length,int w=width,int h=height){
//在游戏地图里随机选择玩家的位置（空地无人，远离出口，不疑无路） 
	vector<position_3D> v;//存储可能会被选到的位置
	int mx_dis=0;
	for(int z=1;z<=h;z++)
		for(int y=2;y<w;y++)
			for(int x=2;x<l;x++){
				position_3D u;
				u.x=x;u.y=y;u.z=z;
				if(space_here(u)&&nobody_here(u)&&nothing_here(u)
					&&count_around_pos(u,4,WALL)<=3)
						mx_dis=max(mx_dis,dis_to_exit[x][y][z]);
			}
	for(int z=1;z<=h;z++){
		for(int y=2;y<w;y++){
			for(int x=2;x<l;x++){
				position_3D u;
				u.x=x;u.y=y;u.z=z;
				if(space_here(u)&&nobody_here(u)&&nothing_here(u)
					&&count_around_pos(u,4,WALL)<=3
					&&mx_dis-dis_to_exit[x][y][z]<=pos_in_room[x][y][z]*5) v.push_back(u); 
			}
		}
	}
	if(v.size()>0) return v[RAND(v.size()-1,0)];
	return (position_3D){2,2,1};
}
//常用函数 
void screen_partition();
void welcome_player();
void ask_player();
void initial();
void game();
void win();
void lose();
void detail();
void end();
void ask_try_again();
void player_calculate_vision1();
void player_calculate_vision2(position_3D pos=player1.pos);
//函数声明 
int main(){//麒轩出品，必属精品 
	srand(time(0));
	hout=GetStdHandle(STD_OUTPUT_HANDLE);
	//屏幕输出句柄（用来更改字体颜色） 
	hideCursor();//隐藏输出光标 
	screen_partition();
	welcome_player();CLEAR();
	while(1){
		ask_player();CLEAR();
		initial();//输出初始画面和进行游戏是连贯的，不能清屏 
		game();CLEAR();
		if(game_success) win();
		else lose();
		detail();
		ask_try_again();
		CLEAR();
		if(!start_again){
			end();
			break;
		}
	}
	return 0;
}
//主函数
void screen_partition(){//屏幕分区 
	whole_screen.init(0,0,MAX_SCREEN_LENGTH-1,MAX_SCREEN_WIDTH-1);
	int midx=MAX_SCREEN_LENGTH/2,midy=MAX_SCREEN_WIDTH/2;//屏幕上显示的游戏地图中心点（玩家的位置） 
	game_map_area.init(max(0,midx-midy*2),0,min(MAX_SCREEN_LENGTH-1,midx+midy*2),MAX_SCREEN_WIDTH-1);
	//以玩家的位置为中心的一个（看起来像）正方形作为游戏地图范围（97*48），上下靠屏幕边界
	vital_signs_area.init(0,0,game_map_area.upper_left.x,MAX_SCREEN_WIDTH-1);
	//玩家信息栏放左边
	item_area.init(game_map_area.lower_right.x,0,MAX_SCREEN_LENGTH-1,MAX_SCREEN_WIDTH-1);
	//玩家物品栏放右边
}
void welcome_player(){
	//此前要清屏 
	formatted_output(2,whole_screen,40,20,0x07,"欢迎来到秘野迷踪！",1,150);
	formatted_output(2,whole_screen,40,21,-1,"作者：wqx",1,150);
	formatted_output(2,whole_screen,40,22,0x0e,"按下回车以开始",1,150);
	wait_until(PRESS_KEY_ENTER);
	formatted_output(2,whole_screen,40,22,0x0b,"游戏加载中......",1,100);
}
void ask_player(){
	//此前要清屏
	formatted_output(2,whole_screen,40,20,0x07,"请问您叫什么名字？（",1,100);
	formatted_output(2,whole_screen,INF,0,0x0e,"不得包含空格和标点符号",1,100);
	formatted_output(2,whole_screen,INF,0,0x07,"）",1,100);
	cin>>player1.name; 
	formatted_output(2,whole_screen,40,21,0x07,"请输入地图长宽高，",1,100);
	formatted_output(2,whole_screen,INF,0,0x0e,
	connect_str("4<=长<=",int_to_str(MAX_LENGTH),"，4<=宽<=",int_to_str(MAX_WIDTH)
	,"，1<=高<=",int_to_str(MAX_HEIGHT)),
	1,100);
	formatted_output(2,whole_screen,INF,0,0x07,"（请以",1,100);
	formatted_output(2,whole_screen,INF,0,0x0e,"空格",1,100);
	formatted_output(2,whole_screen,INF,0,0x07,"分隔）：",1,100);
	cin>>length>>width>>height;
	formatted_output(2,whole_screen,40,22,0x0b,"游戏初始化......",1,100);
}
	void all_assigned(){
		game_end=game_success=false;
		hideCursor();
		for(int z=1;z<=height*2;z++){
			for(int y=1;y<=width;y++){
				for(int x=1;x<=length;x++){
					MAP &POS=game_map[x][y][z];
					POS.floor=NORMAL;
					POS.maze=WALL;
					POS.door_state=false;
					POS.player_enemy=NOBODY;
					POS.emy.init(); 
					POS.things.init();
					POS.in_player_sight=-1;
				}
			}
		}
		mx_dis_to_player=0;
		memset(pos_in_room,0,sizeof(pos_in_room));
		
		cnt_notWALL=cnt_SPACE=cnt_STAIRS=0;
		
		mx_dis_to_player=0;
		for(int i=0;i<(MAX_LENGTH-1)*(MAX_WIDTH-1)*(MAX_HEIGHT*2);i++) pos_dis_to_player[i].clear();
		
		player1.up_down=0;
		while(!pos_in_sight.empty()) pos_in_sight.pop();
		while(!pos_lst_sight.empty()) pos_lst_sight.pop();
		while(!pos_backup.empty()) pos_backup.pop();
		screen_pos.clear();screen_z.clear();
		
		for(int i=0;i<4;i++) cnt_visible[i]=360;
		memset(occlusion,0,sizeof(occlusion));
		
		game_timer.clear(); 
		game_flag.clear();
		
		bugs.clear();ghosts.clear();
		while(!Qbug.empty()) Qbug.pop();
		while(!Qbug_nest.empty()) Qbug_nest.pop();
		while(!Qghost.empty()) Qghost.pop();
		
		while(!laser_beams.empty()) laser_beams.pop();
		while(!darts.empty()) darts.pop();
		while(!spears.empty()) spears.pop();
	}
			void print_game_map_pos(position_3D pos,int kind=1){//kind=1：函数内设置光标 2：函数外设置光标 
				int x=pos.x,y=pos.y,z=pos.z
				,px=(x-player1.pos.x)*2+MAX_SCREEN_LENGTH/2,py=(y-player1.pos.y)+MAX_SCREEN_WIDTH/2;
				if(kind==1&&(px<=game_map_area.upper_left.x||px+1>=game_map_area.lower_right.x
				||py<=game_map_area.upper_left.y||py>=game_map_area.lower_right.y)) return;
				if(kind==1) gotoxy(px,py);
				MAP &POS=game_map[x][y][z];
				thing &THING=POS.things;
				if(POS.emy.dead&&POS.emy.body_disapp>game_time)//有尸体
					print_body(); 
				else if(!nobody_here(pos))//有生物存在 
					print_player_enemy(POS.player_enemy,POS.emy.id);
				else if(THING.drt.exist())//有飞镖
					print_dart(THING.drt.prd(),THING.nst.exist); 
				else if(THING.nst.exist&&THING.nst.id!=-1){//有巢穴口
					nest &NST=THING.nst;
					bug_nest bns=bug_nests[NST.id];
					int c=bns.lfin.change,lf=bns.lfin.life,z=bns.pos.z;
					print_nest(c,lf,z); 
				}
				else if(THING.lsr.exist){//有激光束
					int d=THING.lsr.laser_beam;
					position_3D u=pos;u.x+=dx4[d];u.y+=dy4[d];
					MAP &NPOS=game_map[u.x][u.y][u.z];
					print_laser_beam(d,!light_through(u)||POS.things.mirrors.exist); 
				}
				else if(POS.maze==EXIT)//这里是出口 
					print_exit(x,y);
				else if(POS.maze==WALL)//这里是堵墙 
					print_wall();
				else if(space_here(pos)){//这里是空地 
					if(POS.things.nothing())//啥东西都没有 
						print_space();
					else{//这里放了些东西 
						if(THING.spr.exist)//有矛 
							print_spear(THING.spr.d,THING.spr.head);
						else if(THING.key)//有钥匙 
							print_key(THING.key);
						else if(THING.exit_signs.exist)//有指向出口的标牌
							print_exit_signs(THING.exit_signs.dir);
						else if(THING.mirrors.exist){//有镜子 
							mirror &MIRROR=THING.mirrors;
							print_mirror(MIRROR.side,MIRROR.dir);
						}
						else if(THING.foods.exist){//有食物
						    food &FOOD=THING.foods;
							print_food(FOOD.kind,FOOD.effect);
						}
						else if(THING.wee.exist)//有武器能量/耐久度回复 
							print_weapon_energy_endurance(THING.wee.num,THING.wee.kind);
					}
				}
				else if(DOOR1<=POS.maze&&POS.maze<=DOOR4)//貌似有扇门 
					print_door(POS.door_state,POS.maze);
				else if(POS.maze==UPSTAIR||POS.maze==DOWNSTAIR)//好像有楼梯 
					print_stair(POS.maze);
				else print_error_pos(POS.maze);
				cout<<endl;
			}
		string screen_display_coding(position_3D pos){//屏幕输出编码 
			string col,out,ret;//输出颜色、字符，返回值 
			int x=pos.x,y=pos.y,z=pos.z;
			MAP &POS=game_map[x][y][z];
			thing &THING=POS.things;
			if(POS.emy.dead&&POS.emy.body_disapp>game_time){//有尸体
				col="cf";//SetConsoleTextAttribute(hout,0xcf);
				out="KO";//cout<<"KO;
			}
			else if(!nobody_here(pos)){//有生物存在 
				bool lsr=THING.lsr.exist;int id=POS.emy.id;
				int c=player1.vts.lfin.change,c2=player1.d_change&&!player1.move,c3=0;
				if(id!=-1){
					if(POS.player_enemy==BUG) c3=bugs[id].lfin.change;
					else c3=ghosts[id].lfin.change;
				}
				switch(POS.player_enemy){
					case PLAYER:
						player1.name+=" ";
						if(c2){
							col="9f";//SetConsoleTextAttribute(hout,0x9f);
							switch(player1.d){
								case 0:out="↑";//cout<<"↑";
									break;
								case 1:out="→";//cout<<"→";
									break;
								case 2:out="↓";//cout<<"↓";
									break;
								case 3:out="←";//cout<<"←";
									break;
							}
						}
						else if(c==1) col="af",out=player1.name.substr(0,2);//SetConsoleTextAttribute(hout,0xaf);
						else if(c==2) col="cf",out=player1.name.substr(0,2);//SetConsoleTextAttribute(hout,0xcf);
						else if(c==0&&game_timer["玩家图标闪烁"]<=game_time) col="f9",out=player1.name.substr(0,2);
						//SetConsoleTextAttribute(hout,0xf9);
						//cout<<player1.name.substr(0,2);
						player1.name.erase(player1.name.size()-1,1);
						break;
					case GHOST:
						if(c3==2) col="cf";//SetConsoleTextAttribute(hout,0xcf);
						else col="0f";//SetConsoleTextAttribute(hout,0x0f);
						out="鬼";//cout<<"鬼";
						break;
					case BUG:
						if(c3==2) col="cf";//SetConsoleTextAttribute(hout,0xcf);
						else if(c3==1) col="af";//SetConsoleTextAttribute(hout,0xaf);
						else col="fc";//SetConsoleTextAttribute(hout,0xfc);
						out="虫";//cout<<"虫";
						break;
				}
			}
			else if(THING.drt.exist()){//有飞镖
				if(THING.nst.exist) col="fc";//SetConsoleTextAttribute(hout,0xfc);
				else col="f9";//SetConsoleTextAttribute(hout,0xf9);
				SetConsoleTextAttribute(hout,0xf9);
				switch(THING.drt.prd()){
					case 0:
						out="∧";//cout<<"∧";
						break;
					case 1:
						out="＞";//cout<<"＞";
						break;
					case 2:
						out="∨";//cout<<"∨";
						break;
					case 3:
						out="＜";//cout<<"＜";
						break;
				} 
			} 
			else if(THING.nst.exist&&THING.nst.id!=-1){//有巢穴口
				nest &NST=THING.nst;
				bug_nest bns=bug_nests[NST.id];
				int c=bns.lfin.change,lf=bns.lfin.life;
				switch(c){
					case 0:
						col="fc";//SetConsoleTextAttribute(hout,0xfc);
						out="巢";//cout<<"巢";
						break;
					case 2:
						col="fc";//SetConsoleTextAttribute(hout,0xcf);
						out=int_to_str(lf,0);//cout<<fixed<<setprecision(0)<<lf<<" ";
						break;
				}
			}
			else if(THING.lsr.exist){//有激光束
				int d=THING.lsr.laser_beam;
				position_3D u=pos;u.x+=dx4[d];u.y+=dy4[d];
				MAP &NPOS=game_map[u.x][u.y][u.z];
				bool ipt=!light_through(u)||POS.things.mirrors.exist;
				if(ipt) col="bf";//SetConsoleTextAttribute(hout,0xbf);
				else col="fb";//SetConsoleTextAttribute(hout,0xfb);
				if(ipt) out="※";//cout<<"※";
				else if(d%2==0) out="｜";//cout<<"｜";
				else out="－";//cout<<"－";
			}
			else if(POS.maze==EXIT){
				col="af";//SetConsoleTextAttribute(hout,0xaf);
				if(x==1||y==1) out="E]";//cout<<"E]";
				else out="[E";//cout<<"[E";
			}
			else if(POS.maze==WALL){//这里是堵墙 
				col="77";//SetConsoleTextAttribute(hout,0x77);
				out="  ";//cout<<"  ";
			}
			else if(space_here(pos)){//这里是空地 
				if(POS.things.nothing()){//啥东西都没有 
					col="ff";//SetConsoleTextAttribute(hout,0xff);
					out="  ";//cout<<"  ";
				}
				else{//这里放了些东西 
					if(THING.spr.exist){//有矛 
						int d=THING.spr.d,h=THING.spr.head;
						col="f6";//SetConsoleTextAttribute(hout,0xf6);
						if(h)
							switch(d){
								case 0:
									out="↑";//cout<<"↑";
									break;
								case 1:
									out="→";//cout<<"→";
									break;
								case 2:
									out="↓";//cout<<"↓";
									break;
								case 3:
									out="←";//cout<<"←";
									break;
							}
						else if(d%2==0) out="｜";//cout<<"｜";
						else out="－";//cout<<"－";
					}
					else if(THING.key){//有钥匙 
						switch(THING.key){
							case KEY1:
								col="fc";//SetConsoleTextAttribute(hout,0xfc);
								out=char(3);//cout<<char(3);
								break;
							case KEY2:
								col="fc";//SetConsoleTextAttribute(hout,0xfc);
								out=char(4);//cout<<char(4);
								break;
							case KEY3:
								col="f0";//SetConsoleTextAttribute(hout,0xf0);
								out=char(5);//cout<<char(5);
								break;
							case KEY4:
								col="f0";//SetConsoleTextAttribute(hout,0xf0);
								out=char(6);//cout<<char(6);
								break;
						}
						out+="=";//cout<<"="; 
					}
					else if(THING.exit_signs.exist){//有指向出口的标牌
						col="fa";//SetConsoleTextAttribute(hout,0xfa); 
						switch(THING.exit_signs.dir){
							case 0:
								out=char(24);//"24";//cout<<char(24);
								break;
							case 1:
								out=char(26);//"26";//cout<<char(26);
								break;
							case 2:
								out=char(25);//"25";//cout<<char(25);
								break;
							case 3:
								out=char(27);//"27";//cout<<char(27);
								break;
						}
						out+="]";//cout<<"]"; 
					}
					else if(THING.mirrors.exist){//有镜子 
						col="f0";//SetConsoleTextAttribute(hout,0xf0);
						mirror &MIRROR=THING.mirrors;
						if(MIRROR.side==1)
							switch(MIRROR.dir){
								case 0:
									out="◤";//cout<<"◤";
									break;
								case 1:
									out="◥";//cout<<"◥";
									break;
								case 2:
									out="◢";//cout<<"◢";
									break;
								case 3:
									out="◣";//cout<<"◣";
									break;
							}
						else{
							if(MIRROR.dir==0){
								//if(d1==2&&d2==1) cout<<"◤";
								//else cout<<"◢";
								out="╱";//cout<<"╱";
							}
							else{
								//if(d1==2&&d2==3) cout<<"◥";
								//else cout<<"◣";
								out="╲";//cout<<"╲";
							}
							out+=" ";//cout<<" ";
						}
					}
					else if(THING.foods.exist){//有食物
						food &FOOD=THING.foods;
						switch(FOOD.effect){
							case 1:col="f6";//SetConsoleTextAttribute(hout,0xf6);
								break;
							case 2:col="f5";//SetConsoleTextAttribute(hout,0xf5);
								break;
							case 3:col="f9";//SetConsoleTextAttribute(hout,0xf9);
								break;
						}
						if(FOOD.kind==ADDL) out="v";//cout<<"v"; 
						else out=char(3);//cout<<char(3);
						out+="↑";//cout<<"↑";
					}
					else if(THING.wee.exist){//有武器能量/耐久度回复
						int num=THING.wee.num,kind=THING.wee.kind;
						switch(kind){
							case 0:col="fb";//SetConsoleTextAttribute(hout,0xfb);
								break;
							case 1:col="f6";//SetConsoleTextAttribute(hout,0xf6);
								break;
						}
						out=connect_str("+",int_to_str(num));//cout<<"+"<<num; 
					}
				}
			}
			else if(DOOR1<=POS.maze&&POS.maze<=DOOR4&&!POS.door_state){//貌似有扇门 
				switch(POS.maze){
					case DOOR1:
						col="6f";//SetConsoleTextAttribute(hout,0x6f);
						out=char(3);//cout<<char(3);
						break;
					case DOOR2:
						col="6f";//SetConsoleTextAttribute(hout,0x6f);
						out=char(4);//cout<<char(4);
						break;
					case DOOR3:
						col="6f";//SetConsoleTextAttribute(hout,0x6f);
						out=char(5);//cout<<char(5);
						break;
					case DOOR4:
						col="6f";//SetConsoleTextAttribute(hout,0x6f);
						out=char(6);//cout<<char(6);
						break;
				}
				out+="]";//cout<<"]";
			}
			else if(DOOR1<=POS.maze&&POS.maze<=DOOR4&&POS.door_state){//貌似门开了 
					switch(POS.maze){
						case DOOR1:
							col="2f";//SetConsoleTextAttribute(hout,0x2f);
							out=char(3);//cout<<char(3);
							break;
						case DOOR2:
							col="2f";//SetConsoleTextAttribute(hout,0x2f);
							out=char(4);//cout<<char(4);
							break;
						case DOOR3:
							col="2f";//SetConsoleTextAttribute(hout,0x2f);
							out=char(5);//cout<<char(5);
							break;
						case DOOR4:
							col="2f";//SetConsoleTextAttribute(hout,0x2f);
							out=char(6);//cout<<char(6);
							break;
					}
					out+=" ";//cout<<" ";
			}
			else if(POS.maze==UPSTAIR||POS.maze==DOWNSTAIR){//好像有楼梯 
				col="f0";//SetConsoleTextAttribute(hout,0xf0);
				switch(POS.maze){
					case UPSTAIR:
						out=char(24)+char(24);//cout<<char(24)<<char(24);
						break;
					case DOWNSTAIR:
						out=char(25)+char(25);//cout<<char(25)<<char(25);
						break;
				}
			}
			else{
				col="6f";//SetConsoleTextAttribute(hout,0x6f);
				out="# ";//cout<<"#"<<POS.maze;
			}
			ret=col+out;
			return ret;
		}
		void print_game_map_z(int z){
			for(int y=1;y<=width;y++){
				for(int x=1;x<=length;x++){
					gotoxy((x-1)*2,y-1+(height*2-z)*width);
					print_game_map_pos((position_3D){x,y,z},2);
					//SLEEP(5);
				}
			}
		}
	void print_game_map(){
		for(int z=1;z<=height*2;z++) print_game_map_z(z);
	}
/*
void print(int l,int w,int h){
	for(int z=h;z>=1;z--){
		for(int y=1;y<=w;y++){
			for(int x=1;x<=l;x++){
				gotoxy(x*2-2,y+(height*2-z)*width-1);
				MAP &POS=game_map[x][y][z];
				if(POS.maze==SPACE) SetConsoleTextAttribute(hout,0xff);
				else if(UPSTAIR<=POS.maze&&POS.maze<=DOWNSTAIR){
					switch(POS.maze){
						case UPSTAIR:
							SetConsoleTextAttribute(hout,0x8f);
							cout<<char(24)<<char(24);
							break;
						case DOWNSTAIR:
							SetConsoleTextAttribute(hout,0x0f);
							cout<<char(25)<<char(25);
							break;
					}
				}
				else if(POS.maze==EXIT){
					SetConsoleTextAttribute(hout,0xaf);
					if(x==1||y==1) cout<<"E]";
					else cout<<"[E";
				}
				else SetConsoleTextAttribute(hout,0x77);
				cout<<"  ";
			}
		}
	}
}*/
			void rand_basic(int sx,int sy,int sz,int a,int b,int c,const int l=length,const int w=width,int h=height){
			//生成基础迷宫（空地+墙+楼梯，一条通路），这个尺寸是指一般游戏区的，不包括巢穴区 
				memset(stair_exist,0,sizeof(stair_exist));
				vector<position_3D> vec;//存储只连了一个非墙位置的墙
				map<position_3D,bool> f;//这个墙是否在列表中 
				memset(stair_exist,0,sizeof(stair_exist)); 
				position_3D st;st.x=sx,st.y=sy;st.z=sz;
				int smaze=2;//0：UPSTAIR 1：DOWNSTAIR 2：SPACE 
				if(sz<h&&sz>1) smaze=RAND(1,0);
				else if(sz<h) smaze=0;
				else if(sz>1) smaze=1;
				//能装楼梯就装楼梯 
				if(smaze==2){
					game_map[sx][sy][sz].maze=SPACE;cnt_SPACE++;
					/*
					gotoxy(sx*2-2,sy+(height*2-sz)*width-1);
					SetConsoleTextAttribute(hout,0xff);
					cout<<"  ";*/
				}
				else{
					position_3D pos=st;
					if(smaze==0){
						pos.z=sz+1;
						/*
						gotoxy(pos.x*2-2,pos.y+(height*2-pos.z)*width-1);
						SetConsoleTextAttribute(hout,0x0f);
						cout<<char(25)<<char(25);
						gotoxy(sx*2-2,sy+(height*2-sz)*width-1);
						SetConsoleTextAttribute(hout,0x8f);
						cout<<char(24)<<char(24);*/
					}
					else{
						pos.z=sz-1;
						/*
						gotoxy(pos.x*2-2,pos.y+(height*2-pos.z)*width-1);
						SetConsoleTextAttribute(hout,0x8f);
						cout<<char(24)<<char(24);
						gotoxy(sx*2-2,sy+(height*2-sz)*width-1);
						SetConsoleTextAttribute(hout,0x0f);
						cout<<char(25)<<char(25);*/
					}
					game_map[sx][sy][pos.z].maze=UPSTAIR+(smaze^1),stair_exist[pos.z][smaze^1]=true;
					for(int i=0;i<4;i++){
						position_3D v=dtp3(pos,i,4);
						if(pos_in_area2(v.x,v.y,1,1,l,w,2))
							vec.push_back(v),f[v]=true;
					}
					game_map[sx][sy][sz].maze=UPSTAIR+smaze;stair_exist[sz][smaze]=true;cnt_STAIRS++;
				}
				cnt_notWALL++;
				/*
				SLEEP(10);*/
				for(int i=0;i<4;i++){
					position_3D u=dtp3(st,i,4);
					if(pos_in_area2(u.x,u.y,1,1,l,w,2)){
						vec.push_back(u);f[u]=true; 
					}
				}
				while(vec.size()){
					int k=RAND(vec.size()-1,0);
					position_3D u=vec[k];//随便选一堵墙
					swap(vec[k],vec[vec.size()-1]);vec.pop_back();f[u]=0;//把墙u删除 
					if(count_around_pos(u,4,WALL,l,w)==3&&pos_in_area2(u.x,u.y,1,1,l,w,2)){
					//不是边缘墙且和三面都是墙，不会新增通路，可以拓展
						for(int i=0;i<4;i++){//无论如何u这个墙都会消失，提前把它周围的墙处理好 
							position_3D v=dtp3(u,i,4);
							if(!f.count(v)&&game_map[v.x][v.y][v.z].maze==WALL&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								vec.push_back(v),f[v]=true;
						}
						bool add_stair=RAND_BOOL(a),add_up=0,add_down=0;
						//是否加楼梯，向上/下楼梯分别行不行（虫子的巢穴内部暂不允许存在楼梯） 
						int stair_kind;//楼梯的种类（0：UPSTAIR 1：DOWNSTAIR） 
						position_3D u2=u;u2.z++;//计算上/下楼梯通到的位置 
						if(u.z<=h&&u.z>=1&&u2.z<=h&&game_map[u2.x][u2.y][u2.z].maze==WALL&&count_around_pos(u2,4,WALL,l,w)==4)
							add_up=true; 
						//在一般游戏区内且向上楼梯通到的这个位置不是空地且周围都是墙壁 
						u2=u;u2.z--;//计算下楼梯通到的位置 
						if(u.z<=h&&u2.z>=1&&u2.z<=h&&game_map[u2.x][u2.y][u2.z].maze==WALL&&count_around_pos(u2,4,WALL,l,w)==4)
							add_down=true; 
						//在一般游戏区内且向下楼梯通到的这个位置不是空地且周围都是墙壁 
						bool add_nest=RAND_BOOL((u.z<=h?b:c)); 
						position_3D u3=u;u3.z+=(u.z>h?-height:height);//计算进/出巢穴口通往的位置
						//（>height:在巢穴里，-=height <=height:在巢穴外，+=height） 
						if(!(game_map[u3.x][u3.y][u3.z].maze==WALL&&count_around_pos(u3,4,WALL,l,w)==4))
							add_nest=false;
						//进/出巢穴口通到的这个位置不是空地且周围都是墙壁 这个条件不成立就不行 
						if((add_up||add_down)//上下楼梯至少有一个行
						&&((add_up&&!stair_exist[u.z][0])//这层还没有向上楼梯
						||(add_down&&!stair_exist[u.z][1])//或这层还没有向下楼梯 
						||add_stair)//或想放楼梯
						){
							u2=u;
							if(add_up&&add_down) stair_kind=RAND(1,0);
							else if(add_up) stair_kind=0;
							else stair_kind=1;
							if(stair_kind==0) u2.z++;
							else u2.z--;
							for(int i=0;i<4;i++){//楼上/下周围的墙 
								position_3D v=dtp3(u2,i,4);
								if(!f.count(v)&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								//上面保证楼梯周围都是墙，所以不用判断
									vec.push_back(v),f[v]=true;
							}
							game_map[u.x][u.y][u.z].maze=UPSTAIR+stair_kind;
							game_map[u2.x][u2.y][u2.z].maze=UPSTAIR+(stair_kind^1);
							stair_exist[u.z][stair_kind]=true;stair_exist[u2.z][stair_kind^1]=true;
							cnt_STAIRS+=2;cnt_notWALL+=2;
							/*
							if(stair_kind==0){
								gotoxy(u.x*2-2,u.y+(height*2-u.z)*width-1);
								SetConsoleTextAttribute(hout,0x8f);
								cout<<char(24)<<char(24);
								gotoxy(u2.x*2-2,u2.y+(height*2-u2.z)*width-1);
								SetConsoleTextAttribute(hout,0x0f);
								cout<<char(25)<<char(25);
							}
							else{
								gotoxy(u.x*2-2,u.y+(height*2-u.z)*width-1);
								SetConsoleTextAttribute(hout,0x0f);
								cout<<char(25)<<char(25);
								gotoxy(u2.x*2-2,u2.y+(height*2-u2.z)*width-1);
								SetConsoleTextAttribute(hout,0x8f);
								cout<<char(24)<<char(24);
							}*/
						}
						else if(add_nest){//加个巢穴口没问题
							for(int i=0;i<4;i++){//进/出巢穴口后周围的墙 
								position_3D v=dtp3(u3,i,4);
								if(!f.count(v)&&pos_in_area2(v.x,v.y,1,1,l,w,2))
								//上面保证进/出巢穴口后周围都是墙，所以不用判断
									vec.push_back(v),f[v]=true;
							}
							bug_nest bns;//生成巢穴口
							if(u.z<=height) bns.init(u);
							else bns.init(u3);
							//存储在一般游戏区里的坐标
							bug_nests.push_back(bns);
							int id=int(bug_nests.size())-1;
							Qbug_nest.push(id);//编号存放到队列里 
							game_map[u.x][u.y][u.z].maze=game_map[u3.x][u3.y][u3.z].maze=SPACE;
							nest &NST=game_map[u.x][u.y][u.z].things.nst,&NST2=game_map[u3.x][u3.y][u3.z].things.nst;
							//分别对应u、u3（都得是引用！！！） 
							NST.exist=NST2.exist=true;NST.id=NST2.id=id;//两个对应的巢穴口共用一个编号 
							NST.to=u3;NST2.to=u;//巢穴口的坐标对应起来 
							cnt_SPACE++;cnt_notWALL++;
							/* 
							gotoxy(u.x*2-2,u.y+(height*2-u.z)*width-1);
							SetConsoleTextAttribute(hout,0xfc);
							cout<<"巢";
							gotoxy(u3.x*2-2,u3.y+(height*2-u3.z)*width-1);
							SetConsoleTextAttribute(hout,0xfc);
							cout<<"巢";*/
						}
						else{//楼梯放了会新增一条通路或者不想放楼梯，就只是空地 
							game_map[u.x][u.y][u.z].maze=SPACE;
							cnt_SPACE++;cnt_notWALL++;
							/*
							gotoxy(u.x*2-2,u.y+(height*2-u.z)*width-1);
							SetConsoleTextAttribute(hout,0xff);
							cout<<"  ";*/
						}
						/*
						SLEEP(10);*/
					}
				}
			}
			void fill_dead_ends(int kind,int a,int l=length,int w=width,int h1=1,int h2=height){//填充死胡同 
				vector<position_3D> vec;//存储只连了一个空地的空地（死胡同）
				int cnt2=0;//可能填充的地方（现在不一定是死胡同） 
				for(int z=h1;z<=h2;z++)
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							if(space_here(u)&&nothing_here(u)){
								cnt2++;
								if(count_around_pos(u,4,WALL,l,w)==3&&count_around_pos(u,4,NEST,l,w)==0) vec.push_back(u);
							}
						}
				int cnt=0;
				if(kind==1) cnt=a;
				else cnt=cnt2*a/100;
				/*
				gotoxy(0,40+kind);
				SetConsoleTextAttribute(hout,0x0f);
				cout<<vec.size();
				gotoxy(10,40+kind);
				SetConsoleTextAttribute(hout,0x0f);
				cout<<"#"<<cnt;*/
				while(vec.size()&&cnt){
					int k=RAND(vec.size()-1,0);
					position_3D u=vec[k];//随便选一个不是墙的位置
					game_map[u.x][u.y][u.z].maze=WALL;cnt--;
					swap(vec[k],vec[vec.size()-1]);
					vec.erase(vec.begin()+vec.size()-1);
					//把这个位置改成墙，删除
					/*
					gotoxy(u.x*2-2,u.y+(height*2-u.z)*width-1);
					SetConsoleTextAttribute(hout,0x77);
					cout<<"  ";*/
					for(int i=0;i<4;i++){//一个新增的墙只会使周围的空地可能变成死胡同 
						position_3D v=dtp3(u,i,4);
						if(space_here(v)&&nothing_here(v)&&count_around_pos(v,4,WALL,l,w)==3&&count_around_pos(v,4,NEST,l,w)==0
						&&pos_in_area2(v.x,v.y,1,1,l,w,2))//加个判断是否出界 
							vec.push_back(v);
					}
					/*
					gotoxy(0,40+kind);
					SetConsoleTextAttribute(hout,0x0f);
					cout<<vec.size()<<"  ";
					gotoxy(10,40+kind);
					SetConsoleTextAttribute(hout,0x0f);
					cout<<"#"<<cnt<<"  ";
					SLEEP(10);*/
				}
			}
			void make_room(int a,const int l=length,const int w=width,int h=height){
			//把聚在一起的墙挖光，形成一个房间 
				memset(sum1,0,sizeof(sum1));
				memset(sum2,0,sizeof(sum2));
				for(int z=1;z<=h;z++){
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							sum1[x][y]=int(game_map[x][y][z].maze!=WALL)+sum1[x][y-1];
							sum2[x][y]=int(game_map[x][y][z].maze!=WALL)+sum2[x-1][y];
						}
					for(int y=2;y<w;y++)
						for(int x=2;x<l;x++)//枚举矩形的左上角（至少厚度为2） 
							if(RAND_BOOL(a)&&game_map[x][y][z].maze==WALL
								&&game_map[x+1][y][z].maze==WALL&&game_map[x][y+1][z].maze==WALL){
								int x2=x+1,y2=y+1;//消除的矩形左上角(x,y)，右下角(x2,y2)
								if(RAND_BOOL(50)){
									while(x2<l&&sum1[x2][y2]-sum1[x2][y-1]==0) x2++;
									x2--;
									if(x2==x) continue;
									while(y2<w&&sum2[x2][y2]-sum2[x-1][y2]==0) y2++;
									y2--;
									if(y2==y) continue;
								}
								else{
									while(y2<w&&sum2[x2][y2]-sum2[x-1][y2]==0) y2++;
									y2--;
									if(y2==y) continue;
									while(x2<l&&sum1[x2][y2]-sum1[x2][y-1]==0) x2++;
									x2--;
									if(x2==x) continue;
								}
								for(int j=max(y,2);j<=min(y2,w-1);j++)
									for(int i=max(x,2);i<=min(x2,l-1);i++){//不在边缘墙上的不挖掉 
										game_map[i][j][z].maze=SPACE;
										/*
										gotoxy(i*2-2,j+(height*2-z)*width-1);
										SetConsoleTextAttribute(hout,0xff);
										cout<<"  ";
										SLEEP(10);*/
									}
								for(int i=x;i<=x2;i++)
									for(int j=y;j<=w;j++)
										sum1[x][y]=int(game_map[x][y][z].maze!=WALL)+sum1[x][y-1];
								for(int i=x;i<=l;i++)
									for(int j=y;j<=y2;j++)
										sum2[x][y]=int(game_map[x][y][z].maze!=WALL)+sum2[x-1][y];
							}
				}
				for(int z=1;z<=h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							pos_in_room[x][y][z]=in_room(u);
						}
				for(int z=height+1;z<=height+h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &POS=game_map[u.x][u.y][u.z];
							if(!wall_here(u)) pos_in_nest.push_back(u);
						}
			}
		void rand_maze(int l=length,int w=width,int h=height){
			//print_game_map();
			rand_basic(RAND(l-1,2),RAND(w-1,2),RAND(h,1),5,5,10);
			//调整下面这些函数的参数，生成不同的迷宫
			fill_dead_ends(1,RAND_ALTO(cnt_SPACE,0,RAND(10,5)),length,width,1,height);
			fill_dead_ends(2,85,length,width,height+1,height*2);
			make_room(100);
			//print(l,w,h);
			//SLEEP(10000);
			//CLEAR();
		}
		void make_nest(int a,int l=length,int w=width,int h=height){
			for(int z=1;z<=h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(space_here(u)&&nobody_here(u)&&nothing_here(u)
						&&RAND_BOOL(a)){ 
							bug_nest bns;//生成巢穴口
							bns.init(u);
							bug_nests.push_back(bns);
							int id=int(bug_nests.size())-1;
							POS.things.nst.exist=true;POS.things.nst.id=id;
							Qbug_nest.push(id);
						}
					}
		}
			void make_exits(int l=length,int w=width,int h=height){//生成所有的出口
				memset(vst,0,sizeof(vst));memset(dis_to_exit,0,sizeof(dis_to_exit));
				while(!Q.empty()) Q.pop();
				int exit_nums=RAND_ALTO(max((l+w)*height/10,1),1,5);//游戏地图中出口的数量
				RAND_EXIT_AROUND_GAME_MAP(exit_nums,l,w,h);
			}
			void make_exit_sign(int a,int b,int l=length,int w=width,int h=height){//生成出口的标牌->]（箭头用char(24~27)）
				while(!Q.empty()){//BFS 
					position_3D u=Q.front();Q.pop();
					for(int i=0;i<4;i++){
						position_3D v=dtp3(u,i,4);
						if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
							if(!vst[v.x][v.y][v.z]&&game_map[v.x][v.y][v.z].maze!=WALL){
								vst[v.x][v.y][v.z]=1;
								dis_to_exit[v.x][v.y][v.z]=dis_to_exit[u.x][u.y][u.z]+1;
								Q.push(v);
								if(v.z<=height&&space_here(v)&&nothing_here(v)
								&&count_around_pos(v,4,SPACE)>=3
								&&(pos_in_room[v.x][v.y][v.z]?RAND_BOOL(a):RAND_BOOL(b))
								){
									exit_sign &EXIT_SIGN=game_map[v.x][v.y][v.z].things.exit_signs;
									EXIT_SIGN.exist=1;
									EXIT_SIGN.dir=turn(i,TURN_BACK);
								}
								if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
								else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
								else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
								if(!vst[v.x][v.y][v.z]&&u.z!=v.z){//这边有楼梯或者巢穴口 
									vst[v.x][v.y][v.z]=1;
									dis_to_exit[v.x][v.y][v.z]=dis_to_exit[u.x][u.y][u.z]+1;
									Q.push(v);
								}
							}
						}
					}
				}
			}
		void make_exit(){
			//必须放在迷宫基本设施生成完毕后！！！ 
			make_exits(); 
			make_exit_sign(1,5);
			/*
			for(int z=height*2;z>=1;z--)
				for(int y=1;y<=width;y++)
					for(int x=1;x<=length;x++){
						gotoxy(x*3-2+length*2,y+(height*2-z)*width-1);
						SetConsoleTextAttribute(hout,0x07);
						cout<<dis_to_exit[x][y][z];
					}
			SLEEP(10000);*/
		}
	void make_map(){
		rand_maze();
		//make_nest(2); 
		make_exit();
		//print(length,width,height);SLEEP(5000);
	}
		void player::init(){
			player1.pos=RAND_PLAYER_IN_GAME_MAP();
			game_map[player1.pos.x][player1.pos.y][player1.pos.z].player_enemy=PLAYER;
			player1.d=0;player1.color=0;
			player1.vts.init();
			//player1.vlc.wait_time=1;player1.vlc.ts();//wait_time更新speed 
			player1.vlc.speed=100;player1.vlc.vt();//speed更新wait_time 
			player1.scr.init();
			player1.items.init();
			player1.move=true;
			player1.action_kind=RUN; 
			player1.lst_ud=player1.lst_enter=false;
		}
		void calculate_dis_to_player(int l=length,int w=width,int h=height){
			while(!Q.empty()) Q.pop();
			memset(vst,0,sizeof(vst));memset(dis_to_player,0,sizeof(dis_to_player));
			Q.push(player1.pos);
			vst[player1.pos.x][player1.pos.y][player1.pos.z]=1;
			while(!Q.empty()){//BFS 
				position_3D u=Q.front();Q.pop();
				for(int i=0;i<4;i++){
					position_3D v=dtp3(u,i,4);
					if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
						if(!vst[v.x][v.y][v.z]&&game_map[v.x][v.y][v.z].maze!=WALL){
							vst[v.x][v.y][v.z]=1;
							dis_to_player[v.x][v.y][v.z]=dis_to_player[u.x][u.y][u.z]+1;
							Q.push(v);
							if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
							else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
							else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
							if(!vst[v.x][v.y][v.z]&&u.z!=v.z){//这边有楼梯可以上下 
								vst[v.x][v.y][v.z]=1;
								dis_to_player[v.x][v.y][v.z]=dis_to_player[u.x][u.y][u.z]+1;
								Q.push(v);
							}
						}
					}
				}
			}
			for(int z=1;z<=height+h;z++)
				for(int y=2;y<w;y++)
					for(int x=2;x<l;x++){//统计到玩家不同距离的位置，计算最远距离
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						if(!wall_here(u)) pos_dis_to_player[dis_to_player[x][y][z]].push_back(u);
						mx_dis_to_player=max(mx_dis_to_player,dis_to_player[x][y][z]); 
					}
		}
	void make_player(){
		player1.init();
		calculate_dis_to_player();
		/*
		for(int z=height*2;z>=1;z--)
			for(int y=1;y<=width;y++)
				for(int x=1;x<=length;x++){
					gotoxy(x*3-2+length*3,y+(height-z)*width-1);
					SetConsoleTextAttribute(hout,0x07);
					cout<<dis_to_player[x][y][z];
				}
		SLEEP(30000);*/
	}
		void farther_more_doors(int a,int b,int c){//越远越多
			for(int i=10;i<=mx_dis_to_player;i++)
				if(RAND_BOOL(a)){
					int sz=pos_dis_to_player[i].size(),door_num=RAND_ALTO(sz>0?sz:1,1,b+i*(c-b)/mx_dis_to_player);
					//当前这个距离上可以放门的位置数量（用于随机取位置）和需要的门数量 
					while(sz&&door_num){
						int k=RAND(sz-1,0);
						position_3D u=pos_dis_to_player[i][k];
						swap(pos_dis_to_player[i][k],pos_dis_to_player[i][sz-1]);
						sz--;
						//随机找放门的位置
						MAP &DPOS=game_map[u.x][u.y][u.z]; 
						if(u.z<=height
						&&space_here(u)&&nothing_here(u)&&!count_around_pos(u,4,DOORS)
						&&useful_door(position_3Dto2D(u),u.z,10)){
						//空地、无物、有用（从门的一边到另一边的路程不会太近） 
							int door_kind=RAND(4,1);//随机选门种类
							DPOS.maze=door_kind-1+DOOR1;
							DPOS.door_state=false;
							door_num--;
						}
					}
				}
		}
		void doors_around_rooms(int a,int l=length,int w=width,int h=height){//门生成在房间周围 
			for(int z=1;z<=h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						if(pos_in_room[x][y][z])
							for(int i=0;i<4;i++){
								position_3D v=dtp3(u,i,4);
								MAP &DPOS=game_map[v.x][v.y][v.z]; 
								if(RAND_BOOL(a)
								&&space_here(v)&&nobody_here(v)&&nothing_here(v)
								&&count_around_pos(v,4,WALL)<=2&&!count_around_pos(v,4,DOORS)
								&&!pos_in_room[v.x][v.y][v.z]){
								//空地，周围没有门、不多于2堵墙，不在房间里 
									int door_kind=RAND(4,1);//随机选门种类
									DPOS.maze=door_kind-1+DOOR1;
									DPOS.door_state=false;
								}
							}
					}
		}
	void make_door(){
		farther_more_doors(20,10,80);
		doors_around_rooms(100);
	}
			void bug::init(position_3D u){
				pos=u;d=0;vlc.speed=RAND(10,1);vlc.vt();
				lfin.init(1);
				lst_ud=enter_nest=-INF;change_pos=update=false;
			}
			void bug_nest::init(position_3D u){
				pos=u;
				lfin.init(3);
			}
		void make_bug(int a,int b,int c,int l=length,int w=width,int h=height){//生成虫子 
			for(int z=1;z<=height+h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(space_here(u)&&nobody_here(u)&&nothing_here(u)&&dis_to_player[x][y][z]>=10//至少在玩家10步开外 
						&&RAND_BOOL(a+b/dis_to_exit[x][y][z]*(100-c-a)/b+(z>height?c:0))){ 
							bug bg;//生成虫子
							bg.init(u);
							bugs.push_back(bg);
							int id=int(bugs.size())-1;
							POS.player_enemy=BUG;POS.emy.id=id;
							Qbug.push(id);
						}
					}
		}
			void ghost::init(position_3D u){
				pos=u;d=0;vlc.speed=RAND(3,1);vlc.vt();
				lfin.init(2);
				change_pos=update=false;
			}
		void make_ghost(int a,int l=length,int w=width,int h=height){//生成鬼 
			for(int z=1;z<=height+h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						MAP &POS=game_map[u.x][u.y][u.z];
						if(space_here(u)&&nobody_here(u)&&nothing_here(u)&&dis_to_player[x][y][z]>=20//至少在玩家20步开外 
						&&RAND_BOOL(a)){ 
							ghost gt;//生成鬼
							gt.init(u);
							ghosts.push_back(gt);
							int id=int(ghosts.size())-1;
							POS.player_enemy=GHOST;POS.emy.id=id;
							Qghost.push(id);
						}
					}
		}
	void make_enemy(){
		make_bug(2,15,20);
		make_ghost(1);
	}
			void farther_less_keys(int a,int b,int c){//越远越少 
				for(int i=1;i<=mx_dis_to_player;i++)
					if(RAND_BOOL(a)){
						int sz=pos_dis_to_player[i].size(),key_num=RAND_ALTO(sz>0?sz:1,1,b-i*(b-c)/mx_dis_to_player);
						//当前这个距离上可以放钥匙的位置数量（用于随机取位置）和需要的钥匙数量（会随着生成不断减小） 
						while(sz&&key_num){
							int k=RAND(sz-1,0);
							position_3D u=pos_dis_to_player[i][k];
							swap(pos_dis_to_player[i][k],pos_dis_to_player[i][sz-1]);
							sz--;
							//随机找放钥匙的位置
							MAP &KPOS=game_map[u.x][u.y][u.z]; 
							if(u.z<=height&&space_here(u)&&KPOS.things.nothing()){
								int key_kind=RAND(3,0);//随机选钥匙种类
								KPOS.things.key=key_kind+KEY1;
								key_num--;
							} 
						}
					}
			}
			void keys_in_rooms(int a,int l=length,int w=width,int h=height){//钥匙生成在房间里面
				vector<position_3D> v;
				for(int z=1;z<=h;z++)
					for(int y=1;y<=w;y++)
						for(int x=1;x<=l;x++){
							position_3D u;
							u.x=x;u.y=y;u.z=z;
							MAP &KPOS=game_map[u.x][u.y][u.z]; 
							if(pos_in_room[x][y][z]&&space_here(u)&&KPOS.things.nothing())
								v.push_back(u);
						}
				for(int i=0;i<int(v.size());i++){
					position_3D u=v[i];
					MAP &KPOS=game_map[u.x][u.y][u.z]; 
					if(RAND_BOOL(a)){
						int key_kind=RAND(3,0);//随机选钥匙种类
						KPOS.things.key=key_kind+KEY1;
					} 
				}
			}
			void keys_to_doors(int a,int b,int l=length,int w=width){//每个钥匙都对应一扇门 
				vector<position_3D> vspace;//已访问、未放钥匙的空地	
				vector<position_3D> vdoor[4];//已访问、未放对应钥匙的门（四种分别记录）
				while(!Q.empty()) Q.pop();
				memset(vst,0,sizeof(vst));
				Q.push(player1.pos);
				vst[player1.pos.x][player1.pos.y][player1.pos.z]=1;
				while(1){
					while(!Q.empty()){//BFS 
						position_3D u=Q.front();Q.pop();
						for(int i=0;i<4;i++){
							position_3D v=dtp3(u,i,4);
							if(pos_in_area2(v.x,v.y,1,1,l,w,2)){
								if(!vst[v.x][v.y][v.z]
								&&!wall_here(v)&&!door_here(v)){//不穿墙、不走门（当然不包括起点） 
									vst[v.x][v.y][v.z]=1;
									Q.push(v);
									if(space_here(v)&&nothing_here(v)) vspace.push_back(v);//已访问、没有物品的空地
									else if(game_map[v.x][v.y][v.z].maze==UPSTAIR) v.z++;
									else if(game_map[v.x][v.y][v.z].maze==DOWNSTAIR) v.z--;
									else if(game_map[v.x][v.y][v.z].things.nst.exist) v=game_map[v.x][v.y][v.z].things.nst.to;
									if(u.z!=v.z&&!vst[v.x][v.y][v.z]){//这边有楼梯可以上下/巢穴可以进出，且不会走到去过的地方 
										vst[v.x][v.y][v.z]=1;
										Q.push(v);
									}
								}
								else if(!vst[v.x][v.y][v.z]&&door_here(v)){
									vst[v.x][v.y][v.z]=1;
									vdoor[game_map[v.x][v.y][v.z].maze-DOOR1].push_back(v);
									//已访问、未放对应钥匙的门
								}
							}
						}
					}
					vector<int> vkind;//可以选择的门的种类 
					for(int i=0;i<4;i++)
						if(vdoor[i].size()&&vspace.size()>=vdoor[i].size()) vkind.push_back(i);
					if(vkind.size()){//有可以选择的门的种类  
						int door_kind=vkind[RAND(vkind.size()-1,0)];//随机选门的种类
						for(int i=0;i<int(vdoor[door_kind].size());i++){
							position_3D dr=vdoor[door_kind][i];//当前放的钥匙对应的门 
							Q.push(dr);
							//把放了对应钥匙的门“打开”，作为下次循环的起点 
							int k=RAND(vspace.size()-1,0);
							position_3D u=vspace[k];
							//取出要放钥匙的空地
							MAP &KPOS=game_map[u.x][u.y][u.z];
							if(RAND_BOOL(a*max(1,b/dis_to_player[dr.x][dr.y][dr.z]))){//目前所有门都保证有钥匙 
								int key_kind=door_kind;
								KPOS.things.key=key_kind+KEY1;
								swap(vspace[k],vspace[vspace.size()-1]);vspace.pop_back();//放了钥匙才把这个空地删掉 
							}
							//生成钥匙 
						}
						vdoor[door_kind].clear();//清空这类门 
					}
					else break;//循环到没有未放对应钥匙的门（至少一次，因为最开始没门） 
				}
			}
		void make_key(){
			//farther_less_keys(20,15,5); 
			//keys_in_rooms(10);
			keys_to_doors(100,0); 
		}
		void make_mirror(int a,int l=length,int w=width,int h=height){
			for(int z=1;z<=h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						if(space_here(u)&&no_mirror_around(u)&&nobody_here(u)&&nothing_here(u)
						&&RAND_BOOL(a)){
							int mirror_dir=RAND_MIRROR_DIRECTION(u);
							if(mirror_dir==-1) continue;
							int cw=count_around_pos(u,4,WALL),mirror_side;
							if(cw==2) mirror_side=1;
							else if(!cw) mirror_side=2;
							else mirror_side=RAND(2,1);
							mirror &MIRROR=game_map[u.x][u.y][u.z].things.mirrors;
							MIRROR.exist=1;MIRROR.side=mirror_side;
							if(mirror_side==1) MIRROR.dir=mirror_dir;
							else MIRROR.dir=mirror_dir%2;
						}
					}
		}	
		void make_food(int a,int b,int l=length,int w=width,int h=height){
			for(int z=1;z<=h*2;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						if(space_here(u)&&nobody_here(u)&&nothing_here(u)&&RAND_BOOL(z<=h?a:b)){
							int kind=RAND(ADDL,ADDS),effect=log2(RAND(1<<3,1<<1));//8,7,6,5->3;4,3->2;2->1
							food &FOOD=game_map[u.x][u.y][u.z].things.foods;
							FOOD.exist=1;
							FOOD.kind=kind;FOOD.effect=effect;
						}
					}
		}
		void make_weapon_energy_edc(int a,int b,int c,int l=length,int w=width,int h=height){//生成武器的能量/耐久度回复
			for(int z=1;z<=h*2;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						weapon_energy_edc &WEE=game_map[u.x][u.y][u.z].things.wee;
						if(space_here(u)&&nobody_here(u)&&nothing_here(u)&&RAND_BOOL(z<=h?a:b)){
							WEE.exist=true;
							WEE.num=RAND(9,1);
							if(RAND_BOOL(c)) WEE.kind=0;
							else WEE.kind=1;
						}
					}
		}
		void make_dart(int a,int l=length,int w=width,int h=height){//生成地上的飞镖
			 for(int z=1;z<=h;z++)
				for(int y=1;y<=w;y++)
					for(int x=1;x<=l;x++){
						position_3D u;
						u.x=x;u.y=y;u.z=z;
						dart &DRT=game_map[u.x][u.y][u.z].things.drt;
						if(space_here(u)&&nobody_here(u)&&nothing_here(u)&&RAND_BOOL(a)){
							DRT.num[0]++;
							DRT.d[0]=RAND(3,0);
						}
					}
		}
		void make_box(){
		}
		void make_barrel(){
		}
		void make_TNT(){
		}
		void make_treasure(){
		}
		void make_candle(){
		}
		void make_lamp(){
		} 
		void make_water(){
		}
		void make_magma(){
		}
	void make_item(){
		make_key();
		make_mirror(20); 
		make_food(1,5);
		make_weapon_energy_edc(3,5,30);
		make_dart(2); 
		make_box();
		make_barrel();
		make_TNT();
		make_treasure();
		make_candle();
		make_lamp();
		make_water();
		make_magma();
	}
	void print_initial_picture(){
	    //此前要清屏 
		//whole_screen.output_frame();
		//game_map_area.output_frame();
		vital_signs_area.output_frame();
		item_area.output_frame();
		game_time=lst_see_time=0;
		player_calculate_vision2();
		player_calculate_vision1();
		while(!pos_in_sight.empty()){
			position_3D u=pos_in_sight.front();pos_in_sight.pop();
			print_game_map_pos(u);
			position_2D spos=position_3Dtoscr(u);
			pos_lst_sight.push(spos);
			//screen_pos[spos]=screen_display_coding(u);
		}
		
		formatted_output(1,vital_signs_area,1,1,0x0c
		,connect_str("生命值：",repeat_char(char(3),(player1.vts.lfin.life+5)/10.0),"           "));
		formatted_output(1,vital_signs_area,1,2,0x0a
		,connect_str("体力值：",int_to_str(player1.vts.stg.physical_strength,0),"% "));
		formatted_output(1,vital_signs_area,1,3,0x0e
		,connect_str("击杀数：",int_to_str(player1.scr.kill_count)));
		formatted_output(1,vital_signs_area,1,4,0x07,"手动（按空格键）上下楼");
		formatted_output(1,vital_signs_area,1,5,0x0b,"移动    （F键切换）");
		
		player1.items.print1();player1.items.print2();player1.items.print3();
		player1.items.wpn.print1();player1.items.wpn.print2();player1.items.wpn.print3();
	}
void initial(){//游戏初始化
	//此前要清屏 
	all_assigned();
	make_map();
	make_player();
	make_door();
	make_enemy();
	make_item();
	int cnt=0;
	//print_game_map();
	//SLEEP(10000);
	//CLEAR();
	print_initial_picture();
}			
	void pause(){
		if(game_pause&&_kbhit()){
			switch(_getch()){//侦测按键 
				case PRESS_KEY_ENTER:
					game_pause=false;
					game_flag["游戏暂停/继续"]=true; 
					return;
			}
		}
	}
	void assigned(){
		player1.scr.time_spent=game_time;
		//更新用时 
		while(!pos_backup.empty()) pos_backup.pop();
		while(!pos_change.empty()) pos_change.pop();
		screen_z.clear();
		for(int i=0;i<4;i++) cnt_visible[i]=360;
		memset(occlusion,0,sizeof(occlusion));
		player1.d_change=player1.move=player1.vts.lfin.change=player1.vts.stg.change
		=player1.ud_change=player1.ak_change=player1.flash=player1.use_weapon
		=player1.enemy_move
		=player1.items.num_change=player1.items.sn_change=player1.items.il_change
		=player1.items.wpn.sw_change=player1.items.wpn.data_change=player1.items.wpn.mode_change
		=player1.scr.kc_change=false;
		game_flag["游戏暂停/继续"]=game_flag["虫子被玩家攻击"]=game_flag["清除尸体"]=game_flag["玩家矛改变位置"]=game_flag["飞镖变化"]=false;
	}
			void player_reduce_blood(double sub=1){
				player1.vts.lfin.hurt+=player1.vts.lfin.life;
				player1.vts.lfin.life-=sub;player1.scr.hurt_times++;
				player1.vts.lfin.hurt-=player1.vts.lfin.life;//防止误差 
				player1.vts.lfin.change=2;//扣血 
				pos_change.push(player1.pos);player1.flash=true;
				if(player1.vts.lfin.life<=0){
					player1.vts.lfin.life=0;
					game_end=true;game_success=false;
				}
			}
			void bug_move_away(int id){//改变位置重生 
				bug &bg=bugs[id];
				if(pos_in_nest.size()==0){//没有巢穴了 
					bg.update=false;
					return;
				}
				int k=RAND(pos_in_nest.size()-1,0);
				position_3D npos=pos_in_nest[k];
				bg.pos.x=npos.x;bg.pos.y=npos.y;bg.pos.z=npos.z;
				MAP &NPOS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				if(space_here(bg.pos)&&nobody_here(bg.pos)){
					bg.change_pos=false;bg.enter_nest=true;
					NPOS.player_enemy=BUG;NPOS.emy.id=id;
					bg.lfin.life=1;bg.lfin.change=false;
				}
				else bg.change_pos=true;
			}
		void deal_bug(){
			int bug_num=Qbug.size();
			while(bug_num>0){
				bug_num--;
				int id=Qbug.front();Qbug.pop();
				bug &bg=bugs[id];
				MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
				string s=connect_str("虫子",int_to_str(id));
				if(MHT_DIST2(bg.pos.x,bg.pos.y,bg.pos.z,player1.pos.x,player1.pos.y,player1.pos.z)>50
				&&POS.in_player_sight<lst_see_time)//离玩家距离超过50格且玩家看不到 
					bg.update=false;//停止更新 
				if(!bg.update) continue;
				Qbug.push(id);
				if(bg.change_pos){
					bug_move_away(id);
					continue;
				}
				thing &THING=POS.things;
				if((THING.lsr.exist&&bg.lfin.change!=2)//不是已被攻击状态 
				||(THING.drt.exist1()&&bg.lfin.change!=2)//不是已被攻击状态 
				||(THING.spr.exist&&game_timer[connect_str(s,"被矛刺中")]<=game_time)//1000毫秒延时已到 
				){
				    if(THING.spr.exist){
						game_timer[connect_str(s,"被矛刺中")]=game_time+1000;//每秒计算一次伤害 
						player1.items.wpn.hsr.endurance-=bg.vlc.speed;
						if(player1.items.wpn.hsr.endurance<0) player1.items.wpn.hsr.endurance=0;
						player1.items.wpn.data_change=true;
					}
					else player1.scr.shoot_hit_times++;
					life_injury &lfin=bg.lfin;
					lfin.life--;lfin.change=2;
					if(POS.in_player_sight==lst_see_time){
						pos_change.push(bg.pos);
						game_flag["虫子被玩家攻击"]=true; 
					}
					if(lfin.life<=0){
						player1.scr.kill_count++;player1.scr.kc_change=true;
						POS.emy.dead=true;POS.emy.body_disapp=game_time+200;
						pos_dead.push(bg.pos);
						MAP &POS=game_map[bg.pos.x][bg.pos.y][bg.pos.z];
						POS.player_enemy=NOBODY;POS.emy.id=-1;
						bug_move_away(id);
						continue;
					}
				}
				else if(!(THING.lsr.exist||THING.drt.exist1()||THING.spr.exist)){//要和上面一一对应 
					if(bg.lfin.change!=0&&POS.in_player_sight==lst_see_time){
						pos_change.push(bg.pos);
						game_flag["虫子被玩家攻击"]=true; 
					}
					bg.lfin.change=0;
				}
				if(game_timer[s]>game_time)//时间没到不更新 
					continue;
				game_timer[s]=game_time+bg.vlc.wait_time; 
				if(THING.spr.exist) continue;//被矛刺中无法移动和攻击 
				position_3D npos=bg.pos;
				int d=bg.d;
				if(POS.emy.phm.disapp>game_time&&POS.emy.phm.id!=id) d=POS.emy.phm.d;//有信息素 
				bool special_move=false;
				if(stair_here(npos)&&bg.lst_ud+5000<=game_time){//上下楼 
					if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
					else npos.z--;
					bg.lst_ud=game_time;special_move=true;
				}
				else if(POS.things.nst.exist&&bg.enter_nest+5000<=game_time){//进巢穴口
					position_3D npos2=POS.things.nst.to;
					MAP &POS2=game_map[npos2.x][npos2.y][npos2.z];
					npos.x=npos2.x;npos.y=npos2.y;npos.z=npos2.z;//移动到对应的巢穴口
					bg.enter_nest=game_time;special_move=true;
				}
				if(!special_move){//普通移动 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &THING2=NPOS.things;
				if(!THING2.spr.exist&&(stair_here(npos)||door_here(npos,1)||space_here(npos))&&nobody_here(npos)){
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					POS.emy.phm.disapp=game_time+2000;POS.emy.phm.id=id;POS.emy.phm.d=d;//留下信息素 
					NPOS.player_enemy=BUG;NPOS.emy.id=id;
					if(POS.in_player_sight==lst_see_time&&bg.pos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.push(bg.pos);
					}
					if(NPOS.in_player_sight==lst_see_time&&npos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.push(npos);
					}
					bg.pos=npos;
					if(!stair_here(npos)) bg.lst_ud=game_time-5000;
					if(!NPOS.things.nst.exist) bg.enter_nest=game_time-5000;
				}
				else{
					if(NPOS.player_enemy==PLAYER){
						player_reduce_blood(20.0/bg.vlc.speed);
						bg.lfin.life++;
						if(!game_flag["虫子被玩家攻击"]) bg.lfin.change=1;
					}
					else if(NPOS.player_enemy==BUG&&NPOS.emy.id!=-1&&!bugs[NPOS.emy.id].update){//更新传播
						int add=NPOS.emy.id;
						Qbug.push(add);bugs[add].update=true;
					}
					else if(NPOS.player_enemy==GHOST&&NPOS.emy.id!=-1&&!ghosts[NPOS.emy.id].update){//更新传播 
						int add=NPOS.emy.id;
						Qghost.push(add);ghosts[add].update=true;
					}
					int tmp=count_around_pos(npos,4,SPACE);
					if(npos.z>height&&pos_in_area2(npos.x,npos.y,1,1,length,width,2)
					&&wall_here(npos)&&tmp<3
					&&(tmp<=1?RAND_BOOL(5):RAND_BOOL(1))){
						NPOS.maze=SPACE;
						position_3D npos2=npos;npos2.z-=height;
						MAP &NPOS2=game_map[npos2.x][npos2.y][npos2.z];
						if(NPOS.in_player_sight==lst_see_time){
							game_flag["虫子挖地道"]=true;
						}
						if((wall_here(npos2)||space_here(npos2))&&count_around_pos(npos2,4,SPACE)<=1&&RAND_BOOL(50)){//生成巢穴口
							NPOS2.maze=SPACE;
							bug_nest bns;
							bns.init(npos2);
							bug_nests.push_back(bns);
							int id=int(bug_nests.size())-1;
							Qbug_nest.push(id);
							nest &NST=NPOS.things.nst,&NST2=NPOS2.things.nst;
							NST.exist=NST2.exist=true;NST.id=NST2.id=id;
							NST.to=npos2;NST2.to=npos;
							if(NPOS2.in_player_sight==lst_see_time){
								game_flag["虫子挖地道"]=true;
							}
						}
					}
					if(RAND_BOOL(50)) d=turn(d,TURN_RIGHT);
					else d=turn(d,TURN_LEFT);
					bg.d=d;
				}
			}
		}
			void ghost_move_away(int id){//改变位置重生 
				ghost &gt=ghosts[id];
				gt.pos.x=RAND(length-1,1);gt.pos.y=RAND(width-1,1);gt.pos.z=RAND(height,1);
				MAP &NPOS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				if(space_here(gt.pos)&&nobody_here(gt.pos)){
					NPOS.player_enemy=GHOST;NPOS.emy.id=id;
					gt.lfin.life=2;gt.lfin.change=false;
					gt.change_pos=false;
				}
				else gt.change_pos=true;
			}
			void ghost_turn(int &d,position_3D u){//随机改变方向/跟踪玩家足迹/跟着玩家声音 
				//旁边有玩家>声音>足迹>旁边有足迹>随机 
				vector<int> vd;vd.clear();
				MAP &POS=game_map[u.x][u.y][u.z];
				thing &THING=POS.things;
				position_3D v;
				int snd=-1,fpt=-1,fnear=-1;
				for(int i=0;i<4;i++){
					v=dtp3(u,i,4);
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &THING2=NPOS.things;
					if(player_here(v)){//旁边有玩家就走过去 
						d=i;
						return;//最高级别直接退出 
					}
					if(ghost_through(v)){
						if(d==i) vd.push_back(d);
						if(THING.fpt.d!=-1&&THING.fpt.d<4)//足迹向前后左右 
							fpt=THING.fpt.d;
						else if(THING2.fpt.d!=-1)//旁边有足迹 
							fnear=i;
						vd.push_back(i);
					}
				}
				if(stair_here(u)||POS.things.nst.exist){//上下楼、进出巢穴口
					v=u;
					position_3D v2=v;
					if(POS.things.nst.exist) v2=POS.things.nst.to;
					MAP &POS2=game_map[v2.x][v2.y][v2.z];
					if(POS.maze==UPSTAIR) v.z++;
					else if(POS.maze==DOWNSTAIR) v.z--;
					else{//移动到对应的巢穴口
						v.x=v2.x;
						v.y=v2.y;
						v.z=v2.z;
					}
					MAP &NPOS=game_map[v.x][v.y][v.z];
					thing &THING2=NPOS.things;
					if(player_here(v)){//旁边有玩家就走过去 
						d=4;
						return;//最高级别直接退出 
					}
					if(ghost_through(v)){
						if(d==4) vd.push_back(4);
						if(THING.fpt.d==4)//足迹上下楼 
							fpt=THING.fpt.d;
						else if(THING2.fpt.d!=-1)//旁边有足迹 
							fnear=4;
						vd.push_back(4);
					}
				}
				int sz=vd.size();
				if(snd!=-1) d=snd;
				else if(fpt!=-1) d=fpt;
				else if(fnear!=-1) d=fnear;
				else if(sz) d=vd[RAND(sz-1,0)]; 
			}
		void deal_ghost(){
			int ghost_num=Qghost.size();
			while(ghost_num>0){
				ghost_num--;
				int id=Qghost.front();Qghost.pop();
				ghost &gt=ghosts[id];
				MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
				string s=connect_str("鬼",int_to_str(id));
				if(MHT_DIST2(gt.pos.x,gt.pos.y,gt.pos.z,player1.pos.x,player1.pos.y,player1.pos.z)>200
				&&POS.in_player_sight<lst_see_time)//离玩家距离超过200格且玩家看不到 
					gt.update=false;//停止更新 
				if(!gt.update) continue;
				Qghost.push(id);
				if(gt.change_pos){
					ghost_move_away(id);
					continue;
				}
				thing &THING=POS.things;
				if((THING.lsr.exist&&gt.lfin.change!=2)//不是已被攻击状态 
				||(THING.drt.exist1()&&gt.lfin.change!=2)//不是已被攻击状态 
				){
					player1.scr.shoot_hit_times++;
					life_injury &lfin=gt.lfin;
					lfin.life--;lfin.change=2;
					if(POS.in_player_sight==lst_see_time){
						pos_change.push(gt.pos);
						game_flag["鬼被玩家攻击"]=true; 
					}
					if(lfin.life<=0){
						player1.scr.kill_count++;player1.scr.kc_change=true;
						POS.emy.dead=true;POS.emy.body_disapp=game_time+200;
						pos_dead.push(gt.pos);
						MAP &POS=game_map[gt.pos.x][gt.pos.y][gt.pos.z];
						POS.player_enemy=NOBODY;POS.emy.id=-1;
						ghost_move_away(id);
						continue;
					}
				}
				else if(!(THING.lsr.exist||THING.drt.exist1())){//要和上面一一对应 
					if(gt.lfin.change!=0&&POS.in_player_sight==lst_see_time){
						pos_change.push(gt.pos);
						game_flag["鬼被玩家攻击"]=true; 
					}
					gt.lfin.change=0;
				}
				if(game_timer[s]>game_time)//时间没到不更新 
					continue;
				game_timer[s]=game_time+gt.vlc.wait_time; 
				if(THING.lsr.exist) continue;//被激光命中无法移动和攻击 
				position_3D npos=gt.pos;
				int d=gt.d;
				ghost_turn(d,gt.pos); 
				if(stair_here(npos)&&d==4){//上下楼 
					if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
					else npos.z--;
				}
				else if(POS.things.nst.exist&&d==4){//进巢穴口
					position_3D npos2=POS.things.nst.to;
					MAP &POS2=game_map[npos2.x][npos2.y][npos2.z];
					npos.x=npos2.x;npos.y=npos2.y;npos.z=npos2.z;//移动到对应的巢穴口
				}
				else{//普通移动 
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				thing &THING2=NPOS.things;
				if((stair_here(npos)||door_here(npos,1)||space_here(npos))&&nobody_here(npos)){
					POS.player_enemy=NOBODY;POS.emy.id=-1;
					NPOS.player_enemy=GHOST;NPOS.emy.id=id;
					if(POS.in_player_sight==lst_see_time&&gt.pos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.push(gt.pos);
					}
					if(NPOS.in_player_sight==lst_see_time&&npos.z==player1.pos.z){
						player1.enemy_move=true;
						pos_change.push(npos);
					}
					gt.pos=npos;
				}
				else{
					if(NPOS.player_enemy==PLAYER){
						player_reduce_blood(10.0/gt.vlc.speed);
					}
					else if(NPOS.player_enemy==BUG&&NPOS.emy.id!=-1&&!bugs[NPOS.emy.id].update){//更新传播
						int add=NPOS.emy.id;
						Qbug.push(add);bugs[add].update=true;
					}
					else if(NPOS.player_enemy==GHOST&&NPOS.emy.id!=-1&&!ghosts[NPOS.emy.id].update){//更新传播 
						int add=NPOS.emy.id;
						Qghost.push(add);ghosts[add].update=true;
					}
					gt.d=d;
				}
			}
		}
	void deal_enemy(){
		deal_bug();
		deal_ghost();
	}
				void calculate_vision(position_3D pos,int dir){//计算在pos位置向d方向看的视野
 					position_3D npos=pos;
 					do{
 						npos=dtp3(npos,dir,4);
 						if(!pos_in_area2(npos.x,npos.y,1,1,length,width)) return;
						//超出地图范围就可以直接走人了
						MAP &POS=game_map[npos.x][npos.y][npos.z];
						if(POS.in_player_sight<game_time
						//&&!screen_pos.count(position_3Dtoscr(npos))//屏幕上这个位置没有显示内容
						){
 							pos_in_sight.push(npos);
							//玩家看得见的格子入队
							screen_z[position_3Dtoscr(npos)]=npos.z;//修改屏幕上这个位置所处的楼层（覆盖之前） 
 							POS.in_player_sight=game_time;//标记游戏地图
							if(POS.player_enemy==BUG&&POS.emy.id!=-1){//能看到这个虫子
								int id=POS.emy.id;
								bug &bg=bugs[id];
								if(!bg.update){
									Qbug.push(id);
									bg.update=true;
								}
							}
							else if(POS.player_enemy==GHOST&&POS.emy.id!=-1){//能看到这个鬼
								int id=POS.emy.id;
								ghost &gt=ghosts[id];
								if(!gt.update){
									Qghost.push(id);
									gt.update=true;
								}
							}
						}
 						if(see_through(npos,2)){
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT);
							position_3D pos1=dtp3(npos,d1,4),pos2=dtp3(npos,d2,4);
							if(game_map[pos1.x][pos1.y][pos1.z].in_player_sight<game_time){
 								pos_in_sight.push(pos1);
								screen_z[position_3Dtoscr(pos1)]=pos1.z;
 								game_map[pos1.x][pos1.y][pos1.z].in_player_sight=game_time;
							}
							if(game_map[pos2.x][pos2.y][pos2.z].in_player_sight<game_time){
 								pos_in_sight.push(pos2);
								screen_z[position_3Dtoscr(pos2)]=pos2.z;
 								game_map[pos2.x][pos2.y][pos2.z].in_player_sight=game_time;
							}
						}
						else{
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=turn(dir,TURN_BACK);
							position_3D pos1=dtp3(npos,d1,4),pos2=dtp3(npos,d2,4),pos3=dtp3(pos1,d3,4);
							if(game_map[pos1.x][pos1.y][pos1.z].in_player_sight<game_time
							&&see_through(pos3,2)){
 								pos_in_sight.push(pos1);
								screen_z[position_3Dtoscr(pos1)]=pos1.z;
 								game_map[pos1.x][pos1.y][pos1.z].in_player_sight=game_time;
							}
							pos3=dtp3(pos2,d3,4);
							if(game_map[pos2.x][pos2.y][pos2.z].in_player_sight<game_time
							&&see_through(pos3,2)){
 								pos_in_sight.push(pos2);
								screen_z[position_3Dtoscr(pos2)]=pos2.z;
 								game_map[pos2.x][pos2.y][pos2.z].in_player_sight=game_time;
							}
						}
						/*
						if(game_map[npos.x][npos.y][npos.z].things.mirrors.exist){
							mirror &MIRROR=game_map[npos.x][npos.y][npos.z].things.mirrors;
							int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=MIRROR.dir;
							if(MIRROR.side==1){
								if(dir==d3) calculate_vision(npos,d2);
								else if(d2==d3) calculate_vision(npos,d1);
							}
							else{
								if(dir%2==d3) calculate_vision(npos,d2);
								else calculate_vision(npos,d1);
							}
						}
						else if(player1.up_down){//玩家想通过楼梯看楼上/下 
 							if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
 							else if(game_map[npos.x][npos.y][npos.z].maze==DOWNSTAIR) npos.z--;
 							//上下楼梯要改变坐标
						}*/
					}
					while(see_through(npos,2));//视线可以穿过就继续计算（至少会看见一个格子）
				}
			void player_calculate_vision1(){//计算玩家的视野
				//if(!screen_pos.count(position_3Dtoscr(player1.pos))//屏幕上这个位置没有显示内容
				//){
				//没有看到这个地方
					pos_in_sight.push(player1.pos);
					//标记玩家所在的位置、入队
				//}
				screen_z[position_3Dtoscr(player1.pos)]=player1.pos.z;//修改屏幕上这个位置所处的楼层
				game_map[player1.pos.x][player1.pos.y][player1.pos.z].in_player_sight=game_time;
				for(int i=0;i<4;i++){//四个方向都计算视野 
					calculate_vision(player1.pos,i);
				}
			}
			void player_calculate_vision2(position_3D pos){
				int x=pos.x,y=pos.y,z=pos.z;
				queue<position_3D> visible_stair;//视野范围内的楼梯位置 
				memset(vst,0,sizeof(vst));
				while(!Q.empty()) Q.pop();
				vst[x][y][z]=1;
				pos_in_sight.push(pos);
				screen_z[position_3Dtoscr(pos)]=z;
				game_map[x][y][z].in_player_sight=game_time;
				Q.push(pos);
				while(!Q.empty()&&(cnt_visible[0]||cnt_visible[1]||cnt_visible[2]||cnt_visible[3])){
					position_3D u=Q.front();Q.pop();
					for(int i=0;i<4;i++){
						position_3D v=u;v.x+=dx4[i];v.y+=dy4[i];
						if(!pos_in_area2(v.x,v.y,1,1,length,width)||vst[v.x][v.y][z]) continue;
						vst[v.x][v.y][z]=1;
						if(invisible(v,pos)) continue;
						MAP &POS=game_map[v.x][v.y][z];
						if(POS.in_player_sight<game_time){
							pos_in_sight.push(v);
							screen_z[position_3Dtoscr(v)]=z;
							POS.in_player_sight=game_time;
							if(POS.player_enemy==BUG&&POS.emy.id!=-1){//能看到这个虫子
								int id=POS.emy.id;
								bug &bg=bugs[id];
								if(!bg.update){
									Qbug.push(id);
									bg.update=true;
								}
							}
							else if(POS.player_enemy==GHOST&&POS.emy.id!=-1){//能看到这个鬼
								int id=POS.emy.id;
								ghost &gt=ghosts[id];
								if(!gt.update){
									Qghost.push(id);
									gt.update=true;
								}
							}
						}
						if(wall_here(v)||door_here(v,0)) mark_occlusion(v,pos);
						else Q.push(v); 
						if(stair_here(v)) visible_stair.push(v); 
					}
				}
				/*
				while(!visible_stair.empty()&&player1.up_down){//玩家想通过楼梯看楼上/下 some bugs here
					for(int i=0;i<4;i++) cnt_visible[i]=360;
					memset(occlusion,0,sizeof(occlusion));
					position_3D u=visible_stair.front();visible_stair.pop();
					mark_occlusion(u,pos);
					for(int i=0;i<4;i++){//全部反过来 
						cnt_visible[i]=360-cnt_visible[i]; 
						for(int j=0;j<360;j++) occlusion[i][j]=!occlusion[i][j];
					}
					position_3D v=u;
					if(game_map[u.x][u.y][u.z].maze==UPSTAIR) v.z++;
					else v.z--;
					player_calculate_vision2(v);
				}*/
			}
			void player_use_item(){
				item &ITEM=player1.items;
				vector<int> &v=ITEM.item_lab;
				int x=player1.items.select_number;
				if(x<0||x>=v.size()) return;
				int k=v[x];
				life_injury &lfin=player1.vts.lfin;
				strength &stg=player1.vts.stg;
				bool flag=false;
				int add=(1<<(EFFECT_OF_FOOD+AS1-k-1))*5;
				switch(k){
					case AS1:case AS2:case AS3:
						lfin.life+=add;lfin.recovery+=add;
						lfin.change=true;
						ITEM.foods.food_cnt[0][k-AS1]--;
						if(!ITEM.foods.food_cnt[0][k-AS1]) flag=true;
						break;
					case AL1:case AL2:case AL3:
						stg.physical_strength+=(1<<(EFFECT_OF_FOOD+AL1-k-1))*10;
						stg.change=true;
						ITEM.foods.food_cnt[1][k-AL1]--;
						if(!ITEM.foods.food_cnt[1][k-AL1]) flag=true;
						break;
				}
				if(flag) player1.items.item_lab.erase(v.begin()+x);
				player1.items.il_change=true;
			} 
						void player_shoot_laser_beam(position_3D pos,int dir,int d=4){
		 					position_3D npos=pos;
			 				npos=dtp3(npos,dir,d);
			 				bool hit=false;//是否命中敌人
							player1.scr.shoot_times++;
			 				while(1){
			 					if(!pos_in_area2(npos.x,npos.y,1,1,length,width,2)) return;
			 					if(!light_through(npos))//激光可以穿过就继续计算
									return;
			 					MAP &NPOS=game_map[npos.x][npos.y][npos.z];
								if(NPOS.player_enemy==PLAYER) return;
			 					thing &THING=NPOS.things;
			 					THING.lsr.exist=true;THING.lsr.laser_beam=dir;
								laser_beams.push(npos);
			 					if(NPOS.in_player_sight==lst_see_time) pos_change.push(npos);
			 					if(nobody_here(npos)&&THING.nst.exist&&THING.nst.id!=-1){//命中虫子的巢穴口
			 						position_3D npos2=THING.nst.to;
			 						MAP &NPOS2=game_map[npos2.x][npos2.y][npos2.z];
			 						thing &THING2=NPOS2.things;
								 	nest &NST=THING.nst,&NST2=THING2.nst;
								 	int id=NST.id;
								 	bug_nest &bns=bug_nests[id];
								 	bns.lfin.life--;bns.lfin.change=2;
								 	if(bns.lfin.life<=0){
								 		NST.exist=false;
										NST.id=-1;
										NST2.exist=false;
										NST2.id=-1;
									}
								}
								if(THING.mirrors.exist){//碰到镜子就反射 
									mirror &MIRROR=THING.mirrors;
									int d1=turn(dir,TURN_LEFT),d2=turn(dir,TURN_RIGHT),d3=MIRROR.dir;
									if(MIRROR.side==1){
										if(dir==d3) player_shoot_laser_beam(npos,d2);
										else if(d2==d3) player_shoot_laser_beam(npos,d1);
									}
									else{
										if(dir%2==d3) player_shoot_laser_beam(npos,d2);
										else player_shoot_laser_beam(npos,d1);
									}
									return;
								}
			 					npos=dtp3(npos,dir,d);
							}
						}
					void player_use_laser_gun012(){
						weapon &wpn=player1.items.wpn;
						laser_gun &lsg=wpn.lsg;
						position_3D npos=dtp3(player1.pos,player1.d,4);
						if(light_through(npos)){//至少有1格距离可以射 
							game_timer["清除激光束"]=game_time+lsg.last_time;game_timer["激光枪冷却"]=game_timer["清除激光束"]+lsg.cool_time;
							lsg.energy--;
							wpn.data_change=true; 
							player1.use_weapon=true;
							player_shoot_laser_beam(player1.pos,player1.d);
						}
						if(lsg.kind==1){
							int d2=turn(player1.d,TURN_LEFT),d3=turn(player1.d,TURN_RIGHT);
						 	position_3D npos2=dtp3(player1.pos,d2,4),npos3=dtp3(player1.pos,d3,4);
							if(light_through(npos2)){//至少有1格距离可以射 
								game_timer["清除激光束"]=game_time+lsg.last_time;game_timer["激光枪冷却"]=game_timer["清除激光束"]+lsg.cool_time;
								lsg.energy--;
								wpn.data_change=true; 
						 		player1.use_weapon=true;
								player_shoot_laser_beam(npos2,player1.d);
							}
							if(light_through(npos3)){//至少有1格距离可以射 
						 		game_timer["清除激光束"]=game_time+lsg.last_time;game_timer["激光枪冷却"]=game_timer["清除激光束"]+lsg.cool_time;
						 		lsg.energy--;
								wpn.data_change=true; 
								player1.use_weapon=true;
								player_shoot_laser_beam(npos3,player1.d);
							}
						}
					  	else if(lsg.kind==2){
					 	}
					}
				void player_use_laser_gun(){
					weapon &wpn=player1.items.wpn;
					laser_gun &lsg=wpn.lsg;
					switch(lsg.kind){
						case 0:case 1:case 2:
							player_use_laser_gun012();
							break;
						case 3:
							for(int i=0;i<4;i++){
								position_3D npos=dtp3(player1.pos,i,4);
								if(light_through(npos)){//至少有1格距离可以射 
									game_timer["清除激光束"]=game_time+lsg.last_time;game_timer["激光枪冷却"]=game_timer["清除激光束"]+lsg.cool_time;
									lsg.energy--;
									wpn.data_change=true; 
									player1.use_weapon=true;
									player_shoot_laser_beam(player1.pos,i);
								}
							}
							break;
						case 4:
							break;
					}
				}
			    void player_use_dart(int dir){//生成扔出的飞镖并加入飞镖队列 
					flying_dart fdt;
					dart &DRT=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things.drt; 
					weapon &wpn=player1.items.wpn;
					throwing_dart &drt=wpn.drt;
					fdt.init(player1.pos,dir);
					darts.push(fdt);
					DRT.num[1]++;DRT.d[1]=fdt.d;
					player1.scr.shoot_times++;
					drt.num--;wpn.data_change=true;
					game_timer["扔飞镖冷却"]=game_time+200;
				}
			void player_use_weapon(){
				weapon &wpn=player1.items.wpn;
				laser_gun &lsg=wpn.lsg;
				throwing_dart &drt=wpn.drt;
				switch(wpn.select_wpn){
					case LSG:
						//lsg.energy+=8;
						if(lsg.energy>=lsg.kd_energy[lsg.kind]&&game_timer["激光枪冷却"]<=game_time) player_use_laser_gun();
						break;
					case DART:
						if(drt.num>0&&game_timer["扔飞镖冷却"]<=game_time
						&&!game_map[player1.pos.x][player1.pos.y][player1.pos.z].things.drt.exist1()) player_use_dart(player1.d);
						break;
				}
 			}
				    void player_erase_spear(){//清理上次显示的矛 
			    		while(!spears.empty()){
			    			position_3D u=spears.front();spears.pop();
			    			if(game_map[u.x][u.y][u.z].in_player_sight==lst_see_time)
								pos_change.push(u),game_flag["玩家矛改变位置"]=true;
				    		MAP &POS=game_map[u.x][u.y][u.z];
				    		POS.things.spr.exist=false;
				    	}
				    }
				    void player_use_spear(position_3D pos,int dir,int length){ 
						weapon &wpn=player1.items.wpn;
			    		position_3D npos=dtp3(pos,dir,4),lpos=pos;
			    		int i=1;
			    		if(!(wall_here(npos)||door_here(npos,0)||i>length)){
							game_flag["玩家矛改变位置"]=true;
							//wpn.hsr.endurance--;
							//wpn.data_change=true; 
						}
			    		while(1){
			    			MAP &POS=game_map[npos.x][npos.y][npos.z];
			        		if(wall_here(npos)||door_here(npos,0)||i>length){//矛碰到墙或矛的长度不够 
			    				MAP &LPOS=game_map[lpos.x][lpos.y][lpos.z];
			    				if(i!=1) LPOS.things.spr.head=true;
			        			break;
						    }
				    		thing &THING=POS.things;
				    		spear &spr=THING.spr;
				    		spr.exist=true;spr.d=dir;spr.head=false;
				    		pos_change.push(npos);spears.push(npos);
				    		lpos=npos;npos=dtp3(npos,dir,4);i++;
				    	}
			    	}
			void player_update_spear(){//矛自动更新
				player_erase_spear();
				if(player1.items.wpn.hsr.endurance>0) player_use_spear(player1.pos,player1.d,2); 
			}
		void player_detect_move(){
			int maze;
			vector<int> &v=player1.items.item_lab;
			position_3D npos;
			npos=player1.pos;
			thing &THING=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things;
			int d=-1;
			if(_kbhit()){
				switch(_getch()){//侦测按键 
					case PRESS_KEY_UP:
						d=0;
						break;
					case PRESS_KEY_RIGHT:
						d=1;
						break;
					case PRESS_KEY_DOWN:
						d=2;
						break;
					case PRESS_KEY_LEFT:
						d=3;
						break;
					case PRESS_KEY_SPACE:
						maze=game_map[player1.pos.x][player1.pos.y][player1.pos.z].maze;
						if(!player1.up_down&&(UPSTAIR<=maze&&maze<=DOWNSTAIR||THING.nst.exist)){//玩家想上下楼或进出巢穴口 
							THING.fpt.d=4;//记录足迹
							if(maze==UPSTAIR) npos.z++;
							else if(maze==DOWNSTAIR) npos.z--;
							else npos=THING.nst.to;
						}
						else{
							player1.up_down^=1;
							player1.ud_change=true;
						}
						break;
					case PRESS_KEY_F:
						player1.action_kind=CHOOSE_ITEM;player1.ak_change=true;
						return;
					case PRESS_KEY_E:
						player_use_item();
						return;
					case PRESS_KEY_V:
						if(player1.action_kind==RUN) player1.action_kind=WALK;
						else player1.action_kind=RUN;
						player1.ak_change=true;
						break;
					case PRESS_KEY_S:
						player_use_weapon();
						return;
					case PRESS_KEY_ENTER:
						game_pause=!game_pause;
						game_flag["游戏暂停/继续"]=true; 
						return;
				}
			}
			if(d!=-1){
				if(d==player1.d&&player1.action_kind==WALK||player1.action_kind==RUN){//状态是【行走】转弯时要按两下 
					THING.fpt.d=d;//记录足迹
					npos.x+=dx4[d];
					npos.y+=dy4[d];
				}
			}
			else if(!player1.lst_ud&&stair_here(npos)&&player1.up_down){
				player1.lst_ud=true;//防止卡住
				THING.fpt.d=4;//记录足迹
				if(game_map[npos.x][npos.y][npos.z].maze==UPSTAIR) npos.z++;
				else npos.z--;
			}
			else if(!player1.lst_enter&&THING.nst.exist&&player1.up_down){
				player1.lst_enter=true;//防止卡住
				THING.fpt.d=4;//记录足迹
				npos=THING.nst.to;
			}
			if(player1.pos!=npos){//必须是改变了位置 
				int nmaze=game_map[npos.x][npos.y][npos.z].maze;
				if(!nobody_here(npos)){//这里有别的生物
					player_reduce_blood(10.0/player1.vlc.speed);
					if(game_map[npos.x][npos.y][npos.z].player_enemy==BUG&&game_map[npos.x][npos.y][npos.z].emy.id!=-1){
						int id=game_map[npos.x][npos.y][npos.z].emy.id;
						bug &bg=bugs[id];
						bg.lfin.life++;bg.lfin.change=1;//虫子吸血 
					}
				}
				else if(nmaze==SPACE||nmaze==EXIT//这里是空地、出口
				||(DOOR1<=nmaze&&nmaze<=DOOR4&&game_map[npos.x][npos.y][npos.z].door_state)//或开着的门  
				||(UPSTAIR<=nmaze&&nmaze<=DOWNSTAIR)//或者楼梯
				){
					game_map[player1.pos.x][player1.pos.y][player1.pos.z].player_enemy=NOBODY;
					game_map[npos.x][npos.y][npos.z].player_enemy=PLAYER;
					player1.move=1;
					if(nmaze==EXIT){
						game_end=game_success=true;
						return;
					}
				}
				else if(DOOR1<=nmaze&&nmaze<=DOOR4//这门关了
				&&player1.items.keys.door_keys[nmaze-DOOR1]>=1){//但我有钥匙 
					game_map[player1.pos.x][player1.pos.y][player1.pos.z].player_enemy=NOBODY;
					game_map[npos.x][npos.y][npos.z].player_enemy=PLAYER;
					game_map[npos.x][npos.y][npos.z].door_state=true;
					int &dk=player1.items.keys.door_keys[nmaze-DOOR1+KEY1-1];
					dk--;player1.items.num_change=true;
					if(dk==0){
						v.erase(find(v.begin(),v.end(),nmaze-DOOR1+K1));
						player1.items.il_change=true;
					} 
					player1.move=1;
				}
			}
			if(player1.move) player1.pos=npos;
			if(d!=-1&&player1.d!=d){
				if(!player1.move) player1.flash=true,pos_change.push(player1.pos);
				player1.d_change=true;player1.d=d;
			}
			if((player1.d_change||player1.move)&&player1.items.wpn.select_wpn==SPR) player_update_spear();
			if(!stair_here(player1.pos)) player1.lst_ud=false;
			if(!THING.nst.exist) player1.lst_enter=false;
		}
			void player_check_key(thing &THING,item &items,vector<int> &v){//捡到钥匙 
				int &nkey=THING.key;
				int &dk=items.keys.door_keys[nkey-KEY1];
				if(nkey){
					if(!dk){
						v.push_back(nkey-KEY1+K1);
						items.il_change=true;
					} 
					dk++;items.num_change=true;
					nkey=0; 
				}
			}
			void player_check_food(thing &THING,item &items,vector<int> &v){//捡到食物 
				food &nfood=THING.foods;
				bool &nexist=nfood.exist;
				if(nexist){
					int& nkind=nfood.kind,neffect=nfood.effect;
					int &fc=items.foods.food_cnt[nkind-ADDS][neffect-1];
					if(!fc){
						v.push_back(AS1+(nkind-1)*EFFECT_OF_FOOD+(neffect-1));
						items.il_change=true;
					} 
					fc++;items.num_change=true;
					nexist=nkind=neffect=0; 
				}
			}
			void player_check_wpn_energy_edc(thing &THING,item &items){//获得武器耐久度回复 
				weapon_energy_edc &wee=THING.wee;
				int &ly=items.wpn.lsg.energy,&hec=items.wpn.hsr.endurance,&num=wee.num,&kind=wee.kind;
				bool &dc=items.wpn.data_change,&ex=wee.exist;
				if(ex){
					switch(kind){
						case 0:ly+=num;num=ex=0;dc=1;break;
						case 1:hec+=num;num=ex=0;dc=1;break;
					}
				}
			}
			void player_check_wpn(thing &THING,item &items){//捡到武器
				dart &DRT=THING.drt;
				weapon &wpn=items.wpn;
				int &dnum=wpn.drt.num;
				if(DRT.exist0()){//地上的飞镖 
					dnum+=DRT.num[0];
					DRT.num[0]=0;
					wpn.data_change=true;
				}
			}
		void player_check_thing(){//玩家捡拾物品 
			thing &THING=game_map[player1.pos.x][player1.pos.y][player1.pos.z].things;
			if(THING.nothing()) return;//这里没东西直接退出 
			item &items=player1.items;
			vector<int> &v=items.item_lab;
			player_check_key(THING,items,v);
			player_check_food(THING,items,v);
			player_check_wpn_energy_edc(THING,items);
			player_check_wpn(THING,items);
		}
		void player_choose_item(){
			if(_kbhit()){
				switch(_getch()){//侦测按键 
					case PRESS_KEY_DOWN:
						player1.action_kind=CHANGE_WPN;
						player1.ak_change=true;
						break;
					case PRESS_KEY_RIGHT:
						player1.items.select_number=min(player1.items.select_number+1,9);
						player1.items.sn_change=true;
						break;
					case PRESS_KEY_LEFT:
						player1.items.select_number=max(player1.items.select_number-1,0);
						player1.items.sn_change=true;
						break;
					case PRESS_KEY_F:
						player1.action_kind=RUN;player1.ak_change=true;
						break;
					case PRESS_KEY_E:
						player_use_item();
						break;
					case PRESS_KEY_V:
						player1.action_kind=WALK;
						player1.ak_change=true;
						break;
					case PRESS_KEY_ENTER:
						game_pause=!game_pause;
						game_flag["游戏暂停/继续"]=true; 
						return;
				}
			}
		}
			void player_weapon_mode(){//更改武器模式 
				item &items=player1.items;
				weapon &wpn=items.wpn;
				laser_gun &lsg=wpn.lsg;
				switch(wpn.select_wpn){
					case LSG:
						lsg.kind=(lsg.kind+1)%lsg.kd_cnt;
						wpn.mode_change=true;
						break;
				}
			}
		void player_update_weapon(){//更新武器 
			item &items=player1.items;
			weapon &wpn=items.wpn;
			if(_kbhit()){
				switch(_getch()){//侦测按键 
					case PRESS_KEY_UP:
						player1.action_kind=CHOOSE_ITEM;
						player1.ak_change=true;
						break;
					case PRESS_KEY_RIGHT:
						wpn.select_wpn=(wpn.select_wpn+1)%wpn.wcnt;
						wpn.sw_change=true;
						break;
					case PRESS_KEY_LEFT:
						wpn.select_wpn=(wpn.select_wpn-1+wpn.wcnt)%wpn.wcnt;
						wpn.sw_change=true;
						break;
					case PRESS_KEY_SPACE:
						player_weapon_mode();
						break;
					case PRESS_KEY_F:
						player1.action_kind=RUN;player1.ak_change=true;
						break;
					case PRESS_KEY_E:
						player_use_item();
						break;
					case PRESS_KEY_V:
						player1.action_kind=WALK;
						player1.ak_change=true;
						break;
					case PRESS_KEY_ENTER:
						game_pause=!game_pause;
						game_flag["游戏暂停/继续"]=true; 
						return;
				}
				if(wpn.sw_change){//自动更新 
					player_erase_spear();
					if(wpn.select_wpn==SPR) player_use_spear(player1.pos,player1.d,2);
				}
			}
		}
		void player_lfin_update(){
			if(player1.color!=0){
				player1.flash=true;
				pos_change.push(player1.pos);
			}
			if(player1.move){
				player1.vts.stg.change=1;
				player1.vts.stg.physical_strength--;
				if(player1.vts.stg.physical_strength<0) player1.vts.stg.physical_strength=0;
				game_timer["玩家体力恢复"]=max(game_timer["玩家体力恢复"],game_time+player1.vts.stg.recovery_time);
			}
			else if(game_timer["玩家体力恢复"]<=game_time&&player1.vts.stg.physical_strength<100){
			//体力恢复时间已到 
				player1.vts.stg.change=1;
				player1.vts.stg.physical_strength++;
				game_timer["玩家体力恢复"]+=player1.vts.stg.recovery_time;
			}
			player1.vlc.speed=pow(player1.vts.stg.physical_strength,2)/double(100);player1.vlc.vt();
		}
		void player_sight_update(){
			if(player1.move||player1.ud_change||game_flag["虫子挖地道"]){
				player_calculate_vision2(player1.pos);
				player_calculate_vision1();
				lst_see_time=game_time;//计算视野 
			}
		}
		void player_others(){//其他杂碎 
			if(player1.items.wpn.hsr.endurance==0) player_erase_spear();//矛的耐久度用光自动删除 
		}
	void deal_player(){
		switch(player1.action_kind){
			case RUN:case WALK:
				if(game_timer["玩家移动"]<=game_time){//玩家移动时间已到 
					player_detect_move();
					player_check_thing();
					game_timer["玩家移动"]+=player1.vlc.wait_time;
				}
				break;
			case CHOOSE_ITEM:
				player_choose_item();
				break;
			case CHANGE_WPN:
				player_update_weapon();
				break;
		}
		player_lfin_update();
		player_sight_update();
		player_others();
	}
		void shoot_laser_beam(){//清除激光束 
			if(laser_beams.size()&&game_timer["清除激光束"]<=game_time){
				player1.use_weapon=true;
				while(!laser_beams.empty()){
					position_3D u=laser_beams.front();laser_beams.pop();
					MAP &POS=game_map[u.x][u.y][u.z];
					POS.things.lsr.exist=false;
					if(POS.in_player_sight==lst_see_time) pos_change.push(u);
					if(!POS.things.nst.exist||POS.things.nst.id==-1) continue;
					bug_nest &bgn=bug_nests[POS.things.nst.id];
					if(bgn.lfin.change!=0) bgn.lfin.change=0;//巢穴被击中的闪烁停止 
				}
			}
		}
		void clean_dead(){//清除尸体 
			while(!pos_dead.empty()){
				position_3D u=pos_dead.front();
				MAP &POS=game_map[u.x][u.y][u.z];
				if(POS.emy.body_disapp>game_time) return;//最早的尸体还没到清理时间，接下来的不用看了
				if(POS.in_player_sight=lst_see_time){
					pos_change.push(u);
					game_flag["清除尸体"]=true;
				}
				pos_dead.pop(); 
			}
		}
			void dart_fall(position_3D pos){//飞镖落下 
				MAP &POS=game_map[pos.x][pos.y][pos.z];
				dart &DRT=POS.things.drt;
				DRT.num[1]--;
				DRT.num[0]++;DRT.d[0]=RAND(3,0);
				if(POS.in_player_sight==lst_see_time){//更新屏幕 
					game_flag["飞镖变化"]=true;
					pos_change.push(pos); 
				}
			}
		void throw_dart(){//飞镖飞行 
			int num=darts.size();
			if(num==0) return;
			while(num--){
				flying_dart fdt=darts.front();darts.pop();
				MAP &POS=game_map[fdt.pos.x][fdt.pos.y][fdt.pos.z];
				dart &DRT=POS.things.drt;
				if(fdt.time<=game_time) fdt.time=game_time+fdt.vlc.wait_time;
				else{//没到移动时间 
					darts.push(fdt);
					continue;
				}
				/* 
				if(enemy_here(fdt.pos)){
					dart_fall(fdt.pos);
					continue;//碰到敌人就停止飞行 
				}*/
				position_3D npos=dtp3(fdt.pos,fdt.d,4);//下一个地方 
				MAP &NPOS=game_map[npos.x][npos.y][npos.z];
				dart &NDRT=NPOS.things.drt;
				if(pos_in_area2(npos.x,npos.y,1,1,length,width,2)&&!(wall_here(npos)||door_here(npos,0))){
					if(game_map[fdt.pos.x][fdt.pos.y][fdt.pos.z].in_player_sight==lst_see_time){//更新屏幕 
						game_flag["飞镖变化"]=true;
						pos_change.push(fdt.pos); 
					}
					if(game_map[npos.x][npos.y][npos.z].in_player_sight==lst_see_time){//更新屏幕 
						game_flag["飞镖变化"]=true;
						pos_change.push(npos); 
					}
					DRT.num[1]--;
					fdt.pos=npos;
					NDRT.num[1]++;NDRT.d[1]=fdt.d;
					darts.push(fdt);//重新放回队列 
				}
				else dart_fall(fdt.pos);//碰到墙或关上的门就停止飞行
			}
		}
		void open_close_treasure(){
		}
		void on_off_candle(){
		}
		void move_barrel(){
		}
		void on_off_lamp(){
		}
		void delay_boom_TNT(){
		}
		void pour_water(){
		}
		void pour_magma(){
		}
	void deal_item(){
		shoot_laser_beam();
		clean_dead(); 
		throw_dart();
		open_close_treasure();
		on_off_candle();
		move_barrel();
		on_off_lamp();
		delay_boom_TNT();
		pour_water();
		pour_magma();
	}
		void game_map_update(){//更新显示在屏幕上的游戏地图 
			if(player1.move||player1.ud_change||game_flag["虫子挖地道"]){
			//玩家移动或是否通过楼梯看改变了或虫子在视线范围内挖了地道 
				game_flag["虫子挖地道"]=false; 
				while(!pos_lst_sight.empty()){//先处理上次显示到屏幕的 
					position_2D spos=pos_lst_sight.front();pos_lst_sight.pop();
					if(!screen_z.count(spos)){
						formatted_output(1,game_map_area,spos.x,spos.y,0x00,"  ");//清空屏幕上这个位置 
						if(screen_pos.count(spos)) screen_pos.erase(spos);//屏幕上这个位置的显示内容编码用不上了，删掉 
						continue;
					}
					position_3D npos=position_scrto3D(spos,screen_z[spos]);
					//屏幕坐标转化为游戏地图坐标，z坐标换成现在屏幕上对应位置要显示的楼层
					string ncode=screen_display_coding(npos);
					if(ncode!=screen_pos[spos]){//现在要显示的内容编码和上次不同
						print_game_map_pos(npos);//输出新的内容 
						screen_pos[spos]=ncode;//屏幕上这个位置的显示内容编码更新 
					}
					pos_backup.push(spos);//把屏幕上这个位置放到备份队列里
				}
				while(!pos_in_sight.empty()){//再处理现在新显示到屏幕的 
					position_3D npos=pos_in_sight.front();pos_in_sight.pop();
					position_2D spos=position_3Dtoscr(npos);//npos在屏幕上的对应位置 
					print_game_map_pos(npos);//输出 
					screen_pos[spos]=screen_display_coding(npos);//新增这个位置的屏幕信息
					pos_backup.push(spos);//把这个位置放到备份队列里 
				}
				while(!pos_backup.empty()){//备份队列的内容全部copy到上次显示到屏幕的（给下回合用） 
					pos_lst_sight.push(pos_backup.front()); 
					pos_backup.pop();
				}
				formatted_output(1,vital_signs_area,1,6,0x0f,"1");
			}
			else if(player1.enemy_move||player1.flash||player1.use_weapon
			||game_flag["虫子被玩家攻击"]||game_flag["清除尸体"]||game_flag["玩家矛改变位置"]||game_flag["飞镖变化"]){
			//玩家没移动，显示的游戏地图可能有别的变化（比如突然冒出一个鬼），特殊处理
				while(!pos_change.empty()){
					position_3D npos=pos_change.front();pos_change.pop();
					position_2D spos=position_3Dtoscr(npos);//npos在屏幕上的对应位置 
					print_game_map_pos(npos);//输出 
					screen_pos[spos]=screen_display_coding(npos);//新增这个位置的屏幕信息
					pos_lst_sight.push(spos);//添加到上次显示到屏幕的（给下回合用）
				}
				formatted_output(1,vital_signs_area,1,6,0x0f,"2");
			}
			else formatted_output(1,vital_signs_area,1,6,0x0f,"0");
			if(player1.d_change){//玩家方向改变 
				string s;
				switch(player1.d){
					case 0:s="↑";break;
					case 1:s="→";break;
					case 2:s="↓";break;
					case 3:s="←";break;
				}
				game_map_area.output_frame(s,0x0f,0);
			}
		}
			void lives_update(){//玩家生命体征更新 
				if(player1.vts.lfin.change||player1.d_change||player1.items.sn_change){
					if(player1.vts.lfin.life<10) formatted_output(1,vital_signs_area,1,1,0x0c,"生命垂危！");
					else formatted_output(1,vital_signs_area,1,1,0x0c
						,connect_str("生命值：",repeat_char(char(3),(player1.vts.lfin.life+5)/10.0),"          "));
				}
				if(player1.vts.stg.change||player1.d_change||player1.items.sn_change){
					formatted_output(1,vital_signs_area,1,2,0x0a
					,connect_str("体力值：",int_to_str(player1.vts.stg.physical_strength),"%  "));
					if(player1.vts.stg.physical_strength<25)
						formatted_output(1,vital_signs_area,14,2,0x0a,"体力告急！");
					else formatted_output(1,vital_signs_area,14,2,0x0a,"          ");
				}
			}
			void weapon_update(){//武器状态更新 
				if(player1.ak_change||player1.items.wpn.data_change||player1.items.wpn.sw_change) player1.items.wpn.print1();
				if(player1.items.wpn.mode_change||player1.items.wpn.sw_change) player1.items.wpn.print2();
				if(player1.items.wpn.sw_change) player1.items.wpn.print3();
			}
			void score_update(){//分数更新 
				if(player1.scr.kc_change)
					formatted_output(1,vital_signs_area,1,3,0x0e
					,connect_str("击杀数：",int_to_str(player1.scr.kill_count)));
			}
			void state_update(){//玩家状态更新 
				if(player1.ud_change||player1.d_change||player1.items.sn_change){
					if(player1.up_down)
						formatted_output(1,vital_signs_area,1,4,0x0f,"自动上下楼（可查看楼上/下的场景）");
					else formatted_output(1,vital_signs_area,1,4,0x0f,"手动（按空格键）上下楼           ");
				}
				if(player1.ak_change||player1.d_change||player1.items.sn_change)
					switch(player1.action_kind){
						case RUN:formatted_output(1,vital_signs_area,1,5,0x0b,"奔跑    ");break;
						case WALK:formatted_output(1,vital_signs_area,1,5,0x0b,"行走    ");break;
						case CHOOSE_ITEM:formatted_output(1,vital_signs_area,1,5,0x0b,"选择物品");break;
						case CHANGE_WPN:formatted_output(1,vital_signs_area,1,5,0x0b,"切换武器");break;
					}
				if(game_flag["游戏暂停/继续"]) formatted_output(1,vital_signs_area,1,24,0x0f,(game_pause?"游戏暂停":"        "));
			}
		void vital_signs_update(){
			lives_update();
			weapon_update();
			score_update();
			state_update();
		}
		void item_update(){
			if(player1.ak_change||player1.items.num_change||player1.items.il_change||player1.items.sn_change)
				player1.items.print1();
			if(player1.items.il_change) player1.items.print2();
			if(player1.items.sn_change) player1.items.print3();
		}
	void screen_update(){//屏幕更新 
		game_map_update();
		vital_signs_update();
		item_update();
	}
		void judge_win_lose(){
		}
		void delay_time(){//延时1毫秒 
			SLEEP(1);
			game_time=clock()-start_time;
		}
	void others(){
		judge_win_lose();
		delay_time();
	}
void game(){//游戏部分 
	//此前不要清屏 
	game_time=1;start_time=clock();
	while(!game_end){
		assigned();
		pause();
		if(game_pause) continue;
		deal_enemy();
		deal_player();
		deal_item();
		screen_update();
		others();
	}
} 
void win(){
	score &scr=player1.scr;
	formatted_output(2,whole_screen,40,19,0x0a,
	connect_str("你赢了，",player1.name,"！！！（耗时",to_time(0,0,scr.time_spent/1000),"）"),1,150);
} 
void lose(){
	score &scr=player1.scr;
	formatted_output(2,whole_screen,40,19,0x0c,
	connect_str("你输了，",player1.name,"……（存活",to_time(0,0,scr.time_spent/1000),"）"),1,150);
}
void detail(){//详细游戏信息整理展示 
	int col=0;
	if(game_success) col=0x0a;
	else col=0x09;
	score &scr=player1.scr;
	formatted_output(2,whole_screen,40,20,col,"详细信息：",1,150);
	if(scr.shoot_times!=0) scr.hit_rate=scr.shoot_hit_times*1.0/scr.shoot_times;//
	else scr.hit_rate=0;
	formatted_output(2,whole_screen,40,21,col,
	connect_str("击杀数：",int_to_str(scr.kill_count)," 射击命中率：",double_to_str(scr.hit_rate*100,1),"%")
	,1,150);//
	formatted_output(2,whole_screen,40,22,col,
	connect_str("遭受攻击次数：",int_to_str(scr.hurt_times)
	," 失去生命值：",int_to_str(player1.vts.lfin.hurt),"% 回复生命值：",int_to_str(player1.vts.lfin.recovery),"%")
	,1,150);
}
void ask_try_again(){
	formatted_output(2,whole_screen,40,23,0x07,"按下回车重新开始",1,150);
	wait_until(PRESS_KEY_ENTER);
	formatted_output(2,whole_screen,40,23,0x0b,"游戏加载中......",1,100);
	start_again=true; 
}
void end(){//暂时不用 
	//此前要清屏 
	formatted_output(2,whole_screen,40,20,0x0e,connect_str(player1.name,"，欢迎下次再来！"),1,150);
}
//函数定义 

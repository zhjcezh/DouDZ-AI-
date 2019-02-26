#include <iostream>
#include <string>
#include "class.h"
#include "JLW_time.h"
//#include "JLW_Verification.h"
//#pragma comment(lib,"JLW_Verification_Time.lib")

using namespace std;

#if 1

#define RUN_ACCESS_CONTROL

int main()
{
	//#ifdef RUN_ACCESS_CONTROL
	//	// 初始化标志符
	//	static bool s_IsNotInit_Flag = true, s_IsRight = false;
	//	static int s_Init_count = 0;

	//	if (++s_Init_count > 3000000)
	//	{
	//		s_Init_count = 0;
	//		s_IsNotInit_Flag = true;
	//		s_IsRight = false;
	//	}
	//	if (s_IsNotInit_Flag)
	//	{
	//		s_IsRight = isInPeriodOfValidity("20170623201707150030");
	//		s_IsNotInit_Flag = false;
	//	}
	//#endif


	//#ifdef RUN_ACCESS_CONTROL
	//	if (!s_IsRight)
	//	{
	//		//初始化或认证分数屏蔽
	//		//	similarity = 0.0;
	//		cout << "授权失败" << endl;
	//		system("pause");
	//		return 0;
	//	}
	//#endif

	

	while (true)
	{
		int n, temp, Index;
		int a[20];
		//初始化
		for (int i = 0; i < 20; ++i)
		{
			a[i] = 0;
		}
		//
		n = 17;
		cout << "请输入AI的17张手牌，用空格隔开：" << endl;
		for (int j = 0; j < n; ++j)
		{
			cin >> temp;
			a[temp]++;
		}
		card test1(a);
		int ss = test1.ScoreOfDZ();//-1  1  2
		if(ss == -1)
		{
			cout<<"不抢"<<endl;
		}
		else if(ss == 1)
		{
			cout<<"可抢"<<endl;
		}
		else
		{
			cout<<"必抢"<<endl;
		}
		cout << "请输入地主位置(-1,1,2):";//1为自己是地主，2代表自己出完地主出，1代表地主出玩自己出//自己在1，下家2，上家-1
		cin>>Index;
		if(Index == 1)
		{
			cout<<"请输入底牌三张底牌，用空格隔开："<<endl;
			for(int i = 0;i < 3;++i)
			{
				int temp;
				cin>>temp;
				a[temp]++;
			}
		}
		card test(a);
		test.CaLL(Index);
		int round = 0;
		int active;
		int fn=0;
		int bn=0;
		int my = 17;
		int sum = 0;
		while(true)
		{
			int Out[30], out[30];
			vector<int> vc;
			for (int i = 0; i < 30; ++i)
			{
				out[i] = -1;
				Out[i] = -1;
			}
			if(round == 0 && Index ==1)
			{
				active = 1;
				my = 20;
			}
			else
			{
				cout<<"请输入主动or被动模式"<<endl;
				cin>>active;
			}
			int kind, len;
			//***************************被动出牌(要压别人排)***************//
			int IsRes = 0;
			if(active == 0)
			{
				int lastCards[100];
				cout << "请输入前前手出牌的牌数：";
				int lastN1; cin >> lastN1;
				if(lastN1>0)
				{
					cout << "请输入手牌：";
				}
				for (int l = 0; l < lastN1; l++)
				{
					cin>>lastCards[l];
				}
				if(lastN1 > 0)
				{
					test.UpdateC(lastCards,lastN1,1);
				}
				//*****
				cout << "请输入前一手出牌的牌数：";
				int lastN2; cin >> lastN2;
				if(lastN2 > 0)
				{
					cout << "请输入手牌：";
				}
				for (int l = 0; l < lastN2; l++)
				{
					cin>>lastCards[l];
				}
				if(lastN2 > 0)
				{
					test.UpdateC(lastCards,lastN2,-1);
				}
				if(lastN2 > 0)
				{
					int lc[30];
					memset(lc, 0, sizeof(lc));
					for(int i=0;i<lastN2;i++)
					{
						lc[lastCards[i]]++;
					}

					card midtemp(lc);
					midtemp.InToOut(out);
					if(Index == 2)
						IsRes = test.PassivePlay(out, Out, 1);
					else
					{
						IsRes = test.PassivePlay(out, Out, -1);
					}
				}
				else if(lastN1 > 0)
				{
					int lc[30];
					memset(lc, 0, sizeof(lc));
					for(int i=0;i<lastN1;i++)
					{
						lc[lastCards[i]]++;
					}
					card midtemp(lc);
					midtemp.InToOut(out);
					if(Index == 2)
					{
						IsRes = test.PassivePlay(out, Out, -1);
					}
					else
					{
						IsRes = test.PassivePlay(out, Out, 1);
					}
				}
			}
			//***************************主动出牌(之前的排别人压不了)***************//
			else
			{
				IsRes = 1;
				test.ActivePlay(Out);
			}
			
			kind = Out[2];
			len = Out[1];
			int mcard[30];
			int temp = 0;
			if (Out[2] == -1 || IsRes == -1)
			{
				cout << "要不起" << endl;
				continue;
			}
			vc.clear();
			test.Sort(Out,vc);
			//  单
			for (int i = 0; i < vc.size(); i++)
			{
				cout << vc[i] << " ";
				mcard[i] = vc[i];
				temp++;
			}
			cout << endl;
			test.UpdateC(mcard, temp, 0);
			test.SortTheCard();
			round++;
			sum += temp;
			if (my == sum)
			{
				cout << "赢了" << endl << endl;
				break;
			}
		}			
	}
	system("pause");
	return 0;
}
#else

int main()
{
	#ifdef RUN_ACCESS_CONTROL
		// 初始化标志符
		static bool s_IsNotInit_Flag = true, s_IsRight = false;
		static int s_Init_count = 0;

		if (++s_Init_count > 3000000)
		{
			s_Init_count = 0;
			s_IsNotInit_Flag = true;
			s_IsRight = false;
		}
		if (s_IsNotInit_Flag)
		{
			s_IsRight = isInPeriodOfValidity("20170623201707150030");
			s_IsNotInit_Flag = false;
		}
	#endif


	#ifdef RUN_ACCESS_CONTROL
		if (!s_IsRight)
		{
			//初始化或认证分数屏蔽
			//	similarity = 0.0;
			cout << "授权失败" << endl;
			system("pause");
			return 0;
		}
	#endif

	while (true)
	{
		int n, n1, n2, temp, Index;
		int a[20], b[20], c[20];
		//初始化
		for (int i = 0; i < 20; ++i)
		{
			a[i] = b[i] = c[i] = 0;
		}
		// 
			cout << "请输入AI牌数：";
			cin >> n;
			cout << "请输入AI的手牌，用空格隔开：" << endl;
			for (int j = 0; j < n; ++j)
			{
				cin >> temp;
				a[temp]++;
			}	
			cout << "请输入AI后家牌数：";
			cin>>n1;
			cout << "请输入AI前家牌数：";
			cin>>n2;
			cout<<"请输入外面剩余的牌，用空格隔开：";
			for (int i = 0; i < n1; ++i)
			{
				cin>>temp;
				b[temp]++;
			}
			for (int i = 0; i < n2; ++i)
			{
				cin>>temp;
				c[temp]++;
			}
		cout << "请指定地主位置(-1,1,2)：";
		cin >> Index;//指定地主位置，如果是1，则为自己
		cout << endl;
		/*for (int i = 3; i < 18; ++i)
		{
			cout << a[i] << ' ' << b[i] << ' ' << c[i] << endl;
		}
		cout << endl << endl;*/
		card test(a, b, c, Index);
		cout << "主动模式or被动模式（1/0):";
		int active; cin >> active;
		int Out[30], out[30];
		for (int i = 0; i < 30; ++i)
		{
			out[i] = -1;
			Out[i] = -1;
		}
		//***************************被动出牌***************//
		int IsRes = 0;
		if (active == 0)
		{
			cout << "请输入前一手出牌的牌数：";
			int lastN; cin >> lastN;
			int lastCards[30];
			memset(lastCards, 0, sizeof(lastCards));
			cout << "请输入前一手牌：";
			for (int l = 0; l < lastN; l++)
			{
				int temp;
				cin >> temp;
				lastCards[temp]++;
			}
			card midtemp(lastCards);
			midtemp.InToOut(out);
			
			

			IsRes = test.PassivePlay(out, Out, -1);
		}
		//***************************主动出牌***************//
		else
		{
			IsRes = 1;
			test.ActivePlay(Out);
		}

		if (Out[2] == -1 || IsRes == -1)
		{
			cout << "要不起" << endl;
		}
		//  单
		else if (Out[2] == 0)
		{		
			cout << "出：";
			for (int i = 0; i < Out[1]; ++i)
			{
				cout << Out[0];
			}
			if (Out[1] == 3 && Out[3] > 0)
			{
				cout << "带";
				if (Out[4] == 2)
				{
					cout << Out[3] << Out[3];
				}
				else if (Out[4] == 1)
				{
					cout << Out[3];
				}
			}
			cout << endl;
		}
		//顺子
		else if (Out[2] == 1)
		{
			cout << "出：";
			for (int i = 0; i < Out[1]; ++i)
			{
				cout << Out[0] + i;
			}
			cout << endl;
		}
		//2顺
		else if (Out[2] == 2)
		{
			cout << "出：";
			for (int i = 0; i < Out[1]; ++i)
			{
				cout << Out[0] + i << Out[0] + i;
			}
			cout << endl;
		}
		//飞机
		else if (Out[2] == 3)
		{
			cout << "出：";
			for (int i = 0; i < Out[1]; ++i)
			{
				cout << Out[0] + i << Out[0] + i << Out[0] + i;
			}
			int x = Out[4];
			if (Out[4] > 0)
			{
				cout << "带";
				if (Out[4] > 1)
				{
					cout << Out[3];
				}
				cout << Out[3];
				for (int i = 1; i < Out[1]; ++i)
				{
					for (int j = 0; j < x; ++j)
					{
						cout << Out[4 + i];
					}
				}
			}
			
			cout << endl;
		}
		//炸弹
		else
		{
			cout << "出：";
			if (Out[0] == 17 && Out[2] == 4)
			{
				cout << "王炸";
			}
			else
			{
				for (int i = 0; i < 4; ++i)
				{
					cout << Out[0];
				}
				if (Out[4] > 0)
				{
					cout << "带";
					for (int i = 0; i < Out[4]; ++i)
					{
						cout<<Out[3];
					}
					for (int i = 0; i < Out[4]; ++i)
					{
						cout << Out[5];
					}
				}
			}
			cout << endl;
		}
	}
	system("pause");
	return 0;
}
#endif

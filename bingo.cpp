#include<iostream>
#include<cstdlib>
#include<time.h>
#include<iomanip>
using namespace std;

class Rnd
{ 
private:
	int start;
	int end;
public:
	Rnd()//�����ɋ� 1~25 ���� ���� �ʱ�ȭ
	{
		start =1;end = 25;
	}
	int getRNumber()//��������
	{
		int rn = (int)( (rand() % (end-start+1)) + start );
		return rn;
	}
};

class Bingo 
{
private:
	int bingoNum[5][5];  // ���Ƿ� ������ ���ڸ� �����ϴ� �迭
	int nStatus[5][5];  // bingoNum[5][5]�� ���ڰ� �ҷȴ����� üũ�ϴ� �迭
	int num[25]; // 1�迭�� 25�� ������ �����Ѵ�.
	int WBingoCount[5];//������ ���� Ȯ��
	int HBingoCount[5];//������ ���� Ȯ��
	int RBingoCount;//������ �밢�� Ȯ��
	int LBingoCount;//���� �밢�� Ȯ��

public:
	Bingo()// �� �����ڿ����� bingoNum[5][5] �� �� �̿��� ������ �ʱ�ȭ�Ѵ�. 
	{
		Rnd R;
		int i, j;
		int x;

		for(i = 0; i <25; i++)//1�� �迭�� �ߺ����� ������ �����Ѵ�.
		{
			x = R.getRNumber();
			num[i] = x;
			for(j = 0; j < i; j++)
			{
				if(num[j] == x)
				{
					i--;
					break;
				}
			}
		}
		for(i = 0; i < 5; i++)//1���迭�� 2�� �迭�� �����
		{
			for(j = 0; j < 5; j++)
			{
				bingoNum[i][j] = num[(i*5)+j];
				nStatus[i][j] = bingoNum[i][j];
			}
		}
		//----------------------------�ʱ�ȭ
		for(i=0 ; i<5 ; i++)//�迭 �ʱ�ȭ
		{
			WBingoCount[i]=0;	
			HBingoCount[i]=0;
		}
		RBingoCount=0;
		LBingoCount=0;

	}

	int checkBingo()// ���Լ��� nStatus[5][5]�� �̿��Ͽ� ���� �θ� �� �ִ��� �˻��Ѵ�.
	{	           // �����̸� return 1, �ƴϸ� return 0
		int i,j;
		int Wcount = 0;
		int Hcount = 0;
		int RCcount = 0;
		int LCcount = 0;
		int bingo =0;

		for(i=0 ; i<5 ; i++)// ����,������ ���� üũ
		{
			Wcount = 0;
			Hcount = 0;
			for(j=0 ; j<5 ; j++)
			{
				if(nStatus[i][j] == 0)//����üũ
				{
					Wcount++;
				}
				if(nStatus[j][i] == 0)//����üũ
				{
					Hcount++;
				}
				if(Wcount==5)
				{
					bingo++;
				}
				if(Hcount==5)
				{
					bingo++;
				}
			}
		}

		for(j=4,i=0 ; j>=0,i<5 ; j--,i++)
		{
			if(nStatus[j][j]==0)//���� �밢�� üũ
			{
				LCcount++;
			}
			if(nStatus[i][j]==0)//������ �밢�� üũ
			{
				RCcount++;
			}
			if(LCcount==5)
			{
				bingo++;
			}
			if(RCcount==5)
			{
				bingo++;
			}
		}
		if(bingo>=3)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	void printBingoGrid() // �� �Լ��� nStatus[5][5]�� ����Ѵ�.
	{
		for(int i = 0; i < 5; i++)
		{
			for(int j = 0; j < 5; j++)
			{
				cout << setw(3) << nStatus[i][j];
			}
			cout << "\n";
		}
		cout << "\n";
	}

	int callNumber(int number)
	{
		// �� �Լ��� int number�� �Է����� �޾� ���δ�.
		// �׸���, bingoNum[5][5]�� ���ڰ� ȣ��ƴ��� �˻��ϰ� nStatus[5][5]�� ����Ѵ�.
		// int number�� �̻��� ������ return 1
		// 	    �̻��� ������ return 0 
		//              (1~25 ������ ���ڰ� �ƴ� ���, ���ڰ� �Էµ� ���)

		int i, j;

		for(i=0 ; i<5 ; i++)
		{
			for(j=0 ; j<5 ; j++)
			{
				if(nStatus[i][j] == 0 && bingoNum[i][j]==number)
				{
					cout<<"����!! �ߺ��˴ϴ�"<<endl;
					return 0;
				}
				if(nStatus[i][j] == number)
				{
					nStatus[i][j]=0;
					return 1;
				}
			}
		}
		cout << "����!! 1~25 �߿� ���ڸ� ��������"<<endl;
		return 0;
	}

	int AI()//��ǻ���� [5][5]�迭�� ���ؼ� ����, ���� , �밢����
	{       //0������ �ľ��Ͽ� 0�� ���� ���� �ٿ� 0�� �ְ��ϴ� �˰���.
		int i,j;
		int zerocount[4]={0};//���� ū ���� ���� ���� ������ �迭�� �ֱ�
		int Wzerocount[5]={0};//������ 0 ���� ����
		int Hzerocount[5]={0};//������ 0 ���� ����
		int Wbigline = 0; // ���� 0�� ���� �� ����
		int Hbigline = 0; // ���� 0�� ���� �� ����
		int temp=0;
		int bignum=-1;//���� ���� �밢���� ���� ū ���� ����
		int result;
		int Wbigcount=0;//������ �� 0�� ���� ���� ���� 0���� ����
		int Hbigcount=0;//������ �� 0�� ���� ���� ���� 0���� ����
		int Rbigcount=0;//������ 0 ���� ����
		int Lbigcount=0;//���� 0 ���� ����
		int centercount=0; // �߾ӿ� {11,12,13,21,22,23 31,32,33}�迭 0 ���� ī��Ʈ

		if(nStatus[2][2]==0)
		{

			for(i=1 ; i<4 ; i++)// �߾ӿ� {11,12,13 21,22,23 31,32,33}�迭 0 ���� ī��Ʈ
			{
				for(j=1 ; j<4 ; j++)
				{
					if(nStatus[i][j]==0)
					{
						centercount++;
					}
				}
			}
			if(centercount<2)
			{
				for(i=1 ; i<4 ; i++)//�߾� {11,12,13,21,22,23 31,32,33}�迭�� ���ڸ� �ִ´�
				{
					for(j=1 ; j<4 ; j++)
					{
						if(nStatus[i][j]!=0)
						{
							result = nStatus[i][j];
							nStatus[i][j]=0;
							return result;
						}
					}
				}
			}

			for(i=0 ; i<5 ; i++)//���� ���� 0 üũ
			{
				for(j=0; j<5 ; j++)
				{
					if(nStatus[i][j]==0 && WBingoCount[i]==0)
					{
						Wzerocount[i]++;
						if(Wzerocount[i]==5)
						{
							WBingoCount[i]++;// ���� ������ �߿� ���� �ȴٸ� �ٽ� ���������Ѵ�.
							Wzerocount[i]=0;//�׸��� ������ ������ ������ 0���� �����. 
						}
					}
					if(nStatus[j][i]==0 && HBingoCount[i]==0)
					{
						Hzerocount[i]++;
						if(Hzerocount[i]==5)
						{
							HBingoCount[i]++;// ���� ������ �ٿ� ���� �ȴٸ� �ٽ� ���������Ѵ�.
							Hzerocount[i]=0;//�׸��� �����ٶ����� ������ 0���� �����.
						}
					}
				}
			}

			Wbigcount=Wzerocount[0];//ó�� �������� ����ū���� ��´�.
			Hbigcount=Hzerocount[0];//ó�� �������� ����ū���� ��´�.

			for(i=0 ; i<5 ; i++)//���� ���� 0�̵� ���� ã�´�.
			{
				if( Wbigcount<Wzerocount[i] )
				{
					Wbigcount=Wzerocount[i];
					Wbigline = i;
				}
				if( Hbigcount<Hzerocount[i] )
				{
					Hbigcount=Hzerocount[i];
					Hbigline = i;
				}
			}

			zerocount[0]=Wbigcount;// ���� ���� �밢���� ���ϱ� ���ؼ�
			zerocount[1]=Hbigcount;// ���� ���θ� �����Ѵ�.

			//----------------------------���⼭ ���� �밢��------------

			for(i=4,j=0 ; i>=0,j<5 ; i--,j++)
			{
				if(nStatus[j][j]==0 && LBingoCount == 0)//���� �밢��
				{
					Lbigcount++;
					if(Lbigcount==5)
					{
						LBingoCount++;
						Lbigcount=0;
					}
				}
				if(nStatus[i][j]==0 && RBingoCount ==0)//������ �밢��
				{
					Rbigcount++;
					if(Rbigcount==5)
					{
						RBingoCount++;
						Rbigcount=0;
					}
				}
			}

			zerocount[2]=Lbigcount;//���� �밢���� 0�� ������ �����Ѵ�.
			zerocount[3]=Rbigcount;//������ �밢���� 0�� ������ �����Ѵ�.

			//-------------------------------------------------------
			//zerocount[0]�� �������� 0����
			//zerocount[1]�� �������� 0����
			//zerocount[2]�� ���� �밢�� 0����
			//zerocount[3]�� ������ �밢�� 0����
			temp=zerocount[0];
			for(i=0 ; i<4 ; i++)
			{
				if(zerocount[i] >= temp)
				{
					temp=zerocount[i];//���� ���� ���� ������ �߿� ���� 0�� �������� ã�´�.
					bignum=i;//�̶� ����ū���� bignum�� �����Ѵ�.
				}
			}			

			if(bignum==0)//���ο� 0�� ���� ���� �ִ´�.
			{
				for(j=0 ; j<5 ; j++)
				{
					if(nStatus[Wbigline][j]!=0)
					{
						result = nStatus[Wbigline][j];
						nStatus[Wbigline][j]=0;
						return result;
					}
				}
			}
			else if(bignum==1)//���ο� 0�� ���� ���� �ִ´�.
			{
				for(i=0 ; i<5 ; i++)
				{
					if(nStatus[i][Hbigline]!=0)
					{
						result = nStatus[i][Hbigline];
						nStatus[i][Hbigline]=0;
						return result;
					}
				}
			}
			else if(bignum==2)//���ʴ밢���� 0�� ���� ���� �ִ´�.
			{
				for(i=0 ; i<5 ; i++)
				{
					if(nStatus[i][i]!=0)
					{
						result=nStatus[i][i];
						nStatus[i][i]=0;
						return result;
					}
				}
			}
			else if(bignum==3)//������ �������� 0�� ���� �Ϳ� �ִ´�.
			{
				for(i=0,j=4 ; i<5,j>=0 ; i++,j--)
				{
					if(nStatus[i][j]!=0)
					{
						result=nStatus[i][j];
						nStatus[i][j]=0;
						return result;
					}
				}
			}

		}
		else
		{
			result=nStatus[2][2];
			nStatus[2][2]=0; // ù��°�� nStatus[2][2]�� 0�� ������ 0�� �ִ´�.
			return result;
		}

	}
};



int main()
{
	srand((unsigned)time(NULL));

	Bingo user;
	Bingo com;

	int x;
	int num;
	int a;
	int y;

	while(1)
	{
		fflush(stdin); // ���۸� ����ش�.
		user.printBingoGrid();
		com.printBingoGrid();

		cout << "���ڸ� �����ϼ��� : ";
		x=scanf("%d",&num); // scanf�� ���� ������ �̿ܿ� ��� �Է� �źεǾ� 0�Ǵ� 1�� ����.

		cout << "----------------------------"<<endl;
		if(x==1)//x�� 1�϶����� ������ �Է������Ƿ� �ٽ� ������ �Է½�Ų��.
		{
			a=num;
		}
		if(x==0)//x�� ���ڳ� 0�� ���� �ʰ��� 26�� �ִ´�.
		{
			a=26;
		}
		if(user.callNumber(a)==0)
		{
			continue;
		}

		//----------------------------��ǻ��---------------------------
		com.callNumber(a);
		if(user.checkBingo()==1)// ����ڰ� ���� ���� �θ��� �¸�!!�� üũ
		{
			cout << "----------------------------"<<endl;
			cout << "����!! �¸��ϼ̽��ϴ�!"<<endl;
			user.printBingoGrid();
			cout << "----------------------------"<<endl;
			break;
		}
		if(com.checkBingo()==1)
		{
			cout << "----------------------------"<<endl;
			cout << "����!! �й��ϼ̽��ϴ�!"<<endl;
			com.printBingoGrid();
			cout << "----------------------------"<<endl;
			break;
		}

		y=com.AI();//��ǻ�� ����
		cout << "��ǻ�Ͱ� �θ� ����? : " << y<<endl;
		user.callNumber(y);

		if(com.checkBingo()==1)//��ǻ�Ͱ� ���� ���� �θ��� �¸�!!�� üũ
		{
			cout << "----------------------------"<<endl;
			cout << "����!! �й��ϼ̽��ϴ�!"<<endl;
			com.printBingoGrid();
			cout << "----------------------------"<<endl;
			break;
		}
		if(user.checkBingo()==1)
		{
			cout << "----------------------------"<<endl;
			cout << "����!! �¸��ϼ̽��ϴ�!"<<endl;
			user.printBingoGrid();
			cout << "----------------------------"<<endl;
			break;
		}

	}
}